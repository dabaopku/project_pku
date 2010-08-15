// SendMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FakeQQ.h"
#include "MsgInfo.h"
#include "SendMsgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendMsgDlg dialog


CSendMsgDlg::CSendMsgDlg(CUserInfo * pToUser, CWnd* pParent /*=NULL*/)
	: CDialog(CSendMsgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendMsgDlg)
	m_Msg = _T("");
	//}}AFX_DATA_INIT
	m_pToUser = pToUser;
	m_LocalIp = ::MyInfo.m_Ip;
	m_LoginName = ::MyInfo.m_UserName;
	m_UdpPort.Format("%d", ::MyInfo.m_Port);
}


void CSendMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendMsgDlg)
	DDX_Control(pDX, IDC_TO_PORT, m_ToPort);
	DDX_Control(pDX, IDC_TO_IP, m_ToIp);
	DDX_Text(pDX, IDC_CHAT_MSG, m_Msg);
	DDV_MaxChars(pDX, m_Msg, 250);
	DDX_Text(pDX, IDC_LOCAL_IP, m_LocalIp);
	DDX_Text(pDX, IDC_LOGIN_NAME, m_LoginName);
	DDX_Text(pDX, IDC_TO_USER, m_ToUser);
	DDX_Text(pDX, IDC_UDP_PORT, m_UdpPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendMsgDlg, CDialog)
	//{{AFX_MSG_MAP(CSendMsgDlg)
	ON_BN_CLICKED(ID_SEND_MSG, OnSendMsg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendMsgDlg message handlers

void CSendMsgDlg::OnSendMsg() 
{
	UpdateData(true);

	CMsgInfo Msg;
	Msg.m_FromUser = ::MyInfo;
	strcpy(Msg.m_Msg, m_Msg);
	Msg.m_Time = time(NULL);

	CString ToIp;
	CString ToPort;
	m_ToIp.GetWindowText(ToIp);
	m_ToPort.GetWindowText(ToPort);

	if(::ChatSocket.SendTo(&Msg, sizeof(CMsgInfo), atoi(ToPort), ToIp) != SOCKET_ERROR)
		OnCancel();
	else
	{
		MessageBox("·¢ËÍÑ¶Ï¢Ê§°Ü£¡");
	}
}

BOOL CSendMsgDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if(!m_pToUser)
	{
		m_ToUser = _T(":)");

		m_ToPort.SetWindowText("40000");
		m_ToIp.SetWindowText(::MyInfo.m_Ip);
	}
	else
	{
		m_ToUser = m_pToUser->m_UserName;
		m_ToIp.SetWindowText(m_pToUser->m_Ip);

		CString ToPort;
		ToPort.Format("%d", m_pToUser->m_Port);
		m_ToPort.SetWindowText(ToPort);

		m_ToIp.SetReadOnly();
		m_ToPort.SetReadOnly();
	}
	
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
