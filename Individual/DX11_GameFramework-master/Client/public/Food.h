#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
class CCollider;
END

BEGIN(Client)

class CFood final : public CGameObject
{
public:
	typedef struct tagFoodInfo
	{
		enum FOODKIND { ROYAL_TART, BURRITO, FOOD_END };

		_float3		fPos = _float3(0.f, 0.f, 0.f);
		FOODKIND	eFoodKind;
		
	}FOODINFO;

private:
	CFood(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CFood(const CFood& rhs);
	virtual ~CFood() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_double TimeDelta) override;
	virtual void Late_Tick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CRenderer*				m_pRendererCom = nullptr;
	CShader*				m_pShaderCom = nullptr;
	CModel*					m_pModelCom = nullptr;
	CCollider*				m_pColliderCom = nullptr;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ShaderResources();

private:
	FOODINFO	m_tinFoodInfo;
	FOODINFO	m_tFoodInfo;

public:
	static	CFood* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;
};

END