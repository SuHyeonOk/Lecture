#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CTexture;
class CRenderer;
class CVIBuffer_Rect;
END

BEGIN(Client)

class CE_FlyingEnvironment final : public CGameObject
{
public:
	typedef struct tegEffextInfo
	{
		enum TYPE { BUTTERFLIES_RED, BUTTERFLIES_BLUE, BUTTERFLIES_YELLOW, TYPE_END	};
		TYPE		eType = TYPE_END;

		_float3		f3Pos = { 0.0f, 0.0f, 0.0f };

	}EFFECTINFO;

private:
	CE_FlyingEnvironment(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CE_FlyingEnvironment(const CE_FlyingEnvironment& rhs);
	virtual ~CE_FlyingEnvironment() = default;

public:
	virtual HRESULT		Initialize_Prototype() override;
	virtual HRESULT		Initialize(void* pArg) override;
	virtual void		Tick(_double TimeDelta) override;
	virtual void		Late_Tick(_double TimeDelta) override;
	virtual HRESULT		Render() override;

private:
	HRESULT					SetUp_Components();
	HRESULT					SetUp_ShaderResources();

private:
	CShader*				m_pShaderCom = nullptr;
	CRenderer*				m_pRendererCom = nullptr;
	CTexture*				m_pTextureCom = nullptr;
	CVIBuffer_Rect*			m_pVIBufferCom = nullptr;

private:
	void					Ready_Butterflies();

private:
	EFFECTINFO				m_tEffectInfo = {};

private:
	_int					m_iTexture_Index = 0;
	_int					m_iTextureDead_Count = 0;
	_double					m_dChange_TimeAcc = 0.0;
	_float					m_fAlpha = 1.0f;

	_bool					m_bFindPlayer = false;
	_float4					m_f4RandomLook = { 0.0f, 0.0f, 1.0f, 0.0f };

public:
	static	CE_FlyingEnvironment*		Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject*		Clone(void* pArg = nullptr) override;
	virtual void				Free() override;
};

END