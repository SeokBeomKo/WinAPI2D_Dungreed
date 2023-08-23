#include "framework.h"
#include "CScene_Lobby.h"

#include "CGameObject.h"
#include "CBackGround.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CSound.h"
#include "CD2DImage.h"

CScene_Lobby::CScene_Lobby()
{
	m_fptPlayerPos = { 3700.f, 650.f };
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
}

void CScene_Lobby::Enter()
{
	// 타일 로딩
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\Lobby.tile";
	LoadTile(path);

	// 맵 이미지
	CBack_Ground* town = new CBack_Ground;
	town->Load(L"Town", L"texture\\map\\Lobby.png");
	AddObject(town, GROUP_GAMEOBJ::MAP);

	// 배경 이미지
	CBack_Ground* skyday = new CBack_Ground;
	skyday->Load(L"Sky_Day", L"texture\\background\\Sky_Day.png", { WINSIZEX / 2.f, WINSIZEY / 2.f });
	AddObject(skyday, GROUP_GAMEOBJ::BACK_GROUND);
	/*CBack_Ground* townBG_day = new CBack_Ground;
	townBG_day->Load(L"TownBG_Day", L"texture\\background\\TownBG_Day.png", fPoint(0.f, 160.f), 7.f);
	AddObject(townBG_day, GROUP_GAMEOBJ::BACK_GROUND);
	CBack_Ground* townLayer_day = new CBack_Ground;
	townLayer_day->Load(L"TownLayer_Day", L"texture\\background\\TownLayer_Day.png", fPoint(0.f, 550.f), 3.f);
	AddObject(townLayer_day, GROUP_GAMEOBJ::BACK_GROUND);*/

	// Player 추가
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(m_fptPlayerPos);
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);

	// Monster 추가
	CMonster* pMonster = new CMonster;
	pMonster->SetPos(fPoint(1100, 350));
	pMonster->SetCenterPos(pMonster->GetPos());
	AddObject(pMonster, GROUP_GAMEOBJ::MONSTER);


	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::MONSTER);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::MISSILE_PLAYER, GROUP_GAMEOBJ::MONSTER);

	// Camera Look 
	CCameraManager::getInst()->SetRange(fPoint(1904.f, 384.f));
	CCameraManager::getInst()->SetTargetObj(pPlayer);
}

void CScene_Lobby::Exit()
{
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
