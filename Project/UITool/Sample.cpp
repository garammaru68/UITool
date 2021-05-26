#include "pch.h"
#include "Sample.h"

bool Sample::Init()
{
	m_bClickScaleRange = false;
	m_bRS = false;
	m_pSelectUI = NULL;
	sCursorPos.x = 0;
	sCursorPos.y = 0;
	eCursorPos.x = 0;
	eCursorPos.y = 0;
	v2.x = 0;
	v2.y = 0;

	return true;
}
bool Sample::Frame()
{
	//POINT cursor;
	//GetCursorPos(&cursor);
	//ScreenToClient(g_hWnd, &cursor);

	// UI 생성
	if (g_Input.GetKey(VK_LBUTTON) == KEY_PUSH)
	{
		UIObject* pSelect = SelectUI();

		// 선택이 바뀌는 과정에서 중복 가능성
		//if (pSelect != NULL)
		if (pSelect != NULL && m_pSelectUI != pSelect)
		{
			m_pSelectUI = pSelect;
		}
		if (m_Texture != NULL)
		{
			m_vDownPos = ClickDown();
			//m_pSelectUI = CreateUI(cursor, m_Texture);
			//m_Texture = NULL;
		};
	}
	if (g_Input.GetKey(VK_LBUTTON) == KEY_UP)
	{
		if (m_Texture != NULL)
		{
			m_vUpPos = ClickUp();

			Vector2 RectScale;
			// 크기 설정 일단 보류
			//RectScale = (m_vUpPos - m_vDownPos) / 3;
			RectScale.x = (m_vUpPos.x - m_vDownPos.x) / 2.2;
			RectScale.y = (m_vUpPos.y - m_vDownPos.y) / 2.1;
			//RectScale.x = (m_vUpPos.x - m_vDownPos.x) / 4.35;
			//RectScale.y = (m_vUpPos.y - m_vDownPos.y) / 3.15;

			if (RectScale.x < 0)
			{
				(RectScale.x) * (-1.0f);
			}
			if (RectScale.y < 0)
			{
				(RectScale.y) * (-1.0f);
			}
			//RectScale.x = m_vUpPos.x - m_vDownPos.x;
			//RectScale.y = m_vUpPos.y - m_vDownPos.y;
			m_pSelectUI = CreateUI(RectScale, m_Texture);
			m_Texture = NULL;
		};
	}
	// UI 삭제
	if (g_Input.GetKey(VK_DELETE) == KEY_PUSH)
	{
		if (m_pSelectUI)
		{
			Delete();
		}
	}
	// 마우스 UI 이동 & 마우스 UI 크기
	if (m_pSelectUI)
	{
		// 마우스 UI 이동
		if (g_Input.GetKey(VK_LBUTTON) == KEY_PUSH)
		{
			Matrix matProj = m_pSelectUI->m_PlaneUI.m_matProj;
			vUiPos = ClickDown();
			vUiPos.x = (((2.0f * vUiPos.x) / g_rtClient.right) - 1) / matProj._11;
			vUiPos.y = -(((2.0f * vUiPos.y) / g_rtClient.bottom) - 1) / matProj._22;
			vUiPos.x = m_pSelectUI->m_PlaneUI.m_vPos.x - vUiPos.x;
			vUiPos.y = m_pSelectUI->m_PlaneUI.m_vPos.y - vUiPos.y;
		}
		if (g_Input.GetKey(VK_LBUTTON) == KEY_HOLD && m_bClickScaleRange == false)
		{
			//Matrix matProj = m_pSelectUI->m_PlaneUI.m_matProj;
			//vUiPos = ClickDown();
			//vUiPos.x = (((2.0f * vUiPos.x) / g_rtClient.right) - 1) / matProj._11;
			//vUiPos.y = -(((2.0f * vUiPos.y) / g_rtClient.bottom) - 1) / matProj._22;
			//vUiPos.x = m_pSelectUI->m_PlaneUI.m_vPos.x - vUiPos.x;
			//vUiPos.y = m_pSelectUI->m_PlaneUI.m_vPos.y - vUiPos.y;

			Vector2 ptDown = ClickDown();
			Matrix matProj = m_pSelectUI->m_PlaneUI.m_matProj;
			v2.x = (((2.0f * ptDown.x) / g_rtClient.right) - 1) / matProj._11;
			v2.y = -(((2.0f * ptDown.y) / g_rtClient.bottom) - 1) / matProj._22;

			m_pSelectUI->m_rt.left = m_pSelectUI->m_PlaneUI.m_vPos.x - m_pSelectUI->m_vUIScale.x;
			m_pSelectUI->m_rt.top = m_pSelectUI->m_PlaneUI.m_vPos.y - m_pSelectUI->m_vUIScale.y;
			m_pSelectUI->m_rt.right = m_pSelectUI->m_PlaneUI.m_vPos.x + m_pSelectUI->m_vUIScale.x;
			m_pSelectUI->m_rt.bottom = m_pSelectUI->m_PlaneUI.m_vPos.y + m_pSelectUI->m_vUIScale.y;

			if (v2.x > m_pSelectUI->m_rt.left + 10 &&
				v2.x < m_pSelectUI->m_rt.right - 10 &&
				v2.y > m_pSelectUI->m_rt.top + 10 &&
				v2.y < m_pSelectUI->m_rt.bottom - 10)
			{
				POINT cursor;
				GetCursorPos(&cursor);
				ScreenToClient(g_hWnd, &cursor);

				Matrix matProj = m_pSelectUI->m_PlaneUI.m_matProj;
				Vector2 v1;
				v1.x = (((2.0f * cursor.x) / g_rtClient.right) - 1) / matProj._11;
				v1.y = -(((2.0f * cursor.y) / g_rtClient.bottom) - 1) / matProj._22;

				m_pSelectUI->m_PlaneUI.m_vPos.x = v1.x + vUiPos.x;
				m_pSelectUI->m_PlaneUI.m_vPos.y = v1.y + vUiPos.y;
				m_pSelectUI->m_PlaneUI.m_matWorld._41 = m_pSelectUI->m_PlaneUI.m_vPos.x;
				m_pSelectUI->m_PlaneUI.m_matWorld._42 = m_pSelectUI->m_PlaneUI.m_vPos.y;

			}
		}
		// 사용여부 확인
		//if (g_Input.GetKey(VK_LBUTTON) == KEY_UP)
		//{
		//	vUiPos.x = 0;
		//	vUiPos.y = 0;
		//}

		// 마우스 UI 크기
		//if (g_Input.GetKey(VK_LBUTTON) == KEY_PUSH)
		//{
		//	POINT ptCheck;
		//	GetCursorPos(&ptCheck);
		//	ScreenToClient(g_hWnd, &ptCheck);

		//	Matrix matProj = m_pSelectUI->m_PlaneUI.m_matProj;
		//	ptCheck.x = (((2.0f * ptCheck.x) / g_rtClient.right) - 1) / matProj._11;
		//	ptCheck.y = -(((2.0f * ptCheck.y) / g_rtClient.bottom) - 1) / matProj._22;
		//}
		//if (g_Input.GetKey(VK_LBUTTON) == KEY_UP)
		//{
		//	m_vUpScale = ClickUp();
		//}

		//if (m_pSelectUI->m_rt.left < m_vDownScale.x &&
		//	m_pSelectUI->m_rt.left + 10 > m_vDownScale.x &&
		//	m_pSelectUI->m_rt.top + 10 < m_vDownScale.y &&
		//	m_pSelectUI->m_rt.bottom - 10 > m_vDownScale.y)
		//{
		//	if (g_Input.GetKey(VK_LBUTTON) == KEY_PUSH)
		//	{
		//		m_vDownScale = ClickDown();

		//		Matrix matProj = m_pSelectUI->m_PlaneUI.m_matProj;
		//		m_vUiScale.x = (((2.0f * m_vUiScale.x) / g_rtClient.right) - 1) / matProj._11;
		//		m_vUiScale.y = -(((2.0f * m_vUiScale.y) / g_rtClient.bottom) - 1) / matProj._22;
		//	}
		//	m_pSelectUI->m_matWorld._11 = m_pSelectUI->m_matWorld._11 + m_vUiScale.x;
		//	m_pSelectUI->m_matWorld._22 = m_pSelectUI->m_matWorld._22 + m_vUiScale.y;
		//}
		/////////////////////////////////////////////
		if (g_Input.GetKey('F') == KEY_PUSH/* && m_Texture == NULL*/)
		{
			m_pSelectUI->m_PlaneUI.m_pTexture = m_Texture;
			m_Texture = NULL;
			m_ChangeTexture = NULL;
		}
	}

	// 와이어 프레임
	if (g_Input.GetKey('0') == KEY_PUSH)
	{
		m_bRS = !m_bRS;
	}

	if (m_pSelectUI)
	{
		// Move
		//Vector2	vUIPos;
		//POINT		UIPosMouse = { 0, 0 };
		//if (g_Input.GetKey('W') == KEY_HOLD)
		//{
		//	vUIPos.y = 1.0f * m_pSelectUI->m_PlaneUI.m_fSpeed * g_fSecondPerFrame;
		//	//vUIPos.y = 1.0f * g_fSecondPerFrame;
		//}
		//if (g_Input.GetKey('S') == KEY_HOLD)
		//{
		//	vUIPos.y = -100.0f * g_fSecondPerFrame;
		//}
		//if (g_Input.GetKey('A') == KEY_HOLD)
		//{
		//	vUIPos.x = -100.0f * g_fSecondPerFrame;
		//}
		//if (g_Input.GetKey('D') == KEY_HOLD)
		//{
		//	vUIPos.x = 100.0f * g_fSecondPerFrame;
		//}
		//m_pSelectUI->Move(vUIPos.x + UIPosMouse.x, vUIPos.y + UIPosMouse.y);

		// Scale
		// rt.left,top,right,bottom을 마우스 위치에 맞춘다

		// 마우스로 크기 조절
		Vector2 vUIScale;
		
		if (g_Input.GetKey(VK_LBUTTON) == KEY_PUSH)
		{
			GetCursorPos(&m_ptDown);
			ScreenToClient(g_hWnd, &m_ptDown);

			GetCursorPos(&m_ptDownScale);
			ScreenToClient(g_hWnd, &m_ptDownScale);

			Matrix matProj = m_pSelectUI->m_PlaneUI.m_matProj;
			m_ptDownScale.x = (((2.0f * m_ptDownScale.x) / g_rtClient.right) - 1) / matProj._11;
			m_ptDownScale.y = -(((2.0f * m_ptDownScale.y) / g_rtClient.bottom) - 1) / matProj._22;
			GetCursorPos(&m_ptDownScale);
			ScreenToClient(g_hWnd, &m_ptDownScale);
		}
		if (g_Input.GetKey(VK_LBUTTON) == KEY_UP)
		{
			m_bClickScaleRange = false;
		}
		// rt1
		if (m_pSelectUI->m_rt.left < m_ptDownScale.x &&
			m_pSelectUI->m_rt.left + 10 > m_ptDownScale.x &&
			m_pSelectUI->m_rt.top < m_ptDownScale.y &&
			m_pSelectUI->m_rt.top + 10 > m_ptDownScale.y)
		{
			
		}
		//rt4
		if (g_Input.GetKey(VK_LBUTTON) == KEY_HOLD)
		{
			m_pSelectUI->m_rt.left = m_pSelectUI->m_PlaneUI.m_vPos.x + m_pSelectUI->m_vUIPos.x - m_pSelectUI->m_vUIScale.x;
			m_pSelectUI->m_rt.top = m_pSelectUI->m_PlaneUI.m_vPos.y + m_pSelectUI->m_vUIPos.y - m_pSelectUI->m_vUIScale.y;
			m_pSelectUI->m_rt.right = m_pSelectUI->m_PlaneUI.m_vPos.x + m_pSelectUI->m_vUIPos.x + m_pSelectUI->m_vUIScale.x;
			m_pSelectUI->m_rt.bottom = m_pSelectUI->m_PlaneUI.m_vPos.y + m_pSelectUI->m_vUIPos.y + m_pSelectUI->m_vUIScale.y;

			POINT ptHold;
			GetCursorPos(&ptHold);
			ScreenToClient(g_hWnd, &ptHold);

			//if (m_pSelectUI->m_rt.left < ptHold.x &&
			//	m_pSelectUI->m_rt.left + 10 > ptHold.x &&
			//	m_pSelectUI->m_rt.top + 10 < ptHold.y &&
			//	m_pSelectUI->m_rt.bottom - 10 > ptHold.y)
			if (m_pSelectUI->m_rt.left < m_ptDownScale.x &&
				m_pSelectUI->m_rt.left + 10 > m_ptDownScale.x &&
				m_pSelectUI->m_rt.top + 10 < m_ptDownScale.y &&
				m_pSelectUI->m_rt.bottom - 10 > m_ptDownScale.y)
			{
				m_bClickScaleRange = true;

				POINT ptCursor;
				GetCursorPos(&ptCursor);
				ScreenToClient(g_hWnd, &ptCursor);

				vUIScale.x += m_ptDown.x - ptCursor.x;
				//vUIScale.x += m_ptDown.x - ptHold.x;

				m_pSelectUI->m_PlaneUI.m_matWorld._11 = m_pSelectUI->m_vUIScale.x + vUIScale.x;
				m_pSelectUI->m_PlaneUI.m_matWorld._22 = m_pSelectUI->m_vUIScale.y + vUIScale.y;
				//vUIScale.x += 40.0f * g_fSecondPerFrame;

			}
		}
		// 키보드로 크기 조절
		if (g_Input.GetKey('Q') == KEY_HOLD)
		{
			vUIScale.x += 40.0f * g_fSecondPerFrame;
			m_pSelectUI->m_PlaneUI.m_vPos.x += vUIScale.x;
			m_pSelectUI->m_PlaneUI.m_matWorld._41 = m_pSelectUI->m_PlaneUI.m_vPos.x;
		}
		if (g_Input.GetKey('W') == KEY_HOLD)
		{
			vUIScale.x -= 40.0f * g_fSecondPerFrame;
			m_pSelectUI->m_PlaneUI.m_vPos.x += vUIScale.x;
			m_pSelectUI->m_PlaneUI.m_matWorld._41 = m_pSelectUI->m_PlaneUI.m_vPos.x;
		}
		if (g_Input.GetKey('E') == KEY_HOLD)
		{
			vUIScale.x += 40.0f * g_fSecondPerFrame;
			m_pSelectUI->m_PlaneUI.m_vPos.x -= vUIScale.x;
			m_pSelectUI->m_PlaneUI.m_matWorld._41 = m_pSelectUI->m_PlaneUI.m_vPos.x;
		}
		if (g_Input.GetKey('R') == KEY_HOLD)
		{
			vUIScale.x -= 40.0f * g_fSecondPerFrame;
			m_pSelectUI->m_PlaneUI.m_vPos.x -= vUIScale.x;
			m_pSelectUI->m_PlaneUI.m_matWorld._41 = m_pSelectUI->m_PlaneUI.m_vPos.x;
		}
		if (g_Input.GetKey('A') == KEY_HOLD)
		{
			vUIScale.y += 40.0f * g_fSecondPerFrame;
			m_pSelectUI->m_PlaneUI.m_vPos.y += vUIScale.y;
			m_pSelectUI->m_PlaneUI.m_matWorld._42 = m_pSelectUI->m_PlaneUI.m_vPos.y;
		}
		if (g_Input.GetKey('S') == KEY_HOLD)
		{
			vUIScale.y -= 40.0f * g_fSecondPerFrame;
			m_pSelectUI->m_PlaneUI.m_vPos.y += vUIScale.y;
			m_pSelectUI->m_PlaneUI.m_matWorld._42 = m_pSelectUI->m_PlaneUI.m_vPos.y;
		}
		if (g_Input.GetKey('D') == KEY_HOLD)
		{
			vUIScale.y += 40.0f * g_fSecondPerFrame;
			m_pSelectUI->m_PlaneUI.m_vPos.y -= vUIScale.y;
			m_pSelectUI->m_PlaneUI.m_matWorld._42 = m_pSelectUI->m_PlaneUI.m_vPos.y;
		}
		if (g_Input.GetKey('F') == KEY_HOLD)
		{
			vUIScale.y -= 40.0f * g_fSecondPerFrame;
			m_pSelectUI->m_PlaneUI.m_vPos.y -= vUIScale.y;
			m_pSelectUI->m_PlaneUI.m_matWorld._42 = m_pSelectUI->m_PlaneUI.m_vPos.y;
		}
		//m_pSelectUI->MouseScale(vUIScale.x, vUIScale.y);
		m_pSelectUI->Scale(vUIScale.x, vUIScale.y);
	}

	for (int iUI = 0; iUI < m_vUIList.size(); iUI++)
	{
		UIObject* pUI = m_vUIList[iUI];
		pUI->UpdateSRT();
	}

	return true;
}
bool Sample::Render()
{
	DX::ApplyBS(g_pImmediateContext, DX::SDxState::g_pAlphaBlend);

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
		if (m_pSelectUI)
		{
			m_pSelectUI->m_PlaneUI.m_cbData.vColor[0] = 0.5f;
			m_pSelectUI->m_PlaneUI.m_cbData.vColor[1] = 0.5f;
			m_pSelectUI->m_PlaneUI.m_cbData.vColor[2] = 0.5f;
		}
		if (pUI)
		{
			pUI->m_PlaneUI.Render(g_pImmediateContext);
		}
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
bool Sample::Delete()
{
	for(int iUI = 0; iUI < m_vUIList.size(); iUI++)
	{
		if (m_pSelectUI == m_vUIList[iUI])
		{
			m_vUIList.erase(m_vUIList.begin() + (iUI));
		}
	}
	return true;
}

UIObject* Sample::CreateUI(Vector2 uiScale, STexture* texture)
{
	UIObject* pUI = new UIObject;
	pUI->SetData(m_fLeft);
	pUI->m_PlaneUI.Create(g_pd3dDevice, L"../../data/shader/VS.txt",
		L"../../data/shader/PS.txt", L"../../data/tileA.jpg");
	pUI->m_PlaneUI.m_pTexture = texture;

	pUI->m_PlaneUI.m_matView = m_pMainCamera->m_matView;
	pUI->m_PlaneUI.m_matProj = m_pMainCamera->m_matProj;

	Matrix matProj = pUI->m_PlaneUI.m_matProj;
	Vector2 v;
	v.x = (((2.0f * m_vUpPos.x) / g_rtClient.right) - 1) / matProj._11;
	v.y = -(((2.0f * m_vUpPos.y) / g_rtClient.bottom) - 1) / matProj._22;

	pUI->m_PlaneUI.m_vPos.x = v.x - uiScale.x;
	pUI->m_PlaneUI.m_vPos.y = v.y + uiScale.y;
	pUI->m_PlaneUI.m_matWorld._41 = pUI->m_PlaneUI.m_vPos.x;
	pUI->m_PlaneUI.m_matWorld._42 = pUI->m_PlaneUI.m_vPos.y;

	pUI->m_vUIScale.x = uiScale.x;
	pUI->m_vUIScale.y = uiScale.y;

	pUI->UpdateSRT();
	pUI->UpdateMat();

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
		if (g_Input.GetKey(VK_LBUTTON) == KEY_PUSH && m_Texture == NULL)
		{
			POINT SelPoint = cursor;
			Matrix matProj = pUI->m_PlaneUI.m_matProj;

			SelPoint.x = (((2.0f * SelPoint.x) / g_rtClient.right) - 1) / matProj._11;
			SelPoint.y = -(((2.0f * SelPoint.y) / g_rtClient.bottom) - 1) / matProj._22;

			pUI->m_rt.left = pUI->m_PlaneUI.m_vPos.x + pUI->m_vUIPos.x - pUI->m_vUIScale.x;
			pUI->m_rt.top = pUI->m_PlaneUI.m_vPos.y + pUI->m_vUIPos.y - pUI->m_vUIScale.y;
			pUI->m_rt.right = pUI->m_PlaneUI.m_vPos.x + pUI->m_vUIPos.x + pUI->m_vUIScale.x;
			pUI->m_rt.bottom = pUI->m_PlaneUI.m_vPos.y + pUI->m_vUIPos.y + pUI->m_vUIScale.y;

			if (SelPoint.x > pUI->m_rt.left && SelPoint.x < pUI->m_rt.right &&
				SelPoint.y > pUI->m_rt.top && SelPoint.y < pUI->m_rt.bottom)
			{
				pUI->m_PlaneUI.m_vPos.z = Depth;
				pUI->m_PlaneUI.m_matWorld._43 = pUI->m_PlaneUI.m_vPos.z;
				Depth += 0.1f;

				pSelectUiList.push_back(pUI);
			}
		}
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
Vector2 Sample::ClickDown()
{
	POINT cursor;
	GetCursorPos(&cursor);
	ScreenToClient(g_hWnd, &cursor);

	//Matrix matProj;// = m_pSelectUI->m_PlaneUI.m_matProj;
	//matProj = m_pSelectUI->m_PlaneUI.m_matProj;
	Vector2 sCursor;
	//sCursor.x = (((2.0f * cursor.x) / g_rtClient.right) - 1) / matProj._11;
	//sCursor.y = -(((2.0f * cursor.y) / g_rtClient.bottom) - 1) / matProj._22;
	sCursor.x = cursor.x;
	sCursor.y = cursor.y;
	return sCursor;
}
Vector2 Sample::ClickUp()
{
	POINT cursor;
	GetCursorPos(&cursor);
	ScreenToClient(g_hWnd, &cursor);

	//Matrix matProj;// = m_pSelectUI->m_PlaneUI.m_matProj;
	//matProj = m_pSelectUI->m_PlaneUI.m_matProj;

	Vector2 eCursor;
	//eCursor.x = (((2.0f * cursor.x) / g_rtClient.right) - 1) / matProj._11;
	//eCursor.y = -(((2.0f * cursor.y) / g_rtClient.bottom) - 1) / matProj._22;
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
Sample::Sample(void)
{
	m_pSelectUI = NULL;
}
Sample::~Sample(void)
{

}
// 도형 삽입, 삭제, 컬러 변경, 텍스쳐 변경, 충돌 처리,
// 클릭 홀드시 겹친부분 처리
// 9개의 사각형중 중앙에만 이미지 출력하고, 나머지 테투리 사각형 8개는 이미지 크기 작업을 위해 남겨둔다

// 삭제, 이미지 크기 조절, 텍스쳐 변경