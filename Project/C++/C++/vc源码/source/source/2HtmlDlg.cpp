// 2HtmlDlg.cpp : implementation file
//
#include "stdafx.h"
#include "flashnow.h"
#include "2HtmlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C2HtmlDlg dialog


C2HtmlDlg::C2HtmlDlg(CFlashWnd *pFlash,BOOL URLMode)
: CDialog(C2HtmlDlg::IDD, NULL),p_Flash(pFlash),m_URLMode(URLMode)
{
	m_TempFileName=GetTempFileName("htm");
	//{{AFX_DATA_INIT(C2HtmlDlg)
	m_Code = _T("");
	m_Title = _T("");
	//}}AFX_DATA_INIT
}


void C2HtmlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C2HtmlDlg)
	DDX_Text(pDX, IDC_HTML_CODE, m_Code);
	DDX_Text(pDX, IDC_HTML_TITLE, m_Title);
	DDX_Check(pDX, IDC_MOVIE_PATH, m_URLMode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C2HtmlDlg, CDialog)
//{{AFX_MSG_MAP(C2HtmlDlg)
ON_BN_CLICKED(ID_HTML_COPY, OnCopy)
ON_BN_CLICKED(IDC_MOVIE_PATH, OnMoviePath)
ON_EN_CHANGE(IDC_HTML_TITLE, OnChangeHtmlTitle)
ON_BN_CLICKED(ID_HTML_SAVE, OnSave)
ON_BN_CLICKED(ID_HTML_PREVIEW, OnPreview)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C2HtmlDlg message handlers

BOOL C2HtmlDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_Title=GetFileTitleFromFileName(::theApp.m_MovieURL);
	UpdateCode();
	return TRUE;
}

void C2HtmlDlg::OnCopy() 
{
	CEdit *pCode=(CEdit *)GetDlgItem(IDC_HTML_CODE);
	pCode->SetSel(0,-1);
	pCode->Copy();
}

void C2HtmlDlg::UpdateCode()
{
	CString Template;
	Template.LoadString(IDS_HTML_TEMPLATE);
	
	CTime Time;
	Time=CTime::GetCurrentTime();
	m_Code.Format
		(Template,
		Time.GetYear(),
		Time.GetMonth(),
		Time.GetDay(),
		Time.GetHour(),
		Time.GetMinute(),
		m_Title,
		m_URLMode?(::theApp.m_MovieURL):(GetFileTitleFromFileName(::theApp.m_MovieURL)),
		p_Flash->GetWMode(),
		p_Flash->GetLoop(),
		p_Flash->GetQuality2(),
		p_Flash->GetScale(),
		p_Flash->GetBGColor()
		);
	UpdateData(FALSE);
}

void C2HtmlDlg::OnMoviePath() 
{
	UpdateData(TRUE);
	UpdateCode();	
}

void C2HtmlDlg::OnChangeHtmlTitle() 
{
	UpdateData(TRUE);
	UpdateCode();	
}

void C2HtmlDlg::OnSave() 
{
	CFileDialog Dlg(FALSE,"htm",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"HTML网页文件(*.htm,*.html,*.asp)|*.htm;*.html;*.asp|所有文件(*.*)|*.*||",NULL);
	if(Dlg.DoModal()==IDOK)
	{
		SaveCodes(Dlg.GetPathName());
	}
}

void C2HtmlDlg::OnPreview() 
{
	SaveCodes(m_TempFileName);
	ShellExecute(NULL,"open",m_TempFileName,NULL,NULL,SW_SHOW);
}

void C2HtmlDlg::SaveCodes(CString FileName)
{
	UpdateData(TRUE);
	CFile File;
	File.Open(FileName,CFile::modeCreate|CFile::modeWrite);
	UpdateData(TRUE);
	File.Write(m_Code,m_Code.GetLength());
	File.Close();
}

C2HtmlDlg::~C2HtmlDlg()
{
	DeleteFile(m_TempFileName);
}
