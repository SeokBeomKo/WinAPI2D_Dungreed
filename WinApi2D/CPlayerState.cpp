#include "framework.h"
#include "CPlayerState.h"

#include "CPlayerStateMachine.h"
#include "CPlayer.h"
#include "CAnimator.h"
#include "CGravity.h"

//========================================
//## �⺻ ����							##
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
//## ��� ����							##
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
		return;
	}
	if (KeyDown(VK_SPACE) || KeyDown('W') && m_pStateMachine->GetOwner()->GetGrounded())
	{
		m_pStateMachine->ChangeState(STATE_PLAYER::JUMP);
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
//## �̵� ����							##
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
//## ���� ����							##
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
	//m_pStateMachine->GetOwner()->InitGravity();
	m_pStateMachine->GetOwner()->RemoveJumpCount();
}

void CPlayerJumpState::exit()
{
}

//========================================
//## ���� ���� ����						##
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
//## ���� ����							##
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
//## ���� ����						##
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