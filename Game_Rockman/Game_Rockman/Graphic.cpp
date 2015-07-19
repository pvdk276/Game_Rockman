/*+===================================================================
File:      Graphic.cpp

Summary:   Định nghĩa các phương thức của CGraphic.
===================================================================+*/

#include "Graphic.h"

CGraphic* CGraphic::s_instance = NULL;
IDirect3DPixelShader9* CGraphic::texPS = NULL;

int CGraphic::Init(HWND hWnd)
{
	// Tạo ra đối tượng DirectX.
	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	// Khởi tạo các thuộc tính cho d3dpp.
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;

	// Tạo ra DirectX Device.
	m_d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_d3ddv);

	if (!m_d3ddv)
	{
		/*MessageBox(NULL, L"Failed to create directX device", L"Error", MB_OK);*/
		return 0;
	}

	D3DXCreateSprite(m_d3ddv, &m_lpSpriteHandler);

	//
	// Khởi tạo font handle
	//
	D3DXCreateFont(m_d3ddv, 18, 0,
		FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		"Press Start", &m_pFontHandle);
	return 1;
}

int CGraphic::BeginDraw()
{
	if (m_d3ddv->BeginScene())
		return 0;

	m_d3ddv->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	m_lpSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	return 1;
}

void CGraphic::EndDraw()
{
	m_lpSpriteHandler->End();
	m_d3ddv->EndScene();
	m_d3ddv->Present(NULL, NULL, NULL, NULL);
}

LPD3DXSPRITE CGraphic::GetSpriteHandler()
{
	return m_lpSpriteHandler;
}

CGraphic* CGraphic::GetInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new CGraphic();
	}

	return s_instance;
}

LPDIRECT3DDEVICE9 CGraphic::GetDevice()
{
	return m_d3ddv;
}

bool CGraphic::InitPixelShader(char* hlslFile)
{
	HRESULT hr = 0;

	ID3DXBuffer* shader = 0;
	ID3DXBuffer* errorBuffer = 0;
	ID3DXConstantTable* TextCT = 0;

	// Compile shader from a file
	hr = D3DXCompileShaderFromFile(hlslFile,
		0,
		0,
		"PSMain",           // entry point function name.
		"ps_2_0",           // HLSL shader name.
		D3DXSHADER_DEBUG,
		&shader,            // containing the created shader
		&errorBuffer,       // containing a listing of errors and warnings
		&TextCT);           // used to access shader constants
	if (errorBuffer)
	{
		::MessageBox(0, (char*)errorBuffer->GetBufferPointer(), 0, 0);
		errorBuffer->Release();
		return false;
	}
	if (FAILED(hr))
	{
		::MessageBox(0, "D3DXCompileShaderFromFile() - FAILED", 0, 0);
		return false;
	}

	// creates a pixel shader
	hr = m_d3ddv->CreatePixelShader((DWORD*)shader->GetBufferPointer(), &texPS);
	if (FAILED(hr))
	{
		::MessageBox(0, "CreateVertexShader - FAILED", 0, 0);
		return false;
	}
	shader->Release();
	return true;
}

CGraphic::~CGraphic()
{
	if (m_pFontHandle)
		delete m_pFontHandle;
	if (m_lpSpriteHandler)
		delete m_lpSpriteHandler;
	if (m_d3ddv)
		delete m_d3ddv;
	if (m_d3d)
		delete m_d3d;
}