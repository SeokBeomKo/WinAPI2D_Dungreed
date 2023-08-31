#pragma once
#include "CGameObject.h"

//========================================
//## Back_Ground					    ##
//========================================

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

//========================================
//## ScrollBack_Ground				    ##
//========================================

class CScrollBack_Ground : public CGameObject
{
private:
	CD2DImage* m_pImg;

	fVec2 m_fvDir = fVec2(-1, 0);	// 움직이는 방향
	float m_fVelocity;				// 움직이는 속도

	float m_fSetReturn;				// 리턴 시작할 위치
	float m_fGetReturn;				// 리턴 할 위치
public:
	CScrollBack_Ground();
	~CScrollBack_Ground();

	virtual CScrollBack_Ground* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath, float velo, float setre, float getre, fPoint pos = { 0,0 }, float speed = 0);
};