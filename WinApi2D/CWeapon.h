#pragma once

#include "CItem.h"
#include "IWeapon.h"

class CPlayerAttack;

class CWeapon : public CItem, public IWeapon
{
protected:
	CPlayerAttack* m_pAttack;

	CD2DImage* m_pAttackImg;
public:
	CWeapon();
	CWeapon(const CWeapon& _other);
	~CWeapon();
	virtual CWeapon* Clone() = 0;

	virtual void Init() = 0;

	virtual void use(fPoint _pos) = 0;

	virtual void update() = 0;
	virtual void render() = 0;

	virtual void OnCollision(CCollider* _pOther);		// 재정의용 충돌중 가상함수
	virtual void OnCollisionEnter(CCollider* _pOther);	// 재정의용 충돌시 가상함수
	virtual void OnCollisionExit(CCollider* _pOther);	// 재정의용 탈충돌 가상함수
};

//========================================
//## ShortSword							##
//========================================

class ShortSword : public CWeapon
{
public:
	ShortSword();
	ShortSword(const ShortSword& _other);
	~ShortSword();
	ShortSword* Clone() override;
	void Init() override;

	virtual void use(fPoint _pos);

	virtual void update();
	virtual void render();
};

//========================================
//## PowerKatana						##
//========================================

class PowerKatana : public CWeapon
{
public:
	PowerKatana();
	PowerKatana(const PowerKatana& _other);
	~PowerKatana();
	PowerKatana* Clone() override;
	void Init() override;

	virtual void use(fPoint _pos);

	virtual void update();
	virtual void render();
};