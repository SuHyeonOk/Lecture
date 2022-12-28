#include "stdafx.h"   
#include "..\public\Food.h"

#include "GameInstance.h"
#include "Obj_Manager.h"

CFood::CFood(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CGameObject(pDevice, pContext)
{

}

CFood::CFood(const CFood & rhs)
	: CGameObject(rhs)
{

}

HRESULT CFood::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CFood::Initialize(void * pArg)
{	
	m_wsTag = L"Item_Food";

	CGameObject::GAMEOBJECTDESC		GameObjectDesc;
	ZeroMemory(&GameObjectDesc, sizeof(GameObjectDesc));

	if (nullptr != pArg)
		memcpy(&m_tinFoodInfo, pArg, sizeof(FOODINFO));

	if (m_tinFoodInfo.eFoodKind == m_tFoodInfo.ROYAL_TART)
	{
		GameObjectDesc.TransformDesc.fSpeedPerSec = 0.f;
		GameObjectDesc.TransformDesc.fRotationPerSec = XMConvertToRadians(90.f);
		GameObjectDesc.TransformDesc.f3Pos = _float3(m_tinFoodInfo.fPos.x, m_tinFoodInfo.fPos.y, m_tinFoodInfo.fPos.z);
	}
	else if (m_tinFoodInfo.eFoodKind == m_tFoodInfo.BURRITO)
	{
		GameObjectDesc.TransformDesc.fSpeedPerSec = 0.f;
		GameObjectDesc.TransformDesc.fRotationPerSec = XMConvertToRadians(90.f);
		GameObjectDesc.TransformDesc.f3Pos = _float3(m_tinFoodInfo.fPos.x, m_tinFoodInfo.fPos.y, m_tinFoodInfo.fPos.z);
	}


	if (FAILED(__super::Initialize(&GameObjectDesc)))
		return E_FAIL;

 	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_Pos();

	return S_OK;
}

void CFood::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 1.f), TimeDelta);

	m_pColliderCom->Update(m_pTransformCom->Get_WorldMatrix());
}

void CFood::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);

	CGameInstance::GetInstance()->Add_ColGroup(CCollider_Manager::COL_ITME, this);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CFood::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ShaderResources()))
		return E_FAIL;

	_uint iNumMeshes = m_pModelCom->Get_NumMeshes();

	for (_uint i = 0; i < iNumMeshes; ++i)
	{
		/* 이 모델을 그리기위한 셰이더에 머테리얼 텍스쳐를 전달한다. */
		m_pModelCom->Bind_Material(m_pShaderCom, i, aiTextureType_DIFFUSE, "g_DiffuseTexture");

		m_pModelCom->Render(m_pShaderCom, i);
	}

	if (CObj_Manager::GetInstance()->Get_NavigationRender())
	{
		if (nullptr != m_pColliderCom)
			m_pColliderCom->Render();
	}

	return S_OK;
}

void CFood::On_Collision(CGameObject * pOther)
{
	if (L"Finn" == pOther->Get_Tag() || L"Jake" == pOther->Get_Tag())
		CGameObject::Set_Dead();
}

HRESULT CFood::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Component(CGameInstance::Get_StaticLevelIndex(), TEXT("Prototype_Component_Renderer"), TEXT("Com_Renderer"),
		(CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxModel"), TEXT("Com_Shader"),
		(CComponent**)&m_pShaderCom)))
		return E_FAIL;

	if (m_tinFoodInfo.eFoodKind == m_tFoodInfo.ROYAL_TART)
	{
		/* For.Com_Model */
		if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Royal_Tart"), TEXT("Com_Model"),
			(CComponent**)&m_pModelCom)))
			return E_FAIL;
	}
	else if (m_tinFoodInfo.eFoodKind == m_tFoodInfo.BURRITO)
	{
		/* For.Com_Model */
		if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Burrito"), TEXT("Com_Model"),
			(CComponent**)&m_pModelCom)))
			return E_FAIL;
	}

	CCollider::COLLIDERDESC			ColliderDesc;

	/* For.Com_SPHERE */
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));
	ColliderDesc.vSize = _float3(0.5f, 0.5f, 0.5f);
	ColliderDesc.vCenter = _float3(0.f, ColliderDesc.vSize.y * 0.5f, 0.f);

	if (FAILED(__super::Add_Component(CGameInstance::Get_StaticLevelIndex(), TEXT("Prototype_Component_Collider_SPHERE"), TEXT("Com_Collider"),
		(CComponent**)&m_pColliderCom, &ColliderDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CFood::SetUp_ShaderResources()
{
	if (nullptr == m_pShaderCom)
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(m_pShaderCom->Set_Matrix("g_ViewMatrix", &pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_VIEW))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Set_Matrix("g_ProjMatrix", &pGameInstance->Get_TransformFloat4x4(CPipeLine::D3DTS_PROJ))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CFood * CFood::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
{
	CFood*		pInstance = new CFood(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CFood");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CFood::Clone(void * pArg)
{
	CFood*		pInstance = new CFood(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CFood");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CFood::Free()
{
	__super::Free();

	Safe_Release(m_pColliderCom);
	Safe_Release(m_pModelCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pRendererCom);
}
