#pragma once

class CEntity;

class CGravity
{
	friend class CEntity;

protected:
	CEntity*		m_pOwner;
	bool			m_bIsGravity;
	float			m_fTime;
public:
	CGravity();
	~CGravity();

	virtual void finalupdate();
	void Set(bool set, float time = 0);

	float GetTime();

	bool CheckGravity();
};

