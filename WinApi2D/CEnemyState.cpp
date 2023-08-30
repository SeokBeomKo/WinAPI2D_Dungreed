#include "framework.h"
#include "CEnemyState.h"

#include "CEnemy.h"
#include "CEnemyType.h"
#include "CEnemyStateMachine.h"

#include "CAnimator.h"

//========================================
//## EnemyState							##
//========================================

CEnemyState::CEnemyState(CEnemyStateMachine* _stateMachine, STATE_ENEMY _stateEnum)
{
	stateMachine	= _stateMachine;
	enemy			= _stateMachine->GetOwner();
	m_eState		= _stateEnum;
	m_fDelay		= 0.f;
}

CEnemyState::~CEnemyState()
{
}

STATE_ENEMY CEnemyState::GetStateGroup()
{
	return m_eState;
}

//========================================
//## EnemyIdleState						##
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
	enemy->GetAnimator()->Play(L"Idle");
}

void CEnemyIdleState::OnStateEnter()
{
}

void CEnemyIdleState::OnStateExit()
{
}

//========================================
//## EnemyPatrolState					##
//========================================

CEnemyPatrolState::CEnemyPatrolState(CEnemyStateMachine* _stateMachine, STATE_ENEMY _stateEnum)
	: CEnemyState(_stateMachine, _stateEnum)
{
}

CEnemyPatrolState::~CEnemyPatrolState()
{
}

void CEnemyPatrolState::Execute()
{
	enemy->GetEnemyType()->Move();
	enemy->GetAnimator()->Play(L"Move");
}

void CEnemyPatrolState::OnStateEnter()
{
}

void CEnemyPatrolState::OnStateExit()
{
}

//========================================
//## EnemyTraceState					##
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
	enemy->GetEnemyType()->Move();
	enemy->GetAnimator()->Play(L"Move");
}

void CEnemyTraceState::OnStateEnter()
{
}

void CEnemyTraceState::OnStateExit()
{
}

//========================================
//## EnemyAttackState					##
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
	enemy->GetAnimator()->Play(L"Attack");
}

void CEnemyAttackState::OnStateEnter()
{
	
}

void CEnemyAttackState::OnStateExit()
{
}

//========================================
//## EnemySpawnState					##
//========================================

CEnemySpawnState::CEnemySpawnState(CEnemyStateMachine* _stateMachine, STATE_ENEMY _stateEnum)
	: CEnemyState(_stateMachine, _stateEnum)
{
}

CEnemySpawnState::~CEnemySpawnState()
{
}

void CEnemySpawnState::Execute()
{
}

void CEnemySpawnState::OnStateEnter()
{
	m_fDelay = 0.f;
}

void CEnemySpawnState::OnStateExit()
{
}

//========================================
//## EnemyDeadState						##
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
	m_fDelay = 0.f;
}

void CEnemyDeadState::OnStateExit()
{
}


