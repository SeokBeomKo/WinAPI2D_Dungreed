#pragma once

#include "CEntity.h"

class CD2DImage;
class CEnemyStateMachine;

//========================================
//## Enemy								##
//========================================

class CEnemy : public CEntity
{
protected:
	CEnemyStateMachine* m_pStateMachine;
public:
	CEnemy();
	~CEnemy();
	CEnemy* Clone() = 0;

	void update() = 0;
	void render() = 0;

	void OnCollision(CCollider* _pOther) override;
	void OnCollisionEnter(CCollider* _pOther) override;
	void OnCollisionExit(CCollider* _pOther) override;
};

//========================================
//## GroundEnemy						##
//========================================

class CGroundEnemy : public CEnemy
{
private:

public:
	CGroundEnemy();
	~CGroundEnemy();
	CGroundEnemy* Clone() override;

	void update() override;
	void render() override;
};

//========================================
//## FlyEnemy							##
//========================================

class CFlyEnemy : public CEnemy
{
private:

public:
	CFlyEnemy();
	~CFlyEnemy();
	CFlyEnemy* Clone() override;

	void update() override;
	void render() override;
};
