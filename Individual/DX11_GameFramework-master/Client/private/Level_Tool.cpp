#include "stdafx.h"
#include "..\public\Level_Tool.h"

#include "GameInstance.h"

#include "M_Monster.h"
#include "Coin.h"
#include "Page.h"

#include "B_Star.h"

CLevel_Tool::CLevel_Tool(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CLevel(pDevice, pContext)
{

}

HRESULT CLevel_Tool::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;
	
	if (FAILED(Ready_Layer_UI_Informacion(TEXT("Layer_UI_Informacion"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Bullet(TEXT("Layer_Bullet"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Player(TEXT("Layer_Player"))))
		return E_FAIL;

	if (FAILED(Ready_Lights()))
		return E_FAIL;

	//if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
	//	return E_FAIL;

	if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
		return E_FAIL;

	return S_OK;
}

void CLevel_Tool::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);
}

void CLevel_Tool::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);

}

HRESULT CLevel_Tool::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

	//SetWindowText(g_hWnd, TEXT("Level : TOOL"));

	return S_OK;
}

HRESULT CLevel_Tool::Ready_Layer_UI_Informacion(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Clone_GameObject(CGameInstance::Get_StaticLevelIndex(), pLayerTag, TEXT("Prototype_GameObject_UI_Informacion"))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Tool::Ready_Layer_Bullet(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	CB_Star::BULLETINFO		tBulletInfo;
	tBulletInfo.f3Start_Pos = _float3(4.f, 0.f, 0.f);
	tBulletInfo.f3Target_Pos = _float3(4.f, 0.f, 0.f);
	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_TOOL, TEXT("Layer_Bullet"), TEXT("Prototype_GameObject_B_Star"), &tBulletInfo)))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Tool::Ready_Layer_Player(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Clone_GameObject(CGameInstance::Get_StaticLevelIndex(), TEXT("Layer_Finn"), TEXT("Prototype_GameObject_Finn"), &_float3(5.f, 0.f, 0.f))))
		return E_FAIL;

	if (FAILED(pGameInstance->Clone_GameObject(CGameInstance::Get_StaticLevelIndex(), TEXT("Layer_Jake"), TEXT("Prototype_GameObject_Jake"), &_float3(7.f, 0.f, 0.f))))
		return E_FAIL;

	CCoin::COININFO					tObjInfo;
	tObjInfo.fPos = _float3(2.f, 0.f, 0.f);
	tObjInfo.eState = tObjInfo.IDLE;
	tObjInfo.eCoinKind = tObjInfo.COIN_BRONZE;
	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_TOOL, pLayerTag, TEXT("Prototype_GameObject_Coin"), &tObjInfo)))
		return E_FAIL;

	//CPage::PAGEINFO					tPageInfo;
	//if (FAILED(pGameInstance->Clone_GameObject(LEVEL_TOOL, pLayerTag, TEXT("Prototype_GameObject_Page"), &tPageInfo)))
	//	return E_FAIL;

	CM_Monster::MONSTERDESC		tMonsterDesc;
	tMonsterDesc.f3Pos = _float3(-5.f, 0.f, 0.f);
	tMonsterDesc.eMonsterKind = tMonsterDesc.W_BEE;
	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_TOOL, TEXT("M_PigWarrior_BEE_0"), TEXT("Prototype_GameObject_M_PigWarrior"), &tMonsterDesc)))
		return E_FAIL;
	tMonsterDesc.f3Pos = _float3(-5.f, 0.f, 2.f);
	tMonsterDesc.eMonsterKind = tMonsterDesc.W_WORKER;
	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_TOOL, TEXT("M_PigWarrior_BEE_1"), TEXT("Prototype_GameObject_M_PigWarrior"), &tMonsterDesc)))
		return E_FAIL;
	tMonsterDesc.f3Pos = _float3(-7.f, 0.f, 0.f);
	tMonsterDesc.eMonsterKind = tMonsterDesc.S_COWBOY;
	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_TOOL, TEXT("M_PigWarrior_BEE_0"), TEXT("Prototype_GameObject_M_Pigs"), &tMonsterDesc)))
		return E_FAIL;
	tMonsterDesc.f3Pos = _float3(-7.f, 0.f, 2.f);
	tMonsterDesc.eMonsterKind = tMonsterDesc.S_SR;
	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_TOOL, TEXT("M_PigWarrior_BEE_0"), TEXT("Prototype_GameObject_M_Pigs"), &tMonsterDesc)))
		return E_FAIL;

	tMonsterDesc.f3Pos = _float3(-5.f, 2.f, 2.f);
	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_TOOL, TEXT("M_Gronmes_RED_0"), TEXT("Prototype_GameObject_M_Gronmes_RED"), &tMonsterDesc)))
		return E_FAIL;
	tMonsterDesc.f3Pos = _float3(-4.f, 2.f, 2.f);
	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_TOOL, TEXT("M_Gronmes_RED_1"), TEXT("Prototype_GameObject_M_Gronmes_RED"), &tMonsterDesc)))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Tool::Ready_Lights()
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	LIGHTDESC			LightDesc;
	ZeroMemory(&LightDesc, sizeof LightDesc);

	LightDesc.eType = LIGHTDESC::TYPE_DIRECTIONAL;
	LightDesc.isEnable = true;
	LightDesc.vDirection = _float4(1.f, -1.f, 1.0f, 0.f);
	LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
	LightDesc.vAmbient = _float4(1.f, 1.f, 1.f, 1.f);
	LightDesc.vSpecular = _float4(1.f, 1.f, 1.f, 1.f);

	if (FAILED(pGameInstance->Add_Light(m_pDevice, m_pContext, LightDesc)))
		return E_FAIL;

	//ZeroMemory(&LightDesc, sizeof LightDesc);

	//LightDesc.eType = LIGHTDESC::TYPE_POINT;
	//LightDesc.isEnable = true;
	///*LightDesc.vDirection = _float4(1.f, -1.f, 1.0f, 0.f);*/
	//LightDesc.vPosition = _float4(5.f, 3.f, 5.f, 1.f);
	//LightDesc.fRange = 10.0f;
	//LightDesc.vDiffuse = _float4(1.f, 1.f, 1.f, 1.f);
	//LightDesc.vAmbient = _float4(1.f, 1.f, 1.f, 1.f);
	//LightDesc.vSpecular = _float4(1.f, 1.f, 1.f, 1.f);

	//if (FAILED(pGameInstance->Add_Light(m_pDevice, m_pContext, LightDesc)))
	//	return E_FAIL;


	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Tool::Ready_Layer_BackGround(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_TOOL, pLayerTag, TEXT("Prototype_GameObject_Terrain"))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

HRESULT CLevel_Tool::Ready_Layer_Camera(const _tchar * pLayerTag)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_TOOL, pLayerTag, TEXT("Prototype_GameObject_Camera_Dynamic"))))
		return E_FAIL;

	RELEASE_INSTANCE(CGameInstance);

	return S_OK;
}

CLevel_Tool * CLevel_Tool::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
{
	CLevel_Tool*		pInstance = new CLevel_Tool(pDevice, pContext);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_Tool");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_Tool::Free()
{
	__super::Free();


}

