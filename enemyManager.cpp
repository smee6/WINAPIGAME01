#include "pch.h"
#include "enemyManager.h"
#include "player.h"
#include "stage1.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "stage4.h"

enemyManager::enemyManager()
{

}

enemyManager::~enemyManager()
{

}

HRESULT enemyManager::init()
{
	return S_OK;
}

HRESULT enemyManager::init(int xl, int yl)
{
	/// ���� �ٲ�� �ϰ�
	/// 
	/// 
	/// init, attack, tracing, ko �� �ֳʹ̺��� �̹��� ������ �ٽ� ����������
	/// 
	/// 
	/// ///////

	IMAGEMANAGER->addFrameImage("e1_idle", "image/e1_idle.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("e1_walk", "image/e1_walk.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("e1_walk2", "image/e1_walk2.bmp", 948, 204, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("e1_punch", "image/e1_punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("e1_punch2", "image/e1_punch2.bmp", 948, 204, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("e1_hit", "image/e1_hit.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("e1_hit2", "image/e1_hit2.bmp", 948, 204, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("e1_ko", "image/e1_ko.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));

	img = IMAGEMANAGER->findImage("e1_idle");

	dead = false;

	/*int deadbodypop = 3;*/

	hp = 15;

	x = xl;
	y = yl;

	rc = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());
	return S_OK;
}

void enemyManager::release()
{

}

void enemyManager::update()
{

	x = (rc.left -cam + rc.right - cam) / 2;
	y = (rc.top + rc.bottom) / 2;

	/////////////////////////////////////////////////////////////////
	/////////////////////// xy ���� /////////////////////////////////
	/////////////////////////////////////////////////////////////////


	if (!dead) {
		tracingPlayer();
		attack();
		hitByPlayer();
		KO();
	}
	if (dead) {
		
	}
}

void enemyManager::render()
{


	if (KEYMANAGER->isToggleKey(VK_TAB)) {
		RectangleMakeCenter(getMemDC(), x, y, img->getFrameWidth(), img->getFrameHeight());

		char str[256];
		sprintf_s(str, "������ǥX : %f, Y : %f", x, y);
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

void enemyManager::draw()
{
img->frameRender(getMemDC(), rc.left - cam, rc.top); 
	


	

}

void enemyManager::tracingPlayer()
{//�����Ÿ��� ������ ������ ����

/// ���� �ٲ�� �ϰ� 
/// ///////
	if (getDistance(x,y,plx,ply)<= 800)
	{
		// 150 ���� ��������� ( �׷��Ƿ� �� ���� ����)

		if (abs(x - plx) >= 80 || abs(y-ply) >= 50) {
			
			cnt++;

			if (cnt % 8 == 0)
			{
				stt = enemyWalk;
				img = IMAGEMANAGER->findImage("e1_walk");

				//���ʹ� ������� �ȴ� ��� ���� 
				if(x >= plx) img = IMAGEMANAGER->findImage("e1_walk");

				if (x < plx) img = IMAGEMANAGER->findImage("e1_walk2");

				img->setFrameX(index);
				index++;

				if (index > img->getMaxFrameX()) index = 0;

				//if (x >= plx) {
				//	rc.left -= 14;
				//	rc.right -= 14;
				//}

				//if (x < plx) {
				//	rc.left += 14;
				//	rc.right += 14;
				//}

				//if (y >= ply) {
				//	rc.top -= 4;
				//	rc.bottom -= 4;
				//}

				//if (y < ply) {
				//	rc.top += 4;
				//	rc.bottom += 4;
				//}
// �������̴� �̰� �� �Ʒ� �Ѵ� ������ �� ���� �Ʒ��� �ε巯��
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
	//// 150 �̸��� �ֱ⋚���� ���� �������� �ʴ� ���� = 150���� ����
	////�Ÿ� �ȿ��� ������ ������ ���� ����
	//// �Ƹ� ���⼭ ������ �Ұ� ����
	//// ���⼭ ���� �����̳� �ǰݰ��� ���¸� �ְ� ó���� �غ���
	//	
	//	
	//	}


		}



}

void enemyManager::attack()
{
/// ���� �ٲ�� �ϰ� 
/// ///////
	if (abs(x - plx) <= 90 && abs(y -ply) <= 50 ) {
	
			cnt++;

			if (cnt % 12 == 0) {
				
				if (x >= plx) { 
					img = IMAGEMANAGER->findImage("e1_punch"); 
					if (index == 2) stt = enemyAttack;
					
				}

				if (x < plx) { 
					img = IMAGEMANAGER->findImage("e1_punch2"); 
					if (index == 0) stt = enemyAttack;
				}

				img->setFrameX(index);
				index++;
				
				if (index > img->getMaxFrameX()) index = 0;
				
				
				
				cnt = 0;
	

			}
	
	}
	

}

void enemyManager::hitByPlayer()
{
/// ���� �ٲ�� �ϰ� 
/// ///////
	if (abs(x - plx) < 95 && abs(y - ply) < 50) {
	
		if (playerStt == 2 || playerStt == 3 || playerStt == 8 || playerStt == 9) {
		
			if (x >= plx) {
				img = IMAGEMANAGER->findImage("e1_hit");
				rc.left += 5;
				rc.right += 5;
				hp -= 1;
			}
			if (x < plx) {
				img = IMAGEMANAGER->findImage("e1_hit");
				rc.left -= 5;
				rc.right -= 5;
				hp -= 1;
			}
		}
	
	}


}

void enemyManager::KO()
{
/// ���� �ٲ�� �ϰ� 
/// ///////
	if (hp <= 0) {

		if (x >= plx) {
			img = IMAGEMANAGER->findImage("e1_ko");


			//if (deadbodypop > 0) {
			//	rc.left += 10;
			//	rc.right += 10;
			//	deadbodypop -= 1;

			//}
			stt = enemyKO;
			dead = true;

		}
		if (x < plx) {
			img = IMAGEMANAGER->findImage("e1_ko");


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
// ///////////////////////////////////////////////////////////////////////// ///
// /////////////////////////////////////////////////////////////////////// //
// //////////////////////////////////////////////////////////////////////// //
// //////////////////////////////////////////////////////////////////////// ////
// /////////////////////////////////////////////////////////////////////// //



void enemyManager::setCam(int x)
{
	cam = x;
}
void enemyManager::setPlayerX(int x)
{
	plx = x;
}
void enemyManager::setPlayerY(int y)
{
	ply = y;
}
int enemyManager::showState()
{
	return stt;
}
int enemyManager::getX()
{
	return x;
}
int enemyManager::getY()
{
	return y;
}
void enemyManager::getPlayerstt(int x)
{
	playerStt = x;
	return ;
}
// //////////////////////////////////////////////////////////////////////// //
//////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////// //