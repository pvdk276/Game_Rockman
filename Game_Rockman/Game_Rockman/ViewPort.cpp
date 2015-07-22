#include "Viewport.h"

CViewport* CViewport::s_instance = NULL;

CViewport::CViewport() {
	D3DXMatrixIdentity(&m_MatrixTransform);
	m_MatrixTransform._22 = -1;
	this->SetPosition(D3DXVECTOR2(0, (float)SCREEN_HEIGHT));
}

CViewport::~CViewport() {

}

D3DXVECTOR2 CViewport::TransformMatrix(D3DXVECTOR2 pos) {
	D3DXVECTOR4 result;

	D3DXVECTOR2 x = m_ViewportPos;
	D3DXVec3Transform(&result, &D3DXVECTOR3(pos.x, pos.y, 0), &m_MatrixTransform);
	return D3DXVECTOR2(static_cast<int>(result.x), static_cast<int>(result.y));
}

void CViewport::SetPosition(D3DXVECTOR2 pos, bool isFollowBill) {
	if (isFollowBill)
	{
		// Cập nhật vị trí viewport theo bill.
		m_ViewportPos.x = pos.x - SCREEN_WIDTH / 2.0f;
		m_ViewportPos.y = pos.y + SCREEN_HEIGHT / 2.0f;
	}
	else
	{
		m_ViewportPos.x = pos.x;
		m_ViewportPos.y = pos.y;
	}

	// Xác định lại vị trí viewport nếu ra khỏi biên.
	m_ViewportPos.x = m_ViewportPos.x >= m_limitX1 ? m_ViewportPos.x : m_limitX1;
	m_ViewportPos.x = m_ViewportPos.x >= m_limitX2 ? m_limitX2 : m_ViewportPos.x;
	m_ViewportPos.y = m_ViewportPos.y >= m_limitY1 ? m_ViewportPos.y : m_limitY1;
	m_ViewportPos.y = m_ViewportPos.y >= m_limitY2 ? m_limitY2 : m_ViewportPos.y;

	// Cập nhật lại biên trái và dưới, để bill ko thể đi lùi.
	m_limitX1 = m_ViewportPos.x;
	m_limitY1 = m_ViewportPos.y;

	// Xác định lại ma trận transform.
	m_MatrixTransform._41 = -m_ViewportPos.x;
	m_MatrixTransform._42 = m_ViewportPos.y;
}

D3DXVECTOR2 CViewport::GetPosition()
{
	return m_ViewportPos;
}

void CViewport::SetLimitPos(int mapWidth, int mapHeight)
{
	if (g_nCurentLvl == ID_LEVEL2)
		m_limitX1 = 64;
	else
		m_limitX1 = 0;
	m_limitX2 = mapWidth - SCREEN_WIDTH;
	m_limitY1 = SCREEN_HEIGHT;
	m_limitY2 = mapHeight >= SCREEN_HEIGHT ? mapHeight : SCREEN_HEIGHT;
}

CViewport* CViewport::GetInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new CViewport();
	}

	return s_instance;
}

//void CViewport::SetToPos(D3DXVECTOR2 pos, float timeFrame) 
//{
//	D3DXVECTOR2 posA(this->GetPosition().x, this->GetPosition().y);
//	switch (g_nCurentLvl)
//	{
//	case ID_LEVEL1:
//	case ID_LEVEL3:
//		if (posA.x < pos.x)
//			posA.x += VIEWPORT_VX * timeFrame;
//		else
//			posA.x = pos.x;
//		this->SetPosition(posA);
//		break;
//	case ID_LEVEL2:
//		posA.y += VIEWPORT_VY * timeFrame;
//		if (posA.y > pos.y)
//			posA.y = pos.y;
//		this->SetPosition(posA);
//		break;
//	}
//}