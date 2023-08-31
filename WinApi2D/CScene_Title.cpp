#include "framework.h"
#include "CScene_Title.h"

//

#include "CImage.h"
#include "CBackGround.h"
#include "CButtonUI.h"

SCene_Title::SCene_Title()
{
	CSoundManager::getInst()->AddSound(L"CScene_Start_bgm", L"sound\\title.wav", true);
}

SCene_Title::~SCene_Title()
{
}

void SCene_Title::update()
{
	CScene::update();
}

void StartCheck(DWORD_PTR, DWORD_PTR)
{
	ChangeScn(GROUP_SCENE::LOBBY);
}

void OptionCheck(DWORD_PTR, DWORD_PTR)
{
	ChangeScn(GROUP_SCENE::TOOL);
}

void ExitCheck(DWORD_PTR, DWORD_PTR)
{
	// 윈도우 종료 함수
	PostQuitMessage(0);
}

void SCene_Title::Enter()
{
	CSoundManager::getInst()->Play(L"CScene_Start_bgm");

	CImage* backsky = new CImage;
	backsky->Load(L"Back_Sky", L"texture\\background\\BackSky.png",{WINSIZEX / 2.f, WINSIZEY / 2.f});
	AddObject(backsky, GROUP_GAMEOBJ::BACK_GROUND);

	CScrollBack_Ground* cloud00 = new CScrollBack_Ground;
	cloud00->SetPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	cloud00->Load(L"BackCloud00", L"texture\\background\\BackCloud00.png", 15.f, -1900.f, 2500.f);
	AddObject(cloud00, GROUP_GAMEOBJ::BACK_GROUND);
	CScrollBack_Ground* cloud00clone = cloud00->Clone();
	cloud00clone->SetPos(fPoint(WINSIZEX / 2.f + 2500.f, WINSIZEY / 2.f));
	AddObject(cloud00clone, GROUP_GAMEOBJ::BACK_GROUND);

	CScrollBack_Ground* cloud01 = new CScrollBack_Ground;
	cloud01->SetPos(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	cloud01->Load(L"BackCloud01", L"texture\\background\\BackCloud01.png", 80.f, -2300.f, 2500.f);
	AddObject(cloud01, GROUP_GAMEOBJ::BACK_GROUND);
	CScrollBack_Ground* cloud01clone = cloud01->Clone();
	cloud01clone->SetPos(fPoint(WINSIZEX / 2.f + 2500.f, WINSIZEY / 2.f));
	AddObject(cloud01clone, GROUP_GAMEOBJ::BACK_GROUND);

	// 시작 버튼
	CTitleButtonUI* pStartUI = new CTitleButtonUI();
	pStartUI->Load(L"PlayOff_Kor", L"texture\\ui\\PlayOff_Kor.png", L"PlayOn_Kor", L"texture\\ui\\PlayOn_Kor.png");
	pStartUI->SetPos(fPoint(WINSIZEX / 2 - pStartUI->GetScale().x / 2, WINSIZEY / 2 + 100.f - pStartUI->GetScale().y / 2));
	pStartUI->SetClickedCallBack(StartCheck, 0, 0);
	AddObject(pStartUI, GROUP_GAMEOBJ::UI);
	// 옵션 버튼
	CTitleButtonUI* pOptiontUI = new CTitleButtonUI();
	pOptiontUI->Load(L"OptionOff_Kor", L"texture\\ui\\OptionOff_Kor.png", L"OptionOn_Kor", L"texture\\ui\\OptionOn_Kor.png");
	pOptiontUI->SetPos(fPoint(WINSIZEX / 2 - pOptiontUI->GetScale().x / 2, WINSIZEY / 2 + 150.f - pOptiontUI->GetScale().y / 2));
	pOptiontUI->SetClickedCallBack(OptionCheck, 0, 0);
	AddObject(pOptiontUI, GROUP_GAMEOBJ::UI);
	// 종료 버튼
	CTitleButtonUI* pExitUI = new CTitleButtonUI();
	pExitUI->Load(L"ExitOff_Kor", L"texture\\ui\\ExitOff_Kor.png", L"ExitOn_Kor", L"texture\\ui\\ExitOn_Kor.png");
	pExitUI->SetPos(fPoint(WINSIZEX / 2 - pExitUI->GetScale().x / 2, WINSIZEY / 2 + 200.f - pExitUI->GetScale().y / 2));
	pExitUI->SetClickedCallBack(ExitCheck, 0, 0);
	AddObject(pExitUI, GROUP_GAMEOBJ::UI);

	CImage* logo = new CImage;
	logo->Load(L"MainLogo", L"texture\\background\\MainLogo.png", { WINSIZEX / 2.f, 200.f }, 4.f);
	AddObject(logo, GROUP_GAMEOBJ::BACK_GROUND);
	CImage* copy = new CImage;
	copy->Load(L"Copyright", L"texture\\background\\Copyright.png", {WINSIZEX / 2.f, WINSIZEY - 50.f }, 4.f);
	AddObject(copy, GROUP_GAMEOBJ::BACK_GROUND);

	// Camera Look 지정
	CCameraManager::getInst()->SetLookAt(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
}

void SCene_Title::Exit()
{
	CSoundManager::getInst()->Stop(L"CScene_Start_bgm");
	DeleteAll();

	CCollisionManager::getInst()->Reset();
}
