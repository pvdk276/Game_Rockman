/*+========================================================
File:		Texture.cpp
Sumary:	Hiện thực hóa các phương thức của lớp Texture
========================================================+*/
#include "Texture.h"

CTexture::CTexture(char* fileName, int cols, int rows, int count)
{
	m_szFileName = fileName;
	m_nCols = cols;
	m_nRows = rows;
	m_nCount = count;
	this->load();
}

CTexture::~CTexture()
{
	if (m_lpTexture != NULL)
		m_lpTexture->Release();
	if (m_szFileName)
		delete m_szFileName;
}

void CTexture::load()
{
	D3DXIMAGE_INFO info;
	HRESULT result;
	//Load hình từ đường dẫn của file
	result = D3DXGetImageInfoFromFile(m_szFileName, &info);

	if (result != D3D_OK)
	{
		char str[255];
		sprintf_s(str, "[texture.cpp] Failed to get information from image file [%s]", m_szFileName);
		OutputDebugString(str);
		return;
	}

	RECT s = { 0, 0, info.Width, info.Height };
	this->m_rectSize = s;

	m_nFrameWidth = info.Width / m_nCols;
	m_nFrameHeight = info.Height / m_nRows;

	LPDIRECT3DDEVICE9 dev = CGraphic::GetInstance()->GetDevice();
	if (!dev)
	{
		OutputDebugString("[texture.cpp] Can not get device to Load Image From File.");
		return;
	}
	//Hàm tạo texture từ file
	result = D3DXCreateTextureFromFileEx(
		dev,
		m_szFileName,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255), //Màu để tẩy
		&info,
		NULL,
		&m_lpTexture
		);

	if (result != D3D_OK)
	{
		char str[255];
		sprintf_s(str, "[texture.cpp] Failed to create texture from file [%s]", m_szFileName);
		OutputDebugString(str);
		return;
	}
}

void CTexture::Draw(D3DXVECTOR2 pos, bool isCenter)
{
	D3DXVECTOR3 position(pos.x, pos.y, 0);
	LPD3DXSPRITE spriteHandler = CGraphic::GetInstance()->GetSpriteHandler();
	if (!spriteHandler)
	{
		OutputDebugString("[texture.cpp] Can not get sprite handler to draw.");
		return;
	}

	if (isCenter){
		D3DXVECTOR3 center = D3DXVECTOR3(
			(m_rectSize.right - m_rectSize.left) / 2.0f,
			(m_rectSize.bottom - m_rectSize.top) / 2.0f,
			0);
		spriteHandler->Draw(m_lpTexture, &m_rectSize, &center, &position, 0xFFFFFFFF);
	}
	else
	{
		spriteHandler->Draw(m_lpTexture, &m_rectSize, NULL, &position, 0xFFFFFFFF);
	}
}

void CTexture::DrawRect(D3DXVECTOR2 pos, RECT srcRect, float angle, bool isCenter)
{
	D3DXVECTOR3 position(pos.x, pos.y, 0);
	LPD3DXSPRITE spriteHandler = CGraphic::GetInstance()->GetSpriteHandler();
	if (!spriteHandler)
	{
		OutputDebugString("[texture.cpp] Can not get sprite handler to draw.");
		return;
	}
	if (isCenter){
		D3DXVECTOR3 center = D3DXVECTOR3(
			(srcRect.right - srcRect.left) / 2.0f,
			(srcRect.bottom - srcRect.top) / 2.0f,
			0);
		D3DXVECTOR2 translationSprite = D3DXVECTOR2(0, 0);
		D3DXMATRIX oldMatrix;
		spriteHandler->GetTransform(&oldMatrix);
		D3DXMATRIX matRotate;
		D3DXMatrixTransformation2D(&matRotate, NULL, NULL, NULL, NULL, angle, &pos);
		spriteHandler->SetTransform(&matRotate);
		spriteHandler->Draw(m_lpTexture, &srcRect, &center, NULL, 0xFFFFFFFF);
		D3DXMatrixRotationZ(&matRotate, 0);
		spriteHandler->SetTransform(&oldMatrix);
	}
	else
	{
		spriteHandler->Draw(m_lpTexture, &srcRect, NULL, &position, 0xFFFFFFFF);
	}
}

void CTexture::DrawRectFlip(D3DXVECTOR2 pos, RECT srcRect, float scaleX, float scaleY, float angle, bool isCenter)
{
	D3DXVECTOR3 position(pos.x, pos.y, 0);
	LPD3DXSPRITE spriteHandler = CGraphic::GetInstance()->GetSpriteHandler();
	if (!spriteHandler)
	{
		OutputDebugString("[texture.cpp] Can not get sprite handler to draw.");
		return;
	}
	D3DXVECTOR2 scaling(scaleX, scaleY);
	if (isCenter){
		D3DXVECTOR3 center = D3DXVECTOR3(
			(srcRect.right - srcRect.left) / 2.0f,
			(srcRect.bottom - srcRect.top) / 2.0f,
			0);
		D3DXMATRIX oldMatrix;
		spriteHandler->GetTransform(&oldMatrix);
		D3DXMATRIX matRotate;
		D3DXMatrixTransformation2D(&matRotate, NULL, NULL, &scaling, NULL, angle, &pos);
		spriteHandler->SetTransform(&matRotate);
		spriteHandler->Draw(m_lpTexture, &srcRect, &center, NULL, 0xFFFFFFFF);
		D3DXMatrixRotationZ(&matRotate, 0);
		spriteHandler->SetTransform(&oldMatrix);
	}
	else
	{
		spriteHandler->Draw(m_lpTexture, &srcRect, NULL, &position, 0xFFFFFFFF);
	}
}

LPDIRECT3DTEXTURE9 CTexture::GetTexture()
{
	return this->m_lpTexture;
}

void CTexture::DrawRectFlipX(D3DXVECTOR2 pos, RECT srcRect, float angle, bool isCenter)
{
	D3DXVECTOR3 position(pos.x, pos.y, 0);
	LPD3DXSPRITE spriteHandler = CGraphic::GetInstance()->GetSpriteHandler();
	if (!spriteHandler)
	{
		OutputDebugString("[texture.cpp] Can not get sprite handler to draw.");
		return;
	}
	D3DXVECTOR2 scaling(-1.0f, 1.0f);
	if (isCenter){
		D3DXVECTOR3 center = D3DXVECTOR3(
			(srcRect.right - srcRect.left) / 2.0f,
			(srcRect.bottom - srcRect.top) / 2.0f,
			0);
		D3DXMATRIX oldMatrix;
		spriteHandler->GetTransform(&oldMatrix);
		D3DXMATRIX matRotate;
		D3DXMatrixTransformation2D(&matRotate, NULL, NULL, &scaling, NULL, angle, &pos);
		spriteHandler->SetTransform(&matRotate);
		spriteHandler->Draw(m_lpTexture, &srcRect, &center, NULL, 0xFFFFFFFF);
		D3DXMatrixRotationZ(&matRotate, 0);
		spriteHandler->SetTransform(&oldMatrix);
	}
	else
	{
		spriteHandler->Draw(m_lpTexture, &srcRect, NULL, &position, 0xFFFFFFFF);
	}
}
