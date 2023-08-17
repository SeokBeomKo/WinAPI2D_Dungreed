#include "framework.h"
#include "CEntity.h"
#include "CGravity.h"

CEntity::CEntity()
{
}

CEntity::~CEntity()
{
}

CEntity* CEntity::Clone()
{
	return nullptr;
}

void CEntity::finalupdate()
{
}

void CEntity::render()
{
}

void CEntity::component_render()
{
}

void CEntity::CreateGravity()
{
	m_pGravity = new CGravity;
	m_pGravity->m_pOwner = this;
}

CGravity* CEntity::GetGravity()
{
	return m_pGravity;
}
