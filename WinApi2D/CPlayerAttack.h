#pragma once
#include "CGameObject.h"

class CPlayerAttack : public CGameObject
{
private:
	CD2DImage*			m_pImg;

	int					m_iDamage;			// 공격 데미지
	int					m_iRange;			// 공격 사거리 (플레이어와의 오프셋) : 생성위치
	float				m_fTimeFX;			// 공격 소멸 시간
	fPoint				m_fptDirFX;			// 이펙트 위치조정을 위한 방향

public:
	CPlayerAttack();
	CPlayerAttack(CD2DImage* _img, int _dmg, int _range, fPoint _dir, float _time = 0.4f);
	~CPlayerAttack();

	void Init(fPoint _ownerPos, const wstring& strName, CD2DImage* tex, fPoint lt, fPoint slice, fPoint step, float duration, UINT frmCount, bool reverse, bool rotate, float pos);
	int GetDamage();

	virtual void update();
	virtual void render();
};

