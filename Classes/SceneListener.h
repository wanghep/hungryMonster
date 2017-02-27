#ifndef _GAME_SCENESLISTENER_H_
#define _GAME_SCENESLISTENER_H_

class SceneListener
{
public:
	virtual void SceneBack(int id) = 0;
	virtual void SceneFail(int id) = 0;
	virtual void SceneSuccess(int id, int score) = 0;
	virtual void SceneNext(int id) = 0;
	virtual void SceneReplay(int id) = 0;
};
#endif //_GAME_SCENESLISTENER_H_