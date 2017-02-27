#include "BaseScene.h"

bool BaseScene::validCheckPass = false;

BaseScene::BaseScene(void)
{

}


BaseScene::~BaseScene(void)
{
	SOCKET_CONTRL::unregist( this);

}

bool BaseScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	SOCKET_CONTRL::regist( this,(int)(SOCKET_DATA_TYPE_MOUSE_CONTROL | SOCKET_DATA_TYPE_CLICK  ));
	/* enable touch control */
	// 创建一个事件监听器类型为 OneByOne 的单点触摸

    auto listener1 = EventListenerTouchOneByOne::create();
	// 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
    listener1->setSwallowTouches(true);

	listener1->onTouchBegan =  [this](Touch* touch, Event* event){

		return this->onTouchBegan( touch ,event );
	};
	
	// 添加监听器
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);

	/* enable socket client control **/

	auto _listener = EventListenerCustom::create("socketClientControl", [=]( EventCustom* event ){

		std::string str("Custom event 1 received, ");
        onSocketClientControl( event );
    });

    _eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);

    /*android 返回键  菜单键  监听*/
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(BaseScene::onKeyReleased, this);
    //添加到事件分发器中
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener,this);

    this->setKeypadEnabled(true);//设置相应按键消息

	return true;
}

void BaseScene::clientControlComming( DATA_t * pdata )
{
	EventCustom event("socketClientControl");
    event.setUserData( pdata );
	_eventDispatcher->dispatchEvent(&event);
}

//按键控制（检测onKeyReleased有反应）
void BaseScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode) {
	//监听返回键
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->end();
		break;
	//监听menu键
	case EventKeyboard::KeyCode::KEY_MENU:
		break;
	}
}




