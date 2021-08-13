#include "pch.h"
#include "stage3.h"
#include "player.h"


stage3::stage3()
{
}

stage3::~stage3()
{
}

HRESULT stage3::init()
{
	p1 = new player;
	p1->init(200, WINSIZEY / 2 + 70);

	if (SCENEMANAGER->getMapNumber() == 4) {
		p1->init(900, WINSIZEY / 2 + 100);
		p1->setCameraXpos(850);
		SCENEMANAGER->setMapNumber(3);
	}
	if (SCENEMANAGER->getMapNumber() == 10) {
		p1->init(350, WINSIZEY / 2 + 100);
		p1->setCameraXpos(650);
		SCENEMANAGER->setMapNumber(3);
	}
	IMAGEMANAGER->addImage("map3", "image/map3.bmp", 2600, 640, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("door", "image/door.bmp", 768, 160, 4, 1, true, RGB(255, 0, 255));
	p1->setHP(SCENEMANAGER->hp);

	door = IMAGEMANAGER->findImage("door");

	return S_OK;
}

void stage3::release()
{
}

void stage3::update()
{
	SCENEMANAGER->hp = p1->getHP();
	p1->update();


	mapBlock();


	rc = RectMake(830 - p1->cameraXpos, 430, 192, 160);

	if (getDistance((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2, p1->showXY(1), p1->showXY(2)) <= 20) {
		doorOpen = true;

	}
	else { doorOpen = false; }

	if (doorOpen) {
		door->setFrameX(index);
		index++;
	}
	if (!doorOpen) {
		if (index <= 0) index = 0;
		door->setFrameX(index);
		index--;

	}
	if (doorOpen && KEYMANAGER->isStayKeyDown(VK_UP)) {
		SCENEMANAGER->changeScene("shop");
	
	}


	sceneChange();
}

void stage3::render()
{
	IMAGEMANAGER->findImage("map3")->render(getMemDC(), 0 - p1->cameraXpos, 200);

	

	door->frameRender(getMemDC(), 830 - p1->cameraXpos, 430);
	p1->render();
	if (KEYMANAGER->isToggleKey(VK_TAB)) {
		RectangleMakeCenter(getMemDC(), (rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2, 192, 160);
	}

}

void stage3::sceneChange()
{

	if (p1->cameraXpos >= 900) {
		p1->setCameraReset();
		SCENEMANAGER->changeScene("stage4");
		SCENEMANAGER->setMapNumber(4);
	}

	if (p1->cameraXpos <= -1 && p1->showXY(1) <= WINSIZEX / 2) {
		p1->setCameraReset();
		SCENEMANAGER->changeScene("stage2");
	}

	


}

void stage3::mapBlock()
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


