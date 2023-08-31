#pragma once

#include "CGameObject.h"

class CPlayer;
class CD2DImage;

//========================================
//## VFX								##
//========================================

class CPlayerVFX : public CGameObject
{
protected:
	CPlayer* m_pOwner;

	CD2DImage* m_pImg;

	wstring m_wstrName;
	float m_fPosYOffset;
public:
	CPlayerVFX(CPlayer* _obj);
	CPlayerVFX(const CPlayerVFX& _other);
	~CPlayerVFX();
	CPlayerVFX* Clone() override;

	virtual void update();
	virtual void render();

	void PlayVFX(wstring _name, bool _flip = false);
	virtual void SetOffset() = 0;
};

//========================================
//## Run								##
//========================================

class CPlayerRunVFX : public CPlayerVFX
{
private:
public:
	CPlayerRunVFX(CPlayer* _obj);
	CPlayerRunVFX(const CPlayerRunVFX& _other);
	~CPlayerRunVFX();

	void SetOffset() override;
};

//========================================
//## Jump								##
//========================================

class CPlayerJumpVFX : public CPlayerVFX
{
private:
public:
	CPlayerJumpVFX(CPlayer* _obj);
	CPlayerJumpVFX(const CPlayerJumpVFX& _other);
	~CPlayerJumpVFX();

	void SetOffset() override;
};

//========================================
//## Dash								##
//========================================

class CPlayerDashVFX : public CPlayerVFX
{
private:
public:
	CPlayerDashVFX(CPlayer* _obj);
	CPlayerDashVFX(const CPlayerDashVFX& _other);
	~CPlayerDashVFX();

	void SetOffset() override;
};

