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

	virtual void OnCollision(CCollider* _pOther);		// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionEnter(CCollider* _pOther);	// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionExit(CCollider* _pOther);	// �����ǿ� Ż�浹 �����Լ�
};

//========================================
//## ShortSword							##
//========================================

class ShortSword : public CWeapon
{
public:
	ShortSword();
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
	~PowerKatana();
	PowerKatana* Clone() override;

	virtual void use();

	virtual void update();
	virtual void render();
};