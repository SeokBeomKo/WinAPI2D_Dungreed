#include "framework.h"
#include "CEnemyStateMachine.h"

#include "CEnemyState.h"

CEnemyStateMachine::CEnemyStateMachine()
{
	m_pOwner = nullptr;
	m_pCurState = nullptr;

	AddState(new CEnemyIdleState(this,STATE_ENEMY::IDLE));
	AddState(new CEnemyTraceState(this, STATE_ENEMY::TRACE));
	AddState(new CEnemyAttackState(this, STATE_ENEMY::ATTACK));
	AddState(new CEnemyDeadState(this, STATE_ENEMY::DEAD));

	SetCurState(STATE_ENEMY::IDLE);
}

CEnemyStateMachine::~CEnemyStateMachine()
{
}

CEnemy* CEnemyStateMachine::GetOwner()
{
	return m_pOwner;
}

CEnemyState* CEnemyStateMachine::GetState(STATE_ENEMY _state)
{
	map<STATE_ENEMY, CEnemyState*>::iterator iter = m_mapState.find(_state);
	if (m_mapState.end() == iter)
	{
		return nullptr;
	}
	return iter->second;
}

void CEnemyStateMachine::SetCurState(STATE_ENEMY _state)
{
	m_pCurState = GetState(_state);
}

void CEnemyStateMachine::update()
{
	if (nullptr != m_pCurState)
		m_pCurState->Execute();
}

void CEnemyStateMachine::AddState(CEnemyState* _state)
{
	m_mapState.insert(make_pair(_state->GetStateGroup(), _state));
}

void CEnemyStateMachine::ChangeState(STATE_ENEMY _nextState)
{
	CEnemyState* pNextState = GetState(_nextState);

	m_pCurState->OnStateExit();
	m_pCurState = pNextState;
	m_pCurState->OnStateEnter();
}
