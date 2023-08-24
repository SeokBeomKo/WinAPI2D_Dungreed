#include "framework.h"
#include "CImage.h"

CImage::CImage()
{
    m_pImg = nullptr;
    m_fptPos = {};
}

CImage::~CImage()
{
}

CImage* CImage::Clone()
{
    return nullptr;
}

void CImage::update()
{
}

void CImage::render()
{
    fPoint pos = fPoint(WINSIZEX / 2, WINSIZEY / 2);
    fPoint scale = GetScale();

    CRenderManager::getInst()->RenderImage(
        m_pImg,
        pos.x - scale.x / 2.f,
        pos.y - scale.y / 2.f,
        pos.x + scale.x / 2.f,
        pos.y + scale.y / 2.f
    );
}

void CImage::Load(wstring strKey, wstring strPath, fPoint pos, float scale)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
}
