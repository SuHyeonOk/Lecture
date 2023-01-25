#include "stdafx.h"
#include "..\public\Level_Skeleton_Boss.h"

#include <fstream> // @
#include "Imgui_PropertyEditor.h"	// @

#include "GameInstance.h"
#include "DataManager.h"
#include "Camera_Dynamic.h"
#include "Obj_Manager.h"

#include "O_TextureObject.h"
#include "M_Monster.h"
#include "N_NPC.h"
#include "Food.h"
#include "Coin.h"
#include "Page.h"

#include "S_Jake_Son.h"
#include "Page.h"

CLevel_Skleton_Boss::CLevel_Skleton_Boss(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CLevel(pDevice, pContext)
{

}

HRESULT CLevel_Skleton_Boss::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	if (FAILED(Ready_Lights()))
		return E_FAIL;
	
#ifdef F2_SKELETON

	CObj_Manager::GetInstance()->Set_NextLevel(false);

	if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Finn(TEXT("Layer_Finn"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Jake(TEXT("Layer_Jake"))))
		return E_FAIL;
#else
	if (FAILED(Ready_PreviousData()))
		return E_FAIL;
#endif

	if (FAILED(Ready_Layer_Boss(TEXT("Layer_Gary_Boss"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_SkyBox(TEXT("Layer_SkyBox_Skeleton_Boss"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Map(TEXT("Layer_Skeleton_Boss"))))
		return E_FAIL;

	return S_OK;
}

void CLevel_Skleton_Boss::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

	ImGui();
}

void CLevel_Skleton_Boss::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);

}

HRESULT CLevel_Skleton_Boss::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	//SetWindowText(g_hWnd, TEXT("Level : GAMEPLAY"));

	return S_OK;
}

HRESULT CLevel_Skleton_Boss::Ready_Lights()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	LIGHTDESC			LightDesc;
	ZeroMemory(&LightDesc, sizeof LightDesc);

	LightDesc.eType = LIGHTDESC::TYPE_DIRECTIONAL;
	LightDesc.isEnable = true;
	LightDesc.vDirection = _float4(1.f, -1.f, 1.0f, 0.f);
	LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.4f, 0.4f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.f, 1.f, 1.f);

	if (FAILED(pGameInstance->Add_Light(m_pDevice, m_pContext, LightDesc)))
		return E_FAIL;

	ZeroMemory(&LightDesc, sizeof LightDesc);

	LightDesc.eType = LIGHTDESC::TYPE_POINT;
	LightDesc.isEnable = true;
	/*LightDesc.vDirection = _float4(1.f, -1.f, 1.0f, 0.f);*/
	LightDesc.vPosition = _float4(5.f, 3.f, 5.f, 1.f);
	LightDesc.fRange = 10.0f;
	LightDesc.vDiffuse = _float4(1.f, 0.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(0.4f, 0.2f, 0.2f, 0.2f);
	LightDesc.vSpecular = LightDesc.vDiffuse;

	if (FAILED(pGameInstance->Add_Light(m_pDevice, m_pContext, LightDesc)))
		return E_FAIL;


	ZeroMemory(&LightDesc, sizeof LightDesc);

	LightDesc.eType = LIGHTDESC::TYPE_POINT;
	LightDesc.isEnable = true;
	/*LightDesc.vDirection = _float4(1.f, -1.f, 1.0f, 0.f);*/
	LightDesc.vPosition = _float4(10.f, 3.f, 5.f, 1.f);
	LightDesc.fRange = 10.0f;
	LightDesc.vDiffuse = _float4(0.f, 1.f, 0.f, 1.f);
	LightDesc.vAmbient = _float4(0.2f, 0.4f, 0.2f, 0.2f);
	LightDesc.vSpecular = LightDesc.vDiffuse;

	if (FAILED(pGameInstance->Add_Light(m_pDevice, m_pContext, LightDesc)))
		return E_FAIL;


	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Skleton_Boss::Ready_PreviousData()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CNavigation * pObjNavigationCom = nullptr;

	CTransform * pObjTransformCom;
	pObjTransformCom = dynamic_cast<CTransform*>(pGameInstance->Get_ComponentPtr(CGameInstance::Get_StaticLevelIndex(), TEXT("Layer_Finn"), TEXT("Com_Transform"), 0));
	pObjTransformCom->Set_Pos(_float3(7.0f, 0.0f, 0.0f));

	pObjTransformCom = dynamic_cast<CTransform*>(pGameInstance->Get_ComponentPtr(CGameInstance::Get_StaticLevelIndex(), TEXT("Layer_Jake"), TEXT("Com_Transform"), 0));
	pObjTransformCom->Set_Pos(_float3(8.0f, 0.0f, 0.0f));

	pObjTransformCom = dynamic_cast<CTransform*>(pGameInstance->Get_ComponentPtr(CGameInstance::Get_StaticLevelIndex(), TEXT("Layer_Camera"), TEXT("Com_Transform"), 0));
	pObjTransformCom->Set_Pos(_float3(7.0f, 0.0f, 0.0f));

	pObjNavigationCom = dynamic_cast<CNavigation*>(pGameInstance->Get_ComponentPtr(CGameInstance::Get_StaticLevelIndex(), TEXT("Layer_Finn"), TEXT("Com_Navigation"), 0));	
	pObjNavigationCom->Ready_NextLevel(TEXT("../../Data/Navi_Skeleton_Boss.txt"));
	pObjNavigationCom->Set_CellIndex(22);

	pObjNavigationCom = dynamic_cast<CNavigation*>(pGameInstance->Get_ComponentPtr(CGameInstance::Get_StaticLevelIndex(), TEXT("Layer_Jake"), TEXT("Com_Navigation"), 0));
	pObjNavigationCom->Ready_NextLevel(TEXT("../../Data/Navi_Skeleton_Boss.txt"));
	pObjNavigationCom->Set_CellIndex(22);

	pObjNavigationCom = dynamic_cast<CNavigation*>(pGameInstance->Get_ComponentPtr(CGameInstance::Get_StaticLevelIndex(), TEXT("Layer_BackGround"), TEXT("Com_Navigation"), 0));
	pObjNavigationCom->Ready_NextLevel(TEXT("../../Data/Navi_Skeleton_Boss.txt"));

	CObj_Manager::GetInstance()->Set_NextLevel(false);

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Skleton_Boss::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Clone_GameObject(CGameInstance::Get_StaticLevelIndex(), pLayerTag, TEXT("Prototype_GameObject_Terrain"), &_float3(-50.f, 0.f, -20.f))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Skleton_Boss::Ready_Layer_SkyBox(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_SKELETON_BOSS, pLayerTag, TEXT("Prototype_GameObject_Sky"))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Skleton_Boss::Ready_Layer_Camera(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CCamera_Dynamic::CAMERAINFO eCameraInfo;
	eCameraInfo.eLevel = LEVEL_SKELETON_BOSS;
	eCameraInfo.f3Pos = _float3(7.0f, 0.f, 0.f);
	if (FAILED(pGameInstance->Clone_GameObject(CGameInstance::Get_StaticLevelIndex(), pLayerTag, TEXT("Prototype_GameObject_Camera_Dynamic"), &eCameraInfo)))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Skleton_Boss::Ready_Layer_Finn(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Clone_GameObject(CGameInstance::Get_StaticLevelIndex(), pLayerTag, TEXT("Prototype_GameObject_Finn"), &_float3(7.0f, 0.f, 0.f))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Skleton_Boss::Ready_Layer_Jake(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Clone_GameObject(CGameInstance::Get_StaticLevelIndex(), pLayerTag, TEXT("Prototype_GameObject_Jake"), &_float3(8.0f, 0.f, 0.f))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Skleton_Boss::Ready_Layer_Boss(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_SKELETON_BOSS, pLayerTag, TEXT("Prototype_GameObject_M_Gary_Boss"), &_float3(4.0f, 0.0f, 17.0f))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Skleton_Boss::Ready_Layer_Map(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_SKELETON_BOSS, pLayerTag, TEXT("Prototype_GameObject_Map_Skeleton_Boss"))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

void CLevel_Skleton_Boss::ImGui()
{
	const _char* szObjName[] = { "Box", "JakeSon_Test", "Page_Paint","Page_Marcelint", "Page_Coin", "Page_Fiona", "Page_JakeSon" };
	static int iObjNum = 0;
	ImGui::Combo("##2_Object", &iObjNum, szObjName, IM_ARRAYSIZE(szObjName));


	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	_float4		f4MousePos;
	f4MousePos = pGameInstance->Get_MousePos();

	CPage::PAGEINFO		tPageInfo;

	if (pGameInstance->Mouse_Down(CInput_Device::DIM_MB))
	{
		m_f3ClickPos = { f4MousePos.x, f4MousePos.y, f4MousePos.z };

		if (0 == iObjNum)
		{
			if (FAILED(pGameInstance->Clone_GameObject(LEVEL_SKELETON, TEXT("Prototype_GameObject_O_Box"), TEXT("Prototype_GameObject_O_Box"), &m_f3ClickPos)))
				return;
		}
		else if (1 == iObjNum)
		{
			CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

			CS_Jake_Son::JAKESONINFO tJakeSonInfo;
			tJakeSonInfo.eJakeSon = CS_Jake_Son::JAKESONINFO::JAKESON::JAKE_SON_E;
			tJakeSonInfo.fPos = m_f3ClickPos;
			if (FAILED(pGameInstance->Clone_GameObject(LEVEL_SKELETON, TEXT("Prototype_GameObject_S_Jake_Son"), TEXT("Prototype_GameObject_S_Jake_Son"), &tJakeSonInfo)))
				return;

			RELEASE_INSTANCE(CGameInstance);

		}
		if (2 == iObjNum)
		{
			tPageInfo.fPos = m_f3ClickPos;
			tPageInfo.ePlayerSkill = CSkill_Manager::PLAYERSKILL::SKILL::PAINT;

			if (FAILED(pGameInstance->Clone_GameObject(LEVEL_SKELETON, TEXT("Prototype_GameObject_Page"), TEXT("Prototype_GameObject_Page"), &tPageInfo)))
				return;
		}
		if (3 == iObjNum)
		{
			tPageInfo.fPos = m_f3ClickPos;
			tPageInfo.ePlayerSkill = CSkill_Manager::PLAYERSKILL::SKILL::MARCELINT;

			if (FAILED(pGameInstance->Clone_GameObject(LEVEL_SKELETON, TEXT("Prototype_GameObject_Page"), TEXT("Prototype_GameObject_Page"), &tPageInfo)))
				return;
		}
		if (4 == iObjNum)
		{
			tPageInfo.fPos = m_f3ClickPos;
			tPageInfo.ePlayerSkill = CSkill_Manager::PLAYERSKILL::SKILL::COIN;

			if (FAILED(pGameInstance->Clone_GameObject(LEVEL_SKELETON, TEXT("Prototype_GameObject_Page"), TEXT("Prototype_GameObject_Page"), &tPageInfo)))
				return;
		}
		if (5 == iObjNum)
		{
			tPageInfo.fPos = m_f3ClickPos;
			tPageInfo.ePlayerSkill = CSkill_Manager::PLAYERSKILL::SKILL::FIONA;

			if (FAILED(pGameInstance->Clone_GameObject(LEVEL_SKELETON, TEXT("Prototype_GameObject_Page"), TEXT("Prototype_GameObject_Page"), &tPageInfo)))
				return;
		}
		if (6 == iObjNum)
		{
			tPageInfo.fPos = m_f3ClickPos;
			tPageInfo.ePlayerSkill = CSkill_Manager::PLAYERSKILL::SKILL::JAKESON;

			if (FAILED(pGameInstance->Clone_GameObject(LEVEL_SKELETON, TEXT("Prototype_GameObject_Page"), TEXT("Prototype_GameObject_Page"), &tPageInfo)))
				return;
		}
	}

	RELEASE_INSTANCE(CGameInstance);
}

CLevel_Skleton_Boss * CLevel_Skleton_Boss::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
{
	CLevel_Skleton_Boss*		pInstance = new CLevel_Skleton_Boss(pDevice, pContext);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_Skleton_Boss");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_Skleton_Boss::Free()
{
	__super::Free();


}

