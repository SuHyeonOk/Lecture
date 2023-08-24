#include "..\..\Header\InputDev.h"


USING(Engine)
IMPLEMENT_SINGLETON(CInputDev)

CInputDev::CInputDev()
	: m_pInputSDK(nullptr), m_pKeyBoard(nullptr), m_pMouse(nullptr)
{
	ZeroMemory(m_byKeyState, sizeof(m_byKeyState));
	ZeroMemory(&m_MouseState, sizeof(m_MouseState));
	m_MouseLeftState = KEY_STATE::E_END;
	m_MouseRightState = KEY_STATE::E_END;
}


CInputDev::~CInputDev()
{
	Free();
}

HRESULT CInputDev::Ready_InputDev(HINSTANCE hInst, HWND hWnd)
{
	m_hWnd = hWnd;
	_states.resize(KEY_TYPE_COUNT, KEY_STATE::NONE);

	// DInput �İ�ü�� �����ϴ� �Լ�
	FAILED_CHECK_RETURN(DirectInput8Create(hInst,
											DIRECTINPUT_VERSION,
											IID_IDirectInput8,
											(void**)&m_pInputSDK,
											NULL), E_FAIL);

	// Ű���� ��ü ����
	FAILED_CHECK_RETURN(m_pInputSDK->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr), E_FAIL);

	// ������ Ű���� ��ü�� ���� ������ �� ��ü���� �����ϴ� �Լ�
	m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard);

	// ��ġ�� ���� �������� �������ִ� �Լ�, (Ŭ���̾�Ʈ�� ���ִ� ���¿��� Ű �Է��� ������ ������ �����ϴ� �Լ�)
	m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// ��ġ�� ���� access ������ �޾ƿ��� �Լ�
	m_pKeyBoard->Acquire();


	// ���콺 ��ü ����
	FAILED_CHECK_RETURN(m_pInputSDK->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr), E_FAIL);

	// ������ ���콺 ��ü�� ���� ������ �� ��ü���� �����ϴ� �Լ�
	m_pMouse->SetDataFormat(&c_dfDIMouse);

	// ��ġ�� ���� �������� �������ִ� �Լ�, Ŭ���̾�Ʈ�� ���ִ� ���¿��� Ű �Է��� ������ ������ �����ϴ� �Լ�
	m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// ��ġ�� ���� access ������ �޾ƿ��� �Լ�
	m_pMouse->Acquire();

	return S_OK;
}

void CInputDev::SetUp_InputDev(void)
{
	HWND hwnd = ::GetActiveWindow(); //Ȱ��â�� �ƴϸ� �Է� ����
	if (m_hWnd != hwnd)
	{
		for (_uint key = 0; key < KEY_TYPE_COUNT; key++)
			_states[key] = KEY_STATE::NONE;
		return;
	}

	m_pKeyBoard->GetDeviceState(256, m_byKeyState);

	for (_uint key = 0; key < KEY_TYPE_COUNT; key++)
	{
		// Ű�� ���� ������ true
		if (m_byKeyState[key] & 0x80)
		{
			KEY_STATE& state = _states[key];

			// ���� �����ӿ� Ű�� ���� ���¶�� PRESS
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
				state = KEY_STATE::PRESS;
			else
				state = KEY_STATE::DOWN;
		}
		else
		{
			KEY_STATE& state = _states[key];

			// ���� �����ӿ� Ű�� ���� ���¶�� UP
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
				state = KEY_STATE::UP;
			else
				state = KEY_STATE::NONE;
		}
	}

	m_pMouse->GetDeviceState(sizeof(m_MouseState), &m_MouseState);

	if (Get_DIMouseState(DIM_LB) & 0x8000)
	{
		KEY_STATE& state = m_MouseLeftState;

		// ���� �����ӿ� Ű�� ���� ���¶�� PRESS
		if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
			state = KEY_STATE::PRESS;
		else
			state = KEY_STATE::DOWN;
	}
	else
	{
		KEY_STATE& state = m_MouseLeftState;

		// ���� �����ӿ� Ű�� ���� ���¶�� UP
		if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
			state = KEY_STATE::UP;
		else
			state = KEY_STATE::NONE;
	}


	if (Get_DIMouseState(DIM_RB) & 0x8000)
	{
		KEY_STATE& state = m_MouseRightState;

		// ���� �����ӿ� Ű�� ���� ���¶�� PRESS
		if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
			state = KEY_STATE::PRESS;
		else
			state = KEY_STATE::DOWN;
	}
	else
	{
		KEY_STATE& state = m_MouseRightState;

		// ���� �����ӿ� Ű�� ���� ���¶�� UP
		if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
			state = KEY_STATE::UP;
		else
			state = KEY_STATE::NONE;
	}
}

void Engine::CInputDev::Free(void)
{
	Safe_Release(m_pKeyBoard);
	Safe_Release(m_pMouse);
	Safe_Release(m_pInputSDK);
}