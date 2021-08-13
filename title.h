#pragma once
#include "gameNode.h"



class title : public gameNode
{
private:
	int cnt;
	int logoshow;
	int titleshow;
	bool logoOn,titleOn;

public:
	title();
	~title();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};