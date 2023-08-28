#pragma once

#include "CItem.h"
#include "IWeapon.h"

class CWeapon : public CItem, public IWeapon
{
private:

public:
	CWeapon();
	CWeapon(const CWeapon& _other);
	~CWeapon();
	virtual CWeapon* Clone() = 0;

	virtual void use() = 0;

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

	virtual void use();

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

	virtual void use();

	virtual void update();
	virtual void render();
};