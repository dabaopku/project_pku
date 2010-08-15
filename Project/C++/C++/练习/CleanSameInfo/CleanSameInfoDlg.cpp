// CleanSameInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CleanSameInfo.h"
#include "CleanSameInfoDlg.h"

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


// CCleanSameInfoDlg 对话框




CCleanSameInfoDlg::CCleanSameInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCleanSameInfoDlg::IDD, pParent)
	, inFileName(_T(""))
	, outFilePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCleanSameInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_inFileName, inFileName);
	DDX_Text(pDX, IDC_outFilePath, outFilePath);
}

BEGIN_MESSAGE_MAP(CCleanSameInfoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_Open, &CCleanSameInfoDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_Zip, &CCleanSameInfoDlg::OnBnClickedZip)
	ON_BN_CLICKED(IDC_Output, &CCleanSameInfoDlg::OnBnClickedOutput)
END_MESSAGE_MAP()


// CCleanSameInfoDlg 消息处理程序

BOOL CCleanSameInfoDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCleanSameInfoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCleanSameInfoDlg::OnPaint()
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
HCURSOR CCleanSameInfoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCleanSameInfoDlg::OnBnClickedOpen()
{
	// TODO: 在此添加控件通知处理程序代码

	CFileDialog dlg(TRUE,L"txt",L"*.txt",OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT,L"文本文件;*.txt;*inf|*.txt;*.dic;*.ini");
	if(dlg.DoModal()==IDOK)
		inFileName=dlg.GetPathName();
	UpdateData(FALSE);
}

void CCleanSameInfoDlg::OnBnClickedZip()
{
	// TODO: 在此添加控件通知处理程序代码
	ifstream fin;
	ofstream fout;
	string temp;
	set<string> word;
	fin.open(inFileName,ios::in);
	while(fin>>temp)
		word.insert(temp);
	fin.close();
	fout.open(outFilePath,ios::out);
	set<string>::iterator i;
	i=word.begin();
	while(i!=word.end())
	{
		fout<<*i<<endl;
		i++;
	}
	fout.close();
	MessageBox(L"成功",L"完成!",MB_OK);
}

void TakeoutFileName(const std::string & PathName, std::string & fileName)
{
	using namespace std;
	fileName.clear();
	fileName=PathName;
	int pos1;
	int pos2;
	pos2=fileName.find('.');
	if(pos2!=std::string::npos) fileName=fileName.substr(0,pos2);
	while((pos1=fileName.find("\\"))!=std::string::npos){
		fileName=fileName.substr(pos1+1);
	}
}

int xgUnicodeToAnsi(char* mbstr, const wchar_t* wcstr, int bufsize) 
{ 
	if (bufsize == 0 && mbstr != NULL) 
		return 0; 

	int result = ::WideCharToMultiByte(CP_ACP, 0, wcstr, -1, 
		mbstr, bufsize, NULL, NULL); 
	// assert(mbstr == NULL || result <= (int)bufsize); 
	if (result > 0) 
		mbstr[result-1] = 0; 
	return result; 
}
void CCleanSameInfoDlg::OnBnClickedOutput()
{
	// TODO: 在此添加控件通知处理程序代码
	CString defaultname=L"_new";
	string  a;
	wchar_t * bb=inFileName.GetBuffer();
	inFileName.ReleaseBuffer();
	char aa[100]={0};
	xgUnicodeToAnsi(aa,bb,inFileName.GetLength()*sizeof(char));
	string b(aa);
	CString infile;
	TakeoutFileName(b,a);
	infile=a.c_str();
	defaultname=infile+defaultname;
	

	CFileDialog dlg(FALSE,L"txt",defaultname,OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT,L"所有文件|*.*");
	if(dlg.DoModal()==IDOK)
		outFilePath=dlg.GetPathName();
	UpdateData(FALSE);
}
