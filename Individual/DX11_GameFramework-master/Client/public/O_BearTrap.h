#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CModel;
class CShader;
class CRenderer;
class CCollider;
END

BEGIN(Client)

class CO_BearTrap final : public CGameObject
{
private:
	CO_BearTrap(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CO_BearTrap(const CO_BearTrap& rhs);
	virtual ~CO_BearTrap() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_double TimeDelta) override;
	virtual void Late_Tick(_double TimeDelta) override;
	virtual HRESULT Render() override;

	virtual void		On_Collision(CGameObject* pOther) override;

private:
	CShader*				m_pShaderCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;
	CModel*					m_pModelCom = nullptr;
	CCollider*				m_pColliderCom = nullptr;

private:
	HRESULT			SetUp_Components();
	HRESULT			SetUp_ShaderResources();

private:
	_bool			m_bSound = { false };
	_double			m_dSound_TimeAcc = { 0.0 };

public:
	static	CO_BearTrap*	Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject*	Clone(void* pArg = nullptr) override;
	virtual void			Free() override;
};

END