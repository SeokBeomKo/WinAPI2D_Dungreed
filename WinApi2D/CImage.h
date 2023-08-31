#pragma once
#include "CGameObject.h"

class CImage : public CGameObject
{
private:
	CD2DImage* m_pImg;

	fPoint m_fptPos;
public:
	CImage();
	~CImage();

	virtual CImage* Clone();
	virtual void update();
	virtual void render();

	virtual void Load(wstring _strKey, wstring _strPath, fPoint _pos = { 0,0 }, float _scale = 4.f);
};
