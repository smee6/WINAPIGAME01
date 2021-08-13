#include "pch.h"
#include "enemyManagerB.h"
#include "player.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "stage4.h"
#include "stage5.h"

enemyManagerB::enemyManagerB()
{

}

enemyManagerB::~enemyManagerB()
{

}

HRESULT enemyManagerB::init()
{
	return S_OK;
}

HRESULT enemyManagerB::init(int xl, int yl)
{
	/// 여기 바꿔야 하고
	/// 
	/// 
	/// init, attack, tracing, ko 는 애너미별로 이미지 때문에 다시 정의해주자
	/// 
	/// 
	/// ///////

	IMAGEMANAGER->addFrameImage("e2_idle", "image/e2_idle.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("e2_walk", "image/e2_walk.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("e2_walk2", "image/e2_walk2.bmp", 948, 204, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("e2_punch", "image/e2_punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("e2_punch2", "image/e2_punch2.bmp", 948, 204, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("e2_hit", "image/e2_hit.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("e2_hit2", "image/e2_hit2.bmp", 948, 204, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("e2_ko", "image/e2_ko.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));

	img = IMAGEMANAGER->findImage("e2_idle");

	dead = false;

	/*int deadbodypop = 3;*/

	hp = 24;

	x = xl;
	y = yl;

	rc = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());
	return S_OK;
}

void enemyManagerB::release()
{

}

void enemyManagerB::update()
{

	x = (rc.left - cam + rc.right - cam) / 2;
	y = (rc.top + rc.bottom) / 2;

	/////////////////////////////////////////////////////////////////
	/////////////////////// xy 갱신 /////////////////////////////////
	/////////////////////////////////////////////////////////////////


	if (!dead) {
		tracingPlayer();
		attack();
		hitByPlayer();
		KO();
	}

}

void enemyManagerB::render()
{


	if (KEYMANAGER->isToggleKey(VK_TAB)) {
		RectangleMakeCenter(getMemDC(), x, y, img->getFrameWidth(), img->getFrameHeight());

		char str[256];
		sprintf_s(str, "중점좌표X : %f, Y : %f", x, y);
		TextOut(getMemDC(), x - 50, y + 100, str, strlen(str));

		sprintf_s(str, "camera : %d", cam);
		TextOut(getMemDC(), x - 50, y + 130, str, strlen(str));

		sprintf_s(str, "state : %d", stt);
		TextOut(getMemDC(), x - 50, y + 150, str, strlen(str));

		sprintf_s(str, "hp : %d", hp);
		TextOut(getMemDC(), x - 50, y + 170, str, strlen(str));

	}

	draw();
}

void enemyManagerB::draw()
{
	img->frameRender(getMemDC(), rc.left - cam, rc.top);


}

void enemyManagerB::tracingPlayer()
{//랜덤거리로 들어오면 추적을 시작

/// 여기 바꿔야 하고 
/// ///////
	if (getDistance(x, y, plx, ply) <= 600)
	{
		// 150 에서 추적멈춘다 ( 그러므로 이 밑이 추적)

		if (abs(x - plx) >= 80 || abs(y - ply) >= 50) {

			cnt++;

			if (cnt % 9 == 0)
			{
				stt = enemyWalk;
				img = IMAGEMANAGER->findImage("e2_walk");

				//에너미 방향따라서 걷는 모션 방향 
				if (x >= plx) img = IMAGEMANAGER->findImage("e2_walk");

				if (x < plx) img = IMAGEMANAGER->findImage("e2_walk2");

				img->setFrameX(index);
				index++;

				if (index > img->getMaxFrameX()) index = 0;

				if (x >= plx) {
					rc.left -= 5;
					rc.right -= 5;
				}

				if (x < plx) {
					rc.left += 5;
					rc.right += 5;
				}

				//if (y >= ply) {
				//	rc.top -= 14;
				//	rc.bottom -= 14;
				//}

				//if (y < ply) {
				//	rc.top += 14;
				//	rc.bottom += 14;
				//}
		// 움직임이다 이거 위 아래 둘다 위에는 좀 툭툭 아래는 부드러움
			}
			if (x >= plx) {
				rc.left -= 2;
				rc.right -= 2;
			}

			if (x < plx) {
				rc.left += 2;
				rc.right += 2;
			}

			if (y >= ply) {
				rc.top -= 1;
				rc.bottom -= 1;
			}

			if (y < ply) {
				rc.top += 1;
				rc.bottom += 1;
			}




		}
		//	else {
		//// 150 미만에 있기떄문에 몹이 움직이지 않는 구간 = 150으로 붙음
		////거리 안에는 있지만 추적을 하지 않음
		//// 아마 여기서 공격을 할것 같음
		//// 여기서 공격 가능이나 피격가능 상태를 주고 처리를 해볼까
		//	
		//	
		//	}


	}



}

void enemyManagerB::attack()
{
	/// 여기 바꿔야 하고 
	/// ///////
	if (abs(x - plx) <= 90 && abs(y - ply) <= 50) {

		cnt++;

		if (cnt % 12 == 0) {

			if (x >= plx) {
				img = IMAGEMANAGER->findImage("e2_punch");
				if (index == 2) stt = enemyAttack;

			}

			if (x < plx) {
				img = IMAGEMANAGER->findImage("e2_punch2");
				if (index == 0) stt = enemyAttack;
			}

			img->setFrameX(index);
			index++;

			if (index > img->getMaxFrameX()) index = 0;



			cnt = 0;


		}

	}


}

void enemyManagerB::hitByPlayer()
{
	/// 여기 바꿔야 하고 
	/// ///////
	if (abs(x - plx) < 95 && abs(y - ply) < 50) {

		if (playerStt == 2 || playerStt == 3 || playerStt == 8 || playerStt == 9) {

			if (x >= plx) {
				img = IMAGEMANAGER->findImage("e2_hit");
				rc.left += 5;
				rc.right += 5;
				hp -= 1;
			}
			if (x < plx) {
				img = IMAGEMANAGER->findImage("e2_hit");
				rc.left -= 5;
				rc.right -= 5;
				hp -= 1;
			}
		}

	}


}

void enemyManagerB::KO()
{
	/// 여기 바꿔야 하고 
	/// ///////
	if (hp <= 0) {

		if (x >= plx) {
			img = IMAGEMANAGER->findImage("e2_ko");


			//if (deadbodypop > 0) {
			//	rc.left += 10;
			//	rc.right += 10;
			//	deadbodypop -= 1;

			//}
			stt = enemyKO;
			dead = true;

		}
		if (x < plx) {
			img = IMAGEMANAGER->findImage("e2_ko");


			//if (deadbodypop > 0) {
			//	rc.left -= 10;
			//	rc.right -= 10;
			//	deadbodypop -= 1;

			//}
			stt = enemyKO;
			dead = true;
		}

	}

}




// //////////////////////////////////////////////////////////////////////// //
//////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////// //
// //////////////////////////////////////////////////////////////////////// //
//////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////// //



void enemyManagerB::setCam(int x)
{
	cam = x;
}
void enemyManagerB::setPlayerX(int x)
{
	plx = x;
}
void enemyManagerB::setPlayerY(int y)
{
	ply = y;
}
int enemyManagerB::showState()
{
	return stt;
}
int enemyManagerB::getX()
{
	return x;
}
int enemyManagerB::getY()
{
	return y;
}
void enemyManagerB::getPlayerstt(int x)
{
	playerStt = x;
	return;
}
// //////////////////////////////////////////////////////////////////////// //
//////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////// //