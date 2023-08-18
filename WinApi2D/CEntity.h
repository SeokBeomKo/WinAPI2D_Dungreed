#pragma once

#include "CGameObject.h"

class CGravity;

class CEntity : public CGameObject
{
private:
	int m_iGrounded;		// 오브젝트가 충돌중인 땅타일
protected:	// Component
	CGravity* m_pGravity;	// 오브젝트 중력

public:
	CEntity();
	~CEntity();
	virtual CEntity* Clone();

	virtual CEntity* GetObj();

	virtual void update() = 0;			// 반드시 상속받은 객체가 update를 구현하도록 순수가상함수로 선언
	virtual void finalupdate();
	virtual void render();
	
	void AddGrounded();
	void RemoveGrounded();
	bool GetGrounded();

	void CreateGravity();				// 중력값 생성
	void InitGravity();					// 중력 힘 초기화
	void SetGravity(bool _bGravity);	// 중력 스위치
	CGravity* GetGravity();				// 중력값 반환

	virtual void OnCollision(CCollider* _pOther) {}			// 재정의용 충돌중 가상함수
	virtual void OnCollisionEnter(CCollider* _pOther) {}	// 재정의용 충돌시 가상함수
	virtual void OnCollisionExit(CCollider* _pOther) {}		// 재정의용 탈충돌 가상함수
};

