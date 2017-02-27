#ifndef _GAME_ANIMALINFO_H_
#define _GAME_ANIMALINFO_H_

#include <tuple>
#include <string>

class AnimalInfos
{
private:
	typedef std::tuple<const std::string, const std::string, const std::string, const std::wstring> Infos;
	Infos infos;

public:
	enum InfoType { NAME = 0, PICTURE = 1, SOUND = 2, EXPLAIN = 3 , NONE };
	typedef std::string Info;

	AnimalInfos(Infos);

	Info getInfoByType(InfoType);

};
typedef enum{
	INFO_TYPE_ANIMAL = 0,
}INFO_TYPE_e;

class AnimalInfoTable
{
public:

	static AnimalInfos *infoTable;
	static int infoTableNum;

	static AnimalInfos animalInfoTable[];
	static int animalInfoTableNum;

	//static AnimalInfos infoTable[];
	
	static AnimalInfos applianceInfoTable[];
	static int applianceInfoTableNum;

	static AnimalInfos fruitInfoTable[];
	static int fruitInfoTableNum;

	static AnimalInfos vegetableInfoInfoTable[];
	static int vegetableInfoInfoTableNum;

	static AnimalInfos ballInfoTable[];
	static int ballInfoTableNum;

	static AnimalInfos foodInfoTable[];
	static int foodInfoTableNum;

	static void infoTableNumSelect( INFO_TYPE_e type );
public:

	static AnimalInfos* getInfosByTypeInfo(AnimalInfos::InfoType, AnimalInfos::Info);

};
#endif // _GAME_ANIMALINFO_H_