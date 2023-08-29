#pragma once

class CEnemy;
class CEnemyStateMachine;

//========================================
//## EnemyState							##
//========================================

class CEnemyState
{
protected:
	CEnemy* enemy;
	CEnemyStateMachine* stateMachine;

	STATE_ENEMY m_eState;
public:
	CEnemyState(CEnemyStateMachine* _stateMachine, STATE_ENEMY _stateEnum);
	~CEnemyState();

	void SetStateMachine(CEnemyStateMachine* _stateMachine);
	STATE_ENEMY GetStateGroup();

	virtual void Execute() = 0;
	virtual void OnStateEnter() = 0;
	virtual void OnStateExit() = 0;
};

//========================================
//## EnemyIdleState						##
//========================================

class CEnemyIdleState : public CEnemyState
{
public:
	CEnemyIdleState(CEnemyStateMachine* _stateMachine, STATE_ENEMY _stateEnum);
	~CEnemyIdleState();

	void Execute() override;
	void OnStateEnter() override;
	void OnStateExit() override;
};

//========================================
//## EnemyTraceState					##
//========================================

class CEnemyTraceState : public CEnemyState
{
public:
	CEnemyTraceState(CEnemyStateMachine* _stateMachine, STATE_ENEMY _stateEnum);
	~CEnemyTraceState();

	void Execute() override;
	void OnStateEnter() override;
	void OnStateExit() override;
};

//========================================
//## EnemyAttackState					##
//========================================

class CEnemyAttackState : public CEnemyState
{
public:
	CEnemyAttackState(CEnemyStateMachine* _stateMachine, STATE_ENEMY _stateEnum);
	~CEnemyAttackState();

	void Execute() override;
	void OnStateEnter() override;
	void OnStateExit() override;
};

//========================================
//## EnemyDeadState						##
//========================================

class CEnemyDeadState : public CEnemyState
{
public:
	CEnemyDeadState(CEnemyStateMachine* _stateMachine, STATE_ENEMY _stateEnum);
	~CEnemyDeadState();

	void Execute() override;
	void OnStateEnter() override;
	void OnStateExit() override;
};



