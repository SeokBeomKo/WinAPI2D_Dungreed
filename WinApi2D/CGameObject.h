#pragma once

class CCollider;
class CAnimator;

class CGameObject
{
	friend class CEventManager;

private:
	wstring m_strName;			// 오브젝트 이름
	fPoint m_fptPos;			// 오브젝트 좌표
	fPoint m_fptScale;			// 오브젝트 크기

	// Component
	CCollider* m_pCollider;		// 오브젝트 충돌체
	CAnimator* m_pAnimator;		// 오브젝트 애니메이터

	bool m_bActive;					// 오브젝트 활성화 여부
	void SetActive(bool _bool);		// 오브젝트 활성화 여부 체크
public:
	CGameObject();
	CGameObject(const CGameObject& other);
	~CGameObject();
	virtual CGameObject* Clone() = 0;

	void SetPos(fPoint pos);
	void SetScale(fPoint scale);
	void SetName(wstring name);

	fPoint GetPos();
	fPoint GetScale();
	wstring GetName();

	bool ActiveSelf();					// 오브젝트 활성화 여부

	virtual void update() = 0;			// 반드시 상속받은 객체가 update를 구현하도록 순수가상함수로 선언
	virtual void finalupdate();			// 상속받는 클래스가 오버라이딩 할 수 없게 막는 final 키워드
	virtual void render();
	virtual void component_render();	// 컴포넌트 표시

	void CreateAnimator();					// 애니메이터 생성
	CAnimator* GetAnimator();				// 애니메이터 반환

	void CreateCollider();					// 충돌체 생성
	CCollider* GetCollider();				// 충돌체 반환

	virtual void OnCollision(CCollider* _pOther) {}			// 재정의용 충돌중 가상함수
	virtual void OnCollisionEnter(CCollider* _pOther) {}	// 재정의용 충돌시 가상함수
	virtual void OnCollisionExit(CCollider* _pOther) {}		// 재정의용 탈충돌 가상함수

};

