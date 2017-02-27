#include <cstdlib>
#include <ctime>
#include "AnimalInfos.h"
#include "cocos2d.h"
#include "Auxiliary.h"

AnimalInfos::AnimalInfos(Infos infos) : infos(infos) {}

AnimalInfos::Info AnimalInfos::getInfoByType(InfoType type)
{
	switch(type)
	{
	case InfoType::NAME:
		return std::get<InfoType::NAME>(infos);

	case InfoType::PICTURE:
		return std::get<InfoType::PICTURE>(infos);

	case InfoType::SOUND:
		return std::get<InfoType::SOUND>(infos);

	case InfoType::EXPLAIN:
		return WStrToUTF8(std::get<InfoType::EXPLAIN>(infos));
	}
}

namespace
{
	const std::string PICPATH = "animals/pictures/";
	const std::string SOUNDPATH = "animals/sounds/";
}

AnimalInfos *AnimalInfoTable::infoTable = NULL;


AnimalInfos AnimalInfoTable::animalInfoTable[] = {
	(AnimalInfos)(std::make_tuple("alligator", PICPATH + "alligator.png", SOUNDPATH + "alligator.mp3", L"鳄鱼")),
	(AnimalInfos)(std::make_tuple("bird", PICPATH + "bird.png", SOUNDPATH + "bird.mp3", L"鸟")), 
	(AnimalInfos)(std::make_tuple("boar", PICPATH + "boar.png", SOUNDPATH + "boar.mp3", L"野猪")),
	(AnimalInfos)(std::make_tuple("butterfly", PICPATH + "butterfly.png", SOUNDPATH + "butterfly.mp3", L"蝴蝶")), 
	(AnimalInfos)(std::make_tuple("cat", PICPATH + "cat.png", SOUNDPATH + "cat.mp3", L"猫")),
	(AnimalInfos)(std::make_tuple("cattle", PICPATH + "cattle.png", SOUNDPATH + "cattle.mp3", L"牛")),
	(AnimalInfos)(std::make_tuple("chicken", PICPATH + "chicken.png", SOUNDPATH + "chicken.mp3", L"鸡")), 
	(AnimalInfos)(std::make_tuple("crab", PICPATH + "crab.png", SOUNDPATH + "crab.mp3", L"螃蟹")), 
	(AnimalInfos)(std::make_tuple("crow", PICPATH + "crow.png", SOUNDPATH + "crow.mp3", L"乌鸦")), 
	(AnimalInfos)(std::make_tuple("cuttlefish", PICPATH + "cuttlefish.png", SOUNDPATH + "cuttlefish.mp3", L"乌贼")),
	(AnimalInfos)(std::make_tuple("dinosaur", PICPATH + "dinosaur.png", SOUNDPATH + "dinosaur.mp3", L"恐龙")), 
	(AnimalInfos)(std::make_tuple("dog", PICPATH + "dog.png", SOUNDPATH + "dog.mp3", L"狗")), 
	(AnimalInfos)(std::make_tuple("dolphin", PICPATH + "dolphin.png", SOUNDPATH + "dolphin.mp3", L"海豚")),
	(AnimalInfos)(std::make_tuple("dragonfly", PICPATH + "dragonfly.png", SOUNDPATH + "dragonfly.mp3", L"蜻蜓")),
	(AnimalInfos)(std::make_tuple("duck", PICPATH + "duck.png", SOUNDPATH + "duck.mp3", L"鸭子")), 
	(AnimalInfos)(std::make_tuple("elephant", PICPATH + "elephant.png", SOUNDPATH + "elephant.mp3", L"大象")),
	(AnimalInfos)(std::make_tuple("fox", PICPATH + "fox.png", SOUNDPATH + "fox.mp3", L"狐狸")), 
	(AnimalInfos)(std::make_tuple("frog", PICPATH + "frog.png", SOUNDPATH + "frog.mp3", L"青蛙")),
	(AnimalInfos)(std::make_tuple("giraffe", PICPATH + "giraffe.png", SOUNDPATH + "giraffe.mp3", L"长颈鹿")), 
	(AnimalInfos)(std::make_tuple("goose", PICPATH + "goose.png", SOUNDPATH + "goose.mp3", L"鹅")),
	(AnimalInfos)(std::make_tuple("hedgehog", PICPATH + "hedgehog.png", SOUNDPATH + "hedgehog.mp3", L"刺猬")), 
	(AnimalInfos)(std::make_tuple("honeybee", PICPATH + "honeybee.png", SOUNDPATH + "honeybee.mp3", L"蜜蜂")),
	(AnimalInfos)(std::make_tuple("horse", PICPATH + "horse.png", SOUNDPATH + "horse.mp3", L"马")), 
	(AnimalInfos)(std::make_tuple("leopard", PICPATH + "leopard.png", SOUNDPATH + "leopard.mp3", L"豹子")), 
	(AnimalInfos)(std::make_tuple("lion", PICPATH + "lion.png", SOUNDPATH + "lion.mp3", L"狮子")),
	(AnimalInfos)(std::make_tuple("lizard", PICPATH + "lizard.png", SOUNDPATH + "lizard.mp3", L"蜥蜴")), 
	(AnimalInfos)(std::make_tuple("monkey", PICPATH + "monkey.png", SOUNDPATH + "monkey.mp3", L"猴子")),
	(AnimalInfos)(std::make_tuple("mouse", PICPATH + "mouse.png", SOUNDPATH + "mouse.mp3", L"老鼠")), 
	(AnimalInfos)(std::make_tuple("octopus", PICPATH + "octopus.png", SOUNDPATH + "octopus.mp3", L"章鱼")),
	(AnimalInfos)(std::make_tuple("orangutan", PICPATH + "orangutan.png", SOUNDPATH + "orangutan.mp3", L"猩猩")), 
	(AnimalInfos)(std::make_tuple("owl", PICPATH + "owl.png", SOUNDPATH + "owl.mp3", L"猫头鹰")), 
	(AnimalInfos)(std::make_tuple("parrot", PICPATH + "parrot.png", SOUNDPATH + "parrot.mp3", L"鹦鹉")),
	(AnimalInfos)(std::make_tuple("pig", PICPATH + "pig.png", SOUNDPATH + "pig.mp3", L"猪")), 
	(AnimalInfos)(std::make_tuple("pigeon", PICPATH + "pigeon.png", SOUNDPATH + "pigeon.mp3", L"鸽子")), 
	(AnimalInfos)(std::make_tuple("rabbit", PICPATH + "rabbit.png", SOUNDPATH + "rabbit.mp3", L"兔子")),
	(AnimalInfos)(std::make_tuple("sea horse", PICPATH + "sea horse.png", SOUNDPATH + "sea horse.mp3", L"海马")),
	(AnimalInfos)(std::make_tuple("sea turtle", PICPATH + "sea turtle.png", SOUNDPATH + "sea turtle.mp3", L"海龟")),
	(AnimalInfos)(std::make_tuple("seal", PICPATH + "seal.png", SOUNDPATH + "seal.mp3", L"海豹")), 
	(AnimalInfos)(std::make_tuple("shark", PICPATH + "shark.png", SOUNDPATH + "shark.mp3", L"鲨鱼")),
	(AnimalInfos)(std::make_tuple("sheep", PICPATH + "sheep.png", SOUNDPATH + "sheep.mp3", L"绵羊")), 
	(AnimalInfos)(std::make_tuple("snake", PICPATH + "snake.png", SOUNDPATH + "snake.mp3", L"蛇")),
	(AnimalInfos)(std::make_tuple("sparrow", PICPATH + "sparrow.png", SOUNDPATH + "sparrow.mp3", L"麻雀")), 
	(AnimalInfos)(std::make_tuple("squirrel", PICPATH + "squirrel.png", SOUNDPATH + "squirrel.mp3", L"松鼠")),
	(AnimalInfos)(std::make_tuple("starfish", PICPATH + "starfish.png", SOUNDPATH + "starfish.mp3", L"海星")), 
	(AnimalInfos)(std::make_tuple("swan", PICPATH + "swan.png", SOUNDPATH + "swan.mp3", L"天鹅")),
	(AnimalInfos)(std::make_tuple("tiger", PICPATH + "tiger.png", SOUNDPATH + "tiger.mp3", L"老虎")),
	(AnimalInfos)(std::make_tuple("tortoise", PICPATH + "tortoise.png", SOUNDPATH + "tortoise.mp3", L"乌龟")),
	(AnimalInfos)(std::make_tuple("whale", PICPATH + "whale.png", SOUNDPATH + "whale.mp3", L"鲸鱼")),
	(AnimalInfos)(std::make_tuple("zebra", PICPATH + "zebra.png", SOUNDPATH + "zebra.mp3", L"斑马")),
	(AnimalInfos)(std::make_tuple("kangaroo", PICPATH + "kangaroo.png", SOUNDPATH + "kangaroo.mp3", L"袋鼠")),
};

int AnimalInfoTable::animalInfoTableNum = sizeof(animalInfoTable)/sizeof(AnimalInfos);
int AnimalInfoTable::infoTableNum = sizeof(animalInfoTable)/sizeof(AnimalInfos);


//电器类
AnimalInfos AnimalInfoTable::applianceInfoTable[] = {
	(AnimalInfos)(std::make_tuple("camera", PICPATH + "camera.png", SOUNDPATH + "camera.mp3", L"照相机")),
	(AnimalInfos)(std::make_tuple("mouse", PICPATH + "mouse.png", SOUNDPATH + "mouse.mp3", L"鼠标")),
	(AnimalInfos)(std::make_tuple("blower", PICPATH + "blower.png", SOUNDPATH + "blower.mp3", L"吹风机")),
	(AnimalInfos)(std::make_tuple("notebook", PICPATH + "notebook.png", SOUNDPATH + "notebook.mp3", L"笔记本电脑")),
	(AnimalInfos)(std::make_tuple("shaver", PICPATH + "shaver.png", SOUNDPATH + "shaver.mp3", L"电动剃须刀")),
	(AnimalInfos)(std::make_tuple("printer", PICPATH + "printer.png", SOUNDPATH + "printer.mp3", L"打印机")),
	(AnimalInfos)(std::make_tuple("telephone", PICPATH + "telephone.png", SOUNDPATH + "telephone.mp3", L"电话")),
	(AnimalInfos)(std::make_tuple("television", PICPATH + "television.png", SOUNDPATH + "television.mp3", L"电视")),
	(AnimalInfos)(std::make_tuple("cellphone", PICPATH + "cellphone.png", SOUNDPATH + "cellphone.mp3", L"手机")),
	(AnimalInfos)(std::make_tuple("headset", PICPATH + "headset.png", SOUNDPATH + "headset.mp3", L"耳机")),
	(AnimalInfos)(std::make_tuple("iron", PICPATH + "iron.png", SOUNDPATH + "iron.mp3", L"熨斗")),				
	(AnimalInfos)(std::make_tuple("bulb", PICPATH + "bulb.png", SOUNDPATH + "bulb.mp3", L"电灯泡")),
	(AnimalInfos)(std::make_tuple("refrigerator", PICPATH + "refrigerator.png", SOUNDPATH + "refrigerator.mp3", L"电冰箱")),
	(AnimalInfos)(std::make_tuple("fan", PICPATH + "fan.png", SOUNDPATH + "fan.mp3", L"风扇")),
	(AnimalInfos)(std::make_tuple("oven", PICPATH + "oven.png", SOUNDPATH + "oven.mp3", L"烤箱")),
	(AnimalInfos)(std::make_tuple("juicer", PICPATH + "juicer.png", SOUNDPATH + "juicer.mp3", L"榨汁机")),
};
int AnimalInfoTable::applianceInfoTableNum = sizeof(applianceInfoTable)/sizeof(AnimalInfos);
//水果类
AnimalInfos AnimalInfoTable::fruitInfoTable[] = {
	(AnimalInfos)(std::make_tuple("kiwi", PICPATH + "kiwi.png", SOUNDPATH + "kiwi.mp3", L"猕猴桃")),
	(AnimalInfos)(std::make_tuple("cherry", PICPATH + "cherry.png", SOUNDPATH + "cherry.mp3", L"樱桃")),
	(AnimalInfos)(std::make_tuple("coconut", PICPATH + "coconut.png", SOUNDPATH + "coconut.mp3", L"椰子")),
	(AnimalInfos)(std::make_tuple("peach", PICPATH + "peach.png", SOUNDPATH + "peach.mp3", L"桃子")),
	(AnimalInfos)(std::make_tuple("orange", PICPATH + "orange.png", SOUNDPATH + "orange.mp3", L"橙子")),	
	(AnimalInfos)(std::make_tuple("grape", PICPATH + "grape.png", SOUNDPATH + "grape.mp3", L"葡萄")),
	(AnimalInfos)(std::make_tuple("strawberry", PICPATH + "strawberry.png", SOUNDPATH + "strawberry.mp3", L"草莓")),
	(AnimalInfos)(std::make_tuple("lemon", PICPATH + "lemon.png", SOUNDPATH + "lemon.mp3", L"柠檬")),
	(AnimalInfos)(std::make_tuple("pineapple", PICPATH + "pineapple.png", SOUNDPATH + "pineapple.mp3", L"菠萝")),
	
	(AnimalInfos)(std::make_tuple("apple", PICPATH + "apple.png", SOUNDPATH + "apple.mp3", L"苹果")),
	(AnimalInfos)(std::make_tuple("pear", PICPATH + "pear.png", SOUNDPATH + "pear.mp3", L"梨")),
	(AnimalInfos)(std::make_tuple("mango", PICPATH + "mango.png", SOUNDPATH + "mango.mp3", L"芒果")),
	(AnimalInfos)(std::make_tuple("longan", PICPATH + "longan.png", SOUNDPATH + "longan.mp3", L"桂圆")),
	(AnimalInfos)(std::make_tuple("blueberry ", PICPATH + "blueberry .png", SOUNDPATH + "blueberry .mp3", L"蓝莓")),
	(AnimalInfos)(std::make_tuple("carambola ", PICPATH + "carambola.png", SOUNDPATH + "carambola.mp3", L"杨桃")),
	(AnimalInfos)(std::make_tuple("durian", PICPATH + "durian.png", SOUNDPATH + "durian.mp3", L"榴莲")),
	(AnimalInfos)(std::make_tuple("plum", PICPATH + "plum.png", SOUNDPATH + "plum.mp3", L"李子")),
	(AnimalInfos)(std::make_tuple("tangerine", PICPATH + "tangerine.png", SOUNDPATH + "longan.mp3", L"橘子")),
	(AnimalInfos)(std::make_tuple("pomegranate", PICPATH + "pomegranate.png", SOUNDPATH + "pomegranate.mp3", L"石榴")),
	(AnimalInfos)(std::make_tuple("muskmelon", PICPATH + "muskmelon.png", SOUNDPATH + "muskmelon.mp3", L"香瓜")),
	(AnimalInfos)(std::make_tuple("shaddock", PICPATH + "shaddock.png", SOUNDPATH + "shaddock.mp3", L"柚子")),
	(AnimalInfos)(std::make_tuple("persimmon", PICPATH + "persimmon.png", SOUNDPATH + "persimmon.mp3", L"柿子")),
	(AnimalInfos)(std::make_tuple("fig", PICPATH + "fig.png", SOUNDPATH + "fig.mp3", L"无花果")),
	(AnimalInfos)(std::make_tuple("lichee", PICPATH + "lichee.png", SOUNDPATH + "lichee.mp3", L"荔枝")),
	(AnimalInfos)(std::make_tuple("raspberry", PICPATH + "raspberry.png", SOUNDPATH + "raspberry.mp3", L"树莓")),	
	(AnimalInfos)(std::make_tuple("cumquat", PICPATH + "cumquat.png", SOUNDPATH + "cumquat.mp3", L"金桔")),	
	(AnimalInfos)(std::make_tuple("waxberry", PICPATH + "waxberry.png", SOUNDPATH + "waxberry.mp3", L"杨梅")),	
	(AnimalInfos)(std::make_tuple("haw", PICPATH + "haw.png", SOUNDPATH + "haw.mp3", L"山楂")),
	(AnimalInfos)(std::make_tuple("greengage", PICPATH + "greengage.png", SOUNDPATH + "greengage.mp3", L"青梅")),	
	(AnimalInfos)(std::make_tuple("pitaya", PICPATH + "pitaya.png", SOUNDPATH + "pitaya.mp3", L"火龙果")),	
	(AnimalInfos)(std::make_tuple("pawpaw", PICPATH + "pawpaw.png", SOUNDPATH + "pawpaw.mp3", L"木瓜")),
	(AnimalInfos)(std::make_tuple("banana", PICPATH + "banana.png", SOUNDPATH + "banana.mp3", L"香蕉")),
		(AnimalInfos)(std::make_tuple("watermelon", PICPATH + "watermelon.png", SOUNDPATH + "watermelon.mp3", L"西瓜")),
};

int AnimalInfoTable::fruitInfoTableNum = sizeof(fruitInfoTable)/sizeof(AnimalInfos);

//蔬菜类
AnimalInfos AnimalInfoTable::vegetableInfoInfoTable[] = {
	(AnimalInfos)(std::make_tuple("pea", PICPATH + "pea.png", SOUNDPATH + "pea.mp3", L"豌豆")),
	(AnimalInfos)(std::make_tuple("cabbage", PICPATH + "cabbage.png", SOUNDPATH + "cabbage.mp3", L"卷心菜")),
	(AnimalInfos)(std::make_tuple("pepper", PICPATH + "pepper.png", SOUNDPATH + "pepper.mp3", L"辣椒")),
	(AnimalInfos)(std::make_tuple("cauliflower", PICPATH + "cauliflower.png", SOUNDPATH + "cauliflower.mp3", L"花菜")),
	(AnimalInfos)(std::make_tuple("tomato", PICPATH + "tomato.png", SOUNDPATH + "tomato.mp3", L"番茄")),
	(AnimalInfos)(std::make_tuple("cucumber", PICPATH + "cucumber.png", SOUNDPATH + "cucumber.mp3", L"黄瓜")),
	(AnimalInfos)(std::make_tuple("potato", PICPATH + "potato.png", SOUNDPATH + "potato.mp3", L"土豆")),
	(AnimalInfos)(std::make_tuple("greens", PICPATH + "greens.png", SOUNDPATH + "greens.mp3", L"青菜")),			
	(AnimalInfos)(std::make_tuple("carrot", PICPATH + "carrot.png", SOUNDPATH + "carrot.mp3", L"胡萝卜")),		
	(AnimalInfos)(std::make_tuple("pumpkin", PICPATH + "pumpkin.png", SOUNDPATH + "pumpkin.mp3", L"南瓜")),	
	(AnimalInfos)(std::make_tuple("celery ", PICPATH + "celery .png", SOUNDPATH + "celery .mp3", L"芹菜")),		
	(AnimalInfos)(std::make_tuple("garlic ", PICPATH + "garlic .png", SOUNDPATH + "garlic .mp3", L"蒜")),		
	(AnimalInfos)(std::make_tuple("onion ", PICPATH + "onion .png", SOUNDPATH + "onion .mp3", L"洋葱")),		
	(AnimalInfos)(std::make_tuple("corn", PICPATH + "corn.png", SOUNDPATH + "corn.mp3", L"玉米")),		
	(AnimalInfos)(std::make_tuple("spinach", PICPATH + "spinach.png", SOUNDPATH + "spinach.mp3", L"菠菜")),
	(AnimalInfos)(std::make_tuple("eggplant", PICPATH + "eggplant.png", SOUNDPATH + "eggplant.mp3", L"茄子")),		
	(AnimalInfos)(std::make_tuple("leek", PICPATH + "leek.png", SOUNDPATH + "leek.mp3", L"韭菜")),
	(AnimalInfos)(std::make_tuple("taro", PICPATH + "taro.png", SOUNDPATH + "taro.mp3", L"芋头")),			
	(AnimalInfos)(std::make_tuple("radish", PICPATH + "radish.png", SOUNDPATH + "radish.mp3", L"萝卜")),	
	(AnimalInfos)(std::make_tuple("okra", PICPATH + "okra.png", SOUNDPATH + "okra.mp3", L"秋葵")),		
};
int AnimalInfoTable::vegetableInfoInfoTableNum = sizeof(vegetableInfoInfoTable)/sizeof(AnimalInfos);

//球类
AnimalInfos AnimalInfoTable::ballInfoTable[] = {
	(AnimalInfos)(std::make_tuple("basketball", PICPATH + "basketball.png", SOUNDPATH + "basketball.mp3", L"篮球")),
	(AnimalInfos)(std::make_tuple("football", PICPATH + "football.png", SOUNDPATH + "football.mp3", L"足球")),
	(AnimalInfos)(std::make_tuple("tennis", PICPATH + "tennis.png", SOUNDPATH + "tennis.mp3", L"网球")),
	(AnimalInfos)(std::make_tuple("rugby", PICPATH + "rugby.png", SOUNDPATH + "rugby.mp3", L"橄榄球")),
	(AnimalInfos)(std::make_tuple("volleyball", PICPATH + "volleyball.png", SOUNDPATH + "volleyball.mp3", L"排球")),
	(AnimalInfos)(std::make_tuple("bowling", PICPATH + "bowling.png", SOUNDPATH + "bowling.mp3", L"保龄球")),
	(AnimalInfos)(std::make_tuple("billiards", PICPATH + "billiards.png", SOUNDPATH + "billiards.mp3", L"台球")),
	(AnimalInfos)(std::make_tuple("puck", PICPATH + "puck.png", SOUNDPATH + "puck.mp3", L"冰球")),
	(AnimalInfos)(std::make_tuple("golf", PICPATH + "golf.png", SOUNDPATH + "golf.mp3", L"高尔夫球")),
	(AnimalInfos)(std::make_tuple("baseball", PICPATH + "baseball.png", SOUNDPATH + "baseball.mp3", L"棒球")),
	(AnimalInfos)(std::make_tuple("hockey", PICPATH + "hockey.png", SOUNDPATH + "hockey.mp3", L"曲棍球")),
	(AnimalInfos)(std::make_tuple("cricket", PICPATH + "cricket.png", SOUNDPATH + "cricket.mp3", L"板球")),
	(AnimalInfos)(std::make_tuple("softball", PICPATH + "softball.png", SOUNDPATH + "softball.mp3", L"垒球")),
	(AnimalInfos)(std::make_tuple("polo", PICPATH + "polo.png", SOUNDPATH + "polo.mp3", L"马球")),
	(AnimalInfos)(std::make_tuple("handball", PICPATH + "handball.png", SOUNDPATH + "handball.mp3", L"手球")),
};

int AnimalInfoTable::ballInfoTableNum = sizeof(ballInfoTable)/sizeof(AnimalInfos);
//食物类
AnimalInfos AnimalInfoTable::foodInfoTable[] = {
	(AnimalInfos)(std::make_tuple("sandwich", PICPATH + "sandwich.png", SOUNDPATH + "sandwich.mp3", L"三明治")),
	(AnimalInfos)(std::make_tuple("rice", PICPATH + "rice.png", SOUNDPATH + "rice.mp3", L"米饭")),
	(AnimalInfos)(std::make_tuple("congee", PICPATH + "congee.png", SOUNDPATH + "congee.mp3", L"粥")),
	(AnimalInfos)(std::make_tuple("soup", PICPATH + "soup.png", SOUNDPATH + "soup.mp3", L"汤")),
	(AnimalInfos)(std::make_tuple("dumpling", PICPATH + "dumpling.png", SOUNDPATH + "dumpling.mp3", L"饺子")),
	(AnimalInfos)(std::make_tuple("noodle", PICPATH + "noodle.png", SOUNDPATH + "noodle.mp3", L"面条")),
	(AnimalInfos)(std::make_tuple("pizza", PICPATH + "pizza.png", SOUNDPATH + "pizza.mp3", L"比萨饼")),
	(AnimalInfos)(std::make_tuple("bread", PICPATH + "bread.png", SOUNDPATH + "bread.mp3", L"面包")),
	(AnimalInfos)(std::make_tuple("egg", PICPATH + "egg.png", SOUNDPATH + "egg.mp3", L"鸡蛋")),
	(AnimalInfos)(std::make_tuple("cookies", PICPATH + "cookies.png", SOUNDPATH + "cookies.mp3", L"饼干")),
	(AnimalInfos)(std::make_tuple("pickle", PICPATH + "pickle.png", SOUNDPATH + "pickle.mp3", L"泡菜")),
	(AnimalInfos)(std::make_tuple("cake", PICPATH + "cake.png", SOUNDPATH + "cake.mp3", L"蛋糕")),
	(AnimalInfos)(std::make_tuple("hamburger", PICPATH + "hamburger.png", SOUNDPATH + "hamburger.mp3", L"汉堡")),
	(AnimalInfos)(std::make_tuple("ham", PICPATH + "ham.png", SOUNDPATH + "ham.mp3", L"火腿")),
	(AnimalInfos)(std::make_tuple("wonton", PICPATH + "wonton.png", SOUNDPATH + "wonton.mp3", L"馄饨")),
	(AnimalInfos)(std::make_tuple("milk", PICPATH + "milk.png", SOUNDPATH + "milk.mp3", L"牛奶")),
	(AnimalInfos)(std::make_tuple("chocolate", PICPATH + "chocolate.png", SOUNDPATH + "chocolate.mp3", L"巧克力")),
	(AnimalInfos)(std::make_tuple("sausage", PICPATH + "sausage.png", SOUNDPATH + "alligator.mp3", L"香肠")),
	(AnimalInfos)(std::make_tuple("steak", PICPATH + "steak.png", SOUNDPATH + "steak.mp3", L"牛排")),
	(AnimalInfos)(std::make_tuple("cheese", PICPATH + "cheese.png", SOUNDPATH + "cheese.mp3", L"奶酪")),
	(AnimalInfos)(std::make_tuple("coffee", PICPATH + "coffee.png", SOUNDPATH + "coffee.mp3", L"咖啡")),
	(AnimalInfos)(std::make_tuple("tea", PICPATH + "tea.png", SOUNDPATH + "tea.mp3", L"茶")),
	(AnimalInfos)(std::make_tuple("beer", PICPATH + "beer.png", SOUNDPATH + "beer.mp3", L"啤酒")),
	(AnimalInfos)(std::make_tuple("lollipop", PICPATH + "lollipop.png", SOUNDPATH + "lollipop.mp3", L"棒棒糖")),
};


int AnimalInfoTable::foodInfoTableNum = sizeof(foodInfoTable)/sizeof(AnimalInfos);

void AnimalInfoTable::infoTableNumSelect( INFO_TYPE_e type )
{
	
	switch( type )
	{
	case INFO_TYPE_e::INFO_TYPE_ANIMAL:
		AnimalInfoTable::infoTable = animalInfoTable;
		AnimalInfoTable::infoTableNum = sizeof(animalInfoTable)/sizeof(AnimalInfos);
		break;
	default:
		AnimalInfoTable::infoTable = animalInfoTable;
		AnimalInfoTable::infoTableNum = sizeof(animalInfoTable)/sizeof(AnimalInfos);
		break;
	}
	
	return ;
}

AnimalInfos* AnimalInfoTable::getInfosByTypeInfo(AnimalInfos::InfoType type, AnimalInfos::Info info)
{
	
	for( int i = 0 ; i < infoTableNum ; i++ )
	{
		if(infoTable[i].getInfoByType(type) == info)
		{
			return &infoTable[i];
		}
	}
	cocos2d::log("Type: %d, Info: %s. No such animal in animal table!", (int)type, info.c_str());
	return NULL;
	
}