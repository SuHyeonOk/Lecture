#include "stdafx.h"
#include "GreenSlime.h"

#include "Export_Function.h"

CGreenSlime::CGreenSlime(LPDIRECT3DDEVICE9 pGraphicDev)
	: CMonster(pGraphicDev)
	, m_fIdleSpeed(0.f)
	, m_fTimeAcc(0.f)

{
}


CGreenSlime::~CGreenSlime()
{
}

HRESULT CGreenSlime::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	m_pTransCom->Set_Pos(15.f, 0.f, 15.f);

	m_pTransCom->Set_Y(1.f);

	m_eCurState = IDLE;

	m_fSpeed = 5.f;
	m_fIdleSpeed = 3.f;

	return S_OK;
}

_int CGreenSlime::Update_Object(const _float & fTimeDelta)
{

	Engine::CGameObject::Update_Object(fTimeDelta);

	// 애니메이션 변화
	m_fFrame += m_pTextureCom->Get_FrameEnd()  * fTimeDelta;

	if (m_fFrame >= m_pTextureCom->Get_FrameEnd())
		m_fFrame = 0;

	// Animation Tset
	if (Engine::Get_DIKeyState(DIK_P) & 0X80)
		m_eCurState = ATTACK;
	else if (Engine::Get_DIKeyState(DIK_O) & 0X80)
		m_eCurState = HIT;
	else if (Engine::Get_DIKeyState(DIK_I) & 0X80)
		m_eCurState = DIE;

	Motion_Change(fTimeDelta);

	// Animation 컴포넌트에서 하려고 하는것
	// 1. 프레임 변화 : m_fFrame, TextureEndFrame
	// 2. 상태에 따른 버퍼컴포넌트 변경

	Target_Follow(fTimeDelta);
	Billboard();

	Engine::Add_RenderGroup(RENDER_ALPHA, this);

	return 0;
}

void CGreenSlime::LateUpdate_Object(void)
{
	Engine::CGameObject::LateUpdate_Object();
}

void CGreenSlime::Render_Obejct(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0x00);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pTextureCom->Set_Texture((_ulong)m_fFrame);	// 텍스처 정보 세팅을 우선적으로 한다.
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

HRESULT CGreenSlime::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_RcTexCom"));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_RcTexCom", pComponent });

	pComponent = m_pTransCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_TransformCom"));
	NULL_CHECK_RETURN(m_pTransCom, E_FAIL);
	m_mapComponent[ID_DYNAMIC].insert({ L"Proto_TransformCom", pComponent });

	// m_pTextureCom	
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_GreenSlimeIDLE_Texture"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_GreenSlimeIDLE_Texture", pComponent });

	pComponent = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_GreenSlimeATTACK_Texture"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_GreenSlimeATTACK_Texture", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_GreenSlimeHIT_Texture"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_GreenSlimeHIT_Texture", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_GreenSlimeDIE_Texture"));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_mapComponent[ID_STATIC].insert({ L"Proto_GreenSlimeDIE_Texture", pComponent });
	///////

	return S_OK;
}

void CGreenSlime::Target_Follow(const _float & fTimeDelta)
{
	// 플레이어 따라가기
	CTransform*		pPlayerTransformCom = dynamic_cast<CTransform*>(Engine::Get_Component(L"Layer_GameLogic", L"Player", L"Proto_TransformCom", ID_DYNAMIC));
	NULL_CHECK(pPlayerTransformCom);

	_vec3		vPlayerPos, vPos;
	pPlayerTransformCom->Get_Info(INFO_POS, &vPlayerPos);
	m_pTransCom->Get_Info(INFO_POS, &vPos);

	_float fDist = D3DXVec3Length(&(vPlayerPos - vPos));

	if (fDist < 10.f)
	{
		m_eCurState = HIT;
		m_pTransCom->Chase_Target(&vPlayerPos, m_fSpeed, fTimeDelta);
	}
	else
	{
		m_eCurState = IDLE;

		// 몬스터 좌우로 이동하기
		_vec3		vRight;
		m_pTransCom->Get_Info(INFO_RIGHT, &vRight);

		m_fTimeAcc += fTimeDelta;
		if (2.f < m_fTimeAcc)
		{
			m_fIdleSpeed *= -1;
			m_fTimeAcc = 0.f;
		}

		D3DXVec3Normalize(&vRight, &vRight);
		m_pTransCom->Move_Pos(&(vRight * m_fIdleSpeed * fTimeDelta));

		//////
		//_vec3		vSenter = { 15.f, 0.f, 15.f };

		//_float fDist = D3DXVec3Length(&(vSenter - vPos));

		// _float		fRadius = 5.f;

		//if (fDist > fRadius)
		//{
		//	m_fIdleSpeed *= -1;
		//}	

		//D3DXVec3Normalize(&vRight, &vRight);
		//m_pTransCom->Move_Pos(&(vRight * m_fIdleSpeed * vRight));
	}
}

void CGreenSlime::Billboard()
{
	// 빌보드
	_matrix		matWorld, matView, matBill;
	D3DXMatrixIdentity(&matBill);

	m_pTransCom->Get_WorldMatrix(&matWorld);
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);

	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;

	D3DXMatrixInverse(&matBill, 0, &matBill);

	// 현재 지금 이 코드는 문제가 없지만 나중에 문제가 될 수 있음
	m_pTransCom->Set_WorldMatrix(&(matBill * matWorld));
}


CGreenSlime * CGreenSlime::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CGreenSlime *	pInstance = new CGreenSlime(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CGreenSlime::Free(void)
{
	CGameObject::Free();
}

void CGreenSlime::Motion_Change(const _float& fTimeDelta)
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_pTextureCom = static_cast<CTexture*>(Find_Component(L"Proto_GreenSlimeIDLE_Texture", ID_STATIC));
			break;

		case ATTACK:
			m_pTextureCom = static_cast<CTexture*>(Find_Component(L"Proto_GreenSlimeATTACK_Texture", ID_STATIC));
			break;

		case HIT:
			m_pTextureCom = static_cast<CTexture*>(Find_Component(L"Proto_GreenSlimeHIT_Texture", ID_STATIC));
			break;

		case DIE:
			m_pTextureCom = static_cast<CTexture*>(Find_Component(L"Proto_GreenSlimeDIE_Texture", ID_STATIC));
			break;
		}
		m_ePreState = m_eCurState;
	}
}