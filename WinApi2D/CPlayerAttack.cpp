#include "framework.h"
#include "CPlayerAttack.h"

// component
#include "CAnimator.h"
#include "CCollider.h"

CPlayerAttack::CPlayerAttack()
{
	m_pImg = nullptr;

	m_iDamage		= 0;
	m_iRange		= 100;
	m_fCurTimeFX	= 0.f;
	m_fMaxTimeFX	= 0.4f;
	m_fptDirFX		= { 0, 0 };

	CreateAnimator();
	CreateCollider();
}

CPlayerAttack::CPlayerAttack(CD2DImage* _img, int _dmg, int _range, fPoint _dir, float _time)
{
	m_pImg = _img;
	m_iDamage = _dmg;
	m_iRange = _range;
	m_fptDirFX = _dir;

	CreateAnimator();
	CreateCollider();
}

CPlayerAttack::~CPlayerAttack()
{
}


void CPlayerAttack::Init(fPoint _pos)
{
	fPoint finalpos = _pos;

	m_fptDirFX = MousePos() - CCameraManager::getInst()->GetRenderPos(_pos);

	finalpos = finalpos + m_fptDirFX.normalize() * m_iRange;

	SetPos(finalpos);
	GetCollider()->SetFinalPos(_pos);
}

int CPlayerAttack::GetDamage()
{
	return m_iDamage;
}

float CPlayerAttack::GetDegree()
{
	return atan2(m_fptDirFX.y, m_fptDirFX.x) * RTOD;
}

void CPlayerAttack::PlayVFX()
{
	GetAnimator()->Play(L"Attack");
}

void CPlayerAttack::update()
{
	m_fCurTimeFX += fDT;

	if (m_fCurTimeFX >= m_fMaxTimeFX)
		DeleteObj(this);

	GetAnimator()->update();
}

void CPlayerAttack::render()
{
	component_render();
}
