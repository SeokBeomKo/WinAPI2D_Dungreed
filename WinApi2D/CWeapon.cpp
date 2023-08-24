#include "framework.h"
#include "CWeapon.h"

#include "CCollider.h"
//========================================
//## ShortSword							##
//========================================

ShortSword::ShortSword()
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(L"ShortSword", L"texture\\weapon\\ShortSword.png");
    SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
    SetPos(fPoint(0.f, 0.f));
    SetName(L"ShortSword");

    GetCollider()->SetScale(GetScale());
    GetCollider()->SetOffsetPos(fPoint(0.f, 0.f));
}

ShortSword::~ShortSword()
{
}

void ShortSword::use()
{
}

void ShortSword::render()
{
    fPoint pos = GetPos();
    fPoint renderpos = CCameraManager::getInst()->GetRenderPos(pos);
    fPoint scale = GetScale();

    CRenderManager::getInst()->RenderImage(
        m_pImg,
        renderpos.x - scale.x / 2.f,
        renderpos.y - scale.y / 2.f,
        renderpos.x + scale.x / 2.f,
        renderpos.y + scale.y / 2.f
    );

    component_render();
}

void ShortSword::update()
{
}

CWeapon::CWeapon()
{
}

CWeapon::~CWeapon()
{
}
