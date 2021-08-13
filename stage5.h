#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"

class enemyManager;
class enemyManagerB;
class enemyManagerBoss;
class player;

class stage5 : public gameNode
{
private:
	player* p1;

	enemyManager* e1;
	enemyManager* e2;
	enemyManagerBoss* e3;

	int gameOverCnt;
	int cnt;
public:
	stage5();
	~stage5();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	virtual void sceneChange();
	virtual void mapBlock();
};