/*+========================================================
File:		Texture.h
Sumary:	Định nghĩa lớp Texture, quản lý các texture, thực hiện vẽ
========================================================+*/

#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include "Graphic.h"
/*C+==================================================================
Class:    CTexture

Summary:  Lớp CTexure dùng để tạo và sử dụng các Texture
==================================================================-C*/
class CTexture
{
public:
	/*M+==================================================================
	Method:	    CTexture::CTexture

	Summary:	Phương thức khởi tạo.

	Params: fileName - đường dẫn đến file hình để load lên texture
	cols - số hàng của texture
	rows - số cột của texture
	count - số lượng frame của texture
	==================================================================-M*/
	CTexture(char* fileName, int cols = 1, int rows = 1, int count = 1);

	/*M+==================================================================
	Method:	    CTexture::CTexture

	Summary:	Phương thức hủy.
	==================================================================-M*/
	~CTexture();

	/*M+==================================================================
	Method:	    CTexture::Draw

	Summary:	Phương thức vẽ toàn bộ texture tại vị trí x, y

	Params:		pos - Vị trí vẽ
	isCenter - Vẽ từ vị trí center hay không
	==================================================================-M*/
	void Draw(D3DXVECTOR2 pos, bool isCenter = true);

	/*M+==================================================================
	Method:	    CTexture::DrawRect

	Summary:	Phương thức vẽ một phần RECT của texture tại vị trí x, y

	Params:		pos - Vị trí vẽ
	srcRect - Khu vực nguồn muốn vẽ
	isCenter - Có vẽ từ vị trí trung tâm hay không
	angle - Góc quay (tính theo radian)
	==================================================================-M*/
	void DrawRect(D3DXVECTOR2 pos, RECT srcRect, float angle = 0.0f, bool isCenter = true);

	void DrawRectFlip(D3DXVECTOR2 pos, RECT srcRect, float scaleX = 1.0f, float scaleY = 1.0f, float angle = 0.0f, bool isCenter = true);

	/*M+==================================================================
	Method:	    CTexture::DrawRectFlipX

	Summary:	Phương thức vẽ một phần RECT của texture tại vị trí x, y
	và lật theo chiều X

	Params:		pos - Vị trí vẽ
	srcRect - Khu vực nguồn muốn vẽ
	isCenter - Có vẽ từ vị trí trung tâm hay không
	angle - Góc quay (tính theo radian)
	==================================================================-M*/
	void DrawRectFlipX(D3DXVECTOR2 pos, RECT srcRect, float angle = 0.0f, bool isCenter = true);

	/*M+==================================================================
	Method:	    CTexture::GetTexture

	Summary:	Lấy về con trỏ của texture hiện tại
	==================================================================-M*/
	LPDIRECT3DTEXTURE9 GetTexture();

	//Số cột của texture
	int m_nCols;
	//Số hàng của texture
	int m_nRows;
	//Số lượng frame của texture
	int m_nCount;
	//Kích thước chiều rộng của texture
	int m_nFrameWidth;
	//Kích thước chiều cao của texture
	int m_nFrameHeight;
private:
	//Đường dẫn đến file hình
	char* m_szFileName;
	//Kích thước của hình
	RECT m_rectSize;
	//Con trỏ DirectX Texture chứa texture hiện tại
	LPDIRECT3DTEXTURE9 m_lpTexture;

	/*M+==================================================================
	Method:	    CTexture::load

	Summary:	Phương thức load hình từ file hình vào texture

	Notes:		Phương thức private
	==================================================================-M*/
	void load();
};