#include "framework.h"
#include "CPlayerState.h"

#include "CPlayerStateMachine.h"
#include "CPlayer.h"
#include "CAnimator.h"

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
	if (Key('A') || Key('D'))
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::MOVE);
	}
	m_pStateMachine->GetOwner()->GetAnimator()->Play(L"Idle", GetVertical());
	m_pStateMachine->GetOwner()->Idle();
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
	}
	m_pStateMachine->GetOwner()->Move(Key('D'));
	m_pStateMachine->GetOwner()->GetAnimator()->Play(L"Move", GetVertical());
}

void CPlayerMoveState::enter()
{
}

void CPlayerMoveState::exit()
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
}

void CPlayerJumpState::enter()
{
}

void CPlayerJumpState::exit()
{
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
}

void CPlayerFallState::enter()
{
}

void CPlayerFallState::exit()
{
}


//========================================
//## 죽음 상태						##
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
