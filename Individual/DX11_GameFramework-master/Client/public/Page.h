#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

BEGIN(Engine)
class CShader;
class CRenderer;
class CModel;
END

BEGIN(Client)

class CPage final : public CGameObject
{
public:
	typedef struct tagPageInfo
	{
		enum PAGEKIND { PAGE_END };

		_float3		fPos = _float3(0.f, 0.f, 0.f);
		PAGEKIND	ePageKind;
		
	}PAGEINFO;

private:
	CPage(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CPage(const CPage& rhs);
	virtual ~CPage() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_double TimeDelta) override;
	virtual void Late_Tick(_double TimeDelta) override;
	virtual HRESULT Render() override;

private:
	CRenderer*				m_pRendererCom = nullptr;
	CShader*				m_pShaderCom = nullptr;
	CModel*					m_pModelCom = nullptr;

private:
	HRESULT SetUp_Components();
	HRESULT SetUp_ShaderResources();

private:
	PAGEINFO	m_tinPageInfo;
	PAGEINFO	m_tPageInfo;

public:
	static	CPage* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;
};

END