/*+===================================================================
File:      Sprite.cpp

Summary:   Định nghĩa các phương thức của CSprite.
===================================================================+*/

#include "Sprite.h"


CSprite::CSprite(CTexture* texture, float timeAnimation)
{
	m_pTexture = texture;
	m_nTimeAnimation = timeAnimation;
	m_nIndex = m_nStartIndex = 0;
	m_nEndIndex = m_pTexture->m_nCount - 1;
	m_nTimeLocal = 0.0f;
}

CSprite::CSprite(CTexture* texture, int start, int end, float timeAnimation)
{
	m_pTexture = texture;
	m_nTimeAnimation = timeAnimation;
	m_nIndex = m_nStartIndex = start;
	m_nEndIndex = end;
	m_nTimeLocal = 0.0f;
}

CSprite::~CSprite()
{
	if (m_pTexture)
		delete m_pTexture;
}

void CSprite::SetIndex(int startIndex, int endIndex)
{
	m_nStartIndex = startIndex;
	m_nEndIndex = endIndex;
}

void CSprite::Next()
{
	m_nIndex++;

	if (m_nIndex > m_nEndIndex)
		m_nIndex = m_nStartIndex;
}

void CSprite::Reset()
{
	m_nIndex = 0;
}

void CSprite::Update(float deltaTime)
{
	m_nTimeLocal += deltaTime;
	if (m_nTimeLocal >= m_nTimeAnimation / 1000.0f) {
		m_nTimeLocal = 0;
		this->Next();
	}
}

void CSprite::Draw(D3DXVECTOR2 pos, float angle)
{
	RECT rect;
	int spritePerRow = m_pTexture->m_nCols;
	int width = m_pTexture->m_nFrameWidth;
	int height = m_pTexture->m_nFrameHeight;
	rect.left = (m_nIndex % spritePerRow) * width;
	rect.top = (m_nIndex / spritePerRow) * height;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	LPD3DXSPRITE spriteHandler = CGraphic::GetInstance()->GetSpriteHandler();
	if (!spriteHandler)
	{
		OutputDebugString("[sprite.cpp] Can not get sprite handler to draw.");
		return;
	}
	LPDIRECT3DTEXTURE9 texture = m_pTexture->GetTexture();
	if (!texture)
	{
		OutputDebugString("[sprite.cpp] Can not get texture to draw.");
		return;
	}

	m_pTexture->DrawRect(pos, rect, angle);
}

void CSprite::DrawFlip(D3DXVECTOR2 pos, float scaleX, float scaleY, float angle)
{
	int spritePerRow = m_pTexture->m_nCols;
	int width = m_pTexture->m_nFrameWidth;
	int height = m_pTexture->m_nFrameHeight;
	RECT rect;
	rect.left = (m_nIndex % spritePerRow) * width;
	rect.top = (m_nIndex / spritePerRow) * height;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	LPD3DXSPRITE spriteHandler = CGraphic::GetInstance()->GetSpriteHandler();
	if (!spriteHandler)
	{
		OutputDebugString("[sprite.cpp] Can not get sprite handler to draw.");
		return;
	}
	LPDIRECT3DTEXTURE9 texture = m_pTexture->GetTexture();
	if (!texture)
	{
		OutputDebugString("[sprite.cpp] Can not get texture to draw.");
		return;
	}
	m_pTexture->DrawRectFlip(pos, rect, scaleX, scaleY);
}

void CSprite::DrawFlipX(D3DXVECTOR2 pos, float angle)
{
	int spritePerRow = m_pTexture->m_nCols;
	int width = m_pTexture->m_nFrameWidth;
	int height = m_pTexture->m_nFrameHeight;
	RECT rect;
	rect.left = (m_nIndex % spritePerRow) * width;
	rect.top = (m_nIndex / spritePerRow) * height;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	LPD3DXSPRITE spriteHandler = CGraphic::GetInstance()->GetSpriteHandler();
	if (!spriteHandler)
	{
		OutputDebugString("[sprite.cpp] Can not get sprite handler to draw.");
		return;
	}
	LPDIRECT3DTEXTURE9 texture = m_pTexture->GetTexture();
	if (!texture)
	{
		OutputDebugString("[sprite.cpp] Can not get texture to draw.");
		return;
	}
	m_pTexture->DrawRectFlipX(pos, rect, angle);
}

int CSprite::GetWidth()
{
	return m_pTexture->m_nFrameWidth;
}

int CSprite::GetHeight()
{
	return m_pTexture->m_nFrameHeight;
}
