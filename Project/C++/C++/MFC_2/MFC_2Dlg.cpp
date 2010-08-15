// MFC_2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_2.h"
#include "MFC_2Dlg.h"

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


// CMFC_2Dlg �Ի���




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


// CMFC_2Dlg ��Ϣ�������

BOOL CMFC_2Dlg::OnInitDialog()
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

	// ��ʼ������
	//������
	m_oSalarySlider.SetRangeMin(0);
	m_oSalarySlider.SetRangeMax(10000);
	m_oSalarySlider.SetPos(800);

	//��н
	SetDlgItemInt(IDC_EDIT_salary,800);
	
	//��Ͽ�
#define  Max_Combox_Size	100//��Ͽ�ߴ�

	WINDOWPLACEMENT wp;
	m_oJobCombox.GetWindowPlacement(&wp);
	m_oJobCombox.MoveWindow(
		wp.rcNormalPosition.left,wp.rcNormalPosition.top,
		wp.rcNormalPosition.right-wp.rcNormalPosition.left,
		wp.rcNormalPosition.bottom+Max_Combox_Size);
	m_oJobCombox.AddString(_T("Ӫ��Ա"));
	m_oJobCombox.AddString(_T("ҵ��Ա"));
	m_oJobCombox.AddString(_T("�ͻ�Ա"));
	m_oJobCombox.AddString(_T("�ɹ�Ա"));
	m_oJobCombox.AddString(_T("���Ա"));
	m_oJobCombox.AddString(_T("����"));
	m_oJobCombox.AddString(_T("����"));
	m_oJobCombox.SetCurSel(0);



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFC_2Dlg::OnPaint()
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
HCURSOR CMFC_2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFC_2Dlg::OnLbnSelchangeList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	wsprintf(record,L"%s  %s  %s  ��н %d  ְ�� :%s",info.name,info.sex?L"��":L"Ů",info.marriage?L"�ѻ�":L"δ��",info.salary,GetInfJob(info.job)); 

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
	// ������
	if(nSBCode==TB_THUMBTRACK){
		SetDlgItemInt(IDC_EDIT_salary,m_oSalarySlider.GetPos());
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
