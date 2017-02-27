#include "WordAnimal.h"

static std::string WORDANIMALPICPATH = "animals/pictures/wordanimal.png";

/*
bool WordAnimal::initWithArgs(const std::string name, const std::string picFile, const std::string soundFile, const std::string explaination)

{
	Sprite::initWithFile(WORDANIMALPICPATH);

	wordBoard = LabelTTF::create();
	wordBoard->setString(name);
	wordBoard->setFontSize(42);
	wordBoard->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
	addChild(wordBoard, ItemPriority::PRIORITY_ANIMAL_WORDBOARD);
	this->name = name;
	this->picFile = picFile;
	this->soundFile = soundFile;
	this->explaination = explaination;
	return true;
}
*/
void WordAnimal::setWord(std::string word)
{
	wordBoard->setString(word);
}