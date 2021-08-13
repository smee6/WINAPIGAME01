﻿#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>

using namespace std;

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "timeManager.h"
#include "sceneManager.h"
#include "utils.h"
#include "txtData.h"

using namespace TN_UTILS;

//========================================
// ## 윈도우 설정 디파인문 ## 2021.05.26 ##
//========================================

#define WINNAME		(LPTSTR)TEXT("열혈물어")			//윈도우 이름
#define WINSTARTX	50						//윈도우 시작좌표(left)
#define WINSTARTY	50							//윈도우 시작좌표(top)
#define WINSIZEX	1200								//윈도우 가로크기
#define WINSIZEY	1000								//윈도우 세로크기
// 1200 * 1000 최적화
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define TXTDATA txtData::getSingleton()


#define SAFE_DELETE(p) {if(p) {delete(p); (p) = nullptr;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p) = nullptr;}}

//===========================
// ## extern ## 21.05.28 ##
//===========================

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;