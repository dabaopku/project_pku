// FakeQQDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FakeQQ.h"
#include "FakeQQDlg.h"
#include "ChatRecordSet.h"
#include "ViewLogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFakeQQDlg dialog

CFakeQQDlg::CFakeQQDlg(CWnd* pParent /*=NULL*/)
: CDialog(CFakeQQDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFakeQQDlg)
	m_Elapse = _T("00:00:00");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_bHide = false;
	m_hIcon = ::FaceIcon[::MyInfo.m_Face];
	m_nDisplayTimerID = 1;
	m_nTrayIconFlashTimerID = 2;
	m_bTrayIconFlashing = false;
	m_hFlashingTrayIcon = NULL;
}

void CFakeQQDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFakeQQDlg)
	DDX_Control(pDX, IDC_TOOLBAR_PANE, m_ToolBarPane);
	DDX_Control(pDX, IDC_USER_LIST, m_UserList);
	DDX_Text(pDX, IDC_ELAPSE, m_Elapse);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFakeQQDlg, CDialog)
//{{AFX_MSG_MAP(CFakeQQDlg)
ON_WM_SYSCOMMAND()
ON_WM_TIMER()
ON_WM_DESTROY()
ON_COMMAND(ID_SHOW_WINDOW, OnShowWindow)
ON_NOTIFY(NM_DBLCLK, IDC_USER_LIST, OnDblclkUserList)
ON_COMMAND(ID_HIDE_WINDOW, OnHideWindow)
ON_COMMAND(ID_VIEW_LOG, OnViewLog)
ON_COMMAND(ID_SHOW_LAST_CHAT, OnShowLastChat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFakeQQDlg message handlers

BOOL CFakeQQDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	if (!m_ToolBar.CreateEx(this) ||
		!m_ToolBar.LoadToolBar(IDR_TOOLBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
	CRect Rect;
	m_ToolBarPane.GetWindowRect(Rect);
	ScreenToClient(Rect); 
	m_ToolBar.MoveWindow(&Rect);
	m_ToolBar.SetBarStyle(m_ToolBar.GetBarStyle() |	CBRS_TOOLTIPS | CBRS_FLYBY);
	
	BuildUserList();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_nDisplayTimerID = SetTimer(m_nDisplayTimerID, 1000, NULL);
	m_StartTime = CTime::GetCurrentTime();
	
	m_Nid.cbSize = sizeof(NOTIFYICONDATA);
	m_Nid.hWnd = GetSafeHwnd();
	m_Nid.uID = 0;
	m_Nid.hIcon = m_hIcon;
	m_Nid.uFlags = NIF_ICON|NIF_TIP|NIF_MESSAGE;
	m_Nid.uCallbackMessage = WM_COMMAND;
	
	CString sTitle;
	sTitle.Format("FakeQQ 1.0\r\n%s\r\n%s:%d", ::MyInfo.m_UserName, ::MyInfo.m_Ip, ::MyInfo.m_Port);
	strcpy(m_Nid.szTip, sTitle);
	Shell_NotifyIcon(NIM_ADD, &m_Nid);
	
	SetWindowText(::MyInfo.m_UserName);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFakeQQDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}


void CFakeQQDlg::OnTimer(UINT nIDEvent) 
{
	//闪烁
	if(nIDEvent == m_nTrayIconFlashTimerID)	
	{
		if(m_nTrayIconFlashTicks)
		{
			m_Nid.hIcon = NULL;
		}
		else
		{
			m_Nid.hIcon = m_hFlashingTrayIcon;
		}
		Shell_NotifyIcon(NIM_MODIFY,&m_Nid);
		m_nTrayIconFlashTicks = !m_nTrayIconFlashTicks;
	}
	
	//显示时间
	if(nIDEvent == m_nDisplayTimerID)
	{
		CTimeSpan Elapse = CTime::GetCurrentTime() - m_StartTime;
		CString Prompt = Elapse.Format("%H:%M:%S");
		
		m_Elapse= Prompt;
		UpdateData(false);		
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CFakeQQDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	FlashTrayIcon(m_hIcon, false);
	KillTimer(m_nDisplayTimerID);
	Shell_NotifyIcon(NIM_DELETE, &m_Nid);	
}

void CFakeQQDlg::OnShowWindow() 
{
	ShowWindow(true);
	m_bHide = false;
	SetForegroundWindow();
}

BOOL CFakeQQDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if(!wParam)
	{
		switch(lParam)
		{
		case WM_LBUTTONUP:
			OnShowWindow();
			break;
			
		case WM_LBUTTONDBLCLK:
			OnShowLastChat();
			break;
			
		case WM_RBUTTONUP:
			CMenu Menu, *pMenu;
			Menu.LoadMenu(IDR_POP);
			pMenu=Menu.GetSubMenu(0);
			
			SetForegroundWindow();
			POINT Pt;
			GetCursorPos(&Pt);
			pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_BOTTOMALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,Pt.x,Pt.y,this);
			break;
		}
	}		
	return CDialog::OnCommand(wParam, lParam);
}

void CFakeQQDlg::OnDblclkUserList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	if(phdn->iItem >= 0)	
	{
		CUserInfo * pUser = (CUserInfo *)m_UserList.GetItemData(phdn->iItem);
		CSendMsgDlg SendDlg(pUser);
		SendDlg.DoModal();
	}
	*pResult = 0;
}

void CFakeQQDlg::BuildUserList()
{
	//初始化界面
	m_ImageList.Create(32, 32, TRUE, 8, 1);
	
	for(int i = 0; i < sizeof(::FaceIcon)/sizeof(HICON); i++)
	{
		m_ImageList.Add(::FaceIcon[i]);
	}
	
	m_UserList.SetBkColor(RGB(128, 128, 192));
	m_UserList.SetTextBkColor(RGB(128, 128, 192));
	m_UserList.SetImageList(&m_ImageList, LVSIL_NORMAL);
	m_UserList.SetIconSpacing(0, 10);

	//0为主叫连接
	m_UserList.InsertItem(0, "主叫连接", 0);    
}

CFakeQQDlg::~CFakeQQDlg()
{
	POSITION p = m_UserInfoList.GetHeadPosition();
	while(p)
	{
		CUserInfo * pUser = (CUserInfo *)m_UserInfoList.GetNext(p);
		if(pUser)
			delete pUser;
	}
	
	m_UserInfoList.RemoveAll();
	
	for(int i = 0; i < m_MsgQueue.GetSize(); i++)
	{
		CMsgInfo * pMsg = (CMsgInfo *)m_MsgQueue.GetAt(i);
		if(pMsg)
			delete pMsg;
	}
	
	m_MsgQueue.RemoveAll();
}

void CFakeQQDlg::OnHideWindow() 
{
	ShowWindow(SW_HIDE);
	m_bHide = true;	
}

void CFakeQQDlg::FlashTrayIcon(HICON Icon, bool Flash)
{
	m_nTrayIconFlashTicks = 0;
	if(Flash)
	{
		m_hFlashingTrayIcon = Icon;
		m_nTrayIconFlashTimerID = SetTimer(m_nTrayIconFlashTimerID, 500 , NULL);
		m_bTrayIconFlashing = true;
	}
	else
	{
		KillTimer(m_nTrayIconFlashTimerID);
		m_Nid.hIcon = Icon;
		Shell_NotifyIcon(NIM_MODIFY,&m_Nid);
		m_bTrayIconFlashing = false;
	}
}

void CFakeQQDlg::PushMsg(CMsgInfo *pMsg)
{
	CSingleLock sLock(&m_Mutex);
	
	m_MsgQueue.Add(pMsg);
	
	//保存讯息
	SaveMsg(pMsg);
	
	//在ListCtrl里显示头像
	
	int nItem = FindUser(&pMsg->m_FromUser);
	CUserInfo * pUser;

	if(nItem != -1)
	{
		pUser = (CUserInfo *)m_UserList.GetItemData(nItem);
		delete pUser;
		m_UserList.DeleteItem(nItem);
	}
	else
		nItem = 1;

	nItem = m_UserList.InsertItem(nItem, pMsg->m_FromUser.m_UserName, pMsg->m_FromUser.m_Face);

	pUser = new CUserInfo();
	*pUser = pMsg->m_FromUser;
	m_UserList.SetItemData(nItem, (DWORD)pUser);
	
	//闪动TrayIcon?
	if(m_MsgQueue.GetSize() == 1)
		FlashTrayIcon(::FaceIcon[pMsg->m_FromUser.m_Face]);
	
	sLock.Unlock();	
}

CMsgInfo * CFakeQQDlg::PopMsg()
{
	if(!m_MsgQueue.GetSize())
		return NULL;
	
	CMsgInfo * pMsg = (CMsgInfo *)m_MsgQueue.GetAt(0);
	m_MsgQueue.RemoveAt(0);
	
	//处理TrayIcon
	if(!m_MsgQueue.GetSize())
		FlashTrayIcon(m_hIcon, false);
	else
	{
		CMsgInfo * pNextMsg = (CMsgInfo *)m_MsgQueue.GetAt(0);
		FlashTrayIcon(::FaceIcon[pNextMsg->m_FromUser.m_Face]);
	}
	
	return pMsg;
}

int CFakeQQDlg::FindUser(CUserInfo *pUser)
{
	//0为主叫连接
	for(int i = 1; i < m_UserList.GetItemCount(); i++)
	{
		CUserInfo * pItem = (CUserInfo *)m_UserList.GetItemData(i);
		if(pItem && !strcmp(pItem->m_Ip, pUser->m_Ip) && pItem->m_Port == pUser->m_Port)
			return i;
	}
	return -1;
}

bool CFakeQQDlg::SaveMsg(CMsgInfo *pMsg)
{
	try
	{
		CChatRecordSet crs(&::ChatDB);
		crs.Open();
		crs.AddNew();
		
		crs.m_Address.Format("%s:%d", pMsg->m_FromUser.m_Ip, pMsg->m_FromUser.m_Port);
		crs.m_ChatMsg = pMsg->m_Msg;
		crs.m_UserFace = pMsg->m_FromUser.m_Face;
		crs.m_UserName = pMsg->m_FromUser.m_UserName;
		crs.m_MsgTime = pMsg->m_Time;
		
		if(crs.Update())
			return true;
	}
	catch(CException *e)
	{
		e->Delete();
		return false;
	}
	return false;
}

void CFakeQQDlg::OnViewLog() 
{
	// TODO: Add your command handler code here
	CViewLogDlg LogDlg;
	LogDlg.DoModal();
}

void CFakeQQDlg::OnShowLastChat() 
{
	CMsgInfo * pMsg = PopMsg();
	if(pMsg)
	{
		CReplyMsgDlg ReplyDlg(pMsg);
		ReplyDlg.DoModal();
		delete pMsg;
	}
}
