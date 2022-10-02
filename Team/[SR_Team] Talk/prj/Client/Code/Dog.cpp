#include "stdafx.h"
#include "..\Header\Dog.h"

#include "Export_Function.h"

#include "TalkWindow.h"

CDog::CDog(LPDIRECT3DDEVICE9 pGraphicDev)
	:CNPC(pGraphicDev)
{
}


CDog::~CDog()
{
}

HRESULT CDog::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransCom->Set_Pos(0.f, 1.f, 3.f);

	return S_OK;
}

_int CDog::Update_Object(const _float & fTimeDelta)
{
	Engine::CGameObject::Update_Object(fTimeDelta);
	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	m_pTransCom->Set_Y(1.f);
	m_pAnimtorCom->Play_Animation(fTimeDelta);
	
	OnText();

	return 0;
}

void CDog::LateUpdate_Object(void)
{
	CNPC::Billboard();
	Engine::CGameObject::LateUpdate_Object();
}

void CDog::Render_Obejct(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0x00);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pAnimtorCom->Set_Texture();
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

HRESULT CDog::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTexCom", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	// m_pAnimtorCom
	pComponent = m_pAnimtorCom = dynamic_cast<CAnimator*>(Engine::Clone_Proto(L"Proto_AnimatorCom"));
	NULL_CHECK_RETURN(m_pAnimtorCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_AnimatorCom", pComponent });

	m_pAnimtorCom->Add_Component(L"Proto_NPC_Dog_Texture");

	return S_OK;
}

void CDog::OnText()
{
	CTransform* pPlayerTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_GameLogic", L"Player", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK(pPlayerTransformCom);

	_vec3 vPlayerPos, vPos;
	pPlayerTransformCom->Get_Info(INFO_POS, &vPlayerPos);
	m_pTransCom->Get_Info(INFO_POS, &vPos);

	_float fDist = D3DXVec3Length(&(vPlayerPos - vPos));

	if (fDist < 2.f) // �Ÿ� �� ���� ���� �� ��ȭ ����
	{
		CTalkWindow* pTalkWindow = dynamic_cast<CTalkWindow*>(Engine::Get_GameObject(L"Layer_UI", L"TalkWindow"));
		NULL_CHECK(pTalkWindow);

		pTalkWindow->Set_Text(true);

	}
	else
	{
		CTalkWindow* pTalkWindow = dynamic_cast<CTalkWindow*>(Engine::Get_GameObject(L"Layer_UI", L"TalkWindow"));
		NULL_CHECK(pTalkWindow);

		pTalkWindow->Set_Text(false);
	}
}

CDog * CDog::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDog *	pInstance = new CDog(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CDog::Free(void)
{
	CNPC::Free();
}