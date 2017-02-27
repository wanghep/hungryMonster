#include <iostream>
#include <WinSock2.h>
#include "process.h" 
#include "SocketControl.h"
#pragma comment(lib,"ws2_32.lib")

#define  CLIENTNUMBER  5    //  the most number of the clients that connect to the service socket


class GameSocket
{
public:
	GameSocket();
	~GameSocket();


public:
	static int IDnumber;                // client ID number
	static bool exitFlag ;             // exit ?
	static SOCKET m_SocketService;      //·þÎñÆ÷Ì×½Ó×Ö
	static bool m_DataRevUpdateFlag;      // if need receive the data is true, others false

	HANDLE   m_SocketDataRevThread ;
	static HANDLE   socketRevThread[CLIENTNUMBER];   // the client handle process
	static SOCKET	m_sock_con[CLIENTNUMBER];          // the client socket

	int SocketInit();


	static unsigned __stdcall clientListen( void * pParam );
	static unsigned __stdcall socketDataRecieve( void *pParam );

	void  UpdateDataRev();  // open the data receive
	void  CloseDataRev();   // close the data receive

	static bool SendData(  char* pData , int dataLen,SOCKET sock) ;  // send the data to the client
	bool sendCloseDataToClient(SOCKET sock);                         // send the game close information to the client

	int SocketClose();

	void SocketThreadStart();

	static SOCKET_CONTRL m_contrl;



};


