#pragma once
#include "CScene.h"

class CEntity;

class CScene_Lobby : public CScene
{
private:
	fPoint m_fptPlayerPos;
	CEntity* m_pTarget;
public:
	CScene_Lobby();
	virtual ~CScene_Lobby();

	virtual void update();

	void SetTarget(CEntity* _target);
	CEntity* GetTarget();

	virtual void Enter();
	virtual void Exit();
};

