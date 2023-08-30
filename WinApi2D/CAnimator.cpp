#include "framework.h"
#include "CAnimator.h"
#include "CAnimation.h"

CAnimator::CAnimator()
{
	m_pCurAni = nullptr;
	m_pOwner = nullptr;
}

CAnimator::~CAnimator()
{
	for (map<wstring, CAnimation*>::iterator iter = m_mapAni.begin(); iter != m_mapAni.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	m_mapAni.clear();
}

CGameObject* CAnimator::GetObj()
{
	return m_pOwner;
}

void CAnimator::update()
{
	if (nullptr != m_pCurAni)
	{
		m_pCurAni->update();
	}
}

void CAnimator::render()
{
	if (nullptr != m_pCurAni)
	{
		m_pCurAni->render();
	}
}

void CAnimator::CreateAnimation(const wstring& strName, CD2DImage* tex, fPoint lt, fPoint slice, fPoint step, float duration, UINT frmCount, bool reverse, bool rotate, float pos)
{
	CAnimation* pAni = FindAnimation(strName);
	assert(nullptr == pAni);

	pAni = new CAnimation;

	pAni->SetName(strName);
	pAni->m_pAnimator = this;
	pAni->Create(tex, lt, slice, step, duration, frmCount);
	pAni->m_bFlip = false;
	pAni->m_bRotate = rotate;
	pAni->m_fPlayerPos = pos;

	m_mapAni.insert(make_pair(strName, pAni));
}

CAnimation* CAnimator::FindAnimation(const wstring& strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAni.find(strName);

	if (iter == m_mapAni.end())
	{
		return nullptr;
	}
	return iter->second;
}

void CAnimator::Play(const wstring& strName, bool _flip)
{
	m_pCurAni = FindAnimation(strName);
	m_pCurAni->m_bFlip = _flip;
}

bool CAnimator::IsAnimationFinished() const {
	if (m_pCurAni == nullptr) {
		return true; // 현재 애니메이션이 없으면 종료된 것으로 간주합니다.
	}

	// 현재 애니메이션의 현재 프레임 인덱스와 전체 프레임 개수를 비교하여 체크합니다.
	return m_pCurAni->GetFrameIndex() == m_pCurAni->GetFrameCount() - 1;
}
