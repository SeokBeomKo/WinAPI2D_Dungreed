#pragma once

class CPlayer;
class CPlayerState;

class CPlayerStateMachine
{
	friend class CPlayer;
private:
	CPlayer* m_pPlayer;								// �÷��̾�
	bool m_bVertical;								// false = �� true = �� 

	map<STATE_PLAYER, CPlayerState*> m_mapState;	// �÷��̾��� ��� ����
	CPlayerState* m_pCurState;						// �÷��̾��� ���� ����	
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
