#include "framework.h"
#include "CButtonUI.h"

//========================================
//## ButtonUI						    ##
//========================================

CButtonUI::CButtonUI()
	: CUI(false)
{
	m_pFunc = nullptr;
	m_pParam1 = 0;
	m_pParam2 = 0;
	m_pImg = nullptr;
	m_strText = L"";
}

CButtonUI::~CButtonUI()
{
}

CButtonUI* CButtonUI::Clone()
{
	return new CButtonUI(*this);
}

void CButtonUI::render()
{
	CUI::render();

	if (m_strText.size() > 0)
	{
		CRenderManager::getInst()->RenderText(
			m_strText,
			GetFinalPos().x,
			GetFinalPos().y,
			GetFinalPos().x + GetScale().x,
			GetFinalPos().y + GetScale().y,
			20.f
		);
	}

	if (nullptr != m_pImg)
	{
		CRenderManager::getInst()->RenderImage(
			m_pImg,
			GetFinalPos().x,
			GetFinalPos().y,
			GetFinalPos().x + GetScale().x,
			GetFinalPos().y + GetScale().y
		);
	}
}

void CButtonUI::MouseOn()
{
}

void CButtonUI::MouseLbtnDown()
{
}

void CButtonUI::MouseLbtnUp()
{
}

void CButtonUI::MouseLbtnClicked()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_pParam1, m_pParam2);
	}
}

void CButtonUI::SetImage(CD2DImage* img)
{
	m_pImg = img;
}

void CButtonUI::SetText(const wstring& str)
{
	m_strText = str;
}

void CButtonUI::SetClickedCallBack(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2)
{
	m_pFunc = pFunc;
	m_pParam1 = param1;
	m_pParam2 = param2;
}

//========================================
//## TitleButtonUI					    ##
//========================================

CTitleButtonUI::CTitleButtonUI()
{
	pimg = nullptr;

	m_strOnKey = L"";
	m_strOnPath = L"";
	m_strOffKey = L"";
	m_strOffPath = L"";
}

CTitleButtonUI::~CTitleButtonUI()
{
}

void CTitleButtonUI::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();

	if (IsMouseOn())
	{
		pimg = CResourceManager::getInst()->LoadD2DImage(m_strOnKey, m_strOnPath);
		CRenderManager::getInst()->RenderImage(
			pimg,
			pos.x,
			pos.y,
			pos.x + scale.x,
			pos.y + scale.y
		);
	}
	else
	{
		pimg = CResourceManager::getInst()->LoadD2DImage(m_strOffKey, m_strOffPath);
		CRenderManager::getInst()->RenderImage(
			pimg,
			pos.x,
			pos.y,
			pos.x + scale.x,
			pos.y + scale.y
		);
	}
}

void CTitleButtonUI::Load(wstring strOffKey, wstring strOffPath, wstring strOnKey, wstring strOnPath)
{
	m_strOffKey = strOffKey;
	m_strOffPath = strOffPath;
	m_strOnKey = strOnKey;
	m_strOnPath = strOnPath;

	pimg = CResourceManager::getInst()->LoadD2DImage(strOffKey, strOffPath);
	SetScale(fPoint(pimg->GetWidth() * 4.f, pimg->GetHeight() * 4.f));
}
