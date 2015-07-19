#pragma once

#include "Graphic.h"
#include "Input.h"

class CBaseGameState
{
protected:

	/*M+==================================================================
	Method:	    CBaseGameState::Update

	Summary:	Phương thức ảo update thế giới của GameState.
	==================================================================-M*/
	virtual void Update(float deltaTime) = 0;

	/*M+==================================================================
	Method:	    CBaseGameState::Render

	Summary:	Phương thức ảo vẽ thế giới của GameState.
	==================================================================-M*/
	virtual void Render() = 0;

public:
	CBaseGameState();
	~CBaseGameState();

	/*M+==================================================================
	Method:	    CBaseGameState::Init

	Summary:	Phương thức ảo khởi tạo của GameState.
	==================================================================-M*/
	virtual void Init() = 0;

	/*M+==================================================================
	Method:	    CBaseGameState::Init

	Summary:	Phương thức run của GameState.
	==================================================================-M*/
	void Run(float deltaTime);

	//Biến kiểm tra State đã kết thúc chưa
	bool m_bFinished;
	//Biến chứa con trỏ của state tiếp theo
	CBaseGameState* m_pNextState;
};

