#pragma once
#ifndef _GAME_AUXILIARY_H_
#define _GAME_AUXILIARY_H_

#include <string>
#include "cocos2d.h"

USING_NS_CC;

std::string WStrToUTF8(const std::wstring&);
std::string itos(int);
Rect getRect(Sprite*);

#endif // _GAME_AUXILIARY_H_