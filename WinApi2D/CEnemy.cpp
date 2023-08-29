#include "framework.h"
#include "CEnemy.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CGravity.h"

#include "CEnemyStateMachine.h"

//========================================
//## Enemy								##
//========================================

CEnemy::CEnemy()
{
	m_pImg = nullptr;
	m_pType = nullptr;
	m_pStateMachine = new CEnemyStateMachine();
}

CEnemy::~CEnemy()
{
}

CEnemy* CEnemy::Clone()
{
	return nullptr;
}

void CEnemy::Init(CD2DImage* _img, CEnemyType* _type)
{
	m_pImg = _img;
	m_pType = _type;
}


void CEnemy::SetEnemyType(CEnemyType* _type)
{
	m_pType = _type;
}

CEnemyType* CEnemy::GetEnemyType()
{
	return m_pType;
}

void CEnemy::update()
{
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