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

	image* img;		//이미지
	RECT rc;		//렉트
	float x, y;		//중점좌표
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
	

	virtual int showRC(int x); // 1234로 받아올거고 레프트 탑 라이트 바텀 순
	virtual int showXY(int c); // 1,2 로 받고 x는 1 y는 2
	virtual int showState();
	//virtual int getSpd();
	//virtual void setSpd(int x);

	virtual void camera();
	

	virtual void hit();
	// 스테이지 화면에서 이걸 뿌려준다음에 e1->stt 이런식으로 애너미 상태를 받아와서 애너미가 공격중이면 이 함수에서 뭔가 전달해줘서 
	// 데미지를 입고 뒤로 튕겨나가게 해주자

	virtual void amIhit(int x);
	virtual void getEnemyX(int x);


	int isRunF();

	virtual int getHP();
	virtual void setHP(int x);
	

	virtual void gameOver();
	/// <summary>
	///  맵 이동시에 카메라를 리셋해준다
	/// </summary>
	virtual void setCameraReset();
	virtual void setCameraXpos(int x);
	/// <카메라 관련>
	/// //////////////////////////////////////////////////////////
	int cameraXpos = 0;
	bool cantGoUp, cantGoDown = false;
};

