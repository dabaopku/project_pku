// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "fakeqq.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	//}}AFX_DATA_INIT
	
	m_LocalIp = ::GetLocalIp();
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_Control(pDX, IDC_FACE_LIST, m_FaceList);
	DDX_Control(pDX, IDC_USER_FACE, m_UserFace);
	DDX_Text(pDX, IDC_LOGIN_NAME, m_LoginName);
	DDX_Text(pDX, IDC_UDP_PORT, m_UdpPort);
	DDX_Text(pDX, IDC_LOCAL_IP, m_LocalIp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
//{{AFX_MSG_MAP(CLoginDlg)
ON_CBN_SELCHANGE(IDC_FACE_LIST, OnSelchangeFaceList)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

void CLoginDlg::OnSelchangeFaceList() 
{
	int nItem = m_FaceList.GetCurSel();
	if(nItem == LB_ERR)
	{
		m_UserFace.SetIcon(NULL);
	}
	else
	{
		m_UserFace.SetIcon(::FaceIcon[nItem]);
	}
}

BOOL CLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//读注册表
	DWORD Size = 20;
	TCHAR Values[20];
	CRegKey RegKey;
	
	if(RegKey.Open(HKEY_LOCAL_MACHINE,"Software\\BlueJoe\\FakeQQ") == ERROR_SUCCESS)
	{
		if(RegKey.QueryValue(Values, "Login Name", &Size)  ==ERROR_SUCCESS)
			m_LoginName = Values;
		
		Size = 20;
		if(RegKey.QueryValue(Values, "User Face", &Size)  ==ERROR_SUCCESS)
		{
			CString UserFace = Values;
			int nUserFace = atoi(UserFace);
			m_FaceList.SetCurSel(nUserFace);
			m_UserFace.SetIcon(::FaceIcon[nUserFace]);
		}
		
		Size = 20;
		if(RegKey.QueryValue(Values, "UDP Port", &Size)  ==ERROR_SUCCESS)
		{
			CString UdpPort = Values;
			m_UdpPort = atoi(UdpPort);
		}
	}
	else
	{
		gethostname(Values, 20);
		m_LoginName = Values;
		m_FaceList.SetCurSel(0);
		m_UdpPort = 40000;
	}
	
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLoginDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);
	
	::MyInfo.m_Face = m_FaceList.GetCurSel();
	::MyInfo.m_Port = m_UdpPort;
	strcpy(::MyInfo.m_Ip, m_LocalIp);
	strcpy(::MyInfo.m_UserName, m_LoginName);
	
	if(!::ChatSocket.Create(m_UdpPort, SOCK_DGRAM))
		AfxMessageBox("无法创建Socket，请确认端口号没有冲突。");
	else
	{
		//写注册表
		CRegKey RegKey;
		RegKey.SetValue(HKEY_LOCAL_MACHINE,
			"Software\\BlueJoe\\FakeQQ", ::MyInfo.m_UserName, "Login Name");
		
		CString UserFace;
		UserFace.Format("%d", ::MyInfo.m_Face);
		RegKey.SetValue(HKEY_LOCAL_MACHINE,
			"Software\\BlueJoe\\FakeQQ", UserFace, "User Face");
		
		CString UdpPort;
		UdpPort.Format("%d", ::MyInfo.m_Port);
		RegKey.SetValue(HKEY_LOCAL_MACHINE,
			"Software\\BlueJoe\\FakeQQ", UdpPort, "UDP Port");
		
		CDialog::OnOK();
	}
}
