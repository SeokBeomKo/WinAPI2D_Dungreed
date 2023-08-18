#pragma once

class CCollider;
class CAnimator;

class CGameObject
{
	friend class CEventManager;

private:
	GROUP_GAMEOBJ	m_eGroup;	// ������Ʈ �׷� (���̾�)

	wstring m_strName;			// ������Ʈ �̸�
	fPoint m_fptPos;			// ������Ʈ ��ǥ
	fPoint m_fptScale;			// ������Ʈ ũ��

	bool m_bActive;					// ������Ʈ Ȱ��ȭ ����

protected:	// Component
	CCollider* m_pCollider;		// ������Ʈ �浹ü
	CAnimator* m_pAnimator;		// ������Ʈ �ִϸ�����

public:
	CGameObject();
	CGameObject(const CGameObject& _other);
	~CGameObject();
	virtual CGameObject* Clone() = 0;

	void SetActive(bool _bool);		// ������Ʈ Ȱ��ȭ ���� ����
	void SetGroup(GROUP_GAMEOBJ _group);
	void SetName(wstring _name);
	void SetPos(fPoint _pos);
	void SetScale(fPoint _scale);

	bool ActiveSelf();					// ������Ʈ Ȱ��ȭ ����
	GROUP_GAMEOBJ GetGroup();
	wstring GetName();
	fPoint GetPos();
	fPoint GetScale();


	virtual CGameObject* GetObj();

	virtual void update() = 0;			// �ݵ�� ��ӹ��� ��ü�� update�� �����ϵ��� ���������Լ��� ����
	virtual void finalupdate();			// ��ӹ޴� Ŭ������ �������̵� �� �� ���� ���� final Ű����
	virtual void render();
	virtual void component_render();	// ������Ʈ ǥ��

	void CreateAnimator();					// �ִϸ����� ����
	CAnimator* GetAnimator();				// �ִϸ����� ��ȯ

	void CreateCollider();					// �浹ü ����
	CCollider* GetCollider();				// �浹ü ��ȯ

	virtual void OnCollision(CCollider* _pOther) {}			// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionEnter(CCollider* _pOther) {}	// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionExit(CCollider* _pOther) {}		// �����ǿ� Ż�浹 �����Լ�

};
