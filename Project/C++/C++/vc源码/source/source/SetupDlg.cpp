// SetUpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "flashnow.h"
#include "ViewerFrame.h"
#include "SetUpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog


CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
: CDialog(CSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupDlg)
	//}}AFX_DATA_INIT
	m_DoubleClick=::theApp.m_UserData.m_DoubleClick;
	m_Loop=::theApp.m_UserData.m_Loop;
	m_SlideShow=::theApp.m_UserData.m_SlideShow;
	m_URLMode=::theApp.m_UserData.m_URLMode;
	m_Elapse=::theApp.m_UserData.m_Elapse;
	m_ShowAbout=::theApp.m_UserData.m_ShowAbout;
}


void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupDlg)
	DDX_Control(pDX, IDC_URL_LIST, m_URLList);
	DDX_Control(pDX, IDC_CLEAR_ALL, m_ClearAll);
	DDX_Control(pDX, IDC_DELETE_ITEM, m_DeleteItem);
	DDX_Check(pDX, IDC_DOUBLECLICK_ENABLE, m_DoubleClick);
	DDX_Check(pDX, IDC_MOVIE_LOOP, m_Loop);
	DDX_Check(pDX, IDC_MOVIE_PATH, m_URLMode);
	DDX_Check(pDX, IDC_SLIDE_SHOW, m_SlideShow);
	DDX_Check(pDX, IDC_SHOW_ABOUT, m_ShowAbout);
	DDX_Text(pDX, IDC_ELAPSE, m_Elapse);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
//{{AFX_MSG_MAP(CSetupDlg)
ON_LBN_SELCHANGE(IDC_URL_LIST, OnSelChangeUrlList)
ON_BN_CLICKED(IDC_DELETE_ITEM, OnDeleteItem)
ON_BN_CLICKED(IDC_CLEAR_ALL, OnClearAll)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg message handlers

void CSetupDlg::OnOK() 
{
	UpdateData(TRUE);
	
	::theApp.m_UserData.m_DoubleClick=m_DoubleClick;
	::theApp.m_UserData.m_Loop=m_Loop;
	::theApp.m_UserData.m_SlideShow=m_SlideShow;
	::theApp.m_UserData.m_URLMode=m_URLMode;
	::theApp.m_UserData.m_Elapse=m_Elapse;
	::theApp.m_UserData.m_ShowAbout=m_ShowAbout;
	
	CString Item;
	
	CComboBox *pList=&(::theApp.p_Viewer->m_DlgBar.m_List);
	
	pList->ResetContent();
	for(int i=0;i<m_URLList.GetCount();i++)
	{
		m_URLList.GetText(i,Item);
		pList->InsertString(i,Item);
	}
	pList->SetCurSel(0);
	
	CDialog::OnOK();
}

BOOL CSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString Item;
	CComboBox *pList=&(::theApp.p_Viewer->m_DlgBar.m_List);
	
	for(int i=0;i<pList->GetCount();i++)
	{
		pList->GetLBText(i,Item);
		m_URLList.InsertString(i,Item);
	}
	
	m_DeleteItem.EnableWindow(FALSE);
	m_ClearAll.EnableWindow(m_URLList.GetCount());
	
	return TRUE;
}

void CSetupDlg::OnSelChangeUrlList() 
{
	m_DeleteItem.EnableWindow(m_URLList.GetCurSel()!=-1);
}

void CSetupDlg::OnDeleteItem() 
{
	int Selected=m_URLList.GetCurSel();
	int Total=m_URLList.DeleteString(Selected);
	m_ClearAll.EnableWindow(Total);
	if(Selected<Total)
		m_URLList.SetCurSel(Selected);
	else
		m_DeleteItem.EnableWindow(FALSE);
}

void CSetupDlg::OnClearAll() 
{
	m_URLList.ResetContent();
	m_DeleteItem.EnableWindow(FALSE);
	m_ClearAll.EnableWindow(FALSE);	
}
