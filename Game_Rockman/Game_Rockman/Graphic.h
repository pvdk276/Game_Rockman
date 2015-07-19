#pragma once
/*+===================================================================
File:      CGraphic.h

Summary:   Định nghĩa lớp CGraphic .
===================================================================+*/

#include <d3dx9.h>
#include "Global.h"

/*C+==================================================================
Class:    CGraphic

Summary:  Lớp CGraphic dùng để tạo ra các đối tượng DirectX sử dụng trong
việc vẽ đồ họa trong game.
==================================================================-C*/
class CGraphic
{
private:
	LPDIRECT3D9 m_d3d;                 /* Con trỏ đối tượng DirectX */
	LPDIRECT3DDEVICE9 m_d3ddv;         /* Con trỏ DirectX Device */
	LPD3DXSPRITE m_lpSpriteHandler;    /**/
	LPD3DXFONT m_pFontHandle;	/* Con trỏ dùng trong việc vẽ chữ */
	static CGraphic* s_instance;       /* Con trỏ đến thực thể cửa sổ duy nhất của lớp */
public:

	/*M+==================================================================
	Method:	    CGraphic::Init

	Summary:	Phương thức tạo ra CGraphic.
	==================================================================-M*/
	int Init(HWND hWnd);

	/*M+==================================================================
	Method:	    CGraphic::BeginDraw

	Summary:	Phương thức khi bắt đầu việc vẽ hình.
	==================================================================-M*/
	int BeginDraw();

	/*M+==================================================================
	Method:	    CGraphic::EndDraw

	Summary:	Phương thức khi kế thúc việc vẽ hình.
	==================================================================-M*/
	void EndDraw();

	/*M+==================================================================
	Method:	    CGraphic::GetSpriteHandler

	Summary:	Phương thức lấy ra LPD3DXSPRITE.
	==================================================================-M*/
	LPD3DXSPRITE GetSpriteHandler();

	/*M+==================================================================
	Method:	    CGraphic::GetInstance

	Summary:	Phương thức lấy thực thể duy nhất của lớp.
	==================================================================-M*/
	static CGraphic* GetInstance();

	/*M+==================================================================
	Method:	    CGraphic::GetDevice

	Summary:	Phương thức lấy con trỏ Direct X device để truyền cho các phương
	thức ở các lớp khác
	==================================================================-M*/

	LPDIRECT3DDEVICE9 GetDevice();

	/*M+==================================================================
	Method:	    CGraphic::GetFontHandle

	Summary:	Phương thức lấy con trỏ font của DirectX
	==================================================================-M*/
	LPD3DXFONT* CGraphic::GetFontHandle()
	{
		return &m_pFontHandle;
	}

	/*M+==================================================================
	Method:	    CGraphic::InitPixelShader

	Summary:	Phương thức khởi tạo pixel shader để tạo hiệu ứng chớp
	của sao và nước

	Params:		hlslFile - File chứa các thông tin để dò màu và chuyển màu
	==================================================================-M*/

	bool InitPixelShader(char* hlslFile);

	//Biến lưu trữ PixelShader
	static IDirect3DPixelShader9* texPS;

	~CGraphic();
};

