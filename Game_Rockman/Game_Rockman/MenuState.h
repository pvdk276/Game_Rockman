/*+===================================================================
File:      MenuState.h

Summary:   Định nghĩa lớp CMenuState.
===================================================================+*/

#pragma once

#include "ResourcesManager.h"
#include "GameStateManager.h"
#include "Global.h"
//#include "ScoreState.h"
//#include "DSUtil.h"

/*C+==================================================================
Class:    CMenuState

Summary:  Lớp CMenuState chứa các thuộc tính và phương thức của menu
==================================================================-C*/

class CMenuState : public CBaseGameState
{
private:
	CTexture* m_pBackground;
	CTexture* m_pRockManIcon;
	CTexture* m_pRockManIconGray;
	CTexture* m_pLine1;
	CTexture* m_pLine2;
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_v;
	//CSound* m_pSound;
	bool m_bIsEnterGame;
	bool m_bIsDraw;
	float m_fTimeEnterGame;
	float m_fTimeTwinkle;
	RECT playerRect;
public:
	CMenuState();
	~CMenuState();
	void Init();
	void Update(float deltaTime);
	void Render();
	void End();
};