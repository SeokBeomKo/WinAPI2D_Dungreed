#include "framework.h"
#include "CPlayer.h"

#include "CScene.h"
#include "CTexture.h"

// 컴포넌트
#include "CCollider.h"				// 충돌체
#include "CAnimation.h"				// 애니메이션
#include "CAnimator.h"				// 애니메이터
#include "CGravity.h"				// 중력
#include "CPlayerStateMachine.h"	// 유한상태기계

// 아이템
#include "CWeapon.h"

CPlayer::CPlayer()
{
	m_pCurWeapon	= nullptr;
	m_pCollWeapon = nullptr;
	m_pCurEquip = new CEquip(this);

	m_iJumpCount = 1;
	m_fJumpForce = GRAVITY_POWER;
	m_fDashForce = DASH_POWER;

	m_pStateMachine = new CPlayerStateMachine;
	m_pStateMachine->m_pPlayer = this;

	SetName(L"Player");
	SetScale(fPoint(32.f * 4, 32.f * 4));

	CreateCollider();
	GetCollider()->SetScale(fPoint(32.f, 64.f));
	GetCollider()->SetOffsetPos(fPoint(0.f, 10.f));

	// 플레이어 애니메이션
	CreateAnimator();
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerIdle", L"texture\\player\\PlayerIdle.png");
	GetAnimator()->CreateAnimation(L"Idle", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.1f, 5);
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerMove", L"texture\\player\\PlayerRun.png");
	GetAnimator()->CreateAnimation(L"Move", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 0.06f, 8);
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerJump", L"texture\\player\\PlayerJump.png");
	GetAnimator()->CreateAnimation(L"Jump", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 1.f, 1);
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PlayerDead", L"texture\\player\\PlayerDead.png");
	GetAnimator()->CreateAnimation(L"Dead", m_pImg, fPoint(0.f, 0.f), fPoint(32.f, 32.f), fPoint(32.f, 0.f), 1.f, 1);

	CreateGravity();
}

CPlayer::~CPlayer()
{

}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}

CPlayer* CPlayer::GetObj()
{
	return this;
}

void CPlayer::Idle()
{
}

void CPlayer::Move(bool _isRight)
{
	fPoint pos = GetPos();

	if (_isRight)	pos.x += m_fVelocity * fDT;
	else			pos.x -= m_fVelocity * fDT;
		
	SetPos(pos);
}

void CPlayer::Jump()
{
	fPoint pos = GetPos();

	m_fJumpForce -= GRAVITY_FORCE * fDT;
	pos.y -= m_fJumpForce * fDT;

	SetPos(pos);
}


void CPlayer::Fall()
{
	
}

void CPlayer::Dash(fPoint _dir)
{
	fPoint pos = GetPos();

	m_fDashForce -= DASH_FORCE * fDT;
	pos += _dir * m_fDashForce * fDT;

	SetPos(pos);
}

void CPlayer::Dead()
{
}

void CPlayer::Attack()
{
	m_pCurWeapon->use(GetPos());
}

void CPlayer::Equip()
{
	// 아이템 장착
	if (nullptr == m_pCollWeapon)	return;
	if (nullptr != m_pCurWeapon)	UnEquip();
	
	m_pCurWeapon = m_pCollWeapon->Clone();
	m_pCurEquip->SetEquip(m_pCurWeapon->GetImage());
	m_pCollWeapon->Delete();
	m_pCollWeapon = nullptr;
}

void CPlayer::UnEquip()
{
	// 아이템 장착 해제
	if (nullptr == m_pCurWeapon)	return;		// 장착한 장비가 있는지 ?
	CItem* tItem = m_pCurWeapon->Clone();
	tItem->SetPos(GetPos());
	CreateObj(tItem, GROUP_GAMEOBJ::ITEM);
	m_pCurWeapon = nullptr;
	m_pCurEquip->Init();
}

void CPlayer::SetCollWeapon(CWeapon* collWeapon)
{
	m_pCollWeapon = collWeapon;
}

CWeapon* CPlayer::GetCollWeapon()
{
	return m_pCollWeapon;
}

CWeapon* CPlayer::GetWeapon()
{
	return m_pCurWeapon;
}

void CPlayer::InitDashForce()
{
	m_fDashForce = DASH_POWER;
}

float CPlayer::GetDashForce()
{
	return m_fDashForce;
}

bool CPlayer::GetJumpCount()
{
	return m_iJumpCount != 0;
}

void CPlayer::RemoveJumpCount()
{
	m_iJumpCount--;
}

void CPlayer::InitJumpForce()
{
	m_fJumpForce = GRAVITY_POWER;
}

float CPlayer::GetJump()
{
	return m_fJumpForce;
}

void CPlayer::SetJump(float temp)
{
	m_fJumpForce = temp;
}

void CPlayer::update()
{
	if (nullptr != m_pStateMachine)
	{
		m_pStateMachine->update();
	}
	if (m_pCurEquip->IsEquip())
	{
		m_pCurEquip->update();
	}

	GetAnimator()->update();
}

void CPlayer::render()
{
	if (m_pCurEquip->IsEquip())
	{
		m_pCurEquip->render();
	}
	component_render();
}

//========================================
//## Equip								##
//========================================

CEquip::CEquip()
{
	m_pOwner	= nullptr;
	m_pImg		= nullptr;
	m_fptOffset = {50.f, 10.f};
}

CEquip::CEquip(CGameObject* _owner)
{
	m_pOwner = _owner;
	m_fptOffset = { 50.f, 10.f };
}

CEquip::~CEquip()
{
}

void CEquip::Init()
{
	m_pImg = nullptr;
}

void CEquip::SetEquip(CD2DImage* _image)
{
	m_pImg = _image;
	SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
}

bool CEquip::IsEquip()
{
	return nullptr != m_pImg;
}

void CEquip::render()
{
	fPoint renderpos = CCameraManager::getInst()->GetRenderPos(GetPos());
	fPoint scale = GetScale();

	fPoint mousepos = MousePos();
	fVec2 d;
	d.x = (mousepos.x - renderpos.x);
	d.y = (mousepos.y - renderpos.y);

	float rotateDegree = atan2(d.y, d.x) * RTOD;

	CRenderManager::getInst()->RenderImage(
		m_pImg,
		renderpos.x - scale.x / 2.f,
		renderpos.y - scale.y / 2.f,
		renderpos.x + scale.x / 2.f,
		renderpos.y + scale.y / 2.f, true,
		renderpos - fPoint(m_fptOffset.x, 0.f),
		rotateDegree
	);
}

void CEquip::update()
{
	fPoint pos = m_pOwner->GetPos();
	fPoint realpos = CCameraManager::getInst()->GetRenderPos(pos);
	pos += m_fptOffset;

	SetPos(pos);
}
