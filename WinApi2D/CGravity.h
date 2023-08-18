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
	void SetSwitch(bool _switch);
	void SetTime(float _time = 0);

	float GetTime();

	bool CheckGravity();
};

