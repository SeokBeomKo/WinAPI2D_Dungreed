#include "framework.h"
#include "CEnemy.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CGravity.h"

#include "CEnemyStateMachine.h"
#include "CEnemyType.h"

//========================================
//## Enemy								##
//========================================

CEnemy::CEnemy()
{
	m_pImg = nullptr;
	m_pType = nullptr;
	m_pStateMachine = new CEnemyStateMachine(this);
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

//========================================
//## BigWhiteSkel						##
//========================================

BigWhiteSkelEnemy::BigWhiteSkelEnemy()
{
	SetScaleOffset(1.5f);
	SetName(L"BigSkelleton");
	SetScale(fPoint(33.f * 4.f, 30.f * 4.f));
	
	CreateCollider();
	GetCollider()->SetScale(GetScale());

	CreateAnimator();

	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"BigWhiteSkelIdle", L"texture\\enemy\\BigWhiteSkelIdle.png");
	GetAnimator()->CreateAnimation(L"Idle", m_pImg, fPoint(0.f, 0.f), fPoint(33.f, 30.f), fPoint(0.f, 30.f), 0.1f, 6);
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"BigWhiteSkelMove", L"texture\\enemy\\BigWhiteSkelMove.png");
	GetAnimator()->CreateAnimation(L"Move", m_pImg, fPoint(0.f, 0.f), fPoint(33.f, 30.f), fPoint(0.f, 30.f), 0.1f, 6);
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"BigWhiteSkelAttack", L"texture\\enemy\\BigWhiteSkelAttack.png");
	GetAnimator()->CreateAnimation(L"Attack", m_pImg, fPoint(0.f, 0.f), fPoint(65.f, 48.f), fPoint(0.f, 48.f), 0.1f, 12);

	m_pType = new CEnemyMeleeWalkType(this);
	m_pStateMachine = new CEnemyStateMachine(this);

	CreateGravity();
}

BigWhiteSkelEnemy::~BigWhiteSkelEnemy()
{
}

BigWhiteSkelEnemy* BigWhiteSkelEnemy::Clone()
{
	return new BigWhiteSkelEnemy(*this);
}

void BigWhiteSkelEnemy::update()
{
	if (nullptr != m_pStateMachine)
	{
		m_pStateMachine->update();
	}
	GetAnimator()->update();
}

void BigWhiteSkelEnemy::render()
{
	component_render();
}
