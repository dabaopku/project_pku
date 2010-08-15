// FlashNow.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "FlashNow.h"
#include "SetUpDlg.h"

#include "ViewerFrame.h"
#include "BrowserFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlashNowApp

BEGIN_MESSAGE_MAP(CFlashNowApp, CWinApp)
//{{AFX_MSG_MAP(CFlashNowApp)
ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
ON_COMMAND(ID_SEND_SUGGESTION, OnSendSuggestion)
ON_COMMAND(ID_TOOL_SETUP, OnToolSetup)
ON_COMMAND(ID_OCX_REGISTER, OnOcxRegister)
ON_COMMAND(ID_HELP_MANUAL, OnHelpManual)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlashNowApp construction

CFlashNowApp::CFlashNowApp()
{
    p_FlashIndex=NULL;
    
    p_Browser=NULL;
    p_Viewer=NULL;
    
    TCHAR FileName[_MAX_PATH];
    GetModuleFileName(NULL,FileName,_MAX_PATH);
    m_ModuleFileName=FileName;
    
    m_ModuleFilePath=GetFilePathFromFileName(m_ModuleFileName);
}

CFlashNowApp::~CFlashNowApp()
{
    if(p_FlashIndex)
        delete [] p_FlashIndex;
}
/////////////////////////////////////////////////////////////////////////////
// The one and only CFlashNowApp object

CFlashNowApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFlashNowApp initialization

BOOL CFlashNowApp::InitInstance()
{
    CheckFlashOCX();
    if(!m_FlashOCX.m_Registered)
        return FALSE;
    
    AfxEnableControlContainer();
    
    if(::theApp.m_UserData.m_ShowAbout)
        OnAppAbout();
    
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);
    TCHAR *cp=m_lpCmdLine;
    
    CString FullPath;
    
    if(!m_UserData.m_RunTimes)
        FullPath=m_ModuleFilePath+"sample.swf";
    else
        FullPath=cmdInfo.m_strFileName;
    
    m_Mode=BROWSER;
    if(!FullPath.IsEmpty())
    {
        if(*cp=='-')
        {
            cp++;
            if(*cp=='b'||*cp=='B')
                m_UserData.m_LastPath=FullPath;
        }
        else
            m_Mode=VIEWER;
    }
    
    m_Title[0].LoadString(IDR_VIEWER);
    m_Title[1].LoadString(IDR_BROWSER);
    
#ifdef _AFXDLL
    Enable3dControls();			// Call this when using MFC in a shared DLL
#else
    Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
    
    //创建浏览视图
    p_Browser=new CBrowserFrame;
    m_pMainWnd=p_Browser;
    p_Browser->LoadFrame(IDR_BROWSER,WS_OVERLAPPEDWINDOW|FWS_ADDTOTITLE,NULL,NULL);
    
    //创建查看视图
    p_Viewer=new CViewerFrame;
    m_pMainWnd=p_Viewer;
    p_Viewer->LoadFrame(IDR_VIEWER,WS_OVERLAPPEDWINDOW|FWS_ADDTOTITLE,NULL,NULL);
    
    if(!m_Mode)
    {
        LoadMovie(FullPath);
        p_Viewer->ShowWindow(SW_SHOWMAXIMIZED);
        p_Viewer->UpdateWindow();
    }
    else
    {
        p_Browser->ShowWindow(SW_SHOWMAXIMIZED);
        p_Browser->UpdateWindow();
    }
    return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CFlashNowApp message handlers

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CWnd m_Container;
    CAboutDlg();
    CFlashWnd m_About;
    // Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    BOOL	m_ShowAbout;
    //}}AFX_DATA
    
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL
    
    // Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    m_ShowAbout = ::theApp.m_UserData.m_ShowAbout;
    //}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
ON_WM_DESTROY()
ON_WM_LBUTTONUP()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    DDX_Check(pDX, IDC_SHOW_ABOUT, m_ShowAbout);
    //}}AFX_DATA_MAP
}

// App command to run the dialog
void CFlashNowApp::OnAppAbout()
{
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CFlashNowApp message handlers

void CFlashNowApp::LoadMovie(CString URL)
{
    AttachFile(URL);
    p_Viewer->LoadMovie();
}

//切换至浏览视图
void CFlashNowApp::SwitchToBrowser()
{
    //设置窗口大小
    p_Viewer->GetWindowPlacement(&m_Placement);
    p_Viewer->p_Flash->SetMovie("");
    p_Browser->SetWindowPlacement(&m_Placement);
    //显示浏览视图，隐藏查看视图
    p_Browser->ShowWindow(SW_SHOW);
    p_Viewer->ShowWindow(SW_HIDE);
    m_pMainWnd=p_Browser;
    m_Mode=BROWSER;
    
    p_Browser->OnHilite();
}

void CFlashNowApp::SwitchToViewer()
{
    p_Browser->GetWindowPlacement(&m_Placement);
    p_Browser->p_Preview->SetMovie("");
    
    p_Viewer->SetWindowPlacement(&m_Placement);
    p_Viewer->ShowWindow(SW_SHOW);
    p_Browser->ShowWindow(SW_HIDE);
    m_pMainWnd=p_Viewer;
    m_Mode=VIEWER;
    
    p_Viewer->OnHilite();
}

CUserData::CUserData()
{
    m_Elapse=5000;
    m_RunTimes=0;
    m_Loop=TRUE;
    m_URLMode=TRUE;
    m_DoubleClick=TRUE;
    m_SlideShow=TRUE;
    m_ShowAbout=TRUE;
    
    DWORD Size=80;
    TCHAR Values[_MAX_PATH];
    CRegKey RegKey;
    
    if(RegKey.Open(HKEY_LOCAL_MACHINE,"Software\\BlueJoe\\FlashNow")!=ERROR_SUCCESS)
        return;
    if(RegKey.QueryValue(Values,"Values",&Size)==ERROR_SUCCESS)
        sscanf(Values,"%d %d %d %d %d %d %d",&m_DoubleClick,&m_Loop,&m_URLMode,&m_SlideShow,&m_ShowAbout,&m_Elapse,&m_RunTimes);
    
    Size=_MAX_PATH;
    if(RegKey.QueryValue(Values,"LastPath",&Size)==ERROR_SUCCESS)
        m_LastPath=Values;
    
    Size=2000;
    if(RegKey.QueryValue(m_SavePath,"SavePath",&Size)!=ERROR_SUCCESS)
        m_SavePath[0]='\0';
    
    Size=6000;
    if(RegKey.QueryValue(m_TypedURLs,"TypedURLs",&Size)!=ERROR_SUCCESS)
        m_TypedURLs[0]='\0';
}

CUserData::~CUserData()
{
    TCHAR Values[_MAX_PATH];
    CRegKey RegKey;
    m_RunTimes++;
    sprintf(Values,"%d %d %d %d %d %d %d",m_DoubleClick,m_Loop,m_URLMode,m_SlideShow,m_ShowAbout,m_Elapse,m_RunTimes);
    RegKey.SetValue(HKEY_LOCAL_MACHINE,
        "Software\\BlueJoe\\FlashNow",Values,"Values");
    RegKey.SetValue(HKEY_LOCAL_MACHINE,
        "Software\\BlueJoe\\FlashNow",m_LastPath,"LastPath");
    RegKey.SetValue(HKEY_LOCAL_MACHINE,
        "Software\\BlueJoe\\FlashNow",m_SavePath,"SavePath");
    RegKey.SetValue(HKEY_LOCAL_MACHINE,
        "Software\\BlueJoe\\FlashNow",m_TypedURLs,"TypedURLs");
}

CWnd* CFlashNowApp::GetMainWnd() 
{
    return m_Mode?(CWnd *)p_Browser:(CWnd *)p_Viewer;
}

void CFlashNowApp::SetWindowTitle(CString Title,BOOL BrowserMode)
{
    CWnd *pWnd;
    if(BrowserMode)
        pWnd=p_Browser;
    else
        pWnd=p_Viewer;
    pWnd->SetWindowText(Title.IsEmpty()?m_Title[m_Mode]:m_Title[m_Mode]+" - "+Title);
}

BOOL CAboutDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    CWnd *pWnd=GetDlgItem(IDC_CONTAINER);
    m_Container.Attach(pWnd->m_hWnd);
    
    if (m_About.Create(&m_Container)==-1)
        return FALSE;
    
    m_About.SetMovie(::theApp.m_ModuleFilePath+"flashnow.swf");
    m_About.SetMenu(FALSE);
    SetWindowText("FlashNow!");
    return TRUE;
}

int CFlashNowApp::ExitInstance() 
{
    return CWinApp::ExitInstance();
}

int CFlashNowApp::AttachFile(CString FileName)
{
    m_MovieURL=FileName;
    
    if(!AttachFolder(GetFilePathFromFileName(FileName)))
    {
        p_Browser->p_List->m_SelectedItem=-1;
        return -1;
    }
    
    return p_Browser->p_List->SetSelection(FileName);
}

int CFlashNowApp::AttachFolder(CString Path)
{
    if(!p_Browser->p_Tree->SetSelection(Path,TRUE))
        return 0;
    return p_Browser->p_List->GetItemCount();
}

void CFlashNowApp::OnSendSuggestion() 
{
    ShellExecute(NULL,"open","mailto:bluejoe@sdb.ac.cn?subject=Suggestion On FlashNow 1.05.20",NULL,NULL,SW_SHOW);	
}

CDocument* CFlashNowApp::OpenDocumentFile(LPCTSTR lpszFileName) 
{
    AttachFile(lpszFileName);
    return CWinApp::OpenDocumentFile(lpszFileName);
}

void CAboutDlg::OnDestroy() 
{
    UpdateData(true);
    m_Container.Detach();
    ::theApp.m_UserData.m_ShowAbout = m_ShowAbout;
    CDialog::OnDestroy();
}

CString CFlashNowApp::GetMovieURL()
{
    if(m_FlashIndex==-1)
        return m_MovieURL;
    
    int Which=p_FlashIndex[m_FlashIndex];
    m_MovieURL=p_Browser->p_List->GetItemFullPath(Which);	
    return m_MovieURL;
}

BOOL CFlashNowApp::IsValidFlashIndex()
{
    return(m_FlashIndex>=0&&m_FlashIndex<m_FlashCount);
}

void CFlashNowApp::BuildFlashIndexTable()
{
    m_FlashIndex=-1;
    m_FlashCount=0;
    
    if(p_Browser->p_List->m_SelectedItem==-1)
        return;
    
    if(p_FlashIndex)
        delete [] p_FlashIndex;
    
    p_FlashIndex=new int[p_Browser->p_List->GetItemCount()];
    
    m_FlashCount=0;
    for(int i=0;i<p_Browser->p_List->GetItemCount();i++)
    {
        if(p_Browser->p_List->IsMovie(i))
        {
            p_FlashIndex[m_FlashCount++]=i;
        }
    }
    
    for(i=0;i<m_FlashCount;i++)
    {
        if(p_FlashIndex[i]<=p_Browser->p_List->m_SelectedItem)
            m_FlashIndex=i;
        else
            break;
    }
    
    if(m_FlashIndex<0&&m_FlashCount)
        m_FlashIndex=0;
}

void CFlashNowApp::OnToolSetup() 
{
    CSetupDlg Dlg;
    Dlg.DoModal();	
}

void CFlashNowApp::OnOcxRegister() 
{
    CString	Warning="此操作将安装SWFlash控件中文版，是否确定？";
    if(MessageBox(NULL,Warning,"警告",MB_YESNO|MB_ICONQUESTION)==IDYES)
        m_FlashOCX.Register();
}

void CFlashNowApp::CheckFlashOCX()
{
    CString Warning;
    if(!m_FlashOCX.m_Registered)
    {
        Warning="你的机器没有安装SWFlash控件，FlashNow! 动画浏览器将不能正确运行。";
    }
    else
    {
        if(!m_UserData.m_RunTimes&&!m_FlashOCX.IsChineseVersion())
            Warning="FlashNow! 带有SWFlash控件中文版，提供全中文控件菜单界面。";
        else
            return;
    }
    Warning+="\n是否现在安装SWFlash控件中文版？";
    if(MessageBox(NULL,Warning,"警告",MB_YESNO|MB_ICONQUESTION)==IDYES)
        m_FlashOCX.Register();
}

void CAboutDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
    OnCancel();	
    CDialog::OnLButtonUp(nFlags, point);
}

void CFlashNowApp::OnHelpManual() 
{
    ShellExecute(NULL,"open",theApp.m_ModuleFilePath + "flashnow.chm",NULL,NULL,SW_SHOW);	
}
