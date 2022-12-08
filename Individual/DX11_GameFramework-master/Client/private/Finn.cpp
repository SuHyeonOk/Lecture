#include "stdafx.h"
#include "..\public\Finn.h"

#include "GameInstance.h"

#include "M_Monster.h"
#include "M_PigWarrior_BEE.h"

CFinn::CFinn(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CGameObject(pDevice, pContext)
{

}

CFinn::CFinn(const CFinn & rhs)
	: CGameObject(rhs)
{

}

HRESULT CFinn::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CFinn::Initialize(void * pArg)
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

	m_tPlayerInfo.eState = m_tPlayerInfo.IDLE;

	return S_OK;
}

void CFinn::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	Player_Info();

	Current_Player(TimeDelta);
}

void CFinn::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);

	//CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);
	//if (pGameInstance->Key_Down(DIK_P))
	//{
	//	++m_AnimiNum;
	//}
	//if (pGameInstance->Key_Down(DIK_O))
	//{
	//	--m_AnimiNum;
	//}
	//m_pModelCom->Set_AnimIndex(m_AnimiNum);
	//cout << m_AnimiNum << endl;
	//RELEASE_INSTANCE(CGameInstance);

	Space_Attack(TimeDelta);
	Anim_Change(TimeDelta);
	m_pModelCom->Play_Animation(TimeDelta);	

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CFinn::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ShaderResources()))
		return E_FAIL;

	_uint iNumMeshes = m_pModelCom->Get_NumMeshes();

	for (_uint i = 0; i < iNumMeshes; ++i)
	{
		if (1 == i) // 초보 검 : 2 /  빨간 검 1
			continue;

		/* 이 모델을 그리기위한 셰이더에 머테리얼 텍스쳐를 전달한다. */
		m_pModelCom->Bind_Material(m_pShaderCom, i, aiTextureType_DIFFUSE, "g_DiffuseTexture");

		m_pModelCom->Render(m_pShaderCom, i, "g_BoneMatrices");
	}

	return S_OK;
}

HRESULT CFinn::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Component(CGameInstance::Get_StaticLevelIndex(), TEXT("Prototype_Component_Renderer"), TEXT("Com_Renderer"),
		(CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(CGameInstance::Get_StaticLevelIndex(), TEXT("Prototype_Component_Shader_VtxAnimModel"), TEXT("Com_Shader"),
		(CComponent**)&m_pShaderCom)))
		return E_FAIL;

	/* For.Com_Model */
	if (FAILED(__super::Add_Component(CGameInstance::Get_StaticLevelIndex(), TEXT("Prototype_Component_Model_Finn"), TEXT("Com_Model"),
		(CComponent**)&m_pModelCom)))
		return E_FAIL;


	return S_OK;
}

HRESULT CFinn::SetUp_ShaderResources()
{
	if (nullptr == m_pShaderCom)
		return E_FAIL;

	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	//if (pGameInstance->Key_Pressing(DIK_F))
	//{
	//	_bool	bHit = true;
	//	if (FAILED(m_pShaderCom->Set_RawValue("g_bHit", &bHit, sizeof _bool)))
	//		return E_FAIL;
	//}

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

void CFinn::Player_Info()
{
	//CObj_Manager::PLAYERINFO	tPlayerInfo;
	//tPlayerInfo.iHp = 

	//CObj_Manager::GetInstance()->Set_Current_Player();

	//CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	//if (pGameInstance->Key_Down(DIK_R))
	//{
	//	CM_PigWarrior_BEE* pObj; 
	//	// TODO : Get_Object 를 만들거나, 충돌처리 하여 객체를 받아올 수 있으면 수정

	//	CM_Monster* pMonster = dynamic_cast<CM_Monster*>(pObj);
	//	CObj_Manager::GetInstance()->Set_Player_PushHp(pMonster->Get_Monster_Attack());
	//}

	//RELEASE_INSTANCE(CGameInstance);

}

void CFinn::Current_Player(_double TimeDelta)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CObj_Manager::PLAYERINFO	ePlayerInfo;
	ePlayerInfo = CObj_Manager::GetInstance()->Get_Current_Player();

	if (ePlayerInfo.ePlayer == ePlayerInfo.FINN)					// Player 나라면
	{
		CObj_Manager::GetInstance()->Tick_Player_Transform();		// 현재 플레이어의 좌표를 Tick
		Key_Input(TimeDelta);										// 이동하고
		Check_Follow(TimeDelta);									// 근처에 Jake 가 있는지 확인한다.
	}
	else
		Player_Follow(TimeDelta);									// Player 가 내가 아니라면 따라간다.

	RELEASE_INSTANCE(CGameInstance);
}

void CFinn::Player_Follow(_double TimeDelta)
{
	// 현재 플레이어를 따라간다.

	if (CObj_Manager::PLAYERINFO::STATE::RUN == CObj_Manager::GetInstance()->Get_Current_Player_State())
		m_tPlayerInfo.eState = m_tPlayerInfo.RUN;
	else
	{
		m_dRun_TimeAcc += TimeDelta;
		if (1 < m_dRun_TimeAcc)
		{
			m_tPlayerInfo.eState = m_tPlayerInfo.IDLE;
			m_dRun_TimeAcc = 0;
		}
	}

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	// Jake 에게로
	CTransform * pJakeTransformCom = dynamic_cast<CTransform*>(pGameInstance->Get_ComponentPtr(CGameInstance::Get_StaticLevelIndex(), TEXT("Layer_Jake"), m_pTransformComTag, 0));

	_vector vPlayerPos;
	vPlayerPos = pJakeTransformCom->Get_State(CTransform::STATE_TRANSLATION);			// Jake 좌표 받아옴

	_vector		vMyPos = m_pTransformCom->Get_State(CTransform::STATE_TRANSLATION);		// 내 좌표
	_vector		vDir = vPlayerPos - vMyPos;												// 내 좌표가 객체를 바라보는 방향 벡터

	_float		fDistanceX = XMVectorGetX(XMVector3Length(vDir));						// X 값을 뽑아와 거리 확인

	if (3 > fDistanceX)
		m_pTransformCom->Chase(vPlayerPos, TimeDelta * 0.5, 2.f);
	else
		m_pTransformCom->Chase(vPlayerPos, TimeDelta, 2.f);

	m_pTransformCom->LookAt(vPlayerPos);

	RELEASE_INSTANCE(CGameInstance);
}

void CFinn::Check_Follow(_double TimeDelta)
{
	// 일정시간 동안 Jake 가 근처에 있지 않다면 Jake 를 내 근처로 이동시킨다.

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CTransform * pJakeTransformCom = dynamic_cast<CTransform*>(pGameInstance->Get_ComponentPtr(CGameInstance::Get_StaticLevelIndex(), TEXT("Layer_Jake"), m_pTransformComTag, 0));

	_vector vPlayerPos;
	vPlayerPos = pJakeTransformCom->Get_State(CTransform::STATE_TRANSLATION);		// Jake 좌표 받아옴

	_vector		vMyPos = m_pTransformCom->Get_State(CTransform::STATE_TRANSLATION);	// 내 좌표
	_vector		vDir = vPlayerPos - vMyPos; // 내 좌표가 객체를 바라보는 방향 벡터 (Jaek <- Finn)

	_float		fDistanceX = XMVectorGetX(XMVector3Length(vDir));					// X 값을 뽑아와 거리 확인

	if (4.f < fDistanceX)
	{
		m_dNotfollow_TimeAcc += TimeDelta;
		if (5 < m_dNotfollow_TimeAcc) // 따라오지 못 하는 시간이 5 초를 넘어간다면
		{
			_vector		vMyLook = m_pTransformCom->Get_State(CTransform::STATE_LOOK);
			_float fLookX = XMVectorGetX(vMyLook);
			_float fLookZ = XMVectorGetZ(vMyLook);

			_float fAddX, fAddZ;
			if (0 < fLookX)		// +
				fAddX = 1.2f;
			else				// -
				fAddX = -1.2f;

			if (0 < fLookZ)
				fAddZ = 1.2f;
			else
				fAddZ = -1.2f;

			_float4 f4MyPos;
			XMStoreFloat4(&f4MyPos, vMyPos);
			pJakeTransformCom->Set_Pos(_float3(f4MyPos.x - fAddX, f4MyPos.y, f4MyPos.z - fAddZ));	// 내 옆으로 옮김

			m_dNotfollow_TimeAcc = 0;
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

void CFinn::Key_Input(_double TimeDelta)
{
	if (m_OnMove)
	{
		m_pTransformCom->Go_Straight(TimeDelta);
		m_tPlayerInfo.eState = m_tPlayerInfo.RUN;
	}

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (pGameInstance->Key_Pressing(DIK_UP))
	{
		m_OnMove = true;
		m_pTransformCom->Rotation(m_pTransformCom->Get_State(CTransform::STATE_UP), XMConvertToRadians(0.f));

		if (pGameInstance->Key_Pressing(DIK_RIGHT))
			m_pTransformCom->Rotation(m_pTransformCom->Get_State(CTransform::STATE_UP), XMConvertToRadians(45.f));
		if (pGameInstance->Key_Pressing(DIK_LEFT))
			m_pTransformCom->Rotation(m_pTransformCom->Get_State(CTransform::STATE_UP), XMConvertToRadians(315.f));
	}
	if (pGameInstance->Key_Pressing(DIK_RIGHT))
	{
		m_OnMove = true;
		m_pTransformCom->Rotation(m_pTransformCom->Get_State(CTransform::STATE_UP), XMConvertToRadians(90.f));

		if (pGameInstance->Key_Pressing(DIK_UP))
			m_pTransformCom->Rotation(m_pTransformCom->Get_State(CTransform::STATE_UP), XMConvertToRadians(45.f));
		if (pGameInstance->Key_Pressing(DIK_DOWN))
			m_pTransformCom->Rotation(m_pTransformCom->Get_State(CTransform::STATE_UP), XMConvertToRadians(225.f));
	}
	if (pGameInstance->Key_Pressing(DIK_DOWN))
	{
		m_OnMove = true;
		m_pTransformCom->Rotation(m_pTransformCom->Get_State(CTransform::STATE_UP), XMConvertToRadians(180.f));

		if (pGameInstance->Key_Pressing(DIK_RIGHT))
			m_pTransformCom->Rotation(m_pTransformCom->Get_State(CTransform::STATE_UP), XMConvertToRadians(135.f));
		if (pGameInstance->Key_Pressing(DIK_LEFT))
			m_pTransformCom->Rotation(m_pTransformCom->Get_State(CTransform::STATE_UP), XMConvertToRadians(225.f));
	}
	if (pGameInstance->Key_Pressing(DIK_LEFT))
	{
		m_OnMove = true;
		m_pTransformCom->Rotation(m_pTransformCom->Get_State(CTransform::STATE_UP), XMConvertToRadians(270.f));

		if (pGameInstance->Key_Pressing(DIK_UP))
			m_pTransformCom->Rotation(m_pTransformCom->Get_State(CTransform::STATE_UP), XMConvertToRadians(315.f));
		if (pGameInstance->Key_Pressing(DIK_DOWN))
			m_pTransformCom->Rotation(m_pTransformCom->Get_State(CTransform::STATE_UP), XMConvertToRadians(225.f));
	}

	if (pGameInstance->Key_Up(DIK_UP) || pGameInstance->Key_Up(DIK_RIGHT) || pGameInstance->Key_Up(DIK_DOWN) || pGameInstance->Key_Up(DIK_LEFT))
	{
		m_OnMove = false;
		m_tPlayerInfo.eState = m_tPlayerInfo.IDLE;
	}

	////////////////////////////////////////

	if (pGameInstance->Key_Down(DIK_SPACE))
	{
		m_dSpace_InputTimeAcc += TimeDelta;
		m_bSpace_Attack = true;
	}
		
	RELEASE_INSTANCE(CGameInstance);
}

void CFinn::Space_Attack(_double TimeDelta)
{
	cout << m_iSpace_AttackCount << endl;

	if (!m_bSpace_Attack)
		return;

	m_dSpace_AttackTimeAcc += TimeDelta;
	if (0.5 < m_dSpace_InputTimeAcc)
	{
		m_tPlayerInfo.eState = m_tPlayerInfo.IDLE;
		m_bSpace_Attack = false;
		++m_iSpace_AttackCount;
		m_dSpace_AttackTimeAcc = 0;
	}

	if (0 == m_iSpace_AttackCount)
	{
		m_tPlayerInfo.eState = m_tPlayerInfo.ATTACK_1;
	}
	else if (1 == m_iSpace_AttackCount)
	{
		m_tPlayerInfo.eState = m_tPlayerInfo.ATTACK_2;
	}
	else if (2 == m_iSpace_AttackCount)
	{
		m_tPlayerInfo.eState = m_tPlayerInfo.ATTACK_3;
	}
	else
		m_iSpace_AttackCount = 0;

	// 일정 시간 동안 키입력을 하지 않으면 IDLE 상태로 돌아간다.
	if (5 < m_dSpace_AttackTimeAcc)
	{
		m_tPlayerInfo.eState = m_tPlayerInfo.IDLE;
		m_bSpace_Attack = false;
		m_iSpace_AttackCount = 0;
		m_dSpace_AttackTimeAcc = 0;
	}
}

void CFinn::Anim_Change(_double TimeDelta)
{
	if (m_tPlayerInfo.ePreState != m_tPlayerInfo.eState)
	{
		switch (m_tPlayerInfo.eState)
		{
		case CObj_Manager::PLAYERINFO::IDLE:
			m_pModelCom->Set_AnimIndex(39);
			break;

		case CObj_Manager::PLAYERINFO::RUN:
			m_pModelCom->Set_AnimIndex(49);
			break;

		case CObj_Manager::PLAYERINFO::ATTACK_1:
			m_pModelCom->Set_AnimIndex(18);
			break;
		case CObj_Manager::PLAYERINFO::ATTACK_2:
			m_pModelCom->Set_AnimIndex(19);
			break;
		case CObj_Manager::PLAYERINFO::ATTACK_3:
			m_pModelCom->Set_AnimIndex(20);
			break;

		default:
			break;
		}
		CObj_Manager::GetInstance()->Set_Current_Player_State(m_tPlayerInfo.eState);
		m_tPlayerInfo.ePreState = m_tPlayerInfo.eState;
	}
}

CFinn * CFinn::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
{
	CFinn*		pInstance = new CFinn(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CFinn");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CFinn::Clone(void * pArg)
{
	CFinn*		pInstance = new CFinn(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CFinn");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CFinn::Free()
{
	__super::Free();

	Safe_Release(m_pModelCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pRendererCom);
}
