#include "Animal.h"
#include "LevelBaseScene.h"

static std::string WORDANIMALPICPATH = "animals/pictures/wordanimal.png";
Animal::Animal()
{
	extraSprite = NULL;
	alive = false;
	showType = ANIMAL_SPRITE_SHOW_TYPE_e::ANIMAL_SPRITE_SHOW_NONE;
	extraPropert = ANIMAL_SPRITE_EXTRA_PROPERT_e::ANIMAL_SPRITE_EXTRA_PROPERT_NULL;
	buildConstResoure();
}

bool Animal::fastStageExtraTextureInited = false;
std::string Animal::plusOnePath ="";
std::string Animal::plusTwoPath ="";
std::string Animal::plusThreePath ="";
std::string Animal::plusBombPath ="";
std::string Animal::plusMushroomPath ="";

//index effect by ANIMAL_SPRITE_EXTRA_PROPERT_e
Texture2D* Animal::fastStageExtraTexture[FAST_STAGE_EXTRA_TEXTURE_NUM] = {NULL,NULL,NULL,NULL,NULL,NULL};

void Animal::buildConstResoure()
{
	if( !fastStageExtraTextureInited )
	{
		fastStageExtraTextureInited = true;
		std::string basePath("scenes/levelscene/"); 
		plusOnePath = basePath + "plusone.png";
		plusTwoPath = basePath + "plustwo.png";
		plusThreePath = basePath + "plusthree.png";
		plusBombPath = basePath + "bomb.png";
		plusMushroomPath = basePath + "mushroom.png";
		fastStageExtraTexture[ANIMAL_SPRITE_EXTRA_PROPERT_NULL] = NULL;
		fastStageExtraTexture[ANIMAL_SPRITE_EXTRA_PROPERT_PLUS_1] =  Director::getInstance()->getTextureCache()->addImage(plusOnePath);
		fastStageExtraTexture[ANIMAL_SPRITE_EXTRA_PROPERT_PLUS_2] =  Director::getInstance()->getTextureCache()->addImage(plusTwoPath);
		fastStageExtraTexture[ANIMAL_SPRITE_EXTRA_PROPERT_PLUS_3] =  Director::getInstance()->getTextureCache()->addImage(plusThreePath);
		fastStageExtraTexture[ANIMAL_SPRITE_EXTRA_PROPERT_BOMB]   =  Director::getInstance()->getTextureCache()->addImage(plusBombPath);
		fastStageExtraTexture[ANIMAL_SPRITE_EXTRA_PROPERT_LIFE]   =  Director::getInstance()->getTextureCache()->addImage(plusMushroomPath);
		/*
		for( int i = 0 ; i < FAST_STAGE_EXTRA_TEXTURE_NUM ; i++ )
		{
			fastStageExtraTexture[i]->retain();
		}
		*/
	}
}

int Animal::getShowType()
{
	return showType;
}

void Animal::setShowType( int type )
{
	if ( showType != type )
	{
		//remove Old Texture
		if( showType != ANIMAL_SPRITE_SHOW_TYPE_e::ANIMAL_SPRITE_SHOW_NONE )
		{
			CCTextureCache::sharedTextureCache()->removeTexture(getTexture());
		}
		if( ANIMAL_SPRITE_SHOW_TYPE_e::ANIMAL_SPRITE_SHOW_PICTURE == type )
		{
			Sprite::initWithFile(picFile);
			this->wordBoard->setVisible(false);
		}
		else if( ANIMAL_SPRITE_SHOW_TYPE_e::ANIMAL_SPRITE_SHOW_WORD == type )
		{
			Sprite::initWithFile(WORDANIMALPICPATH);
			this->wordBoard->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
			this->wordBoard->setVisible(true);
		}
		else if( ANIMAL_SPRITE_SHOW_TYPE_e::ANIMAL_SPRITE_SHOW_PICTURE_EXTRA == type )
		{
			Sprite::initWithFile(picFile);
			this->wordBoard->setVisible(false);
			//
		}
	}
	showType = type;
}

Animal* Animal::createWithInfos( AnimalInfos *infos)
{
	
	Animal *animal = createWithArgs(
		infos->getInfoByType(AnimalInfos::InfoType::NAME),
		infos->getInfoByType(AnimalInfos::InfoType::PICTURE),
		infos->getInfoByType(AnimalInfos::InfoType::SOUND),
		infos->getInfoByType(AnimalInfos::InfoType::EXPLAIN)
		);
	

	return animal ;
}


Animal* Animal::createWithName(const std::string name)
{
	return createWithInfos(AnimalInfoTable::getInfosByTypeInfo(AnimalInfos::InfoType::NAME, name));
}


Animal* Animal::createWithArgs(const std::string name, const std::string picFile, const std::string soundFile , std::string explaination)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto a = new Animal();
	if(a && a->initWithArgs(name, picFile, soundFile,explaination))
	{
		//a->setPosition(visibleSize.width/2, visibleSize.height/2);
		//a->autorelease();
		//a->extraSprite = Sprite::create();
		
        //a->extraSprite->setTexture(fastStageExtraTexture[1]);
		//a->setPosition(0,0);
		//a->addChild(a->extraSprite,ItemPriority::PRIORITY_EXTRA_SPRITE);  
		//a->extraSprite->setVisible( false );
		//
		return a;
	}
	else
	{
		log("Create Animal Failed!");
		return nullptr;
	}
}

bool Animal::initWithArgs(const std::string name, const std::string picFile, const std::string soundFile ,const std::string explaination )
{

	//Sprite::initWithFile(picFile);
	this->name = name;
	this->picFile = picFile;
	this->soundFile = soundFile;
	this->explaination = explaination;

	wordBoard = LabelTTF::create();
	wordBoard->setString(name);
	wordBoard->setFontSize(42);
	//wordBoard->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
	wordBoard->setVisible( false );
	addChild(wordBoard, ItemPriority::PRIORITY_ANIMAL_WORDBOARD);

	
	
	return true;
}
Ref* Animal::autorelease()
{
	
	return Sprite::autorelease();
}

std::string Animal::getName()
{
	return name;
}

std::string Animal::getExplaination()
{
	return explaination;
}

std::string Animal::getPicFile()
{
	return picFile;
}

std::string Animal::getSoundFile()
{
	return soundFile;
}

bool Animal::isAlve() 
{
	return alive;
}
void Animal::setAlive(  bool alive )
{
	this->alive = alive;
}


void Animal::speak( )
{
	if( !LevelBaseScene::mute )
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()
			->playEffect(soundFile.c_str());
		
	}
	else
	{
		return ;
	}
}

void Animal::setWord(std::string word)
{
	wordBoard->setString(word);
}

int Animal::getExtraPropert()
{
	return extraPropert;
}

void Animal::setExtraPropert( int propert )
{
	if( extraSprite == NULL )
	{
		if( propert != ANIMAL_SPRITE_EXTRA_PROPERT_e::ANIMAL_SPRITE_EXTRA_PROPERT_NULL )
		{
			//extraSprite = Sprite::create();
			//Texture2D* text = fastStageExtraTexture[propert];
			//extraSprite->setTexture(text);
			extraSprite = Sprite::createWithTexture( fastStageExtraTexture[propert] );
			addChild(extraSprite,ItemPriority::PRIORITY_EXTRA_SPRITE); 
			extraSprite->setPosition( getContentSize().width/2, getContentSize().height/2);
			extraSprite->setVisible( true );
			//extraSprite->autorelease();
		}
		else
		{
			//extraSprite->setVisible( false );
		}
	}
	extraPropert = propert;

	
}
