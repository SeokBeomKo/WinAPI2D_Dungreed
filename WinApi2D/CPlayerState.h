#pragma once

class CPlayerStateMachine;

//========================================
//## �⺻ ����							##
//========================================

class CPlayerState
{
protected:
	CPlayerStateMachine* m_pStateMachine;

public:
	CPlayerState(CPlayerStateMachine* _machine);
	~CPlayerState();

	bool GetVertical();

	virtual void update() = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;
};

//========================================
//## ��� ����							##
//========================================

class CPlayerIdleState : public CPlayerState
{
private:

public:
	CPlayerIdleState(CPlayerStateMachine* _machine);
	~CPlayerIdleState();

	virtual void update();
	virtual void enter();
	virtual void exit();
};

//========================================
//## �̵� ����							##
//========================================

class CPlayerMoveState : public CPlayerState
{
private:

public:
	CPlayerMoveState(CPlayerStateMachine* _machine);
	~CPlayerMoveState();

	virtual void update();
	virtual void enter();
	virtual void exit();
};

//========================================
//## ���� ����							##
//========================================

class CPlayerJumpState : public CPlayerState
{
private:

public:
	CPlayerJumpState(CPlayerStateMachine* _machine);
	~CPlayerJumpState();

	virtual void update();
	virtual void enter();
	virtual void exit();
};

//========================================
//## ���� ���� ����						##
//========================================

class CPlayerDoubleJumpState : public CPlayerState
{
private:

public:
	CPlayerDoubleJumpState(CPlayerStateMachine* _machine);
	~CPlayerDoubleJumpState();

	virtual void update();
	virtual void enter();
	virtual void exit();
};

//========================================
//## ���� ����							##
//========================================

class CPlayerFallState : public CPlayerState
{
private:

public:
	CPlayerFallState(CPlayerStateMachine* _machine);
	~CPlayerFallState();

	virtual void update();
	virtual void enter();
	virtual void exit();
};

//========================================
//## ���� ����							##
//========================================

class CPlayerDeadState : public CPlayerState
{
private:

public:
	CPlayerDeadState(CPlayerStateMachine* _machine);
	~CPlayerDeadState();

	virtual void update();
	virtual void enter();
	virtual void exit();
};