#include "stdafx.h"
#include "..\public\UI_Informacion.h"

#include "GameInstance.h"
#include "Obj_Manager.h"

CUI_Informacion::CUI_Informacion(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CUI_(pDevice, pContext)
{
}

CUI_Informacion::CUI_Informacion(const CUI_Informacion & rhs)
	: CUI_(rhs)
{
}

HRESULT CUI_Informacion::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;
	
	return S_OK;
}

HRESULT CUI_Informacion::Initialize(void * pArg)
{
	CGameObject::GAMEOBJECTDESC		GameObjectDesc;
	ZeroMemory(&GameObjectDesc, sizeof(GameObjectDesc));

	GameObjectDesc.TransformDesc.fSpeedPerSec = 5.f;
	GameObjectDesc.TransformDesc.fRotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(CGameObject::Initialize(&GameObjectDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_fSizeX = 448.f / 1.5f;
	m_fSizeY = 200.f / 1.5f;

	m_fX = m_fSizeX * 0.5f;
	m_fY = m_fSizeY * 0.5f;


	m_pTransformCom->Set_Scaled(_float3(m_fSizeX, m_fSizeY, 1.f));
	m_pTransformCom->Set_State(CTransform::STATE_TRANSLATION, XMVectorSet(m_fX - g_iWinSizeX * 0.5f, -m_fY + g_iWinSizeY * 0.5f, 0.f, 1.f));

	XMStoreFloat4x4(&m_ViewMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&m_ProjMatrix, XMMatrixOrthographicLH(_float(g_iWinSizeX), _float(g_iWinSizeY), 0.f, 1.f));

	return S_OK;
}

void CUI_Informacion::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
}

void CUI_Informacion::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);

	if(nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);
}

HRESULT CUI_Informacion::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ShaderResources()))
		return E_FAIL;

	m_pShaderCom->Begin(0);

	m_pVIBufferCom->Render();

	return S_OK;
}

HRESULT CUI_Informacion::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Component(CGameInstance::Get_StaticLevelIndex(), TEXT("Prototype_Component_Renderer"), TEXT("Com_Renderer"),
		(CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(CGameInstance::Get_StaticLevelIndex(), TEXT("Prototype_Component_Shader_VtxTex"), TEXT("Com_Shader"),
		(CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_VIBuffer */
	if (FAILED(__super::Add_Component(CGameInstance::Get_StaticLevelIndex(), TEXT("Prototype_Component_VIBuffer_Rect"), TEXT("Com_VIBuffer"),
		(CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* For.Com_Texture */
	if (FAILED(__super::Add_Component(CGameInstance::Get_StaticLevelIndex(), TEXT("Prototype_Component_Texture_UI_Finn_Informacion"), TEXT("Com_Texture_Finn"),
		(CComponent**)&m_pTextureCom[TYPE_FINN])))
		return E_FAIL;
	/* For.Com_Texture */
	if (FAILED(__super::Add_Component(CGameInstance::Get_StaticLevelIndex(), TEXT("Prototype_Component_Texture_UI_Jake_Informacion"), TEXT("Com_Texture_Jake"),
		(CComponent**)&m_pTextureCom[TYPE_JAKE])))
		return E_FAIL;

	return S_OK;
}

HRESULT CUI_Informacion::SetUp_ShaderResources()
{
	if (nullptr == m_pShaderCom)
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_Matrix("g_ViewMatrix", &m_ViewMatrix)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_Matrix("g_ProjMatrix", &m_ProjMatrix)))
		return E_FAIL;

	if (CObj_Manager::PLAYERINFO::FINN == CObj_Manager::GetInstance()->Get_Current_Player().ePlayer)
	{
		if (FAILED(m_pTextureCom[TYPE_FINN]->Bind_ShaderResource(m_pShaderCom, "g_Texture")))
			return E_FAIL;
	}
	else if (CObj_Manager::PLAYERINFO::JAKE == CObj_Manager::GetInstance()->Get_Current_Player().ePlayer)
	{
		if (FAILED(m_pTextureCom[TYPE_JAKE]->Bind_ShaderResource(m_pShaderCom, "g_Texture")))
			return E_FAIL;
	}

	return S_OK;
}

CUI_Informacion * CUI_Informacion::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
{
 	CUI_Informacion*		pInstance = new CUI_Informacion(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CUI_Informacion");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CUI_Informacion::Clone(void * pArg)
{
	CUI_Informacion*		pInstance = new CUI_Informacion(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CUI_Informacion");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CUI_Informacion::Free()
{
	__super::Free();

	for (auto& pTextureCom : m_pTextureCom)
		Safe_Release(pTextureCom);
}