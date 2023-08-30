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
	m_pStateMachine = nullptr;
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

void CEnemy::SetEnemyScaleOffset(float _scaleOffset)
{
	m_fEnemyScaleOffset = _scaleOffset;
}

void CEnemy::SetEnemyPosOffset(fPoint _posOffset)
{
	m_fptEnemyPosOffset = _posOffset;
}

void CEnemy::SetEnemyVelocity(float _velocity)
{
	m_fVelocity = _velocity;
}

void CEnemy::SetEnemyDirection(int _dir)
{
	m_iDirection = _dir;
}

float CEnemy::GetEnemyScaleOffset()
{
	return m_fEnemyScaleOffset;
}

fPoint CEnemy::GetEnemyPosOffset()
{
	return m_fptEnemyPosOffset;
}

float CEnemy::GetEnemyVelocity()
{
	return m_fVelocity;
}

int CEnemy::GetEnemyDirection()
{
	return m_iDirection;
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
	CGameObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetGroup() == GROUP_GAMEOBJ::ATTACK_PLAYER)
	{
		/*CPlayerAttack* pAttack = (CPlayerAttack*)pOther->GetObj();
		m_tInfo.fHP -= pAttack->GetDamage();
		CSoundManager::getInst()->Play(L"MonsterHit");
		if (m_tInfo.fHP <= 0)
		{
			pFX->PlayFX(this, L"Die");
			DeleteObj(this);
		}*/
		m_pStateMachine->ChangeState(STATE_ENEMY::DEAD);
	}
}

void CEnemy::OnCollisionExit(CCollider* _pOther)
{
}

//========================================
//## BigWhiteSkel						##
//========================================

BigWhiteSkelEnemy::BigWhiteSkelEnemy()
{
	SetEnemyScaleOffset(1.7f);
	SetEnemyPosOffset({ 50.f, -40.f });
	SetName(L"BigSkelleton");
	SetScale(fPoint(33.f * 4.f, 30.f * 4.f));

	CreateAnimator();
	// Enemy 기본 이미지
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"EnemySpawn", L"texture\\enemy\\EnemySpawn.png");
	GetAnimator()->CreateAnimation(L"Spawn", m_pImg, fPoint(0.f, 0.f), fPoint(31.f, 31.f), fPoint(31.f, 0), 0.1f, 15);
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"EnemyDead", L"texture\\enemy\\EnemyDead.png");
	GetAnimator()->CreateAnimation(L"Dead", m_pImg, fPoint(0.f, 0.f), fPoint(40.f, 40.f), fPoint(40, 0), 0.05f, 11);
	// Enemy 이미지
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"BigWhiteSkelIdle", L"texture\\enemy\\BigWhiteSkelIdle.png");
	GetAnimator()->CreateAnimation(L"Idle", m_pImg, fPoint(0.f, 0.f), fPoint(33.f, 30.f), fPoint(0.f, 30.f), 0.1f, 6);
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"BigWhiteSkelMove", L"texture\\enemy\\BigWhiteSkelMove.png");
	GetAnimator()->CreateAnimation(L"Move", m_pImg, fPoint(0.f, 0.f), fPoint(33.f, 30.f), fPoint(0.f, 30.f), 0.1f, 6);
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"BigWhiteSkelAttack", L"texture\\enemy\\BigWhiteSkelAttack.png");
	GetAnimator()->CreateAnimation(L"Attack", m_pImg, fPoint(0.f, 0.f), fPoint(65.f, 48.f), fPoint(0.f, 48.f), 0.1f, 12);

	m_pType = new CEnemyMeleeWalkType(this);
	m_pStateMachine = new CEnemyStateMachine(this);
	m_pStateMachine->SetAttackDelay(1.f);	// 공격 딜레이 설정
}

BigWhiteSkelEnemy::~BigWhiteSkelEnemy()
{
}

BigWhiteSkelEnemy* BigWhiteSkelEnemy::Clone()
{
	return new BigWhiteSkelEnemy(*this);
}

void BigWhiteSkelEnemy::InitSpawn()
{
	CreateCollider();
	GetCollider()->SetScale({ 70.f,120.f });

	CreateGravity();
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
