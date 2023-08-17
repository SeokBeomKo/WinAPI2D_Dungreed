#include "framework.h"
#include "CPlayerStateMachine.h"
#include "CPlayerState.h"

CPlayerStateMachine::CPlayerStateMachine()
{
	m_pPlayer	= nullptr;
	m_pCurState = nullptr;
}

CPlayerStateMachine::~CPlayerStateMachine()
{
	for (map<STATE_PLAYER, CPlayerState*>::iterator iter = m_mapState.begin(); iter != m_mapState.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	m_mapState.clear();
}

CPlayer* CPlayerStateMachine::GetOwner()
{
	return m_pPlayer;
}

CPlayerState* CPlayerStateMachine::GetState(STATE_PLAYER state)
{
	map<STATE_PLAYER, CPlayerState*>::iterator iter = m_mapState.find(state);
	if (m_mapState.end() == iter)
	{
		return nullptr;
	}
	return iter->second;
}

void CPlayerStateMachine::ChangeState(STATE_PLAYER nextState)
{
	CPlayerState* pNextState = GetState(nextState);
	assert(m_pCurState != pNextState);

	m_pCurState->exit();
	m_pCurState = pNextState;
	m_pCurState->enter();
}
