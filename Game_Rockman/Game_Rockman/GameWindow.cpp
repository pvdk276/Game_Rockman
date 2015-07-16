#include "GameWindow.h"

CGameWindow::CGameWindow()
{

}


CGameWindow::~CGameWindow()
{

}

CGameWindow* CGameWindow::s_instance = NULL;

int CGameWindow::Init(HINSTANCE hInstance)
{
	m_hInstance = hInstance;

	// Tạo thuộc tính cho lớp cửa sổ.
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = m_hInstance;

	wc.lpfnWndProc = (WNDPROC)CGameWindow::WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = GAME_NAME; // Cần để là 1 hằng lưu lại tên. nếu bị lỗi LPCWSTR vào properties của project set character set -> multi-byte
	wc.hIconSm = NULL;

	// Đăng ký lớp cửa sổ.
	RegisterClassEx(&wc);

	RECT clientRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);

	// Tạo cửa sổ.
	m_hWnd = CreateWindow(
		GAME_NAME,
		GAME_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top,
		NULL,
		NULL,
		m_hInstance,
		NULL);

	if (!m_hWnd)
	{
		//int error = GetLastError();
		//trace(L"[ERORR] Failed to create window!!! Error code: %d.", error);
		//MessageBox(NULL, "Cannot create game window", "Error", MB_OK);
		return 0;
	}

	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

	return 1;
}

LRESULT CALLBACK CGameWindow::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

HINSTANCE CGameWindow::GetHInstance()
{
	return this->m_hInstance;
}

HWND CGameWindow::GetHWND()
{
	return m_hWnd;
}

CGameWindow* CGameWindow::GetInstance()
{
	if (s_instance == NULL)
		s_instance = new CGameWindow();

	return s_instance;
}
