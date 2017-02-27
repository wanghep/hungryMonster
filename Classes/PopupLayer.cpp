#include "PopupLayer.h"
 
PopupLayer::PopupLayer():
m__pMenu(NULL)
, m_contentPadding(0)
, m_contentPaddingTop(0)
, m_callbackListener(NULL)
, m_callback(NULL)
, m__sfBackGround(NULL)
, m__s9BackGround(NULL)
, m__ltContentText(NULL)
, m__ltTitle(NULL)
{
     
}
 
PopupLayer::~PopupLayer(){
    CC_SAFE_RELEASE(m__pMenu);
    CC_SAFE_RELEASE(m__sfBackGround);
    CC_SAFE_RELEASE(m__ltContentText);
    CC_SAFE_RELEASE(m__ltTitle);
    CC_SAFE_RELEASE(m__s9BackGround);
}
 
bool PopupLayer::init(){
    if(!Layer::init()){
        return false;
    }
        this->setContentSize(Size::ZERO);
         
        // ��ʼ����Ҫ�� Menu
        CCMenu* menu = CCMenu::create();
        menu->setPosition(Vec2::ZERO);
        setMenuButton(menu);
         
        setTouchEnabled(true);
 
    return true;
}
 
bool PopupLayer::onTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    //
    //CCLog("PopupLayer touch");
    return true;
}
 
PopupLayer* PopupLayer::create(const char *backgroundImage){
    PopupLayer* ml = PopupLayer::create();
    ml->setSpriteBackGround(CCSprite::create(backgroundImage));
    ml->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
    return ml;
}
 
void PopupLayer::setTitle(const char *title, int fontsize){
    CCLabelTTF* ltfTitle = CCLabelTTF::create(title, "", fontsize);
    setLabelTitle(ltfTitle);
}
 
void PopupLayer::setContentText(const char *text, int fontsize, int padding, int paddingTop){
    CCLabelTTF* ltf = CCLabelTTF::create(text, "", fontsize);
    setLabelContentText(ltf);
    m_contentPadding = padding;
    m_contentPaddingTop = paddingTop;
}
 
void PopupLayer::setCallbackFunc(cocos2d::CCObject *target, SEL_CallFuncN callfun){
    m_callbackListener = target;
    m_callback = callfun;    
}
 
 
bool PopupLayer::addButton(const char *normalImage, const char *selectedImage, const char *title, int tag){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint pCenter = ccp(winSize.width / 2, winSize.height / 2);
     
    // ����ͼƬ�˵���ť
    CCMenuItemImage* menuImage = CCMenuItemImage::create(normalImage, selectedImage, this, menu_selector(PopupLayer::buttonCallback));
    menuImage->setTag(tag);
    menuImage->setPosition(pCenter);
     
    // �������˵��������λ��
    CCSize imenu = menuImage->getContentSize();
    CCLabelTTF* ttf = CCLabelTTF::create(title, "", 20);
    ttf->setColor(ccc3(0, 0, 0));
    ttf->setPosition(ccp(imenu.width / 2, imenu.height / 2));
    menuImage->addChild(ttf);
     
    getMenuButton()->addChild(menuImage);
    return true;
}
 
void PopupLayer::buttonCallback(cocos2d::CCObject *pSender){
    Node* node = dynamic_cast<Node*>(pSender);
    //CCLog("touch tag: %d", node->getTag());
    if (m_callback && m_callbackListener){
        (m_callbackListener->*m_callback)(node);
    }
    this->removeFromParent();
}
 
void PopupLayer::onEnter(){
    CCLayer::onEnter();
     
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint pCenter = ccp(winSize.width / 2, winSize.height / 2);
     
    CCSize contentSize;
    // �趨�ò�����������ʱ����
    if (getContentSize().equals(Size::ZERO)) {
        getSpriteBackGround()->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(getSpriteBackGround(), 0, 0);
        contentSize = getSpriteBackGround()->getTexture()->getContentSize();
    } else {
        Scale9Sprite *background = getSprite9BackGround();
        background->setContentSize(getContentSize());
        background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(background, 0, 0);
        contentSize = getContentSize();
    }
     
     
    // ��Ӱ�ť����������λ��
    this->addChild(getMenuButton());
    float btnWidth = contentSize.width / (getMenuButton()->getChildrenCount() + 1);
     
    Vector<Node*> vecArray = getMenuButton()->getChildren();
    CCObject* pObj = NULL;
    int i = 0;
    for(auto& e : vecArray){
        CCNode* node = dynamic_cast<Node*>(e);
        node->setPosition(Point(winSize.width/2 - contentSize.width/2+btnWidth*(i+1),winSize.height/2-contentSize.height/3));
        i++;
    }
  /*  CCARRAY_FOREACH(array, pObj){
        CCNode* node = dynamic_cast<ccnode*>(pObj);
        node->setPosition(ccp( winSize.width / 2 - contentSize.width / 2 + btnWidth * (i + 1), winSize.height / 2 - contentSize.height / 3));
        i++;
    }*/
     
     
    // ��ʾ�Ի������
    if (getLabelTitle()){
        getLabelTitle()->setPosition(ccpAdd(pCenter, ccp(0, contentSize.height / 2 - 35.0f)));
        this->addChild(getLabelTitle());
    }
     
    // ��ʾ�ı�����
    if (getLabelContentText()){
        CCLabelTTF* ltf = getLabelContentText();
        ltf->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        ltf->setDimensions(CCSizeMake(contentSize.width - m_contentPadding * 2, contentSize.height - m_contentPaddingTop));
        ltf->setHorizontalAlignment(kCCTextAlignmentLeft);
        this->addChild(ltf);
    }
 
    // ����Ч��
    CCAction* popupLayer = CCSequence::create(CCScaleTo::create(0.0, 0.0),
                                              CCScaleTo::create(0.06, 1.05),
                                              CCScaleTo::create(0.08, 0.95),
                                              CCScaleTo::create(0.08, 1.0), NULL);
    this->runAction(popupLayer);
 
}
 
void PopupLayer::onExit(){
     
    //CCLog("popup on exit.");
    CCLayer::onExit();
}