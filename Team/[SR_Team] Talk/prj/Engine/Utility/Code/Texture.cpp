#include "..\..\Header\Texture.h"

USING(Engine)
#include "Export_Function.h"

CTexture::CTexture(LPDIRECT3DDEVICE9 pGraphicDev)
	:CComponent(pGraphicDev)
	,m_iFrameEnd(0)
{
}

CTexture::CTexture(const CTexture & rhs)
	:CComponent(rhs)
{
	m_iFrameEnd = rhs.m_iFrameEnd;

	_uint iSize = rhs.m_vecTexture.size();
	m_vecTexture.reserve(iSize);
	m_vecTexture = rhs.m_vecTexture;

	for (_uint i = 0; i < iSize; ++i)
		m_vecTexture[i]->AddRef();	// �İ�ü�� ���������� ��������� �Ѵ�(�����Ϳ���)
									// �׷��� ���� ���縦 �ص� ������ ������
									// Texture(�� Ŭ����) ��ü�� RefCount�� ����������� ��.
}

CTexture::~CTexture()
{
}

HRESULT CTexture::Ready_Texture(const _tchar * pPath, TEXTUREID eType, const _uint & iCnt)
{
	m_vecTexture.reserve(iCnt);

	m_iFrameEnd = iCnt; 

	IDirect3DBaseTexture9*	pTexture = nullptr;

	for (_uint i = 0; i < iCnt; ++i)
	{
		TCHAR	szFileName[256] = L"";
		wsprintf(szFileName, pPath, i);

		switch (eType)
		{
		case TEX_NORMAL:
			if (FAILED(D3DXCreateTextureFromFile(m_pGraphicDev, szFileName, (LPDIRECT3DTEXTURE9*)&pTexture)))
				return E_FAIL;

			break;

		case TEX_CUBE:
			if (FAILED(D3DXCreateCubeTextureFromFile(m_pGraphicDev, szFileName, (LPDIRECT3DCUBETEXTURE9*)&pTexture)))
				return E_FAIL;

			break;
		}

		m_vecTexture.push_back(pTexture);

	}

	return S_OK;
}

void CTexture::Set_Texture(const _uint & iIndex)
{
	if (m_vecTexture.size() <= iIndex)
		return;
	
	// ����� �⺻ ����̽��� ������ �ִ� ��½���(0)���� �ؽ��ĸ� �����ϰ� ������
	// ���߿� ���̴����� �׷���ī��� ���� ������ �ϵ��� �ϴ� ��쵵 ����� �ȴ�.
	m_pGraphicDev->SetTexture(0, m_vecTexture[iIndex]);
}

CTexture * CTexture::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar * pPath, TEXTUREID eType, const _uint & iCnt)
{
	CTexture *		pInstance = new CTexture(pGraphicDev);

	if (FAILED(pInstance->Ready_Texture(pPath, eType, iCnt)))
	{
		MSG_BOX("Texture Create Failed");
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CTexture::Clone(void)
{
	return new CTexture(*this);
}

void CTexture::Free(void)
{
	CComponent::Free();

	for (auto& iter : m_vecTexture)
		Safe_Release(iter);

	m_vecTexture.clear();
}