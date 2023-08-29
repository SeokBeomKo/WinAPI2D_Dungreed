#pragma once

//========================================
//## Enemy								##
//========================================

class CEnemyType
{
private:
public:
	virtual void Idle() = 0;
	virtual void Trace() = 0;
	virtual void Attack() = 0;
};

//========================================
//## MeleeWalkEnemy						##
//========================================

class CEnemyMeleeWalkType : public CEnemyType
{
private:
public:
	void Idle() override;
	void Trace() override;
	void Attack() override;
};

//========================================
//## RangeWalkEnemy						##
//========================================

class CEnemyRangeWalkType : public CEnemyType
{
private:
public:
	void Idle() override;
	void Trace() override;
	void Attack() override;
};

//========================================
//## MeleeFlyEnemy						##
//========================================

class CEnemyMeleeFlyType : public CEnemyType
{
private:
public:
	void Idle() override;
	void Trace() override;
	void Attack() override;
};

//========================================
//## RangeFlyEnemy						##
//========================================

class CEnemyRangeFlyType : public CEnemyType
{
private:
public:
	void Idle() override;
	void Trace() override;
	void Attack() override;
};

