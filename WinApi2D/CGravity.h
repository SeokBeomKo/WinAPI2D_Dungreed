#pragma once

class CGameObject;

class CGravity
{
	friend class CGameObject;

private:
	CGameObject*	m_pOwner;
	bool			m_bIsGravity;
	float			m_fTime;
public:
	CGravity();
	~CGravity();

	virtual void finalupdate();
	void OnOffGravity(bool set, float time = 0);

	float GetTime();

	bool CheckGravity();
};

