#include "stdafx.h"
#include "..\public\DataManager.h"

IMPLEMENT_SINGLETON(CDataManager)

CDataManager::CDataManager()
{
}

void CDataManager::Set_FoodInfo(const _tchar & ObjName, const _float3 & ObjPos)
{
	OBJINFO		eObjInfo;
	memcpy(eObjInfo.ObjName, &ObjName, sizeof(_char[MAX_PATH]));
	eObjInfo.ObjPos = ObjPos;

	m_vecFoodInfo.push_back(eObjInfo);
}

void CDataManager::Set_CoinInfo(const _tchar & ObjName, const _float3 & ObjPos)
{
	OBJINFO		eObjInfo;
	memcpy(eObjInfo.ObjName, &ObjName, sizeof(_char[MAX_PATH]));
	eObjInfo.ObjPos = ObjPos;

	m_vecCoinInfo.push_back(eObjInfo);
}

void CDataManager::Set_PageInfo(const _tchar & ObjName, const _float3 & ObjPos)
{
	OBJINFO		eObjInfo;
	memcpy(eObjInfo.ObjName, &ObjName, sizeof(_char[MAX_PATH]));
	eObjInfo.ObjPos = ObjPos;

	m_vecPageInfo.push_back(eObjInfo);
}

void CDataManager::Set_MonsterInfo(const _tchar & ObjName, const _float3 & ObjPos)
{
	OBJINFO		eObjInfo;
	memcpy(eObjInfo.ObjName, &ObjName, sizeof(_char[MAX_PATH]));
	eObjInfo.ObjPos = ObjPos;

	m_vecMonsterInfo.push_back(eObjInfo);
}

void CDataManager::Free()
{
}
