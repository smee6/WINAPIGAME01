#include "pch.h"
#include "shop.h"
#include "player.h"

shop::shop()
{
}

shop::~shop()
{
}

HRESULT shop::init()
{


	p1 = new player;
	p1->init(5000, WINSIZEY / 2 + 5000);
	IMAGEMANAGER->addImage("shop_1", "image/shop_1.bmp", 1200, 640, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shop_2", "image/shop_2.bmp", 1200, 640, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shop_3", "image/shop_3.bmp", 1200, 640, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shop_4", "image/shop_4.bmp", 1200, 640, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("eat", "image/p1_eat.bmp", 2212, 204, 7, 1, true, RGB(255, 0, 255));


	eat = IMAGEMANAGER->findImage("eat");

	shopNum = 1;


	p1->setHP(SCENEMANAGER->hp);

	return S_OK;
}

void shop::release()
{
}

void shop::update()
{
	
	SCENEMANAGER->hp = p1->getHP();

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && shopNum < 4) {
		shopNum += 1;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP) && shopNum > 1) {
		shopNum -= 1;
	}

	switch (shopNum)
	{
	case 1:
		if (KEYMANAGER->isOnceKeyDown('A')) { 
			eatmotion = true;
			SCENEMANAGER->hp = p1->getHP() + 30;
		p1->setHP(SCENEMANAGER->hp);
		}
	case 2:
		if (KEYMANAGER->isOnceKeyDown('A')) {
			eatmotion = true;
			SCENEMANAGER->hp = p1->getHP() + 20;
			p1->setHP(SCENEMANAGER->hp);
		}
	case 3:
		if (KEYMANAGER->isOnceKeyDown('A')) {
			eatmotion = true;
			SCENEMANAGER->hp = p1->getHP() + 10;
			p1->setHP(SCENEMANAGER->hp);
		}
	case 4:
		if (KEYMANAGER->isOnceKeyDown('A')) {
			SCENEMANAGER->setMapNumber(10);
			//»óÁ¡¿¡¼­ ³ª°¥¶© ¸Ê³Ñ¹ö 10
			SCENEMANAGER->changeScene("stage3");
		}
	}

	if (eatmotion) {
		cnt++;
		if (cnt % 7 == 0) {
			index++;
			eat->setFrameX(index);
			if (index == 6) {
				index = 0;
				eatmotion = false;
			}
		
		}


	}


}

void shop::render()
{
	if( shopNum == 1) IMAGEMANAGER->findImage("shop_1")->render(getMemDC(), 0, 200);
	if (shopNum == 2) IMAGEMANAGER->findImage("shop_2")->render(getMemDC(), 0, 200);
	if (shopNum == 3) IMAGEMANAGER->findImage("shop_3")->render(getMemDC(), 0, 200);
	if (shopNum == 4) IMAGEMANAGER->findImage("shop_4")->render(getMemDC(), 0, 200);
	eat->frameRender(getMemDC(), 130, 350);
	p1->render();


}
