#include "framework.h"
#include "CPlayerState.h"

#include "CPlayerStateMachine.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CGravity.h"
#include "CPlayerVFX.h"

//========================================
//## 기본 상태							##
//========================================

CPlayerState::CPlayerState(CPlayerStateMachine* _machine)
{
	m_pStateMachine = _machine;
}

CPlayerState::~CPlayerState()
{
}

void CPlayerState::EquipHandle()
{
	if (KeyDown('E'))
	{
		if (nullptr == m_pStateMachine->GetOwner()->GetWeapon())
			m_pStateMachine->GetOwner()->Equip();
		else
		{
			m_pStateMachine->GetOwner()->UnEquip();
		}
	}
}

void CPlayerState::AttackHandle()
{
	if (nullptr == m_pStateMachine->GetOwner()->GetWeapon())	return;

	if (KeyDown(VK_LBUTTON))
	{
		m_pStateMachine->GetOwner()->Attack();
	}
}

bool CPlayerState::IdleHandle()
{
	if (m_pStateMachine->GetOwner()->GetGrounded())
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::IDLE);
		return true;
	}
	return false;
}

bool CPlayerState::MoveHandle()
{
	if (Key('A') || Key('D'))
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::MOVE);
		return true;
	}
	return false;
}

void CPlayerState::OverMoveHandle()
{
	if (Key('A') || Key('D'))
	{
		m_pStateMachine->GetOwner()->Move(Key('D'));
	}
}

bool CPlayerState::DashHandle()
{
	if (KeyDown(VK_RBUTTON))
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::DASH);
		return true;
	}
	return false;
}

bool CPlayerState::JumpHandle()
{
	if (KeyDown(VK_SPACE) || KeyDown('W') && m_pStateMachine->GetOwner()->GetGrounded())
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::JUMP);
		return true;
	}
	return false;
}

bool CPlayerState::DownJumpHandle()
{
	if (Key('S') && KeyDown(VK_SPACE))
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::DOWNJUMP);
		return true;
	}
	return false;
}

bool CPlayerState::FallHandle()
{
	if (!m_pStateMachine->GetOwner()->GetGrounded())
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::FALL);
		return true;
	}
	return false;
}

bool CPlayerState::GetVertical()
{
	fPoint pos = m_pStateMachine->GetOwner()->GetPos();
	fPoint realpos = CCameraManager::getInst()->GetRenderPos(pos);
	return MousePos().x <= realpos.x;
}

//========================================
//## 대기 상태							##
//========================================

CPlayerIdleState::CPlayerIdleState(CPlayerStateMachine* _machine)
	: CPlayerState(_machine)
{
}

CPlayerIdleState::~CPlayerIdleState()
{
}

void CPlayerIdleState::update()
{
	AttackHandle();
	EquipHandle();
	if (DownJumpHandle())	return;
	if (MoveHandle())		return;
	if (JumpHandle())		return;
	if (FallHandle())		return;
	if (DashHandle())		return;

	m_pStateMachine->GetOwner()->Idle();
	m_pStateMachine->GetOwner()->GetAnimator()->SetCurAniFlip(GetVertical());
	m_pStateMachine->GetOwner()->SetGravity(!m_pStateMachine->GetOwner()->GetGrounded());
}

void CPlayerIdleState::enter()
{
	m_pStateMachine->GetOwner()->GetAnimator()->Play(L"Idle", GetVertical());
}

void CPlayerIdleState::exit()
{
}

//========================================
//## 이동 상태							##
//========================================

CPlayerMoveState::CPlayerMoveState(CPlayerStateMachine* _machine)
	: CPlayerState(_machine)
{
	m_fabsDelay = 0.f;
}

CPlayerMoveState::~CPlayerMoveState()
{
}

void CPlayerMoveState::update()
{
	m_fabsDelay += fDT;
	if (m_fabsDelay >= 0.5f)
	{
		m_pStateMachine->GetOwner()->GetVFX(L"RunVFX")->PlayVFX(L"RunVFX", GetVertical());
		//CSoundManager::getInst()->Play(L"step1");
		m_fabsDelay = 0.f;
	}
	AttackHandle();
	EquipHandle();
	if (DownJumpHandle())	return;
	if (!Key('A') && !Key('D'))
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::IDLE);
		return;
	}
	if (JumpHandle())		return;
	if (FallHandle())		return;
	if (DashHandle())		return;

	m_pStateMachine->GetOwner()->Move(Key('D'));
	m_pStateMachine->GetOwner()->GetAnimator()->SetCurAniFlip(GetVertical());
	m_pStateMachine->GetOwner()->SetGravity(!m_pStateMachine->GetOwner()->GetGrounded());
}

void CPlayerMoveState::enter()
{
	m_fabsDelay = 1.f;
	m_pStateMachine->GetOwner()->GetAnimator()->Play(L"Move", GetVertical());
}

void CPlayerMoveState::exit()
{
}

//========================================
//## 대쉬 상태							##
//========================================

CPlayerDashState::CPlayerDashState(CPlayerStateMachine* _machine)
	: CPlayerState(_machine)
{
	m_fDashTime = 0.f;
	m_fptDirection = {};
}

CPlayerDashState::~CPlayerDashState()
{
}

void CPlayerDashState::update()
{
	AttackHandle();
	if (DashHandle())		return;
	if (m_pStateMachine->GetOwner()->GetDashForce() <= DASH_POWER * 0.1f)
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::FALL);
		return;
	}
	m_pStateMachine->GetOwner()->SetGravity(false);
	m_pStateMachine->GetOwner()->GetAnimator()->SetCurAniFlip(GetVertical());
	m_pStateMachine->GetOwner()->Dash(m_fptDirection);
}

void CPlayerDashState::enter()
{
	//CSoundManager::getInst()->Play(L"dash");
	m_pStateMachine->GetOwner()->GetAnimator()->Play(L"Jump", GetVertical());
	m_pStateMachine->GetOwner()->InitDashForce();
	m_fDashTime = 0.f;
	m_pStateMachine->GetOwner()->SetPassPlatform(true);

	m_fptDirection = (MousePos() - CCameraManager::getInst()->GetRenderPos(m_pStateMachine->GetOwner()->GetPos())).normalize();
}

void CPlayerDashState::exit()
{
	m_pStateMachine->GetOwner()->SetPassPlatform(false);
	
	m_fptDirection = {  };
}

//========================================
//## 점프 상태							##
//========================================

CPlayerJumpState::CPlayerJumpState(CPlayerStateMachine* _machine)
	: CPlayerState(_machine)
{
}

CPlayerJumpState::~CPlayerJumpState()
{
}

void CPlayerJumpState::update()
{
	AttackHandle();
	EquipHandle();
	m_pStateMachine->GetOwner()->Jump();

	if (m_pStateMachine->GetOwner()->GetJumpForce() <= 0.f)
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::FALL);
		return;
	}
	m_pStateMachine->GetOwner()->GetAnimator()->SetCurAniFlip(GetVertical());
	OverMoveHandle();
	if (DashHandle())		return;
}

void CPlayerJumpState::enter()
{
	//CSoundManager::getInst()->Play(L"jumping");
	m_pStateMachine->GetOwner()->GetAnimator()->Play(L"Jump", GetVertical());
	m_pStateMachine->GetOwner()->GetVFX(L"JumpVFX")->PlayVFX(L"JumpVFX");

	m_pStateMachine->GetOwner()->InitJumpForce();
	m_pStateMachine->GetOwner()->RemoveJumpCount();
	m_pStateMachine->GetOwner()->SetPassPlatform(true);
}

void CPlayerJumpState::exit()
{
	m_pStateMachine->GetOwner()->SetPassPlatform(false);
}

//========================================
//## 더블 점프 상태						##
//========================================

CPlayerDoubleJumpState::CPlayerDoubleJumpState(CPlayerStateMachine* _machine)
	: CPlayerState(_machine)
{
}

CPlayerDoubleJumpState::~CPlayerDoubleJumpState()
{
}

void CPlayerDoubleJumpState::update()
{
	AttackHandle();
	EquipHandle();
	OverMoveHandle();
	if (DashHandle())		return;
}

void CPlayerDoubleJumpState::enter()
{
}

void CPlayerDoubleJumpState::exit()
{
}

//========================================
//## 아래 점프 상태						##
//========================================

CPlayerDownJumpState::CPlayerDownJumpState(CPlayerStateMachine* _machine)
	: CPlayerState(_machine)
{
}

CPlayerDownJumpState::~CPlayerDownJumpState()
{
}

void CPlayerDownJumpState::update()
{
	m_pStateMachine->ChangeState(STATE_PLAYER::FALL);
}

void CPlayerDownJumpState::enter()
{
	m_pStateMachine->GetOwner()->SetGrounded(0);
}

void CPlayerDownJumpState::exit()
{
}

//========================================
//## 낙하 상태							##
//========================================


CPlayerFallState::CPlayerFallState(CPlayerStateMachine* _machine)
	: CPlayerState(_machine)
{
}

CPlayerFallState::~CPlayerFallState()
{
}

void CPlayerFallState::update()
{
	AttackHandle();
	EquipHandle();
	OverMoveHandle();
	if (IdleHandle())		return;
	if (DashHandle())		return;

	m_pStateMachine->GetOwner()->Fall();
	m_pStateMachine->GetOwner()->GetAnimator()->Play(L"Jump", GetVertical());
}

void CPlayerFallState::enter()
{
	m_pStateMachine->GetOwner()->InitGravity();
	m_pStateMachine->GetOwner()->SetGravity(true);
}

void CPlayerFallState::exit()
{
}


//========================================
//## 죽음 상태							##
//========================================

CPlayerDeadState::CPlayerDeadState(CPlayerStateMachine* _machine)
	: CPlayerState(_machine)
{
}

CPlayerDeadState::~CPlayerDeadState()
{
}

void CPlayerDeadState::update()
{
}

void CPlayerDeadState::enter()
{
}

void CPlayerDeadState::exit()
{
}


