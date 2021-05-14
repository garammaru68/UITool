#include "pch.h"
#include "UIObject.h"

bool UIObject::Init()
{
	return true;
}
bool UIObject::Frame()
{
	return true;
}
bool UIObject::Render()
{
	return true;
}
bool UIObject::Release()
{
	return true;
}
//////////////////////////////////////////////////////////////////
bool UIObject::Update(Matrix matrixView, Matrix matrixProj, POINT cursor)
{
	Matrix matProj = matrixProj;
	Vector2 v;
	v.x = (((2.0f * cursor.x) / g_rtClient.right) - 1) / matProj._11;
	v.y = -(((2.0f * cursor.y) / g_rtClient.bottom) - 1) / matProj._22;
	m_PlaneUI.m_vPos.x = v.x;
	m_PlaneUI.m_vPos.y = v.y;

	m_matUI._41 = m_PlaneUI.m_vPos.x;
	m_matUI._42 = m_PlaneUI.m_vPos.y;

	Matrix matScale = Matrix::CreateScale(100, 100, 1);
	Matrix matrix;
	matrix = matScale * m_matUI;
	g_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_PlaneUI.SetMatrix(&matrix, &matrixView, &matrixProj);

	return true;
}
//SShapePlane* UIForm::CreateUIForm(Matrix matrixView, Matrix matrixProj, POINT cursor, STexture* texture)
//{
//	for (int parts = 0; parts < 9; parts++)
//	{
//		SShapePlane* pUI = new SShapePlane;
//		
//		pUI->Create(g_pd3dDevice, L"../../data/shader/VS.txt",
//			L"../../data/shader/PS.txt", L"../../data/tileA.jpg");
//		pUI->m_pTexture = texture;
//		Update(matrixView, matrixProj, cursor);
//
//		m_pUIFormList.push_back(pUI);
//	}
//}
