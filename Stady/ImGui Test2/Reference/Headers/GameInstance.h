#pragma once

/* �̱���.  */
/* Ŭ���̾�Ʈ�� ������ ������ ���� ������� Ŭ����. */

#include "Base.h"

#include "Component_Manager.h"

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
	void Clear_Level(_uint iLevelIndex);

public: /* For.Graphic_Device */
	ID3D11Device*			Get_Device();
	ID3D11DeviceContext*	Get_Context();
	HRESULT Clear_Graphic_Device(const _float4* pColor);
	HRESULT Present();

public: /* For.Input_Device */
	_bool		Key_Down(_uchar eKeyID);
	_bool		Key_Up(_uchar eKeyID);
	_bool		Key_Pressing(_uchar eKeyID);

	_bool		Mouse_Down(MOUSEKEYSTATE eMouseKeyID);
	_bool		Mouse_Up(MOUSEKEYSTATE eMouseKeyID);
	_bool		Mouse_Pressing(MOUSEKEYSTATE eMouseKeyID);

	_byte		Get_DIKeyState(_ubyte byKeyID);
	_byte		Get_DIMouseState(MOUSEKEYSTATE byMouseID);
	_long		Get_DIMouseMove(MOUSEMOVESTATE eMoveState);

public: /* For.Level_Manager */
	HRESULT Open_Level(_uint iLevelIndex, class CLevel* pNewLevel);	
	HRESULT Render_Level();

public: /* For.Object_Manager */
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObject* pPrototype);
	HRESULT Clone_GameObject(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg = nullptr);
	
public: /* For.Component_Manager */
	HRESULT Add_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag, class CComponent* pPrototype);
	class CComponent* Clone_Component(_uint iLevelIndex, const _tchar* pPrototypeTag, void* pArg = nullptr);


private:
	class CGraphic_Device*			m_pGraphic_Device = nullptr;
	class CInput_Device*			m_pInput_Device = nullptr;
	class CLevel_Manager*			m_pLevel_Manager = nullptr;
	class CObject_Manager*			m_pObject_Manager = nullptr;
	class CComponent_Manager*		m_pComponent_Manager = nullptr;

public:
	static void Release_Engine();

public:
	virtual void Free() override;
};

END