#include "framework.h"
#include "CPlayerState.h"

#include "CPlayerStateMachine.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CGravity.h"

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
	if (Key('S') && KeyDown(VK_SPACE))
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::DOWNJUMP);
		return;
	}
	if (Key('A') || Key('D'))
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::MOVE);
		return;
	}
	if (KeyDown(VK_SPACE) || KeyDown('W') && m_pStateMachine->GetOwner()->GetGrounded())
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::JUMP);
		return;
	}
	if (!m_pStateMachine->GetOwner()->GetGrounded())
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::FALL);
		return;
	}
	if (KeyDown(VK_RBUTTON))
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::DASH);
		return;
	}
	m_pStateMachine->GetOwner()->Idle();
	m_pStateMachine->GetOwner()->SetGravity(!m_pStateMachine->GetOwner()->GetGrounded());
	m_pStateMachine->GetOwner()->GetAnimator()->Play(L"Idle", GetVertical());
}

void CPlayerIdleState::enter()
{
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
}

CPlayerMoveState::~CPlayerMoveState()
{
}

void CPlayerMoveState::update()
{
	if (!Key('A') && !Key('D'))
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::IDLE);
		return;
	}
	if (KeyDown(VK_SPACE) || KeyDown('W'))
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::JUMP);
		return;
	}
	if (!m_pStateMachine->GetOwner()->GetGrounded())
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::FALL);
		return;
	}

	m_pStateMachine->GetOwner()->Move(Key('D'));
	m_pStateMachine->GetOwner()->SetGravity(!m_pStateMachine->GetOwner()->GetGrounded());
	m_pStateMachine->GetOwner()->GetAnimator()->Play(L"Move", GetVertical());
}

void CPlayerMoveState::enter()
{
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
}

CPlayerDashState::~CPlayerDashState()
{
}

void CPlayerDashState::update()
{
	m_fDashTime += fDT;
	if (m_fDashTime >= 0.1f)
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::IDLE);
		return;
	}
	m_pStateMachine->GetOwner()->Dash();
	m_pStateMachine->GetOwner()->GetAnimator()->Play(L"Jump", GetVertical());
}

void CPlayerDashState::enter()
{
	m_fDashTime = 0.f;
}

void CPlayerDashState::exit()
{
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
	m_pStateMachine->GetOwner()->Jump();
	if (m_pStateMachine->GetOwner()->GetJump() < 50.f)
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::FALL);
		return;
	}

	if (Key('A') || Key('D'))
	{
		m_pStateMachine->GetOwner()->Move(Key('D'));
	}
	
	m_pStateMachine->GetOwner()->GetAnimator()->Play(L"Jump", GetVertical());
}

void CPlayerJumpState::enter()
{
	m_pStateMachine->GetOwner()->InitForce();
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
	if (m_pStateMachine->GetOwner()->GetGrounded())
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::IDLE);
		return;
	}
	if (Key('A') || Key('D'))
	{
		m_pStateMachine->GetOwner()->Move(Key('D'));
	}
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


