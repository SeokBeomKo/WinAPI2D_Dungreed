#include "framework.h"
#include "CItem.h"

CItem::CItem()
{
	m_pImg = nullptr;
	CreateCollider();
	CreateGravity();
}

CItem::~CItem()
{
}

void CItem::OnCollision(CCollider* _pOther)
{
}

void CItem::OnCollisionEnter(CCollider* _pOther)
{
}

void CItem::OnCollisionExit(CCollider* _pOther)
{
}
