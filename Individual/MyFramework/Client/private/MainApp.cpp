#include "stdafx.h"
#include "..\public\MainApp.h"

#include "GameInstance.h"

#include "Level_Loading.h"
#include "Camera_Dynamic.h"

#include "ImGui_Manager.h"


CMainApp::CMainApp()
	: m_pGameInstance(CGameInstance::GetInstance())
{
	Safe_AddRef(m_pGameInstance);

	/*D3D11_SAMPLER_DESC		SamplerDesc;
	m_pDevice->CreateSamplerState();
	m_pContext->PSSetSamplers();*/	
}

HRESULT CMainApp::Initialize()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	/* ���ӿ��� �ʱ�ȭ */
	GRAPHIC_DESC			GraphicDesc;
	ZeroMemory(&GraphicDesc, sizeof(GRAPHIC_DESC));

	GraphicDesc.hWnd = g_hWnd;
	GraphicDesc.iViewportSizeX = g_iWinSizeX;
	GraphicDesc.iViewportSizeY = g_iWinSizeY;
	GraphicDesc.eWindowMode = GRAPHIC_DESC::WINMODE_WIN;

	if (FAILED(m_pGameInstance->Initialize_Engine(g_hInst, LEVEL_END, GraphicDesc, &m_pDevice, &m_pContext)))
		return E_FAIL;

	if (FAILED(Ready_Prototype_Component()))
		return E_FAIL;

	if (FAILED(Ready_Prototype_GameObject()))
		return E_FAIL;

	if (FAILED(Start_Level(LEVEL_LOGO)))
		return E_FAIL;

#ifdef _DEBUG
	if (::AllocConsole() == TRUE) {
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}
#endif

#if defined (USE_IMGUI)
	// ImGui_Manager �ʱ�ȭ
	CImGui_Manager::GetInstance()->Ready_Imgui();
#endif

	return S_OK;
}

void CMainApp::Tick(_double TimeDelta)
{
	if (nullptr == m_pGameInstance)
		return;

#if defined (USE_IMGUI)
	// ImGui_Manager ������Ʈ
	CImGui_Manager::GetInstance()->Tick_Imgui();
#endif

	m_pGameInstance->Tick_Engine(TimeDelta);
}

HRESULT CMainApp::Render()
{
	if (nullptr == m_pGameInstance || 
		nullptr == m_pRenderer)
		return E_FAIL;

	m_pGameInstance->Clear_Graphic_Device(&_float4(0.5f, 0.5f, 0.5f, 1.f));

	m_pRenderer->Draw_RenderGroup();

	m_pGameInstance->Render_Level();

	m_pGameInstance->Present();

#if defined(USE_IMGUI)
	// ImGui_Manager ������
	CImGui_Manager::GetInstance()->Render_Imgui();
#endif

	return S_OK;
}

HRESULT CMainApp::Start_Level(LEVEL eLevelID)
{
	if (LEVEL_LOADING == eLevelID || 
		nullptr == m_pGameInstance)
		return E_FAIL;

	if (FAILED(m_pGameInstance->Open_Level(LEVEL_LOADING, CLevel_Loading::Create(m_pDevice, m_pContext, eLevelID))))
		return E_FAIL;



	return S_OK;
}

HRESULT CMainApp::Ready_Prototype_Component()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	/* For.Prototype_Component_Renderer */
	if (FAILED(m_pGameInstance->Add_Prototype(CGameInstance::Get_StaticLevelIndex(), TEXT("Prototype_Component_Renderer"),
		m_pRenderer = CRenderer::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	/* For.Prototype_Component_VIBuffer_Rect */
	if (FAILED(m_pGameInstance->Add_Prototype(CGameInstance::Get_StaticLevelIndex(), TEXT("Prototype_Component_VIBuffer_Rect"),
		CVIBuffer_Rect::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_VtxTex */	
	if (FAILED(m_pGameInstance->Add_Prototype(CGameInstance::Get_StaticLevelIndex(), TEXT("Prototype_Component_Shader_VtxTex"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxTex.hlsl"), VTXTEX_DECLARATION::Elements, VTXTEX_DECLARATION::iNumElements))))
		return E_FAIL;


	Safe_AddRef(m_pRenderer);

	return S_OK;
}

HRESULT CMainApp::Ready_Prototype_GameObject()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	/* For.Prototype_GameObject_Camera_Dynamic */
	if (FAILED(m_pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Camera_Dynamic"),
		CCamera_Dynamic::Create(m_pDevice, m_pContext))))
		return E_FAIL;


	return S_OK;
}

CMainApp * CMainApp::Create()
{
	CMainApp*		pInstance = new CMainApp;

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CMainApp");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMainApp::Free()
{
#if defined(USE_IMGUI)
	// ImGui_Manager Free
	CImGui_Manager::GetInstance()->DestroyInstance();
#endif

	Safe_Release(m_pGameInstance);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pContext);
	Safe_Release(m_pDevice);

	CGameInstance::Release_Engine();

#ifdef _DEBUG
	FreeConsole();
#endif
}