#include "SuccessScene.h"

int SuccessScene::score = 0;

Scene* SuccessScene::createScene(int id)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SuccessScene::create();
	layer->setId(id);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool SuccessScene::init()
{
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

void SuccessScene::setScene()
{
	auto background = Sprite::create("scenes/successscene/background.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, ItemPriority::PRIORITY_BACKGROUND);

	auto board = Sprite::create("scenes/successscene/board.png");
	board->setPosition(visibleSize.width / 2, visibleSize.height * 9 / 20);
	addChild(board, ItemPriority::PRIORITY_SUCCESSBOARD);

	auto boardConSiz = board->getContentSize();

	auto monHead = Sprite::create("scenes/successscene/monhead.png");
	monHead->setPosition(monHead->getContentSize().width * 2,
		boardConSiz.height / 2 + monHead->getContentSize().height / 3);
	board->addChild(monHead);


	auto scoreBoard = LabelTTF::create("Score: " + itos(score), "微软雅黑 Bold", 96); // 宽字符通不过编译
	scoreBoard->setPosition(monHead->getPositionX() + monHead->getContentSize().width +
		scoreBoard->getContentSize().width / 2, monHead->getPositionY());
	scoreBoard->setColor(Color3B::YELLOW);
	board->addChild(scoreBoard);

	nextButton = Sprite::create("scenes/successscene/next.png");
	nextButton->setPosition(board->getPositionX() - board->getContentSize().width / 5,
		board->getPositionY() - board->getContentSize().height / 6);

	backButton = Sprite::create("scenes/successscene/back.png");
	backButton->setPosition(board->getPositionX() + board->getContentSize().width / 5,
		board->getPositionY() - board->getContentSize().height / 6);

	addChild(backButton, ItemPriority::PRIORITY_BACKBUTTON);
	addChild(nextButton, ItemPriority::PRIORITY_NEXTBUTTON);

	setController();

}

void SuccessScene::setController()
{
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

void SuccessScene::setId(int id)
{
	this->id = id;
}

void SuccessScene::setScore(int n)
{
	score = n;
}

bool SuccessScene::onTouchBegan(Touch* touch, Event* event)
{
	auto location = touch->getLocation();
	hand->setPosition(location.x, location.y - hand->getContentSize().height/2);

	if(getRect(nextButton).containsPoint(location))
	{
		log("SceneNext Called");
		GameController::getInstance()->SceneNext(id);
	}
	if(getRect(backButton).containsPoint(location))
	{
		log("SceneBack Called");
		GameController::getInstance()->SceneBack(id);
	}

	return true;
}

bool SuccessScene::positionInScreenAdjust(Vec2& pos)
{
	if( pos.x <0  ) { pos.x = 0 ;}
	if( pos.x >= visibleSize.width ) { pos.x = visibleSize.width-1 ;}
	if( pos.y <0  ) { pos.y = 0 ;}
	if( pos.y >=visibleSize.height  ) { pos.y = visibleSize.height -1 ;}

	return true;
}

void SuccessScene::onSocketClientControl( EventCustom* event )
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
		if(getRect(nextButton).containsPoint(location))
		{
			log("SceneNext Called");
			GameController::getInstance()->SceneNext(id);
		}
		if(getRect(backButton).containsPoint(location))
		{
			log("SceneBack Called");
			GameController::getInstance()->SceneBack(id);
		}
	}
	
}