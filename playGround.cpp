#include "pch.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기에다 해라!!!
HRESULT playGround::init()
{
	gameNode::init(true);

	
	SCENEMANAGER->addScene("stage1", new stage1);
	SCENEMANAGER->addScene("stage2", new stage2);
	SCENEMANAGER->addScene("stage3", new stage3);
	SCENEMANAGER->addScene("stage4", new stage4);
	SCENEMANAGER->addScene("stage5", new stage5);
	SCENEMANAGER->addScene("title", new title);
	SCENEMANAGER->addScene("shop", new shop);
	SCENEMANAGER->addScene("ending", new ending);

	SCENEMANAGER->changeScene("title");

	IMAGEMANAGER->addImage("UI_up_hp", "image/upper_ui_hp.bmp", 1200, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_up", "image/upper_ui.bmp", 1200, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_down", "image/lower_ui.bmp", 1200, 160, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("coin", "image/coin.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("logooff2", "image/logooff2.bmp", 1200, 1000, true, RGB(255, 0, 255));

	return S_OK;
}

//메모리 해제는 여기다 해라!!!!
void playGround::release()
{
	gameNode::release();


}

//연산처리는 여기다가!
void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();
	

}

//여기다 그려줘라!!!
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============위에는 제발 건드리지 마라 ============
	

	SCENEMANAGER->render();

	// 위아래 흑백 UI


	if (KEYMANAGER->isToggleKey(VK_TAB)) {
		TIMEMANAGER->render(getMemDC());
	}

	IMAGEMANAGER->findImage("UI_down")->render(getMemDC(), 0, 840);


	//=============== 밑에도 건들지마라 ================
	_backBuffer->render(getHDC(), 0, 0);

}

