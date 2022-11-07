#pragma once

#include "Base.h"

/* 게임내에 필요한 객체들을 내 기준(CLayer)에 따라 나누어 보관한다. */
/* 객체들을 나누어 저장하고 있는 CLayer들을 보관하는 클래스이다. */
/* 모든 객체들의 갱신(Tick, Late_Tick)을 담당한다. */

BEGIN(Engine)

class CObject_Manager final : public CBase
{
	DECLARE_SINGLETON(CObject_Manager);
private:
	CObject_Manager();
	virtual ~CObject_Manager() = default;

public:
	// Engine : GameInstance의 Initialize_Engine()에서 돌아간다.
	HRESULT Reserve_Manager(_uint iNumLevels);
	// Engine : GameInstance의 Clear_Level()에서 돌아간다.
	HRESULT Clear(_uint iLevelIndex);

public:
	// Client : 클라이언트에서 [원형]을 생성할 때 사용
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObject* pPrototype); 
	// Client : 클라이언트에서 [사본]을 생성할 때 사용
	HRESULT Clone_GameObject(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg = nullptr);
	// Engine : GameInstace의 Tick_Engine()에서 돌아간다.
	void Tick(_double TimeDelta);
	void Late_Tick(_double TimeDelta);

private: /* 원형객체들을ㅇ 모아놓는다. */
	map<const _tchar*, class CGameObject*>			m_Prototypes;
	typedef map<const _tchar*, class CGameObject*>	PROTOTYPES;

private: /* 사본객체들을 보관하기위한 컨테이너. */
	map<const _tchar*, class CLayer*>*			m_pLayers = nullptr;
	typedef map<const _tchar*, class CLayer*>	LAYERS;
	_uint										m_iNumLevels = 0;

private:
	class CGameObject* Find_Prototype(const _tchar* pPrototypeTag);
	class CLayer* Find_Layer(_uint iLevelIndex, const _tchar* pLayerTag);

public:
	virtual void Free() override;
};

END