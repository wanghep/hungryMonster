#ifndef _GAME_BASE_LEVELSCENE_H_
#define _GAME_BASE_LEVELSCENE_H_

#include <string>

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BaseScene.h"
#include "SceneListener.h"
#include "ItemPriority.h"
#include "Animal.h"
#include "Monster.h"
#include "Auxiliary.h"

USING_NS_CC;
using namespace ui;

typedef enum{
	GAME_LOGIC_STEP1 = 1 ,
	GAME_LOGIC_STEP2 ,
	GAME_LOGIC_STEP3 ,
	GAME_LOGIC_STEP_LAST,
	GAME_LOGIC_STEP_END ,
} e_GAME_LOGIC_STEP;

typedef enum{
	TITLE_SPITE_LEFT,
	TITLE_SPITE_MIDDLE,
	TITLE_SPITE_RIGHT,
} TITLE_SPRITE_POSTION_e;

typedef enum{
	TITLE_SPITE_NODE_TYPE_SPITE,
	TITLE_SPITE_NODE_TYPE_LABELTTF,
	TITLE_SPITE_NODE_TYPE_BUTTON,
} TITLE_SPITE_NODE_TYPE_e;

typedef enum{
	TITLE_SPITE_NODE_TAG_PLAY_1_MUSHROOM1,
	TITLE_SPITE_NODE_TAG_PLAY_1_MUSHROOM2,
	TITLE_SPITE_NODE_TAG_PLAY_1_MUSHROOM3,
	TITLE_SPITE_NODE_TAG_PLAY_1_MUSHROOM4,
	TITLE_SPITE_NODE_TAG_PLAY_1_MUSHROOM5,
	TITLE_SPITE_NODE_TAG_PLAY_1_SCORE,
	TITLE_SPITE_NODE_TAG_TITLE,
	//TITLE_SPITE_NODE_TAG_PLAY_2_SCORE,
	//TITLE_SPITE_NODE_TAG_PLAY_2_MUSHROOM1,
	//TITLE_SPITE_NODE_TAG_PLAY_2_MUSHROOM2,
	//TITLE_SPITE_NODE_TAG_PLAY_2_MUSHROOM3,
	//TITLE_SPITE_NODE_TAG_PLAY_2_MUSHROOM4,
	//TITLE_SPITE_NODE_TAG_PLAY_2_MUSHROOM5,
	TITLE_SPITE_NODE_TAG_MUTE,
	TITLE_SPITE_NODE_TAG_EXIT,

} TITLE_SPITE_NODE_TAG_e;

typedef struct{
	TITLE_SPITE_NODE_TAG_e  tag;
	string					spritePath;
	Node					*node;
	TITLE_SPITE_NODE_TYPE_e  type;
	TITLE_SPRITE_POSTION_e	layOutPosition;

}TITIE_SPRITE_t;

#define CONST_NUMBER				0
#define INFINITE_GAME_SPEED			0X7FFFFFFF
class LevelBaseScene : public BaseScene
{
public:
		LevelBaseScene();
		~LevelBaseScene();
private:
	static TITIE_SPRITE_t titleBarList[];  // all tile sprite list here
protected:

	// init()
	virtual void setMember();
	virtual void setScene();
	virtual void gameLogic();

	// setMember()
	virtual void setId() = 0;
	virtual void setSceneListener() = 0;
	virtual void setGameParameter() = 0;
	virtual void setResourcePath();
	virtual void setTitleInfo() = 0;
	virtual void setTargetWord();
	Node* findTitleBar( int which );
	void speakGreate( Node * node );
	// setScene()
	void stageInit();
	//void addProgress();
	void addTimer();
	void addMonster();
	void setMonsterBoard(Monster*);
	void setStageAnimalShowType( int type );
	void updateLifeBar( Monster *monster );

	// gameLogic()
	virtual void update(float) override;
	virtual void addAnimal(float);
	void updateTimer(float);

	// update()
	virtual bool stageOverCheck();
	virtual bool failCondition();

	// addAnimal()
	virtual Animal* createAnimal();
	void setAnimalAction(Animal*);
	void freshScoreBoard(Monster*);
	int stageLastAnimalPropertSelect( );
	bool stageLastEndFlag;
	//Some member
#define MAX_ANIMAL_ARRAY_NUM_EASY		20
#define MAX_ANIMAL_ARRAY_NUM_MIDDLE		35
#define MAX_ANIMAL_ARRAY_NUM_DIFFICUL	50
#define MAX_SPEED_CAT			5 //SLOW
#define MIN_SPEED_CAT			1 //FAST
	int howManyAnimalDealWithInOneStage;

	int speedControlCount; //control the game speed by this variable 
	int runningAnimalNum ; // how many animals has been created
	int stageAllAnimalNum;
	int usedInfoTableIndex; // which index's element will be use at next scence  
	map<int ,Animal*> runningAnimalMap; //<0,animal*>,<1,animal*>,<2,animal*>,<3,animal*>,<4,animal*>...

	vector<int/* animal index */> readyToTarget;
#define FULL_BLOOM_VOLUM		100
	int monsterBordWordType; //AnimalInfos::InfoType::NAME or EXPLAIN
	int bloom ;// default = 100 
	int stageStep ; //
	int id;
	Size visibleSize;
	float stepWidth;
	float stepHeight;
	SceneListener *sceneListener;
	//std::string targetWord;
	int targetIndex;  // which index's animal will be hunt
	Array *animalArray;
	Array *monsterArray;
	int timerCount;
	int captureCount;
	int comboCount;
	int monsterCount;
	bool targetExisted; // target animal exist flag

	std::string titlePath;
	std::string titleBgPath;
	 
	// Game Parameter:

	int targetCount;
	int finishedCount;
	int increasedScore;
	int decreasedScore;
	float addAnimalInterval;
	int showTargetInterval;
	int maxAnimalNum;
	float minDuration;  
	float maxDuration; 
	int terminalTime;

	// Scene
	Sprite *background;
	Sprite *title;
	Sprite *titleBg;
	Sprite *star;
	//Sprite *mute;
	Array *scoreBoardArray;
	Sprite *closeButton;
	ui::Button *muteSprite;
	Sprite *timer;
	LabelTTF *timerBoard;
	ProgressTimer *progress;
	LabelTTF *progNumBoard;

	// setScene();
	bool NextTurnReq();
	
	void buildRunningAnimalMap();
	void buildreadyToTargetVect();
	Animal *RandomCreateAnimal();
	void relaseAllRunningAnimalMap();
	Animal* pickUpWithIndex( int index );
	void addBackground();
	void addTitle();
	void addReflectTitleBarToManagerArray();
	void addCloseButton();
	void addKeyboardListener();
	void lastStageCatchOver(float delta);
	void lastStageOver(Node *sender);
	void sceneOver(  float delta );
	// Capture()
	virtual void tryCapture(Monster*);
	void captureWhatever(Monster *monster, Animal *anim);
	virtual void captureCorrect(Monster*, Animal*);
	virtual void captureWrong(Monster*, Animal*);

	// Other
	void onKeyPressed(EventKeyboard::KeyCode, Event*);
	Vec2 positionInScreenAdjust(Sprite*, Vec2);
	bool isAnimalExisted(std::string);
	bool onTouchBegan(Touch*, Event*);
	void onSocketClientControl(EventCustom*);
	void animalMoveFinished(Node*);
	void touchMuteButton(Object* object, TouchEventType type);
	void touchExitButton(Object* object, TouchEventType type);
	// ResourcePath
	std::string backgroundPath;
	std::string starPath;
	std::string fireflyPath;
	std::string cloudPath;
	std::string scoreWordPath;
	std::string progBgPath;
	std::string progFgPath;
	std::string timerPath;
	std::string normalButtonPath;
	std::string selectedButtonPath;
	
	std::string wrongAudioPath;
	std::string greatAudioPath;
	
public:
	static int gameSpeed;  //1/2/3/4/5/INFINITE_GAME_SPEED
	static bool mute;
	virtual bool init();
	static void pauseGame();
	static void resumeGame();
	
};

#endif// _GAME_BASE_LEVELSCENE_H_
