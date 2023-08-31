#pragma once

#include "CEntity.h"

class CD2DImage;
class CPlayerStateMachine;
class CWeapon;
class CEquip;

class CPlayerVFXController;
class CPlayerVFX;

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

	CWeapon* m_pCurWeapon;	// 보유 무기 (인벤토리)
	CEquip* m_pCurEquip;	// 장착 무기 렌더
	CPlayerVFXController* m_pVFXcontroller;
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

	int GetDirection();

	void InitDashForce();
	float GetDashForce();

	bool GetJumpCount();
	void RemoveJumpCount();

	void InitJumpForce();

	float GetJumpForce();
	void SetJumpForce(float temp);

	CPlayerVFX* GetVFX(wstring _name);

	virtual void update();
	virtual void render();
};

//========================================
//## Equip								##
//========================================

class CEquip : public CGameObject
{
private:
	CGameObject* m_pOwner;
	CD2DImage* m_pImg;
protected:
	fPoint	m_fptOffset;
public:
	CEquip();
	CEquip(CGameObject* _owner);
	~CEquip();
	virtual CEquip* Clone() { return this; };

	void Init();
	void SetEquip(CD2DImage* _image);
	bool IsEquip();

	virtual void render();
	virtual void update();
};

