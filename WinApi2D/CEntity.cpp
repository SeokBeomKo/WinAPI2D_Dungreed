#include "framework.h"
#include "CEntity.h"

#include "CGravity.h"
#include "CCollider.h"

CEntity::CEntity()
{
	m_pGravity = nullptr;
}

CEntity::~CEntity()
{
}

CEntity* CEntity::Clone()
{
	return nullptr;
}

CEntity* CEntity::GetObj()
{
	return this;
}

void CEntity::finalupdate()
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->finalupdate();
	}
	if (nullptr != m_pGravity)
	{
		m_pGravity->finalupdate();
	}
}

void CEntity::render()
{
	//component_render();
}

void CEntity::CreateGravity()
{
	m_pGravity = new CGravity;
	m_pGravity->m_pOwner = this;
}

void CEntity::SetGravity(bool _bGravity)
{
	if (nullptr == m_pGravity)	return;

	m_pGravity->Set(_bGravity);
}

CGravity* CEntity::GetGravity()
{
	return m_pGravity;
}
