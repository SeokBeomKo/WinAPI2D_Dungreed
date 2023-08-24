#include "framework.h"
#include "CItem.h"

CItem::CItem()
{
	CreateGravity();

	CreateCollider();
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
