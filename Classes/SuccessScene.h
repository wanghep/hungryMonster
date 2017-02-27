#ifndef _GAME_SUCCESSSCENE_H_
#define _GAME_SUCCESSSCENE_H_

#include <iostream>
#include "cocos2d.h"
#include "GameController.h"
#include "Auxiliary.h"

USING_NS_CC;

class SuccessScene : public Layer
{
public:
	static void setScore(int);

private:
	int id;
	static int score;

	Size visibleSize;
	Vec2 origin;
	Sprite *backButton;
	Sprite *nextButton;
	Sprite *hand;

	int stepWidth;
	int stepHight;

	void setScene();
	void setController();
	
	bool positionInScreenAdjust(Vec2& pos);

public:

	void setId(int);

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene(int id);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	bool onTouchBegan(Touch* touch, Event* event);
	// implement the "static create()" method manually

	void onSocketClientControl( EventCustom* event );

	CREATE_FUNC(SuccessScene);
};


#endif