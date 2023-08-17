#pragma once

class CPlayerStateMachine;

//========================================
//## 기본 상태							##
//========================================

class CPlayerState
{
private:
	CPlayerStateMachine* m_pStateMachine;

public:
	CPlayerState();
	~CPlayerState();

	virtual void update() = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;
};

//========================================
//## 대기 상태							##
//========================================

class CPlayerIdleState : public CPlayerState
{
private:

public:
	CPlayerIdleState();
	~CPlayerIdleState();

	virtual void update();
	virtual void enter();
	virtual void exit();
};

//========================================
//## 이동 상태							##
//========================================

class CPlayerMoveState : public CPlayerState
{
private:

public:
	CPlayerMoveState();
	~CPlayerMoveState();

	virtual void update();
	virtual void enter();
	virtual void exit();
};

//========================================
//## 점프 상태							##
//========================================

class CPlayerJumpState : public CPlayerState
{
private:

public:
	CPlayerJumpState();
	~CPlayerJumpState();

	virtual void update();
	virtual void enter();
	virtual void exit();
};

//========================================
//## 낙하 상태							##
//========================================

class CPlayerFallState : public CPlayerState
{
private:

public:
	CPlayerFallState();
	~CPlayerFallState();

	virtual void update();
	virtual void enter();
	virtual void exit();
};
