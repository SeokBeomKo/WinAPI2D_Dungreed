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

	float m_fAttackDelay;	// °ø°Ý µô·¹ÀÌ
public:
	CEnemyStateMachine();
	CEnemyStateMachine(CEnemy* _owner);
	~CEnemyStateMachine();

	CEnemy* GetOwner();
	CEnemyState* GetState(STATE_ENEMY _state);

	float GetAttackDelay();

	void SetCurState(STATE_ENEMY _state);
	void SetAttackDelay(float _attack);

	void update();

	void AddState(CEnemyState* _state);
	void ChangeState(STATE_ENEMY _nextState);
};

