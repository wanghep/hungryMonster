#pragma once
#include "cocos2d.h"
#include "SocketControl.h"

USING_NS_CC;

#define TOTAL_STEP_NUMBER 50

class BaseScene :	public cocos2d::Layer , public lisInterface
{
public:
	BaseScene(void);
	
	~BaseScene(void);
	
	static bool validCheckPass ;

	bool init();

	void clientControlComming( DATA_t * pdata );

	virtual bool onTouchBegan(Touch* touch, Event* event) = 0;
		
	virtual void onSocketClientControl( EventCustom* event ) = 0;

	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

};
