#include "pch.h"
#include "stage5.h"
#include "player.h"
#include "enemyManagerBoss.h"


stage5::stage5()
{
}

stage5::~stage5()
{
}

HRESULT stage5::init()
{
	p1 = new player;
	p1->init(200, WINSIZEY / 2 + 70);

	IMAGEMANAGER->addImage("map5", "image/map5.bmp", 3036, 640, true, RGB(255, 0, 255));


	
	e3 = new enemyManagerBoss;
	e3->init(2800, WINSIZEY / 2 + 70);


	 p1->setHP(SCENEMANAGER->hp);


	return S_OK;
}

void stage5::release()
{
}

void stage5::update()
{
	SCENEMANAGER->hp = p1->getHP();
	p1->update();
	if (p1->isRunF() == 1) {
		p1->update();
	}
	else if (p1->isRunF() == 0) {

	}
	mapBlock();

	p1->amIhit(e3->showState());
	if (e3->showState() == 2) {
		p1->getEnemyX(e3->getX());
	}



	e3->update();
	e3->setCam(p1->cameraXpos);
	e3->setPlayerX(p1->showXY(1));
	e3->setPlayerY(p1->showXY(2));
	e3->getPlayerstt(p1->showState());




	sceneChange();
}

void stage5::render()
{
	IMAGEMANAGER->findImage("map5")->render(getMemDC(), 0 - p1->cameraXpos, 200);

	p1->render();


	if (p1->showXY(2) >= e3->getY()) { e3->render(); p1->render(); }
	else if (p1->showXY(2) < e3->getY()) { p1->render(); e3->render(); }


	// // 
	// 	   // //
	// 	   // // // 
	// 	   // // // // 
	// 
	// º¸½º Á×À¸¸é ¾À ¿Ã¶ó°¡´Â°Í //
	// // // // 
	// // //

	if (e3->showState() == 4) {
		gameOverCnt++;
		IMAGEMANAGER->findImage("logooff2")->alphaRender(getMemDC(), gameOverCnt);
		if (gameOverCnt >= 255) {
			gameOverCnt = 255;
			if (cnt % 3000 == 0) {
				SCENEMANAGER->changeScene("ending");
			}
		}

		
	}

	// //
	// // // //// //// //

}


void stage5::sceneChange()
{
	if (p1->cameraXpos <= -1 && p1->showXY(1) <= WINSIZEX / 2) {
		p1->setCameraReset();
		SCENEMANAGER->changeScene("stage4");
	}
	if (p1->cameraXpos >= 1500) {
		p1->setCameraXpos(1500);
	}
}

void stage5::mapBlock()
{
	if (p1->showXY(2) <= 520) {
		// ¹ØÀ¸·Î °¡¶ó°í ½÷ÁÜ 
		p1->cantGoUp = true;
	}
	else {
		p1->cantGoUp = false;
	}
	if (p1->showXY(2) >= 730) {
		//À§·Î °¡¶ó°í ½÷ÁÜ
		p1->cantGoDown = true;
	}
	else {
		p1->cantGoDown = false;
	}
}
