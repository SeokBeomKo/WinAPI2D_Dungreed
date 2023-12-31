#pragma once

class CGameObject;
class CAnimation;
class CD2DImage;

class CAnimator
{
	friend class CGameObject;

private:
	map<wstring, CAnimation*>	m_mapAni;
	CAnimation*					m_pCurAni;
	CGameObject*				m_pOwner;

public:
	CAnimator();
	~CAnimator();

	CGameObject* GetObj();

	void update();
	void render();

	void CreateAnimation(const wstring& strName, CD2DImage* tex, fPoint lt, fPoint slice,
		fPoint step, float duration, UINT frmCount, bool reverse = false, bool rotate = false, float pos = 0);
	CAnimation* FindAnimation(const wstring& strName);
	void Play(const wstring& strName, bool _flip = false);
};

