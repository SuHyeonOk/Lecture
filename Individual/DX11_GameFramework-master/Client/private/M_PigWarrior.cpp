#include "stdafx.h"
#include "..\public\M_PigWarrior.h"

#include "GameInstance.h"
#include "Obj_Manager.h"
#include "ItemManager.h"
#include "Utilities_Manager.h"

#include "UI_3DTexture.h"
#include "W_PigWarrior.h"
#include "Bone.h"

CM_PigWarrior::CM_PigWarrior(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CM_Monster(pDevice, pContext)
{

}

CM_PigWarrior::CM_PigWarrior(const CM_PigWarrior & rhs)
	: CM_Monster(rhs)
{

}

HRESULT CM_PigWarrior::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT CM_PigWarrior::Initialize(void * pArg)
{
	m_wsTag = L"Monster__PigWarrior";

	CM_Monster::MONSTERDESC		MonsterDesc;
	ZeroMemory(&MonsterDesc, sizeof(MonsterDesc));

	if (nullptr != pArg)
		memcpy(&MonsterDesc, pArg, sizeof(MonsterDesc));

	m_tMonsterDesc.eMonsterKind = MonsterDesc.eMonsterKind;

	if (m_tMonsterDesc.eMonsterKind == m_tMonsterDesc.W_BEE)
	{
		MonsterDesc.TransformDesc.fSpeedPerSec = 1.5f;
		MonsterDesc.TransformDesc.fRotationPerSec = XMConvertToRadians(90.0f);
		MonsterDesc.TransformDesc.f3Pos = _float3(MonsterDesc.f3Pos.x, MonsterDesc.f3Pos.y, MonsterDesc.f3Pos.z);
		m_f4CenterPos = _float4(MonsterDesc.f3Pos.x, MonsterDesc.f3Pos.y, MonsterDesc.f3Pos.z, 1.f);
	}
	else if (m_tMonsterDesc.eMonsterKind == m_tMonsterDesc.W_WORKER)
	{
		MonsterDesc.TransformDesc.fSpeedPerSec = 1.5f;
		MonsterDesc.TransformDesc.fRotationPerSec = XMConvertToRadians(90.0f);
		MonsterDesc.TransformDesc.f3Pos = _float3(MonsterDesc.f3Pos.x, MonsterDesc.f3Pos.y, MonsterDesc.f3Pos.z);
		m_f4CenterPos = _float4(MonsterDesc.f3Pos.x, MonsterDesc.f3Pos.y, MonsterDesc.f3Pos.z, 1.f);
	}

	if (FAILED(CM_Monster::Initialize(&MonsterDesc)))
		return E_FAIL;

	if (FAILED(SetUp_Components()))
		return E_FAIL;

	m_tMonsterInfo.eState = m_tMonsterInfo.MOVE;
	m_tMonsterInfo.iHp = 50;
	m_tMonsterInfo.iExp = 25;
	m_tMonsterInfo.iAttack = 5;

	if (FAILED(Ready_Parts()))
		return E_FAIL;

	return S_OK;
}

void CM_PigWarrior::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	Monster_Tick(TimeDelta);

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	m_MonsterParts[0]->Tick(TimeDelta);
	m_MonsterParts[1]->Tick(TimeDelta);
	m_pColliderCom[COLLTYPE_AABB]->Update(m_pTransformCom->Get_WorldMatrix());

	RELEASE_INSTANCE(CGameInstance);
}

void CM_PigWarrior::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);

	m_pModelCom->Play_Animation(TimeDelta);

	m_MonsterParts[0]->Late_Tick(TimeDelta);
	m_MonsterParts[1]->Late_Tick(TimeDelta);
	CGameInstance::GetInstance()->Add_ColGroup(CCollider_Manager::COL_MONSTER, this);

	if (nullptr != m_pRendererCom)
		m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_NONALPHABLEND, this);
}

HRESULT CM_PigWarrior::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	if (FAILED(SetUp_ShaderResources()))
		return E_FAIL;

	_uint iNumMeshes = m_pModelCom->Get_NumMeshes();

	for (_uint i = 0; i < iNumMeshes; ++i)
	{
		if (m_tMonsterDesc.eMonsterKind == m_tMonsterDesc.W_BEE)
			if (2 == i)	continue;	// 꿀벌 칼 없애기
		if (m_tMonsterDesc.eMonsterKind == m_tMonsterDesc.W_WORKER)
			if (1 == i) continue;	// 노동자 칼 없애기

		/* 이 모델을 그리기위한 셰이더에 머테리얼 텍스쳐를 전달한다. */
		m_pModelCom->Bind_Material(m_pShaderCom, i, aiTextureType_DIFFUSE, "g_DiffuseTexture");

		m_pModelCom->Render(m_pShaderCom, i, "g_BoneMatrices");
	}

	return S_OK;
}

void CM_PigWarrior::On_Collision(CGameObject * pOther)
{
	CM_Monster::On_Collision(pOther);

	// TODO : !하고 싶다면..? PigWarrior 의 경우에는 방패 때문에 예외적으로 충돌 처리
}

HRESULT CM_PigWarrior::SetUp_Components()
{
	/* For.Com_Renderer */
	if (FAILED(__super::Add_Component(CGameInstance::Get_StaticLevelIndex(), TEXT("Prototype_Component_Renderer"), TEXT("Com_Renderer"),
		(CComponent**)&m_pRendererCom)))
		return E_FAIL;

	/* For.Com_Shader */
	if (FAILED(__super::Add_Component(CGameInstance::Get_StaticLevelIndex(), TEXT("Prototype_Component_Shader_VtxAnimModel"), TEXT("Com_Shader"),
		(CComponent**)&m_pShaderCom)))
		return E_FAIL;

	if (m_tMonsterDesc.eMonsterKind == m_tMonsterDesc.W_BEE)
	{
		/* For.Com_Model */
		if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_M_PigWarrior_BEE"), TEXT("Com_Model"),
			(CComponent**)&m_pModelCom)))
			return E_FAIL;
	}
	else if (m_tMonsterDesc.eMonsterKind == m_tMonsterDesc.W_WORKER)
	{
		/* For.Com_Model */
		if (FAILED(__super::Add_Component(LEVEL_GAMEPLAY, TEXT("Prototype_Component_Model_M_PigWarrior_WORKER"), TEXT("Com_Model"),
			(CComponent**)&m_pModelCom)))
			return E_FAIL;
	}

	CCollider::COLLIDERDESC			ColliderDesc;

	/* For.Com_AABB */
	ZeroMemory(&ColliderDesc, sizeof(CCollider::COLLIDERDESC));
	ColliderDesc.vSize = _float3(0.5f, 0.7f, 0.5f);
	ColliderDesc.vCenter = _float3(0.f, ColliderDesc.vSize.y * 0.5f, 0.f);

	if (FAILED(__super::Add_Component(CGameInstance::Get_StaticLevelIndex(), TEXT("Prototype_Component_Collider_AABB"), TEXT("Com_Collider"),
		(CComponent**)&m_pColliderCom[COLLTYPE_AABB], &ColliderDesc)))
		return E_FAIL;
	
	return S_OK;
}

HRESULT CM_PigWarrior::SetUp_ShaderResources()
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

HRESULT CM_PigWarrior::Ready_Parts()
{
	CGameObject*		pPartObject = nullptr;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CW_PigWarrior::WEAPONDESC			WeaponDesc;
	ZeroMemory(&WeaponDesc, sizeof(CW_PigWarrior::WEAPONDESC));

	WeaponDesc.eWarriorType = WeaponDesc.SWORD;
	WeaponDesc.iAttack = m_tMonsterInfo.iAttack;
	WeaponDesc.PivotMatrix = m_pModelCom->Get_PivotFloat4x4();
	WeaponDesc.pSocket = m_pModelCom->Get_BonePtr("woodenSword");
	WeaponDesc.pTargetTransform = m_pTransformCom;
	Safe_AddRef(WeaponDesc.pSocket);
	Safe_AddRef(m_pTransformCom);

	pPartObject = pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_PigWarrior_Weapon"), &WeaponDesc);
	if (nullptr == pPartObject)
		return E_FAIL;

	m_MonsterParts.push_back(pPartObject);

	WeaponDesc.eWarriorType = WeaponDesc.CYLINDER;
	WeaponDesc.iAttack = m_tMonsterInfo.iAttack;
	WeaponDesc.PivotMatrix = m_pModelCom->Get_PivotFloat4x4();
	WeaponDesc.pSocket = m_pModelCom->Get_BonePtr("Bone001_shield");
	WeaponDesc.pTargetTransform = m_pTransformCom;
	Safe_AddRef(WeaponDesc.pSocket);
	Safe_AddRef(m_pTransformCom);

	pPartObject = pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_PigWarrior_Weapon"), &WeaponDesc);
	if (nullptr == pPartObject)
		return E_FAIL;

	m_MonsterParts.push_back(pPartObject);

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CM_PigWarrior::Monster_Tick(const _double& TimeDelta)
{
	if (0 >= m_tMonsterInfo.iHp)
		m_tMonsterInfo.eState = m_tMonsterInfo.DIE;

	switch (m_tMonsterInfo.eState)
	{
	case MONSTERINFO::STATE::IDLE:
		Idle_Tick(TimeDelta);
		m_pModelCom->Set_AnimIndex(7, false);
		break;

	case MONSTERINFO::STATE::MOVE:
		Move_Tick(TimeDelta);
		m_pModelCom->Set_AnimIndex(8, false);
		break;

	case MONSTERINFO::STATE::FIND:
		Find_Tick();
		m_pModelCom->Set_AnimIndex(3, false);
		break;

	case MONSTERINFO::STATE::ATTACK:
		Attack_Tick(TimeDelta);
		m_pModelCom->Set_AnimIndex(1, false);
		break;

	case MONSTERINFO::STATE::HIT:
		Hit_Tick();
		m_pModelCom->Set_AnimIndex(6, false);
		break;

	case MONSTERINFO::STATE::DIE:
		Die_Tick();
		m_pModelCom->Set_AnimIndex(4, false);
		break;
	}
}

void CM_PigWarrior::Idle_Tick(const _double& TimeDelta)
{
	// IDLE 일 때, MOVE 일 때 똑같이 거리 이내 플레이어가 있는지 확인한다.
	_float	fDistance = CObj_Manager::GetInstance()->Get_Player_Distance(m_pTransformCom->Get_State(CTransform::STATE_TRANSLATION));
	if (!m_bAttack && 3.f > fDistance)	// ※ 플레이어 탐색 범위		
		m_tMonsterInfo.eState = m_tMonsterInfo.FIND;

	// 없다면 IDLE 과 MOVE 를 번갈아 가며 실행한다.
	if(m_pModelCom->Animation_Check(7) && m_pModelCom->Get_Finished())
		m_tMonsterInfo.eState = m_tMonsterInfo.MOVE;
}

void CM_PigWarrior::Move_Tick(const _double& TimeDelta)
{
	// 1 : 플레이어를 찾았을 때의 MOVE
	// 2 : 플레이어를 찾지 못 하고 랜덤으로 이동하는 MOVE

	if (m_bFind)		// 플레이어를 찾았을 때! 플레이어와 거리가 1이 될 때 까지 이동한다.
	{
		m_pTransformCom->LookAt(CObj_Manager::GetInstance()->Get_Player_Transform());
		m_pTransformCom->Chase(CObj_Manager::GetInstance()->Get_Player_Transform(), TimeDelta);

		// 거리가 4 안 이라면 플레이어를 따라가서 거리가 1이 될 때 공격한다.
		if (1.f > CObj_Manager::GetInstance()->Get_Player_Distance(m_pTransformCom->Get_State(CTransform::STATE_TRANSLATION)))
			m_tMonsterInfo.eState = m_tMonsterInfo.ATTACK;

		// ※ 플레이어 포기 범위
		if (4.f < CObj_Manager::GetInstance()->Get_Player_Distance(m_pTransformCom->Get_State(CTransform::STATE_TRANSLATION)))
			m_bFind = false; // 크흠.. 범위 벗어났을 때 막 뱅글뱅글 돌면서 회전하는 문제 있음..

	}
	else				// 플레이어를 찾지 못 했을 때 랜덤으로 이동하고 있는다
	{
		// MOVE 일 때, IDLE 일 때 똑같이 거리 이내 플레이어가 있는지 확인한다.
		_float	fDistance = CObj_Manager::GetInstance()->Get_Player_Distance(m_pTransformCom->Get_State(CTransform::STATE_TRANSLATION));
		if (!m_bAttack && 3.f > fDistance)	// ※ 플레이어 탐색 범위
			m_tMonsterInfo.eState = m_tMonsterInfo.FIND;

		//// 없다면 IDLE 과 MOVE 를 번갈아 가며 실행한다.
		//CM_Monster::Random_Move(m_pTransformCom, m_f4CenterPos, TimeDelta);
		//m_dMove_TimeAcc += TimeDelta;	// MOVE 한지 3초가 지나면 Idle 상태로
		//if (3 < m_dMove_TimeAcc)		// ※ 몬스터 MOVE 시간
		//{
		//	m_tMonsterInfo.eState = m_tMonsterInfo.IDLE;
		//	m_bAttack = false;
		//	m_dMove_TimeAcc = 0;
		//}
		if (!CM_Monster::Random_Move(m_pTransformCom, m_f4CenterPos, TimeDelta, 3))
		{
			m_tMonsterInfo.eState = m_tMonsterInfo.IDLE;
			m_bAttack = false;
		}
	}
}

void CM_PigWarrior::Find_Tick()
{
	m_bFind = true;	// 플레이어를 찾았다면 플레이어에게 다가가기 위해서 MOVE로 이동한다.

	if (25 == m_pModelCom->Get_Keyframes())
		m_tMonsterInfo.eState = m_tMonsterInfo.MOVE;

	m_pTransformCom->LookAt(CObj_Manager::GetInstance()->Get_Player_Transform());

	// 3D UI 로 느낌표를 띄워주기 위해서 작성한 코드
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	_vector	vMyPos;
	vMyPos = m_pTransformCom->Get_State(CTransform::STATE_TRANSLATION);

	_float4	f4MyPos;
	XMStoreFloat4(&f4MyPos, vMyPos);

	CUI_3DTexture::TEXTUREINFO	tTextureInfo;
	tTextureInfo.eTextureType = tTextureInfo.TYPE_FIND;
	tTextureInfo.f2Size = _float2(0.7f, 0.7f);
	tTextureInfo.f3Pos = _float3(f4MyPos.x, f4MyPos.y + 1.3f, f4MyPos.z - 0.5f);
	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_GAMEPLAY, TEXT("Layer_Texture_UI_Find_0"), TEXT("Prototype_GameObject_UI_3DTexture"), &tTextureInfo)))
		return;

	RELEASE_INSTANCE(CGameInstance);
}

void CM_PigWarrior::Attack_Tick(const _double& TimeDelta)
{
	m_bFind = false;

	_int	iRandomNum = CUtilities_Manager::GetInstance()->Get_Random(0, 1);

	if (0 == iRandomNum && m_pModelCom->Get_Finished())	// 랜덤으로 0이 들어오면 바로 MOVE로 가고, 1일 때는 ATTACK 이다.
	{
		m_bAttack = true;
		m_tMonsterInfo.eState = m_tMonsterInfo.MOVE;
	}
}

void CM_PigWarrior::Hit_Tick()
{
	if (m_pModelCom->Get_Finished())
		m_tMonsterInfo.eState = m_tMonsterInfo.MOVE;
}

void CM_PigWarrior::Die_Tick()
{
	// 몬스터가 죽고 나면 할 행동

	CGameObject::Set_Dead();
	CObj_Manager::GetInstance()->Set_Player_Exp(m_tMonsterInfo.iExp);	// 플레이어에게 경험치 증가

	if (!m_OneCoin)	// 동전 생성
	{
		// Item
		_vector vMyPos = m_pTransformCom->Get_State(CTransform::STATE_TRANSLATION);
		_float4 vf4MyPos;
		XMStoreFloat4(&vf4MyPos, vMyPos);

		CItemManager::GetInstance()->RandomCoin_Clone(_float3(vf4MyPos.x, vf4MyPos.y, vf4MyPos.z), 5, 1, 0);

		m_OneCoin = true;
	}
}

CM_PigWarrior * CM_PigWarrior::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
{
	CM_PigWarrior*		pInstance = new CM_PigWarrior(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CM_PigWarrior");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CM_PigWarrior::Clone(void * pArg)
{
	CM_PigWarrior*		pInstance = new CM_PigWarrior(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CM_PigWarrior");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CM_PigWarrior::Free()
{
	__super::Free();

	for (auto& pPart : m_MonsterParts)
		Safe_Release(pPart);
	m_MonsterParts.clear();
}