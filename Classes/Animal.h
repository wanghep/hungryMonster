#ifndef _GAME_ANIMAL_H_
#define _GAME_ANIMAL_H_

#include <iostream>
#include <vector>
#include <tuple>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ItemPriority.h"
#include "AnimalInfos.h"


USING_NS_CC;

typedef enum
{
	ANIMAL_SPRITE_SHOW_NONE		= 0,
	ANIMAL_SPRITE_SHOW_PICTURE	= 1,
	ANIMAL_SPRITE_SHOW_WORD	= 2,
	ANIMAL_SPRITE_SHOW_PICTURE_EXTRA	= 3,
}ANIMAL_SPRITE_SHOW_TYPE_e;

typedef enum
{
	ANIMAL_SPRITE_EXTRA_PROPERT_NULL = 0,
	ANIMAL_SPRITE_EXTRA_PROPERT_PLUS_1 ,
	ANIMAL_SPRITE_EXTRA_PROPERT_PLUS_2,
	ANIMAL_SPRITE_EXTRA_PROPERT_PLUS_3,
	ANIMAL_SPRITE_EXTRA_PROPERT_BOMB,
	ANIMAL_SPRITE_EXTRA_PROPERT_LIFE,
	
	
}ANIMAL_SPRITE_EXTRA_PROPERT_e;

class Animal : public Sprite
{
public:
	LabelTTF *wordBoard;
public :
	Animal();
protected:


	int extraPropert; // ANIMAL_SPRITE_EXTRA_PROPERT_e 
	std::string name;
	std::string picFile;
	std::string soundFile;
	std::string explaination;
	int showType;  // ANIMAL_SPRITE_SHOW_TYPE_e
	#define FAST_STAGE_EXTRA_TEXTURE_NUM		ANIMAL_SPRITE_EXTRA_PROPERT_LIFE+1
	static bool fastStageExtraTextureInited ;
	static Texture2D* fastStageExtraTexture[FAST_STAGE_EXTRA_TEXTURE_NUM];	// for fast stage extra texture , it's belong const resource
	
	void buildConstResoure();
	virtual bool initWithArgs(const std::string name, const std::string picFile, const std::string soundFile , const std::string explaination );


public:
	static std::string plusOnePath;
	static std::string plusTwoPath;
	static std::string plusThreePath;
	static std::string plusBombPath;
	static std::string plusMushroomPath;
	void setExtraPropert(int propert);
	int getExtraPropert();
	static Animal* createWithInfos( AnimalInfos *infos);
	static Animal* createWithArgs(const std::string name, const std::string picFile, const std::string soundFile , std::string explaination );
	static Animal* createWithName(const std::string name);

	std::string getName();
	std::string getExplaination();
	std::string getPicFile();
	std::string getSoundFile();
	void speak( );
	bool alive;
	Sprite *extraSprite;  // +1,+2,+3,bomb,mushroom
	void setAlive( bool alive );
	bool isAlve();
	void setWord(std::string word);
	int getShowType();
	void setShowType( int type );
	Ref* autorelease();

};

#endif //_GAME_ANIMAL_H_