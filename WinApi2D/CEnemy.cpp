#include "framework.h"
#include "CEnemy.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CGravity.h"

#include "CEnemyStateMachine.h"
#include "CGroundEnemyState.h"
#include "CFlyEnemyState.h"

//========================================
//## Enemy								##
//========================================

CEnemy::CEnemy()
{
}

CEnemy::~CEnemy()
{
}

void CEnemy::render()
{
}

void CEnemy::OnCollision(CCollider* _pOther)
{
}

void CEnemy::OnCollisionEnter(CCollider* _pOther)
{
}

void CEnemy::OnCollisionExit(CCollider* _pOther)
{
}

//========================================
//## GroundEnemy						##
//========================================

CGroundEnemy::CGroundEnemy()
{
}

CGroundEnemy::~CGroundEnemy()
{
}

CGroundEnemy* CGroundEnemy::Clone()
{
	return nullptr;
}

void CGroundEnemy::update()
{
	if (nullptr != GetGravity())
		GetGravity()->finalupdate();
	if (nullptr != GetAnimator())
		GetAnimator()->update();
	if (nullptr != m_pStateMachine)
		m_pStateMachine->update();
}

void CGroundEnemy::render()
{
	component_render();
}

//========================================
//## FlyEnemy							##
//========================================

CFlyEnemy::CFlyEnemy()
{
}

CFlyEnemy::~CFlyEnemy()
{
}

CFlyEnemy* CFlyEnemy::Clone()
{
	return nullptr;
}

void CFlyEnemy::update()
{
	if (nullptr != GetAnimator())
		GetAnimator()->update();
	if (nullptr != m_pStateMachine)
		m_pStateMachine->update();
}

void CFlyEnemy::render()
{
	component_render();
}
