// ViewLogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FakeQQ.h"
#include "ViewLogDlg.h"
#include "ChatRecordSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewLogDlg dialog


CViewLogDlg::CViewLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CViewLogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewLogDlg)
	m_ChatMsg = _T("");
	m_UserName = _T("");
	m_MsgTime = _T("");
	m_Address = _T("");
	//}}AFX_DATA_INIT
}


void CViewLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewLogDlg)
	DDX_Control(pDX, IDC_USER_FACE, m_UserFace);
	DDX_Control(pDX, IDC_LOG_LIST, m_LogList);
	DDX_Text(pDX, ID_CHAT_MSG, m_ChatMsg);
	DDX_Text(pDX, IDC_USER_NAME, m_UserName);
	DDX_Text(pDX, IDC_MSG_TIME, m_MsgTime);
	DDX_Text(pDX, IDC_ADDRESS, m_Address);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewLogDlg, CDialog)
	//{{AFX_MSG_MAP(CViewLogDlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LOG_LIST, OnItemChangedLogList)
	ON_BN_CLICKED(ID_CLEAR_LOG, OnClearLog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewLogDlg message handlers

BOOL CViewLogDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_LogList.InsertColumn(0, "用户名", LVCFMT_LEFT, 80);
	m_LogList.InsertColumn(1, "讯息内容", LVCFMT_LEFT, 280);

    DWORD NewStyle = m_LogList.GetExtendedStyle();
    NewStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    m_LogList.SetExtendedStyle(NewStyle);

	RefreshList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CViewLogDlg::OnItemChangedLogList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	if(phdn->iItem >= 0)	
	{
		CChatRecordSet crs(&::ChatDB);
		crs.m_strFilter.Format("ID=%d", m_LogList.GetItemData(phdn->iItem));
		crs.Open();
		if(!crs.IsEOF())
		{
			m_ChatMsg = crs.m_ChatMsg;
			m_Address = crs.m_Address;
			m_UserName = crs.m_UserName;
			m_UserFace.SetIcon(::FaceIcon[crs.m_UserFace]);
			CTime MsgTime(crs.m_MsgTime);
			m_MsgTime = MsgTime.Format("%Y-%m-%d %H:%M:%S");
			UpdateData(false);
		}
	}
	*pResult = 0;
}

void CViewLogDlg::OnClearLog() 
{
	if(MessageBox("该操作将删除所有讯息记录，是否继续?", "警告", MB_YESNO | MB_ICONEXCLAMATION) != IDYES)
		return;
	try
	{
		::ChatDB.ExecuteSQL("delete from chat");
	}
	catch(CException *e)
	{
		e->Delete();
	}

	RefreshList();
}

void CViewLogDlg::RefreshList()
{
	m_LogList.DeleteAllItems();
	
	try
	{
		CChatRecordSet crs(&::ChatDB);
		crs.Open();
		int nItem = 0;
		while(!crs.IsEOF())
		{
			nItem = m_LogList.InsertItem(nItem, crs.m_UserName, crs.m_UserFace);
			m_LogList.SetItemText(nItem, 1, crs.m_ChatMsg);
			m_LogList.SetItemData(nItem, (DWORD)crs.m_ID);
			crs.MoveNext();
		}
	}
	catch(CException *e)
	{
		e->Delete();
	}
}
