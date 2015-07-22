/*+===================================================================
File:      GameStateManager.h

Summary:   Định nghĩa lớp CGameStateManager .
===================================================================+*/
#pragma once

#include "BaseGameState.h"
#include "ResourcesManager.h"
#include "Timer.h"
#include <vector>
#include "MenuState.h"

/*C+==================================================================
Class:    CGameStateManager

Summary:  Lớp CGameStateManager là lớp singletone chứa phương thức để
chuyển đổi giữa các GameState, lưu trạng thái, get GameState hiện tại.
==================================================================-C*/
class CGameStateManager
{
private:

	CBaseGameState* m_pCurrentState;            /* State hiện tại của game */

	static CGameStateManager* s_instance;       /* Con trỏ đến thực thể cửa sổ duy nhất của lớp */

	//Đối tượng quản lý tài nguyên Game
	CResourcesManager* m_pResourceManager;
	//Mảng chứa các State
	vector<CBaseGameState*> m_aGameState;
public:
	CGameStateManager();
	~CGameStateManager();

	/*M+==================================================================
	Method:	    CGameStateManager::Init

	Summary:	Phương thức khởi tạo.
	==================================================================-M*/
	int Init(CBaseGameState* state);

	/*M+==================================================================
	Method:	    CGameStateManager::GetCurrentState

	Summary:	Phương thức lấy State hiện tại của game.
	==================================================================-M*/
	CBaseGameState* GetCurrentState();

	/*M+==================================================================
	Method:	    CGameStateManager::ChangeState

	Summary:	Phương thức lấy State hiện tại của game.
	==================================================================-M*/
	void ChangeState(CBaseGameState* state);

	/*M+==================================================================
	Method:	    CGameStateManager::GetInstance

	Summary:	Phương thức lấy thực thể duy nhất của lớp.
	==================================================================-M*/
	static CGameStateManager* GetInstance();

	CBaseGameState* m_pNextState;
};
