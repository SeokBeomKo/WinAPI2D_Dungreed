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

	float m_fEnemyScaleOffset = 1.f;
	fPoint m_fptEnemyPosOffset = { 0,0 };
public:
	CEnemy();
	~CEnemy();
	CEnemy* Clone();

	CEnemyType* GetEnemyType();
	void SetEnemyScaleOffset(float _scaleOffset);
	void SetEnemyPosOffset(fPoint _posOffset);

	float GetEnemyScaleOffset();
	fPoint GetEnemyPosOffset();

	virtual void update();
	virtual void render();

	void OnCollision(CCollider* _pOther) override;
	void OnCollisionEnter(CCollider* _pOther) override;
	void OnCollisionExit(CCollider* _pOther) override;
};

//========================================
//## BigWhiteSkel						##
//========================================

class BigWhiteSkelEnemy : public CEnemy
{
private:
public:
	BigWhiteSkelEnemy();
	~BigWhiteSkelEnemy();
	BigWhiteSkelEnemy* Clone();

	void update() override;
	void render() override;
};