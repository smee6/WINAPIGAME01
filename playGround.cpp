#include "pch.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ���⿡�� �ض�!!!
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

//�޸� ������ ����� �ض�!!!!
void playGround::release()
{
	gameNode::release();


}

//����ó���� ����ٰ�!
void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();
	

}

//����� �׷����!!!
void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============������ ���� �ǵ帮�� ���� ============
	

	SCENEMANAGER->render();

	// ���Ʒ� ��� UI


	if (KEYMANAGER->isToggleKey(VK_TAB)) {
		TIMEMANAGER->render(getMemDC());
	}

	IMAGEMANAGER->findImage("UI_down")->render(getMemDC(), 0, 840);


	//=============== �ؿ��� �ǵ������� ================
	_backBuffer->render(getHDC(), 0, 0);

}

