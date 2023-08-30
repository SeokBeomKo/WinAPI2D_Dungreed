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

	float m_fVelocity = 100.f;	// 이동속도
	int m_iDirection = 1;		// 방향 : 1 우, -1 좌

	float m_fEnemyScaleOffset = 1.f;
	fPoint m_fptEnemyPosOffset = { 0,0 };
public:
	CEnemy();
	~CEnemy();
	CEnemy* Clone();


	CEnemyType* GetEnemyType();
	void SetEnemyScaleOffset(float _scaleOffset);
	void SetEnemyPosOffset(fPoint _posOffset);
	void SetEnemyVelocity(float _velocity);
	void SetEnemyDirection(int _dir = 1);

	float GetEnemyScaleOffset();
	fPoint GetEnemyPosOffset();
	float GetEnemyVelocity();
	int GetEnemyDirection();

	virtual void Init() = 0;
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

	void Init() override;
	void update() override;
	void render() override;
};