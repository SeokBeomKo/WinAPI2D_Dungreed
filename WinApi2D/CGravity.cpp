#include "framework.h"
#include "CGravity.h"

#include "CEntity.h"

CGravity::CGravity()
{
	m_pOwner		= nullptr;
	m_bIsGravity	= true;
	m_fTime			= 0;
}

CGravity::~CGravity()
{
}

void CGravity::finalupdate()
{
	if (!m_bIsGravity)
	{
		return;
	}

	fPoint pos = m_pOwner->GetPos();
	m_fTime += GRAVITY * fDT;
	if (m_fTime > 1200.f)
	{
		m_fTime = 1200.f;
	}
	pos.y += m_fTime * fDT;
	m_pOwner->SetPos(pos);
}

void CGravity::OnOffGravity(bool set, float time)
{
	m_bIsGravity = set;
	m_fTime = time;
}

float CGravity::GetTime()
{
	return m_fTime;
}

bool CGravity::CheckGravity()
{
	return m_bIsGravity;
}

