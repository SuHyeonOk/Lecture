#include "..\public\Camera.h"
#include "GameInstance.h"
#include "PipeLine.h"

CCamera::CCamera(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CGameObject(pDevice, pContext)
	, m_pPipeLine(CPipeLine::GetInstance())
{
	Safe_AddRef(m_pPipeLine);	
}

CCamera::CCamera(const CCamera & rhs) 
	: CGameObject(rhs)
	, m_pPipeLine(rhs.m_pPipeLine)
{
	Safe_AddRef(m_pPipeLine);
	
}

HRESULT CCamera::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCamera::Initialize(void * pArg)
{
	CAMERADESC	CameraDesc;
	ZeroMemory(&CameraDesc, sizeof(CAMERADESC));

	if (nullptr != pArg)
		memcpy(&CameraDesc, pArg, sizeof(CameraDesc));

	if (FAILED(__super::Initialize(&CameraDesc)))
		return E_FAIL;

	/* 카메라(게임오브젝트)가 들고있는 트랜스폼에 카메라의 상태를 동기화한다. */
	m_pTransformCom->Set_State(CTransform::STATE_TRANSLATION, XMLoadFloat4(&CameraDesc.vEye));
	m_pTransformCom->LookAt(XMLoadFloat4(&CameraDesc.vAt));

	return S_OK;
}

void CCamera::Tick(_double TimeDelta)
{
	if (nullptr == m_pPipeLine)
		return;

 	m_pPipeLine->Set_Transform(CPipeLine::D3DTS_VIEW, m_pTransformCom->Get_WorldMatrix_Inverse());
	m_pPipeLine->Set_Transform(CPipeLine::D3DTS_PROJ, XMMatrixPerspectiveFovLH(XMConvertToRadians(60.0f), 1280 / 720.f, 0.2f, 300.f));
}

void CCamera::Late_Tick(_double TimeDelta)
{
}

HRESULT CCamera::Render()
{
	return S_OK;
}



void CCamera::Free()
{
	__super::Free();

	Safe_Release(m_pPipeLine);

}
