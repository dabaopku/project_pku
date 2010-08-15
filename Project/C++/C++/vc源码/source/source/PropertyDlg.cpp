// PropertyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "flashnow.h"
#include "ViewerClient.h"
#include "PropertyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyDlg dialog


CPropertyDlg::CPropertyDlg(int Frames)
: CDialog(CPropertyDlg::IDD, NULL),m_Frames(Frames)
{
	//{{AFX_DATA_INIT(CPropertyDlg)
	m_CreateTime = _T("");
	m_FileName = _T("");
	m_FileSize = _T("");
	m_ModifyTime = _T("");
	m_TotalFrame = _T("");
	//}}AFX_DATA_INIT
}


void CPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyDlg)
	DDX_Text(pDX, IDC_CREATETIME, m_CreateTime);
	DDX_Text(pDX, IDC_FILENAME, m_FileName);
	DDX_Text(pDX, IDC_FILESIZE, m_FileSize);
	DDX_Text(pDX, IDC_MODIFYTIME, m_ModifyTime);
	DDX_Text(pDX, IDC_TOTALFRAMES, m_TotalFrame);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropertyDlg, CDialog)
//{{AFX_MSG_MAP(CPropertyDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyDlg message handlers

BOOL CPropertyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString Text;
	CFileStatus Status;
	if(CFile::GetStatus(::theApp.m_MovieURL,Status))
	{
	CTime Time;
	Time=Status.m_ctime;
	m_CreateTime.Format("%04d-%02d-%02d %02d:%02d",Time.GetYear(),Time.GetMonth(),Time.GetDay(),Time.GetHour(),Time.GetMinute());
	Time=Status.m_mtime;
	m_ModifyTime.Format("%04d-%02d-%02d %02d:%02d",Time.GetYear(),Time.GetMonth(),Time.GetDay(),Time.GetHour(),Time.GetMinute());
	m_FileSize.Format("%dKB",(Status.m_size+1023)/1024);
	m_FileName=Status.m_szFullName;
	}
	else
	{
	m_CreateTime="(未知时间)";
	m_ModifyTime="(未知时间)";
	m_FileSize="(未知大小)";
	m_FileName=::theApp.m_MovieURL;
	}
	m_TotalFrame.Format("%d",m_Frames);
	
	UpdateData(FALSE);
	return TRUE;
}
