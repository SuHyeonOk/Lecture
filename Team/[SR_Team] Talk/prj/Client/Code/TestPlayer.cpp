#include "stdafx.h"
#include "..\Header\TestPlayer.h"

#include "Export_Function.h"

CTestPlayer::CTestPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_vDirection(0.f, 0.f, 0.f)
{
}


CTestPlayer::~CTestPlayer()
{
}

HRESULT CTestPlayer::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

_int CTestPlayer::Update_Object(const _float & fTimeDelta)
{
	Key_Input(fTimeDelta);
	Engine::CGameObject::Update_Object(fTimeDelta);
	Add_RenderGroup(RENDER_NONALPHA, this); // TestPlayer�� �����׷쿡 ����
	return 0;
}

void CTestPlayer::LateUpdate_Object(void)
{
	Set_OnTerrain();
	//Engine::CGameObject::LateUpdate_Object();
}

void CTestPlayer::Render_Obejct(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pTextureCom->Set_Texture(0);

	m_pBufferCom->Render_Buffer();
	
	// TestPlayer�� ���� ������Ʈ�� ��� �� ������ ������ �����ؾ߸� �ٸ� ������Ʈ�� �ݿ����� �ʴ´�.
	// m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

HRESULT CTestPlayer::Add_Component(void)
{
	CComponent*		pComponent = nullptr;

	// �������� ���� ������Ʈ
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTexCom", pComponent });

	// �ؽ��� �İ�ü ���� ������Ʈ
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Clone_Proto(L"Proto_PlayerTexture"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_PlayerTexture", pComponent });

	// ������� ��ȯ Ʈ������ ������Ʈ
	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	// ����Ÿ��� ��� ������Ʈ
	pComponent = m_pCalculatorCom = dynamic_cast<CCalculator*>(Clone_Proto(L"Proto_CalculatorCom"));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_CalculatorCom", pComponent });
	
	return S_OK;
}

void CTestPlayer::Key_Input(const _float & fTimeDelta)
{
	m_pTransCom->Get_Info(INFO_LOOK, &m_vDirection);

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		D3DXVec3Normalize(&m_vDirection, &m_vDirection);
		m_pTransCom->Move_Pos(&(m_vDirection * 10.f * fTimeDelta));
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		D3DXVec3Normalize(&m_vDirection, &m_vDirection);
		m_pTransCom->Move_Pos(&(m_vDirection * -10.f * fTimeDelta));
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_pTransCom->Rotation(ROT_Y, D3DXToRadian(180.f * fTimeDelta));

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_pTransCom->Rotation(ROT_Y, D3DXToRadian(-180.f * fTimeDelta));

}

void CTestPlayer::Set_OnTerrain(void)
{
	_vec3		vPos;
	m_pTransCom->Get_Info(INFO_POS, &vPos);

	Engine::CTerrainTex*	pTerrainTexCom = dynamic_cast<Engine::CTerrainTex*>(Engine::Get_Component(L"Layer_Environment", L"Terrain", L"Proto_TerrainTexCom", ID_STATIC));
	NULL_CHECK(pTerrainTexCom);

	_float fHeight = m_pCalculatorCom->HeightOnTerrain(&vPos, pTerrainTexCom->Get_VtxPos(), VTXCNTX, VTXCNTZ);

	m_pTransCom->Set_Pos(vPos.x, fHeight + 1.f, vPos.z);
}

CTestPlayer * CTestPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTestPlayer *	pInstance = new CTestPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CTestPlayer::Free(void)
{
	CGameObject::Free();
}