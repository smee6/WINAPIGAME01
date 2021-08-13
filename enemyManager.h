#pragma once
#include "gameNode.h"
#include "player.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "stage4.h"
#include "stage5.h"

enum enemyState {
	enemyIdle,
	enemyWalk, // 감지하면 걸어오는것
	enemyAttack,
	hitByPlayer,
	enemyKO
};

class player;


class enemyManager : public gameNode
{
private:

protected:
	image* img;		//이미지
	RECT rc;		//렉트
	float x, y;		//중점좌표
	int cnt, index , delay;
	int hp;
	int playerStt;

	/*int deadbodypop = 1;*/
	bool dead;
	enemyState stt;


	int plx, ply;
	int cam;

public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual HRESULT init(int xl, int yl);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void draw();

	virtual void tracingPlayer();
	virtual void attack();
	virtual void hitByPlayer();
	virtual void KO();

	
	virtual void setCam(int x);

	virtual void setPlayerX(int x);
	virtual void setPlayerY(int y);
	virtual int showState();
	virtual int getX();
	virtual int getY();
	virtual void getPlayerstt(int x);
};

