#pragma once
#include "Obj.h"

class CItem : public CObj
{
public:
	typedef struct ItemInfo
	{
		unsigned int iID;

	}ITEMINFO;

public:
	CItem();
	virtual ~CItem();

public:
	virtual void OnCollision(CObj * pOther) override;

public:
	virtual HRESULT Initialize() override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render() override;
	virtual void Release(void) override;

public:
	static void		Make_Item(unsigned int iID, D3DXVECTOR3 vPos, float _fImageScale);

public:
	void		Set_ID(unsigned int iID) { m_ItemInfo.iID = iID; }
	ITEMINFO	Get_ItemInfo() { return m_ItemInfo; }

	void		Set_ImageScale(float _fScale) { m_fScale = _fScale;}

private:
	void		ChoiceStateKey();

private:
	ITEMINFO	m_ItemInfo;
	float		m_fScale;

};

