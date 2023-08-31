#pragma once
#include "CScene.h"

class SCene_Title : public CScene
{
private:
public:
	SCene_Title();
	virtual ~SCene_Title();

	virtual void update();

	virtual void Enter();
	virtual void Exit();
};

