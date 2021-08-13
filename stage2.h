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

class stage2 : public gameNode
{
private:
	player* p1;
	enemyManagerB* e1;
	enemyManagerB* e2;
	enemyManager* e3;
	enemyManagerC* e4;

public:
	stage2();
	~stage2();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void sceneChange();
	virtual void mapBlock();
};