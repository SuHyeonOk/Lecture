#pragma once
#include "SkeletalCube.h"

enum class PlayerArrowType
{
	NORMAL,
	MULTISHOT,
	LASER
};

enum PlayerInputMask
{
	PLAYER_W = 1,
	PLAYER_A = 1 << 1,
	PLAYER_S = 1 << 2,
	PLAYER_D = 1 << 3,

	PLAYER_ML = 1 << 4,
	PLAYER_MR = 1 << 5,
	PLAYER_1 = 1 << 6,
	PLAYER_2 = 1 << 7,
	PLAYER_3 = 1 << 8,
	PLAYER_ROLL = 1 << 9,
	PLAYER_POTION = 1 << 10,
};

class CController;
class CStatComponent;
class CInventory;

class CPlayer : public CSkeletalCube
{
	friend class CCamAnimation;
protected:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayer() override;

private:
	enum PlayerState
	{
		IDLE,
		WALK,
		ATTACK,
		STUN,
		ROLL,
		LEGACY,
		FASCINATE,
		DEAD,
		STATE_END
	};

	enum Animation
	{
		ANIM_WALK,
		ANIM_IDLE,
		ANIM_DEAD,
		ANIM_ATTACK1,
		ANIM_ATTACK2,
		ANIM_ATTACK3,
		ANIM_RANGE_ATTACK,
		ANIM_LEGACY1,
		ANIM_LEGACY2,
		ANIM_LEGACY3,
		ANIM_ROLL,
		ANIM_TELEPORT,
		ANIM_RESCUE,
		ANIM_END
	};

	template<_int VX, _int VZ>
	using iBlockIndex = array<array<_int, VZ>, VX>;

public:
	virtual HRESULT Ready_Object(const wstring& wstrPath);
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void LateUpdate_Object() override;
	virtual void Render_Object() override;
	virtual void Free() override;
	virtual void AnimationEvent(const string& strEvent) override;

	virtual void AttackState();
	void StateChange();
	_vec3 GetInfo(INFOID eID) { return m_pRootPart->pTrans->m_vInfo[eID]; }
	void SetVisible(bool bVisible){ m_bVisible = bVisible; }
	_bool IsVisible() const { return m_bVisible; }
	void PlayerSpawn();

	void SpawnArrow(_uint iDamage, PlayerArrowType eType, _bool bCritical = false, ArrowType eArrowType = ARROW_NORMAL);
	_bool PickTargetEnemy(OUT _vec3& vLookAt);

	// controller �Է��Լ�
	void SetMoveDir(_float fX, _float fZ);
	void RangeAttackPress(bool bOn) { m_bRangeAttack = bOn; }
	void MeleeAttackPress(bool bOn) { m_bMeleeAttack = bOn; }
	void RollPress() { m_bRoll = true; }
	void Legacy1Press() { m_bLegacy1 = true; }
	void Legacy2Press() { m_bLegacy2 = true; }
	void Legacy3Press() { m_bLegacy3 = true; }
	void Legacy4Press();
	void SetArrowLookAt(const _vec3& vLookAt) {m_vArrowLookAt = vLookAt;}

	// ��Ȥ ���� �Լ�
	void WalkToTarget(const _vec3& vTargetPos) { m_vTargetPos = vTargetPos; }
	void RotationToSaton(void);
	// ~��Ȥ ���� �Լ�


	void UsePotion();

	void RotateTo(_float fYaw);
	//

	// UI�� �Լ�
	_float GetRollCoolTime() const { return m_CurRollCoolTime / s_RollCoolTime; }
	_float GetPotionCoolTime() const { return m_CurPotionCoolTime / s_PotionCollTime; }
	CInventory* GetInventory() const { return m_pInventory; }
	//

	//������ ����(�ӽ�)
	void WeaponChange(ITEMTYPE eIT);
	void SetSpeed(_float fSpeed) { m_fSpeed = fSpeed; }
	static CPlayer* Create(LPDIRECT3DDEVICE9 pGraphicDev, const wstring& wstrPath, _bool bRemote = false);

	void SetName(const string& strName) {m_strName = strName;}

	_float GetYawToCursor();
	string GetName() { return m_strName;}

	static _bool s_bDropDead;
private:
	void RotateToCursor();
	void RotateToMove();

	CInventory* m_pInventory = nullptr;

protected:
	string m_strName = "NoNamed";

	SkeletalPart* m_pWeaponPart = nullptr;
	CStatComponent* m_pStat = nullptr;
	CCollisionCom* m_pColl = nullptr;

	PlayerState m_eState = STATE_END;
	array<CubeAnimFrame, ANIM_END> m_arrAnim;

	const static _float s_RollCoolTime;
	_float m_CurRollCoolTime;
	const static _float s_PotionCollTime;
	_float m_CurPotionCoolTime;
	_float m_fSpeed; // �ӵ�
	_float m_fRollSpeed; // ������ �ӵ�

	_int  m_iAttackCnt = 0;

	_vec3 m_vMoveDirNormal{0.f, 0.f, 0.f}; // �̵� ����

	// true : PlayAnimationOnce ��� ���� ����(���� �ִϸ��̼� ���� ����), false: �ٸ� �ִϸ��̼� ������
	_bool m_bCanPlayAnim = true; // ���� �������� �ִϸ��̼� ���� �ִϸ��̼� ���� ���� ����

	_bool m_bRoll = false; // controller �Է�
	_bool m_bMeleeAttack = false; // controller �Է�
	_bool m_bRangeAttack = false; // controller �Է�
	_bool m_bMove = false; // controller �Է�

	_bool m_bLegacy1 = false;
	_bool m_bLegacy2 = false;
	_bool m_bLegacy3 = false;

	_bool m_bApplyMeleeAttack = false;
	_bool m_bApplyMeleeAttackNext = false;

	DWORD m_dwWalkDust;
	DWORD m_dwRollDust;

	// ���Ÿ����� �ٰŸ� ����� �ٽ� ���ƿ� �� 1�����ӵ��� �ٰŸ� ���� ��ġ�� �̻��� ������ ���� ����.
	_bool m_bDelay = false;
	iBlockIndex<VTXCNTX, VTXCNTZ> arrBlock{};

	_vec3 m_vTargetPos;

	string m_strStatus;

	_bool m_bVisible = false;

	_bool m_bLaser = false;
	_float m_fLaserTime = 2.f;
	_float m_fCurLaserTime = 0.f;




	_vec3 m_vArrowLookAt; // for remote player
};


