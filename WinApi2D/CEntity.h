#pragma once

#include "CGameObject.h"

class CGravity;

class CEntity : public CGameObject
{
private:
	int m_iGrounded;		// ������Ʈ�� �浹���� ��Ÿ��
protected:	// Component
	CGravity* m_pGravity;	// ������Ʈ �߷�

public:
	CEntity();
	~CEntity();
	virtual CEntity* Clone();

	virtual CEntity* GetObj();

	virtual void update() = 0;			// �ݵ�� ��ӹ��� ��ü�� update�� �����ϵ��� ���������Լ��� ����
	virtual void finalupdate();
	virtual void render();
	
	void AddGrounded();
	void RemoveGrounded();
	bool GetGrounded();

	void CreateGravity();				// �߷°� ����
	void InitGravity();					// �߷� �� �ʱ�ȭ
	void SetGravity(bool _bGravity);	// �߷� ����ġ
	CGravity* GetGravity();				// �߷°� ��ȯ

	virtual void OnCollision(CCollider* _pOther) {}			// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionEnter(CCollider* _pOther) {}	// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionExit(CCollider* _pOther) {}		// �����ǿ� Ż�浹 �����Լ�
};
