#include "framework.h"
#include "CGameObject.h"
#include "CCollider.h"
#include "CAnimator.h"

CGameObject::CGameObject()
{
	m_fptPos = {};
	m_fptScale = {};
	m_pCollider = nullptr;
	m_pAnimator = nullptr;
	m_bActive = true;
}

CGameObject::CGameObject(const CGameObject& _other)
{
	m_strName	= _other.m_strName;
	m_fptPos	= _other.m_fptPos;
	m_fptScale	= _other.m_fptScale;
	m_pCollider = nullptr;
	m_pAnimator = nullptr;
	m_bActive = true;

	if (nullptr != _other.m_pCollider)
	{
		m_pCollider = new CCollider(*_other.m_pCollider);
		m_pCollider->m_pOwner = this;
	}
	if (nullptr != _other.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*_other.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}
}

CGameObject::~CGameObject()
{
	if (nullptr != m_pCollider)
	{
		delete m_pCollider;
	}
	if (nullptr != m_pAnimator)
	{
		delete m_pAnimator;
	}
}

void CGameObject::SetPos(fPoint _pos)
{
	m_fptPos = _pos;
}

void CGameObject::SetScale(fPoint _scale)
{
	m_fptScale = _scale;
}

void CGameObject::SetGroup(GROUP_GAMEOBJ _group)
{
	m_eGroup = _group;
}

void CGameObject::SetName(wstring _name)
{
	m_strName = _name;
}

fPoint CGameObject::GetPos()
{
	return m_fptPos;
}

fPoint CGameObject::GetScale()
{
	return m_fptScale;
}

GROUP_GAMEOBJ CGameObject::GetGroup()
{
	return m_eGroup;
}

wstring CGameObject::GetName()
{
	return m_strName;
}

bool CGameObject::ActiveSelf()
{
	return m_bActive;
}

CGameObject* CGameObject::GetObj()
{
	return this;
}

void CGameObject::SetActive(bool _bool)
{
	m_bActive = _bool;
}

void CGameObject::finalupdate()
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->finalupdate();
	}
}

void CGameObject::render()
{
	// 절대 위치를 넘기고, 랜더링 위치를 받아옴
	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(m_fptPos);

	// 카메라를 기준으로 그려져야하는 위치
	CRenderManager::getInst()->RenderRectangle(
		fptRenderPos.x - m_fptScale.x / 2,
		fptRenderPos.y - m_fptScale.y / 2,
		fptRenderPos.x + m_fptScale.x / 2,
		fptRenderPos.y + m_fptScale.y / 2);

	component_render();
}

void CGameObject::component_render()
{
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->render();
	}
	if (nullptr != m_pCollider && Debug())
	{
		m_pCollider->render();
	}
}

CCollider* CGameObject::GetCollider()
{
	return m_pCollider;
}

void CGameObject::CreateCollider()
{
	m_pCollider = new CCollider();
	m_pCollider->m_pOwner = this;
}

CAnimator* CGameObject::GetAnimator()
{
	return m_pAnimator;
}

void CGameObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
}
