#pragma once

class CPlayer;
class CPlayerState;

class CPlayerStateMachine
{
	friend class CPlayer;
private:
	CPlayer* m_pPlayer;								// 플레이어
	bool m_bVertical;								// false = 좌 true = 우 

	map<STATE_PLAYER, CPlayerState*> m_mapState;	// 플레이어의 모든 상태
	CPlayerState* m_pCurState;						// 플레이어의 현재 상태	
public:
	CPlayerStateMachine();
	~CPlayerStateMachine();

	CPlayer* GetOwner();
	bool GetVertical();
	CPlayerState* GetState(STATE_PLAYER state);
	STATE_PLAYER GetCurrentState();

	void SetVertical(bool _vertical);

	void update();

	void ChangeState(STATE_PLAYER nextState);
};

