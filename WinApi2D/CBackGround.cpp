#include "framework.h"
#include "CBackGround.h"

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
