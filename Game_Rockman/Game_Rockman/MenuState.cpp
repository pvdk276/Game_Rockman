/*+===================================================================
File:      MenuState.cpp

Summary:   Hiện thực hóa các phương thức của lớp CMenuState
===================================================================+*/
#include "MenuState.h"
#include "Viewport.h"
#include "Input.h"

CMenuState::CMenuState()
{
	this->Init();
}

CMenuState::~CMenuState()
{
	if (m_pBackground)
		delete m_pBackground;
	/*if (m_pSound)
		delete m_pSound;*/
}

void CMenuState::Init()
{
	m_pBackground = CResourcesManager::GetInstance()->GetTexture(ID_TEXTURE_BACKGROUND_3);
	m_pRockManIcon = CResourcesManager::GetInstance()->GetTexture(ID_TEXTURE_ICON_ROCK_MAN);
	m_pRockManIconGray = CResourcesManager::GetInstance()->GetTexture(ID_TEXTURE_ICON_ROCK_MAN_GRAY);
	m_pLine1 = CResourcesManager::GetInstance()->GetTexture(ID_TEXTURE_BACKGROUND_4);
	m_pLine2 = CResourcesManager::GetInstance()->GetTexture(ID_TEXTURE_BACKGROUND_2);
	m_pGameTitle = CResourcesManager::GetInstance()->GetTexture(ID_TEXTURE_GAME_TITLE);
	//m_pSound = CResourcesManager::GetInstance()->GetSound(ID_SOUND_OP_THEME);
	//m_pSound->Play();
	m_pos = D3DXVECTOR2(0, 0);
	m_v = D3DXVECTOR2(-200.0f, 0.0f);
	m_bIsEnterGame = false;
	m_bFinished = false;
	m_fTimeEnterGame = 2.0f;
}

void CMenuState::Update(float deltaTime)
{
	if (m_bFinished)
		return;
	if (CInput::GetInstance()->IsKeyPress(DIK_RETURN))
	{
		m_pos.x = SCREEN_WIDTH / 2;
		m_v.x = 0;
	}
	if (m_pos.x == SCREEN_WIDTH / 2)
	{
		if (CInput::GetInstance()->IsKeyPress(DIK_RETURN))
		{
			m_bIsEnterGame = true;
		}
	}
	if (m_bIsEnterGame)
	{
		if (m_fTimeTwinkle > 0)
		{
			m_fTimeTwinkle -= deltaTime;
		}
		else
		{
			m_fTimeTwinkle = 0.2f;
			m_bIsDraw = !m_bIsDraw;
		}
		if (m_fTimeEnterGame >= 0)
		{
			m_fTimeEnterGame -= deltaTime;
		}
		else
		{
			m_fTimeEnterGame = 2.0f;
			this->End();
		}
	}

}

void CMenuState::Render()
{
	if (m_bFinished)
		return;
	//Vẽ màn hình xanh
	for (int i = 0; i <= SCREEN_HEIGHT; i += 15)
	{
		for (int j = 0; j <= SCREEN_WIDTH; j += 15)
		{
			m_pBackground->Draw(D3DXVECTOR2(j, i));
		}
	}
	//Vẽ Game Title
	m_pGameTitle->Draw(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2.5));
	//Vẽ Rock man 
	m_pRockManIcon->Draw(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 1.5));

	//Vẽ Line1
	for (int i = 0;i <= SCREEN_WIDTH / 2 - 50 ;i+=5)
	{
		m_pLine1->Draw(D3DXVECTOR2(i, SCREEN_HEIGHT / 1.5));
	}
	for (int i = SCREEN_WIDTH;i >= SCREEN_WIDTH / 2 + 50;i -= 5)
	{
		m_pLine1->Draw(D3DXVECTOR2(i, SCREEN_HEIGHT / 1.5));
	}
	//Vẽ Line2
	for (int i = 0;i <= SCREEN_WIDTH / 2 - 50;i += 5)
	{
		m_pLine2->Draw(D3DXVECTOR2(i, SCREEN_HEIGHT / 1.5 + 10));
	}
	for (int i = SCREEN_WIDTH;i >= SCREEN_WIDTH / 2 + 50;i -= 5)
	{
		m_pLine2->Draw(D3DXVECTOR2(i, SCREEN_HEIGHT / 1.5 + 10));
	}
	//Khi nhấn Enter
	if (m_bIsDraw)
	{
		m_pRockManIconGray->Draw(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 1.5));
	}
}

void CMenuState::End()
{
	m_bFinished = true;
	delete m_pNextState;
	//m_pNextState = new CPlaysa();
	CGameStateManager::GetInstance()->ChangeState(m_pNextState);
}