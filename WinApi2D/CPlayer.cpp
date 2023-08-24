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
#include "IWeapon.h"

CPlayer::CPlayer()
{
	m_pCurWeapon = nullptr;

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

	/*CAnimation* pAni;
	pAni = GetAnimator()->FindAnimation(L"LeftMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);
	pAni = GetAnimator()->FindAnimation(L"RightMove");
	pAni->GetFrame(1).fptOffset = fPoint(0.f, -20.f);*/
}

CPlayer::~CPlayer()
{

}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
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
	m_pCurWeapon->use();
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

IWeapon* CPlayer::GetWeapon()
{
	return m_pCurWeapon;
}

void CPlayer::update()
{
	if (nullptr != m_pStateMachine)
	{
		m_pStateMachine->update();
	}

	GetAnimator()->update();
}

void CPlayer::render()
{
	component_render();
}
