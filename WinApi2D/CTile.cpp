#include "framework.h"
#include "CTile.h"
#include "CD2DImage.h"

#include "CCollider.h"
#include "CGravity.h"

#include "CEntity.h"

CTile::CTile()
{
	m_pImg = nullptr;
	m_iX = 0;
	m_iY = 0;
	m_iIdx = 0;
	m_group = GROUP_TILE::NONE;
	SetScale(fPoint(SIZE_TILE, SIZE_TILE));
}

CTile::~CTile()
{
}

CTile* CTile::Clone()
{
	return new CTile(*this);
}

void CTile::update()
{
}

void CTile::render()
{
	if (nullptr == m_pImg)
	{
		return;
	}

	UINT iWidth = m_pImg->GetWidth();
	UINT iHeight = m_pImg->GetHeight();

	UINT iMaxRow = iHeight / SIZE_TILE;
	UINT iMaxCol = iWidth / SIZE_TILE;

	UINT iCurRow = (m_iIdx / iMaxCol) % iMaxRow;
	UINT iCurCol = (m_iIdx % iMaxCol);

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(GetPos());
	fPoint fptScale = GetScale();

	if (0 != m_iIdx)
	{
		CRenderManager::getInst()->RenderFrame(
			m_pImg,
			fptRenderPos.x,
			fptRenderPos.y,
			fptRenderPos.x + fptScale.x,
			fptRenderPos.y + fptScale.y,
			iCurCol * fptScale.x,
			iCurRow * fptScale.y,
			(iCurCol + 1) * fptScale.x,
			(iCurRow + 1) * fptScale.y
		);
	}

	component_render();
}

void CTile::SetD2DImage(CD2DImage* pImg)
{
	m_pImg = pImg;
}

void CTile::SetImgIdx(UINT idx)
{
	m_iIdx = idx;
}

void CTile::SetX(int x)
{
	m_iX = x;
}

void CTile::SetY(int y)
{
	m_iY = y;
}

void CTile::SetGroup(GROUP_TILE group)
{
	m_group = group;
}

int CTile::GetIdx()
{
	return m_iIdx;
}

int CTile::GetX()
{
	return m_iX;
}

int CTile::GetY()
{
	return m_iY;
}

GROUP_TILE CTile::GetGroup()
{
	return m_group;
}


void CTile::Save(FILE* pFile)
{
	fwrite(&m_iX, sizeof(int), 1, pFile);
	fwrite(&m_iY, sizeof(int), 1, pFile);
	fwrite(&m_iIdx, sizeof(int), 1, pFile);

	int group = (int)m_group;
	fwrite(&group, sizeof(int), 1, pFile);
}

void CTile::Load(FILE* pFile)
{
	fread(&m_iX, sizeof(int), 1, pFile);
	fread(&m_iY, sizeof(int), 1, pFile);
	fread(&m_iIdx, sizeof(int), 1, pFile);

	int group;
	fread(&group, sizeof(int), 1, pFile);
	m_group = (GROUP_TILE)group;
}

void CTile::OnCollisionEnter(CCollider* pOther)
{
	CEntity* pEntity = dynamic_cast<CEntity*>(pOther->GetObj());
	if (nullptr == pEntity)	return;

	switch (this->GetGroup())
	{
	case GROUP_TILE::GROUND:
		pEntity->AddGrounded();
		pEntity->m_ftempY = (this->GetPosY() - (this->GetScale().y + pEntity->GetScale().y) / 4 - 1.9f); // TODO : 1.5f 오프셋값
		break;
	case GROUP_TILE::PLATFORM:
		if (pEntity->GetPassPlatform()) break;
		pEntity->AddGrounded();
		break;
	default:
		break;
	}

	if (this->GetGroup() == GROUP_TILE::GROUND)
	{
		
	}
	else if (this->GetGroup() == GROUP_TILE::PLATFORM)
	{
		
	}
}

void CTile::OnCollision(CCollider* pOther)
{
	CEntity* pEntity = dynamic_cast<CEntity*>(pOther->GetObj());
	if (nullptr == pEntity)	return;

	if (this->GetGroup() == GROUP_TILE::GROUND)
	{
		pEntity->SetPosY(pEntity->m_ftempY);
	}
}

void CTile::OnCollisionExit(CCollider* pOther)
{
	CEntity* pEntity = dynamic_cast<CEntity*>(pOther->GetObj());
	if (nullptr == pEntity)	return;

	switch (this->GetGroup())
	{
	case GROUP_TILE::GROUND:
		pEntity->RemoveGrounded();
		break;
	case GROUP_TILE::PLATFORM:
		if (pEntity->GetGrounded())	// Entity 가 땅에 있었을 때만 카운트 --
		{
			pEntity->RemoveGrounded();
		}
		break;
	default:
		break;
	}

	if (this->GetGroup() == GROUP_TILE::GROUND)
	{

	}
}
