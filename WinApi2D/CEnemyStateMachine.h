#pragma once

class CEnemy;
class CEnemyState;

class CEnemyStateMachine
{
	friend class CEnemy;
private:
	map<STATE_ENEMY, CEnemyState*> m_mapState;
	CEnemy* m_pOwner;
	CEnemyState* m_pCurState;
public:
	CEnemyStateMachine(GROUP_ENEMY _group);
	~CEnemyStateMachine();

	CEnemy* GetOwner();
	CEnemyState* GetState(STATE_ENEMY _state);
	void SetCurState(STATE_ENEMY _state);

	void update();

	void AddState(CEnemyState* _state);
	void ChangeState(STATE_ENEMY _nextState);
};

