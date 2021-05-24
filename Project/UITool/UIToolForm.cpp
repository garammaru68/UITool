// UIToolForm.cpp: 구현 파일
//

#include "pch.h"
#include "UITool.h"
#include "UIToolForm.h"


// UIToolForm

IMPLEMENT_DYNCREATE(UIToolForm, CFormView)

UIToolForm* UIToolForm::CreateOnce(CWnd* pParent)
{
	UIToolForm* pForm = new UIToolForm;
	pForm->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 300, 400),
	pParent, 0, NULL);
	return pForm;
}

UIToolForm::UIToolForm()
	: CFormView(IDD_UIToolForm)
	, m_szTexture(_T(""))
	, m_fRectSize(0)
{
}
UIToolForm::~UIToolForm()
{
}

void UIToolForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_TextureList);
	DDX_Text(pDX, IDC_EDIT1, m_szTexture);
	DDX_Text(pDX, IDC_EDIT2, m_fRectSize);
	DDV_MinMaxFloat(pDX, m_fRectSize, 0, 1.0);
}

BEGIN_MESSAGE_MAP(UIToolForm, CFormView)
	ON_LBN_SELCHANGE(IDC_LIST1, &UIToolForm::TextureFileList)
	ON_BN_CLICKED(IDC_BUTTON2, &UIToolForm::SelectTextureOK)
	ON_BN_CLICKED(IDC_BUTTON3, &UIToolForm::DeleteTextureButton)
	ON_EN_CHANGE(IDC_EDIT2, &UIToolForm::RectScaleEdit)
	ON_BN_CLICKED(IDC_BUTTON4, &UIToolForm::SaveButton)
	ON_BN_CLICKED(IDC_BUTTON5, &UIToolForm::LoadButton)
END_MESSAGE_MAP()

void UIToolForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_TextureList.InsertString(0, L"main_start_nor.png");
	m_TextureList.InsertString(1, L"popup_normal.png");
	m_TextureList.InsertString(2, L"popup_box2.png");
	m_TextureList.InsertString(3, L"grass_2.jpg");
	m_TextureList.InsertString(4, L"002.jpg");
	m_TextureList.InsertString(5, L"flagstone.bmp");
	m_TextureList.InsertString(6, L"wal156S.bmp");
	m_TextureList.SetCurSel(0);

}

// UIToolForm 진단

#ifdef _DEBUG
void UIToolForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void UIToolForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

void UIToolForm::TextureFileList()
{
	int iSel = m_TextureList.GetCurSel();
	m_TextureList.GetText(iSel, m_szTexture);
	std::string name = CT2CA(m_szTexture);
	m_Texture = g_TexMgr.Load(g_pd3dDevice, to_mw(name).c_str());
	UpdateData(FALSE);
	CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();
	pApp->m_Sample.m_Texture = m_Texture;
}


void UIToolForm::SelectTextureOK()
{
	UpdateData(FALSE);
	CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();
	//pApp->m_Sample.m_Texture = m_Texture;
	pApp->m_Sample.m_pSelectUI->m_PlaneUI.m_pTexture = m_Texture;
	pApp->m_Sample.m_Texture = NULL;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void UIToolForm::DeleteTextureButton()
{
	UpdateData(FALSE);
	CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();
	pApp->m_Sample.Delete();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void UIToolForm::RectScaleEdit()
{
	UpdateData(TRUE);
	CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();
	pApp->m_Sample.m_fLeft = m_fRectSize;

	pApp->m_Sample.m_Texture = NULL;
}


void UIToolForm::SaveButton()
{
	CFileDialog dlg(
		FALSE,
		L"bmp",
		NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		L"bmp files(*.bmp)|*.bmp| All Files(*.*)|*.*|",
		this);
	if (dlg.DoModal() == IDOK)
	{
		CString filename;
		filename = dlg.GetPathName();
		AfxMessageBox(filename);
	}
}


void UIToolForm::LoadButton()
{
	CFileDialog dlg(
		TRUE,
		L"bmp",
		NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		L"bmp files(*.bmp)|*.bmp| All Files(*.*)|*.*|",
		this);
	if (dlg.DoModal() == IDOK)
	{
		CString filename;
		filename = dlg.GetPathName();
		filename += dlg.GetFileName();
		AfxMessageBox(filename);
	}
}
