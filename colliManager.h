#pragma once
#include "gameNode.h"
class colliManager : public gameNode
{
private:

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

