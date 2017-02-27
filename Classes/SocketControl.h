#pragma once
#include <iostream>
#include <string>

#define  NUMBERFORLIST  20
using namespace std;


typedef enum
{
	SOCKET_DATA_TYPE_INVALID		= 0	,
	SOCKET_DATA_TYPE_MOUSE_CONTROL	= 1,
	SOCKET_DATA_TYPE_CLICK			= 2,
	SOCKET_DATA_TYPE_GAME_OVER		= 4,

}SOCKET_DATA_TYPE;

typedef struct {

	int ID ;

	SOCKET_DATA_TYPE Type;

	union{

		struct 
		{
			int step_x;		// 1;2;3;4 +-
			int step_y;		//1;2;3;4  +1
		}mouseControl;

		/*struct{
			int dummy;
		}dum;*/

	}context;
}DATA_t; 


typedef struct 
{
	int Datelenth;
	DATA_t data;
} gamedate;



// list for 
// List <( type , lisInterface* ) >  linstenerList;


class lisInterface
{
public:
	virtual void clientControlComming( DATA_t * pdata ) =0;

};


typedef struct 
{
	lisInterface * plis; //interface


	int type;                 // 0 : invalid ,1: mouse control ,2: click  3: game over

}linstenerList;




class SOCKET_CONTRL{



public:
	SOCKET_CONTRL();
	~SOCKET_CONTRL();

	gamedate m_gameControlData;           //  the game control data form the socket 
	
	bool m_GamedataCome;                 //  if the socket recive the data ,come true

	static bool m_GamedataNeedForControl; //  if anyone regist,come true, but if the regist list is empty,come false

	static linstenerList m_Lin[NUMBERFORLIST];         //  regist list

	static void regist(  lisInterface *l , int type ); // add into LIST 
	
	bool GameDataHandleF(gamedate data, int len);

	bool GameDataHandleS(char *message, int len);

	static void unregist(lisInterface *l );            // removoe l type

	//lisInterface * m_linster;

	//send( DATA_t *p )
};
