#include "stdafx.h"
#include "..\public\Level_Loading.h"

#include "Loader.h"
#include "GameInstance.h"
#include "Obj_Manager.h"

#include "Level_Tool.h"
#include "Level_Logo.h"
#include "Level_GamePlay.h"

CLevel_Loading::CLevel_Loading(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CLevel(pDevice, pContext)
{

}

HRESULT CLevel_Loading::Initialize(LEVEL eNextLevelID)
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;

	m_eNextLevelID = eNextLevelID;

	/* eNextLevelID를 위한 자원을 쓰레드에게 준비해라. */
	m_pLoader = CLoader::Create(m_pDevice, m_pContext, eNextLevelID);
	if (nullptr == m_pLoader)
		return E_FAIL;

	/* 로딩씬 구성을 위한 객체를 생성한다. */
	/* 로딩바. 배경. 등등등. */

	return S_OK;
}

void CLevel_Loading::Tick(_double TimeDelta)
{
	__super::Tick(TimeDelta);

}

void CLevel_Loading::Late_Tick(_double TimeDelta)
{
	__super::Late_Tick(TimeDelta);


	CGameInstance*	pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (true == m_pLoader->isFinished())
	{
		if (pGameInstance->Key_Down(DIK_RETURN))
		{
			CLevel*		pLevel = nullptr;

			// ?◐ : 현재 플레이어가 있는 Level 변경 될 때 마다 처리해 주어야 한다.
			CObj_Manager::PLAYERINFO ePlayerInfo;

			switch (m_eNextLevelID)
			{
			case LEVEL_TOOL:
				CObj_Manager::GetInstance()->Set_Plyaer_Level(LEVEL_TOOL);
				pLevel = CLevel_Tool::Create(m_pDevice, m_pContext);
				break;

			case LEVEL_LOGO:
				CObj_Manager::GetInstance()->Set_Plyaer_Level(LEVEL_LOGO);
				pLevel = CLevel_Logo::Create(m_pDevice, m_pContext);
				break;

			case LEVEL_GAMEPLAY:
				CObj_Manager::GetInstance()->Set_Plyaer_Level(LEVEL_GAMEPLAY);
				pLevel = CLevel_GamePlay::Create(m_pDevice, m_pContext);
				break;
			}

			if (nullptr == pLevel)
				return;

			if (FAILED(pGameInstance->Open_Level(m_eNextLevelID, pLevel)))
				return;
		}
	}

	Safe_Release(pGameInstance);
}

HRESULT CLevel_Loading::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;
	
	SetWindowText(g_hWnd, m_pLoader->Get_LoadingText());

	return S_OK;
}

CLevel_Loading * CLevel_Loading::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext, LEVEL eNextLevelID)
{
	CLevel_Loading*		pInstance = new CLevel_Loading(pDevice, pContext);

	if (FAILED(pInstance->Initialize(eNextLevelID)))
	{
		MSG_BOX("Failed to Created : CLevel_Loading");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_Loading::Free()
{
	__super::Free();

	Safe_Release(m_pLoader);

}
