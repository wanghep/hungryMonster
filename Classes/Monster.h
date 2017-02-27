#ifndef _GAME_MONSTER_H_
#define _GAME_MONSTER_H_

#include <iostream>
#include <vector>
#include "cocos2d.h"
#include "Animal.h"

USING_NS_CC;

class Monster : public Sprite
{
private:	
#define MAX_LIFE_NUMBER			5
	static int life;
	int id;
public:
	Monster();
	static Monster* create();
	bool init();
	virtual ~Monster();

	Sprite *animationSprite;

	static int getLife();
	static void addALife();
	static bool deadALife();
	void setId( int newId );
	int getId();
	bool capture(Animal *anim);
	void setWord(std::string);

	Sprite *board;
	LabelTTF *word;

	static int scores[10];
	void freshWordBoard();
	void setBoard();
	void hideBoard();

	FiniteTimeAction *currentAction;
	FiniteTimeAction *leftMoveAction;
	FiniteTimeAction *rightMoveAction;
	FiniteTimeAction *leftHappyAction;
	FiniteTimeAction *rightHappyAction;
	FiniteTimeAction *leftAngryAction;
	FiniteTimeAction *rightAngryAction;
	FiniteTimeAction *deadAction;
	void leftMove(Node * n = NULL);
	void rightMove(Node *	n = NULL);
	static void staticVarInit();
	void angry();
	void happy();
	void dead();
private:
	Size contentSize;

	void setAnimation();

};

bool isContained(Rect, Rect);

#endif // _GAME_MONSTER_H_