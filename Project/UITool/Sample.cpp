#include "pch.h"
#include "Sample.h"

bool Sample::Init()
{
	m_bRS = false;
	m_pSelectUI = NULL;

	return true;
}
bool Sample::Frame()
{
	POINT cursor;
	GetCursorPos(&cursor);
	ScreenToClient(g_hWnd, &cursor);

	UIObject*	pSelect = SelectUI();;

	if (g_Input.GetKey(VK_LBUTTON) == KEY_PUSH)
	{	
		if (!m_Texture == NULL)
		{
			m_pSelectUI = CreateUI(cursor, m_Texture);
			m_Texture = NULL;
		};
	}
	if (g_Input.GetKey('1') == KEY_PUSH)
	{
		m_bRS = !m_bRS;
	}
	/////////// Select ///////////////
	if (pSelect != NULL && m_pSelectUI != pSelect)
	{
		m_pSelectUI = pSelect;
	}
	/////////// MOVE /////////////
	if (m_pSelectUI)
	{
		Vector2 vUIPos;
		if (g_Input.GetKey('W'))
		{
			vUIPos.y = 20.0f * g_fSecondPerFrame;
		}
		if (g_Input.GetKey('S') == KEY_PUSH)
		{
			vUIPos.y = -20.0f * g_fSecondPerFrame;
		}

		if (g_Input.GetKey('A') == KEY_PUSH)
		{
			vUIPos.x = -20.0f * g_fSecondPerFrame;
		}

		if (g_Input.GetKey('D') == KEY_PUSH)
		{
			vUIPos.x = 20.0f * g_fSecondPerFrame;
		}
		m_pSelectUI->Move(vUIPos.x, vUIPos.y);
	}

	for (int iUI = 0; iUI < m_vUIList.size(); iUI++)
	{
		UIObject* pUI = m_vUIList[iUI];
		pUI->Update();
		//pUI->matUpdate();
	}
	return true;
}
bool Sample::Render()
{
	if (m_bRS)
	{
		ApplyRS(g_pImmediateContext, SDxState::g_pRSWireFrame);
	}
	for (int iUI = 0; iUI < m_vUIList.size(); iUI++)
	{
		UIObject* pUI = m_vUIList[iUI];
		pUI->m_PlaneUI.m_cbData.vColor[0] = m_pMainCamera->m_vLook.x;
		pUI->m_PlaneUI.m_cbData.vColor[1] = m_pMainCamera->m_vLook.y;
		pUI->m_PlaneUI.m_cbData.vColor[2] = m_pMainCamera->m_vLook.z;
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
	return true;
}

UIObject* Sample::CreateUI(POINT cursor, STexture* texture)
{
	UIObject* pUI = new UIObject;
	pUI->m_PlaneUI.Create(g_pd3dDevice, L"../../data/shader/VS.txt",
		L"../../data/shader/PS.txt", L"../../data/tileA.jpg");
	pUI->m_PlaneUI.m_pTexture = texture;

	pUI->m_matUiView = m_pMainCamera->m_matView;
	pUI->m_matUiProj = m_pMainCamera->m_matProj;

	Matrix matProj = pUI->m_matUiProj;
	Vector2 v;
	v.x = (((2.0f * cursor.x) / g_rtClient.right) - 1) / matProj._11;
	v.y = -(((2.0f * cursor.y) / g_rtClient.bottom) - 1) / matProj._22;
	pUI->m_PlaneUI.m_vPos.x = v.x;
	pUI->m_PlaneUI.m_vPos.y = v.y;
	pUI->m_matUiWorld._41 = pUI->m_PlaneUI.m_vPos.x + pUI->m_vUIPos.x;
	pUI->m_matUiWorld._42 = pUI->m_PlaneUI.m_vPos.y + pUI->m_vUIPos.y;

	float ScaleX = 100;
	float ScaleY = 100;

	pUI->m_rt.left = cursor.x - ScaleX / 2;
	pUI->m_rt.top = cursor.y - ScaleY / 2;
	pUI->m_rt.right = cursor.x + ScaleX / 2;
	pUI->m_rt.bottom = cursor.y + ScaleY / 2;

	Matrix matScale = Matrix::CreateScale(ScaleX, ScaleY, 1);
	Matrix matrix;
	matrix = matScale * pUI->m_matUiWorld;
	g_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pUI->m_PlaneUI.SetMatrix(&matrix, &pUI->m_matUiView, &pUI->m_matUiProj);

	m_vUIList.push_back(pUI);

	return pUI;
}

UIObject* Sample::SelectUI()
{
	POINT cursor;
	GetCursorPos(&cursor);
	ScreenToClient(g_hWnd, &cursor);

	UIObject* pSelectUI = NULL;
	for (int select = 0; select < m_vUIList.size(); select++)
	{
		UIObject* pUI = m_vUIList[select];
		if (g_Input.GetKey(VK_LBUTTON) == KEY_PUSH && m_Texture == NULL)
		{
			if (cursor.x > pUI->m_rt.left &&
				cursor.x < pUI->m_rt.right)
			{
				if (cursor.y > pUI->m_rt.top &&
					 cursor.y < pUI->m_rt.bottom)
				{
					pSelectUI = pUI;
				}
			}
		}
	}
	return pSelectUI;
}