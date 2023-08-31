#pragma once

class CPlayer;
class CPlayerVFX;

class CPlayerVFXController
{
private:
	map<wstring, CPlayerVFX*> m_mapVFX;

public:
	CPlayerVFXController(CPlayer* _obj);
	~CPlayerVFXController();

	CPlayerVFX* GetVFX(wstring _name);
};

