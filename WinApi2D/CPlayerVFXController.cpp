#include "framework.h"
#include "CPlayerVFXController.h"
#include "CPlayerVFX.h"

CPlayerVFXController::CPlayerVFXController(CPlayer* _obj)
{
	m_mapVFX.insert(make_pair(L"JumpVFX", new CPlayerJumpVFX(_obj)));
	m_mapVFX.insert(make_pair(L"RunVFX", new CPlayerRunVFX(_obj)));
	m_mapVFX.insert(make_pair(L"DashVFX", new CPlayerDashVFX(_obj)));
}

CPlayerVFXController::~CPlayerVFXController()
{
	for (map<wstring, CPlayerVFX*>::iterator iter = m_mapVFX.begin(); iter != m_mapVFX.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	m_mapVFX.clear();
}

CPlayerVFX* CPlayerVFXController::GetVFX(wstring _name)
{
	map<wstring, CPlayerVFX*>::iterator iter = m_mapVFX.find(_name);
	if (m_mapVFX.end() == iter)
	{
		return nullptr;
	}
	return iter->second;
}
