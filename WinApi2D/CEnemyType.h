#pragma once

class CEnemy;

//========================================
//## Enemy								##
//========================================

class CEnemyType
{
protected:
	CEnemy* m_pOwner;
public:
	CEnemyType();
	CEnemyType(CEnemy* _owner);
	~CEnemyType();

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
	CEnemyMeleeWalkType(CEnemy* _owner);
	~CEnemyMeleeWalkType();

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
	CEnemyRangeWalkType(CEnemy* _owner);
	~CEnemyRangeWalkType();

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
	CEnemyMeleeFlyType(CEnemy* _owner);
	~CEnemyMeleeFlyType();

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
	CEnemyRangeFlyType(CEnemy* _owner);
	~CEnemyRangeFlyType();

	void Idle() override;
	void Trace() override;
	void Attack() override;
};

