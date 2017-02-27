#ifndef _GAME_ITEMPRIORITY_H_
#define _GAME_ITEMPRIORITY_H_

#include <iostream>

class ItemPriority
{
public:
	static const int PRIORITY_BACKGROUND = 0;
	static const int PRIORITY_CLOSEBUTTON = 12;

	// StartScene
	static const int PRIORITY_SNOW = 1;
	static const int PRIORITY_START_TITLE = 2;
	static const int PRIORITY_LEVELITEM = 2;
	static const int PRIORITY_HAND = 12;

	// LevelScene
	static const int PRIORITY_MONSTER = 3;
	static const int PRIORITY_MONSTER_ANIMATION = 4;
	static const int PRIORITY_MONSTER_BOARD = 5;
	static const int PRIORITY_MONSTER_WORD = 6;
	static const int PRIORITY_ANIMAL = 7;
	static const int PRIORITY_ANIMAL_WORDBOARD = 8;
	static const int PRIORITY_CLOUD = 7;
	static const int PRIORITY_FIREFLY = 7;
	static const int PRIORITY_SHOWANIMAL = 8;
	static const int PRIORITY_PLUSSCORE = 9;
	static const int PRIORITY_TITLE_BACKGROUND = 10;
	static const int PRIORITY_TITLE = 12;
	static const int PRIORITY_STAR = 12;
	static const int PRIORITY_SCOREBOARD = 12;
	static const int PRIORITY_PROGNUMBOARD = 12;
	static const int PRIORITY_BARBACKGROUND = 12;
	static const int PRIORITY_PROGRESSBAR = 13;
	static const int PRIORITY_TIMER = 12;
	static const int PRIORITY_TIMERBOARD = 12;
	static const int PRIORITY_EXTRA_SPRITE = 14;
	
	// SuccessScene & FailScene
	static const int PRIORITY_BACKBUTTON = 6;

	static const int PRIORITY_SUCCESSBOARD = 5;
	static const int PRIORITY_NEXTBUTTON = 6;

	static const int PRIORITY_FAILBOARD = 5;
	static const int PRIORITY_REPLAYBUTTON = 6;


	static const int TAG_PROGRESSBAR = 40;
};
#endif // _GAME_ITEMPRIORITY_H_