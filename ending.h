#pragma once
#include "gameNode.h"


class ending : public gameNode
{
private:

	int cnt;
	int cnt2;
	int index;
	int mapPos;
	int gameOverCnt;

public:
	ending();
	~ending();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};