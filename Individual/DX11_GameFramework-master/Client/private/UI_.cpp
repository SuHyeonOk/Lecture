#include "stdafx.h"
#include "..\public\UI_.h"
#include "GameInstance.h"

#include "Obj_Manager.h"
#include "UI_Manager.h"
#include "UI_SkillIcon.h"
#include "Skill_Manager.h"

#include "UI_ShopIndex.h"

CUI_::CUI_(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
	: CGameObject(pDevice, pContext)
{
}

CUI_::CUI_(const CUI_ & rhs)
	: CGameObject(rhs)
{
}

HRESULT CUI_::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;
	
	return S_OK;
}

HRESULT CUI_::Initialize(void * pArg)
{
	CGameObject::GAMEOBJECTDESC		GameObjectDesc;
	ZeroMemory(&GameObjectDesc, sizeof(GameObjectDesc));

	GameObjectDesc.TransformDesc.fSpeedPerSec = 0.0f;
	GameObjectDesc.TransformDesc.fRotationPerSec = XMConvertToRadians(90.0f);

	if (FAILED(CGameObject::Initialize(&GameObjectDesc)))
		return E_FAIL;

	CUI_*		pUI = nullptr;

	CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	// [0] : Npc 와의 대화창
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_Talk")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);

	// [1] : Monster 공격시 UI
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_Monster")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);

	// [2] : Monster 공격시 UI
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_Monster_HealthBar_Bar")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);

	// [3] : Monster 공격시 UI
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_Monster_HealthBar_BarBack")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);

	// [4] : Player Indormacion
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_Player_Informacion")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);

	// [5] : Player HpBar
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_Player_HPBar")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);

	// [6] : Player HpBarBack
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_Player_HPBarBack")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);

	// [7] : Player LevelBar
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_Player_Level_HPBar")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);

	// [8] : Player LevelBarBack
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_Player_Level_HPBarBack")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);

	// [9] : Player LevelNumber
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_Player_Level_Number")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);


	// [10] : Weapons
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_Player_Weapons")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);

	// [11] : Weapon
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_Player_Weapon")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);

	// [12] : Skill_Scroll
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_Player_Skill_Scroll")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);

	// [13] : Skill_Icon_One
	ITEMINDEX eItemIndex = ITEM_ONE;
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_Player_Skill_Icon"), &eItemIndex));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);
	// [14] : Skill_Icon_Two
	eItemIndex = ITEM_TWO;
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_Player_Skill_Icon"), &eItemIndex));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);
	// [15] : Skill_Icon_Three
	eItemIndex = ITEM_THREE;
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_Player_Skill_Icon"), &eItemIndex));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);
	// [16] : Skill_Icon_Four
	eItemIndex = ITEM_FOUR;
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_Player_Skill_Icon"), &eItemIndex));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);

	// [17] : Skill_Scroll_Count_One
	ITEMINDEX eItemCount = ITEM_ONE;
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_Player_Skill_Scroll_Count"), &eItemCount));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);
	// [18] : Skill_Scroll_Count_Two
	eItemCount = ITEM_TWO;
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_Player_Skill_Scroll_Count"), &eItemCount));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);
	// [19] : Skill_Scroll_Count_Three
	eItemCount = ITEM_THREE;
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_Player_Skill_Scroll_Count"), &eItemCount));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);
	// [20] : Skill_Scroll_Count_Four
	eItemCount = ITEM_FOUR;
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_Player_Skill_Scroll_Count"), &eItemCount));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);

	// [21] : MninMap
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_MninMap")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);
	// [22] : MninMap
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_Snail")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);

	// [23] : Boss 공격시 UI
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_Boss")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);

	// [24] : Boss 공격시 UI
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_Boss_HealthBar_Bar")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);

	// [25] : Boss 공격시 UI
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_Boss_HealthBar_BarBack")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);

	// [26] : Inventory_X
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_Inventory_X")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);

	// [27] : Inventory
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_Inventory")));

	if (nullptr == pUI)
		return E_FAIL;

	m_vecUI.push_back(pUI);
	
	// [28] : Icon_One
	INVENTORYICON eInventoryIcon;
	eInventoryIcon = INVENTORYICON::ICON_ONE;
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_Icon"), &eInventoryIcon));
	if (nullptr == pUI)
		return E_FAIL;
	m_vecUI.push_back(pUI);

	// [29] : Icon_Two
	eInventoryIcon = INVENTORYICON::ICON_TWO;
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_Icon"), &eInventoryIcon));
	if (nullptr == pUI)
		return E_FAIL;
	m_vecUI.push_back(pUI);

	// [30] : Icon_Three
	eInventoryIcon = INVENTORYICON::ICON_THREE;
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_Icon"), &eInventoryIcon));
	if (nullptr == pUI)
		return E_FAIL;
	m_vecUI.push_back(pUI);

	// [31] : Icon_Four
	eInventoryIcon = INVENTORYICON::ICON_FOUR;
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_Icon"), &eInventoryIcon));
	if (nullptr == pUI)
		return E_FAIL;
	m_vecUI.push_back(pUI);

	// [32] : Icon_Five
	eInventoryIcon = INVENTORYICON::ICON_FIVE;
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_Icon"), &eInventoryIcon));
	if (nullptr == pUI)
		return E_FAIL;
	m_vecUI.push_back(pUI);

	// [33] : Icon_Six
	eInventoryIcon = INVENTORYICON::ICON_SIX;
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_Icon"), &eInventoryIcon));
	if (nullptr == pUI)
		return E_FAIL;
	m_vecUI.push_back(pUI);

	// [34] : CurrentIcon
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_CurrentIcon")));
	if (nullptr == pUI)
		return E_FAIL;
	m_vecUI.push_back(pUI);

	// [35] : ShopBase
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_ShopBase")));
	if (nullptr == pUI)
		return E_FAIL;
	m_vecUI.push_back(pUI);
	// [36] : ShopIndex
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_ShopIndex")));
	if (nullptr == pUI)
		return E_FAIL;
	m_vecUI.push_back(pUI);
	// [37] : ShopSword
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_ShopSword")));
	if (nullptr == pUI)
		return E_FAIL;
	m_vecUI.push_back(pUI);

	// [38] : CutScene
	pUI = dynamic_cast<CUI_*>(pGameInstance->Clone_GameObject(TEXT("Prototype_GameObject_UI_CutScene")));
	if (nullptr == pUI)
		return E_FAIL;
	m_vecUI.push_back(pUI);
	
	RELEASE_INSTANCE(CGameInstance);


	return S_OK;
}

void CUI_::Tick(_double TimeDelta)
{
	if (LEVEL_LOADING == CObj_Manager::GetInstance()->Get_Current_Level())
		return;

	if (CObj_Manager::PLAYERINFO::PLAYER::CUTSCENE_ONE == CObj_Manager::GetInstance()->Get_Current_Player().ePlayer ||
		CObj_Manager::PLAYERINFO::PLAYER::CUTSCENE_TWO == CObj_Manager::GetInstance()->Get_Current_Player().ePlayer)
	{
		m_vecUI[38]->Tick(TimeDelta);
		return;
	}

	if(CUI_Manager::GetInstance()->Get_Talk())
		m_vecUI[0]->Tick(TimeDelta);

	if (CUI_Manager::GetInstance()->Get_UI_Monster())
	{
		m_vecUI[1]->Tick(TimeDelta);
 		m_vecUI[3]->Tick(TimeDelta);
		m_vecUI[2]->Tick(TimeDelta);
	}

	// 플레이어 Hp, Level 등등..
	m_vecUI[4]->Tick(TimeDelta);
	m_vecUI[6]->Tick(TimeDelta);
	m_vecUI[5]->Tick(TimeDelta);
	m_vecUI[8]->Tick(TimeDelta);
	m_vecUI[7]->Tick(TimeDelta);
	m_vecUI[9]->Tick(TimeDelta);
	
	if (CObj_Manager::PLAYERINFO::PLAYER::FINNANDJAKE == CObj_Manager::GetInstance()->Get_Current_Player().ePlayer)
	{
		// 미니게임
		m_vecUI[22]->Tick(TimeDelta);
		return;
	}

	// 무기
	m_vecUI[10]->Tick(TimeDelta);
	m_vecUI[11]->Tick(TimeDelta);

	// 스킬
	m_vecUI[12]->Tick(TimeDelta);
	if (true == CUI_Manager::GetInstance()->Get_IsIcon_Index(ITEM_ONE))
	{
		m_vecUI[13]->Tick(TimeDelta);		// 스킬 창에 아이템이 들어오게 되면 아이콘을 출력한다.

		CSkill_Manager::PLAYERSKILL tPlayerSkill;
		tPlayerSkill.eSkill = CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_ONE);
		_int iCount = CSkill_Manager::GetInstance()->Get_PageCount(tPlayerSkill.eSkill);
		if(1 < iCount)
			m_vecUI[17]->Tick(TimeDelta);	// 스킬 창에 아이템이 1개 이상이라면 숫자를 표시한다.
	}
	if (true == CUI_Manager::GetInstance()->Get_IsIcon_Index(ITEM_TWO))
	{
		m_vecUI[14]->Tick(TimeDelta);

		CSkill_Manager::PLAYERSKILL tPlayerSkill;
		tPlayerSkill.eSkill = CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_TWO);
		_int iCount = CSkill_Manager::GetInstance()->Get_PageCount(tPlayerSkill.eSkill);
		if (1 < iCount)
			m_vecUI[18]->Tick(TimeDelta);
	}
	if (true == CUI_Manager::GetInstance()->Get_IsIcon_Index(ITEM_THREE))
	{
		m_vecUI[15]->Tick(TimeDelta);

		CSkill_Manager::PLAYERSKILL tPlayerSkill;
		tPlayerSkill.eSkill = CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_THREE);
		_int iCount = CSkill_Manager::GetInstance()->Get_PageCount(tPlayerSkill.eSkill);
		if (1 < iCount)
			m_vecUI[19]->Tick(TimeDelta);
	}
	if (true == CUI_Manager::GetInstance()->Get_IsIcon_Index(ITEM_FOUR))
	{
		m_vecUI[16]->Tick(TimeDelta);

		CSkill_Manager::PLAYERSKILL tPlayerSkill;
		tPlayerSkill.eSkill = CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_FOUR);
		_int iCount = CSkill_Manager::GetInstance()->Get_PageCount(tPlayerSkill.eSkill);
		if (1 < iCount)
			m_vecUI[20]->Tick(TimeDelta);
	}

	// 미니맵
	m_vecUI[21]->Tick(TimeDelta);

	if (LEVEL_SKELETON_BOSS == CObj_Manager::GetInstance()->Get_Current_Level())	// Boss 전에서만 유아이를 띄운다.
	{
		if (false == CUI_Manager::GetInstance()->Get_UI_Monster())
		{
			// Boss UI
			m_vecUI[23]->Tick(TimeDelta);
			m_vecUI[25]->Tick(TimeDelta);
			m_vecUI[24]->Tick(TimeDelta);
		}
	}

	// Inventory
	m_vecUI[26]->Tick(TimeDelta);
	if (true == CObj_Manager::GetInstance()->Get_Inventory())
	{
		m_vecUI[27]->Tick(TimeDelta);

		m_vecUI[34]->Tick(TimeDelta);	// CurrentIcon

		m_vecUI[28]->Tick(TimeDelta);	// Jake Son 계속 출력한다.

		//// 1 번째 인벤토리 칸에 어떤 스킬이 있는지 그 스킬의 개수가 1개 이상일 때 출력한다.
		//CSkill_Manager::PLAYERSKILL::SKILL ePlayerSkill = CUI_Manager::GetInstance()->Get_InventoryIcon(INVENTORYICON::ICON_TWO);
		//_int iCount = CSkill_Manager::GetInstance()->Get_PageCount(ePlayerSkill);
		//if (1 < iCount)
		if (true == CUI_Manager::GetInstance()->Get_IsInventoryIcon_Index(INVENTORYICON::ICON_TWO))
			m_vecUI[29]->Tick(TimeDelta);

		if (true == CUI_Manager::GetInstance()->Get_IsInventoryIcon_Index(INVENTORYICON::ICON_THREE))
			m_vecUI[30]->Tick(TimeDelta);

		if (true == CUI_Manager::GetInstance()->Get_IsInventoryIcon_Index(INVENTORYICON::ICON_FOUR))
			m_vecUI[31]->Tick(TimeDelta);

		if (true == CUI_Manager::GetInstance()->Get_IsInventoryIcon_Index(INVENTORYICON::ICON_FIVE))
			m_vecUI[32]->Tick(TimeDelta);

		if (true == CUI_Manager::GetInstance()->Get_IsInventoryIcon_Index(INVENTORYICON::ICON_SIX))
			m_vecUI[33]->Tick(TimeDelta);
	}

	if (true == CUI_Manager::GetInstance()->Get_Shop())
	{
		// Shop
		m_vecUI[35]->Tick(TimeDelta);

		if (3 <= CObj_Manager::GetInstance()->Get_Current_Player().iKey)
			m_vecUI[37]->Tick(TimeDelta);
		
		m_vecUI[36]->Tick(TimeDelta);
	}
	else
	{
		//CUI_ShopIndex* pUI_ShopIdex = dynamic_cast<CUI_ShopIndex*>(m_vecUI[36]);
		//pUI_ShopIdex->Reset();

		((CUI_ShopIndex*)m_vecUI[36])->Reset();
	}

	//CGameInstance*		pGameInstance = GET_INSTANCE(CGameInstance);

	//if (pGameInstance->Key_Down(DIK_P))
	//{
	//	cout << "전체적인 상태 } " << 0 << "> " << _int(CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_ONE)) << " || " <<
	//	1 << "> " << _int(CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_TWO)) << " || " <<
	//	2 << "> " << _int(CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_THREE)) << " || " <<
	//	3 << "> " << _int(CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_FOUR)) << endl;

	//	cout << "전체적인 상태 형변환 안 한 것 } " << 0 << " : " << CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_ONE) << " || " <<
	//		1 << "> " << CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_TWO) << " || " <<
	//		2 << "> " << CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_THREE) << " || " <<
	//		3 << "> " << CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_FOUR) << endl;

	//	if (true == CUI_Manager::GetInstance()->Get_IsIcon_Index(ITEM_ONE))
	//		cout << 1 << "] : " << _int(CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_ONE)) << endl;
	//	if (true == CUI_Manager::GetInstance()->Get_IsIcon_Index(ITEM_TWO))
	//		cout << 2 << "] : " << _int(CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_TWO)) << endl;
	//	if (true == CUI_Manager::GetInstance()->Get_IsIcon_Index(ITEM_THREE))
	//		cout << 3 << "] : " << _int(CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_THREE)) << endl;
	//	if (true == CUI_Manager::GetInstance()->Get_IsIcon_Index(ITEM_FOUR))
	//		cout << 4 << "] : " << _int(CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_FOUR)) << endl;
	//}

	//RELEASE_INSTANCE(CGameInstance);

	__super::Tick(TimeDelta);
}

void CUI_::Late_Tick(_double TimeDelta)
{
	if (LEVEL_LOADING == CObj_Manager::GetInstance()->Get_Current_Level())
		return;

	if (CObj_Manager::PLAYERINFO::PLAYER::CUTSCENE_ONE == CObj_Manager::GetInstance()->Get_Current_Player().ePlayer ||
		CObj_Manager::PLAYERINFO::PLAYER::CUTSCENE_TWO == CObj_Manager::GetInstance()->Get_Current_Player().ePlayer)
	{
		m_vecUI[38]->Late_Tick(TimeDelta);
		return;
	}

	if (CUI_Manager::GetInstance()->Get_Talk())
		m_vecUI[0]->Late_Tick(TimeDelta);

	if (CUI_Manager::GetInstance()->Get_UI_Monster())
	{
		m_vecUI[1]->Late_Tick(TimeDelta);
		m_vecUI[3]->Late_Tick(TimeDelta);
		m_vecUI[2]->Late_Tick(TimeDelta);
	}

	m_vecUI[4]->Late_Tick(TimeDelta);
	m_vecUI[6]->Late_Tick(TimeDelta);
	m_vecUI[5]->Late_Tick(TimeDelta);
	m_vecUI[8]->Late_Tick(TimeDelta);
	m_vecUI[7]->Late_Tick(TimeDelta);
	m_vecUI[9]->Late_Tick(TimeDelta);

	if (CObj_Manager::PLAYERINFO::PLAYER::FINNANDJAKE == CObj_Manager::GetInstance()->Get_Current_Player().ePlayer)
	{
		m_vecUI[22]->Late_Tick(TimeDelta);
		return;
	}

	m_vecUI[10]->Late_Tick(TimeDelta);
	m_vecUI[11]->Late_Tick(TimeDelta);

	m_vecUI[12]->Late_Tick(TimeDelta);
	if (true == CUI_Manager::GetInstance()->Get_IsIcon_Index(ITEM_ONE))
	{
		m_vecUI[13]->Late_Tick(TimeDelta);

		CSkill_Manager::PLAYERSKILL tPlayerSkill;
		tPlayerSkill.eSkill = CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_ONE);
		_int iCount = CSkill_Manager::GetInstance()->Get_PageCount(tPlayerSkill.eSkill);
		if (1 < iCount)
			m_vecUI[17]->Late_Tick(TimeDelta);
	}
	if (true == CUI_Manager::GetInstance()->Get_IsIcon_Index(ITEM_TWO))
	{
		m_vecUI[14]->Late_Tick(TimeDelta);

		CSkill_Manager::PLAYERSKILL tPlayerSkill;
		tPlayerSkill.eSkill = CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_TWO);
		_int iCount = CSkill_Manager::GetInstance()->Get_PageCount(tPlayerSkill.eSkill);
		if (1 < iCount)
			m_vecUI[18]->Late_Tick(TimeDelta);
	}
	if (true == CUI_Manager::GetInstance()->Get_IsIcon_Index(ITEM_THREE))
	{
		m_vecUI[15]->Late_Tick(TimeDelta);

		CSkill_Manager::PLAYERSKILL tPlayerSkill;
		tPlayerSkill.eSkill = CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_THREE);
		_int iCount = CSkill_Manager::GetInstance()->Get_PageCount(tPlayerSkill.eSkill);
		if (1 < iCount)
			m_vecUI[19]->Late_Tick(TimeDelta);
	}
	if (true == CUI_Manager::GetInstance()->Get_IsIcon_Index(ITEM_FOUR))
	{
		m_vecUI[16]->Late_Tick(TimeDelta);

		CSkill_Manager::PLAYERSKILL tPlayerSkill;
		tPlayerSkill.eSkill = CUI_Manager::GetInstance()->Get_SkillIcon(ITEM_FOUR);
		_int iCount = CSkill_Manager::GetInstance()->Get_PageCount(tPlayerSkill.eSkill);
		if (1 < iCount)
			m_vecUI[20]->Late_Tick(TimeDelta);
	}

	m_vecUI[21]->Late_Tick(TimeDelta);

	if (LEVEL_SKELETON_BOSS == CObj_Manager::GetInstance()->Get_Current_Level())
	{
		if (false == CUI_Manager::GetInstance()->Get_UI_Monster())
		{
			m_vecUI[23]->Late_Tick(TimeDelta);
			m_vecUI[25]->Late_Tick(TimeDelta);
			m_vecUI[24]->Late_Tick(TimeDelta);
		}
	}

	m_vecUI[26]->Late_Tick(TimeDelta);
	if (true == CObj_Manager::GetInstance()->Get_Inventory())
	{
		m_vecUI[27]->Late_Tick(TimeDelta);

		m_vecUI[34]->Late_Tick(TimeDelta);

		m_vecUI[28]->Late_Tick(TimeDelta);

		if (true == CUI_Manager::GetInstance()->Get_IsInventoryIcon_Index(INVENTORYICON::ICON_TWO))
			m_vecUI[29]->Late_Tick(TimeDelta);

		if (true == CUI_Manager::GetInstance()->Get_IsInventoryIcon_Index(INVENTORYICON::ICON_THREE))
			m_vecUI[30]->Late_Tick(TimeDelta);

		if (true == CUI_Manager::GetInstance()->Get_IsInventoryIcon_Index(INVENTORYICON::ICON_FOUR))
			m_vecUI[31]->Late_Tick(TimeDelta);

		if (true == CUI_Manager::GetInstance()->Get_IsInventoryIcon_Index(INVENTORYICON::ICON_FIVE))
			m_vecUI[32]->Late_Tick(TimeDelta);

		if (true == CUI_Manager::GetInstance()->Get_IsInventoryIcon_Index(INVENTORYICON::ICON_SIX))
			m_vecUI[33]->Late_Tick(TimeDelta);
	}

	if (true == CUI_Manager::GetInstance()->Get_Shop())
	{
		m_vecUI[35]->Late_Tick(TimeDelta);

		if (3 <= CObj_Manager::GetInstance()->Get_Current_Player().iKey)
			m_vecUI[37]->Late_Tick(TimeDelta);

		m_vecUI[36]->Late_Tick(TimeDelta);
	}



	__super::Late_Tick(TimeDelta);

	//if(nullptr != m_pRendererCom)
	//	m_pRendererCom->Add_RenderGroup(CRenderer::RENDER_UI, this);
}

HRESULT CUI_::Render()
{
	if (LEVEL_LOADING == CObj_Manager::GetInstance()->Get_Current_Level())
		return E_FAIL;

	if (FAILED(__super::Render()))
		return E_FAIL;

	return S_OK;
}

CUI_ * CUI_::Create(ID3D11Device * pDevice, ID3D11DeviceContext * pContext)
{
 	CUI_*		pInstance = new CUI_(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : CUI_");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CUI_::Clone(void * pArg)
{
	CUI_*		pInstance = new CUI_(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CUI_");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CUI_::Free()
{
	__super::Free();

	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pShaderCom);
	Safe_Release(m_pRendererCom);
}
