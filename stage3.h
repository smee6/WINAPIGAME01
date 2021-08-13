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

class stage3 : public gameNode
{
private:
	player* p1;
	image* door;
	RECT rc;
	int index;
	bool doorOpen;
public:
	stage3();
	~stage3();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void sceneChange();
	virtual void mapBlock();
};