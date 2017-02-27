#include "FailScene.h"

Scene* FailScene::createScene(int id)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = FailScene::create();
	layer->setId(id);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool FailScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	
	stepWidth = getContentSize().width/TOTAL_STEP_NUMBER;
	stepHight = getContentSize().height/TOTAL_STEP_NUMBER;

	setScene();

	return true;
}

void FailScene::setScene()
{
	auto background = Sprite::create("scenes/failscene/background.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, ItemPriority::PRIORITY_BACKGROUND);

	auto board = Sprite::create("scenes/failscene/board.png");
	board->setPosition(visibleSize.width / 2, visibleSize.height * 9 / 20);
	addChild(board, ItemPriority::PRIORITY_FAILBOARD);

	replayButton = Sprite::create("scenes/failscene/replay.png");
	replayButton->setPosition(board->getPositionX() - board->getContentSize().width / 5,
		board->getPositionY() - board->getContentSize().height / 6);
	
	addChild(replayButton, ItemPriority::PRIORITY_REPLAYBUTTON);

	backButton = Sprite::create("scenes/failscene/back.png");
	backButton->setPosition(board->getPositionX() + board->getContentSize().width / 5,
		board->getPositionY() - board->getContentSize().height / 6);

	addChild(backButton, ItemPriority::PRIORITY_BACKBUTTON);

	setController();
}

void FailScene::setId(int id)
{
	this->id = id;
}

void FailScene::setController()
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

bool FailScene::onTouchBegan(Touch* touch, Event* event)
{
	auto location = touch->getLocation();
	hand->setPosition(location.x, location.y - hand->getContentSize().height/2);

	if(getRect(replayButton).containsPoint(location))
	{
		GameController::getInstance()->SceneReplay(id);
	}
	if(getRect(backButton).containsPoint(location))
	{
		GameController::getInstance()->SceneBack(id);
	}

	return true;
}

void FailScene::onSocketClientControl( EventCustom* event )
{
	DATA_t* pControlData = static_cast<DATA_t*>(event->getUserData());

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
		if(getRect(replayButton).containsPoint(location))
		{
			GameController::getInstance()->SceneReplay(id);
		}
		if(getRect(backButton).containsPoint(location))
		{
			GameController::getInstance()->SceneBack(id);
		}
	}
	
        
}

bool FailScene::positionInScreenAdjust(Vec2& pos)
{
	if( pos.x <0  ) { pos.x = 0 ;}
	if( pos.x >= visibleSize.width ) { pos.x = visibleSize.width-1 ;}
	if( pos.y <0  ) { pos.y = 0 ;}
	if( pos.y >=visibleSize.height  ) { pos.y = visibleSize.height -1 ;}

	return true;
}