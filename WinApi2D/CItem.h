#pragma once

#include "CEntity.h"

class CD2DImage;

class CItem : public CEntity
{
protected:
	CD2DImage* m_pImg;

public:
	CItem();
	~CItem();
	virtual CItem* Clone() = 0;

	CD2DImage* GetImage();
	virtual void Delete();

	virtual void update() = 0;
	virtual void render() = 0;

	virtual void OnCollision(CCollider* _pOther);		// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionEnter(CCollider* _pOther);	// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionExit(CCollider* _pOther);	// �����ǿ� Ż�浹 �����Լ�
};
