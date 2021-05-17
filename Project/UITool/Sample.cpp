#include "pch.h"
#include "Sample.h"

bool Sample::Init()
{
	m_bRS = false;
	m_pSelectUI = NULL;
	sCursorPos.x = 0;
	sCursorPos.y = 0;
	eCursorPos.x = 0;
	eCursorPos.y = 0;
	m_bClickState = false;
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

	//if (pSelect != NULL)
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

	if (m_pSelectUI)
	{
		// Move
		Vector2	vUIPos;
		POINT		UIPosMouse = { 0, 0 };
		if (g_Input.GetKey('W') == KEY_HOLD)
		{
			vUIPos.y = 1.0f * m_pSelectUI->m_PlaneUI.m_fSpeed * g_fSecondPerFrame;
			//vUIPos.y = 1.0f * g_fSecondPerFrame;
		}
		if (g_Input.GetKey('S') == KEY_HOLD)
		{
			vUIPos.y = -100.0f * g_fSecondPerFrame;
		}
		if (g_Input.GetKey('A') == KEY_HOLD)
		{
			vUIPos.x = -100.0f * g_fSecondPerFrame;
		}
		if (g_Input.GetKey('D') == KEY_HOLD)
		{
			vUIPos.x = 100.0f * g_fSecondPerFrame;
		}
		/////// 텍스쳐 마우스 이동 ///////
		//if (g_Input.GetKey(VK_LBUTTON) == KEY_PUSH)
		//{
		//	sCursorPos = ClickDown();
		//}
		//if (g_Input.GetKey(VK_LBUTTON) == KEY_UP)
		//{
		//	eCursorPos = ClickUp();
		//}
		if (MoveDistance().x != NULL || MoveDistance().y != NULL )
		{
			if (m_bClickState == false)
			{
				UIPosMouse = MoveDistance();
				sCursorPos.x = 0;
				sCursorPos.y = 0;
				eCursorPos.x = 0;
				eCursorPos.y = 0;
			}
			//MoveDistance().x = 0.0f;
		}
		// Scale
		Vector2 vUIScale;
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
		m_pSelectUI->Move(vUIPos.x + UIPosMouse.x , vUIPos.y + UIPosMouse.y);
		m_pSelectUI->Scale(vUIScale.x, vUIScale.y);
	}

	for (int iUI = 0; iUI < m_vUIList.size(); iUI++)
	{
		UIObject* pUI = m_vUIList[iUI];
		pUI->Update();
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

	float Depth = 0.1f;

	vector<UIObject*> pSelectUiList;
	//UIObject* pSelectUI = NULL;
	for (int select = 0; select < m_vUIList.size(); select++)
	{
		UIObject* pUI = m_vUIList[select];
		if (g_Input.GetKey(VK_LBUTTON) == KEY_HOLD && m_Texture == NULL)
		{
			POINT SelPoint = cursor;
			
			if (SelPoint.x > pUI->m_rt.left && SelPoint.x < pUI->m_rt.right &&
				SelPoint.y > pUI->m_rt.top && SelPoint.y < pUI->m_rt.bottom)
			{
				// fix - m_rt가 안변함
				m_bClickState = true;
				sCursorPos = ClickDown();

				pUI->m_PlaneUI.m_vPos.z = Depth;
				pUI->m_PlaneUI.m_matWorld._43 = pUI->m_PlaneUI.m_vPos.z;
				Depth += 0.1f;

				pSelectUiList.push_back(pUI);
				//pSelectUI = pUI;
			}
		}
		if (g_Input.GetKey(VK_LBUTTON) == KEY_UP && m_bClickState)
		{
			eCursorPos = ClickUp();
			m_bClickState = false;
		}
		MoveDistance();
	}
	// 겹친부분 처리
	UIObject* pSelect = NULL;
	if (pSelectUiList.size() != 0)
	{
		pSelect = pSelectUiList[0];
		for (int select = 1; select < pSelectUiList.size(); select++)
		{
			if (pSelect->m_PlaneUI.m_vPos.z > pSelectUiList[select]->m_PlaneUI.m_vPos.z)
			{
				pSelect = pSelectUiList[select];
			}
		}
	}
	return pSelect;
}
POINT Sample::ClickDown()
{
	POINT cursor;
	GetCursorPos(&cursor);
	ScreenToClient(g_hWnd, &cursor);

	POINT sCursor;
	sCursor.x = cursor.x;
	sCursor.y = cursor.y;

	return sCursor;
}
POINT Sample::ClickUp()
{
	POINT cursor;
	GetCursorPos(&cursor);
	ScreenToClient(g_hWnd, &cursor);

	POINT eCursor;
	eCursor.x = cursor.x;
	eCursor.y = cursor.y;

	return eCursor;

}
POINT Sample::MoveDistance()
{
	POINT FinalDistance;
	FinalDistance.x = eCursorPos.x - sCursorPos.x;
	FinalDistance.y = -(eCursorPos.y - sCursorPos.y);

	return FinalDistance;
}