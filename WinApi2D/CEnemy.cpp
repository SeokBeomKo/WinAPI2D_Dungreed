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

CEnemy* CEnemy::Clone()
{
	return nullptr;
}

CEnemyType* CEnemy::GetEnemyType()
{
	return m_pType;
}

void CEnemy::update()
{
	if (nullptr != GetGravity())
		GetGravity()->finalupdate();
	if (nullptr != GetAnimator())
		GetAnimator()->update();
	if (nullptr != m_pStateMachine)
		m_pStateMachine->update();
}

void CEnemy::render()
{
	component_render();
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