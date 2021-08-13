#include "pch.h"
#include "enemyManagerBoss.h"
#include "player.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "stage4.h"
#include "stage5.h"

enemyManagerBoss::enemyManagerBoss()
{

}

enemyManagerBoss::~enemyManagerBoss()
{

}

HRESULT enemyManagerBoss::init()
{
	return S_OK;
}

HRESULT enemyManagerBoss::init(int xl, int yl)
{
	/// 여기 바꿔야 하고
	/// 
	/// 
	/// init, attack, tracing, ko 는 애너미별로 이미지 때문에 다시 정의해주자
	/// 
	/// 
	/// ///////

	IMAGEMANAGER->addFrameImage("boss_idle", "image/boss_idle.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("boss_walk", "image/boss_walk.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_walk2", "image/boss_walk2.bmp", 948, 204, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("boss_punch", "image/boss_punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_punch2", "image/boss_punch2.bmp", 948, 204, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("boss_hit", "image/boss_hit.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_hit2", "image/boss_hit2.bmp", 948, 204, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("boss_ko", "image/boss_ko.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));

	img = IMAGEMANAGER->findImage("boss_idle");

	dead = false;

	/*int deadbodypop = 3;*/

	hp = 100;

	x = xl;
	y = yl;

	rc = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());
	return S_OK;
}

void enemyManagerBoss::release()
{

}

void enemyManagerBoss::update()
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

void enemyManagerBoss::render()
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

void enemyManagerBoss::draw()
{
	img->frameRender(getMemDC(), rc.left - cam, rc.top);


}

void enemyManagerBoss::tracingPlayer()
{//랜덤거리로 들어오면 추적을 시작

/// 여기 바꿔야 하고 
/// ///////
	if (getDistance(x, y, plx, ply) <= 800)
	{
		// 150 에서 추적멈춘다 ( 그러므로 이 밑이 추적)

		if (abs(x - plx) >= 95 || abs(y - ply) >= 50) {

			cnt++;

			if (cnt % 5 == 0)
			{
				stt = enemyWalk;
				img = IMAGEMANAGER->findImage("boss_walk");

				//에너미 방향따라서 걷는 모션 방향 
				if (x >= plx) img = IMAGEMANAGER->findImage("boss_walk");

				if (x < plx) img = IMAGEMANAGER->findImage("boss_walk2");

				img->setFrameX(index);
				index++;

				if (index > img->getMaxFrameX()) index = 0;

				if (x >= plx) {
					rc.left -= 6;
					rc.right -= 6;
				}

				if (x < plx) {
					rc.left += 6;
					rc.right += 6;
				}

				if (y >= ply) {
					rc.top -= 2;
					rc.bottom -= 2;
				}

				if (y < ply) {
					rc.top += 2;
					rc.bottom += 2;
				}

			}
/////////////////////////////////////////////////////////////////////////////////////////			
/////////////////////////////////////////////////////////////////////////////////////////
// 이동속도 위는 딱딱 밑은 물렁
/////////////////////////////////////////////////////////////////////////////////////////
			if (x >= plx) {
				rc.left -= 4;
				rc.right -= 4;
			}

			if (x < plx) {
				rc.left += 4;
				rc.right += 4;
			}

			if (y >= ply) {
				rc.top -= 2;
				rc.bottom -= 2;
			}

			if (y < ply) {
				rc.top += 2;
				rc.bottom += 2;
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

void enemyManagerBoss::attack()
{
	/// 여기 바꿔야 하고 
	/// ///////
	if (abs(x - plx) <= 100 && abs(y - ply) <= 50) {

		cnt++;

		if (cnt % 8 == 0) {

			if (x >= plx) {
				img = IMAGEMANAGER->findImage("boss_punch");
				if (index == 0) stt = enemyAttack;

			}

			if (x < plx) {
				img = IMAGEMANAGER->findImage("boss_punch2");
				if (index == 1) stt = enemyAttack;
			}

			img->setFrameX(index);
			index++;

			if (index > img->getMaxFrameX()) index = 0;



			cnt = 0;


		}

	}


}

void enemyManagerBoss::hitByPlayer()
{
	/// 여기 바꿔야 하고 
	/// ///////
	if (abs(x - plx) < 95 && abs(y - ply) < 50) {

		if (playerStt == 2 || playerStt == 3 || playerStt == 8 || playerStt == 9) {

			if (x >= plx) {
				img = IMAGEMANAGER->findImage("boss_hit");
				rc.left += 5;
				rc.right += 5;
				hp -= 1;
			}
			if (x < plx) {
				img = IMAGEMANAGER->findImage("boss_hit");
				rc.left -= 5;
				rc.right -= 5;
				hp -= 1;
			}
		}

	}


}

void enemyManagerBoss::KO()
{
	/// 여기 바꿔야 하고 
	/// ///////
	if (hp <= 0) {

		if (x >= plx) {
			img = IMAGEMANAGER->findImage("boss_ko");


			//if (deadbodypop > 0) {
			//	rc.left += 10;
			//	rc.right += 10;
			//	deadbodypop -= 1;

			//}
			stt = enemyKO;
			dead = true;

		}
		if (x < plx) {
			img = IMAGEMANAGER->findImage("boss_ko");


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



void enemyManagerBoss::setCam(int x)
{
	cam = x;
}
void enemyManagerBoss::setPlayerX(int x)
{
	plx = x;
}
void enemyManagerBoss::setPlayerY(int y)
{
	ply = y;
}
int enemyManagerBoss::showState()
{
	return stt;
}
int enemyManagerBoss::getX()
{
	return x;
}
int enemyManagerBoss::getY()
{
	return y;
}
void enemyManagerBoss::getPlayerstt(int x)
{
	playerStt = x;
	return;
}
// //////////////////////////////////////////////////////////////////////// //
//////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////// //