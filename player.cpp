#include "pch.h"
#include "player.h"

player::player()
{
}

player::~player()
{
}

HRESULT player::init(int xl, int yl)
{
	IMAGEMANAGER->addFrameImage("p_idle", "image/p_idle.bmp", 316, 408, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("p_jump", "image/p_jump.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("p_walk", "image/p_walk.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("p_run", "image/p_run.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("p_KO", "image/p_KO.bmp", 632, 408, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("p_punch", "image/p_punch.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("p_kick", "image/p_kick.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("p_hit", "image/p_hit.bmp", 948, 408, 3, 2, true, RGB(255, 0, 255));


	img = IMAGEMANAGER->findImage("p_idle");

	hp = 230;

	x = xl;
	y = yl;

	isDead = false;

	rc = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());


    return S_OK;
}

void player::release()
{
}

void player::update()
{
	if (!isDead) {
		keyControl();
		move();
		KO();
		camera();
	}
	




}

void player::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) {
	RectangleMakeCenter(getMemDC(), x, y, img->getFrameWidth(), img->getFrameHeight());
	char str[256];
	sprintf_s(str, "중점좌표X : %f, Y : %f", x, y);
	TextOut(getMemDC(), x-50, y+100, str, strlen(str));

	sprintf_s(str, "camera : %d", cameraXpos);
	TextOut(getMemDC(), x - 50, y + 130, str, strlen(str));

	sprintf_s(str, "state : %d", stt);
	TextOut(getMemDC(), x - 50, y + 150, str, strlen(str));

	sprintf_s(str, "hp : %d", hp);
	TextOut(getMemDC(), x - 50, y + 170, str, strlen(str));
	}

	draw();

	// hp바는 플레이어가 가지고 있자
	IMAGEMANAGER->findImage("UI_up_hp")->render(getMemDC(), hp-253, 0);

	IMAGEMANAGER->findImage("UI_up")->render(getMemDC(), 0, 0);


	gameOver();
	

}

void player::draw()
{
	img->frameRender(getMemDC(), rc.left, rc.top);
}


///////////////////////////////////////////////////////////////////////////////////////////
// 키 /////////////// 컨트롤 ///////////////////////////////////////////////////////////////
void player::keyControl()
{
	x = (rc.left + rc.right)/2;
	y = (rc.top + rc.bottom)/2;


	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		speed = playerSpeed;
		img = IMAGEMANAGER->findImage("p_walk");
		stt = right_walk;
		rc.left += speed;
		rc.right += speed;
		
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		
		stt = right_idle;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		speed = playerSpeed;
		img = IMAGEMANAGER->findImage("p_walk");
		stt = left_walk;
		rc.left -= speed;
		rc.right -= speed;

		
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		
		stt = left_idle;
	}

	/// < 대쉬인데 일단 임시임 >
	/// ////////////////////////////////////////////////
	// 대쉬 일단 봉인 나중에 시간 남으면 만지기 (카메라 좀 만져야해서)
	if (KEYMANAGER->isStayKeyDown('Q'))
	{
		isRun = true;

	}
	if (KEYMANAGER->isOnceKeyUp('Q'))
	{
		isRun = false;
	}




	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (cantGoUp) return;
		if (stt == right_idle) stt = right_walk;
		if (stt == left_idle) stt = left_walk; 

		rc.top -= speed;
		rc.bottom -= speed;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		if (stt == right_walk) stt = right_idle;
		if (stt == left_walk) stt = left_idle;

	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (cantGoDown) return;
		if (stt == right_idle) stt = right_walk;
		if (stt == left_idle) stt = left_walk;

		rc.top += speed;
		rc.bottom += speed;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (stt == right_walk) stt = right_idle;
		if (stt == left_walk) stt = left_idle;

	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (stt == right_idle || stt == right_walk) stt = right_punch;
		if (stt == left_idle || stt == left_walk) stt = left_punch;

	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		if (stt == right_punch) stt = right_idle;
		if (stt == left_punch) stt = left_idle; 

	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		if (stt == right_idle || stt == right_walk) stt = right_kick;
		if (stt == left_idle || stt == left_walk) stt = left_kick;

	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		if (stt == right_kick) stt = right_idle;
		if (stt == left_kick) stt = left_idle;

	}

	//if (KEYMANAGER->isOnceKeyDown('D'))
	//{
	//	if (stt == right_idle || stt == right_walk) stt = right_jump;
	//	if (stt == left_idle || stt == left_walk) stt = left_jump;

	//}
	//if (KEYMANAGER->isOnceKeyUp('D'))
	//{
	//	if (stt == right_jump) stt = right_idle;
	//	if (stt == left_jump) stt = left_idle;
	//}




}

void player::move()
{

	cnt++;
	
	if (cnt % 4 == 0) 
	{

		switch (stt)
		{
		case state::right_idle:

			img = IMAGEMANAGER->findImage("p_idle");
			img->setFrameY(0);
			img->setFrameX(index);
			index++;

			if (index >= img->getMaxFrameX()) index = 0;
			break;

		case state::right_walk:
			
			// img = IMAGEMANAGER->findImage("p_walk");
			img->setFrameY(0);
			img->setFrameX(index);
			index++;

			if (index > img->getMaxFrameX()) index = 0;
			break;

		case state::right_punch:
			
			img = IMAGEMANAGER->findImage("p_punch");
			img->setFrameY(0);
			img->setFrameX(index);
			index++;

			if (index > img->getMaxFrameX()) index = 0;
			break;

		case state::right_kick:
			img = IMAGEMANAGER->findImage("p_kick");
			img->setFrameY(0);
			img->setFrameX(index);
			index++;

			if (index > img->getMaxFrameX()) index = 0;
			break;

		case state::right_jump:
			img = IMAGEMANAGER->findImage("p_jump");
			img->setFrameY(0);
			img->setFrameX(index);
			index=0;
			if (index >= img->getMaxFrameX()) index = 0;
			break;

		case state::right_jumpattck:
			
			img->setFrameY(0);
			img->setFrameX(index);
			index++;

			if (index >= img->getMaxFrameX()) index = 0;
			break;

		case state::left_idle:
			
			img = IMAGEMANAGER->findImage("p_idle");
			img->setFrameY(1);
			img->setFrameX(index);
			index--;

			if (index <= 0) index = img->getMaxFrameX();
			break;

		case state::left_walk:
			
			
			// img = IMAGEMANAGER->findImage("p_walk");
			img->setFrameY(1);
			img->setFrameX(index);
			index--;

			if (index < 0) index = img->getMaxFrameX();
			break;

		case state::left_punch:
			
			
			img = IMAGEMANAGER->findImage("p_punch");
			img->setFrameY(1);
			img->setFrameX(index);
			index--;

			if (index < 0) index = img->getMaxFrameX();
			break;

		case state::left_kick:
			img = IMAGEMANAGER->findImage("p_kick");
			img->setFrameY(1);
			img->setFrameX(index);
			index--;

			if (index < 0) index = img->getMaxFrameX();
			break;

		case state::left_jump:
			img = IMAGEMANAGER->findImage("p_jump");
			img->setFrameY(1);
			img->setFrameX(index);
			index=2;

			if (index <= 0) index = img->getMaxFrameX();
			break;

		case state::left_jumpattck:
			
			img->setFrameY(1);
			img->setFrameX(index);
			index--;

			if (index <= 0) index = img->getMaxFrameX();
			break;
		case state::hitted:
			img = IMAGEMANAGER->findImage("p_hit");
			img->setFrameY(0);
			img->setFrameX(index);
			index++;

			if (index >= img->getMaxFrameX()) index = 0;
			break;


		}
		cnt = 0;
	}



}


/// 누구한테든 일단 맞으면 뒤로 밀림
/// 밀리고 피까임 hp뒤에다가 애너미 데미지 같은거 추가해주면 될것같음 (안해도 될듯) (보스만)

void player::hit()
{
	img = IMAGEMANAGER->findImage("p_hit");

	img->setFrameX(1);

	if (enemyX >= x) {

		rc.left -= 3;
		rc.right -= 3;
		hp -= 0.5;
		stt = right_idle;
	}
	if (enemyX < x) {
		rc.left += 3;
		rc.right += 3;
		stt = left_idle;
		hp -= 0.5;
	}
}


// x로 애너미의 공격상태를 받아왔음.  amihit 이 애너미 상태 읽어오는거임 사실
void player::amIhit(int x)
{
	if (x == 2 && !isDead) {
		stt = hitted;
		hit();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////


//죽음
void player::KO()
{


	if (hp <= 0) {
		img = IMAGEMANAGER->findImage("p_KO");
		isDead = true;

	}

}












void player::getEnemyX(int x)
{
	enemyX = x;
}

int player::getHP()
{
	return hp;
}

void player::setHP(int x)
{
	hp = x;
}

int player::isRunF()
{
	if (!isRun) { return 0; }
	if (isRun) { return 1; }

}

void player::setCameraReset()
{
	cameraXpos = 0;

	return ;
}

void player::setCameraXpos(int x)
{
	cameraXpos = x;
}

// 이거 내가 게임오버 당하는거

void player::gameOver()
{
	if (isDead) {

		gameOverCnt++;
		IMAGEMANAGER->findImage("logooff2")->alphaRender(getMemDC(), gameOverCnt);

		if (gameOverCnt == 255) {
			gameOverCnt = 255;
			SCENEMANAGER->changeScene("title");
			isDead = false;
			gameOverCnt = 0;
		
		}

	
	
	}
















}








/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 카메라 ///////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////


void player::camera() {
	// && stt != right_idle && stt != left_idle
	if (rc.right >= WINSIZEX ) {
		
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isOnceKeyDown('Q')) {
			speed = playerSpeed;
			cameraXpos -= playerSpeed;

		}

		if (stt != right_walk) return;

		rc.right = WINSIZEX;
		rc.left = WINSIZEX - img->getFrameWidth();
		speed = 0;
		cameraXpos += playerSpeed;


		if (KEYMANAGER->isStayKeyDown(VK_UP) || KEYMANAGER->isStayKeyDown(VK_DOWN)) {
			cameraXpos -= playerSpeed;
			speed = playerSpeed;
		}


	}
	// && stt != left_idle && stt != right_idle
	if (rc.left <= 0 ) {

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) || KEYMANAGER->isOnceKeyDown('E')) {
			speed = playerSpeed;
			cameraXpos += playerSpeed;
		}
		if (stt != left_walk) return;

		rc.right = img->getFrameWidth();;
		rc.left = 0;

		speed = 0;
		cameraXpos -= playerSpeed;

		if (KEYMANAGER->isStayKeyDown(VK_UP) || KEYMANAGER->isStayKeyDown(VK_DOWN)) {
			cameraXpos += playerSpeed;
			speed = playerSpeed;
		}

	}


}





//// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////혹시 필요시 사용 :: 남 주는곳////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////


int player::showState()
{
	return stt;
}
int player::showRC(int x) // 1234로 받아올거고 레프트 탑 라이트 바텀 순

{
	int sol = 0;
	if (x == 1) { sol = rc.left; }
	if (x == 2) { sol = rc.top; }
	if (x == 3) { sol = rc.right; }
	if (x == 4) { sol = rc.bottom; }


	return sol;
}



int player::showXY(int c) // 1,2 로 받고 x는 1 y는 2

{
	int sol = 0;
	if (c == 1) { sol = x; }
	if (c == 2) { sol = y; }
	return sol;
}

//int player::getSpd() {
//
//	return speed;
//}
//
//void player::setSpd(int x) {
//
//	speed = x;
//}
///////////////////////////////////////////////////////////////////////////////////////////