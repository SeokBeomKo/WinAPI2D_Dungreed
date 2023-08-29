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
	CEnemyStateMachine* m_pStateMachine;
	CEnemyType* m_pType;
public:
	CEnemy();
	~CEnemy();
	CEnemy* Clone();

	CEnemyType* GetEnemyType();

	void update();
	void render();

	void OnCollision(CCollider* _pOther) override;
	void OnCollisionEnter(CCollider* _pOther) override;
	void OnCollisionExit(CCollider* _pOther) override;
};
