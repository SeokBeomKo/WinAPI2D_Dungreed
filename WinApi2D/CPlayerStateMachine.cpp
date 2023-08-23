#include "framework.h"
#include "CPlayerStateMachine.h"
#include "CPlayerState.h"

CPlayerStateMachine::CPlayerStateMachine()
{
	m_pPlayer	= nullptr;
	m_pCurState = nullptr;
	m_bVertical = true;

	m_mapState.insert(make_pair(STATE_PLAYER::IDLE,			new CPlayerIdleState(this)));
	m_mapState.insert(make_pair(STATE_PLAYER::MOVE,			new CPlayerMoveState(this)));
	m_mapState.insert(make_pair(STATE_PLAYER::DASH,			new CPlayerDashState(this)));
	m_mapState.insert(make_pair(STATE_PLAYER::JUMP,			new CPlayerJumpState(this)));
	m_mapState.insert(make_pair(STATE_PLAYER::DOUBLEJUMP,	new CPlayerDoubleJumpState(this)));
	m_mapState.insert(make_pair(STATE_PLAYER::DOWNJUMP,		new CPlayerDownJumpState(this)));
	m_mapState.insert(make_pair(STATE_PLAYER::FALL,			new CPlayerFallState(this)));
	m_mapState.insert(make_pair(STATE_PLAYER::DEAD,			new CPlayerDeadState(this)));

	m_pCurState = GetState(STATE_PLAYER::IDLE);
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

bool CPlayerStateMachine::GetVertical()
{
	return m_bVertical;
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

STATE_PLAYER CPlayerStateMachine::GetCurrentState()
{
	for (const auto& statePair : m_mapState)
	{
		if (statePair.second == m_pCurState)
		{
			return statePair.first;
		}
	}

	return STATE_PLAYER::IDLE; // 현재 상태를 찾지 못한 경우 기본 상태 반환
}

void CPlayerStateMachine::SetVertical(bool _vertical)
{
	m_bVertical = _vertical;
}

void CPlayerStateMachine::update()
{
	m_pCurState->update();
}

void CPlayerStateMachine::ChangeState(STATE_PLAYER nextState)
{
	CPlayerState* pNextState = GetState(nextState);
	assert(m_pCurState != pNextState);

	m_pCurState->exit();
	m_pCurState = pNextState;
	m_pCurState->enter();
}
