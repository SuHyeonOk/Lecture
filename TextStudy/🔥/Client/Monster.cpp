#include "stdafx.h"
#include "Monster.h"

#include "TextureMgr.h"
#include "Device.h"

CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}



HRESULT CMonster::Initialize(void)
{
	m_sTag = "Tag_Annie";

	m_wstrObjKey = L"Monster";
	m_wstrStateKey = L"Annie";

	m_tFrame = { 0.f, 0.f };

	m_tInfo.vPos = { 300.f, 400.f, 0.f };

	m_tCollisionInfo.vPos = { 300.f, 400.f, 0.f };
	m_tCollisionInfo.vLook = { 0.f, -1.f, 0.f };

	m_fRadius = 25.f;
	m_vPoint[0] = { m_tCollisionInfo.vPos.x - m_fRadius, m_tCollisionInfo.vPos.y - m_fRadius, 0.f };
	m_vPoint[1] = { m_tCollisionInfo.vPos.x + m_fRadius, m_tCollisionInfo.vPos.y - m_fRadius, 0.f };
	m_vPoint[2] = { m_tCollisionInfo.vPos.x + m_fRadius, m_tCollisionInfo.vPos.y + m_fRadius, 0.f };
	m_vPoint[3] = { m_tCollisionInfo.vPos.x - m_fRadius, m_tCollisionInfo.vPos.y + m_fRadius, 0.f };

	for (int i = 0; i < 4; ++i)
		m_vOriginPoint[i] = m_vPoint[i];

	return S_OK;
}

int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	D3DXMATRIX	matScale, matTrans;

	D3DXMatrixScaling(&matScale, 0.3f, 0.3f, 0.3f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + CObj::m_vScroll.x,
		m_tInfo.vPos.y + CObj::m_vScroll.y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;

	m_tCollisionInfo.matWorld = matScale * matTrans;

	for (int i = 0; i < 4; ++i)
	{
		m_vPoint[i] = m_vOriginPoint[i];
		m_vPoint[i] -= {300.f, 400.f, 0.f};
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], &m_tCollisionInfo.matWorld);
	}

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	Move_Frame();
}

void CMonster::Render()
{
	const TEXINFO*		pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);

	float	fCenterX = pTexInfo->tImgInfo.Width / 2.f;
	float	fCenterY = pTexInfo->tImgInfo.Height / 2.f;

	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr,
		D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CMonster::Release(void)
{
}



void CMonster::OnCollision(CObj * pOther)
{

}