#include "pch.h"
#include "stage2.h"
#include "player.h"
#include "enemyManager.h"


stage2::stage2()
{
}

stage2::~stage2()
{
}

HRESULT stage2::init()
{
	IMAGEMANAGER->addImage("map2", "image/map2.bmp", 3500, 640, true, RGB(255, 0, 255));


	p1 = new player;
	p1->init(200, WINSIZEY / 2 + 100);
	if (SCENEMANAGER->getMapNumber() == 3) {
		p1->init(900, WINSIZEY / 2 + 100);
		p1->setCameraXpos(1640);
		SCENEMANAGER->setMapNumber(2);
	}


	e1 = new enemyManagerB;
	e1->init(900, WINSIZEY / 2 + 100);

	e2 = new enemyManagerB;
	e2->init(1900, WINSIZEY / 2 + 150);

	e3 = new enemyManager;
	e3->init(3200, WINSIZEY / 2 + 70);

	e4 = new enemyManagerC;
	e4->init(1700, WINSIZEY / 2 + 50);

	p1->setHP(SCENEMANAGER->hp);

	return S_OK;
}

void stage2::release()
{
}

void stage2::update()
{
	SCENEMANAGER->hp = p1->getHP();
	p1->update();
	if (p1->isRunF() == 1) {
		p1->update();
	}
	else if (p1->isRunF() == 0) {

	}
	mapBlock();
	//ÇÃ·¹ÀÌ¾î ÇÇ°Ý
	p1->amIhit(e1->showState());
	p1->amIhit(e2->showState());
	p1->amIhit(e3->showState());
	p1->amIhit(e4->showState());
	if (e1->showState() == 2) {
		p1->getEnemyX(e1->getX());
	}
	if (e2->showState() == 2) {
		p1->getEnemyX(e2->getX());
	}
	if (e3->showState() == 2) {
		p1->getEnemyX(e3->getX());
	}
	if (e4->showState() == 2) {
		p1->getEnemyX(e4->getX());
	}
	//

	e1->update();
	e1->setCam(p1->cameraXpos);
	e1->setPlayerX(p1->showXY(1));
	e1->setPlayerY(p1->showXY(2));
	e1->getPlayerstt(p1->showState());


	e2->update();
	e2->setCam(p1->cameraXpos);
	e2->setPlayerX(p1->showXY(1));
	e2->setPlayerY(p1->showXY(2));
	e2->getPlayerstt(p1->showState());


	e3->update();
	e3->setCam(p1->cameraXpos);
	e3->setPlayerX(p1->showXY(1));
	e3->setPlayerY(p1->showXY(2));
	e3->getPlayerstt(p1->showState());

	e4->update();
	e4->setCam(p1->cameraXpos);
	e4->setPlayerX(p1->showXY(1));
	e4->setPlayerY(p1->showXY(2));
	e4->getPlayerstt(p1->showState());


	sceneChange();
}

void stage2::render()
{
	IMAGEMANAGER->findImage("map2")->render(getMemDC(), 0 - p1->cameraXpos, 200);



	if (p1->showXY(2) >= e1->getY()) e1->render();
	if (p1->showXY(2) >= e4->getY()) e4->render();
	if (p1->showXY(2) >= e3->getY()) e3->render();
	if (p1->showXY(2) >= e2->getY()) e2->render();

	p1->render();

	if (p1->showXY(2) < e1->getY()) e1->render();
	if (p1->showXY(2) < e4->getY()) e4->render();
	if (p1->showXY(2) < e3->getY()) e3->render();
	if (p1->showXY(2) < e2->getY()) e2->render();



}

void stage2::sceneChange()
{
	if (p1->cameraXpos >= 1650) {
		p1->setCameraReset();
		SCENEMANAGER->setMapNumber(3);
		SCENEMANAGER->changeScene("stage3");
	}

	if (p1->cameraXpos <= -1 && p1->showXY(1)<=WINSIZEX/2) {
		p1->setCameraReset();
		SCENEMANAGER->changeScene("stage1");
	}
}


void stage2::mapBlock()
{
	if (p1->showXY(2) <= 510) {
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

