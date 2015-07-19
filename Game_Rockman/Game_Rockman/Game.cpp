#include "Game.h"

CGame::CGame()
{

}
CGame::~CGame()
{
	if (m_pTimer)
		delete m_pTimer;
}
int CGame::Init(HINSTANCE hInstance)
{
	CGameWindow* pGameWindow = CGameWindow::GetInstance();

	// Khởi tạo cửa sổ game.
	if (!pGameWindow->Init(hInstance))
	{
		OutputDebugString("[Game.cpp] Cannot init pGameWindow.");
		return 0;
	}
	/*
	// Khởi tạo đối tượng đồ họa của game.
	if (!CGraphic::GetInstance()->Init(pGameWindow->GetHWND()))
	{
		OutputDebugString("[Game.cpp] Cannot init CGraphic.");
		return 0;
	}


	//Khởi tạo đối tượng Input.
	if (!CInput::GetInstance()->Init(pGameWindow->GetHInstance(), pGameWindow->GetHWND()))
	{
		OutputDebugString("[Game.cpp] Cannot init CInput.");
		return 0;
	}

	//Khởi tạo đối tượng quản lí GameState.
	if (!CGameStateManager::GetInstance()->Init(new CMenuState()))
	{
		OutputDebugString("[Game.cpp] Cannot init CGameStateManager.");
		return 0;
	}
	*/
	//	Khởi tạo đối tượng timer
	m_pTimer = CTimer::GetInstance();
	m_pTimer->SetMaxFps((float)GAME_FPS);
	return 1;
}
void CGame::Run()
{
	MSG msg;
	int done = 0;
	m_pTimer->StartCount();

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (m_pTimer->GetTime() < 1.0f)
			{
				m_pTimer->EndCount();
				// Get Stage hiện tại và run.
				//CGameStateManager::GetInstance()->GetCurrentState()->Run(m_pTimer->GetTime());
			}
		}
	}
}