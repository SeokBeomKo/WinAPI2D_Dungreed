#include "framework.h"
#include "CEntity.h"

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
}

CGravity* CEntity::GetGravity()
{
	return nullptr;
}
