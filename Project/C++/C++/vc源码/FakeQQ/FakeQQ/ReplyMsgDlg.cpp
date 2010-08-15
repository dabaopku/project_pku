// ReplyMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FakeQQ.h"
#include "ReplyMsgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReplyMsgDlg dialog


CReplyMsgDlg::CReplyMsgDlg(CMsgInfo * pMsg, CWnd* pParent /*=NULL*/)
	: CDialog(CReplyMsgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReplyMsgDlg)
	m_MsgTime = _T("");
	//}}AFX_DATA_INIT

	m_UserName = pMsg->m_FromUser.m_UserName;
	m_Address.Format("%s:%d", pMsg->m_FromUser.m_Ip, pMsg->m_FromUser.m_Port);
	m_Msg = pMsg->m_Msg;
	CTime MsgTime(pMsg->m_Time);
	m_MsgTime = MsgTime.Format("%Y-%m-%d %H:%M:%S");

	m_pMsg = pMsg;
}


void CReplyMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReplyMsgDlg)
	DDX_Control(pDX, IDC_USER_FACE, m_UserFace);
	DDX_Text(pDX, ID_CHAT_MSG, m_Msg);
	DDX_Text(pDX, IDC_ADDRESS, m_Address);
	DDX_Text(pDX, IDC_USER_NAME, m_UserName);
	DDX_Text(pDX, IDC_MSG_TIME, m_MsgTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReplyMsgDlg, CDialog)
	//{{AFX_MSG_MAP(CReplyMsgDlg)
	ON_BN_CLICKED(IDOK, OnReplyMsg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReplyMsgDlg message handlers

void CReplyMsgDlg::OnReplyMsg() 
{
	CSendMsgDlg SendDlg(&m_pMsg->m_FromUser);
	OnCancel();
	SendDlg.DoModal();
}

BOOL CReplyMsgDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_UserFace.SetIcon(::FaceIcon[m_pMsg->m_FromUser.m_Face]);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
