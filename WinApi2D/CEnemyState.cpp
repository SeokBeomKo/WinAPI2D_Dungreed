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
	m_pStateMachine = _stateMachine;
	m_pEnemy		= _stateMachine->GetOwner();
	m_eState		= _stateEnum;
	m_fAttackDelay	= _stateMachine->GetAttackDelay();
	m_fAbsDelay		= 0.f;
	m_fPatrolDelay  = 0.f;
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
	m_fPatrolDelay -= fDT;
	if (m_fPatrolDelay <= 0.f)
	{
		m_pStateMachine->ChangeState(STATE_ENEMY::PATROL);
	}
	m_pEnemy->GetEnemyType()->Idle();
	m_pEnemy->GetAnimator()->Play(L"Idle");
}

void CEnemyIdleState::OnStateEnter()
{
	srand(GetTickCount64());
	m_fPatrolDelay = rand() % 5 + 1;
}

void CEnemyIdleState::OnStateExit()
{
	m_fPatrolDelay = 0.f;
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
	m_fPatrolDelay -= fDT;
	if (m_fPatrolDelay <= 0.f)
	{
		m_pStateMachine->ChangeState(STATE_ENEMY::IDLE);
	}
	m_pEnemy->GetEnemyType()->Move();
	m_pEnemy->GetAnimator()->Play(L"Move",m_pEnemy->GetEnemyDirection() != 1);
}

void CEnemyPatrolState::OnStateEnter()
{
	srand(GetTickCount64());
	m_pEnemy->SetEnemyDirection((rand() % 2) * 2 - 1);
	m_fPatrolDelay = rand() % 4 + 2;
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
	m_pEnemy->GetEnemyType()->Move();
	m_pEnemy->GetAnimator()->Play(L"Move");
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
	m_pEnemy->GetEnemyType()->Attack();
	m_pEnemy->GetAnimator()->Play(L"Attack");
}

void CEnemyAttackState::OnStateEnter()
{
	m_pEnemy->SetScaleOffset(m_pEnemy->GetEnemyScaleOffset());
	m_pEnemy->SetPosOffset(m_pEnemy->GetEnemyPosOffset());
}

void CEnemyAttackState::OnStateExit()
{
	m_pEnemy->SetScaleOffset(1.f);
	m_pEnemy->SetPosOffset({ 0,0 });
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
	m_pEnemy->GetAnimator()->Play(L"Spawn");
	if (m_pEnemy->GetAnimator()->IsAnimationFinished())
	{
		m_pStateMachine->ChangeState(STATE_ENEMY::IDLE);
	}
}

void CEnemySpawnState::OnStateEnter()
{
	fPoint resize_scale = m_pEnemy->GetScale();
	m_pEnemy->SetScaleOffset((resize_scale.x + resize_scale.y) * 0.5f);
}

void CEnemySpawnState::OnStateExit()
{
	m_pEnemy->SetScaleOffset(1.f);
	m_pEnemy->Init();
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
}

void CEnemyDeadState::OnStateExit()
{
}


