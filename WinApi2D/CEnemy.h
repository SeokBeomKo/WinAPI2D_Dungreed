#pragma once

#include "CEntity.h"

class CD2DImage;
class CEnemyStateMachine;
class CEnemyType;

//========================================
//## Enemy								##
//========================================

class CEnemy : public CEntity
{
protected:
	CD2DImage* m_pImg;
	CEnemyType* m_pType;

	CEnemyStateMachine* m_pStateMachine;
public:
	CEnemy();
	~CEnemy();
	CEnemy* Clone();

	void Init(CD2DImage* _img, CEnemyType* _type);

	void SetEnemyType(CEnemyType* _type);
	CEnemyType* GetEnemyType();

	void update();
	void render();

	void OnCollision(CCollider* _pOther) override;
	void OnCollisionEnter(CCollider* _pOther) override;
	void OnCollisionExit(CCollider* _pOther) override;
};
