#pragma once

#include "CEntity.h"

class CD2DImage;
class CPlayerStateMachine;
class IWeapon;
class CWeapon;

class CPlayer : public CEntity
{
private:
	CD2DImage* m_pImg;
	CPlayerStateMachine* m_pStateMachine;

	float m_fVelocity = 350.f;	// 이동속도

	float m_fJumpForce;		// 점프 힘
	float m_fDashForce;		// 대쉬 힘
	int m_iJumpCount;		// 점프 횟수
protected:
	CWeapon* m_pCollWeapon;	// 충돌중인 무기

	CWeapon* m_pCurWeapon;	// 장착 무기

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* Clone();

	virtual CPlayer* GetObj();

	void Idle();
	void Move(bool _isRight);
	void Jump();
	// void DoubleJump();
	void Fall();
	void Dash(fPoint _dir);
	void Dead();

	void Attack();

	void Equip();
	void UnEquip();

	// 무기
	void SetCollWeapon(CWeapon* collWeapon);
	CWeapon* GetCollWeapon();
	CWeapon* GetWeapon();

	void InitDashForce();
	float GetDashForce();

	bool GetJumpCount();
	void RemoveJumpCount();

	void InitJumpForce();

	float GetJump();
	void SetJump(float temp);

	virtual void update();
	virtual void render();
};

