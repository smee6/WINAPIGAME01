#include "pch.h"
#include "title.h"

title::title()
{
}

title::~title()
{
}

HRESULT title::init()
{
	SCENEMANAGER->mapchangecnt = 0;
	SCENEMANAGER->setMapNumber(0);
	IMAGEMANAGER->addImage("logo", "image/logo.bmp", 1200, 1000, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("logooff", "image/logooff.bmp", 1200, 1000, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("title", "image/title.bmp", 1200, 1000, true, RGB(255, 0, 255));
	

	titleshow = 0;
	logoshow = 0;

	return S_OK;
}

void title::release()
{
}

void title::update()
{
	if (!logoOn) {
		cnt++;
		if (cnt % 2 == 0) {

			logoshow++;

		}
		if (logoshow >= 254 || KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
			logoOn = true;
			
		}

	}
	if (logoOn && !titleOn) {
		logoshow = 255;
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
			titleOn = true;
		}
	}
	if (titleOn) {
		logoshow--;
		if (logoshow <= 150 || KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
			logoshow = 0;
			titleshow++;
		}
	}
	if (titleshow >= 150) {
		titleshow = 255;
	}
	if (titleshow == 255) {
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
			SCENEMANAGER->changeScene("stage1");

		}
	}

}

void title::render()
{
	IMAGEMANAGER->findImage("logooff")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("logo")->alphaRender(getMemDC(), logoshow);
	IMAGEMANAGER->findImage("title")->alphaRender(getMemDC(), titleshow);


}
