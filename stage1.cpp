#include "pch.h"
#include "stage1.h"
#include "player.h"
#include "enemyManager.h"




stage1::stage1()
{
}

stage1::~stage1()
{
}

HRESULT stage1::init()
{

	IMAGEMANAGER->addImage("map1", "image/map1.bmp", 4500, 640, true, RGB(255, 0, 255));

	p1 = new player;
	

	p1->init(300 , WINSIZEY / 2+50);
	if (SCENEMANAGER->getMapNumber() == 2) {
		p1->init(900, WINSIZEY / 2 + 100);
		p1->setCameraXpos(3150);
		SCENEMANAGER->setMapNumber(1);
	}

	/// <¹èÄ¡>
	/// /

	e1 = new enemyManager;
	e1->init(1250, WINSIZEY / 2 + 100);

	e2 = new enemyManager;
	e2->init(1500, WINSIZEY / 2 + 150);

	e3 = new enemyManagerB;
	e3->init(1700, WINSIZEY / 2 + 70);

	e4 = new enemyManager;
	e4->init(3000, WINSIZEY / 2 + 50);

	e5 = new enemyManager;
	e5->init(3700, WINSIZEY / 2 + 200);

	if (SCENEMANAGER->mapchangecnt >= 1) {
		p1->setHP(SCENEMANAGER->hp);
	}

	return S_OK;
}

void stage1::release()
{
}

void stage1::update()
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
	p1->amIhit(e5->showState());

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
	if (e5->showState() == 2) {
		p1->getEnemyX(e5->getX());
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

	e5->update();
	e5->setCam(p1->cameraXpos);
	e5->setPlayerX(p1->showXY(1));
	e5->setPlayerY(p1->showXY(2));
	e5->getPlayerstt(p1->showState());
	sceneChange();
}

void stage1::render()
{	
	IMAGEMANAGER->findImage("map1")->render(getMemDC(),0- p1->cameraXpos,200);




	if (p1->showXY(2) >= e1->getY()) e1->render();
	if (p1->showXY(2) >= e4->getY()) e4->render();
	if (p1->showXY(2) >= e3->getY()) e3->render();
	if (p1->showXY(2) >= e5->getY()) e5->render();
	if (p1->showXY(2) >= e2->getY()) e2->render();

	p1->render();

	if (p1->showXY(2) < e1->getY()) e1->render();
	if (p1->showXY(2) < e4->getY()) e4->render();
	if (p1->showXY(2) < e3->getY()) e3->render();
	if (p1->showXY(2) < e5->getY()) e5->render();
	if (p1->showXY(2) < e2->getY()) e2->render();

}

void stage1::sceneChange()
{
	if (p1->cameraXpos < -1) {
		p1->setCameraXpos(0);
	}

	if (p1->cameraXpos >= 3200) {
		p1->setCameraReset();

		SCENEMANAGER->changeScene("stage2");
		SCENEMANAGER->setMapNumber(2);
		SCENEMANAGER->mapchangecnt++;
	}
	
}

void stage1::mapBlock()
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
	} else {
	p1->cantGoDown = false;
	}

}


