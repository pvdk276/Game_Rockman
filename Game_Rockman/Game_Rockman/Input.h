/*+===================================================================
File:      Input.h

Summary:   Định nghĩa lớp CInput .
===================================================================+*/
#pragma once
#include <dinput.h>

#define KEYBOARD_BUFFER_SIZE 1024 

/*C+==================================================================
Class:    CInput

Summary:  Lớp CInput dùng để xử lí bàn phím, xác định phím nào được
nhấn.
==================================================================-C*/

class CInput
{
private:
	LPDIRECTINPUT8 m_lpInput;                                /*Đối tượng DirectInput*/
	LPDIRECTINPUTDEVICE8 m_lpInputDevice;                    /*Đối tượng DirectInputDevice*/

	BYTE  m_keyStates[256];                                  /**/
	DIDEVICEOBJECTDATA m_keyEvents[KEYBOARD_BUFFER_SIZE];    /**/

	DWORD m_dwElements;

	static CInput* s_instance;                               /* Con trỏ đến thực thể cửa sổ duy nhất của lớp */
public:
	~CInput();

	/*M+==================================================================
	Method:	    CInput::Init

	Summary:	Phương thức tạo ra CInput.
	==================================================================-M*/
	int Init(HINSTANCE hInstance, HWND hWnd);

	/*M+==================================================================
	Method:	    CInput::ProcessKeyBroad

	Summary:	Phương thức khởi động bàn phím.
	==================================================================-M*/
	void ProcessKeyBroad();

	/*M+==================================================================
	Method:	    CInput::IsKeyPress

	Summary:	Phương thức kiếm tra xem phím có được nhấn hay không(theo
	phương pháp buffer).
	==================================================================-M*/
	int IsKeyPress(int keyCode);

	/*M+==================================================================
	Method:	    CInput::IsKeyPress

	Summary:	Phương thức kiếm tra xem phím có được nhả hay không(theo
	phương pháp buffer).
	==================================================================-M*/
	int IsKeyRelease(int keyCode);

	/*M+==================================================================
	Method:	    CInput::IsKeyDown

	Summary:	Phương thức kiếm tra xem phím có được giữ hay không.
	==================================================================-M*/
	int IsKeyDown(int keyCode);

	/*M+==================================================================
	Method:	    CInput::IsKeyDown

	Summary:	Phương thức kiếm tra xem phím có được thả hay không.
	==================================================================-M*/
	int IsKeyUp(int keyCode);

	/*M+==================================================================
	Method:	    CInput::GetInstance

	Summary:	Phương thức lấy thực thể duy nhất của lớp.
	==================================================================-M*/
	static CInput* GetInstance();

	/*M+==================================================================
	Method:	    CInput::Unacquire

	Summary:	Phương thức unacquire keyboard
	==================================================================-M*/
	void Unacquire();
};

