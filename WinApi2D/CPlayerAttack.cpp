#include "framework.h"
#include "CPlayerAttack.h"

// component
#include "CAnimator.h"
#include "CCollider.h"

CPlayerAttack::CPlayerAttack()
{
	m_pImg = nullptr;

	m_iDamage	= 0;
	m_iRange	= 0;
	m_fTimeFX	= 0.f;
	m_fptDirFX	= { 0, 0 };
}

CPlayerAttack::CPlayerAttack(CD2DImage* _img, int _dmg, int _range, fPoint _dir, float _time)
{
	m_pImg = _img;
	m_iDamage = _dmg;
	m_iRange = _range;
	m_fTimeFX = _time;
	m_fptDirFX = _dir;

	CreateAnimator();
	CreateCollider();
}

CPlayerAttack::~CPlayerAttack()
{
}


void CPlayerAttack::Init(fPoint _ownerPos, fPoint _slice, fPoint _step, float _duration, UINT _frmCount, bool _reverse, bool _rotate, float _pos)
{
	fPoint finalpos = GetPos();
	fPoint pos = _ownerPos;
	fPoint realpos = CCameraManager::getInst()->GetRenderPos(pos);

	m_fptDirFX = MousePos() - realpos;

	float rotateDegree = atan2(m_fptDirFX.y, m_fptDirFX.x) * 180 / 3.141592;

	GetAnimator()->CreateAnimation(L"Attack", m_pImg, fPoint(0.f, 0.f), _slice, _step, _duration, _frmCount, _reverse, _rotate, rotateDegree);
	SetScale(_slice * 4.f);
	GetCollider()->SetScale(_slice * 4.f);

	finalpos.x = finalpos.x + m_fptDirFX.normalize().x * m_iRange;
	finalpos.y = finalpos.y + m_fptDirFX.normalize().y * m_iRange;

	SetPos(finalpos);
	GetCollider()->SetFinalPos(_ownerPos);
}

int CPlayerAttack::GetDamage()
{
	return m_iDamage;
}

void CPlayerAttack::update()
{
	m_fTimeFX += fDT;

	if (m_fTimeFX >= m_fTimeFX)
		DeleteObj(this);

	GetAnimator()->update();
}

void CPlayerAttack::render()
{
	GetAnimator()->Play(L"Attack");

	component_render();
}
