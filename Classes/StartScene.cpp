#include "StartScene.h"

USING_NS_CC;

#define LOG_TAG "StartScene"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

namespace
{
	const std::string BASEPATH = "scenes/startscene/";
}

std::vector<Sprite *> *StartScene::Levels = new std::vector<Sprite *>();

Scene* StartScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}
	
	visibleSize = Director::getInstance()->getVisibleSize();
	
	stepWidth = getContentSize().width/TOTAL_STEP_NUMBER;
	stepHight = getContentSize().height/TOTAL_STEP_NUMBER;

	setScene();


	return true;
}

void StartScene::setScene()
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create(BASEPATH + "background.png");

	background->setPosition(visibleSize.width/2, visibleSize.height/2);
	addChild(background, ItemPriority::PRIORITY_BACKGROUND);


	Texture2D* snow = TextureCache::sharedTextureCache()->addImage(BASEPATH + "snow.png");
	ParticleSystem* snowp = ParticleSnow::create();
	snowp->setTexture(snow);
	snowp->setScale(5.0);
	snowp->setPosition(visibleSize.width / 2,visibleSize.height);
	addChild(snowp, ItemPriority::PRIORITY_SNOW);


	this->setTitle();
	this->setController();

	level1Item = Sprite::create(BASEPATH + "level1.png");
	level1Item->setPosition(visibleSize.width * 1 / 3, visibleSize.height * 2 / 5);
	addChild(level1Item, ItemPriority::PRIORITY_LEVELITEM);
	level2Item = Sprite::create(BASEPATH + "level2.png");
	level2Item->setPosition(visibleSize.width * 2 / 3, visibleSize.height * 2 / 5);
	addChild(level2Item, ItemPriority::PRIORITY_LEVELITEM);
	level3Item = Sprite::create(BASEPATH + "level3.png");
	level3Item->setPosition(visibleSize.width * 1 / 3, visibleSize.height * 1 / 5);
	addChild(level3Item, ItemPriority::PRIORITY_LEVELITEM);
	level4Item = Sprite::create(BASEPATH + "level4.png");
	level4Item->setPosition(visibleSize.width * 2 / 3, visibleSize.height * 1 / 5);
	addChild(level4Item, ItemPriority::PRIORITY_LEVELITEM);

    /*去除游戏内退出按钮
	auto closeButton = ui::Button::create("scenes/closenormal.png", "scenes/closeselected.png");
	closeButton->setScale(2.0f);
	closeButton->setPosition(Vec2(visibleSize.width - closeButton->getContentSize().width,
		closeButton->getContentSize().height));
	closeButton->addTouchEventListener(this, toucheventselector(StartScene::touchCloseButton));
	addChild(closeButton, ItemPriority::PRIORITY_CLOSEBUTTON);
	*/
	return;
}

void StartScene::setTitle()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Monster *monster = Monster::create();
	monster->hideBoard();
	monster->setPosition(- monster->getContentSize().width, visibleSize.height * 7 / 9);
	monster->rightMove();
	ActionInterval *moveleft = MoveBy::create(3.0f, Vec3(visibleSize.width + 2 * monster->getContentSize().width, 0, 0));
	CCCallFuncN* flip = CCCallFuncN::create(this, callfuncN_selector(StartScene::MonsterFlip));
	Action* move = RepeatForever::create(Sequence::create(moveleft, flip, moveleft->reverse(), flip, NULL));
	monster->runAction(move);
	addChild(monster, ItemPriority::PRIORITY_MONSTER);
}

void StartScene::setController()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	hand = Sprite::create("scenes/hand.png");
	hand->setPosition(visibleSize.width/2, visibleSize.height/2);
	addChild(hand, ItemPriority::PRIORITY_HAND);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [this](Touch *touch, Event *event)
	{
		this->onTouchBegan(touch, event);
		return true;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void StartScene::MonsterFlip(Node *sender)
{
	Monster *monster = (Monster *)sender;
	if(monster->currentAction == monster->leftMoveAction)
		monster->rightMove();
	else
		monster->leftMove();
}

bool StartScene::onTouchBegan(Touch* touch, Event* event)
{
	auto location = touch->getLocation();
	hand->setPosition(location.x, location.y - hand->getContentSize().height/2);

	if(getRect(level1Item).containsPoint(location))
	{
		AnimalInfoTable::infoTableNumSelect(INFO_TYPE_e::INFO_TYPE_ANIMAL); //first select resource
		GameController::getInstance()->enterLevel1();
	}
/*
	if(getRect(level2Item).containsPoint(location))
	{
		GameController::getInstance()->enterLevel2();
	}
	if(getRect(level3Item).containsPoint(location))
	{
		GameController::getInstance()->enterLevel3();
	}
	if(getRect(level4Item).containsPoint(location))
	{
		GameController::getInstance()->enterLevel4();
	}
	*/
	return true;
}

void StartScene::touchCloseButton(Object* object, ui::TouchEventType type)
{
	Director::getInstance()->end();
}

void StartScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

bool StartScene::positionInScreenAdjust(Vec2& pos)
{
	if( pos.x <0  ) { pos.x = 0 ;}
	if( pos.x >= visibleSize.width ) { pos.x = visibleSize.width-1 ;}
	if( pos.y <0  ) { pos.y = 0 ;}
	if( pos.y >=visibleSize.height  ) { pos.y = visibleSize.height -1 ;}

	return true;
}

void StartScene::onSocketClientControl( EventCustom* event )
{
	log("onSocketClientControl");

	DATA_t* pControlData = static_cast<DATA_t*>(event->getUserData());
	log("onSocketClientControl:%2d", pControlData->Type);

	if( pControlData->Type == SOCKET_DATA_TYPE_MOUSE_CONTROL )
	{
		int  x = hand->getPositionX() + this->stepWidth * pControlData->context.mouseControl.step_x;
		
		int  y = hand->getPositionY() + this->stepHight * ( 0 - pControlData->context.mouseControl.step_y);
		
		auto newPosition = Vec2( x , y );
		printf( "newPosition< x , y > =  < %d , %d >\n" ,x ,y );
		if(positionInScreenAdjust(newPosition))
		{
			hand->setPosition(newPosition);
		}
		else
		{
			printf( "newPosition  out of range \n" );
		}
	}

	else if( pControlData->Type == SOCKET_DATA_TYPE_CLICK )
	{
		Point location(hand->getPositionX(), hand->getPositionY() + hand->getContentSize().height/2);

		if(getRect(level1Item).containsPoint(location))
		{
			GameController::getInstance()->enterLevel1();
		}
		
	}
        
}
