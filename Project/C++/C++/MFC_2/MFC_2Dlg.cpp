// MFC_2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_2.h"
#include "MFC_2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMFC_2Dlg 对话框




CMFC_2Dlg::CMFC_2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFC_2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_oNameEdit);
	DDX_Control(pDX, IDC_SLIDER1, m_oSalarySlider);
	DDX_Control(pDX, IDC_EDIT_salary, m_oSalaryEdit);
	DDX_Control(pDX, IDC_COMBO1, m_oJobCombox);
	DDX_Control(pDX, IDC_LIST1, m_oEmployeeList);
}

BEGIN_MESSAGE_MAP(CMFC_2Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_LBN_SELCHANGE(IDC_LIST1, &CMFC_2Dlg::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC_2Dlg::OnBnClickedButton1)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CMFC_2Dlg 消息处理程序

BOOL CMFC_2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 初始化代码
	//滑动条
	m_oSalarySlider.SetRangeMin(0);
	m_oSalarySlider.SetRangeMax(10000);
	m_oSalarySlider.SetPos(800);

	//月薪
	SetDlgItemInt(IDC_EDIT_salary,800);
	
	//组合框
#define  Max_Combox_Size	100//组合框尺寸

	WINDOWPLACEMENT wp;
	m_oJobCombox.GetWindowPlacement(&wp);
	m_oJobCombox.MoveWindow(
		wp.rcNormalPosition.left,wp.rcNormalPosition.top,
		wp.rcNormalPosition.right-wp.rcNormalPosition.left,
		wp.rcNormalPosition.bottom+Max_Combox_Size);
	m_oJobCombox.AddString(_T("营销员"));
	m_oJobCombox.AddString(_T("业务员"));
	m_oJobCombox.AddString(_T("送货员"));
	m_oJobCombox.AddString(_T("采购员"));
	m_oJobCombox.AddString(_T("会计员"));
	m_oJobCombox.AddString(_T("秘书"));
	m_oJobCombox.AddString(_T("经理"));
	m_oJobCombox.SetCurSel(0);



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC_2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFC_2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFC_2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFC_2Dlg::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CMFC_2Dlg::OnBnClickedButton1()
{
	struct employee_info
	{
		CString name;
		bool	sex;
		bool	marriage;
		int		salary;
		int		job;
	};

	employee_info info;

	m_oNameEdit.GetWindowText(info.name);

	if (IsDlgButtonChecked(IDC_RADIO_man))
	{
		info.sex=true;
	}
	else
		info.sex=false;

	info.salary=GetDlgItemInt(IDC_EDIT_salary);
	info.marriage=IsDlgButtonChecked(IDC_CHECK_marrige)==BST_CHECKED?true:false;
	info.job=m_oJobCombox.GetCurSel();

	TCHAR record[1024];
	wsprintf(record,L"%s  %s  %s  月薪 %d  职务 :%s",info.name,info.sex?L"男":L"女",info.marriage?L"已婚":L"未婚",info.salary,GetInfJob(info.job)); 

	m_oEmployeeList.AddString(record);
}


TCHAR* CMFC_2Dlg::GetInfJob(int ID)
{
	TCHAR str[1024];
	ZeroMemory(str,1024);

	m_oJobCombox.GetLBText(ID,str);

	return str;
}

void CMFC_2Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// 滑动条
	if(nSBCode==TB_THUMBTRACK){
		SetDlgItemInt(IDC_EDIT_salary,m_oSalarySlider.GetPos());
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
