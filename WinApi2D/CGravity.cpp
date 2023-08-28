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
	m_fTime += GRAVITY_FORCE * fDT;
	if (m_fTime > GRAVITY_POWER)
	{
		m_fTime = GRAVITY_POWER;
	}
	pos.y += m_fTime * fDT;
	m_pOwner->SetPos(pos);
}

void CGravity::SetSwitch(bool _switch)
{
	m_bIsGravity = _switch;
}

void CGravity::SetTime(float _time)
{
	m_fTime = _time;
}

float CGravity::GetTime()
{
	return m_fTime;
}

bool CGravity::CheckGravity()
{
	return m_bIsGravity;
}

