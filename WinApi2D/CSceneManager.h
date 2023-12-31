#pragma once

class CScene;

class CSceneManager
{
	SINGLETON(CSceneManager);
	
	friend class CEventManager;

private:
	CScene* m_arrScene[(int)GROUP_SCENE::SIZE];		// ��ü �� ���
	CScene* m_pCurScene;							// ���� ��

	void ChangeScene(GROUP_SCENE scene);			// �� ��ȯ

	bool m_bDebug;							// ����׸��
public:
	void update();
	void render();
	void init();

	void SetDebug();					
	bool GetDebug();

	CScene* GetCurScene();							//���� �� ��ȯ
};

