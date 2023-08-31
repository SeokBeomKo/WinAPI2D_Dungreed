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

void CImage::Load(wstring _strKey, wstring _strPath, fPoint _pos, float _scale)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(_strKey, _strPath);
    SetPos(_pos);
    SetScale(fPoint(m_pImg->GetWidth() * _scale, m_pImg->GetHeight() * _scale));
}
