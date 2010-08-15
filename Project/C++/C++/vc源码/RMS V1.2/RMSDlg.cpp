// RMSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RMS.h"
#include "RMSDlg.h"
#include "Picture.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CRMSApp theApp;//引用外部全局变量 @@@养成习惯@@@

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
// CRMSDlg dialog

CRMSDlg::CRMSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRMSDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRMSDlg)
	m_Txt = _T("");
	m_word = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRMSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRMSDlg)
	DDX_Text(pDX, IDC_EDIT2, m_Txt);
	DDX_Text(pDX, IDC_EDIT1, m_word);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRMSDlg, CDialog)
	//{{AFX_MSG_MAP(CRMSDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton_in)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton_out)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton_pre)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton_next)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton_del)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton_Fileout)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton_File_In)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton_File_Del)
	ON_BN_CLICKED(IDC_BUTTON6, OnOK)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton_Find)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRMSDlg message handlers

BOOL CRMSDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
    _variant_t vtxt;

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
			strAboutMenu = _T( "关于蓝风 图文资源管理程序!" );
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		    pSysMenu->DeleteMenu( 4, MF_BYPOSITION );// 删除最大化命令
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
    try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");//创建记录集实例
		m_pRecordset->Open("SELECT * FROM jpg ORDER BY id",_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);//打开记录集
//	    m_pRecordset->MoveFirst;
	}
	catch(_com_error e)
	{
		AfxMessageBox("读取数据库失败!");
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRMSDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRMSDlg::OnPaint() 
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
	//	OnButton_in();
	}
	else
	{
    //	OnButton_in();
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRMSDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRMSDlg::OnOK() 
{
exit(0);//退出整个应用程序（线程）   
//	CDialog::OnOK();//退出对话框
//OnCancel();  // （线程）
m_pRecordset->Update();
m_pRecordset->Close();
}

void CRMSDlg::OnButton_in() //从库中提取并显示
{
	// TODO: Add your control notification handler code here
	try
	{
		// "pic" 是字段名，该字段保存着 OLE 对象
		long nSize = m_pRecordset->GetFields()->GetItem("pic")->ActualSize;	// 获取字段 "pic" 的当前单元的大小（在分配内存空间时要用到）	
		if(nSize > 0)
		{
			_variant_t varBLOB;
			varBLOB = m_pRecordset->GetFields()->GetItem("pic")->GetChunk(nSize);// 读取 OLE 对象 --> varBLOB

			if(varBLOB.vt == (VT_ARRAY | VT_UI1))
			{
				if(BYTE *pBuffer = new BYTE [nSize+1])		// 申请必要的存储空间
				{	
					void* pBuf = NULL;

					SafeArrayAccessData(varBLOB.parray,(void**)&pBuf);
					memcpy(pBuffer,pBuf,nSize);				// 复制数据到缓冲区 pBuffer
					SafeArrayUnaccessData (varBLOB.parray);

					// SafeArrayAccessData() 的作用是给 varBLOB 分配一个 void 型指针
					// 因为 memcpy 的第二个参数只接受 void 型指针

					// 读取图像
					if(m_Pic.m_IPicture != NULL) m_Pic.FreePictureData();
					m_Pic.LoadPictureData(pBuffer, nSize);
					delete [] pBuffer;
					pBuf=0;
					 
					// 显示图像
				    CStatic *pStaic;
                    pStaic=(CStatic*)GetDlgItem(IDC_IMAGE);//指向图片将要要显示的区域
                   // memDC.CreateCompatibleDC(GetDC());
                    pStaic->GetClientRect(&rect);//得到指定区域

                    CClientDC dc(pStaic); //定义初始化设备变量

					m_Pic.UpdateSizeOnDC(&dc); // Allocate memory for m_Pic
					m_Pic.Show(&dc,CRect(0,0,188,190));
                    
					OnButton_Fileout();		
				}
			}
		}
	}
	catch (_com_error e)
	{
	}
		
}

void CRMSDlg::OnButton_out() //存入库并显示
{
	// TODO: Add your control notification handler code here
	CFile f;
	CString  FilePathName;
	CFileException e;
    
	CFileDialog dlg(TRUE,NULL,NULL,0,"jpg Files (*.jpg)|*.jpg||",this); //TRUE为OPEN对话框，FALSE为SAVE AS对话框
	if(dlg.DoModal()==IDOK)
	{
		FilePathName=dlg.GetPathName();

		if(f.Open(FilePathName, CFile::modeRead | CFile::typeBinary, &e)) //打开指定的jpg文件
		{
			int nSize = f.GetLength();          //先得到 jpg 文件长度
			BYTE* pBuffer = new BYTE [nSize];   //按文件的大小在堆上申请一块内存 pBuffer
	 
			if (f.Read(pBuffer, nSize) > 0 )    //把 jpg 文件读到 pBuffer
			{
				//把pBuffer里的jpg数据放到库中
				BYTE* pBuf = pBuffer;			
				VARIANT			varBLOB;		
				SAFEARRAY		*psa;
			    SAFEARRAYBOUND	rgsabound[1];
				
			//	m_pRecordset->AddNew();			//添加一条新记录
				 OnButton_File_In();//读入文件	
			
				if(pBuf)
				{    
					rgsabound[0].lLbound = 0;
					rgsabound[0].cElements = nSize;

					psa = SafeArrayCreate(VT_UI1, 1, rgsabound); // 创建 SAFEARRAY 对象 psa
					for (long i = 0; i < (long)nSize; i++)
						SafeArrayPutElement (psa, &i, pBuf++);	 // 将 bBuf 指向的二进制数据
																 // 保存到 psa 中

					varBLOB.vt = VT_ARRAY | VT_UI1;	// 将 varBLOB 类型设为 BYTE 类型数组
					varBLOB.parray = psa;			// 保存 psa 到 varBLOB

					
					m_pRecordset->GetFields()->GetItem("pic")->AppendChunk(varBLOB);//添加 varBLOB 到数据库
				}            
				// 更新数据库
				m_pRecordset->Update();

				// 读取图像
				if(m_Pic.m_IPicture != NULL) m_Pic.FreePictureData();
				m_Pic.LoadPictureData(pBuffer, nSize);
				delete [] pBuffer;
				pBuf=0;                //空指针指向0
			}
			f.Close();
             
		}
                   
		// 显示图像
	            	CStatic *pStaic;
                    pStaic=(CStatic*)GetDlgItem(IDC_IMAGE);//指向图片将要要显示的区域
                   // memDC.CreateCompatibleDC(GetDC());
                    pStaic->GetClientRect(&rect);//得到指定区域

                    CClientDC dc(pStaic); //定义初始化设备变量

					m_Pic.UpdateSizeOnDC(&dc); // Allocate memory for m_Pic
					m_Pic.Show(&dc,CRect(0,0,188,190));
					OnButton_Fileout();
	}	
}

void CRMSDlg::OnButton_pre() 
{
	// TODO: Add your control notification handler code here
	try{
		m_pRecordset->MovePrevious();	//上一个记录
		OnButton_in();
		OnButton_Fileout();
	}
	catch (_com_error e) 
	{
	}

	if(m_pRecordset->BOF)				//若成立，表示到了第一条记录之前
	{
		m_pRecordset->MoveNext(); 
	    AfxMessageBox("这已经是第一条记录了 ∵");
	}
	//	m_pRecordset->MoveNext();		//第一条记录之前没有任何数据，所以前进一条记录

}

void CRMSDlg::OnButton_next() 
{
	// TODO: Add your control notification handler code here
	try{
		m_pRecordset->MoveNext();       //下一个记录
		OnButton_in();
		OnButton_Fileout();
	}
	catch (_com_error e) 
	{
	}

	if(m_pRecordset->adoEOF)			//若成立，表示到了最后一条记录之后
	{
		m_pRecordset->MovePrevious();
		AfxMessageBox("到最后一条记录了 ∵");
	}
	//	m_pRecordset->MovePrevious();	//最后一条记录之后没有任何数据，所以后退一条记录
}

void CRMSDlg::OnButton_del() 
{
	// TODO: Add your control notification handler code here
	m_pRecordset->Delete(adAffectCurrent);	// 删除当前行记录
	m_pRecordset->Update();
	OnButton_next();
	OnButton_in();
}

void CRMSDlg::OnButton_Fileout() 
{
	// TODO: Add your control notification handler code here
//	m_pRecordset->Move(m_nCurrentSel,_variant_t((long)adBookmarkFirst));
    vtxt = m_pRecordset->GetCollect("txt");
	m_Txt = (LPCTSTR)(_bstr_t)vtxt;//vtxt.lVal;为数字 存入时要用（long）强制转换/ bstrVal为字符
 //  m_Txt = m_pRecordset->GetCollect("txt").bstrVal;
  // m_Old.Format("%d",m_pRecordset->GetCollect("old").lVal);// m_Old 为long型
	//m_pRecordset->PutCollect("old",atol(m_Old));
	UpdateData(FALSE);//下次操作生效
}

void CRMSDlg::OnButton_File_In() 
{
	// TODO: Add your control notification handler code here
//	if(!m_pRecordset->adoEOF && !m_pRecordset->BOF)
//	{
	try
	{
	m_pRecordset->AddNew();
    UpdateData(TRUE);//获取文本框输入内容 @@@很重要@@@
    m_pRecordset->PutCollect("txt",_variant_t(m_Txt));
//	}
//	else
//		AfxMessageBox("指针出界，现在不能读入数据！");
// UpdateData(TRUE);//即时更新
	m_pRecordset->Update();
	AfxMessageBox("插入成功!"); 
	}
	catch(_com_error *e) 
{ 
AfxMessageBox(e->ErrorMessage()); 
} 
}

void CRMSDlg::OnButton_File_Del() 
{
	// TODO: Add your control notification handler code here
	m_pRecordset->Delete(adAffectCurrent);
	m_pRecordset->MoveNext();
    OnButton_Fileout() ;
}

void CRMSDlg::OnButton_Find() 
{
	// TODO: Add your control notification handler code here
   UpdateData(TRUE);

   if ( m_word.IsEmpty() )
   {
      MessageBox( _T( "怎么能不输入关键字呢?" ), 
                  _T( "蓝风提醒!" ), MB_OK | MB_ICONINFORMATION );
      return;
   }
   
   else if ( !m_word.Find( ' ' ) )
   {
      MessageBox( _T( "关键字前面不能有空格!" ),
                  _T( "蓝风提醒" ), MB_OK | MB_ICONINFORMATION );
      return;
   }
   else
     Search();
}

void CRMSDlg::Search()
{
//	UpdateData(TRUE);
    CString      strSQL;
	 HRESULT  hr;
	strSQL= "SELECT * FROM jpg WHERE txt like '%" + m_word + "%'";
    m_Txt="";

	hr = m_pRecordset->Open((LPCTSTR) strSQL,_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);

	   if(hr)
		
	{
		while(!m_pRecordset->adoEOF)
		{
       //  m_Txt =  m_pRecordset->GetCollect("txt").bstrVal;
		//	    vtxt = m_pRecordset->GetCollect("txt");
//	m_Txt = (LPCTSTR)(_bstr_t)vtxt;
m_Txt="测试";
		}
	}
   
}
