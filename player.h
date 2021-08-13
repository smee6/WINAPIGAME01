#pragma once
#include "gameNode.h"
#define playerSpeed 6

enum state {
	right_idle,
	right_walk,
	right_punch,
	right_kick,
	right_jump,
	right_jumpattck,
	left_idle,
	left_walk,
	left_punch,
	left_kick,
	left_jump,
	left_jumpattck,
	hitted,

};
class player : public gameNode
{
	state stt;


protected:

	image* img;		//�̹���
	RECT rc;		//��Ʈ
	float x, y;		//������ǥ
	float speed = playerSpeed;
	int cnt , index ;
	bool isJump = false;
	int hp;
	int gameOverCnt;
	bool isRun;

	bool isHit;
	bool isDead;
	int enemyX;

	

public:
	player();
	~player();

	virtual HRESULT init(int xl, int yl);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void draw();
	virtual void keyControl();
	virtual void move();
	virtual void KO();
	

	virtual int showRC(int x); // 1234�� �޾ƿðŰ� ����Ʈ ž ����Ʈ ���� ��
	virtual int showXY(int c); // 1,2 �� �ް� x�� 1 y�� 2
	virtual int showState();
	//virtual int getSpd();
	//virtual void setSpd(int x);

	virtual void camera();
	

	virtual void hit();
	// �������� ȭ�鿡�� �̰� �ѷ��ش����� e1->stt �̷������� �ֳʹ� ���¸� �޾ƿͼ� �ֳʹ̰� �������̸� �� �Լ����� ���� �������༭ 
	// �������� �԰� �ڷ� ƨ�ܳ����� ������

	virtual void amIhit(int x);
	virtual void getEnemyX(int x);


	int isRunF();

	virtual int getHP();
	virtual void setHP(int x);
	

	virtual void gameOver();
	/// <summary>
	///  �� �̵��ÿ� ī�޶� �������ش�
	/// </summary>
	virtual void setCameraReset();
	virtual void setCameraXpos(int x);
	/// <ī�޶� ����>
	/// //////////////////////////////////////////////////////////
	int cameraXpos = 0;
	bool cantGoUp, cantGoDown = false;
};

