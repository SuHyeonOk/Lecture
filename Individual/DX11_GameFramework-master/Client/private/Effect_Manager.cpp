#include "stdafx.h"
#include "..\public\Effect_Manager.h"

#include "GameInstance.h"
#include "Utilities_Manager.h"

IMPLEMENT_SINGLETON(CEffect_Manager)

CEffect_Manager::CEffect_Manager()
{
}

void CEffect_Manager::Food_Up(_float3 fSize)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_GAMEPLAY, TEXT("Layer_Texture_Effect"), TEXT("Prototype_GameObject_E_Food_Up"), &fSize)))
		return;

	RELEASE_INSTANCE(CGameInstance);
}

void CEffect_Manager::Change_Smoke(_float3 fSize)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	_float	fRandomNumberX = CUtilities_Manager::GetInstance()->Get_Random(-0.5f, 0.5f);
	_float	fRandomNumberY = CUtilities_Manager::GetInstance()->Get_Random(-0.5f, 0.5f);

	fSize = _float3(fSize.x * fRandomNumberX, fSize.y * fRandomNumberY, fSize.z);

	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_GAMEPLAY, TEXT("Layer_Texture_Effect"), TEXT("Prototype_GameObject_E_Smoke"), &fSize)))
		return;

	RELEASE_INSTANCE(CGameInstance);
}

void CEffect_Manager::Skill_Marceline_Waves_Create(_float3 fSize)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_GAMEPLAY, TEXT("Layer_Texture_Effect"), TEXT("Prototype_GameObject_E_Skill_Marceline_Waves"), &fSize)))
		return;

	RELEASE_INSTANCE(CGameInstance);
}

void CEffect_Manager::Skill_Marceline_Sound_Create(_float3 fSize)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	_float	fRandomNumberX = CUtilities_Manager::GetInstance()->Get_Random(-2.0f, 2.0f);
	_float	fRandomNumberY = CUtilities_Manager::GetInstance()->Get_Random(0.6f, 2.0f);
	_float	fRandomNumberZ = CUtilities_Manager::GetInstance()->Get_Random(0.0f, 2.0f);

	_int fRandomPos = CUtilities_Manager::GetInstance()->Get_Random(0, 4);

	if (0 == fRandomPos)
		fSize = _float3(fSize.x + fRandomNumberX, fSize.y + fRandomNumberY, fSize.z + fRandomNumberZ);
	else if (1 == fRandomPos)
		fSize = _float3(fSize.x - fRandomNumberX, fSize.y + fRandomNumberY, fSize.z + fRandomNumberZ);
	else if (2 == fRandomPos)
		fSize = _float3(fSize.x + fRandomNumberX, fSize.y + fRandomNumberY, fSize.z - fRandomNumberZ);
	else if (3 == fRandomPos)
		fSize = _float3(fSize.x - fRandomNumberX, fSize.y + fRandomNumberY, fSize.z - fRandomNumberZ);

	//_float	fRandomNumber = CUtilities_Manager::GetInstance()->Get_Random(-1.0f, 1.0f);

	//fSize.x *= fRandomNumber;
	//fSize.y *= fRandomNumber;
	//fSize.z *= fRandomNumber;

	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_GAMEPLAY, TEXT("Layer_Texture_Effect"), TEXT("Prototype_GameObject_E_Skill_Marceline_Sound"), &fSize)))
		return;

	RELEASE_INSTANCE(CGameInstance);
}

void CEffect_Manager::DieCenter_Create(CE_DieCenter::DIECENTERINFO tDieCenter)
{
	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	_float	fRandomNumber = CUtilities_Manager::GetInstance()->Get_Random(-0.1f, 0.1f);

	CE_DieCenter::DIECENTERINFO	tDieCenterInfo;
	tDieCenterInfo.eMonsterKind = tDieCenter.eMonsterKind;
	tDieCenterInfo.f3Pos = _float3(tDieCenter.f3Pos.x + fRandomNumber, tDieCenter.f3Pos.y + fRandomNumber, tDieCenter.f3Pos.z);
 	if (FAILED(pGameInstance->Clone_GameObject(LEVEL_GAMEPLAY, TEXT("Layer_Texture_Effect"), TEXT("Prototype_GameObject_E_DieCenter"), &tDieCenterInfo)))
		return;

	RELEASE_INSTANCE(CGameInstance);
}

void CEffect_Manager::Free()
{
}
