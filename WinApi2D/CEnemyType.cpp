#include "framework.h"
#include "CEnemyType.h"
#include "CEnemy.h"

//========================================
//## Enemy								##
//========================================

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
	m_pOwner->SetGravity(!m_pOwner->GetGrounded());
}

void CEnemyMeleeWalkType::Move()
{
	m_pOwner->SetGravity(!m_pOwner->GetGrounded());
}

void CEnemyMeleeWalkType::Attack()
{
	m_pOwner->SetGravity(!m_pOwner->GetGrounded());
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
	m_pOwner->SetGravity(!m_pOwner->GetGrounded());
}

void CEnemyRangeWalkType::Move()
{
	m_pOwner->SetGravity(!m_pOwner->GetGrounded());
}

void CEnemyRangeWalkType::Attack()
{
	m_pOwner->SetGravity(!m_pOwner->GetGrounded());
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

void CEnemyMeleeFlyType::Move()
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

void CEnemyRangeFlyType::Move()
{
}

void CEnemyRangeFlyType::Attack()
{
}
