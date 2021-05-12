#include "pch.h"
#include "Sample.h"

bool Sample::Init()
{
	//m_Plane = new SShapePlane;
	//SMapDesc desc;
	//desc.iNumCols = 257;// m_Map.m_iNumCols;
	//desc.iNumRows = 257; //m_Map.m_iNumRows;
	//desc.fCellDistance = 10;
	//desc.fScaleHeight = 10.0f;
	//desc.szTexFile = L"../../data/map/grass_2.jpg";
	//desc.szVS = L"../../data/shader/VS.txt";
	//desc.szPS = L"../../data/shader/PS.txt";

	//m_Plane.CreateMap(g_pd3dDevice, g_pImmediateContext, desc);
	m_Plane.Create(g_pd3dDevice, L"../../data/shader/VS.txt",
		L"../../data/shader/PS.txt", L"../../data/tileA.jpg");

	return true;
}
bool Sample::Frame()
{
	m_Plane.Frame();

	POINT cursor;
	GetCursorPos(&cursor);
	ScreenToClient(g_hWnd, &cursor);

	if (g_Input.GetKey(VK_LBUTTON) == KEY_PUSH)
	{
		AddUI();
	}

	Matrix matProj = m_pMainCamera->m_matProj;
	Vector2 v;
	v.x = (((2.0f * cursor.x) / g_rtClient.right) - 1) / matProj._11;
	v.y = -(((2.0f * cursor.y) / g_rtClient.bottom) - 1) / matProj._22;
	m_Plane.m_vPos.x = v.x;
	m_Plane.m_vPos.y = v.y;

	m_matPlane._41 = m_Plane.m_vPos.x;
	m_matPlane._42 = m_Plane.m_vPos.y;

	Matrix matScale = Matrix::CreateScale(100, 100, 1);
	Matrix matrix;
	matrix = matScale * m_matPlane;
	g_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_Plane.SetMatrix(&matrix, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);

	return true;
}
bool Sample::Render()
{
	m_Plane.m_cbData.vColor[0] = m_pMainCamera->m_vLook.x;
	m_Plane.m_cbData.vColor[1] = m_pMainCamera->m_vLook.y;
	m_Plane.m_cbData.vColor[2] = m_pMainCamera->m_vLook.z;
	
	m_Plane.m_pTexture = m_Texture;
	m_Plane.Render(g_pImmediateContext);
	g_pImmediateContext->RSSetState(SDxState::g_pRSNoneCullSolid);
	g_pImmediateContext->PSSetSamplers(0, 1, &SDxState::g_pSSWrapLinear);
	g_pImmediateContext->OMSetDepthStencilState(SDxState::g_pDSSDepthEnable, 0);

	for (int iPlane = 0; iPlane < m_vPlaneList.size(); iPlane++)
	{
		SShapePlane* pPlane = m_vPlaneList[iPlane];
		pPlane->Render(g_pImmediateContext);
	}
	//for (auto data : m_vMatrixList)
	//{
	//	m_Plane.SetMatrix(&data, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	//	m_Plane.Render(g_pImmediateContext);
	//}
	return true;
}
bool Sample::Release()
{
	m_Plane.Release();
	return true;
}

SShapePlane* Sample::AddUI()
{
	SShapePlane* m_pPlane = new SShapePlane;
	m_pPlane->Create(g_pd3dDevice, L"../../data/shader/VS.txt",
		L"../../data/shader/PS.txt", L"../../data/tileA.jpg");

	m_vPlaneList.push_back(m_pPlane);

	return m_pPlane;
}
bool Sample::Update(POINT cursor)
{
	Matrix matProj = m_pMainCamera->m_matProj;
	Vector2 v;
	v.x = (((2.0f * cursor.x) / g_rtClient.right) - 1) / matProj._11;
	v.y = -(((2.0f * cursor.y) / g_rtClient.bottom) - 1) / matProj._22;
	//m_pPlane->m_vPos.x = v.x;
	//m_pPlane->m_vPos.y = v.y;

	m_matPlane._41 = m_Plane.m_vPos.x;
	m_matPlane._42 = m_Plane.m_vPos.y;

	Matrix matScale = Matrix::CreateScale(100, 100, 1);
	Matrix matrix;
	matrix = matScale * m_matPlane;
	g_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_Plane.SetMatrix(&matrix, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);


	return true;
}