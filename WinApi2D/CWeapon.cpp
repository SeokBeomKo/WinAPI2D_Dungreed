#include "framework.h"
#include "CWeapon.h"

#include "CCollider.h"
#include "CPlayer.h"

//========================================
//## Weapon							    ##
//========================================

CWeapon::CWeapon()
{
}

CWeapon::~CWeapon()
{
}

void CWeapon::OnCollision(CCollider* _pOther)
{
    CPlayer* pEntity = dynamic_cast<CPlayer*>(_pOther->GetObj());
    if (nullptr == pEntity)	return;                                 // 충돌한 플레이어를 잘 가져왔는지 ?
    if (GROUP_GAMEOBJ::PLAYER != pEntity->GetGroup())   return;     // 충돌한 플레이어의 그룹이 PLAYER 로 잘 설정되어있는지 ?
    if (nullptr != pEntity->GetCollWeapon()) return;                // 충돌한 플레이어와 충돌중인 무기 아이템이 있는지 ?
    
    pEntity->SetCollWeapon(this);
}

void CWeapon::OnCollisionEnter(CCollider* _pOther)
{
    CPlayer* pEntity = dynamic_cast<CPlayer*>(_pOther->GetObj());
    if (nullptr == pEntity)	return;                                 // 충돌한 플레이어를 잘 가져왔는지 ?
    if (GROUP_GAMEOBJ::PLAYER != pEntity->GetGroup())   return;     // 충돌한 플레이어의 그룹이 PLAYER 로 잘 설정되어있는지 ?
    if (nullptr != pEntity->GetCollWeapon()) return;                // 충돌한 플레이어와 충돌중인 무기 아이템이 있는지 ?
    
    pEntity->SetCollWeapon(this);
}

void CWeapon::OnCollisionExit(CCollider* _pOther)
{
    CPlayer* pEntity = dynamic_cast<CPlayer*>(_pOther->GetObj());
    if (nullptr == pEntity)	return;                                 // 충돌한 플레이어를 잘 가져왔는지 ?
    if (GROUP_GAMEOBJ::PLAYER != pEntity->GetGroup())   return;     // 충돌한 플레이어의 그룹이 PLAYER 로 잘 설정되어있는지 ?
    if (nullptr == pEntity->GetCollWeapon()) return;                // 충돌한 플레이어와 충돌중인 무기 아이템이 있는지 ?

    pEntity->SetCollWeapon(nullptr);
}

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
    SetGravity(!GetGrounded());
}
