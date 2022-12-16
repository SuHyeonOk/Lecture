#pragma once

#include "Client_Defines.h"
#include "M_Monster.h"

BEGIN(Client)

class CM_Gronmes final : public CM_Monster
{
private:
	CM_Gronmes(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CM_Gronmes(const CM_Gronmes& rhs);
	virtual ~CM_Gronmes() = default;

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
	virtual void		Monster_Tick(const _double& TimeDelta)	override;
	virtual void		Idle_Tick(const _double& TimeDelta)		override;
	virtual void		Move_Tick(const _double& TimeDelta)		override;
	virtual void		Find_Tick()								override;
	virtual void		Attack_Tick(const _double& TimeDelta)	override;
	virtual void		Hit_Tick()								override;
	virtual	void		Die_Tick()								override;

private:
	_float4				m_f4CenterPos;

	_bool				m_bAttack = false;
	_double				m_dBullet_TimeAcc = 0;

public:
	static	CM_Gronmes*		Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject*	Clone(void* pArg = nullptr) override;
	virtual void			Free()						override;
};

END