#pragma once

#include <Windows.h>
#include "Global.h"

class CGameWindow
{
private:
	HINSTANCE m_hInstance;		        /* Định danh của ứng dụng */
	HWND	  m_hWnd;			        /* Định danh của cửa sổ */
	static CGameWindow* s_instance;     /* Con trỏ đến thực thể cửa sổ duy nhất của lớp */
public:
	CGameWindow();
	~CGameWindow();
	/*M+==================================================================
	Method:	    CGameWindow::Init

	Summary:	Phương thức tạo ra CGameWindow.
	==================================================================-M*/
	int Init(HINSTANCE hInstance);

	/*M+==================================================================
	Method:	    CGameWindow::WinProc

	Summary:	Phương thức xử lý thông điệp cửa sổ.
	==================================================================-M*/
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	/*M+==================================================================
	Method:	    CGameWindow::GetHInstance

	Summary:	Phương thức lấy đối tượng Handle Instance.
	==================================================================-M*/
	HINSTANCE GetHInstance();

	/*M+==================================================================
	Method:	    CGameWindow::GetHWND

	Summary:	Phương thức lấy đối tượng HWND.
	==================================================================-M*/
	HWND GetHWND();

	/*M+==================================================================
	Method:	    CGameWindow::GetInstance

	Summary:	Phương thức lấy thực thể duy nhất của lớp.
	==================================================================-M*/
	static CGameWindow* GetInstance();
};

