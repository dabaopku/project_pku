// FileOpenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "flashnow.h"
#include "FileOpenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileOpenDlg

IMPLEMENT_DYNAMIC(CFileOpenDlg,CFileDialog)

CFileOpenDlg::CFileOpenDlg(BOOL bOpenFileDialog,LPCTSTR lpszDefExt,LPCTSTR lpszFileName,DWORD dwFlags,LPCTSTR lpszFilter,CWnd *pParentWnd)
: CFileDialog(bOpenFileDialog,lpszDefExt,lpszFileName,dwFlags,lpszFilter,pParentWnd)
{
	m_ofn.Flags|=(OFN_HIDEREADONLY|OFN_EXPLORER|OFN_ENABLETEMPLATE);
	m_ofn.Flags&=~OFN_ENABLESIZING;
	m_ofn.hInstance=AfxGetInstanceHandle();
	m_ofn.lpTemplateName=MAKEINTRESOURCE(IDD_FILE_OPEN);
	m_ofn.lpstrTitle="´ò¿ª";
	m_ofn.lpstrInitialDir=::theApp.m_Path;
	//{{AFX_DATA_INIT(CFileOpenDlg)
	m_Path=_T("");
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CFileOpenDlg,CDialog)
//{{AFX_MSG_MAP(CFileOpenDlg)
ON_WM_DESTROY()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CFileOpenDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CWnd *pWnd=GetDlgItem(IDC_PREVIEW_SCREEN);
	m_Container.Attach(pWnd->m_hWnd);
	
	if (m_Flash.Create(&m_Container)==-1)
		return -1;
	return FALSE;
}

void CFileOpenDlg::OnFileNameChange()
{
	UpdateData(TRUE);
	m_Path=GetPathName();
	m_Flash.SetMovie(m_Path);
	UpdateData(FALSE);
}

void CFileOpenDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileOpenDlg)
	DDX_Text(pDX,IDC_MOVIE_PATH,m_Path);
	//}}AFX_DATA_MAP
}

void CFileOpenDlg::OnDestroy() 
{
	m_Container.Detach();
	CDialog::OnDestroy();
}
