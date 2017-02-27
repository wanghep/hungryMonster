#include "SocketControl.h"
#include "cocos2d.h"

//#include <android/log.h>
//#include "org_cocos2dx_cpp_jniInterface.h"
using namespace cocos2d;
using namespace std;
bool SOCKET_CONTRL:: m_GamedataNeedForControl = false;
linstenerList SOCKET_CONTRL::m_Lin[NUMBERFORLIST]; 

#define LOG_TAG "SOCKET_CONTRL"
//#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGD log

SOCKET_CONTRL::SOCKET_CONTRL()
{
	memset(m_Lin,0,sizeof(linstenerList)*NUMBERFORLIST);
	m_GamedataCome = false;
	
}

SOCKET_CONTRL::~SOCKET_CONTRL()
{

}




void SOCKET_CONTRL::regist( lisInterface *l , int type )
{
	for (int i = 0; i < NUMBERFORLIST; ++i)
	{
		LOGD("GameDataHandleFregist:%2d", type);
		if (m_Lin[i].type == SOCKET_DATA_TYPE_INVALID )
		{
			LOGD("GameDataHandleFregist1:%2d", type);
			m_Lin[i].type = type;
			m_Lin[i].plis = l;
			m_GamedataNeedForControl = true; 
			break;
		}
	}

}

void SOCKET_CONTRL::unregist(lisInterface *l )
{
	for (int i = 0 ; i < NUMBERFORLIST;++i)
	{
		if (/*m_Lin[i].plis == l &&*/ m_Lin[i].plis == l)
		{
			m_Lin[i].plis = 0 ;
			m_Lin[i].type = SOCKET_DATA_TYPE_INVALID ;
		}

	}
}




bool SOCKET_CONTRL::GameDataHandleF(gamedate gdata, int len)
{
	LOGD("GameDataHandleF:%2d:%2d", gdata.Datelenth, len);
//	char *ms = "ADASJKDzvxxvzvxvxvxvA";
//	GameDataHandleS(ms, 10);

	if (len<0 || len == 0)
	{
		return false;
	}
	if (gdata.Datelenth + 4 != len)
	{
		return false;
	}
//	regist_socket_data_l(m_linster,1);
	LOGD("GameDataHandleF:%2d", m_GamedataNeedForControl);

	memcpy(&m_gameControlData,&gdata,len);
	int gamecontroltpye = m_gameControlData.data.Type;
	LOGD("GameDataHandleF1");

	if (m_GamedataNeedForControl )
	{
		for (int i = 0 ; i < NUMBERFORLIST; ++ i)
		{
			LOGD("GameDataHandleF:%2d", m_Lin[i].type);
			if ( 0 != ( gamecontroltpye  & m_Lin[i].type ))
			{
				LOGD("GameDataHandleF:%2d", gamecontroltpye);
				m_Lin[i].plis->clientControlComming(&m_gameControlData.data);
			}
		}

	}
	LOGD("GameDataHandleF2");
	cout<<m_gameControlData.Datelenth<<endl;
	cout<<m_gameControlData.data.ID<<endl;
	cout<<m_gameControlData.data.Type<<endl;
	cout<<m_gameControlData.data.context.mouseControl.step_x<<endl ;
	cout<<m_gameControlData.data.context.mouseControl.step_y <<endl;
	//cout<<m_gameControlData.data.context.dum.dummy<<endl ;
	
	

	return true;
}

bool SOCKET_CONTRL::GameDataHandleS(char *message, int len) {

	/*
	LOGD("GameDataHandleS:%s", message);
	sendDataToRemote(message, len);
	*/
	return true;
}





