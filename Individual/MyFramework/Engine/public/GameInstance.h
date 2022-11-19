#pragma once

/* 싱글톤.  */
/* 클라이언트와 엔진의 소통을 위해 만들어진 클래스. */

#include "Base.h"
#include "Input_Device.h"
#include "Component_Manager.h"
#include "PipeLine.h"


BEGIN(Engine)

class ENGINE_DLL CGameInstance final : public CBase
{
	DECLARE_SINGLETON(CGameInstance);
private:
	CGameInstance();
	virtual ~CGameInstance() = default;

public:
	static _uint Get_StaticLevelIndex() {
		return m_iStaticLevelIndex;
	}

public: /* For.GameInstance */	
	static const _tchar*			m_pPrototypeTransformTag;

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

	_bool		Mouse_Down(CInput_Device::MOUSEKEYSTATE eMouseKeyID);
	_bool		Mouse_Up(CInput_Device::MOUSEKEYSTATE eMouseKeyID);
	_bool		Mouse_Pressing(CInput_Device::MOUSEKEYSTATE eMouseKeyID);

	_byte		Get_DIKeyState(_ubyte byKeyID);
	_byte		Get_DIMouseState(CInput_Device::MOUSEKEYSTATE byMouseID);
	_long		Get_DIMouseMove(CInput_Device::MOUSEMOVESTATE eMoveState);

public: /* For.Level_Manager */
	HRESULT Open_Level(_uint iLevelIndex, class CLevel* pNewLevel);	
	HRESULT Render_Level();

public: /* For.Object_Manager */
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObject* pPrototype);
	HRESULT Clone_GameObject(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg = nullptr);
	
public: /* For.Component_Manager */
	HRESULT Add_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag, class CComponent* pPrototype);
	class CComponent* Clone_Component(_uint iLevelIndex, const _tchar* pPrototypeTag, void* pArg = nullptr);

public: /* For.PipeLine */
	_matrix Get_TransformMatrix(CPipeLine::TRANSFORMSTATE eState) ;
	_float4x4 Get_TransformFloat4x4(CPipeLine::TRANSFORMSTATE eState) ;
	_matrix Get_TransformMatrix_Inverse(CPipeLine::TRANSFORMSTATE eState) ;
	void Set_Transform(CPipeLine::TRANSFORMSTATE eState, _fmatrix TransformMatrix);

public: /* For.Timer_Manager */ 
	_double		Get_TimeDelta(const _tchar* pTimerTag);
	HRESULT		Ready_Timer(const _tchar* pTimerTag);
	void		Update_Timer(const _tchar* pTimerTag);


private:
	static _uint					m_iStaticLevelIndex;

private:
	class CGraphic_Device*			m_pGraphic_Device = nullptr;
	class CInput_Device*			m_pInput_Device = nullptr;
	class CLevel_Manager*			m_pLevel_Manager = nullptr;
	class CObject_Manager*			m_pObject_Manager = nullptr;
	class CComponent_Manager*		m_pComponent_Manager = nullptr;
	class CPipeLine*				m_pPipeLine = nullptr;
	class CTimer_Manager*			m_pTimer_Manager = nullptr;

public:
	static void Release_Engine();

public:
	virtual void Free() override;
};

END