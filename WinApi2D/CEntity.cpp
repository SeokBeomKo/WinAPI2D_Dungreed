#include "framework.h"
#include "CEntity.h"

#include "CGravity.h"
#include "CCollider.h"

CEntity::CEntity()
{
	m_pGravity = nullptr;
	m_bIsPass = false;
	m_iGrounded = 0;

	m_foffsetY = 0.f;
}

CEntity::CEntity(const CEntity& _other)
{
	m_bIsPass = false;
	m_iGrounded = 0;

	m_foffsetY = 0.f;
	if (nullptr != _other.m_pGravity)
	{
		m_pGravity = new CGravity(*_other.m_pGravity);
		m_pGravity->m_pOwner = this;
	}
}

CEntity::~CEntity()
{
	if (nullptr != m_pGravity)
	{
		delete m_pGravity;
	}
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

void CEntity::SetPassPlatform(bool _set)
{
	m_bIsPass = _set;
}

bool CEntity::GetPassPlatform()
{
	return m_bIsPass;
}

void CEntity::AddGrounded()
{
	m_iGrounded++;
}

void CEntity::RemoveGrounded()
{
	m_iGrounded--;
}

void CEntity::SetGrounded(int _set)
{
	m_iGrounded = _set;
}

bool CEntity::GetGrounded()
{
	return m_iGrounded != 0;
}

void CEntity::CreateGravity()
{
	m_pGravity = new CGravity;
	m_pGravity->m_pOwner = this;
}

void CEntity::InitGravity()
{
	m_pGravity->SetTime();
}

void CEntity::SetGravity(bool _bGravity)
{
	if (nullptr == m_pGravity)	return;

	m_pGravity->SetSwitch(_bGravity);
}

CGravity* CEntity::GetGravity()
{
	return m_pGravity;
}
