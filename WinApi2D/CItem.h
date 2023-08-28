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

	virtual void OnCollision(CCollider* _pOther);		// 재정의용 충돌중 가상함수
	virtual void OnCollisionEnter(CCollider* _pOther);	// 재정의용 충돌시 가상함수
	virtual void OnCollisionExit(CCollider* _pOther);	// 재정의용 탈충돌 가상함수
};

