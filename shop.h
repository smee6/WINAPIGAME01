#pragma once
#include "gameNode.h"
#include "player.h"

class player;
class shop : public gameNode
{
private:
	image* eat;

	player* p1;
	int cnt;
	int shopNum = 1;
	int index;
	bool eatmotion;

public:
	shop();
	~shop();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};