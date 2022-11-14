#pragma once

/* �̱���.  */
/* Ŭ���̾�Ʈ�� ������ ������ ���� ������� Ŭ����. */

#include "Base.h"
#include "Input_Device.h"

BEGIN(Engine)

class ENGINE_DLL CGameInstance final : public CBase
{
	DECLARE_SINGLETON(CGameInstance);
private:
	CGameInstance();
	virtual ~CGameInstance() = default;

public: /* For.GameInstance */
	HRESULT Initialize_Engine(HINSTANCE hInst, _uint iNumLevels, const GRAPHIC_DESC& GraphicDesc, ID3D11Device** ppDeviceOut, ID3D11DeviceContext** ppContextOut);
	void Tick_Engine(_double TimeDelta);

public: /* For.Graphic_Device */
	ID3D11Device*			Get_Device();
	ID3D11DeviceContext*	Get_Context();
	HRESULT Clear_Graphic_Device(const _float4* pColor);
	HRESULT Present();

public: /* For.Input_Device */
	_byte		Get_DIKeyState(_ubyte byKeyID);
	_byte		Get_DIMouseState(CInput_Device::MOUSEKEYSTATE byMouseID);
	_long		Get_DIMouseMove(CInput_Device::MOUSEMOVESTATE eMoveState);

public: /* For.Level_Manager */
	HRESULT Open_Level(class CLevel* pNewLevel);	
	HRESULT Render_Level();
	

private:
	class CGraphic_Device*			m_pGraphic_Device = nullptr;
	class CInput_Device*			m_pInput_Device = nullptr;
	class CLevel_Manager*			m_pLevel_Manager = nullptr;

public:
	static void Release_Engine();

public:
	virtual void Free() override;
};

END