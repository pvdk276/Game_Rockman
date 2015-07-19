/*+===================================================================
File:      Sprite.h

Summary:   Định nghĩa lớp CSprite .
===================================================================+*/

#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Texture.h"
#include "Graphic.h"

/*C+==================================================================
Class:    CSprite

Summary:  Lớp CSprite dùng để vẽ hình và tạo animation.
==================================================================-C*/

class CSprite
{
private:
	//LPDIRECT3DTEXTURE9 m_lpImage;	 /*Texture giữ hình ảnh*/
	//LPD3DXSPRITE m_lpSpriteHandler;  /**/

	CTexture* m_pTexture;			/*Con trỏ đối tượng texture giữ hình ảnh*/
public:
	int m_nIndex;					 /*Vị trí hiện tại trên texture*/
	int m_nStartIndex;               /*Chỉ số đầu của Sprite*/
	int m_nEndIndex;                 /*Chỉ số cuối của Sprite*/
	float m_nTimeAnimation;			/*Thời gian của hiệu ứng chuyển frame*/
	float m_nTimeLocal;				/*Thời gian tính hiệu ứng chuyển frame*/

	/*M+==================================================================
	Method:	    CSprite::CSprite

	Summary:	Phương thức tạo khởi với các tham số.

	Args:		texture - Con trỏ chứa texture sẽ truyền vào
	timeAnimation - Thời gian hiệu ứng chuyển frame
	==================================================================-M*/
	CSprite(CTexture* texture, float timeAnimation);

	/*M+==================================================================
	Method:	    CSprite::CSprite

	Summary:	Phương thức tạo khởi với các tham số.

	Args:		texture - Con trỏ chứa texture sẽ truyền vào
	start - Chỉ số frame đầu
	end - Chỉ số frame cuối
	timeAnimation - Thời gian hiệu ứng chuyển frame
	==================================================================-M*/
	CSprite(CTexture* texture, int start, int end, float timeAnimation);

	/*M+==================================================================
	Method:	    CSprite::~CSprite

	Summary:	Phương thức hủy.
	==================================================================-M*/
	~CSprite();

	/*M+==================================================================
	Method:	    CSprite::SetIndex

	Summary:	Phương thức thiết lập vị trí bắt đầu và kết thúc của một
	chuyển động.
	==================================================================-M*/
	void SetIndex(int startIndex, int endIndex);

	/*M+==================================================================
	Method:	    CSprite::Next

	Summary:	Phương thức chuyển sprite.
	==================================================================-M*/
	void Next();

	/*M+==================================================================
	Method:	    CSprite::Reset

	Summary:	Phương thức reset lại vị trí của sprite đầu (m_nStartIndex).
	==================================================================-M*/
	void Reset();

	/*M+==================================================================
	Method:	    CSprite::Update

	Summary:	Phương thức cập nhật Sprite

	Args:	    deltaTime - Thời gian chuyển frame
	==================================================================-M*/
	void Update(float deltaTime);

	/*M+==================================================================
	Method:	    CSprite::Draw

	Summary:	Phương thức vẽ sprite bình thường.

	Args:	    D3DXVECTOR2 pos - Vị trí vẽ
	color - Màu để tạo alpha
	angle - góc xoay
	==================================================================-M*/
	void Draw(D3DXVECTOR2 pos, float angle = 0.0f);

	void DrawFlip(D3DXVECTOR2 pos, float scaleX = 1.0f, float scaleY = 1.0f, float angle = 0.0f);

	/*M+==================================================================
	Method:	    CSprite::DrawFlipX

	Summary:	Phương thức vẽ sprite lật theo trục X.

	Args:	    D3DXVECTOR2 pos - Vị trí vẽ
	==================================================================-M*/
	void DrawFlipX(D3DXVECTOR2 pos, float angle = 0.0f);

	/*M+==================================================================
	Method:	    CSprite::GetWidth

	Summary:	Phương thức lấy về chiều rộng của 1 Frame.
	==================================================================-M*/
	int GetWidth();

	/*M+==================================================================
	Method:	    CSprite::GetHeight

	Summary:	Phương thức lấy về chiều cao của 1 Frame.
	==================================================================-M*/
	int GetHeight();
};

