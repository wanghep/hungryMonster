#include "Monster.h"

int Monster::scores[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int Monster::life = MAX_LIFE_NUMBER;
Monster::Monster()
{
	id = -1;
}
Monster *Monster::create()
{

	auto monster = new Monster();
	if(monster && monster->init())
	{
		monster->autorelease();
		return monster;
	}
	else
	{
		return nullptr;
	}
}

void Monster::staticVarInit()
{
	Monster::scores[0] = 0;
	Monster::life = MAX_LIFE_NUMBER;
}

void Monster::setId( int newId )
{
	if( newId == 0 )
	{
		staticVarInit();
	}

	id = newId;
}

int Monster::getId()
{
	return id;
}


bool Monster::init()
{
	
	if(!Sprite::init())
		return false;


	setAnimation();
	setBoard();

	currentAction = nullptr;
	this->leftMove();

	return true;
}

Monster::~Monster()
{
	log("Monster destruction");
}

int Monster::getLife()
{
	return life;
}

void Monster::addALife()
{

	if(life < MAX_LIFE_NUMBER )
	{
		life++;
	}
}

//if real dead return true , or return false 
bool Monster::deadALife()
{
	if( life > 0 )
	{
		life--;
	}
	if( life <= 0 )
	{
		
		return true;
	}
	else
	{
		return false;
	}
}

void Monster::leftMove( Node * n )
{
	if(currentAction == leftMoveAction)
		return;
	//stopAllActions();
	if(currentAction)
	{
		
		stopAction(currentAction);
	}
	currentAction = leftMoveAction;
	this->animationSprite->runAction(leftMoveAction);
	//leftMoveAction->retain();
	//rightMoveAction->retain();
}

void Monster::rightMove( Node * n  )
{
	if(currentAction == rightMoveAction)
		return;
	//stopAllActions();
	if(currentAction)
	{
		stopAction(currentAction);
	}
	currentAction = rightMoveAction;
	this->animationSprite->runAction(rightMoveAction);
	//leftMoveAction->retain();
	//rightMoveAction->retain();
}

void Monster::setBoard()
{
	board = Sprite::create("monster/board.png");
	board->setScale(1.2);
	board->setPosition(this->getContentSize().width/3, this->getContentSize().height * 10 / 20);
	addChild(board, ItemPriority::PRIORITY_MONSTER_BOARD);

	word = LabelTTF::create("test", "Î¢ÈíÑÅºÚ", 36);
	word->setPosition(board->getContentSize().width/2, board->getContentSize().height * 4 / 5);

	board->addChild(word, ItemPriority::PRIORITY_MONSTER_WORD);
}

void Monster::hideBoard()
{
	board->removeFromParent();
}

bool Monster::capture(Animal *anim)
{
	auto animRect = anim->getBoundingBox();
	auto cageRect = this->getBoundingBox();

	if(isContained(animRect, cageRect))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//whether rect1 is contained in rect2
bool isContained(Rect rect1, Rect rect2)
{
	return rect2.getMaxX() > rect1.getMaxX()
		&& rect2.getMaxY() > rect1.getMaxY()
		&& rect2.getMinX() < rect1.getMinX()
		&& rect2.getMinY() < rect1.getMinY();
}

void Monster::setAnimation()
{

	contentSize = Sprite::create("monster/left1.png")->getContentSize();
	this->setContentSize(contentSize);

	animationSprite = Sprite::create();
	animationSprite->setPosition(contentSize.width/2, contentSize.height/2);

	this->addChild(animationSprite, ItemPriority::PRIORITY_MONSTER_ANIMATION);

	Animation *leftAnimation = CCAnimation::create();  

	for (int i = 1; i < 7; i++)  
	{  
		char szImageFileName[128] = {0};  
		sprintf(szImageFileName, "monster/left%d.png", i);  
		leftAnimation->addSpriteFrameWithFileName(szImageFileName);    
	}  
	leftAnimation->setDelayPerUnit(0.5f / 6.0f); 
	leftAnimation->setRestoreOriginalFrame(true);
	Animate *leftAnimate = Animate::create(leftAnimation);  

	leftMoveAction = RepeatForever::create(dynamic_cast<CCActionInterval *>
		(CCSequence::create(leftAnimate, leftAnimate->reverse(), NULL)));
	leftMoveAction->retain();

	Animation *rightAnimation = CCAnimation::create();  
	rightAnimation->retain();

	for (int i = 1; i < 7; i++)  
	{  
		char szImageFileName[128] = {0};  
		sprintf(szImageFileName, "monster/right%d.png", i);  
		rightAnimation->addSpriteFrameWithFileName(szImageFileName);    
	}  

	rightAnimation->setDelayPerUnit(0.5f / 6.0f); 
	rightAnimation->setRestoreOriginalFrame(true);
	Animate *rightAnimate = Animate::create(rightAnimation);  

	rightMoveAction = RepeatForever::create(dynamic_cast<ActionInterval *>
		(CCSequence::create(rightAnimate, rightAnimate->reverse(), NULL)));
	rightMoveAction->retain();

	FiniteTimeAction *leftMoveActionDone = CallFuncN::create(this, callfuncN_selector(Monster::leftMove));  
	FiniteTimeAction *rightMoveActionDone = CallFuncN::create(this, callfuncN_selector(Monster::rightMove));  

	/* left angry */
	Animation *leftAngryAnimation = CCAnimation::create();  
	leftAngryAnimation->retain();

	leftAngryAnimation->addSpriteFrameWithFileName("monster/left1.png");
	leftAngryAnimation->addSpriteFrameWithFileName("monster/left1_drak.png");
	  

	leftAngryAnimation->setDelayPerUnit(0.2); 
	leftAngryAnimation->setRestoreOriginalFrame(true);
	Animate *leftAngryAnimate = Animate::create(leftAngryAnimation);  

	leftAngryAction = Sequence::create( Repeat::create( leftAngryAnimate , 3 ), leftMoveActionDone, NULL);
	leftAngryAction->retain();

	/* right angry */
	Animation *rightAngryAnimation = CCAnimation::create();  
	rightAngryAnimation->retain();

	rightAngryAnimation->addSpriteFrameWithFileName("monster/right1.png");
	rightAngryAnimation->addSpriteFrameWithFileName("monster/right1_drak.png");
	  

	rightAngryAnimation->setDelayPerUnit(0.2); 
	rightAngryAnimation->setRestoreOriginalFrame(true);
	Animate *rightAngryAnimate = Animate::create(rightAngryAnimation);  

	rightAngryAction = Sequence::create( Repeat::create( rightAngryAnimate , 3 ), rightMoveActionDone, NULL);
	rightAngryAction->retain();


	/* left happy */
	Animation *leftHappyAnimation = CCAnimation::create();  
	leftHappyAnimation->retain();

	leftHappyAnimation->addSpriteFrameWithFileName("monster/left1_happy.png");
	leftHappyAnimation->addSpriteFrameWithFileName("monster/left1_happy.png");
	leftHappyAnimation->addSpriteFrameWithFileName("monster/left1_happy.png");
	leftHappyAnimation->addSpriteFrameWithFileName("monster/left1_happy.png");
	  

	leftHappyAnimation->setDelayPerUnit(0.5f / 6.0f); 
	leftHappyAnimation->setRestoreOriginalFrame(true);
	Animate *leftHappyAnimate = Animate::create(leftHappyAnimation);  
	leftHappyAnimate->retain();
	leftHappyAction = Sequence::create( leftHappyAnimate , leftMoveActionDone, NULL);
	leftHappyAction->retain();

	/* right happy */
	Animation *rightHappyAnimation = CCAnimation::create();  
	rightHappyAnimation->retain();

	rightHappyAnimation->addSpriteFrameWithFileName("monster/right1_happy.png");
	rightHappyAnimation->addSpriteFrameWithFileName("monster/right1_happy.png");
	rightHappyAnimation->addSpriteFrameWithFileName("monster/right1_happy.png");
	rightHappyAnimation->addSpriteFrameWithFileName("monster/right1_happy.png");
	  

	rightHappyAnimation->setDelayPerUnit(0.5f / 6.0f); 
	rightHappyAnimation->setRestoreOriginalFrame(true);
	Animate *rightHappyAnimate = Animate::create(rightHappyAnimation);  
	rightHappyAnimate->retain();
	rightHappyAction = Sequence::create( rightHappyAnimate, rightMoveActionDone, NULL);
	rightHappyAction->retain();

	/*dead*/
	Animation *deadAnimation = CCAnimation::create();  
	deadAnimation->retain();

	deadAnimation->addSpriteFrameWithFileName("monster/bomb1.png");
	deadAnimation->addSpriteFrameWithFileName("monster/bomb2.png");
	deadAnimation->addSpriteFrameWithFileName("monster/bomb3.png");

	deadAnimation->setDelayPerUnit(0.2); 
	//deadAnimation->setRestoreOriginalFrame(true);
	Animate *deadAnimate = Animate::create(deadAnimation);  
	deadAnimate->retain();
	deadAction = Sequence::create( deadAnimate, CCFadeOut::create(1.0), NULL);
	deadAction->retain();

	

}

void Monster::angry()
{
	
	//stopAllActions();

	this->stopAction(currentAction);
	this->stopAction(leftHappyAction);
	this->stopAction(rightHappyAction);
	this->stopAction( leftAngryAction );
	this->stopAction( rightAngryAction );

	if(currentAction == leftMoveAction)
	{
		currentAction = NULL;
		animationSprite->runAction( leftAngryAction );
	}
	else
	{
		currentAction = NULL;
		animationSprite->runAction( rightAngryAction );
	}

	
}



void Monster::happy()
{
	this->stopAction(currentAction);
	this->stopAction(leftHappyAction);
	this->stopAction(rightHappyAction);
	this->stopAction( leftAngryAction );
	this->stopAction( rightAngryAction );

	if(currentAction == leftMoveAction)
	{
		currentAction = NULL;
		animationSprite->runAction( leftHappyAction );
	}
	else
	{
		currentAction = NULL;
		animationSprite->runAction( rightHappyAction );
	}
}

void Monster::dead()
{
	this->stopAction(currentAction);
	this->stopAction(leftHappyAction);
	this->stopAction(rightHappyAction);
	this->stopAction( leftAngryAction );
	this->stopAction( rightAngryAction );
	currentAction = NULL;

	animationSprite->runAction( deadAction );
}

void Monster::setWord(std::string word)
{
	this->word->setString(word);
}