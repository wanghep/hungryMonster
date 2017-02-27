#ifndef _GAME_STARTSCENE_H_
#define _GAME_STARTSCENE_H_

#include <vector>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameController.h"
#include "BaseScene.h"
#include "Auxiliary.h"

USING_NS_CC;
using namespace ui;

class StartScene : public BaseScene
{

private:

	static std::vector<Sprite *> *Levels;
	Node *gameLayer;
	void setScene();
	void setTitle();
	void setController();
	void MonsterFlip(Node *sender);
	void touchCloseButton(Object* object, TouchEventType type);

	Size visibleSize;
	int stepWidth;
	int stepHight;
	bool positionInScreenAdjust(Vec2& pos);

	Sprite *level1Item;
	Sprite *level2Item;
	Sprite *level3Item;
	Sprite *level4Item;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();

	Sprite *hand;
	
    void menuCloseCallback(cocos2d::Ref* pSender);
	void onSocketClientControl( EventCustom* event );
	bool onTouchBegan(Touch* touch, Event* event);
	CREATE_FUNC(StartScene);
};

#endif // _GAME_STARTSCENE_H_
