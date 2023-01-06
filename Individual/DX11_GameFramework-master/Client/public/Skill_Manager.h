#pragma once

#include "Client_Defines.h"
#include "Base.h"
#include "GameObject.h"

BEGIN(Client)

class CSkill_Manager : public CBase
{
	DECLARE_SINGLETON(CSkill_Manager)

	// 0 : 3방향 총알
	// 1 : 마르셀린
	// 2 : 돈
	// 3 : 피오나
	// 4 : 무지개콘
	// 5 : 핀 제이크 합체
	// 5 : 칼

public:
	typedef struct tagPlyaerSkill
	{
		enum SKILL { PAINT, MARCELINT, SKILL_END };
		SKILL		eSkill = SKILL_END;			// 현재 사용 중 인 스킬

	}PLAYERSKILL;

	typedef struct tagPlayerMagicSkill
	{
		enum SKILLSTATE { IDLE, RUN, ATTACK, HIT, SKILLSTATE_END };
		SKILLSTATE		eSkill = SKILLSTATE_END;

	}MAGICSKILL;

public:
	CSkill_Manager();
	virtual ~CSkill_Manager() = default;

public:		// 플레이어
	PLAYERSKILL					Get_Player_Skill() { return m_tPlayerSkill; }
	void						Set_Player_Skill(PLAYERSKILL::SKILL eSkillState) { m_tPlayerSkill.eSkill = eSkillState; }

	MAGICSKILL					Get_Magic_Skill() { return m_tMagicSkill; }
	void						Set_Magic_Skill(MAGICSKILL::SKILLSTATE eSkillState) { m_tMagicSkill.eSkill = eSkillState; }

public:
	void		CSkill_Manager::Page_Use(ITEMINDEX	iIndex);
	void		CSkill_Manager::Page_PickUp(CGameObject * pOther);										// 현재 먹은 (충돌한) Page 의 종류 관리

public:		// 유아이 관련
	_int		Get_PageCount(PLAYERSKILL::SKILL iIndex) { return m_arrPageCount[iIndex]; }				

	void		CSkill_Manager::SkillIcon(PLAYERSKILL::SKILL eSkill);										// IconIndex가 비어있는지 확인하고, 인덱스에 값을 채운다.

private:
	PLAYERSKILL		m_tPlayerSkill;
	MAGICSKILL		m_tMagicSkill;

	_int			m_arrPageCount[ITEMINDEX_END] = { 0 };

public:
	virtual void Free() override;	
};

END