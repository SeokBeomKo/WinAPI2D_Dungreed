#pragma once

#include "CItem.h"
#include "IWeapon.h"

class CWeapon : public CItem, public IWeapon
{
private:

public:
	CWeapon();
	~CWeapon();

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
	~ShortSword();

	virtual void use();

	virtual void update();
	virtual void render();
};

