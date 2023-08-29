#include "framework.h"
#include "CEnemyStateMachine.h"

CEnemyStateMachine::CEnemyStateMachine(GROUP_ENEMY _group)
{
}

CEnemyStateMachine::~CEnemyStateMachine()
{
}

CEnemy* CEnemyStateMachine::GetOwner()
{
	return nullptr;
}

CEnemyState* CEnemyStateMachine::GetState(STATE_ENEMY _state)
{
	return nullptr;
}

void CEnemyStateMachine::SetCurState(STATE_ENEMY _state)
{
}

void CEnemyStateMachine::update()
{
}

void CEnemyStateMachine::AddState(CEnemyState* _state)
{
}

void CEnemyStateMachine::ChangeState(STATE_ENEMY _nextState)
{
}
