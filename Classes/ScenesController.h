#include "LevelScene1.h"

class ScenesController
{

private:
	ScenesController *_controller;
public:
	static ScenesController *getInstance();
	void startGame();

};