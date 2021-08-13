#pragma once
#include <vector>

class animation
{
public:
	//������ ����Ʈ
	typedef vector<POINT> _vFrameList;

	//�������Ʈ
	typedef vector<int> _vPlayList;

private:
	int					_frameNum;			//������ ����

	_vFrameList			_frameList;		
	_vPlayList			_playList;

	int					_frameWidth;		//������ ����ũ��
	int					_frameHeight;		//������ ����ũ��

	BOOL				_loop;				//�ִϸ��̼� ���� ����

	float				_frameUpdateSec;	//������ ������Ʈ
	float				_elapsedSec;		

	DWORD				_nowPlayIdx;
	BOOL				_play;
public:
	animation();
	~animation();

	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release();

	//����Ʈ �ִϸ��̼� ���
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);

	//�迭�� ��Ƽ� �ִϸ��̼� ���
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);

	//���� �ִϸ��̼� ���
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);

	void setFPS(int framePerSec);

	void frameUpdate(float elapsedTime);

	void start();
	void stop();
	void pause();
	void resume();


	inline BOOL isPlay() { return _play; }

	inline POINT getFramePos() { return _frameList[_playList[_nowPlayIdx]]; }

	inline int getFrameWidth()	{ return _frameWidth; }
	inline int getFrameHeight() { return _frameHeight; }
};

