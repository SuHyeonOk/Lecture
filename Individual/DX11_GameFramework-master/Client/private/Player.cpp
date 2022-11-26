#include "stdafx.h"
#include "..\public\Player.h"
#include "GameInstance.h"

CPlayer::CPlayer(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CGameObject(pDevice, pContext)
{

}

CPlayer::CPlayer(const CPlayer & rhs)
	: CGameObject(rhs)
{

}

HRESULT CPlayer::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;
	
	return S_OK;
}

HRESULT CPlayer::Initialize(void * pArg)
{
	_float3	f3Pos = _float3(0.f, 0.f, 0.f);

	if (nullptr != pArg)
		memcpy(&f3Pos, pArg, sizeof(_float3));

	CGameObject::GAMEOBJECTDESC		GameObjectDesc;
	ZeroMemory(&GameObjectDesc, sizeof(GameObjectDesc));

	GameObjectDesc.TransformDesc.fSpeedPerSec = 5.f;
	GameObjectDesc.TransformDesc.fRotationPerSec = XMConvertToRadians(90.0f);
	GameObjectDesc.TransformDesc.f3Pos = _float3(f3Pos.x, f3Pos.y, f3Pos.z);

	if (FAILED(__super::Initialize(&GameObjectDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_pTransformCom->Set_Pos();

	return S_OK;
}

void CPlayer::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);


}

void CPlayer::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);

	Key_Input(TimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (pGameInstance->Mouse_Down(CInput_Device::DIM_MB))
	{
		_float4		f4MousePos, f4PlayerPos;
		_vector		vPlayerPos;
		vPlayerPos = m_pTransformCom->Get_State(CTransform::STATE_TRANSLATION);

		XMStoreFloat4(&f4PlayerPos, vPlayerPos);
		cout << "PlayerPos : " << f4PlayerPos.x << " | " << f4PlayerPos.y << " | " << f4PlayerPos.z << " | " << f4PlayerPos.w << endl;

		f4MousePos = pGameInstance->Get_MousePos();
		m_pTransformCom->Set_Pos(_float3(f4MousePos.x, f4MousePos.y, f4MousePos.z));
		int a = 0;
	}

	RELEASE_INSTANCE(CGameInstance);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CPlayer::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ShaderResources()))
		return E_FAIL;

	m_pShaderCom->Begin(0);

	m_pModelCom->Render();
	
	return S_OK;
}

HRESULT CPlayer::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Component(CGameInstance::Get_StaticLevelIndex(), TEXT("Prototype_Component_Renderer"), TEXT("Com_Renderer"),
		(CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Shader_VtxModel"), TEXT("Com_Shader"),
		(CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_Fiona"), TEXT("Com_Model"),	
		(CComponent**)&m_pModelCom)))
		return E_FAIL;


	

	return S_OK;
}

HRESULT CPlayer::SetUp_ShaderResources()
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


	/* For.Lights */
	const LIGHTDESC* pLightDesc = pGameInstance->Get_LightDesc(0);
	if (nullptr == pLightDesc)
		return E_FAIL;
	//
	//if (FAILED(m_pShaderCom->Set_RawValue("g_vLightDir", &pLightDesc->vDirection, sizeof(_float4))))
	//	return E_FAIL;
	//if (FAILED(m_pShaderCom->Set_RawValue("g_vLightDiffuse", &pLightDesc->vDiffuse, sizeof(_float4))))
	//	return E_FAIL;
	//if (FAILED(m_pShaderCom->Set_RawValue("g_vLightAmbient", &pLightDesc->vAmbient, sizeof(_float4))))
	//	return E_FAIL;
	//if (FAILED(m_pShaderCom->Set_RawValue("g_vLightSpecular", &pLightDesc->vSpecular, sizeof(_float4))))
	//	return E_FAIL;

	//if (FAILED(m_pShaderCom->Set_RawValue("g_vCamPosition", &pGameInstance->Get_CamPosition(), sizeof(_float4))))
	//	return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	



	return S_OK;
}

void CPlayer::Key_Input(_double TimeDelta)
{
	_matrix PlayerWorld;
	PlayerWorld = m_pTransformCom->Get_WorldMatrix();
	_float4x4 f44PlayerWorld;
	XMStoreFloat4x4(&f44PlayerWorld, PlayerWorld);

	// TimerSample
	m_dTimeAcc += TimeDelta;
	if (1.f < m_dTimeAcc)
	{
		cout << "PlayerWorld_Right	: " << f44PlayerWorld._11 << " | " << f44PlayerWorld._12 << " | " << f44PlayerWorld._13 << " | " << f44PlayerWorld._14 << endl;
		cout << "PlayerWorld_Up		: " << f44PlayerWorld._21 << " | " << f44PlayerWorld._22 << " | " << f44PlayerWorld._23 << " | " << f44PlayerWorld._24 << endl;
		cout << "PlayerWorld_Look	: " << f44PlayerWorld._31 << " | " << f44PlayerWorld._32 << " | " << f44PlayerWorld._33 << " | " << f44PlayerWorld._34 << endl;
		cout << "PlayerWorld_Pos		: " << f44PlayerWorld._41 << " | " << f44PlayerWorld._42 << " | " << f44PlayerWorld._43 << " | " << f44PlayerWorld._44 << endl;
		cout << "----------------------------------------" << endl;

		m_dTimeAcc = 0;
	}

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (pGameInstance->Key_Pressing(DIK_UP))
	{
		m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 1.f), 0.f);
		m_pTransformCom->Go_Straight(TimeDelta);

		if (pGameInstance->Key_Pressing(DIK_RIGHT))
		{
			m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_UP), TimeDelta * 25.f);
			//m_pTransformCom->Rotation(m_pTransformCom->Get_State(CTransform::STATE_UP), 0.5f);
			m_pTransformCom->Go_Straight(TimeDelta / 2);
		}
		if (pGameInstance->Key_Pressing(DIK_LEFT))
		{
			m_pTransformCom->Turn(m_pTransformCom->Get_State(CTransform::STATE_UP), TimeDelta * -25.f);
			//m_pTransformCom->Rotation(m_pTransformCom->Get_State(CTransform::STATE_UP), -0.5f);
			m_pTransformCom->Go_Straight(TimeDelta / 2);
		}
	}
	//if (pGameInstance->Key_Pressing(DIK_DOWN))
	//{
	//	m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 1.f), -1.f);
	//	m_pTransformCom->Go_Backward(TimeDelta);
	//}

	//if (pGameInstance->Key_Pressing(DIK_UP) && pGameInstance->Key_Pressing(DIK_RIGHT))
	//{
	//	m_pTransformCom->Rotation(m_pTransformCom->Get_State(CTransform::STATE_UP), 45.f);
	//	//m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), TimeDelta * 1.f);
	//	m_pTransformCom->Go_Straight(TimeDelta);
	//}
	if (pGameInstance->Key_Pressing(DIK_RIGHT))
	{
		//m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 1.f), -80.f);
		//m_pTransformCom->Go_Straight(TimeDelta);
		m_pTransformCom->Go_Right(TimeDelta);
	}
	//if (pGameInstance->Key_Pressing(DIK_RIGHT) && pGameInstance->Key_Pressing(DIK_DOWN))
	//{
	//	//m_pTransformCom->Rotation(m_pTransformCom->Get_State(CTransform::STATE_UP), 135.f);
	//	//m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), TimeDelta * -90.f * 0.05f);
	//	m_pTransformCom->Go_Straight(TimeDelta);
	//}
	if (pGameInstance->Key_Pressing(DIK_DOWN))
	{
		//m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 1.f), 180.f);
		m_pTransformCom->Go_Backward(TimeDelta);
	}
	//if (pGameInstance->Key_Pressing(DIK_DOWN) && pGameInstance->Key_Pressing(DIK_LEFT))
	//{
	//	//m_pTransformCom->Rotation(m_pTransformCom->Get_State(CTransform::STATE_UP), 225.f);
	//	m_pTransformCom->Go_Straight(TimeDelta);
	//}
	if (pGameInstance->Key_Pressing(DIK_LEFT))
	{
		//m_pTransformCom->Rotation(XMVectorSet(0.f, 1.f, 0.f, 1.f), 80.f);
		//m_pTransformCom->Go_Straight(TimeDelta);
		m_pTransformCom->Go_Left(TimeDelta);
	}
	//if (pGameInstance->Key_Pressing(DIK_LEFT) && pGameInstance->Key_Pressing(DIK_UP))
	//{
	//	m_pTransformCom->Rotation(m_pTransformCom->Get_State(CTransform::STATE_UP), -45.f);
	//	//m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), TimeDelta * -1.f);
	//	m_pTransformCom->Go_Straight(TimeDelta);
	//}

	//_long			MouseMove = 0;
	//_float			fSensitivity = 0.05f;

	//if (MouseMove = pGameInstance->Get_DIMouseMove(CInput_Device::DIMS_X))
	//{
	//	m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), TimeDelta * MouseMove * fSensitivity);
	//}

	RELEASE_INSTANCE(CGameInstance);
}

CPlayer * CPlayer::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
{
 	CPlayer*		pInstance = new CPlayer(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CPlayer");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CPlayer::Clone(void * pArg)
{
	CPlayer*		pInstance = new CPlayer(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CPlayer");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPlayer::Free()
{
	__super::Free();

	Safe_Release(m_pModelCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pRendererCom);

}
