#pragma once
#include "CScene.h"

class CScene_Lobby : public CScene
{
public:
	CScene_Lobby();
	virtual ~CScene_Lobby();

	virtual void update();

	virtual void Enter();
	virtual void Exit();
};

