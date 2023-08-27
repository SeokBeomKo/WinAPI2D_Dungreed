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

CD2DImage* CItem::GetImage()
{
	return m_pImg;
}

void CItem::Delete()
{
	DeleteObj(this);
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
