#include "pch.h"
#include "Sample.h"

bool Sample::Init()
{
	//m_Plane.Create(g_pd3dDevice, L"../../data/shader/VS.txt",
	//	L"../../data/shader/PS.txt", L"../../data/tileA.jpg");

	return true;
}
bool Sample::Frame()
{
	//m_Plane.Frame();
	POINT cursor;
	GetCursorPos(&cursor);
	ScreenToClient(g_hWnd, &cursor);

	if (g_Input.GetKey(VK_LBUTTON) == KEY_PUSH)
	{
		if (!m_Texture == NULL)
		{
			CreateUI(cursor, m_Texture);
			m_Texture = NULL;
		};
	}

	if (g_Input.GetKey('0') == KEY_PUSH)
	{
		SDxState::g_RasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
		SDxState::SetRasterizerState(g_pd3dDevice, g_pImmediateContext,
			SDxState::g_RasterizerDesc);
		ApplyRS(g_pImmediateContext, SDxState::g_pRSEdit.Get());
	}
	//Matrix matProj = m_pMainCamera->m_matProj;
	//Vector2 v;
	//v.x = (((2.0f * cursor.x) / g_rtClient.right) - 1) / matProj._11;
	//v.y = -(((2.0f * cursor.y) / g_rtClient.bottom) - 1) / matProj._22;
	//m_Plane.m_vPos.x = v.x;
	//m_Plane.m_vPos.y = v.y;
	//m_matPlane._41 = m_Plane.m_vPos.x;
	//m_matPlane._42 = m_Plane.m_vPos.y;

	//Matrix matScale = Matrix::CreateScale(100, 100, 1);
	//Matrix matrix;
	//matrix = matScale * m_matPlane;
	//g_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//m_Plane.SetMatrix(&matrix, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);

	return true;
}
bool Sample::Render()
{
	//m_Plane.m_cbData.vColor[0] = m_pMainCamera->m_vLook.x;
	//m_Plane.m_cbData.vColor[1] = m_pMainCamera->m_vLook.y;
	//m_Plane.m_cbData.vColor[2] = m_pMainCamera->m_vLook.z;
	//
	//m_Plane.m_pTexture = m_Texture;
	//m_Plane.Render(g_pImmediateContext);
	//g_pImmediateContext->RSSetState(SDxState::g_pRSNoneCullSolid);
	//g_pImmediateContext->PSSetSamplers(0, 1, &SDxState::g_pSSWrapLinear);
	//g_pImmediateContext->OMSetDepthStencilState(SDxState::g_pDSSDepthEnable, 0);

	for (int iUI = 0; iUI < m_vUIList.size(); iUI++)
	{
		UIObject* pUI = m_vUIList[iUI];
		pUI->m_PlaneUI.m_cbData.vColor[0] = m_pMainCamera->m_vLook.x;
		pUI->m_PlaneUI.m_cbData.vColor[1] = m_pMainCamera->m_vLook.y;
		pUI->m_PlaneUI.m_cbData.vColor[2] = m_pMainCamera->m_vLook.z;

		//SDxState::g_RasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
		//SDxState::SetRasterizerState(g_pd3dDevice, g_pImmediateContext,
		//SDxState::g_RasterizerDesc);
		//ApplyRS(g_pImmediateContext, SDxState::g_pRSEdit.Get());
		pUI->m_PlaneUI.Render(g_pImmediateContext);
	}

	return true;
}
bool Sample::Release()
{
	for (int iUI = 0; iUI < m_vUIList.size(); iUI++)
	{
		UIObject* pUI = m_vUIList[iUI];
		pUI->m_PlaneUI.Release();
	}
	//m_Plane.Release();
	return true;
}

UIObject* Sample::CreateUI(POINT cursor, STexture* texture)
{
	UIObject* pUI = new UIObject;
	pUI->m_PlaneUI.Create(g_pd3dDevice, L"../../data/shader/VS.txt",
		L"../../data/shader/PS.txt", L"../../data/tileA.jpg");
	pUI->m_PlaneUI.m_pTexture = texture;
	pUI->Update(m_pMainCamera->m_matView, m_pMainCamera->m_matProj, cursor);
	m_vUIList.push_back(pUI);

	return pUI;
}
//UIObject* Sample::CreateUIForm(POINT cursor, STexture* texture)
//{
//	for (int parts = 0; parts < 9; parts++)
//	{
//		CreateUI(cursor, texture);
//		cursor.x -= m_Text
//	}
//
//	UIObject* pUI = new UIObject;
//	pUI->m_PlaneUI.Create(g_pd3dDevice, L"../../data/shader/VS.txt",
//		L"../../data/shader/PS.txt", L"../../data/tileA.jpg");
//	pUI->m_PlaneUI.m_pTexture = texture;
//	pUI->Update(m_pMainCamera->m_matView, m_pMainCamera->m_matProj, cursor);
//	m_vUIList.push_back(pUI);
//
//	return pUI;
//}