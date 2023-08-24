#pragma once
class IWeapon
{
public:
	virtual void use() = 0;
};

class IMeleeWeapon : public IWeapon
{
public:
	virtual void use() = 0;
};

class IRangeWeapon : public IWeapon
{
public:
	virtual void use() = 0;
};

