// CleanSameInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CleanSameInfo.h"
#include "CleanSameInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCleanSameInfoDlg �Ի���




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


// CCleanSameInfoDlg ��Ϣ�������

BOOL CCleanSameInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCleanSameInfoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCleanSameInfoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCleanSameInfoDlg::OnBnClickedOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CFileDialog dlg(TRUE,L"txt",L"*.txt",OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT,L"�ı��ļ�;*.txt;*inf|*.txt;*.dic;*.ini");
	if(dlg.DoModal()==IDOK)
		inFileName=dlg.GetPathName();
	UpdateData(FALSE);
}

void CCleanSameInfoDlg::OnBnClickedZip()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	MessageBox(L"�ɹ�",L"���!",MB_OK);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	

	CFileDialog dlg(FALSE,L"txt",defaultname,OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT,L"�����ļ�|*.*");
	if(dlg.DoModal()==IDOK)
		outFilePath=dlg.GetPathName();
	UpdateData(FALSE);
}
