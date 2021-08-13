#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
#include "enemyManagerB.h"
#include "enemyManagerC.h"
#include "enemyManagerD.h"

class enemyManager;
class enemyManagerB;
class enemyManagerC;
class enemyManagerD;

class player;

class stage4 : public gameNode
{
private:
	player* p1;
	enemyManagerC* e1;
	enemyManagerC* e2;
	enemyManagerB* e3;
	enemyManagerD* e4;
	enemyManager* e5;

public:
	stage4();
	~stage4();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	virtual void sceneChange();
	virtual void mapBlock();
};