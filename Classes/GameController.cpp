#include "GameController.h"

GameController *GameController::_controller = nullptr;

GameController::GameController(){}

GameController::~GameController(){}

GameController *GameController::getInstance()
{
	if(_controller == nullptr)
	{
		_controller = new GameController();
	}
	return _controller;
}

void GameController::startGame()
{
	auto director = Director::getInstance();

	auto scene = StartScene::createScene();
	//auto scene = FailScene::createScene();
	director->runWithScene(scene);
}

void GameController::SceneBack(int id)
{
	auto startScene = StartScene::createScene();
	if (!startScene)
	{
		return ;
	}

	Scene* pScene = TransitionCrossFade::create(0.2,startScene);
	Director::getInstance()->replaceScene(pScene);
}

void GameController::SceneSuccess(int id, int score)
{	
	SuccessScene::setScore(score);
	auto scene = SuccessScene::createScene(id);
	if (!scene)
	{
		return ;
	}
	Scene* pScene = TransitionCrossFade::create(0.2,scene);
	Director::getInstance()->replaceScene(pScene);
}

void GameController::SceneFail(int id)
{		
	auto scene = FailScene::createScene(id);
	if (!scene)
	{
		return ;
	}

	Scene* pScene = TransitionFade::create(0.2,scene);
	Director::getInstance()->replaceScene(pScene);
}

void GameController::SceneNext(int id)
{
	switch(id)
	{
/*	case 1:
		enterLevel2();
		break;

	case 2:
		enterLevel3();
		break;
	case 3:
		enterLevel4();
		break;
	*/
	case 4:
		enterMenu();
		break;
	default:
		break;
	}
}

void GameController::SceneReplay(int id)
{
	switch(id)
	{
	case 1:
		enterLevel1();
		break;
	default:
		break;
	}
}

void GameController::enterMenu()
{		
	auto startScene = StartScene::createScene();
	if (!startScene)
	{
		return ;
	}

	Scene* pScene = TransitionCrossFade::create(0.2,startScene);
	Director::getInstance()->replaceScene(pScene);
}

void GameController::enterLevel1()
{		
	auto scene1 = LevelScene1::createScene();
	if (!scene1)
	{
		return ;
	}

	Scene* pScene = TransitionCrossFade::create(0.2, scene1);
	Director::getInstance()->replaceScene(pScene);
}
