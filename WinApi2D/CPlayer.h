#pragma once

#include "CEntity.h"

class CD2DImage;
class CPlayerStateMachine;

class CPlayer : public CEntity
{
private:
	CD2DImage* m_pImg;
	CPlayerStateMachine* m_pStateMachine;

	float m_fVelocity = 350.f;
	float m_fForce = 1200.f;

	float m_fJumpForce;
	float m_fDashForce;
	int m_iJumpCount;
public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	void Idle();
	void Move(bool _isRight);
	void Jump();
	// void DoubleJump();
	void Fall();
	void Dash(fPoint _dir);
	void Dead();

	void InitDashForce();
	float GetDashForce();

	bool GetJumpCount();
	void RemoveJumpCount();

	void InitJumpForce();
	float GetForce();

	float GetJump();
	void SetJump(float temp);

	virtual void update();
	virtual void render();
};

