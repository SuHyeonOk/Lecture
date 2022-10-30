#pragma once
#include "Monster.h"
#include <functional>

class CController;
class CBossHPUI;

class CRedStoneMonstrosity : public CMonster
{
private:
	enum CRedStoneMonstrosityState
	{
		INTRO,
		WALK,
		CHOP,
		SPIT,
		SUMMON,
		WINDMILL,
		DEAD,
		STATE_END
	};


private:
	explicit CRedStoneMonstrosity(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRedStoneMonstrosity(const CMonster& rhs);
	virtual ~CRedStoneMonstrosity() override;

public:
	virtual HRESULT Ready_Object() override;
	virtual void AnimationEvent(const string& strEvent) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void LateUpdate_Object() override;
	virtual void Free() override;
	static CRedStoneMonstrosity* Create(LPDIRECT3DDEVICE9 pGraphicDev, const wstring& wstrPath);

	virtual void StateChange();

	// controller ���� �Լ�
	_vec3 Get_TargetPos() { return m_vTargetPos; }
	void WalkToTarget(const _vec3& vTargetPos) { m_vTargetPos = vTargetPos; }
	void Chop(const _vec3& vTargetPos)
	{
		m_bChop = true;
		m_vTargetPos = vTargetPos;
	}
	void Spit(const _vec3& vTargetPos)
	{
		m_bSpit = true;
		m_vTargetPos = vTargetPos;
	}
	void Summon(const _vec3& vTargetPos)
	{
		m_bSummon = true;
		m_vTargetPos = vTargetPos;
	}
	void Windmill(const _vec3& vTargetPos)
	{
		m_bWindmill = true;
		m_vTargetPos = vTargetPos;
	}



private:
	CRedStoneMonstrosityState m_eState = STATE_END;
	array<CubeAnimFrame, STATE_END> m_arrAnim;

	void	SetOff() 
	{
		m_bChop = false;
		m_bSpit = false;
		m_bSummon = false;
		m_bWindmill = false;
	}
	// true : PlayAnimationOnce ��� ���� ����(���� �ִϸ��̼� ���� ����), false: �ٸ� �ִϸ��̼� ������
	_bool m_bCanPlayAnim = true; // ���� �������� �ִϸ��̼� ���� �ִϸ��̼� ���� ���� ����

	_vec3 m_vTargetPos = CGameUtilMgr::s_vZero; // controller �Է�

	_bool m_bChop = false; // controller �Է�
	_bool m_bSpit = false; // controller �Է�
	_bool m_bSummon = false; // controller �Է�
	_bool m_bWindmill = false; // controller �Է�
	

	_bool m_bChopFire = false; // anim event �Է�
	_bool m_bWindmillFire = false; // anim event �Է�
	_matrix m_matSommonWorld[6];

	ULONGLONG m_dwWindTime = 0;

	_bool m_bIntroPlay = false;

	CBossHPUI* m_pBossHPUI = nullptr;
};
