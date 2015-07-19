#ifndef _GAME_H_
#define _GAME_H_

#include "d3d9.h"
#include "GameWindow.h"
#include "Timer.h"
#include "Graphic.h"
#include "Input.h"

class CGame
{
private:
	CTimer* m_pTimer;
public:
	CGame();
	~CGame();
	int Init(HINSTANCE hInstance);
	void Run();
};
#endif