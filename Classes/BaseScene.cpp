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
	// ����һ���¼�����������Ϊ OneByOne �ĵ��㴥��

    auto listener1 = EventListenerTouchOneByOne::create();
	// �����Ƿ���û�¼����� onTouchBegan �������� true ʱ��û
    listener1->setSwallowTouches(true);

	listener1->onTouchBegan =  [this](Touch* touch, Event* event){

		return this->onTouchBegan( touch ,event );
	};
	
	// ��Ӽ�����
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, this);

	/* enable socket client control **/

	auto _listener = EventListenerCustom::create("socketClientControl", [=]( EventCustom* event ){

		std::string str("Custom event 1 received, ");
        onSocketClientControl( event );
    });

    _eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);

    /*android ���ؼ�  �˵���  ����*/
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(BaseScene::onKeyReleased, this);
    //��ӵ��¼��ַ�����
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener,this);

    this->setKeypadEnabled(true);//������Ӧ������Ϣ

	return true;
}

void BaseScene::clientControlComming( DATA_t * pdata )
{
	EventCustom event("socketClientControl");
    event.setUserData( pdata );
	_eventDispatcher->dispatchEvent(&event);
}

//�������ƣ����onKeyReleased�з�Ӧ��
void BaseScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode) {
	//�������ؼ�
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->end();
		break;
	//����menu��
	case EventKeyboard::KeyCode::KEY_MENU:
		break;
	}
}




