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
public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	void Idle();
	void Move(bool _isRight, bool _isGrounded = true);
	// void Jump();
	// void DoubleJump();
	void Dash();
	void Dead();


	virtual void update();
	virtual void render();
};

