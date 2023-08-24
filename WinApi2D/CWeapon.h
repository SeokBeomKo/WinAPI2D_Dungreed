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

