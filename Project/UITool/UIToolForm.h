#pragma once



// UIToolForm 폼 보기
//STexture*		m_Texture;

class UIToolForm : public CFormView
{
	DECLARE_DYNCREATE(UIToolForm)
public:
	static UIToolForm* CreateOnce(CWnd* pParent);
	STexture*		m_Texture;
protected:
	UIToolForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~UIToolForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UIToolForm };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_szTexture;
	CListBox m_TextureList;
	afx_msg void TextureFileList();
	afx_msg void SelectTextureOK();
	virtual void OnInitialUpdate();
};


