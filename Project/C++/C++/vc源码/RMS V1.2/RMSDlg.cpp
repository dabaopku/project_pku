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

extern CRMSApp theApp;//�����ⲿȫ�ֱ��� @@@����ϰ��@@@

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
			strAboutMenu = _T( "�������� ͼ����Դ�������!" );
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		    pSysMenu->DeleteMenu( 4, MF_BYPOSITION );// ɾ���������
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
    try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");//������¼��ʵ��
		m_pRecordset->Open("SELECT * FROM jpg ORDER BY id",_variant_t((IDispatch*)theApp.m_pConnection,true),adOpenStatic,adLockOptimistic,adCmdText);//�򿪼�¼��
//	    m_pRecordset->MoveFirst;
	}
	catch(_com_error e)
	{
		AfxMessageBox("��ȡ���ݿ�ʧ��!");
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
exit(0);//�˳�����Ӧ�ó����̣߳�   
//	CDialog::OnOK();//�˳��Ի���
//OnCancel();  // ���̣߳�
m_pRecordset->Update();
m_pRecordset->Close();
}

void CRMSDlg::OnButton_in() //�ӿ�����ȡ����ʾ
{
	// TODO: Add your control notification handler code here
	try
	{
		// "pic" ���ֶ��������ֶα����� OLE ����
		long nSize = m_pRecordset->GetFields()->GetItem("pic")->ActualSize;	// ��ȡ�ֶ� "pic" �ĵ�ǰ��Ԫ�Ĵ�С���ڷ����ڴ�ռ�ʱҪ�õ���	
		if(nSize > 0)
		{
			_variant_t varBLOB;
			varBLOB = m_pRecordset->GetFields()->GetItem("pic")->GetChunk(nSize);// ��ȡ OLE ���� --> varBLOB

			if(varBLOB.vt == (VT_ARRAY | VT_UI1))
			{
				if(BYTE *pBuffer = new BYTE [nSize+1])		// �����Ҫ�Ĵ洢�ռ�
				{	
					void* pBuf = NULL;

					SafeArrayAccessData(varBLOB.parray,(void**)&pBuf);
					memcpy(pBuffer,pBuf,nSize);				// �������ݵ������� pBuffer
					SafeArrayUnaccessData (varBLOB.parray);

					// SafeArrayAccessData() �������Ǹ� varBLOB ����һ�� void ��ָ��
					// ��Ϊ memcpy �ĵڶ�������ֻ���� void ��ָ��

					// ��ȡͼ��
					if(m_Pic.m_IPicture != NULL) m_Pic.FreePictureData();
					m_Pic.LoadPictureData(pBuffer, nSize);
					delete [] pBuffer;
					pBuf=0;
					 
					// ��ʾͼ��
				    CStatic *pStaic;
                    pStaic=(CStatic*)GetDlgItem(IDC_IMAGE);//ָ��ͼƬ��ҪҪ��ʾ������
                   // memDC.CreateCompatibleDC(GetDC());
                    pStaic->GetClientRect(&rect);//�õ�ָ������

                    CClientDC dc(pStaic); //�����ʼ���豸����

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

void CRMSDlg::OnButton_out() //����Ⲣ��ʾ
{
	// TODO: Add your control notification handler code here
	CFile f;
	CString  FilePathName;
	CFileException e;
    
	CFileDialog dlg(TRUE,NULL,NULL,0,"jpg Files (*.jpg)|*.jpg||",this); //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
	if(dlg.DoModal()==IDOK)
	{
		FilePathName=dlg.GetPathName();

		if(f.Open(FilePathName, CFile::modeRead | CFile::typeBinary, &e)) //��ָ����jpg�ļ�
		{
			int nSize = f.GetLength();          //�ȵõ� jpg �ļ�����
			BYTE* pBuffer = new BYTE [nSize];   //���ļ��Ĵ�С�ڶ�������һ���ڴ� pBuffer
	 
			if (f.Read(pBuffer, nSize) > 0 )    //�� jpg �ļ����� pBuffer
			{
				//��pBuffer���jpg���ݷŵ�����
				BYTE* pBuf = pBuffer;			
				VARIANT			varBLOB;		
				SAFEARRAY		*psa;
			    SAFEARRAYBOUND	rgsabound[1];
				
			//	m_pRecordset->AddNew();			//���һ���¼�¼
				 OnButton_File_In();//�����ļ�	
			
				if(pBuf)
				{    
					rgsabound[0].lLbound = 0;
					rgsabound[0].cElements = nSize;

					psa = SafeArrayCreate(VT_UI1, 1, rgsabound); // ���� SAFEARRAY ���� psa
					for (long i = 0; i < (long)nSize; i++)
						SafeArrayPutElement (psa, &i, pBuf++);	 // �� bBuf ָ��Ķ���������
																 // ���浽 psa ��

					varBLOB.vt = VT_ARRAY | VT_UI1;	// �� varBLOB ������Ϊ BYTE ��������
					varBLOB.parray = psa;			// ���� psa �� varBLOB

					
					m_pRecordset->GetFields()->GetItem("pic")->AppendChunk(varBLOB);//��� varBLOB �����ݿ�
				}            
				// �������ݿ�
				m_pRecordset->Update();

				// ��ȡͼ��
				if(m_Pic.m_IPicture != NULL) m_Pic.FreePictureData();
				m_Pic.LoadPictureData(pBuffer, nSize);
				delete [] pBuffer;
				pBuf=0;                //��ָ��ָ��0
			}
			f.Close();
             
		}
                   
		// ��ʾͼ��
	            	CStatic *pStaic;
                    pStaic=(CStatic*)GetDlgItem(IDC_IMAGE);//ָ��ͼƬ��ҪҪ��ʾ������
                   // memDC.CreateCompatibleDC(GetDC());
                    pStaic->GetClientRect(&rect);//�õ�ָ������

                    CClientDC dc(pStaic); //�����ʼ���豸����

					m_Pic.UpdateSizeOnDC(&dc); // Allocate memory for m_Pic
					m_Pic.Show(&dc,CRect(0,0,188,190));
					OnButton_Fileout();
	}	
}

void CRMSDlg::OnButton_pre() 
{
	// TODO: Add your control notification handler code here
	try{
		m_pRecordset->MovePrevious();	//��һ����¼
		OnButton_in();
		OnButton_Fileout();
	}
	catch (_com_error e) 
	{
	}

	if(m_pRecordset->BOF)				//����������ʾ���˵�һ����¼֮ǰ
	{
		m_pRecordset->MoveNext(); 
	    AfxMessageBox("���Ѿ��ǵ�һ����¼�� ��");
	}
	//	m_pRecordset->MoveNext();		//��һ����¼֮ǰû���κ����ݣ�����ǰ��һ����¼

}

void CRMSDlg::OnButton_next() 
{
	// TODO: Add your control notification handler code here
	try{
		m_pRecordset->MoveNext();       //��һ����¼
		OnButton_in();
		OnButton_Fileout();
	}
	catch (_com_error e) 
	{
	}

	if(m_pRecordset->adoEOF)			//����������ʾ�������һ����¼֮��
	{
		m_pRecordset->MovePrevious();
		AfxMessageBox("�����һ����¼�� ��");
	}
	//	m_pRecordset->MovePrevious();	//���һ����¼֮��û���κ����ݣ����Ժ���һ����¼
}

void CRMSDlg::OnButton_del() 
{
	// TODO: Add your control notification handler code here
	m_pRecordset->Delete(adAffectCurrent);	// ɾ����ǰ�м�¼
	m_pRecordset->Update();
	OnButton_next();
	OnButton_in();
}

void CRMSDlg::OnButton_Fileout() 
{
	// TODO: Add your control notification handler code here
//	m_pRecordset->Move(m_nCurrentSel,_variant_t((long)adBookmarkFirst));
    vtxt = m_pRecordset->GetCollect("txt");
	m_Txt = (LPCTSTR)(_bstr_t)vtxt;//vtxt.lVal;Ϊ���� ����ʱҪ�ã�long��ǿ��ת��/ bstrValΪ�ַ�
 //  m_Txt = m_pRecordset->GetCollect("txt").bstrVal;
  // m_Old.Format("%d",m_pRecordset->GetCollect("old").lVal);// m_Old Ϊlong��
	//m_pRecordset->PutCollect("old",atol(m_Old));
	UpdateData(FALSE);//�´β�����Ч
}

void CRMSDlg::OnButton_File_In() 
{
	// TODO: Add your control notification handler code here
//	if(!m_pRecordset->adoEOF && !m_pRecordset->BOF)
//	{
	try
	{
	m_pRecordset->AddNew();
    UpdateData(TRUE);//��ȡ�ı����������� @@@����Ҫ@@@
    m_pRecordset->PutCollect("txt",_variant_t(m_Txt));
//	}
//	else
//		AfxMessageBox("ָ����磬���ڲ��ܶ������ݣ�");
// UpdateData(TRUE);//��ʱ����
	m_pRecordset->Update();
	AfxMessageBox("����ɹ�!"); 
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
      MessageBox( _T( "��ô�ܲ�����ؼ�����?" ), 
                  _T( "��������!" ), MB_OK | MB_ICONINFORMATION );
      return;
   }
   
   else if ( !m_word.Find( ' ' ) )
   {
      MessageBox( _T( "�ؼ���ǰ�治���пո�!" ),
                  _T( "��������" ), MB_OK | MB_ICONINFORMATION );
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
m_Txt="����";
		}
	}
   
}
