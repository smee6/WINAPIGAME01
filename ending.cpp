#include "pch.h"
#include "ending.h"

ending::ending()
{
}

ending::~ending()
{
}

HRESULT ending::init()
{
    mapPos = 0;

    IMAGEMANAGER->addImage("ending", "image/ending.bmp", 15000, 1000, true, RGB(255, 0, 255));


    return S_OK;
}

void ending::release()
{
}

void ending::update()
{

    cnt++;

    if (cnt % 2 == 0) {
        mapPos += 25;
    }
    if (mapPos >= 13800) {
        mapPos = 13800;

        gameOverCnt++;
        

        if (gameOverCnt == 255) {
            gameOverCnt = 255;
            SCENEMANAGER->changeScene("title");

            gameOverCnt = 0;

        }
    }

}

void ending::render()
{
    IMAGEMANAGER->findImage("ending")->render(getMemDC(), 0 - mapPos, 0);
    // img = IMAGEMANAGER->findImage("p_walk");

    IMAGEMANAGER->addFrameImage("p_walk", "image/p_walk.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));

    IMAGEMANAGER->findImage("p_walk")->frameRender(getMemDC(), WINSIZEX / 2 - 160, WINSIZEY / 2);



    cnt2++;
    if (cnt % 3 == 0) {
        IMAGEMANAGER->findImage("p_walk")->setFrameY(0);
        IMAGEMANAGER->findImage("p_walk")->setFrameX(index);
        if (mapPos < 13800) {
            index++;
        }
        if (index > IMAGEMANAGER->findImage("p_walk")->getMaxFrameX()) index = 0;
    
    }


    IMAGEMANAGER->findImage("logooff2")->alphaRender(getMemDC(), gameOverCnt);
}
