#include "framework.h"
#include "CEnemyState.h"

#include "CEnemy.h"
#include "CEnemyType.h"
#include "CEnemyStateMachine.h"

//========================================
//## EnemyState							##
//========================================

CEnemyState::CEnemyState(CEnemyStateMachine* _stateMachine)
{
	stateMachine = _stateMachine;
	enemy = _stateMachine->GetOwner();
}

CEnemyState::~CEnemyState()
{
}

//========================================
//## EnemyState							##
//========================================

CEnemyIdleState::CEnemyIdleState(CEnemyStateMachine* _stateMachine)
	: CEnemyState(_stateMachine)
{
}

CEnemyIdleState::~CEnemyIdleState()
{
}

void CEnemyIdleState::Execute()
{
	enemy->GetEnemyType()->Idle();
}

void CEnemyIdleState::OnStateEnter()
{
}

void CEnemyIdleState::OnStateExit()
{
}

//========================================
//## EnemyState							##
//========================================

CEnemyTraceState::CEnemyTraceState(CEnemyStateMachine* _stateMachine)
	: CEnemyState(_stateMachine)
{
}

CEnemyTraceState::~CEnemyTraceState()
{
}

void CEnemyTraceState::Execute()
{
	enemy->GetEnemyType()->Trace();
}

void CEnemyTraceState::OnStateEnter()
{
}

void CEnemyTraceState::OnStateExit()
{
}

//========================================
//## EnemyState							##
//========================================

CEnemyAttackState::CEnemyAttackState(CEnemyStateMachine* _stateMachine)
	: CEnemyState(_stateMachine)
{
}

CEnemyAttackState::~CEnemyAttackState()
{
}

void CEnemyAttackState::Execute()
{
	enemy->GetEnemyType()->Attack();
}

void CEnemyAttackState::OnStateEnter()
{
}

void CEnemyAttackState::OnStateExit()
{
}

//========================================
//## EnemyState							##
//========================================

CEnemyDeadState::CEnemyDeadState(CEnemyStateMachine* _stateMachine)
	: CEnemyState(_stateMachine)
{
}

CEnemyDeadState::~CEnemyDeadState()
{
}

void CEnemyDeadState::Execute()
{
}

void CEnemyDeadState::OnStateEnter()
{
}

void CEnemyDeadState::OnStateExit()
{
}
