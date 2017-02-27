#include "LevelBaseScene.h"
#include "WordAnimal.h"
#include "PopupLayer.h"
#include "define.h"
bool LevelBaseScene::mute = false;
int randomNum = 0;
void generateValidFile();
bool validCheck( );
int payHandleShark = 0xFFFFFFFF;
int gameSpeedBeforPause = INFINITE_GAME_SPEED;
int LevelBaseScene::gameSpeed = 5;
LevelBaseScene::LevelBaseScene()
{
	targetCount = 0;
	finishedCount = 0;
	runningAnimalNum = 0;
	srand(time(NULL));// init seed  
	targetIndex = 0;
	addAnimalInterval = 0.1; //0.5s normal 0.4 , 0.3 ,0.2  
	//gameSpeed = 5; // 2-5 , 2:the fastest 5: the lowest
	speedControlCount = 0;
	usedInfoTableIndex = 0;
	stageLastEndFlag = true;
	muteSprite = NULL;
	howManyAnimalDealWithInOneStage = MAX_ANIMAL_ARRAY_NUM_EASY;

}


LevelBaseScene::~LevelBaseScene()
{

}


void LevelBaseScene::pauseGame()
{
	gameSpeedBeforPause = gameSpeed;
	gameSpeed = INFINITE_GAME_SPEED;

}
void LevelBaseScene::resumeGame()
{
	gameSpeed = gameSpeedBeforPause;
	gameSpeedBeforPause = INFINITE_GAME_SPEED;
}

bool LevelBaseScene::init()
{
	//progress = NULL;
	log("LOG: enter init()");

	if ( !BaseScene::init() )
	{
		log("LOG: BaseScene init() false");
		return false;
	}

	setMember();
	stageInit();
	setScene();
	
	gameLogic();

	return true;
}

// init()
void LevelBaseScene::setMember()
{
	stageStep = GAME_LOGIC_STEP1;
	bloom = FULL_BLOOM_VOLUM;
	visibleSize = Director::getInstance()->getVisibleSize();
	stepWidth = visibleSize.width / TOTAL_STEP_NUMBER;
	stepHeight = visibleSize.height / TOTAL_STEP_NUMBER;

	animalArray = Array::create();
	animalArray->retain();
	
	monsterArray = Array::create();
	monsterArray->retain();

	scoreBoardArray = Array::create();
	scoreBoardArray->retain();

	timerCount = 0;
	captureCount = 0;
	monsterCount = 0;
	comboCount = 0;
	targetExisted = false;

	/*
	//todo get diffical setting 
	switch( stage )
	{ // easy 
	case easy:
		howManyAnimalDealWithInOneStage = MAX_ANIMAL_ARRAY_NUM_EASY;
		break;
	case middle:
		howManyAnimalDealWithInOneStage = MAX_ANIMAL_ARRAY_NUM_MIDDLE;
		break;
	case difficul:
		howManyAnimalDealWithInOneStage = MAX_ANIMAL_ARRAY_NUM_DIFFICUL;
		break;
	default:
		break;
	}
	*/

	setId();
	setSceneListener();
	setResourcePath();
	setGameParameter();
	setTitleInfo();

	

}



// setMember()
void LevelBaseScene::setId()
{}

// setMember()
void LevelBaseScene::setResourcePath()
{
	std::string basePath("scenes/levelscene/"); 

	backgroundPath = basePath + "background.png";
	starPath = basePath + "star.png";
	fireflyPath = basePath + "firefly.png";
	cloudPath = basePath + "cloud.png";
	scoreWordPath = basePath + "scoreword.png";
	progFgPath = basePath + "progfg.png";
	progBgPath = basePath + "progbg.png";
	timerPath = basePath + "timer.png";
	normalButtonPath = basePath + "normalbutton.png";
	selectedButtonPath = basePath + "selectedbutton.png";


	wrongAudioPath = basePath + "wrong.mp3";
	greatAudioPath = basePath + "great.mp3";

}

// setMember()
void LevelBaseScene::setGameParameter() {}

// setMember()
void LevelBaseScene::setTitleInfo()
{
	titleBgPath = "";
	titlePath = "";
}

// setMember()
void LevelBaseScene::setTargetWord()
{
	//first get target engilish word
	//targetWord = AnimalInfoTable::getRandomInfos().getInfoByType(AnimalInfos::InfoType::NAME);
	if( readyToTarget.size() <= 0 )
	{
		return;
	}

	int randomNum = rand()%readyToTarget.size();
	
	targetIndex = readyToTarget.at(randomNum);
	std::vector<int>::iterator it = readyToTarget.begin()+randomNum;
	readyToTarget.erase( it );


	for(int i = 0; i < monsterArray->count(); ++i)
	{
		setMonsterBoard((Monster*)monsterArray->getObjectAtIndex(i));
	}
	//log("targetWord == %s", runningAnimalMap[targetIndex]->getName() );
}

// init()
void LevelBaseScene::setScene()
{
	addBackground();
	addTitle();
	//addCloseButton();
	addMonster();
	addReflectTitleBarToManagerArray();
	//addProgress();
	addKeyboardListener();
}

// setScene()
void LevelBaseScene::addBackground()
{
	auto background = Sprite::create(backgroundPath);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, ItemPriority::PRIORITY_BACKGROUND);
}

//只允许有一个middle 出现
TITIE_SPRITE_t LevelBaseScene::titleBarList[]= {
	{TITLE_SPITE_NODE_TAG_PLAY_1_MUSHROOM1,"scenes/levelscene/mushroom.png", NULL, TITLE_SPITE_NODE_TYPE_e::TITLE_SPITE_NODE_TYPE_SPITE, TITLE_SPRITE_POSTION_e::TITLE_SPITE_LEFT},
	{TITLE_SPITE_NODE_TAG_PLAY_1_MUSHROOM2,"scenes/levelscene/mushroom.png", NULL, TITLE_SPITE_NODE_TYPE_e::TITLE_SPITE_NODE_TYPE_SPITE, TITLE_SPRITE_POSTION_e::TITLE_SPITE_LEFT},
	{TITLE_SPITE_NODE_TAG_PLAY_1_MUSHROOM3,"scenes/levelscene/mushroom.png", NULL, TITLE_SPITE_NODE_TYPE_e::TITLE_SPITE_NODE_TYPE_SPITE, TITLE_SPRITE_POSTION_e::TITLE_SPITE_LEFT},
	{TITLE_SPITE_NODE_TAG_PLAY_1_MUSHROOM4,"scenes/levelscene/mushroom.png", NULL, TITLE_SPITE_NODE_TYPE_e::TITLE_SPITE_NODE_TYPE_SPITE, TITLE_SPRITE_POSTION_e::TITLE_SPITE_LEFT},
	{TITLE_SPITE_NODE_TAG_PLAY_1_MUSHROOM5,"scenes/levelscene/mushroom.png", NULL, TITLE_SPITE_NODE_TYPE_e::TITLE_SPITE_NODE_TYPE_SPITE, TITLE_SPRITE_POSTION_e::TITLE_SPITE_LEFT},
	{TITLE_SPITE_NODE_TAG_PLAY_1_SCORE,"", NULL, TITLE_SPITE_NODE_TYPE_e::TITLE_SPITE_NODE_TYPE_LABELTTF, TITLE_SPRITE_POSTION_e::TITLE_SPITE_LEFT},
	{TITLE_SPITE_NODE_TAG_TITLE,"scenes/levelscene/title1.png", NULL, TITLE_SPITE_NODE_TYPE_e::TITLE_SPITE_NODE_TYPE_SPITE, TITLE_SPRITE_POSTION_e::TITLE_SPITE_MIDDLE},
	//{TITLE_SPITE_NODE_TAG_PLAY_2_SCORE,"", NULL, TITLE_SPITE_NODE_TYPE_e::TITLE_SPITE_NODE_TYPE_LABELTTF, TITLE_SPRITE_POSTION_e::TITLE_SPITE_RIGHT},
	//{TITLE_SPITE_NODE_TAG_PLAY_2_MUSHROOM1,"scenes/levelscene/mushroom.png", NULL, TITLE_SPITE_NODE_TYPE_e::TITLE_SPITE_NODE_TYPE_SPITE, TITLE_SPRITE_POSTION_e::TITLE_SPITE_RIGHT},
	//{TITLE_SPITE_NODE_TAG_PLAY_2_MUSHROOM2,"scenes/levelscene/mushroom.png", NULL, TITLE_SPITE_NODE_TYPE_e::TITLE_SPITE_NODE_TYPE_SPITE, TITLE_SPRITE_POSTION_e::TITLE_SPITE_RIGHT},
	//{TITLE_SPITE_NODE_TAG_PLAY_2_MUSHROOM3,"scenes/levelscene/mushroom.png", NULL, TITLE_SPITE_NODE_TYPE_e::TITLE_SPITE_NODE_TYPE_SPITE, TITLE_SPRITE_POSTION_e::TITLE_SPITE_RIGHT},
	//{TITLE_SPITE_NODE_TAG_PLAY_2_MUSHROOM4,"scenes/levelscene/mushroom.png", NULL, TITLE_SPITE_NODE_TYPE_e::TITLE_SPITE_NODE_TYPE_SPITE, TITLE_SPRITE_POSTION_e::TITLE_SPITE_RIGHT},
	//{TITLE_SPITE_NODE_TAG_PLAY_2_MUSHROOM5,"scenes/levelscene/mushroom.png", NULL, TITLE_SPITE_NODE_TYPE_e::TITLE_SPITE_NODE_TYPE_SPITE, TITLE_SPRITE_POSTION_e::TITLE_SPITE_RIGHT},
	{TITLE_SPITE_NODE_TAG_MUTE,"scenes/levelscene/speakerOn.png", NULL, TITLE_SPITE_NODE_TYPE_e::TITLE_SPITE_NODE_TYPE_BUTTON, TITLE_SPRITE_POSTION_e::TITLE_SPITE_RIGHT},
	{TITLE_SPITE_NODE_TAG_EXIT,"scenes/levelscene/exit.png",NULL,TITLE_SPITE_NODE_TYPE_e::TITLE_SPITE_NODE_TYPE_BUTTON,TITLE_SPRITE_POSTION_e::TITLE_SPITE_RIGHT},

};  // all tile sprite list here

// setScene()

Node* LevelBaseScene::findTitleBar( int which )
{
	int len = sizeof( titleBarList ) / sizeof(TITIE_SPRITE_t);
	
	for( int i = 0 ; i < len ; i++ )
	{
		if(titleBarList[i].tag == which)
		{
			return titleBarList[i].node;
		}
	}

	return NULL;

}


void LevelBaseScene::addTitle()
{
	//wangheping add new
	//first create all sprite

	titleBg = Sprite::create(titleBgPath);
	titleBg->setPosition(visibleSize.width/2, visibleSize.height - titleBg->getContentSize().height/2);
	addChild(titleBg, ItemPriority::PRIORITY_TITLE_BACKGROUND);

	
	int len = sizeof( titleBarList ) / sizeof(TITIE_SPRITE_t);
	int expectSize = 0;
	int allSpiteSize = 0;
	for( int i = 0 ; i < len ; i++ )
	{
		if(titleBarList[i].type == TITLE_SPITE_NODE_TYPE_e::TITLE_SPITE_NODE_TYPE_SPITE )
		{
			titleBarList[i].node = Sprite::create(titleBarList[i].spritePath);
			allSpiteSize += titleBarList[i].node->getContentSize().width;
		}
		else if(titleBarList[i].type == TITLE_SPITE_NODE_TYPE_e::TITLE_SPITE_NODE_TYPE_LABELTTF  )
		{
			titleBarList[i].node = LabelTTF::create("0000分", "微软雅黑 Bold", 60);
		}
		else 
		{
			titleBarList[i].node = ui::Button::create( titleBarList[i].spritePath , titleBarList[i].spritePath );
		}
		expectSize += titleBarList[i].node->getContentSize().width;
	}

	if( visibleSize.width <= expectSize )
	{
		//zoom all control expect TTF control
		float room =  (float)(allSpiteSize + visibleSize.width -expectSize) / (float)allSpiteSize ;

		for( int i = 0 ; i < len ; i++ )
		{
			if(titleBarList[i].type == TITLE_SPITE_NODE_TYPE_e::TITLE_SPITE_NODE_TYPE_SPITE )
			{
				Size size = titleBarList[i].node->getContentSize();
				size.width *= room;
				titleBarList[i].node->setContentSize( size );
			}
		}
	}

	//place all titlebar

	int nextLeftBarSouldPlacePos = 0;  // 下一个bar 应该放置的位置的左下角位置
	for( int i = 0 ; i < len ; i++ )
	{
		if(titleBarList[i].layOutPosition == TITLE_SPRITE_POSTION_e::TITLE_SPITE_LEFT )
		{
			titleBarList[i].node->setPosition(( nextLeftBarSouldPlacePos + titleBarList[i].node->getContentSize().width/2 ), titleBg->getPositionY() );
			nextLeftBarSouldPlacePos += titleBarList[i].node->getContentSize().width;
			addChild(titleBarList[i].node, ItemPriority::PRIORITY_TITLE);
		}
	}

	int nextRightBarSouldPlacePos = 0;  // 下一个bar 应该放置的位置的右下角位置
	for( int i = len-1 ; i > 0 ; i-- )
	{
		if(titleBarList[i].layOutPosition == TITLE_SPRITE_POSTION_e::TITLE_SPITE_RIGHT)
		{
			titleBarList[i].node->setPosition(( visibleSize.width - nextRightBarSouldPlacePos - titleBarList[i].node->getContentSize().width/2 ), titleBg->getPositionY() );
			nextRightBarSouldPlacePos += titleBarList[i].node->getContentSize().width;
			addChild(titleBarList[i].node, ItemPriority::PRIORITY_TITLE);
		}
	}

	for( int i = 0 ; i < len ; i++ )
	{
		if(titleBarList[i].layOutPosition == TITLE_SPRITE_POSTION_e::TITLE_SPITE_MIDDLE )
		{
			titleBarList[i].node->setPosition( nextLeftBarSouldPlacePos +( visibleSize.width - nextRightBarSouldPlacePos - nextLeftBarSouldPlacePos)/2 , titleBg->getPositionY() );
			addChild(titleBarList[i].node, ItemPriority::PRIORITY_TITLE);
			break;
		}
	}

}

// setScene()
void LevelBaseScene::addReflectTitleBarToManagerArray()
{
	LabelTTF *label = (LabelTTF*)findTitleBar(TITLE_SPITE_NODE_TAG_PLAY_1_SCORE);

	scoreBoardArray->addObject( label );
	label->setString(itos(Monster::scores[0]) + WStrToUTF8(L"分"));
	
	/*
	label = (LabelTTF*)findTitleBar(TITLE_SPITE_NODE_TAG_PLAY_2_SCORE);

	scoreBoardArray->addObject( label );
	label->setString(itos(Monster::scores[1]) + WStrToUTF8(L"分"));
	*/

	muteSprite = (ui::Button *)findTitleBar(TITLE_SPITE_NODE_TAG_MUTE);
	muteSprite->addTouchEventListener(this, toucheventselector(LevelBaseScene::touchMuteButton));

	((ui::Button *)findTitleBar(TITLE_SPITE_NODE_TAG_EXIT))->addTouchEventListener(this, toucheventselector(LevelBaseScene::touchExitButton));
}
/*
// setScene()
void LevelBaseScene::addProgress()
{
	progNumBoard = LabelTTF::create(itos(targetCount), "Consolas", 60);
	progNumBoard->setPosition(visibleSize.width - progNumBoard->getContentSize().width,
		titleBg->getPositionY());
	addChild(progNumBoard, ItemPriority::PRIORITY_PROGNUMBOARD);

	Sprite *progressBg = Sprite::create(progBgPath);
	progressBg->setPosition(progNumBoard->getPositionX() - progNumBoard->getContentSize().width
		- progressBg->getContentSize().width / 2, titleBg->getPositionY());
	addChild(progressBg, ItemPriority::PRIORITY_BARBACKGROUND);

	Sprite *progressFg = Sprite::create(progFgPath);
	progress = ProgressTimer::create(progressFg);
	progress->setPosition(progressBg->getPosition());
	progress->setType(ProgressTimer::Type::BAR);
	progress->setBarChangeRate(ccp(1,0));
	progress->setMidpoint(ccp(0, 0));
	progress->setTag(ItemPriority::TAG_PROGRESSBAR);
	addChild(progress, ItemPriority::PRIORITY_PROGRESSBAR);
}
*/
// setScene()
void LevelBaseScene::addTimer()
{
	timer = Sprite::create(timerPath);
	auto conSiz = timer->getContentSize();
	timer->setPosition(title->getPositionX() + title->getContentSize().width +  conSiz.width,
		titleBg->getPositionY());
	timer->setScale(1.3f);
	addChild(timer, ItemPriority::PRIORITY_TIMER);

	timerBoard = LabelTTF::create(itos(terminalTime), "Consolas", 32);
	timerBoard->setColor(Color3B::GRAY);
	timerBoard->setPosition(conSiz / 2);
	timer->addChild(timerBoard);
}


// setScene()
void LevelBaseScene::addMonster()
{

	auto monster = Monster::create();
	setMonsterBoard(monster);
	monsterArray->addObject(monster);
	monster->setId(monsterCount);
	monsterCount++;
	monster->setPosition(visibleSize.width/2, monster->getContentSize().height/2);
	addChild(monster, ItemPriority::PRIORITY_MONSTER);
}

// setScene()
void LevelBaseScene::setMonsterBoard(Monster* monster)
{
	if( AnimalInfos::InfoType::EXPLAIN == monsterBordWordType )
	{
		monster->setWord(runningAnimalMap[targetIndex]->getExplaination());
	}
	else if(AnimalInfos::InfoType::NAME == monsterBordWordType)
	{
		monster->setWord(runningAnimalMap[targetIndex]->getName());
	}
	else
	{
		monster->setWord("?");
	}
}

// setScene()
void LevelBaseScene::addKeyboardListener()
{
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(LevelBaseScene::onKeyPressed, this);
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
}

// addKeyboardListener()
void LevelBaseScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if( keyCode == cocos2d::EventKeyboard::KeyCode::KEY_F2)
	{
		if( monsterCount < 2 )
		{ // the most player is 2
			addMonster();
			//addScoreBoard();
		}
	}

	if( keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W ||
		keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S ||
		keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A ||
		keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D ||
		keyCode == cocos2d::EventKeyboard::KeyCode::KEY_J )
	{
		Monster *monster = (Monster*)monsterArray->getObjectAtIndex(0);
		Vec2 newPosition = monster->getPosition();
		switch(keyCode)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			newPosition.y += stepHeight;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			newPosition.y -= stepHeight;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
			monster->leftMove();
			newPosition.x -= stepWidth;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			monster->rightMove();
			newPosition.x += stepWidth;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_J:
			tryCapture(monster);
			break;
		}
		monster->setPosition(positionInScreenAdjust(monster, newPosition));
		return;
	}
	
	if( monsterArray->count() > 1 && (
		keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW ||
		keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW ||
		keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
		keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW ||
		keyCode == cocos2d::EventKeyboard::KeyCode::KEY_0 ))
	{
		Monster *monster = (Monster*)monsterArray->getObjectAtIndex(1);
		Vec2 newPosition = monster->getPosition();
		switch(keyCode)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
			newPosition.y += stepHeight;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			newPosition.y -= stepHeight;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			monster->leftMove();
			newPosition.x -= stepWidth;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			monster->rightMove();
			newPosition.x += stepWidth;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_0:
			tryCapture(monster);
			break;
		}
		monster->setPosition(positionInScreenAdjust(monster, newPosition));
		return;
	}
}

// onKeyPressed()
Vec2 LevelBaseScene::positionInScreenAdjust(Sprite* sprite, Vec2 position)
{
	auto contentSize = sprite->getContentSize();
	Rect boundRect(contentSize.width/2, contentSize.height/2, 
		visibleSize.width - contentSize.width, visibleSize.height - contentSize.height);

	if(position.x < boundRect.getMinX())
		position.x = boundRect.getMinX();
	if(position.x > boundRect.getMaxX())
		position.x = boundRect.getMaxX();
	if(position.y < boundRect.getMinY())
		position.y = boundRect.getMinY();
	if(position.y > boundRect.getMaxY())
		position.y = boundRect.getMaxY();

	return position;
}

// onKeyPressed()
void LevelBaseScene::tryCapture(Monster* monster)
{
	bool isCaptured = false;
	bool captureRightAnimFlag = false;
	Animal* capturedWrongAnim = NULL;
	Animal* anim = NULL;
	Vec2 animPos;


	for(int i = 0; i < animalArray->count(); ++i)
	{
		anim = (Animal*)(animalArray->objectAtIndex(i));
		animPos = anim->getPosition();
		isCaptured = monster->capture(anim);
		if(isCaptured == true)
		{
			if( anim->getExtraPropert() != ANIMAL_SPRITE_EXTRA_PROPERT_e::ANIMAL_SPRITE_EXTRA_PROPERT_NULL )
			{//at last stage
				captureWhatever(monster, anim);
			}
			else
			{
				if(anim == runningAnimalMap[targetIndex])  
				{ // yes, this is the target
					captureCorrect(monster, anim);
					animalArray->removeObject(anim);
					anim->removeFromParent();
					anim->setAlive(false);
					captureRightAnimFlag = true;
					break;
				}
				else
				{
					capturedWrongAnim = anim;

				}
			}

		}
	}

	if( !captureRightAnimFlag && (capturedWrongAnim != NULL ) )
	{
		captureWrong(monster, capturedWrongAnim);
		if( monster->deadALife() )
		{
			for( int i = 0 ; i < monsterArray->count() ; i++ )
			{
				((Monster*)(monsterArray->getObjectAtIndex( i )))->dead();
			}
			scheduleOnce(schedule_selector(LevelBaseScene::sceneOver ), 0.6f); //在之后执行，并且只执行一次。
		

		}
		else
		{	
			updateLifeBar( monster);
			animalArray->removeObject(capturedWrongAnim);
			capturedWrongAnim->removeFromParent();
			capturedWrongAnim->setAlive(false);
		}
	}
}

void LevelBaseScene::captureWhatever(Monster *monster, Animal *anim)
{
	gameSpeed = MIN_SPEED_CAT;
	Sprite *extraSprite = NULL;
	switch( anim->getExtraPropert() )
	{
	case ANIMAL_SPRITE_EXTRA_PROPERT_NULL :
		break;
	case ANIMAL_SPRITE_EXTRA_PROPERT_PLUS_1 :
		freshScoreBoard(monster); 
		extraSprite = Sprite::create( Animal::plusOnePath );
		Monster::scores[0] += 1; // add score
		
		break;
	case ANIMAL_SPRITE_EXTRA_PROPERT_PLUS_2 :
		extraSprite = Sprite::create( Animal::plusTwoPath );
		Monster::scores[0] += 2; // add score
		freshScoreBoard(monster); 
		break;
	case ANIMAL_SPRITE_EXTRA_PROPERT_PLUS_3 :
		extraSprite = Sprite::create( Animal::plusThreePath );
		Monster::scores[0] += 3; // add score
		freshScoreBoard(monster); 
		break;
	case ANIMAL_SPRITE_EXTRA_PROPERT_BOMB :
		extraSprite = Sprite::create( Animal::plusBombPath );
		if( monster->deadALife() )
		{
			sceneListener->SceneFail(id);
		}
		else
		{
			updateLifeBar( monster);
		}
		break;
	case ANIMAL_SPRITE_EXTRA_PROPERT_LIFE :
		extraSprite = Sprite::create( Animal::plusMushroomPath );
		monster->addALife();
		updateLifeBar( monster);
		break;
	default:
		log("getExtraPropert error propert!");
		break;
	}

	auto pos = monster->getPosition();
	auto conSz = monster->getContentSize();

	extraSprite->setPosition(pos.x + conSz.width / 3, pos.y + conSz.height / 3);
	addChild(extraSprite, ItemPriority::PRIORITY_PLUSSCORE);
	extraSprite->runAction(Sequence::create(
		Spawn::create(ScaleTo::create(1.0f, 2.0f), FadeOut::create(1.0f), NULL), RemoveSelf::create(), NULL));


	animalMoveFinished(anim);
}

// tryCapture()
void LevelBaseScene::captureCorrect(Monster *monster, Animal *anim)
{
	finishedCount++;		//ok to catch
	anim->speak(  );
	targetExisted = false;
	Monster::scores[0] += increasedScore; // add score
	freshScoreBoard(monster); 
	setTargetWord();

	//progress->setPercentage(progress->getPercentage() + 100.0f / targetCount);

	auto pos = monster->getPosition();
	auto conSz = monster->getContentSize();
	comboCount++;
	FiniteTimeAction *speakGreat = CallFuncN::create(this, callfuncN_selector(LevelBaseScene::speakGreate)); 
	Sprite* plusScore = NULL;
		
	if(comboCount >= 5)
	{
		if( !mute )
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(greatAudioPath.c_str());
		}
		plusScore = Sprite::create(Animal::plusThreePath);
		monster->scores[0] += 3;
		if((randomNum & 0x0000000f) < 11 )
		{ // 有一定几率播放音乐
			speakGreat = NULL;
		}
	}
	else if(comboCount >= 3)
	{
		plusScore = Sprite::create(Animal::plusTwoPath);
		monster->scores[0] += 2;
		speakGreat = NULL;
		
	}
	else
	{
		plusScore = Sprite::create(Animal::plusOnePath);
		speakGreat = NULL;
	}
	plusScore->setPosition(pos.x + conSz.width / 3, pos.y + conSz.height / 3);
	addChild(plusScore, ItemPriority::PRIORITY_PLUSSCORE);


	plusScore->runAction(Sequence::create(
		Spawn::create(ScaleTo::create(1.0f, 2.0f), FadeOut::create(1.0f), NULL), RemoveSelf::create(), NULL));
		
	
	LabelTTF *word = LabelTTF::create(anim->getName(), "微软雅黑", 80);

	word->setPosition( pos.x , pos.y + conSz.height/2 );

	addChild(word, ItemPriority::PRIORITY_PLUSSCORE);
	
	word->runAction(Sequence::create(
		Spawn::create(ScaleTo::create(1.0f, 2.0f), FadeOut::create(1.0f), NULL), RemoveSelf::create(), NULL));
	
	if( comboCount %3 == 0 )
	{
		if( gameSpeed > MIN_SPEED_CAT )
		{
			gameSpeed --;
		}
	}
	
	//FiniteTimeAction *speak = CallFuncN::create(this, callfuncN_selector(Animal::speak));  
	monster->happy();
	
	runAction(Sequence::create(  DelayTime::create(1.5f) , speakGreat ,NULL) );
	/*
	Sprite *firefly = Sprite::create(fireflyPath);
	firefly->setPosition(anim->getPosition());
	addChild(firefly, ItemPriority::PRIORITY_FIREFLY);

	firefly->runAction(Sequence::create(ScaleTo::create(0.5f, 2), 
		DelayTime::create(0.5f), RemoveSelf::create(), NULL));
*/
	/*
	Animal *realAnim = Animal::createWithName(anim->getName());
	realAnim->setPosition(anim->getPosition());
	addChild(realAnim, ItemPriority::PRIORITY_SHOWANIMAL);
	
	anim->runAction(Seque nce::create(ScaleTo::create(1.0f, 2), 
		RemoveSelf::create(), animalMoveFinished(anim) ));
	*/
	animalMoveFinished(anim);
}

void LevelBaseScene::speakGreate( Node * node )
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(greatAudioPath.c_str());
}
// tryCapture()
void LevelBaseScene::captureWrong(Monster *monster, Animal *anim)
{
	comboCount = 0;
	if( !mute )
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(wrongAudioPath.c_str());
	}
	if( gameSpeed < MAX_SPEED_CAT )
	{
		gameSpeed ++;
	}
	/*
	Monster::scores[monster->id] -= decreasedScore;
	if(Monster::scores[monster->id] < 0)
	{
		Monster::scores[monster->id] = 0;
		freshScoreBoard(monster);
		sceneListener->SceneFail(id);
	}
	freshScoreBoard(monster);
	*/
	monster->angry();
		/*
	Sprite *cloud = Sprite::create(cloudPath);
	cloud->setPosition(anim->getPosition());
	addChild(cloud, ItemPriority::PRIORITY_CLOUD);

	FiniteTimeAction *action = Spawn::create(ScaleTo::create(1.0f, 2.0f), 
		RotateBy::create(1.0f, 360), NULL);
	cloud->runAction(Sequence::create(action,
		RemoveSelf::create(), NULL));
		*/
}

// tryCapture()
void LevelBaseScene::freshScoreBoard(Monster* monster)
{
	//int index = monsterArray->getIndexOfObject(monster);
	auto scoreBoard = (LabelTTF *)scoreBoardArray->getObjectAtIndex(0);
	scoreBoard->setString(itos(Monster::scores[0]) + WStrToUTF8(L"分"));
}


void LevelBaseScene::buildRunningAnimalMap()
{
	
	if( howManyAnimalDealWithInOneStage < ( AnimalInfoTable::infoTableNum - usedInfoTableIndex ) )
	{
		runningAnimalNum = howManyAnimalDealWithInOneStage;
	}
	else
	{
		runningAnimalNum =  AnimalInfoTable::infoTableNum - usedInfoTableIndex;
	}

	stageAllAnimalNum = runningAnimalNum;  // record how many element number for target select

	for( int i = 0 ; i < runningAnimalNum ; i ++ )
	{
		runningAnimalMap[i] = Animal::createWithInfos(&AnimalInfoTable::infoTable[usedInfoTableIndex+i]);
			
	}

	usedInfoTableIndex += runningAnimalNum;

}

void LevelBaseScene::buildreadyToTargetVect()
{
	
	readyToTarget.clear();

	for( int i = 0 ; i < runningAnimalNum ; i ++ )
	{
		readyToTarget.push_back(i);
	}

}

void LevelBaseScene::setStageAnimalShowType( int type )
{
	for( int i = 0 ; i < runningAnimalNum ; i++ )
	{
		runningAnimalMap[i]->setShowType( type );
	}
}

Animal* LevelBaseScene::pickUpWithIndex( int index )
{
	if( index < runningAnimalNum  )
	{
		if( runningAnimalMap[index]->isAlve() )
		{
			return NULL;
		}
		else
		{
			runningAnimalMap[index]->setAlive(true);
			return runningAnimalMap[index];
		}
	}
	else
	{
		return NULL;
	}

}

// 请求下一轮操作
bool LevelBaseScene::NextTurnReq()
{
	if(usedInfoTableIndex < AnimalInfoTable::infoTableNum )
	{//still have some element for netxt turn
		return true;
	}
	else
	{
		return false;
	}
}
extern void callJavaStartToPay( int handleSharkCode );
void LevelBaseScene::stageInit()
{
/*
	if( progress != NULL )
	{
			progress->setPercentage( 0.0 ); // reset stage progress percent 
	}
*/
	finishedCount = 0;
	switch( stageStep )
	{
	case GAME_LOGIC_STEP1:
		relaseAllRunningAnimalMap();
		buildRunningAnimalMap();
		setStageAnimalShowType(ANIMAL_SPRITE_SHOW_TYPE_e::ANIMAL_SPRITE_SHOW_PICTURE);
		monsterBordWordType = AnimalInfos::InfoType::EXPLAIN;
		break;
	case GAME_LOGIC_STEP2:
		monsterBordWordType = AnimalInfos::InfoType::NAME;
		if( validCheck() )
		{
			//do nothing . continue game
		}
		else
		{
			pauseGame();
			payHandleShark = rand();
			callJavaStartToPay( payHandleShark );
			
		}


		break;
	case GAME_LOGIC_STEP3:
		monsterBordWordType = AnimalInfos::InfoType::EXPLAIN;
		setStageAnimalShowType(ANIMAL_SPRITE_SHOW_TYPE_e::ANIMAL_SPRITE_SHOW_WORD);
		break;
	case GAME_LOGIC_STEP_LAST:
		gameSpeed = MIN_SPEED_CAT;
		stageLastEndFlag = false;
		monsterBordWordType = AnimalInfos::InfoType::NONE;
		setStageAnimalShowType(ANIMAL_SPRITE_SHOW_TYPE_e::ANIMAL_SPRITE_SHOW_PICTURE_EXTRA);
		scheduleOnce(schedule_selector(LevelBaseScene::lastStageCatchOver), 60.0f); //在1.0f之后执行，并且只执行一次。
		break;
	default:
		monsterBordWordType = AnimalInfos::InfoType::EXPLAIN;
		break;
	}
	buildreadyToTargetVect();
	setTargetWord();

}

// init()
void LevelBaseScene::gameLogic()
{
	scheduleUpdate();
	schedule(schedule_selector(LevelBaseScene::addAnimal), addAnimalInterval);  
}

// gameLogic()
void LevelBaseScene::update(float delta)
{

	if( stageOverCheck() )
	{
		if( stageStep >= GAME_LOGIC_STEP_END )
		{
			if( NextTurnReq() )
			{
				stageStep = GAME_LOGIC_STEP1 ; // enter next turn's step 1
				stageInit(); // 重新初始化
			}
			else
			{
				//the mission over
				sceneListener->SceneSuccess(id, Monster::scores[0]); // notify scene Listener
			}
			
		}
		else
		{
			stageStep ++; // 进入下一个阶段
			/* jump the last stage while no next turn required */
			if( stageStep == GAME_LOGIC_STEP_LAST )
			{
				if( !NextTurnReq() )
				{
					//the mission over
					sceneListener->SceneSuccess(id, Monster::scores[0]); // notify scene Listener
				}
			}
			
			stageInit(); // 重新初始化
		}
	}

	/*
	if(successCondition())
	{
		sceneListener->SceneSuccess(id, Monster::scores[0]); // 未考虑多人情况，因为不知道显示多个怪物中的哪一个的分数
	}
	*/else if(failCondition())
	{
			sceneListener->SceneFail(id);
	}
	switch (stageStep)
	{
	case GAME_LOGIC_STEP1:
		break;
	case GAME_LOGIC_STEP2:
		break;
	case GAME_LOGIC_STEP3:
		break;
	default:
		break;
	}

}

// gameLogic()
void LevelBaseScene::updateTimer(float delta)
{
	static bool alarmFlag = false;
	int leftTime = terminalTime - ++timerCount;
	if(leftTime <= 10 && !alarmFlag)
	{
		timerBoard->setColor(Color3B::RED);
		Action* leap = RepeatForever::create(
			Sequence::create(ScaleTo::create(0.2f, 0.8f), ScaleTo::create(0.2f, 1.25f),
			ScaleTo::create(0.2f, 1.25f), ScaleTo::create(0.2f, 0.8f), NULL));
		timerBoard->runAction(leap);
	}
	timerBoard->setString(itos(leftTime));
}



// update()
bool LevelBaseScene::stageOverCheck()
{
	if( stageStep < GAME_LOGIC_STEP_LAST )
	{
	#ifdef __MYDEBUG
		if(finishedCount >= stageAllAnimalNum/10 )
	#else
		if(finishedCount >= stageAllAnimalNum )
	#endif
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return stageLastEndFlag; 
	}
}

// update()
bool LevelBaseScene::failCondition()
{
	return false;
}

// gameLogic()
void LevelBaseScene::lastStageOver(Node *sender)
{
	stageLastEndFlag = true;
}

void LevelBaseScene::sceneOver(  float delta )
{
	sceneListener->SceneFail(id);
}


void LevelBaseScene::lastStageCatchOver( float delta)
{
	gameSpeed = INFINITE_GAME_SPEED;		//speed = 0 , stop

	FiniteTimeAction *lastStageOver = CallFuncN::create(this, callfuncN_selector(LevelBaseScene::lastStageOver));  

	LabelTTF *ttf = LabelTTF::create(WStrToUTF8(L"下一波食物即将到达"), "微软雅黑", 144);
	ttf->setPosition(visibleSize.width/2, visibleSize.height / 2);
	addChild(ttf);
	FadeIn* fadeIn =FadeIn::create(5.0);
	FadeOut* fadeOut = FadeOut::create(5.0);


	Vector<FiniteTimeAction*> arrayOfActions  ;
	arrayOfActions.pushBack(fadeIn);
	arrayOfActions.pushBack(fadeOut);
	arrayOfActions.pushBack(RemoveSelf::create());
	arrayOfActions.pushBack(lastStageOver);
	
	
	ttf->runAction(Sequence::create( arrayOfActions ));

}

//plus1 : plus2 : plus3 : bomb : mushroom  = 5:4:3:2:1
unsigned char jumpN = 0;
int LevelBaseScene::stageLastAnimalPropertSelect( )
{
	int ran = (rand() & 0x0f);
	
	/*
	if( ran > 10 )
	{
		return ANIMAL_SPRITE_EXTRA_PROPERT_e::ANIMAL_SPRITE_EXTRA_PROPERT_PLUS_1;
	}
	else if( ran > 6 )
	{
		return ANIMAL_SPRITE_EXTRA_PROPERT_e::ANIMAL_SPRITE_EXTRA_PROPERT_PLUS_2;
	}
	else if( ran > 3 )
	{
		return ANIMAL_SPRITE_EXTRA_PROPERT_e::ANIMAL_SPRITE_EXTRA_PROPERT_PLUS_3;
	}
	*/
	if( ran > 3 )
	{
		return ANIMAL_SPRITE_EXTRA_PROPERT_e::ANIMAL_SPRITE_EXTRA_PROPERT_NULL;
	}
	else if( ran > 1 )
	{
		return ANIMAL_SPRITE_EXTRA_PROPERT_e::ANIMAL_SPRITE_EXTRA_PROPERT_BOMB;
	}
	else
	{
		if( (jumpN++)<<6 == 0 ) // 4 次选一次，跳过连续的random后重复的问题
		{
			return ANIMAL_SPRITE_EXTRA_PROPERT_e::ANIMAL_SPRITE_EXTRA_PROPERT_LIFE;
		}
		else
		{
			return ANIMAL_SPRITE_EXTRA_PROPERT_e::ANIMAL_SPRITE_EXTRA_PROPERT_NULL;
		}
	}


}

// gameLogic()
void LevelBaseScene::addAnimal(float delta)
{
	speedControlCount++;
	if( speedControlCount >= gameSpeed )
	{
		speedControlCount = 0;
	}
	else
	{
		return;
	}
	Animal *anim = createAnimal();

	if( anim == NULL )
	{
		return ;
	}
	if( GAME_LOGIC_STEP_LAST == stageStep )
	{
		anim->setExtraPropert( stageLastAnimalPropertSelect() );
	}
	else
	{
		anim->setExtraPropert( ANIMAL_SPRITE_EXTRA_PROPERT_e::ANIMAL_SPRITE_EXTRA_PROPERT_NULL );
	}

	animalArray->addObject(anim);

	anim->setScale(1.5f);
	float animWidth = anim->getContentSize().width;
	anim->setPosition(rand()%int(visibleSize.width-animWidth)+animWidth/2, visibleSize.height);
	this->addChild(anim, ItemPriority::PRIORITY_ANIMAL);

	setAnimalAction(anim);
	return;
}

Animal *LevelBaseScene::RandomCreateAnimal()
{
	randomNum = rand();
	return pickUpWithIndex(randomNum % runningAnimalNum);
}
// addAnimal()
Animal* LevelBaseScene::createAnimal()
{
	Animal *anim = nullptr;
	static int showCount = CONST_NUMBER +  rand()%showTargetInterval;
	
	{
		if(targetExisted == false)
		{
			if(showCount == 0){
				anim = pickUpWithIndex( targetIndex );
				if( anim != NULL )
				{
					targetExisted = true;
					showCount = CONST_NUMBER +  rand()%showTargetInterval;
				}
			}else{
				anim = RandomCreateAnimal();
				showCount--;
	
			}
		}
		else{
			anim = RandomCreateAnimal();
			//while(isAnimalExisted(anim->getName()))
			//	anim = RandomCreateAnimal();
			
			showCount = CONST_NUMBER +  rand()%showTargetInterval;
		}

	}
	return anim;
}

void LevelBaseScene::relaseAllRunningAnimalMap()
{
	readyToTarget.clear();
	for( int i = 0 ; i < runningAnimalNum ; i++ )
	{
		if( runningAnimalMap[i] != NULL )
		{
			runningAnimalMap[i]->autorelease();
		}
	}

	runningAnimalNum = 0;
}
// createAnimal()
bool LevelBaseScene::isAnimalExisted(std::string name)
{
	for(int i = 0; i < animalArray->count(); ++i)
	{
		if(((Animal *)animalArray->objectAtIndex(i))->getName() == name)
			return true;
	}
	return false;
}

// addAnimal()
void LevelBaseScene::setAnimalAction(Animal *anim)
{
	static const int rangeDuration = maxDuration - minDuration;  
	float actualDuration = (rand()%rangeDuration + minDuration)*gameSpeed/MAX_SPEED_CAT; 

	actualDuration = actualDuration < minDuration ? minDuration : actualDuration;
	
	FiniteTimeAction *actionMove = MoveTo::create(actualDuration, 
		Vec2(anim->getPositionX(), 0 - anim->getContentSize().width/2.0));
	FiniteTimeAction *actionMoveDone = CallFuncN::create(this, callfuncN_selector(LevelBaseScene::animalMoveFinished));  
	anim->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}

void LevelBaseScene::animalMoveFinished(Node *sender)
{
	auto anim = (Animal *)sender;
	if(anim == runningAnimalMap[targetIndex])
		targetExisted = false;

	animalArray->removeObject(anim);
	anim->removeFromParent();
	anim->setAlive(false);
	return;
}

void LevelBaseScene::updateLifeBar( Monster *monster )
{
	int life = monster->getLife();

	TITIE_SPRITE_t *beginSprite = NULL;

	beginSprite = &titleBarList[TITLE_SPITE_NODE_TAG_PLAY_1_MUSHROOM1];

	for( int i = 0 ; i < MAX_LIFE_NUMBER ; i++ )
	{
		if( life >0 )
		{
			beginSprite->node->setVisible(true);
			life--;
		}
		else
		{
			beginSprite->node->setVisible(false);
		}
		beginSprite++;
	}
}


void LevelBaseScene::touchExitButton(Object* object, ui::TouchEventType type) 
{
	if( type == ui::TouchEventType::TOUCH_EVENT_ENDED )
	{
		
		//TODO make sure exit?
		if( true )
		{
			sceneListener->SceneFail(id);
		}
	}
}


void LevelBaseScene::touchMuteButton(Object* object, ui::TouchEventType type) 
{
	if( type == ui::TouchEventType::TOUCH_EVENT_ENDED )
	{
		mute = !mute;
		if( mute )
		{
			muteSprite->loadTextures("scenes/levelscene/speakerOff.png","scenes/levelscene/speakerOff.png");
		}
		else
		{
			muteSprite->loadTextures("scenes/levelscene/speakerOn.png","scenes/levelscene/speakerOn.png");
		}
	}
}

bool LevelBaseScene::onTouchBegan(Touch* touch, Event* event)
{
	log("onTouchBegan");
	
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	if(target == closeButton)
	{
		sceneListener->SceneBack(id);
		return true;
	}
	

	Vec2 pos = touch->getLocation();
	Monster *mon = (Monster*)monsterArray->getObjectAtIndex(0);
	mon->setPosition(pos);
	tryCapture(mon);

	return true;
}

 
/*
void LevelBaseScene::menuCallback(cocos2d::Object *pSender){
    //payPopupLayer();
}
 */

void LevelBaseScene::onSocketClientControl(EventCustom* event)
{
	log("LOG: onSocketClientControl");
	DATA_t* pControlData = static_cast<DATA_t*>(event->getUserData());
	auto monster = (Monster*)monsterArray->getObjectAtIndex(pControlData->ID);

	auto frameSize = CCDirector::sharedDirector()->getWinSize();
	if( pControlData->Type == SOCKET_DATA_TYPE_MOUSE_CONTROL )
	{
		int  x = frameSize.width * pControlData->context.mouseControl.step_x / 2000;
		int  y = frameSize.height * (1.0f- pControlData->context.mouseControl.step_y / 2000.0f);
		auto newPosition = Vec2( x , y );
		printf( "newPosition< x , y > =  < %d , %d >\n" ,x ,y );
		positionInScreenAdjust(monster, newPosition);
		monster->setPosition(newPosition);
	}
//	if( pControlData->Type == SOCKET_DATA_TYPE_MOUSE_CONTROL )
//	{
//		int  x = monster->getPositionX() +
//			stepWidth * pControlData->context.mouseControl.step_x;
//		int  y = monster->getPositionY() +
//			stepHeight * ( 0 - pControlData->context.mouseControl.step_y);
//		auto newPosition = Vec2( x , y );
//		printf( "newPosition< x , y > =  < %d , %d >\n" ,x ,y );
//		positionInScreenAdjust(monster, newPosition);
//		monster->setPosition(newPosition);
//	}

	else if( pControlData->Type == SOCKET_DATA_TYPE_CLICK )
	{
		tryCapture(monster);
	}

}

#ifdef _WINDOWS

void callJavaStartToPay( int handleSharkCode )
{

}
#endif
