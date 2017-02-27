
#include "GameSocket.h"

using namespace std;
const unsigned short LISTEN_PORT = 8700;

int GameSocket::IDnumber = 0;
bool GameSocket::m_DataRevUpdateFlag = true;

bool GameSocket::exitFlag = false;

SOCKET GameSocket::m_SocketService = 0;

SOCKET_CONTRL GameSocket:: m_contrl;

SOCKET GameSocket::m_sock_con[CLIENTNUMBER] = {0};
HANDLE GameSocket::socketRevThread[CLIENTNUMBER] = {0};

GameSocket::GameSocket()
{
	m_SocketDataRevThread = NULL;
	SocketInit();
}
GameSocket::~GameSocket()
{
	SocketClose();
}



int GameSocket::SocketInit()
{
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData;

	int err = WSAStartup(wVersionRequested, &wsaData);

	if ( 0 != err )
	{
		cout<<"WSAStartup failed. return: "<<err<<endl;
		return -1;
	}

	if ( wsaData.wVersion != wVersionRequested )
	{
		cout<<"wsaData.wVersion: "<<wsaData.wVersion<<" is not equal to wVersionRequested: "<<wVersionRequested<<endl;
		WSACleanup();
		return -2;
	}

	m_SocketService = socket(AF_INET, SOCK_STREAM, 0);

	if ( INVALID_SOCKET == m_SocketService )
	{
		cout<<"socket error: "<<WSAGetLastError()<<endl;
		return -3;
	}

	SOCKADDR_IN addr_server;
	addr_server.sin_family	= AF_INET;
	addr_server.sin_port	= htons(LISTEN_PORT);
	addr_server.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	err = bind(m_SocketService, (SOCKADDR*)&addr_server, sizeof(addr_server));
	
	if ( SOCKET_ERROR == err )
	{
		cout<<"bind error: "<<WSAGetLastError()<<endl;
		return -4;
	}

	//err = listen(m_SocketService, SOMAXCONN);
	err = listen(m_SocketService, CLIENTNUMBER);

	if ( SOCKET_ERROR == err )
	{
		cout<<"listen error: "<<WSAGetLastError()<<endl;
		return -5;
	}
	cout<<"Start listening on port "<<LISTEN_PORT<<endl;

	SocketThreadStart();
	return true;

}


SOCKADDR_IN addr_client;
int addrlen = sizeof(addr_client);

unsigned __stdcall GameSocket::clientListen(void * pParam)
{
	if (m_SocketService == 0 )
	{
		return false;
	}
	gamedate clientID;
	memset(&clientID,0,sizeof(gamedate));
	clientID.Datelenth = sizeof(gamedate);
	int k = 0;
	
	while (! GameSocket::exitFlag )
	{
		m_sock_con[k] = accept(m_SocketService, (SOCKADDR*)&addr_client, &addrlen);

		if ( INVALID_SOCKET != m_sock_con[k] && (! GameSocket::exitFlag) && k<CLIENTNUMBER)
		{
			IDnumber++;
			clientID.data.ID = IDnumber;
			SendData((char*)&clientID,sizeof(gamedate),m_sock_con[k]);  //  send the ID information to the client

			cout<<inet_ntoa(addr_client.sin_addr)<<":"<<ntohs(addr_client.sin_port)<<" connected!"<<endl;

		    socketRevThread[k] = (HANDLE)_beginthreadex(NULL, 0, &(GameSocket::socketDataRecieve), &m_sock_con[k],  0,NULL);
			k++;
			
		}
		else
		{
			int error = WSAGetLastError();
			cout<<"accept error: "<<WSAGetLastError()<<endl;

			closesocket(m_sock_con[k]); //关闭套接字 
			return false;
			//break;
			//WSACleanup();  //释放套接字资源  
		}
	}

	return true;
	
}

unsigned __stdcall GameSocket::socketDataRecieve(void * pParam)
{

	SOCKET *sock_con = (SOCKET*)pParam;
	int err = 0;
	int dataAll = 0;
	gamedate rev;
	memset(&rev,0,sizeof(gamedate));

	while ( !GameSocket::exitFlag )
	{
		if (GameSocket::m_DataRevUpdateFlag)
		{
			err = recv(*sock_con, (char*)&rev, sizeof(gamedate) - dataAll, 0);
			dataAll += err;

			if (dataAll == sizeof(gamedate))
			{
				m_contrl.GameDataHandleF(rev,dataAll);
				dataAll = 0;
			}

			if ( err <= 0 )
			{
				cout<<"recv error: "<<WSAGetLastError()<<endl;
				break;
			}

			//cout<<err<<endl;
		}		

	}

	cout<<inet_ntoa(addr_client.sin_addr)<<":"<<ntohs(addr_client.sin_port)<<" left!"<<endl;

	try {

		int errs = closesocket(*sock_con);
		if ( SOCKET_ERROR == errs )
		{
			cout<<"closesocket error: "<<WSAGetLastError()<<endl;
		
		}
	}
	catch( ... )
	{
		cout<<"socketDataRecieve got a execption ";
	}
	return 0;

}


bool GameSocket::SendData( char* pData , int dataLen,SOCKET sock)
{

	if( NULL == m_SocketService )
	{
		return false;
	}
	if ( INVALID_SOCKET != sock )
	{
		int retVal = send(sock, (char*)pData , dataLen, 0);

		if (SOCKET_ERROR == retVal)
		{
			cout << "send failed!" << endl;
			return false;
		}

	}
	else
	{
		cout<<"accept error: "<<WSAGetLastError()<<endl;
		return false;
	}

	return true;

}

void GameSocket::UpdateDataRev()
{
	m_DataRevUpdateFlag = true;
}
void GameSocket::CloseDataRev()
{
	m_DataRevUpdateFlag = false;
}


int GameSocket::SocketClose()
{
	GameSocket::exitFlag = true;
	
	
	if( m_SocketService != 0 )
	{
		closesocket(m_SocketService); 
		m_SocketService = 0;   
		WSACleanup(); 

	}

	for (int i = 0 ; i < CLIENTNUMBER; ++i)
	{
		if (socketRevThread[i] != 0)
		{
			CloseHandle(socketRevThread[i]);
			socketRevThread[i] = NULL;

		}
	}

	if(m_SocketDataRevThread!=NULL)
	{
		CloseHandle(m_SocketDataRevThread);
		m_SocketDataRevThread = NULL;
	}	

	return m_SocketService;
}

void  GameSocket::SocketThreadStart() 
{

	if( m_SocketService != 0 )
	{	
		m_SocketDataRevThread = (HANDLE)_beginthreadex(NULL, 0, &(GameSocket::clientListen), NULL,  0,NULL);
	}
	if ( m_SocketDataRevThread == 0 )
	{   
		printf("no thread create  1\n");
	}
}
bool GameSocket::sendCloseDataToClient(SOCKET sock)
{

	if( NULL == m_SocketService )
	{
		return false;
	}
	gamedate ms;
	memset(&ms,0,sizeof(gamedate));
	ms.Datelenth = sizeof(gamedate);
	ms.data.Type = SOCKET_DATA_TYPE_GAME_OVER;   // close the game

	if ( INVALID_SOCKET != sock )
	{
		int retVal = send(sock, (char*)&ms , sizeof(gamedate), 0);

		if (SOCKET_ERROR == retVal)
		{
			cout << "send failed!" << endl;
			return false;
		}

	}
	else
	{
		cout<<"accept error: "<<WSAGetLastError()<<endl;
		return false;
	}

	return true;


}


//DWORD WINAPI funproc(LPVOID lpparentet)  
//{  
	//Sleep(10000);  

	//GameSocket m;
	//m.SocketInit();
	//m.DataReceive();

//	cout<<"子线程线程！"<<endl;  
	//return 0;  
//} 

//void main()
//{
	
//	GameSocket s;

	//s.SocketInit();
	
	//CreateThread(NULL,0,funproc,NULL,0,NULL);  

	//s.m_SocketDataRevThread = (HANDLE)_beginthreadex(NULL, 0,(unsigned int (__stdcall *)(void *))s.DataReceive(), NULL,  0,NULL);

	
	


	//s.SocketThreadStart();

	
	/*
		char send_buf[256] = {0};

		cin.getline(send_buf, 256);

		cin.clear();

		

		s.DataSend(send_buf,sizeof(send_buf));

		cout<<"ssss"<<endl;*/
	
		//Sleep(10000);  






//}
