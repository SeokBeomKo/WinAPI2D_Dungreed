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
public:
	CEnemyState(CEnemyStateMachine* _stateMachine);
	~CEnemyState();

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
	CEnemyIdleState(CEnemyStateMachine* _stateMachine);
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
	CEnemyTraceState(CEnemyStateMachine* _stateMachine);
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
	CEnemyAttackState(CEnemyStateMachine* _stateMachine);
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
	CEnemyDeadState(CEnemyStateMachine* _stateMachine);
	~CEnemyDeadState();

	void Execute() override;
	void OnStateEnter() override;
	void OnStateExit() override;
};



