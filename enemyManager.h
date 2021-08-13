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
	enemyWalk, // �����ϸ� �ɾ���°�
	enemyAttack,
	hitByPlayer,
	enemyKO
};

class player;


class enemyManager : public gameNode
{
private:

protected:
	image* img;		//�̹���
	RECT rc;		//��Ʈ
	float x, y;		//������ǥ
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

