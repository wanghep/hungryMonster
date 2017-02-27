#include "LevelScene1.h"

Scene *LevelScene1::createScene()
{
	auto scene = Scene::create();
	auto layer = LevelScene1::create();
	if(layer)
		log("\nLOG: layer is not nullptr\n");
	else
		log("\nLOG: layer is nullptr\n");
	scene->addChild(layer);
	return scene;
}

void LevelScene1::setId()
{
	id = 1;
}

void LevelScene1::setSceneListener()
{
	sceneListener = GameController::getInstance();
}

void LevelScene1::setGameParameter()
{
	targetCount = 10;
	increasedScore = 1;
	decreasedScore = 0;
	showTargetInterval = 4;
	maxAnimalNum = 15;
	minDuration = 2.0;
	maxDuration = 8.0;
	terminalTime = 0; // No timer
}

void LevelScene1::setTitleInfo()
{
	titleBgPath = "scenes/levelscene/titlebg1.png";
	titlePath = "scenes/levelscene/title1.png";
}
/*
void LevelScene1::setMonsterBoard(Monster* monster)
{
	std::string explaination = AnimalInfoTable::getInfosByTypeInfo(AnimalInfos::InfoType::NAME, targetWord)
		.getInfoByType(AnimalInfos::InfoType::EXPLAIN);
	monster->setWord(explaination);
}
*/