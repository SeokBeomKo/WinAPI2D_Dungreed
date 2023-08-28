#pragma once
#include "CGameObject.h"

class CPlayerAttack : public CGameObject
{
private:
	CD2DImage*			m_pImg;

	int					m_iDamage;			// ���� ������
	int					m_iRange;			// ���� ��Ÿ� (�÷��̾���� ������) : ������ġ
	float				m_fCurTimeFX;		// ���� �Ҹ� �ð�
	float				m_fMaxTimeFX;		//
	fPoint				m_fptDirFX;			// ����Ʈ ��ġ������ ���� ����

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
