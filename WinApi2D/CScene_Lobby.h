#pragma once
#include "CScene.h"

class CScene_Lobby : public CScene
{
private:
	fPoint m_fptPlayerPos;
public:
	CScene_Lobby();
	virtual ~CScene_Lobby();

	virtual void update();

	virtual void Enter();
	virtual void Exit();
};

