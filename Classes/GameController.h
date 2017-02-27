#ifndef _GAME_GAMECONTROLLER_H_
#define _GAME_GAMECONTROLLER_H_

#include <iostream>
#include "cocos2d.h"
#include "SceneListener.h"
#include "StartScene.h"
#include "LevelBaseScene.h"
#include "LevelScene1.h"
#include "SuccessScene.h"
#include "FailScene.h"

USING_NS_CC;

class GameController : public SceneListener
{

private:
	static GameController *_controller;
	GameController();
	~GameController();

public:
	static GameController *getInstance();
	static int difcultStage ;
	void startGame();

	virtual void SceneBack(int id) override;
	virtual void SceneSuccess(int id, int score) override;
	virtual void SceneFail(int id) override;
	virtual void SceneNext(int id) override;
	virtual void SceneReplay(int id) override;

	void enterMenu();
	void enterLevel1();
	
};

#endif // _GAME_GAMECONTROLLER_H_