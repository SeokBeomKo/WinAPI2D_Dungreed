#include "framework.h"
#include "CScene_Lobby.h"

#include "CGameObject.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CSound.h"
#include "CD2DImage.h"

CScene_Lobby::CScene_Lobby()
{
}

CScene_Lobby::~CScene_Lobby()
{
}

void CScene_Lobby::update()
{
	CScene::update();

	if (KeyDown(VK_TAB))
	{
		ChangeScn(GROUP_SCENE::TOOL);
	}

	if (KeyDown('Z'))
	{
		CSoundManager::getInst()->AddSound(L"bgm", L"sound\\drumloop.wav", true);
		CSoundManager::getInst()->Play(L"bgm");
	}

	if (KeyDown('X'))
	{
		CSoundManager::getInst()->Stop(L"bgm");
	}
}

void CScene_Lobby::Enter()
{
	// 타일 로딩
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\temp";
	LoadTile(path);

	// Player 추가
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(fPoint(200, 200));
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);

	// Monster 추가
	CMonster* pMonster = new CMonster;
	pMonster->SetPos(fPoint(1100, 350));
	pMonster->SetCenterPos(pMonster->GetPos());
	AddObject(pMonster, GROUP_GAMEOBJ::MONSTER);


	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::MISSILE_PLAYER, GROUP_GAMEOBJ::MONSTER);

	// Camera Look 지정
	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
}

void CScene_Lobby::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
