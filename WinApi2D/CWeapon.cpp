#include "framework.h"
#include "CWeapon.h"

#include "CPlayerAttack.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CPlayer.h"

//========================================
//## Weapon							    ##
//========================================

CWeapon::CWeapon()
{
}

CWeapon::CWeapon(const CWeapon& _other)
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

ShortSword::ShortSword(const ShortSword& _other)
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

ShortSword* ShortSword::Clone()
{
    return new ShortSword(*this);
}

void ShortSword::Init()
{
}

void ShortSword::use(fPoint _pos)
{
    m_pAttack = new CPlayerAttack();
    m_pAttack->Init(_pos);
    m_pAttackImg = CResourceManager::getInst()->LoadD2DImage(L"ShortSwordFX", L"texture\\weapon\\effect\\ShortSwordFX.png");
    m_pAttack->GetAnimator()->CreateAnimation(L"Attack", m_pAttackImg, fPoint(0.f, 0.f), fPoint(28.f, 40.f), fPoint(0.f, 40.f), 0.134f, 3, false, true, m_pAttack->GetDegree());
    m_pAttack->PlayVFX();
    m_pAttack->SetScale(fPoint(28.f, 40.f) * 3.f);
    m_pAttack->GetCollider()->SetScale(fPoint(40.f, 28.f) * 3.f);

    CreateObj(m_pAttack, GROUP_GAMEOBJ::ATTACK_PLAYER);
}

void ShortSword::update()
{
    SetGravity(!GetGrounded());
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

//========================================
//## PowerKatana						##
//========================================

PowerKatana::PowerKatana()
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PowerKatana", L"texture\\weapon\\PowerKatana.png");
    SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
    SetPos(fPoint(0.f, 0.f));
    SetName(L"PowerKatana");

    GetCollider()->SetScale(GetScale());
    GetCollider()->SetOffsetPos(fPoint(0.f, 0.f));
}

PowerKatana::PowerKatana(const PowerKatana& _other)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(L"PowerKatana", L"texture\\weapon\\PowerKatana.png");
    SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
    SetPos(fPoint(0.f, 0.f));
    SetName(L"PowerKatana");

    GetCollider()->SetScale(GetScale());
    GetCollider()->SetOffsetPos(fPoint(0.f, 0.f));
}

PowerKatana::~PowerKatana()
{
}

PowerKatana* PowerKatana::Clone()
{
    return new PowerKatana(*this);
}

void PowerKatana::Init()
{
}

void PowerKatana::use(fPoint _pos)
{
    m_pAttack = new CPlayerAttack();
    m_pAttack->Init(_pos);
    m_pAttackImg = CResourceManager::getInst()->LoadD2DImage(L"EXPowerKatanaSwingPlusFX", L"texture\\weapon\\effect\\EXPowerKatanaSwingPlusFX.png");
    m_pAttack->GetAnimator()->CreateAnimation(L"Attack", m_pAttackImg, fPoint(0.f, 0.f), fPoint(138.f, 164.f), fPoint(0.f, 164.f), 0.0333f, 12, false, true, m_pAttack->GetDegree());
    m_pAttack->PlayVFX();
    m_pAttack->SetScale(fPoint(138.f, 164.f) * 1.5f);
    m_pAttack->GetCollider()->SetScale(fPoint(164.f, 138.f) * 1.5f);

    CreateObj(m_pAttack, GROUP_GAMEOBJ::ATTACK_PLAYER);
}

void PowerKatana::update()
{
    SetGravity(!GetGrounded());
}

void PowerKatana::render()
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
