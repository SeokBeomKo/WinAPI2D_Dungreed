#include "framework.h"
#include "CPlayerVFX.h"
#include "CPlayer.h"

// component
#include "CAnimator.h"

CPlayerVFX::CPlayerVFX(CPlayer* _obj)
{
	m_pOwner = _obj;
	m_wstrName = L"";
	m_fPosYOffset = 0.f;
	CreateAnimator();

	CreateObj(this, GROUP_GAMEOBJ::VFX_PLAYER);
}

CPlayerVFX::CPlayerVFX(const CPlayerVFX& _other)
{
	m_pImg = _other.m_pImg;
	m_pOwner = _other.m_pOwner;
	m_wstrName = _other.m_wstrName;
	m_fPosYOffset = _other.m_fPosYOffset;
}

CPlayerVFX::~CPlayerVFX()
{
}

CPlayerVFX* CPlayerVFX::Clone()
{
	return nullptr;
}

void CPlayerVFX::update()
{
	if (!GetAnimator()->IsAnimationFinished())
		GetAnimator()->update();
}

void CPlayerVFX::render()
{
	if (!GetAnimator()->IsAnimationFinished())
		component_render();
}

void CPlayerVFX::PlayVFX(wstring _name, bool _flip)
{
	GetAnimator()->Play(_name, _flip);
	SetOffset();
}

//========================================
//## Run								##
//========================================

CPlayerRunVFX::CPlayerRunVFX(CPlayer* _obj)
	: CPlayerVFX(_obj)
{
	m_wstrName = L"RunVFX";
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"RunVFX", L"texture\\player\\RunFX.png");
	GetAnimator()->CreateAnimation(L"RunVFX", m_pImg, fPoint(0.f, 0.f), fPoint(16.f, 16.f), fPoint(16.f, 0.f), 0.05f, 6);
	SetScale(fPoint(16.f, 16.f) * 4.f);
}

CPlayerRunVFX::CPlayerRunVFX(const CPlayerRunVFX& _other)
	: CPlayerVFX(_other)
{
}

CPlayerRunVFX::~CPlayerRunVFX()
{
}

void CPlayerRunVFX::SetOffset()
{
	float offsetX = m_pOwner->GetPos().x + (40.f * m_pOwner->GetDirection());
	SetPos({ offsetX, m_pOwner->GetPos().y + m_pOwner->GetScale().y / 8.f });
}

//========================================
//## Jump								##
//========================================

CPlayerJumpVFX::CPlayerJumpVFX(CPlayer* _obj)
	: CPlayerVFX(_obj)
{
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerJumpVFX", L"texture\\player\\JumpFX.png");
	GetAnimator()->CreateAnimation(L"JumpVFX", m_pImg, fPoint(0.f, 0.f), fPoint(9.f, 10.f), fPoint(9.f, 0.f), 0.05f, 5);
	SetScale(fPoint(9.f, 10.f) * 4.f);
}

CPlayerJumpVFX::CPlayerJumpVFX(const CPlayerJumpVFX& _other)
	: CPlayerVFX(_other)
{
}

CPlayerJumpVFX::~CPlayerJumpVFX()
{
}

void CPlayerJumpVFX::SetOffset()
{
	SetPos({ m_pOwner->GetPos().x, m_pOwner->GetPos().y + m_pOwner->GetScale().y / 6.f });
}

//========================================
//## Dash								##
//========================================

CPlayerDashVFX::CPlayerDashVFX(CPlayer* _obj)
	: CPlayerVFX(_obj)
{
}

CPlayerDashVFX::CPlayerDashVFX(const CPlayerDashVFX& _other)
	: CPlayerVFX(_other)
{
}

CPlayerDashVFX::~CPlayerDashVFX()
{
}

void CPlayerDashVFX::SetOffset()
{
}
