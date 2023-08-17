#include "framework.h"
#include "CPlayerState.h"

//========================================
//## 기본 상태							##
//========================================

CPlayerState::CPlayerState()
{
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

CPlayerIdleState::CPlayerIdleState()
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

CPlayerMoveState::CPlayerMoveState()
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

CPlayerJumpState::CPlayerJumpState()
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

CPlayerFallState::CPlayerFallState()
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
