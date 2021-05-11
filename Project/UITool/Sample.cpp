#include "pch.h"
#include "Sample.h"

bool Sample::Init()
{
	m_Plane.Create(g_pd3dDevice, L"../../data/shader/VS.txt",
		L"../../data/shader/PS.txt", L"../../data/tileA.jpg");

	return true;
}
bool Sample::Frame()
{
	POINT cursor;
	GetCursorPos(&cursor);
	ClientToScreen(g_hWnd, &cursor);

	m_Plane.m_vPos.x = cursor.x;
	m_Plane.m_vPos.y = cursor.y;

	if (g_Input.GetKey(VK_RBUTTON) == KEY_PUSH)
	{
		g_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_Plane.SetMatrix(NULL,
			&m_pMainCamera->m_matView,
			&m_pMainCamera->m_matProj);
		m_Plane.Render(g_pImmediateContext);
		g_pImmediateContext->RSSetState(SDxState::g_pRSWireFrame);
		g_pImmediateContext->PSSetSamplers(0, 1, &SDxState::g_pSSWrapLinear);
		g_pImmediateContext->OMSetDepthStencilState(SDxState::g_pDSSDepthEnable, 0);
	}
	m_Plane.Frame();

	return true;
}
bool Sample::Render()
{
	//g_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//m_Plane.SetMatrix(NULL,
	//	&m_pMainCamera->m_matView,
	//	&m_pMainCamera->m_matProj);
	//m_Plane.Render(g_pImmediateContext);
	//g_pImmediateContext->RSSetState(SDxState::g_pRSWireFrame);
	//g_pImmediateContext->PSSetSamplers(0, 1, &SDxState::g_pSSWrapLinear);
	//g_pImmediateContext->OMSetDepthStencilState(SDxState::g_pDSSDepthEnable, 0);


	return true;
}
bool Sample::Release()
{
	m_Plane.Release();
	return true;
}