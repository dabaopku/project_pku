// CalculatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"

#include "CExpress.h"

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
	CQiuXpButton	m_buttonabout;
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
	DDX_Control(pDX, IDOK, m_buttonabout);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalculatorDlg dialog

CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalculatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalculatorDlg)
	m_number = 0.0;
	m_sExpress = _T("");
	m_nResult = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	NumberState=1;
	m_bExp=false;
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalculatorDlg)
	DDX_Control(pDX, IDC_EDIT_PUTOUT, m_edit1);
	DDX_Control(pDX, IDOK, m_button33);
	DDX_Control(pDX, IDC_OPERATION9, m_button32);
	DDX_Control(pDX, IDC_OPERATION8, m_button31);
	DDX_Control(pDX, IDC_OPERATION7, m_button30);
	DDX_Control(pDX, IDC_OPERATION6, m_button29);
	DDX_Control(pDX, IDC_OPERATION5, m_button28);
	DDX_Control(pDX, IDC_OPERATION4, m_button27);
	DDX_Control(pDX, IDC_OPERATION3, m_button26);
	DDX_Control(pDX, IDC_OPERATION22, m_button25);
	DDX_Control(pDX, IDC_OPERATION21, m_button24);
	DDX_Control(pDX, IDC_OPERATION20, m_button23);
	DDX_Control(pDX, IDC_OPERATION2, m_button22);
	DDX_Control(pDX, IDC_OPERATION19, m_button21);
	DDX_Control(pDX, IDC_OPERATION18, m_button20);
	DDX_Control(pDX, IDC_OPERATION17, m_button19);
	DDX_Control(pDX, IDC_OPERATION16, m_button18);
	DDX_Control(pDX, IDC_OPERATION15, m_button17);
	DDX_Control(pDX, IDC_OPERATION14, m_button16);
	DDX_Control(pDX, IDC_OPERATION13, m_button15);
	DDX_Control(pDX, IDC_OPERATION12, m_button14);
	DDX_Control(pDX, IDC_OPERATION11, m_button13);
	DDX_Control(pDX, IDC_OPERATION10, m_button12);
	DDX_Control(pDX, IDC_OPERATION1, m_button11);
	DDX_Control(pDX, IDC_NUMBER9, m_button10);
	DDX_Control(pDX, IDC_NUMBER8, m_button09);
	DDX_Control(pDX, IDC_NUMBER7, m_button08);
	DDX_Control(pDX, IDC_NUMBER6, m_button07);
	DDX_Control(pDX, IDC_NUMBER5, m_button06);
	DDX_Control(pDX, IDC_NUMBER4, m_button05);
	DDX_Control(pDX, IDC_NUMBER3, m_button04);
	DDX_Control(pDX, IDC_NUMBER2, m_button03);
	DDX_Control(pDX, IDC_NUMBER10, m_button02);
	DDX_Control(pDX, IDC_NUMBER1, m_button01);
	DDX_Control(pDX, IDC_CHAR6, m_button6);
	DDX_Control(pDX, IDC_CHAR5, m_button5);
	DDX_Control(pDX, IDC_CHAR4, m_button4);
	DDX_Control(pDX, IDC_CHAR3, m_button3);
	DDX_Control(pDX, IDC_CHAR2, m_button2);
	DDX_Control(pDX, IDC_CHAR1, m_button1);
	DDX_Text(pDX, IDC_EDIT_PUTOUT, m_number);
	DDX_Text(pDX, IDC_EDIT1, m_sExpress);
	DDX_Text(pDX, IDC_EDIT2, m_nResult);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialog)	
	//{{AFX_MSG_MAP(CCalculatorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDM_LOADSKIN, OnLoadskin)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_WM_CONTEXTMENU()
	ON_WM_KEYDOWN()
	ON_COMMAND_RANGE(IDC_NUMBER1,IDC_NUMBER10,OnNumberKey)
	ON_COMMAND_RANGE(IDC_OPERATION1,IDC_OPERATION22,OnOperationKey)
	ON_COMMAND(ID_OPT_EXP, OnOptExp)
	ON_UPDATE_COMMAND_UI(ID_OPT_EXP, OnUpdateOptExp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()

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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	m_Menu.LoadMenu(IDR_MAINFRAME);
	SetMenu( &m_Menu );

	SetWindowSkin( m_hWnd , "Dialog" );
	SetDialogSkin("Dialog");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
void CCalculatorDlg::OnNumberKey(UINT nID)
{
	int n=0;
	switch(nID)
	{
	case IDC_NUMBER1:n=1;break;
	case IDC_NUMBER2:n=2;break;
	case IDC_NUMBER3:n=3;break;
	case IDC_NUMBER4:n=4;break;
	case IDC_NUMBER5:n=5;break;
	case IDC_NUMBER6:n=6;break;
	case IDC_NUMBER7:n=7;break;
	case IDC_NUMBER8:n=8;break;
	case IDC_NUMBER9:n=9;break;
	case IDC_NUMBER10:n=0;break;
	}
	if(NumberState==1)
	{
		t=t*10;
		if(DotState==1)
		{
			m_number=m_number+(double)n/t;
		}
		else
		{
			m_number=m_number*10+n;
		}
	
		number1=m_number;
		UpdateData(FALSE);
	}
	else
	{
		t=t*10;
		if(DotState==1)
		{
			m_number=m_number+(double)n/t;
		}
		else
		{
			m_number=m_number*10+n;
		}
		number2=m_number;
		UpdateData(FALSE);
	}
}
void CCalculatorDlg::OnOperationKey(UINT nID)
{
	switch(nID)
	{
	case IDC_OPERATION1:m_number=-m_number;
					  if(NumberState==1)
					  number1=m_number;
					  else number2=m_number;
					  UpdateData(FALSE);
					  break;                 
	case IDC_OPERATION2:
		{
			if(DotState==1)
			{
				m_number=m_number;
				if(NumberState==1)
					number1=m_number;
				else number2=m_number;
			}
			else
			{
				m_number=(int)m_number/10;
				if(NumberState==1)
					number1=m_number;
				else number2=m_number;
			}
			UpdateData(FALSE);
			break;
		}
	case IDC_OPERATION3:OperationState=1;m_number=0;UpdateData(FALSE);NumberState=2;DotState=2;break;
	case IDC_OPERATION4:OperationState=2;m_number=0;UpdateData(FALSE);NumberState=2;DotState=2;break;
	case IDC_OPERATION5:OperationState=3;m_number=0;UpdateData(FALSE);NumberState=2;DotState=2;break;
	case IDC_OPERATION6:OperationState=4;m_number=0;UpdateData(FALSE);NumberState=2;DotState=2;break;
	case IDC_OPERATION7:number1=number2=m_number=0;UpdateData(FALSE);NumberState=1;break;
	case IDC_OPERATION8:number1=m_number=sqrt(number1);UpdateData(FALSE);break;
	case IDC_OPERATION9:number1=m_number=(double)1/number1;UpdateData(FALSE);break;
	case IDC_OPERATION10:number1=m_number=number1*number1*number1;UpdateData(FALSE);break;
	case IDC_OPERATION11:
		{
			m_number=1;
			for(int i=1;i<=number1;i++)
			{
				m_number=m_number*i;
			}
			UpdateData(FALSE);
			break;
		}
	case IDC_OPERATION12:OperationState=5;m_number=0;UpdateData(FALSE);NumberState=2;DotState=2;break;
	case IDC_OPERATION13:number1=m_number=number1*number1;UpdateData(FALSE);break;
	case IDC_OPERATION14:OperationState=6;m_number=0;UpdateData(FALSE);NumberState=2;DotState=2;break;
	case IDC_OPERATION15:number1=m_number=log10(number1);UpdateData(FALSE);break;
	case IDC_OPERATION16:UpdateData(FALSE);break;//左边的括号
	case IDC_OPERATION17:UpdateData(FALSE);break;//右边的括号
	case IDC_OPERATION18:number1=number2=m_number=0;UpdateData(FALSE);NumberState=1;break;
	case IDC_OPERATION19:DotState=1;t=1;UpdateData(FALSE);break;
	case IDC_OPERATION20:Calculator ();break;
	case IDC_OPERATION21:
		{
			if(NumberState==1)
			{
				number1=m_number=3.1415926;
				UpdateData(FALSE);
			}
			else
			{
				number2=m_number=3.1415926;
				UpdateData(FALSE);
			}
			break;
		}
	case IDC_OPERATION22:
		{
			if(NumberState==1)
			{
				number1=m_number=0.618;
				UpdateData(FALSE);
			}
			else
			{
				number2=m_number=0.618;
				UpdateData(FALSE);
			}
			break;
		}
	}
}
void CCalculatorDlg::Calculator ()
{
	if(!m_bExp)
	{
		switch(OperationState)
		{
		case 1:m_number=(double)number1/number2;NumberState=1;UpdateData(FALSE);break;
		case 2:m_number=number1*number2;NumberState=1;UpdateData(FALSE);break;
		case 3:m_number=number1+number2;NumberState=1;UpdateData(FALSE);break;
		case 4:m_number=number1-number2;NumberState=1;UpdateData(FALSE);break;
		case 5:
			{
				m_number=1;
				for(int i=0;i<number2;i++)
				{
					m_number=m_number*number1;
				}
				NumberState=1;
				UpdateData(FALSE);
				break;
			}
		case 6:
			{
				m_number=fmod(number1,number2);
				NumberState=1;
				UpdateData(FALSE);
				break;
			}
		}
		OperationState=0;
	}
	else
	{
		int ans;             //保存算术表达式的计算结果
		bool quit=false;     //是否退出计算
		CExpress exp;
		
		UpdateData(true);
		int len=m_sExpress.GetLength();
		for(int i=0;i<m_sExpress.GetLength();i++)
			exp.expr[i]=m_sExpress.GetAt(i);
		exp.expr[len]='\0';

		if(setjmp(errjb)==0)    //如果没有错误
		{
			if(exp.expr[0]=='q'||exp.expr[0]=='Q')
				//检查第一个字符，是否退出？
				quit=true;			
			else
				{
					//调用推导式“E -> T+E | T-E | T”的函数，
					//从起始符号“E”开始推导。
					ans=exp.E_AddSub();
						
					//此时，程序认为对表达式的语法分析已经完毕，下面判断出错的原因：
						
					//如果表达式中的某个右括号后直接跟着数字或其他字符，
					//则报错，因为数字i不属于FOLLOW(）)集。
					if(exp.expr[exp.pos-1]==')'&&exp.expr[exp.pos]!='\0')
						exp.Error(CHAR_AFTER_RIGHT);
						
					//如果表达式中的某个数字或右括号后直接跟着左括号，
					//则报错，因为左括号不属于FOLLOW(E)集。
					if(exp.expr[exp.pos]=='(')
						exp.Error(LEFT_AFTER_NUM);
						
					//如果结尾有其他非法字符
					if(exp.expr[exp.pos]!='\0')
						exp.Error(INVALID_CHAR_TAIL);
						
				}
			}
		m_nResult=ans;
		char str[10];
		sprintf(str,"%d",ans);
		m_sExpress=m_sExpress+"="+str;
		UpdateData(FALSE);
	}
}
void CCalculatorDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCalculatorDlg::OnLoadskin() 
{
	char strExt[]= "Skin Files(*.smf)|*.smf||";
	CFileDialog dlg( TRUE, "*.smf", "*.smf" , OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		             , strExt ,  this );

	if( dlg.DoModal() == IDOK  )
	{
		LoadSkinFile( (char*)(LPCSTR)(dlg.GetPathName()) );
	}		
}

void CCalculatorDlg::OnAppAbout() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();	
}

void CCalculatorDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
 {
 	// CG: This block was added by the Pop-up Menu component
 	{
 		if (point.x == -1 && point.y == -1){
 			//keystroke invocation
 			CRect rect;
 			GetClientRect(rect);
 			ClientToScreen(rect);
 
 			point = rect.TopLeft();
 			point.Offset(5, 5);
 		}
 
 		CMenu menu;
 		VERIFY(menu.LoadMenu(IDR_POPUPMENU));
 
 		CMenu* pPopup = menu.GetSubMenu(0);
 		ASSERT(pPopup != NULL);
 		CWnd* pWndPopupOwner = this;
 
 		while (pWndPopupOwner->GetStyle() & WS_CHILD)
 			pWndPopupOwner = pWndPopupOwner->GetParent();
 
 		TrackSkinPopupMenu( pPopup->m_hMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
 			pWndPopupOwner->m_hWnd );
 	}
//	OnLoadskin() ;
}

BOOL CCalculatorDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN || pMsg->message == WM_CHAR)
         SendMessage(pMsg->message,pMsg->wParam,pMsg->lParam);	
	return CDialog::PreTranslateMessage(pMsg);
}

void CCalculatorDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(!m_bExp)
	{
		UINT nID;
		int n=0;
		if(nChar<58&&nChar>47){
			switch(nChar) {
				case 49:nID=IDC_NUMBER1;break;
				case 50:nID=IDC_NUMBER2;break;
				case 51:nID=IDC_NUMBER3;break;
				case 52:nID=IDC_NUMBER4;break;
				case 53:nID=IDC_NUMBER5;break;
				case 54:nID=IDC_NUMBER6;break;
				case 55:nID=IDC_NUMBER7;break;
				case 56:
					{
						if(::GetKeyState(VK_SHIFT)&0x8000)
						{OnOperationKey(IDC_OPERATION4);goto a;}
						else
							nID=IDC_NUMBER8;
				}
				break;
			case 57:
				{
						if(::GetKeyState(VK_SHIFT)&0x8000)
						{OnOperationKey(IDC_OPERATION16);goto a;}
						else
							nID=IDC_NUMBER9;
				}
				break;
			case 48:
					{
						if(::GetKeyState(VK_SHIFT)&0x8000)
						{OnOperationKey(IDC_OPERATION17);goto a;}
						else
							nID=IDC_NUMBER10;
					}
					break;
			default:break;
			}
			OnNumberKey(nID);
		}
		else
		{
			UINT nID;	
			switch(nChar)
			{
			case 189: nID=IDC_OPERATION6; break;   //-
			case 8: nID=IDC_OPERATION2; break;     //BackSpace
			case 191: nID=IDC_OPERATION3; break;   ///
			case 187:   //+/=
				{
					if(::GetKeyState(VK_SHIFT)&0x8000)
						nID=IDC_OPERATION5;
					else
						nID=IDC_OPERATION20;
				}
				break;
			case 190: nID=IDC_OPERATION19; break;     //.
			}
			OnOperationKey(nID);
		}
	}
	a:	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

// 是否选择表达式运算方式
//
void CCalculatorDlg::OnOptExp()   
{
	m_bExp=!m_bExp;
	CEdit* pLB=(CEdit*)GetDlgItem(IDC_EDIT_PUTOUT);
	CEdit* pLBNew=(CEdit*)GetDlgItem(IDC_EDIT1);
	
	if(m_bExp)
	{
		pLB->ShowWindow(SW_HIDE);	
		pLBNew->ShowWindow(SW_SHOW);
	}
	else
	{
		pLB->ShowWindow(SW_SHOW);	
		pLBNew->ShowWindow(SW_HIDE);
	}

	m_sExpress="0";
	m_nResult=0;
	m_number=0;
	UpdateData(FALSE);


}

void CCalculatorDlg::OnUpdateOptExp(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bExp==true);
}
