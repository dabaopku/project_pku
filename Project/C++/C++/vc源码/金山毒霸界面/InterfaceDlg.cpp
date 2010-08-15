// InterfaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Interface.h"
#include "InterfaceDlg.h"

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
// CInterfaceDlg dialog

CInterfaceDlg::CInterfaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInterfaceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInterfaceDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInterfaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInterfaceDlg)
	DDX_Control(pDX, IDC_HOMEBTN, m_HomeBtn);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_STARTBTN, m_StartBtn);
	DDX_Control(pDX, IDC_CLOSEBTN, m_CloseBtn);
	DDX_Control(pDX, IDC_BITMAPBTN, m_BitmapBtn);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInterfaceDlg, CDialog)
	//{{AFX_MSG_MAP(CInterfaceDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CLOSEBTN, OnClosebtn)
	ON_BN_CLICKED(IDC_STARTBTN, OnStartbtn)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BITMAPBTN, &CInterfaceDlg::OnBnClickedBitmapbtn)
	ON_EN_CHANGE(IDC_EDIT1, &CInterfaceDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_CHECK2, &CInterfaceDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CInterfaceDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK1, &CInterfaceDlg::OnBnClickedCheck1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CInterfaceDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterfaceDlg message handlers

BOOL CInterfaceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	ModifyStyle( WS_CAPTION, WS_MINIMIZEBOX, SWP_DRAWFRAME );//设置图标
	SetWindowText("金山毒霸专杀工具");//设置对话框的标题
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_bEnable=true;
	// TODO: Add extra initialization here
	m_bmpBackground.LoadBitmap(IDB_BITMAPBACKGROUND);	/// 加载背景
	m_BitmapBtn.LoadBitmaps(IDB_BITMAPNORMAL,IDB_BITMAPSEL);
	m_CloseBtn.LoadBitmaps(IDB_BITMAPCLOSENORMAL,IDB_BITMAPDOWN);
	m_StartBtn.LoadBitmaps(IDB_BITMAPONNORMAL,IDB_BITMAPONDOWN);
	m_HomeBtn.LoadBitmaps(IDB_BITMAPHOMENORMAL,IDB_BITMAPHOMEDOWN);
	m_List.InsertColumn(0,"文件路径",LVCFMT_LEFT,360);
	m_List.InsertColumn(1,"扫描结果",LVCFMT_LEFT,117);
	m_List.InsertColumn(2,"状态",LVCFMT_LEFT,89);
	m_Link1.SubclassDlgItem(IDC_STATIC1,this);
	m_Link1.SetCaption("金山毒霸对该病毒的解决方案");
	m_Link1.SetTextColor(RGB(0,130,255));
	
	m_Link2.SubclassDlgItem(IDC_STATIC2,this);
	m_Link2.SetCaption("上卓越网：在线购买金山毒霸");
	m_Link2.SetTextColor(RGB(0,130,255));

	m_Link3.SubclassDlgItem(IDC_STATIC3,this);
	m_Link3.SetCaption("网易病毒预警短信");
	m_Link3.SetTextColor(RGB(0,0,255));
	CRect rect1;
	m_Link3.GetWindowRect(&rect1);
	rect1.top+=17;
	rect1.bottom+=17;
	m_Link3.MoveWindow(rect1.left,rect1.top,rect1.Width(),rect1.Height());

	m_Static4.SubclassDlgItem(IDC_STATIC4,this);
	m_Static4.SetCaption("总文件数：");
	m_Static4.SetBackColor(RGB(222,223,222));

	m_Static5.SubclassDlgItem(IDC_STATIC5,this);
	m_Static5.SetCaption("病毒数：");
	m_Static5.SetBackColor(RGB(222,223,222));

	m_Static6.SubclassDlgItem(IDC_STATIC6,this);
	m_Static6.SetCaption("清除数：");
	m_Static6.SetBackColor(RGB(222,223,222));

	m_Static7.SubclassDlgItem(IDC_STATIC7,this);
	m_Static7.SetCaption("清除数：");
	m_Static7.SetBackColor(RGB(222,223,222));

	m_Static8.SubclassDlgItem(IDC_STATIC8,this);
	m_Static8.SetCaption("");
	m_Static8.SetBackColor(RGB(222,223,222));

	m_Static9.SubclassDlgItem(IDC_STATIC9,this);
	m_Static9.SetCaption("扫描状态：");
	m_Static9.SetBackColor(RGB(222,223,222));

	m_Static10.SubclassDlgItem(IDC_STATIC10,this);
	m_Static10.SetCaption("扫描路径：");
	m_Static10.SetBackColor(RGB(222,223,222));

	m_ColorBtn1.SubclassDlgItem(IDC_CHECK1,this);
	m_ColorBtn1.SetBackColor(RGB(222,223,222));

	m_ColorBtn2.SubclassDlgItem(IDC_CHECK2,this);
	m_ColorBtn2.SetBackColor(RGB(222,223,222));

	m_ColorBtn3.SubclassDlgItem(IDC_CHECK3,this);
	m_ColorBtn3.SetBackColor(RGB(222,223,222));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInterfaceDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CInterfaceDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
//		CDialog::OnPaint();
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		CDC dcMem; 
		dcMem.CreateCompatibleDC(&dc); 
		BITMAP bitMap;
		m_bmpBackground.GetBitmap(&bitMap);
		CBitmap *pbmpOld=dcMem.SelectObject(&m_bmpBackground);
		dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bitMap.bmWidth,bitMap.bmHeight,SRCCOPY);
		//dc.BitBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,SRCCOPY);
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CInterfaceDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CInterfaceDlg::OnClosebtn() 
{
	
	OnOK();
}

void CInterfaceDlg::OnStartbtn() 
{
	
	if(m_bEnable)
	{
		m_StartBtn.LoadBitmaps(IDB_BITMAPOFFNORMAL,IDB_BITMAPOFFDOWN);
		m_bEnable=false;
		m_StartBtn.RedrawWindow();
	}
	else
	{
		m_StartBtn.LoadBitmaps(IDB_BITMAPONNORMAL,IDB_BITMAPONDOWN);
		m_bEnable=true;
		m_StartBtn.RedrawWindow();
	}
}

void CInterfaceDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x, point.y));
	//向系统发送HTCAPTION消息，让系统以为鼠标点在标题栏上
	CDialog::OnLButtonDown(nFlags, point);
}


