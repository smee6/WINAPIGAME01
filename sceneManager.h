#pragma once
#include "singletonBase.h"
#include <string>
#include <map>

class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
private:
	typedef map<string, gameNode*>				mapSceneList;
	typedef map<string, gameNode*>::iterator	mapSceneIter;

private:
	static gameNode* _currentScene;

	mapSceneList _mSceneList;

	int currentLoc = 0;

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();
	int getMapNumber();
	void setMapNumber(int x);


	
	/////////////////////////////////
	int hp;
	int mapchangecnt = 0;

	gameNode* addScene(string sceneName, gameNode* scene);

	HRESULT changeScene(string sceneName);
};

