/*+========================================================
File:		Viewport.h
Sumary:	Định nghĩa lớp Viewport
========================================================+*/
#pragma once
#include <d3dx9.h>
#include "Global.h"
#include "GameInfo.h"

/*C+==================================================================
Class:    CViewport

Summary:  Lớp CViewport định nghĩa Camera để vẽ theo tọa độ của
thế giới thật
==================================================================-C*/

#define VIEWPORT_VX 100
#define VIEWPORT_VY 100

class CViewport
{
public:
	/*M+==================================================================
	Method:	    CViewport::CViewport

	Summary:	Phương thức khởi tạo
	==================================================================-M*/
	CViewport();

	/*M+==================================================================
	Method:	    CViewport::~CViewport

	Summary:	Phương thức hủy
	==================================================================-M*/
	~CViewport();

	/*M+==================================================================
	Method:	    CViewport::TransformMatrix

	Summary:	Phương thức chuyển tọa độ của direct X sang tọa độ của
	thế giới thực
	==================================================================-M*/
	D3DXVECTOR2 TransformMatrix(D3DXVECTOR2 pos);

	/*M+==================================================================
	Method:	    CViewport::SetPosition

	Summary:	Phương thức chuyển tọa độ của direct X sang tọa độ của
	thế giới thực
	==================================================================-M*/
	void SetPosition(D3DXVECTOR2 pos, bool isFollowBill = true);

	/*M+==================================================================
	Method:	    CViewport::SetPosition

	Summary:	Phương thức lấy ra vị trí viewport.
	==================================================================-M*/
	D3DXVECTOR2 GetPosition();

	/*M+==================================================================
	Method:	    CViewport::SetLimitPos

	Summary:	Phương thức thiết lập biên trái, phải, trên, dưới của
	viewport theo map.
	==================================================================-M*/
	void SetLimitPos(int mapWidth, int mapHeight);

	static CViewport* GetInstance();
private:
	//Ma trận Transform
	D3DXMATRIX m_MatrixTransform;
	//Vị trí của view port
	D3DXVECTOR2 m_ViewportPos;

	float m_limitX1;    // Giới hạn bên trái.
	float m_limitX2;    // Giới hạn bên phải.
	float m_limitY1;    // Giới hạn ở dưới.
	float m_limitY2;    // Giới ở trên.

	static CViewport* s_instance;
};