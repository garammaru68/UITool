// UIToolPane.cpp: 구현 파일
//

#include "pch.h"
#include "UITool.h"
#include "UIToolPane.h"


// UIToolPane

IMPLEMENT_DYNAMIC(UIToolPane, CDockablePane)

UIToolPane::UIToolPane()
{

}

UIToolPane::~UIToolPane()
{
}

BEGIN_MESSAGE_MAP(UIToolPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()

int UIToolPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_wndForm = UIToolForm::CreateOnce(this);
	return 0;
}


void UIToolPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	if (m_wndForm)
	{
		m_wndForm->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER);
	}
}


int UIToolPane::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	CFrameWnd* pParentFrame = GetParentFrame();
	if (pParentFrame == pDesktopWnd ||
		pDesktopWnd->IsChild(pParentFrame))
	{
		return CDockablePane::OnMouseActivate(pDesktopWnd, nHitTest, message);
	}

	return CDockablePane::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
