#pragma once

#include "UIToolForm.h"

class UIToolPane : public CDockablePane
{
	DECLARE_DYNAMIC(UIToolPane)
public:
	UIToolForm*		m_wndForm;

	UIToolPane();
	virtual ~UIToolPane();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


