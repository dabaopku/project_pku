// FakeQQ.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FakeQQ.h"
#include "FakeQQDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFakeQQApp

BEGIN_MESSAGE_MAP(CFakeQQApp, CWinApp)
	//{{AFX_MSG_MAP(CFakeQQApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFakeQQApp construction

CFakeQQApp::CFakeQQApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFakeQQApp object

CFakeQQApp theApp;
HICON FaceIcon[];
CUserInfo MyInfo;
CChatSocket ChatSocket;
CDatabase ChatDB;

/////////////////////////////////////////////////////////////////////////////
// CFakeQQApp initialization

BOOL CFakeQQApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	
	if(!DBReady())
		return FALSE;

	UINT nFaceID[] = {IDI_FACE0, IDI_FACE1, IDI_FACE2, IDI_FACE3, IDI_FACE4};

	for(int i = 0; i < sizeof(nFaceID)/sizeof(UINT); i++)
	{
		FaceIcon[i] = LoadIcon(nFaceID[i]);
	}

	CLoginDlg LoginDlg;
	if(LoginDlg.DoModal() == IDCANCEL)
		return FALSE;

	CFakeQQDlg dlg;
	ChatSocket.m_pDlg = &dlg;
	m_pMainWnd = &dlg;

	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.

	::ChatDB.Close();
	return FALSE;
}

bool CFakeQQApp::DBReady()
{
	TCHAR FileName[_MAX_PATH];
	GetModuleFileName(NULL, FileName, _MAX_PATH);
	CString DBFileName = FileName;
	CString DSN;
	DSN = "DSN=FakeQQ;FileType=Ms Access;DBQ=" + DBFileName + ".mdb;MaxScanRows=20";
	if(!SQLConfigDataSource(NULL, ODBC_ADD_DSN, "Microsoft Access Driver (*.mdb)", DSN))
	{
		::MessageBox(NULL,"无法创建ODBC数据源!", "错误", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	try
	{
		if(::ChatDB.Open("FakeQQ", FALSE, FALSE, "ODBC;"))
			return true;
	}
	catch(CException * e)
	{
		e->Delete();
		::MessageBox(NULL,"无法打开系统数据库!", "错误", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	return false;
}

CString GetLocalIp()
{
	struct hostent* phost;
    char ip[20];
	char hostname[50];

	gethostname(hostname,50);
	phost = gethostbyname(hostname);
	char ** names;
	names = phost->h_aliases;
	char ** iplist;
	iplist = phost->h_addr_list;
	while( * iplist)
	{
		strcpy(ip,inet_ntoa( * (struct in_addr * ) * iplist));
		iplist ++;
	}
    CString LocalIp = ip;
    return LocalIp;
}