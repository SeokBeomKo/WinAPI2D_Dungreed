#include "framework.h"
#include "CBackGround.h"

//========================================
//## Back_Ground					    ##
//========================================

CBack_Ground::CBack_Ground()
{
	m_pImg = nullptr;
	m_fptPos = {};
	m_fSpeed = 0.f;
}

CBack_Ground::CBack_Ground(float _speed)
	: CBack_Ground()
{
	m_fSpeed = _speed;
}

CBack_Ground::~CBack_Ground()
{
}

CBack_Ground* CBack_Ground::Clone()
{
	return nullptr;
}

void CBack_Ground::update()
{
}

void CBack_Ground::render()
{
    fPoint pos = fPoint(m_fptPos.x, m_fptPos.y);
    fPoint scale = GetScale();
    fPoint renderpos = CCameraManager::getInst()->GetRenderPos(pos);
    if (0 != m_fSpeed)
    {
        renderpos = pos + (renderpos - pos) / m_fSpeed;
    }
    else
    {
        renderpos = pos + (renderpos - pos);
    }

    CRenderManager::getInst()->RenderImage(
        m_pImg,
        renderpos.x,
        renderpos.y,
        renderpos.x + scale.x,
        renderpos.y + scale.y
    );
}

void CBack_Ground::Load(wstring strKey, wstring strPath, fPoint pos, float speed)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
    m_fptPos = pos;
    m_fSpeed = speed;
}

//========================================
//## ScrollBack_Ground				    ##
//========================================

CScrollBack_Ground::CScrollBack_Ground()
{
    m_pImg = nullptr;
    m_fVelocity = 0.f;

    m_fSetReturn = 0.f;
    m_fGetReturn = 0.f;
}

CScrollBack_Ground::~CScrollBack_Ground()
{
}

CScrollBack_Ground* CScrollBack_Ground::Clone()
{
    return new CScrollBack_Ground(*this);
}

void CScrollBack_Ground::update()
{
    fPoint pos = GetPos();

    pos.x += m_fVelocity * m_fvDir.x * fDT;
    pos.y += m_fVelocity * m_fvDir.y * fDT;

    SetPos(pos);

    if (pos.x < m_fSetReturn)
    {
        SetPos(fPoint(WINSIZEX / 2 + m_fGetReturn, WINSIZEY / 2));
    }
}

void CScrollBack_Ground::render()
{
    fPoint pos = GetPos();
    fPoint scale = GetScale();

    CRenderManager::getInst()->RenderImage(
        m_pImg,
        pos.x - scale.x / 2.f,
        pos.y - scale.y / 2.f,
        pos.x + scale.x / 2.f,
        pos.y + scale.y / 2.f
    );
}

void CScrollBack_Ground::Load(wstring strKey, wstring strPath, float velo, float setre, float getre, fPoint pos, float speed)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
    m_fVelocity = velo;
    m_fSetReturn = setre;
    m_fGetReturn = getre;
}
