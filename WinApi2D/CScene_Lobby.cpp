#include "framework.h"
#include "CScene_Lobby.h"
#include "CSound.h"
#include "CD2DImage.h"

#include "CImage.h"
#include "CBackGround.h"

// Entity
#include "CGameObject.h"
#include "CPlayer.h"
#include "CEnemy.h"

#include "CEnemyType.h"

// 아이템
#include "CWeapon.h"

CScene_Lobby::CScene_Lobby()
{
	m_fptPlayerPos = { 3700.f, 650.f };
	// 배경음
	CSoundManager::getInst()->AddSound(L"CScene_Town_bgm", L"sound\\0.Town.wav", true);

	//// 플레이어
	//CSoundManager::getInst()->AddSound(L"dash", L"sound\\dash.wav", false);
	//CSoundManager::getInst()->AddSound(L"jumping", L"sound\\jumping.wav", false);
	//CSoundManager::getInst()->AddSound(L"step1", L"sound\\step1.wav", false);
	//CSoundManager::getInst()->AddSound(L"equip", L"sound\\equip.wav", false);

	//// 적
	/*CSoundManager::getInst()->AddSound(L"MonsterHit", L"sound\\MonsterHit.wav", false);
	CSoundManager::getInst()->AddSound(L"MonsterDie", L"sound\\MonsterDie.wav", false);
	CSoundManager::getInst()->AddSound(L"MonsterSpawn", L"sound\\MonsterSpawn.wav", false);*/
}

CScene_Lobby::~CScene_Lobby()
{
}

void CScene_Lobby::update()
{
	CScene::update();

	if (KeyDown(VK_F2))
	{
		// Enemy 추가
		CEnemy* pBigSkeleton01 = new BigWhiteSkelEnemy(GetTarget());
		pBigSkeleton01->SetPos(m_fptPlayerPos);
		AddObject(pBigSkeleton01, GROUP_GAMEOBJ::ENEMY);
	}
}

void CScene_Lobby::SetTarget(CEntity* _target)
{
	m_pTarget = _target;
}

CEntity* CScene_Lobby::GetTarget()
{
	if (nullptr != m_pTarget)
		return m_pTarget;
	return nullptr;
}

void CScene_Lobby::Enter()
{
	CCameraManager::getInst()->FadeIn(2.f);
	// 배경음
	CSoundManager::getInst()->Play(L"CScene_Town_bgm");

	// 타일 로딩
	wstring path = CPathManager::getInst()->GetContentPath();
	path += L"tile\\Lobby.tile";
	LoadTile(path);

	// 타일 이미지
	CBack_Ground* town = new CBack_Ground;
	town->Load(L"Town", L"texture\\map\\Lobby.png");
	AddObject(town, GROUP_GAMEOBJ::MAP);

	// 배경 이미지
	CImage* skyday = new CImage;
	skyday->Load(L"Sky_Day", L"texture\\background\\Sky_Day.png", {WINSIZEX /2.f , WINSIZEY / 2.f});
	AddObject(skyday, GROUP_GAMEOBJ::BACK_GROUND);
	CBack_Ground* townBG_day = new CBack_Ground;
	townBG_day->Load(L"TownBG_Day", L"texture\\background\\TownBG_Day.png", fPoint(0.f, 160.f), 7.f);
	AddObject(townBG_day, GROUP_GAMEOBJ::BACK_GROUND);
	CBack_Ground* townLayer_day = new CBack_Ground;
	townLayer_day->Load(L"TownLayer_Day", L"texture\\background\\TownLayer_Day.png", fPoint(0.f, 550.f), 3.f);
	AddObject(townLayer_day, GROUP_GAMEOBJ::BACK_GROUND);

	// Player 추가
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetPos(m_fptPlayerPos);
	AddObject(pPlayer, GROUP_GAMEOBJ::PLAYER);
	SetTarget(pPlayer);

	// Enemy 추가
	CEnemy* pBigSkeleton01 = new BigWhiteSkelEnemy(GetTarget());
	pBigSkeleton01->SetPos(m_fptPlayerPos);
	AddObject(pBigSkeleton01, GROUP_GAMEOBJ::ENEMY);

	// Item 추가
	CItem* pShortSword = new ShortSword;
	pShortSword->SetPos({ 4000.f, 650.f });
	AddObject(pShortSword, GROUP_GAMEOBJ::ITEM);

	CItem* pPowerKatana = new PowerKatana;
	pPowerKatana->SetPos({ 3500.f, 650.f });
	AddObject(pPowerKatana, GROUP_GAMEOBJ::ITEM);

	// 타일 충돌
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::TILE);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::ITEM, GROUP_GAMEOBJ::TILE);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::ENEMY, GROUP_GAMEOBJ::TILE);

	// 공격 충돌
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::ATTACK_ENEMY);
	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::ENEMY, GROUP_GAMEOBJ::ATTACK_PLAYER);

	CCollisionManager::getInst()->CheckGroup(GROUP_GAMEOBJ::PLAYER, GROUP_GAMEOBJ::ITEM);

	// Camera Look 
	CCameraManager::getInst()->SetRange(fPoint(1904.f, 384.f));
	CCameraManager::getInst()->SetTargetObj(pPlayer);
}

void CScene_Lobby::Exit()
{
	CSoundManager::getInst()->Stop(L"CScene_Town_bgm");
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
