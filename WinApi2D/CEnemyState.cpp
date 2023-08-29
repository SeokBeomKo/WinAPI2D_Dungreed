#include "framework.h"
#include "CEnemyState.h"

#include "CEnemy.h"
#include "CEnemyType.h"
#include "CEnemyStateMachine.h"

//========================================
//## EnemyState							##
//========================================

CEnemyState::CEnemyState(CEnemyStateMachine* _stateMachine, STATE_ENEMY _stateEnum)
{
	stateMachine = _stateMachine;
	enemy = _stateMachine->GetOwner();
	m_eState = _stateEnum;
}

CEnemyState::~CEnemyState()
{
}

STATE_ENEMY CEnemyState::GetStateGroup()
{
	return m_eState;
}

//========================================
//## EnemyState							##
//========================================

CEnemyIdleState::CEnemyIdleState(CEnemyStateMachine* _stateMachine, STATE_ENEMY _stateEnum)
	: CEnemyState(_stateMachine, _stateEnum)
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

CEnemyTraceState::CEnemyTraceState(CEnemyStateMachine* _stateMachine, STATE_ENEMY _stateEnum)
	: CEnemyState(_stateMachine, _stateEnum)
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

CEnemyAttackState::CEnemyAttackState(CEnemyStateMachine* _stateMachine, STATE_ENEMY _stateEnum)
	: CEnemyState(_stateMachine, _stateEnum)
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

CEnemyDeadState::CEnemyDeadState(CEnemyStateMachine* _stateMachine, STATE_ENEMY _stateEnum)
	: CEnemyState(_stateMachine, _stateEnum)
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
