/*+===================================================================
File:      BaseGameState.cpp

Summary:   Định nghĩa các phương thức của CBaseGameState.
===================================================================+*/

#include "BaseGameState.h"

CBaseGameState::CBaseGameState()
{
	m_pNextState = NULL;
}

CBaseGameState::~CBaseGameState()
{
	if (m_pNextState)
		delete m_pNextState;
}

void CBaseGameState::Run(float deltaTime)
{
	// Update thế giới.
	Update(deltaTime);

	// Vẽ thế giới.
	if (CGraphic::GetInstance()->BeginDraw())
	{
		CInput::GetInstance()->ProcessKeyBroad();
		Render();
		CGraphic::GetInstance()->EndDraw();
	}
}