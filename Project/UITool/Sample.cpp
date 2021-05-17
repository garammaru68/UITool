#include "pch.h"
#include "Sample.h"

bool Sample::Init()
{
	m_bRS = false;
	m_pSelectUI = NULL;
	bButtonState = false;
	//m_pSelectUI->m_vUIScale.x = 100;
	//m_pSelectUI->m_vUIScale.y = 100;

	return true;
}
bool Sample::Frame()
{
	POINT cursor;
	GetCursorPos(&cursor);
	ScreenToClient(g_hWnd, &cursor);

	UIObject*	pSelect = SelectUI();

	if (pSelect != NULL && m_pSelectUI != pSelect)
	{
		m_pSelectUI = pSelect;
	}

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

	//if (m_pSelectUI)
	//{
	//	Vector2 vUIPos;
	//	Vector2 vUIScale;
	//	// Move
	//	if (g_Input.GetKey('W') == KEY_HOLD)
	//	{
	//		vUIPos.y = 2.0f * g_fSecondPerFrame;
	//	}
	//	if (g_Input.GetKey('S') == KEY_HOLD)
	//	{
	//		vUIPos.y = -2.0f * g_fSecondPerFrame;
	//	}
	//	if (g_Input.GetKey('A') == KEY_HOLD)
	//	{
	//		vUIPos.x = -2.0f * g_fSecondPerFrame;
	//	}
	//	if (g_Input.GetKey('D') == KEY_HOLD)
	//	{
	//		vUIPos.x = 2.0f * g_fSecondPerFrame;
	//	}
	//	// Scale
	//	if (g_Input.GetKey('Q') == KEY_PUSH)
	//	{
	//		vUIScale.x += 2.0f * g_fSecondPerFrame;
	//	}
	//	m_pSelectUI->Move(vUIPos.x, vUIPos.y);
	//	m_pSelectUI->Scale(vUIScale.x, vUIScale.y);
	//}
	//m_pSelectUI->m_PlaneUI.m_cbData.vColor[0] = 255;
	//m_pSelectUI->m_PlaneUI.m_cbData.vColor[1] = 255;
	//m_pSelectUI->m_PlaneUI.m_cbData.vColor[2] = 255;

	return true;
}
bool Sample::Render()
{
	if (m_pSelectUI)
	{
		Vector2 vUIPos;
		Vector2 vUIScale;
		// Move
		if (g_Input.GetKey('W') == KEY_HOLD)
		{
			vUIPos.y = 1.0f * g_fSecondPerFrame;
		}
		if (g_Input.GetKey('S') == KEY_HOLD)
		{
			vUIPos.y = -1.0f * g_fSecondPerFrame;
		}
		if (g_Input.GetKey('A') == KEY_HOLD)
		{
			vUIPos.x = -1.0f * g_fSecondPerFrame;
		}
		if (g_Input.GetKey('D') == KEY_HOLD)
		{
			vUIPos.x = 1.0f * g_fSecondPerFrame;
		}
		// Scale
		if (g_Input.GetKey('Q') == KEY_HOLD)
		{
			vUIScale.x += 40.0f * g_fSecondPerFrame;
		}
		if (g_Input.GetKey('E') == KEY_HOLD)
		{
			vUIScale.x -= 40.0f * g_fSecondPerFrame;
		}
		if (g_Input.GetKey('Z') == KEY_HOLD)
		{
			vUIScale.y += 40.0f * g_fSecondPerFrame;
		}
		if (g_Input.GetKey('C') == KEY_HOLD)
		{
			vUIScale.y -= 40.0f * g_fSecondPerFrame;
		}
		//if (bButtonState == true)
		//{
			m_pSelectUI->Move(vUIPos.x, vUIPos.y);
			m_pSelectUI->Scale(vUIScale.x, vUIScale.y);
		//}

	}

	for (int iUI = 0; iUI < m_vUIList.size(); iUI++)
	{
		UIObject* pUI = m_vUIList[iUI];
		pUI->Update();
	}

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

	pUI->m_PlaneUI.m_matView = m_pMainCamera->m_matView;
	pUI->m_PlaneUI.m_matProj = m_pMainCamera->m_matProj;

	Matrix matProj = pUI->m_PlaneUI.m_matProj;
	Vector2 v;
	v.x = (((2.0f * cursor.x) / g_rtClient.right) - 1) / matProj._11;
	v.y = -(((2.0f * cursor.y) / g_rtClient.bottom) - 1) / matProj._22;
	pUI->m_PlaneUI.m_vPos.x = v.x;
	pUI->m_PlaneUI.m_vPos.y = v.y;
	pUI->m_PlaneUI.m_matWorld._41 = pUI->m_PlaneUI.m_vPos.x;
	pUI->m_PlaneUI.m_matWorld._42 = pUI->m_PlaneUI.m_vPos.y;

	pUI->m_vUIScale.x = 100.0f;
	pUI->m_vUIScale.y = 100.0f;

	pUI->m_rt.left = cursor.x - pUI->m_vUIScale.x / 2;
	pUI->m_rt.top = cursor.y - pUI->m_vUIScale.y / 2;
	pUI->m_rt.right = cursor.x + pUI->m_vUIScale.x / 2;
	pUI->m_rt.bottom = cursor.y + pUI->m_vUIScale.y / 2;

	//pUI->m_rt.left = cursor.x - ScaleX / 2;
	//pUI->m_rt.top = cursor.y - ScaleY / 2;
	//pUI->m_rt.right = cursor.x + ScaleX / 2;
	//pUI->m_rt.bottom = cursor.y + ScaleY / 2;

	pUI->Update();
	pUI->matUpdate();

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