#pragma once

class CPlayer;
class CPlayerState;

class CPlayerStateMachine
{
private:
	CPlayer* m_pPlayer;								// 플레이어

	map<STATE_PLAYER, CPlayerState*> m_mapState;	// 플레이어의 모든 상태
	CPlayerState* m_pCurState;						// 플레이어의 현재 상태	
public:
	CPlayerStateMachine();
	~CPlayerStateMachine();

	CPlayer* GetOwner();
	CPlayerState* GetState(STATE_PLAYER state);

	void ChangeState(STATE_PLAYER nextState);
};

