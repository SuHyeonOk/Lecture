#pragma once
#include "Component.h"
#include "Texture.h"
#include "GameObject.h"

#include "Engine_Include.h"

BEGIN(Engine)

class ENGINE_DLL CAnimator : public CComponent
{
private:
	explicit CAnimator(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CAnimator(const CAnimator& rhs);
	virtual ~CAnimator();

	// �ִϸ��̼� �����, ���� ��Ű��, �ٲٱ�

public:
	HRESULT		Ready_Animator();

	HRESULT		Add_Component(const _tchar * pTectureTag);

	void		Play_Animation(const _float& fTimeDelta);
	void		Change_Animation(const _tchar * pTectureTag);
	void		Set_Texture();

	const _float&	Get_Currentframe() { return m_fFrame; }
	 
private: // Key : Tag, Velaue : TextComponent
	map<const _tchar*, CTexture*>		m_mapAnimation;

public:
	static	CAnimator*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*		Clone(void);
	virtual void			Free(void);

private:
	CTexture*				m_pCurAnim = nullptr;

private:
	_float					m_fFrame;
};

END