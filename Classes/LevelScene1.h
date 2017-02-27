#ifndef _GAME_LEVEL_SCENE_1_H_
#define _GAME_LEVEL_SCENE_1_H_
#include "LevelBaseScene.h"
#include "GameController.h"

class LevelScene1 : public LevelBaseScene
{
private:

	virtual void setId() override;
	virtual void setSceneListener() override;
	virtual void setGameParameter() override;
	virtual void setTitleInfo() override;

	//void setMonsterBoard(Monster*);

public:
	static Scene *createScene();
	CREATE_FUNC(LevelScene1);

};
#endif //_GAME_LEVEL_SCENE_1_H_