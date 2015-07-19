/*+===================================================================
File:      Input.cpp

Summary:   Định nghĩa các phương thức của CInput.
===================================================================+*/

#include "Input.h"

CInput* CInput::s_instance = NULL;

int CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT result;
	result = DirectInput8Create(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_lpInput,
		NULL);
	if (result != DI_OK)
	{
		//trace(L"[ERROR] Failed to Create Direct Input!!! Error code: %d.", result);
		return 0;
	}

	//
	// Khởi tạo đối tượng làm việc với bàn phím
	//
	result = m_lpInput->CreateDevice(
		GUID_SysKeyboard,
		&m_lpInputDevice,
		NULL);
	if (result != DI_OK)
	{
		//trace(L"[ERROR] Faile to create direct input keyboard!!! Error code: %d.", result);
		return 0;
	}

	// 
	// Thiết lập dạng dữ liệu bàn phím
	//
	result = m_lpInputDevice->SetDataFormat(&c_dfDIKeyboard);
	if (result != DI_OK)
	{
		//trace(L"[ERROR] Faile to set data format for direct input keyboard!!! Error code: %d.", result);
		return 0;
	}

	result = m_lpInputDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (result != DI_OK)
	{
		//trace(L"[ERROR] Faile to set cooperative level for direct input keyboard!!! Error code: %d.", result);
		return 0;
	}

	//
	// Cài đặt bộ đệm cho bàn phím
	//
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE;
	m_lpInputDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	m_lpInputDevice->Acquire();
	if (result != DI_OK)
	{
		//trace(L"[WARRNING] Faile to acquire direct input keyboard!!! Error code: %d.", result);
		return 0;
	}
	return 1;
}

void CInput::ProcessKeyBroad()
{
	if (m_lpInputDevice->GetDeviceState(sizeof(m_keyStates), m_keyStates) != DI_OK)
	{
		m_lpInputDevice->Acquire();
		m_lpInputDevice->GetDeviceState(sizeof(m_keyStates), m_keyStates);
	}

	m_dwElements = KEYBOARD_BUFFER_SIZE;
	m_lpInputDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_keyEvents, &m_dwElements, 0);
}

int CInput::IsKeyPress(int keyCode)
{

	for (DWORD i = 0; i < m_dwElements; i++)
	{
		int keyCodeBuffer = m_keyEvents[i].dwOfs;
		int keyState = m_keyEvents[i].dwData;

		if ((keyCode == keyCodeBuffer) && ((keyState & 0x80) > 0))
		{
			return 1;
		}
	}

	return 0;
}

int CInput::IsKeyRelease(int keyCode)
{
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT result = m_lpInputDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_keyEvents, &dwElements, 0);

	for (DWORD i = 0; i < dwElements; i++)
	{
		int keyCodeBuffer = m_keyEvents[i].dwOfs;
		int keyState = m_keyEvents[i].dwData;

		if ((keyCode == keyCodeBuffer) && ((keyState & 0x80) == 0))
		{
			return 1;
		}
	}

	return 0;
}

int CInput::IsKeyDown(int keyCode)
{
	return (m_keyStates[keyCode] & 0x80) > 0;
}

int CInput::IsKeyUp(int keyCode)
{
	return (m_keyStates[keyCode] & 0x80) == 0;
}

CInput* CInput::GetInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new CInput();
	}

	return s_instance;
}

CInput::~CInput()
{
	if (m_lpInput)
		delete m_lpInput;
	if (m_lpInputDevice)
		delete m_lpInputDevice;
}

void CInput::Unacquire()
{
	m_lpInputDevice->Unacquire();
}