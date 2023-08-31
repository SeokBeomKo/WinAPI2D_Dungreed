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
	m_pOwner		= _stateMachine->GetOwner();
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

	float fLen = (m_pOwner->GetTarget()->GetPos() - m_pOwner->GetPos()).Length();

	if (fLen <= m_pOwner->GetEnemyAttackDis())
	{
		m_pStateMachine->ChangeState(STATE_ENEMY::ATTACK);
		return;
	}
	if (fLen <= m_pOwner->GetEnemyRegionDis())
	{
		m_pStateMachine->ChangeState(STATE_ENEMY::TRACE);
		return;
	}
	if (m_fPatrolDelay <= 0.f)
	{
		m_pStateMachine->ChangeState(STATE_ENEMY::PATROL);
		return;
	}
	m_pOwner->GetEnemyType()->Idle();
}

void CEnemyIdleState::OnStateEnter()
{
	m_pOwner->GetAnimator()->Play(L"Idle", m_pOwner->GetEnemyDirection() != 1);
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
	float fLen = (m_pOwner->GetTarget()->GetPos() - m_pOwner->GetPos()).Length();

	if (fLen <= m_pOwner->GetEnemyAttackDis())
	{
		m_pStateMachine->ChangeState(STATE_ENEMY::ATTACK);
		return;
	}
	if (fLen <= m_pOwner->GetEnemyRegionDis())
	{
		m_pStateMachine->ChangeState(STATE_ENEMY::TRACE);
		return;
	}
	if (m_fPatrolDelay <= 0.f)
	{
		m_pStateMachine->ChangeState(STATE_ENEMY::IDLE);
		return;
	}
	m_pOwner->GetEnemyType()->Move();
	
}

void CEnemyPatrolState::OnStateEnter()
{
	srand(GetTickCount64());
	m_pOwner->SetEnemyDirection((rand() % 2) * 2 - 1);
	m_fPatrolDelay = rand() % 4 + 2;
	m_pOwner->GetAnimator()->Play(L"Move", m_pOwner->GetEnemyDirection() != 1);
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
	float fLen = (m_pOwner->GetTarget()->GetPos() - m_pOwner->GetPos()).Length();

	if (fLen > m_pOwner->GetEnemyRegionDis())
	{
		m_pStateMachine->ChangeState(STATE_ENEMY::IDLE);
		return;
	}
	if (fLen <= m_pOwner->GetEnemyAttackDis())
	{
		m_pStateMachine->ChangeState(STATE_ENEMY::ATTACK);
		return;
	}

	if (m_pOwner->GetTarget()->GetPos().x > m_pOwner->GetPos().x)
		m_pOwner->SetEnemyDirection(1);
	else
		m_pOwner->SetEnemyDirection(-1);
	m_pOwner->GetAnimator()->SetCurAniFlip(m_pOwner->GetEnemyDirection() != 1);
	m_pOwner->GetEnemyType()->Move();
}

void CEnemyTraceState::OnStateEnter()
{
	m_pOwner->GetAnimator()->Play(L"Move", m_pOwner->GetEnemyDirection() != 1);
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
	if (m_pOwner->GetAnimator()->IsAnimationFinished())
	{
		m_pStateMachine->ChangeState(STATE_ENEMY::IDLE);
		return;
	}
	m_pOwner->GetEnemyType()->Attack();
}

void CEnemyAttackState::OnStateEnter()
{
	m_pOwner->GetAnimator()->Play(L"Attack", m_pOwner->GetEnemyDirection() != 1);
	m_pOwner->SetScaleOffset(m_pOwner->GetEnemyScaleOffset());
	m_pOwner->SetPosOffset(m_pOwner->GetEnemyPosOffset());
}

void CEnemyAttackState::OnStateExit()
{
	m_pOwner->SetScaleOffset(1.f);
	m_pOwner->SetPosOffset({ 0,0 });
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
	if (m_pOwner->GetAnimator()->IsAnimationFinished())
	{
		m_pStateMachine->ChangeState(STATE_ENEMY::IDLE);
	}
}

void CEnemySpawnState::OnStateEnter()
{
	m_pOwner->GetAnimator()->Play(L"Spawn");
	float resize_scale = (m_pOwner->GetScale().x + m_pOwner->GetScale().y) * 0.5f;
	m_pOwner->SetScale({ resize_scale, resize_scale });
}

void CEnemySpawnState::OnStateExit()
{
	m_pOwner->SetScaleOffset(1.f);
	m_pOwner->InitSpawn();
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
	if (m_pOwner->GetAnimator()->IsAnimationFinished())
	{
		m_pStateMachine->ChangeState(STATE_ENEMY::IDLE);
	}
}

void CEnemyDeadState::OnStateEnter()
{
	m_pOwner->GetAnimator()->Play(L"Dead");
	float resize_scale = (m_pOwner->GetScale().x + m_pOwner->GetScale().y) * 0.5f;
	m_pOwner->SetScale({ resize_scale, resize_scale });
	m_pOwner->SetGravity(false);
}

void CEnemyDeadState::OnStateExit()
{
	DeleteObj(m_pOwner);
}


