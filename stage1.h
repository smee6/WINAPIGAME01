#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"
#include "enemyManagerB.h"



class enemyManager;
class enemyManagerB;
class player;

class stage1 : public gameNode
{
private:
	player* p1;
	enemyManager* e1;
	enemyManager* e2;
	enemyManagerB* e3;
	enemyManager* e4;
	enemyManager* e5;

public:
	stage1();
	~stage1();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void sceneChange();
	virtual void mapBlock();
};