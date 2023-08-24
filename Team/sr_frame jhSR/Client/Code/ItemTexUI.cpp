#include "stdafx.h"
#include "ItemTexUI.h"


CItemTexUI::CItemTexUI(LPDIRECT3DDEVICE9 pGraphicDev) : CUI(pGraphicDev)
{
}


CItemTexUI::~CItemTexUI()
{
}

HRESULT CItemTexUI::Ready_Object()
{
	D3DXMatrixOrthoLH(&m_ProjMatrix, WINCX, WINCY, 0.f, 1.f);

	m_pBufferCom = Add_Component<CRcTex>(L"Proto_RcTexCom", L"Proto_RcTexCom", ID_STATIC);
	m_pTextureCom = Add_Component<CTexture>(L"Proto_InventoryUI_Texture", L"Proto_InventoryUI_Texture", ID_STATIC);
	m_pTransCom = Add_Component<CTransform>(L"Proto_TransformCom", L"Proto_TransformCom", ID_DYNAMIC);


	m_iTexNum = 0;
	m_iRenderPriority = 9;
	return S_OK;
}

_int CItemTexUI::Update_Object(const _float & fTimeDelta)
{
	if (m_bClose)
		return OBJ_NOEVENT;

	CUI::Update_Object(fTimeDelta);


	if (m_bWorldSet == false)
	{
		_vec3 vScale = m_pTransCom->m_vScale;
		_vec3 vPos = _vec3(WINCX * 0.37f, WINCY * 0.29f, 0.f);
		_vec3 vAngle = m_pTransCom->m_vAngle;
		vScale.x *= 0.1f;
		vScale.y *= 0.15f;
		CGameUtilMgr::MatWorldComposeEuler(matworld, vScale, vAngle, vPos);

		m_bWorldSet = true;
	}
	
		
	

	return OBJ_NOEVENT;
}

void CItemTexUI::Render_Object()
{
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &CGameUtilMgr::s_matIdentity);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);



	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransCom->Get_WorldMatrixPointer());
	m_pTextureCom->Set_Texture(m_iTexNum);
	m_pBufferCom->Render_Buffer();

	SetTexture(m_iTexNum);

	_vec3 vPos = { matworld._41, matworld._42, 0.f };

	Render_Font(L"Gothic_Regular30", wstrItemName[0].c_str(),
		&_vec2(vPos.x + WINCX * 0.28f, -vPos.y + WINCY *0.48f),
		D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	Render_Font(L"Gothic_Bold20", wstrItemName[1].c_str(),
		&_vec2(vPos.x + WINCX * 0.28f, -vPos.y + WINCY *0.58f),
		D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	Render_Font(L"Gothic_Bold20", wstrItemName[2].c_str(),
		&_vec2(vPos.x + WINCX * 0.28f, -vPos.y + WINCY *0.65f),
		D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	Render_Font(L"Gothic_Bold20", L"ȿ�� �ο�",
		&_vec2(vPos.x + WINCX * 0.395f, vPos.y + WINCY *0.45f),
		D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
}

void CItemTexUI::Free()
{
	CUI::Free();
}

CItemTexUI * CItemTexUI::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _uint iTexNum)
{
	CItemTexUI* pInstance = new CItemTexUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}


void CItemTexUI::SetTexture(_int iTexNum)
{
	switch (iTexNum)
	{
	case 7:
	{
		//axe
		wstrItemName[0] = L"����";
		wstrItemName[1] = L"���� ���� 60";
		wstrItemName[2] = L"������ ȿ������ �����,\n�ȼ��� �������� ���� ������ ���˴ϴ�.";
	}
	break;
	case 8:
	{
		//crossbow
		wstrItemName[0] = L"�����";
		wstrItemName[1] = L"���Ÿ� ���� 20";
		wstrItemName[2] = L"�ܼ������� ������ ���� �ִ� �����Դϴ�.\n�������� ������ ȭ�� �浹ó����\n�Ǹ��� �ߴٰ� �������ϴ�.";
	}
	break;
	case 9:
	{
		//galive
		wstrItemName[0] = L"�۷��̺�";
		wstrItemName[1] = L"�ٰŸ� ���� 35";
		wstrItemName[2] = L"�ȼ������� �پ ������ �� �Ѹ����� �ÿ�ȸ \n������ ġ���ϴ� �ǹ̷� �ϻ�� �����Դϴ�.\n�� �۷��̺�� �ڵ��� ���� ���� �ֽ��ϴ�.";
	}
	break;
	case 10:
	{
		//sword
		wstrItemName[0] = L"��";
		wstrItemName[1] = L"�ٰŸ� ���� 25";
		wstrItemName[2] = L"ưư�ϰ� �ϰ� �� �� �ִ� ���Դϴ�.";
	}
	break;
	case 11:
	{
		//boots
		wstrItemName[0] = L"�ż��� ����";
		wstrItemName[1] = L"���ӽð� 10";
		wstrItemName[2] = L"ȿ���ο��� ���� �ż��� �������� �����ϰ�\n�ϴ� �����Դϴ�. ����ó�� ��� �� ��Ȯ����\n���� �����մϴ�. ";
	}
	break;
	case 13:
	{
		//firework
		wstrItemName[0] = L"���� ȭ��";
		wstrItemName[1] = L"���Ÿ� ���� 50";
		wstrItemName[2] = L"��ƼŬ �̻��� �־����ϴ�. �Ҹ� �ֳ���?";

	}
	break;
	case 14:
	{
		//shockpowder
		wstrItemName[0] = L"��� ����";
		wstrItemName[1] = L"���� ���ӽð� 2��";
		wstrItemName[2] = L"��� ����� ������ ���������� ���� �������\n���� �������� �����Դϴ�.";
	}
	break;
	case 15:
	{
		//Laser
		wstrItemName[0] = L"������ ��";
		wstrItemName[1] = L"������ ���� �ð� 2��";
		wstrItemName[2] = L"������� ȭ���� �������� �ٲ�ϴ�. ";
	}
	break;
	case 16:
	{
		//multishot
		wstrItemName[0] = L"��Ƽ��";
		wstrItemName[1] = L"ȭ�� 5���� ���ÿ� ������";
		wstrItemName[2] = L"���� ȭ��� ���� ����ϸ� ����� �Ͼ���?";
	}
	break;
	case 17:
	{
		//���
		wstrItemName[0] = L"���� ��";
		wstrItemName[1] = L"�˿� ���� �Ӽ� �ο�";
		wstrItemName[2] = L"�� ������ ����ũ�� Ƣ�鼭 ���͵��� ������ŵ�ϴ�.";
	}
	break;
	case 18:
	{
		//����̵�
		wstrItemName[0] = L"ȸ���� ��";
		wstrItemName[1] = L"�۷��̺꿡 �ٶ� �Ӽ� �ο�";
		wstrItemName[2] = L"������ ���� ������ ȭ�󵥹����� �Խ��ϴ�.";
	}
	break;
	case 19:
	{
		//���� ��
		wstrItemName[0] = L"���� ��";
		wstrItemName[1] = L"������ ���� ȿ�� �ο�";
		wstrItemName[2] = L"������ ���ݹ��� �ȿ� �ִ� ���͵��� ������ �ɸ��ϴ�.";
	}
	break;
	case 20:
	{
		//���ݷ� ����
		wstrItemName[0] = L"���� ��";
		wstrItemName[1] = L"���ݷ� ����";
		wstrItemName[2] = L"���ݷ��� �����մϴ�.";
	}
	break;
	default:
		MSG_BOX("input nonTextIndex");
		break;
	}
}
