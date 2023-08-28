#pragma once
#include "CGameObject.h"

class CPlayerAttack : public CGameObject
{
private:
	CD2DImage*			m_pImg;

	int					m_iDamage;			// 공격 데미지
	int					m_iRange;			// 공격 사거리 (플레이어와의 오프셋) : 생성위치
	float				m_fCurTimeFX;		// 공격 소멸 시간
	float				m_fMaxTimeFX;		//
	fPoint				m_fptDirFX;			// 이펙트 위치조정을 위한 방향

public:
	CPlayerAttack();
	CPlayerAttack(CD2DImage* _img, int _dmg, int _range, fPoint _dir, float _time = 0.4f);
	~CPlayerAttack();
	virtual CPlayerAttack* Clone() { return this; }

	void Init(fPoint _pos);
	int GetDamage();

	float GetDegree();

	virtual void update();
	virtual void render();
};

