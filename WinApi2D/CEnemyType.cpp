#include "framework.h"
#include "CEnemyType.h"
#include "CEnemy.h"

//========================================
//## Enemy								##
//========================================

CEnemyType::CEnemyType()
{
	m_pOwner = nullptr;
}

CEnemyType::CEnemyType(CEnemy* _owner)
{
	m_pOwner = _owner;
}

CEnemyType::~CEnemyType()
{
}

//========================================
//## MeleeWalkEnemy						##
//========================================

CEnemyMeleeWalkType::CEnemyMeleeWalkType(CEnemy* _owner)
	: CEnemyType(_owner)
{
}

CEnemyMeleeWalkType::~CEnemyMeleeWalkType()
{
}

void CEnemyMeleeWalkType::Idle()
{
}

void CEnemyMeleeWalkType::Trace()
{
}

void CEnemyMeleeWalkType::Attack()
{
}

//========================================
//## RangeWalkEnemy						##
//========================================

CEnemyRangeWalkType::CEnemyRangeWalkType(CEnemy* _owner)
	: CEnemyType(_owner)
{
}

CEnemyRangeWalkType::~CEnemyRangeWalkType()
{
}

void CEnemyRangeWalkType::Idle()
{
}

void CEnemyRangeWalkType::Trace()
{
}

void CEnemyRangeWalkType::Attack()
{
}

//========================================
//## MeleeFlyEnemy						##
//========================================

CEnemyMeleeFlyType::CEnemyMeleeFlyType(CEnemy* _owner)
	: CEnemyType(_owner)
{
}

CEnemyMeleeFlyType::~CEnemyMeleeFlyType()
{
}

void CEnemyMeleeFlyType::Idle()
{
}

void CEnemyMeleeFlyType::Trace()
{
}

void CEnemyMeleeFlyType::Attack()
{
}

//========================================
//## RangeFlyEnemy						##
//========================================

CEnemyRangeFlyType::CEnemyRangeFlyType(CEnemy* _owner)
	: CEnemyType(_owner)
{
}

CEnemyRangeFlyType::~CEnemyRangeFlyType()
{
}

void CEnemyRangeFlyType::Idle()
{
}

void CEnemyRangeFlyType::Trace()
{
}

void CEnemyRangeFlyType::Attack()
{
}
