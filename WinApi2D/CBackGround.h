#pragma once
#include "CGameObject.h"
class CBack_Ground : public CGameObject
{
private:
	CD2DImage* m_pImg;

	fPoint m_fptPos;
	float m_fSpeed;

public:
	CBack_Ground();
	CBack_Ground(float _speed);
	~CBack_Ground();

	virtual CBack_Ground* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath, fPoint pos = {0,0}, float speed = 0);
};

