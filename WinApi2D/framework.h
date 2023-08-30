// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#pragma comment(lib, "Msimg32.lib")

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <math.h>
#include <assert.h>

// STL
#include <vector>
#include <map>
#include <list>

using namespace std;

// Util
#include "SingleTon.h"
#include "struct.h"
#include "Logger.h"

//========================================
//## 게임 그룹						##
//========================================

enum class GROUP_GAMEOBJ
{
	DEFAULT,
	BACK_GROUND,
	MAP,
	TILE,
	ENEMY,
	PLAYER,
	ATTACK_PLAYER,
	ATTACK_ENEMY,
	ITEM,

	UI,		// UI는 모든 게임오브젝트 중 최상단 Layer에 위치
	SIZE,
};

enum class GROUP_SCENE
{
	TOOL,
	TITLE,
	LOBBY,
	INGAME,

	SIZE,
};

enum class GROUP_TILE
{
	NONE,
	GROUND,
	PLATFORM,
	WALL,
	TOPANGLE,
	BOTANGLE,
	RIGHTSLOPE,
	LEFTSLOPE,

	SIZE,
};

enum class GROUP_ENEMY
{
	MELEE_WALK,
	RANGE_WALK,
	MELEE_FLY,
	RANGE_FLY,

	BOSS,

	SIZE,
};

//========================================
//## 상태 그룹							##
//========================================

enum class STATE_PLAYER
{
	IDLE,
	MOVE,
	DASH,
	JUMP,
	DOUBLEJUMP,
	DOWNJUMP,
	FALL,

	DEAD,

	SIZE,
};

enum class STATE_ENEMY
{
	IDLE,
	PATROL,
	TRACE,
	ATTACK,

	SPAWN,
	DEAD,

	SIZE,
};

//========================================
//## 이벤트 타입					##
//========================================

enum class TYPE_EVENT
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	CHANGE_SCENE,

	SIZE,
};

// Core & Manager
#include "CCore.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CPathManager.h"
#include "CCollisionManager.h"
#include "CEventManager.h"
#include "CResourceManager.h"
#include "CCameraManager.h"
#include "CUIManager.h"
#include "CSoundManager.h"
#include "CRenderManager.h"

//========================================
//##			디파인문				##
//========================================

#define DASH_FORCE  4000				// 돌아가는 힘
#define DASH_POWER	2000				// 가해지는 힘

#define GRAVITY_FORCE		2000		// 돌아가는 힘
#define GRAVITY_POWER		1200		// 가해지는 힘

#define PI			3.141592
#define RTOD		180 / PI

#define WINSTARTX   100
#define WINSTARTY   100
#define WINSIZEX	1280
#define	WINSIZEY	720
#define WINSTYLE	WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

#define DT				CTimeManager::getInst()->GetDT()
#define fDT				CTimeManager::getInst()->GetfDT()

#define Key(key)		CKeyManager::getInst()->GetButton(key)
#define KeyUp(key)		CKeyManager::getInst()->GetButtonUP(key)
#define KeyDown(key)	CKeyManager::getInst()->GetButtonDOWN(key)

#define MousePos()		CKeyManager::getInst()->GetMousePos()

#define DebugMode()		CSceneManager::getInst()->SetDebug()
#define Debug()			CSceneManager::getInst()->GetDebug()

#define CreateObj(pObj, group)	CEventManager::getInst()->EventCreateObject(pObj, group)
#define DeleteObj(pObj)			CEventManager::getInst()->EventDeleteObject(pObj)
#define ChangeScn(scene)		CEventManager::getInst()->EventChangeScene(scene)

//========================================
//## 전역변수(인스턴스, 윈도우 핸들)	##
//========================================

extern HINSTANCE hInst;
extern HWND hWnd;

template <class T> void SafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}