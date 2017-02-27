#ifndef _GAME_WORDANIMAL_H_
#define _GAME_WORDANIMAL_H_

#include "Animal.h"

class WordAnimal : public Animal
{

private:
	LabelTTF *wordBoard;
	//virtual bool initWithArgs(const std::string, const std::string, const std::string , const std::string ) override;

public:
	void setWord(std::string);



};
#endif // _GAME_WORDANIMAL_H_