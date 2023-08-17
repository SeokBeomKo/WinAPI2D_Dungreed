#pragma once
#include "CGameObject.h"

class CGravity;

class CEntity : public CGameObject
{
private:
	CGravity* m_pGravity;	// 오브젝트 중력
public:
	CEntity();
	~CEntity();
	virtual CEntity* Clone();

	virtual void update() = 0;			// 반드시 상속받은 객체가 update를 구현하도록 순수가상함수로 선언
	virtual void finalupdate();			// 상속받는 클래스가 오버라이딩 할 수 없게 막는 final 키워드
	virtual void render();
	virtual void component_render();	// 컴포넌트들의 영역을 표시하기 위해

	void CreateGravity();				// 중력값 생성
	CGravity* GetGravity();				// 중력값 반환

	virtual void OnCollision(CCollider* _pOther) {}			// 재정의용 충돌중 가상함수
	virtual void OnCollisionEnter(CCollider* _pOther) {}	// 재정의용 충돌시 가상함수
	virtual void OnCollisionExit(CCollider* _pOther) {}		// 재정의용 탈충돌 가상함수
};

