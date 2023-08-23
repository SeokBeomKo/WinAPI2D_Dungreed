#pragma once

class CPlayerStateMachine;

//========================================
//## 기본 상태							##
//========================================

class CPlayerState
{
protected:
	CPlayerStateMachine* m_pStateMachine;

public:
	CPlayerState(CPlayerStateMachine* _machine);
	~CPlayerState();

	bool DownJumpHandle();
	bool GetVertical();

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
	CPlayerIdleState(CPlayerStateMachine* _machine);
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
	CPlayerMoveState(CPlayerStateMachine* _machine);
	~CPlayerMoveState();

	virtual void update();
	virtual void enter();
	virtual void exit();
};

//========================================
//## 대쉬 상태							##
//========================================

class CPlayerDashState : public CPlayerState
{
private:
	float m_fDashTime;
	fPoint m_fptDirection;
public:
	CPlayerDashState(CPlayerStateMachine* _machine);
	~CPlayerDashState();

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
	CPlayerJumpState(CPlayerStateMachine* _machine);
	~CPlayerJumpState();

	virtual void update();
	virtual void enter();
	virtual void exit();
};

//========================================
//## 더블 점프 상태						##
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
//## 아래 점프 상태						##
//========================================

class CPlayerDownJumpState : public CPlayerState
{
private:

public:
	CPlayerDownJumpState(CPlayerStateMachine* _machine);
	~CPlayerDownJumpState();

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
	CPlayerFallState(CPlayerStateMachine* _machine);
	~CPlayerFallState();

	virtual void update();
	virtual void enter();
	virtual void exit();
};

//========================================
//## 죽음 상태							##
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
