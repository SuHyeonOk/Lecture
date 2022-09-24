#pragma once

#include "Component.h"
#include "Engine_Include.h"

BEGIN(Engine)

class ENGINE_DLL CGameObject : public CBase
{
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CGameObject(const CGameObject& rhs);
	virtual ~CGameObject();

public:
	// Get_Component는 어떤 레벨에서 호출하느냐에 따라 필요로하는 매개변수가 달라진다.
	CComponent*				Get_Component(const _tchar* pComponentTag, COMPONENTID eID);

public:
	virtual		HRESULT		Ready_Object(void);
	virtual		_int		Update_Object(const _float& fTimeDelta);
	virtual		void		LateUpdate_Object(void);
	virtual		void		Render_Obejct(void);

public:
	CComponent*				Find_Component(const _tchar* pComponentTag, COMPONENTID eID);

protected:
	LPDIRECT3DDEVICE9					m_pGraphicDev;
	map<const _tchar*, CComponent*>		m_mapComponent[ID_END];


public:
	virtual void	Free(void);

};

END
