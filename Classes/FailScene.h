#ifndef _GAME_FAILSCENE_H_
#define _GAME_FAILSCENE_H_

#include <iostream>
#include "cocos2d.h"
#include "GameController.h"
#include "BaseScene.h"
#include "Auxiliary.h"

USING_NS_CC;

class FailScene : public BaseScene
{
private:
	int id;

	Size visibleSize;
	Vec2 origin;
	Sprite *hand;
	Sprite *replayButton;
	Sprite *backButton;

	void setScene();
	void setController();

	int stepWidth;
	int stepHight;
	bool positionInScreenAdjust(Vec2& pos);

public:

	void setId(int);

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene(int);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	bool onTouchBegan(Touch* touch, Event* event);

	void onSocketClientControl( EventCustom* event );
	// implement the "static create()" method manually
	CREATE_FUNC(FailScene);
};


#endif