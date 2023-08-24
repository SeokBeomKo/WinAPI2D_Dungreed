#pragma once

#include "CEntity.h"

class CD2DImage;
class CPlayerStateMachine;
class IWeapon;

class CPlayer : public CEntity
{
private:
	CD2DImage* m_pImg;
	CPlayerStateMachine* m_pStateMachine;

	float m_fVelocity = 350.f;	// �̵��ӵ�

	float m_fJumpForce;		// ���� ��
	float m_fDashForce;		// �뽬 ��
	int m_iJumpCount;		// ���� Ƚ��
protected:
	IWeapon* m_pCurWeapon;	// ���� ����

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

	void Attack();

	void InitDashForce();
	float GetDashForce();

	bool GetJumpCount();
	void RemoveJumpCount();

	void InitJumpForce();

	float GetJump();
	void SetJump(float temp);

	IWeapon* GetWeapon();

	virtual void update();
	virtual void render();
};

