#include "framework.h"
#include "CPlayerState.h"

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

void CPlayerState::update()
{
}

void CPlayerState::enter()
{
}

void CPlayerState::exit()
{
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
