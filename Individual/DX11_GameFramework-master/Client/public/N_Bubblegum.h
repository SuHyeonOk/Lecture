#pragma once

#include "Client_Defines.h"
#include "N_NPC.h"

BEGIN(Client)

class CN_Bubblegum final : public CN_NPC
{
private:
	CN_Bubblegum(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CN_Bubblegum(const CN_Bubblegum& rhs);
	virtual ~CN_Bubblegum() = default;

public:
	virtual HRESULT		Initialize_Prototype()					override;
	virtual HRESULT		Initialize(void* pArg)					override;
	virtual void		Tick(_double TimeDelta)					override;
	virtual void		Late_Tick(_double TimeDelta)			override;
	virtual HRESULT		Render()								override;

	virtual void		On_Collision(CGameObject* pOther) override;

private:
	virtual HRESULT		SetUp_Components()						override;
	virtual HRESULT		SetUp_ShaderResources()					override;

private:
	virtual void		Help_UI()								override;
	virtual void		Talk_UI()								override;

private:
	_bool		m_bTalk_UI = false;

public:
	static	CN_Bubblegum*	Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject*	Clone(void* pArg = nullptr) override;
	virtual void			Free()						override;
};

END