// ViewerFrame.cpp : implementation file
//

#include "stdafx.h"
#include "flashnow.h"
#include "BrowserFrame.h"
#include "ViewerFrame.h"
#include "FileOpenDlg.h"
#include "FileOpenDlg.h"
#include "PropertyDlg.h"
#include "2HTMLDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewerFrame
static UINT indicators[] =
{
	ID_SEPARATOR,
		ID_INDICATOR_LOADED,
		ID_INDICATOR_CURRENTFRAME,
		ID_INDICATOR_FRAMES
};


IMPLEMENT_DYNCREATE(CViewerFrame, CFrameWnd)

CViewerFrame::CViewerFrame()
{
	m_Wait=FALSE;
	m_Frames=0;
	m_Progress=0;
	m_CurrentFrame=-1;
	m_FullScreen=FALSE;
}

CViewerFrame::~CViewerFrame()
{
}


BEGIN_MESSAGE_MAP(CViewerFrame, CFrameWnd)
//{{AFX_MSG_MAP(CViewerFrame)
ON_WM_CLOSE()
ON_WM_CREATE()
ON_WM_SIZE()
ON_WM_GETMINMAXINFO()
ON_COMMAND(ID_FILE_PROPERTY, OnFileProperty)
ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
ON_UPDATE_COMMAND_UI(ID_FILE_PROPERTY, OnUpdateFileProperty)
ON_UPDATE_COMMAND_UI(ID_MOVIE_FORWARD, OnUpdateMovieForward)
ON_UPDATE_COMMAND_UI(ID_FRAME_BACK, OnUpdateFrameBack)
ON_UPDATE_COMMAND_UI(ID_FRAME_END, OnUpdateFrameEnd)
ON_UPDATE_COMMAND_UI(ID_FRAME_FORWARD, OnUpdateFrameForward)
ON_UPDATE_COMMAND_UI(ID_FRAME_REWIND, OnUpdateFrameRewind)
ON_UPDATE_COMMAND_UI(ID_MOVIE_BACK, OnUpdateMovieBack)
ON_COMMAND(ID_MOVIE_FORWARD, OnMovieForward)
ON_COMMAND(ID_MOVIE_TAIL, OnMovieTail)
ON_COMMAND(ID_MOVIE_STOP, OnMovieStop)
ON_UPDATE_COMMAND_UI(ID_MOVIE_STOP, OnUpdateMovieStop)
ON_COMMAND(ID_MOVIE_PLAY, OnMoviePlay)
ON_UPDATE_COMMAND_UI(ID_MOVIE_PLAY, OnUpdateMoviePlay)
ON_COMMAND(ID_MOVIE_LOOP, OnMovieLoop)
ON_UPDATE_COMMAND_UI(ID_MOVIE_LOOP, OnUpdateMovieLoop)
ON_COMMAND(ID_MOVIE_HEAD, OnMovieHead)
ON_COMMAND(ID_MOVIE_BACK, OnMovieBack)
ON_COMMAND(ID_FRAME_REWIND, OnFrameRewind)
ON_COMMAND(ID_FRAME_FORWARD, OnFrameForward)
ON_COMMAND(ID_FRAME_END, OnFrameEnd)
ON_COMMAND(ID_FRAME_BACK, OnFrameBack)
ON_COMMAND(ID_ZOOM_IN, OnZoomIn)
ON_COMMAND(ID_ZOOM_OUT, OnZoomOut)
ON_COMMAND(ID_SHOW_ALL, OnShowAll)
ON_WM_TIMER()
ON_COMMAND(ID_EXACT_IT, OnExactIt)
ON_COMMAND(ID_END_FULL_SCREEN, OnEndFullScreen)
ON_UPDATE_COMMAND_UI(ID_FULL_SCREEN, OnUpdateFullScreen)
ON_UPDATE_COMMAND_UI(ID_ZOOM_IN, OnUpdateZoomIn)
ON_UPDATE_COMMAND_UI(ID_ZOOM_OUT, OnUpdateZoomOut)
ON_UPDATE_COMMAND_UI(ID_SHOW_ALL, OnUpdateShowAll)
ON_UPDATE_COMMAND_UI(ID_EXACT_IT, OnUpdateExactIt)
ON_COMMAND(ID_ACTUAL_SIZE, OnActualSize)
ON_UPDATE_COMMAND_UI(ID_ACTUAL_SIZE, OnUpdateActualSize)
ON_COMMAND(ID_BACK_COLOR, OnBackColor)
ON_COMMAND(ID_HIGH_QUALITY, OnHighQuality)
ON_COMMAND(ID_LOW_QUALITY, OnLowQuality)
ON_COMMAND(ID_MEDIUM_QUALITY, OnMediumQuality)
ON_UPDATE_COMMAND_UI(ID_HIGH_QUALITY, OnUpdateHighQuality)
ON_UPDATE_COMMAND_UI(ID_LOW_QUALITY, OnUpdateLowQuality)
ON_UPDATE_COMMAND_UI(ID_MEDIUM_QUALITY, OnUpdateMediumQuality)
ON_COMMAND(ID_MOVIE_QUALITY, OnMovieQuality)
ON_UPDATE_COMMAND_UI(ID_MOVIE_QUALITY, OnUpdateMovieQuality)
ON_COMMAND(ID_FILE_SAVE_NOW, OnFileSaveNow)
ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_NOW, OnUpdateFileSaveNow)
	ON_COMMAND(ID_FILE_EXPORT_FLASH, OnFileExportFlash)
	ON_UPDATE_COMMAND_UI(ID_FILE_EXPORT_FLASH, OnUpdateFileExportFlash)
	ON_COMMAND(ID_FILE_EXPORT_HTML, OnFileExportHtml)
	ON_UPDATE_COMMAND_UI(ID_FILE_EXPORT_HTML, OnUpdateFileExportHtml)
	ON_COMMAND(ID_HELP_PRODUCT, OnHelpProduct)
	ON_UPDATE_COMMAND_UI(ID_BACK_COLOR, OnUpdateBackColor)
	ON_COMMAND(ID_SLIDE_SHOW, OnSlideShow)
	ON_UPDATE_COMMAND_UI(ID_SLIDE_SHOW, OnUpdateSlideShow)
ON_COMMAND(ID_FULL_SCREEN, OnFullScreen)
	ON_COMMAND(ID_MOVIE_BROWSE, OnMovieBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewerFrame message handlers

void CViewerFrame::OnClose() 
{
	CFrameWnd::OnClose();
	if(::theApp.p_Browser)
	{
		::theApp.p_Browser->DestroyWindow();
		::theApp.p_Browser=NULL;
	}
}

BOOL CViewerFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	if(!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	
	cs.dwExStyle&=~WS_EX_CLIENTEDGE;
	cs.lpszClass=AfxRegisterWndClass(0,0,0,::theApp.LoadIcon(IDI_VIEWER));
	return TRUE;
}

int CViewerFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_View.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	
	if (!m_ToolBar.CreateEx(this) ||
		!m_ToolBar.LoadToolBar(IDR_VIEWER))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	
	if (!m_FlashToolBar.CreateEx(this) ||
		!m_FlashToolBar.LoadToolBar(IDR_FLASH))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	
	m_ToolBar.SetDropDownButton(ID_FILE_SAVE_NOW,IDM_SAVEPATH_POP);
	m_FlashToolBar.SetDropDownButton(ID_MOVIE_QUALITY,IDM_QUALITY_POP);
	
	if (!m_DlgBar.Create(this, IDD_VIEWER, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;
	}
	
	if (!m_ReBar.Create(this) ||
		!m_ReBar.AddBar(&m_ToolBar) ||
		!m_ReBar.AddBar(&m_FlashToolBar) ||
		!m_ReBar.AddBar(&m_DlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;    
	}
	if (!m_StatusBar.Create(this) ||
		!m_StatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;    
	}
	
	UINT ID,Style;
	int Pane,Width;
	Pane=m_StatusBar.CommandToIndex(ID_INDICATOR_LOADED);
	m_StatusBar.GetPaneInfo(Pane,ID,Style,Width);
	m_StatusBar.SetPaneInfo(Pane,ID,Style|SBPS_OWNERDRAW,Width);
	
	m_ToolBar.SetBarStyle(m_ToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
	
	m_FlashToolBar.SetBarStyle(m_FlashToolBar.GetBarStyle()|
		CBRS_TOOLTIPS | CBRS_FLYBY);
	
	m_DlgBar.OnInitDialog();
	return 0;
}

void CViewerFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	m_DlgBar.ResizeSlider();	
}

void CViewerFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	if(m_FullScreen)
	{
		lpMMI->ptMaxSize.x=m_FullScreenRect.Width();
		lpMMI->ptMaxSize.y=m_FullScreenRect.Height();
		lpMMI->ptMaxPosition.x=m_FullScreenRect.Width();
		lpMMI->ptMaxPosition.y=m_FullScreenRect.Height();
		
		lpMMI->ptMaxTrackSize.x=m_FullScreenRect.Width();
		lpMMI->ptMaxTrackSize.y=m_FullScreenRect.Height();
	}
	
	CRect Rect;
    GetWindowRect(&Rect);
    CRect ClientRect;
    GetClientRect(&ClientRect);
	
    int WidthOffset = Rect.Width() - ClientRect.Width();
    lpMMI->ptMinTrackSize.x = VIEWER_WIDTH_LIMIT + WidthOffset;
	
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

void CViewerFrame::OnFileProperty() 
{
	CPropertyDlg Dlg(m_Frames);
	Dlg.DoModal();
}

void CViewerFrame::OnFileOpen() 
{
	CFileOpenDlg Dlg(TRUE,NULL,"*.swf",0,"ShockwaveFlash动画文件(*.swf)|*.swf|程序文件(*.exe)|*.exe|所有文件(*.*)|*.*||");
	if(Dlg.DoModal()==IDOK)
	{
		if(::theApp.AttachFile(Dlg.GetPathName())!=-1)
			LoadMovie();
	}
}

void CViewerFrame::OnUpdateFileProperty(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_Flash->GetReadyState()==4);			
	
	ShowProgress();
	ShowFrames();
	ShowCurrentFrame(m_DlgBar.m_DragMode);
	if(!m_DlgBar.m_DragMode&&!m_Wait&&::theApp.m_UserData.m_SlideShow&&m_CurrentFrame==m_Frames-1&&::theApp.m_FlashIndex<::theApp.m_FlashCount-1)
	{
		m_Wait=TRUE;
		m_TimerID=SetTimer(800520,::theApp.m_UserData.m_Elapse,NULL);
	}
}

void CViewerFrame::OnUpdateMovieForward(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(::theApp.m_FlashIndex>=0&&::theApp.m_FlashIndex<::theApp.m_FlashCount-1);	
}

void CViewerFrame::OnUpdateMovieBack(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(::theApp.m_FlashIndex>0);	
}

void CViewerFrame::OnUpdateFrameRewind(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_Flash->GetReadyState()==4&&m_CurrentFrame>0);	
}

void CViewerFrame::OnUpdateFrameForward(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_Flash->GetReadyState()==4&&m_CurrentFrame<m_Frames);	
}

void CViewerFrame::OnUpdateFrameEnd(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_Flash->GetReadyState()==4&&m_CurrentFrame<m_Frames);	
}

void CViewerFrame::OnUpdateFrameBack(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_Flash->GetReadyState()==4&&m_CurrentFrame>0);	
}

void CViewerFrame::OnMovieForward() 
{
	if(::theApp.m_FlashIndex==::theApp.m_FlashCount-1)
		return;
	::theApp.m_FlashIndex++;
	NoWait();
	LoadMovie(FALSE);
}

void CViewerFrame::OnMovieTail() 
{
	if(::theApp.m_FlashIndex==::theApp.m_FlashCount-1)
		return;
	::theApp.m_FlashIndex=::theApp.m_FlashCount-1;
	NoWait();
	LoadMovie(FALSE);
}

void CViewerFrame::OnMovieStop() 
{
	NoWait();
	p_Flash->StopPlay();
}

void CViewerFrame::OnUpdateMovieStop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_Flash->GetReadyState()==4&&p_Flash->IsPlaying());
}

void CViewerFrame::OnMoviePlay() 
{
	NoWait();
	p_Flash->Play();
}

void CViewerFrame::OnUpdateMoviePlay(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_Flash->GetReadyState()==4&&!p_Flash->IsPlaying());
}

void CViewerFrame::OnMovieLoop() 
{
	p_Flash->SetLoop(!p_Flash->GetLoop());
}

void CViewerFrame::OnUpdateMovieLoop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(p_Flash->GetLoop());
}

void CViewerFrame::OnMovieHead() 
{
	if(!::theApp.m_FlashIndex)
		return;
	::theApp.m_FlashIndex=0;
	NoWait();
	LoadMovie(FALSE);
}

void CViewerFrame::OnMovieBack() 
{
	if(!::theApp.m_FlashIndex)
		return;
	::theApp.m_FlashIndex--;
	NoWait();
	LoadMovie(FALSE);
}

void CViewerFrame::OnFrameRewind() 
{
	NoWait();
	p_Flash->Rewind();
}

void CViewerFrame::OnFrameForward() 
{
	NoWait();
	p_Flash->Forward();
}

void CViewerFrame::OnFrameEnd() 
{
	NoWait();
	p_Flash->GotoFrame(m_Frames-1);
}

void CViewerFrame::OnFrameBack() 
{
	NoWait();
	p_Flash->Back();
}

void CViewerFrame::OnZoomIn() 
{
	p_Flash->Zoom(80);
}

void CViewerFrame::OnZoomOut() 
{
	p_Flash->Zoom(125);
}

void CViewerFrame::SetCurrentFrame(int Value)
{
	if(m_CurrentFrame==Value)
		return;
	
	BOOL Playing=p_Flash->IsPlaying();
	p_Flash->GotoFrame(Value);
	if(Playing)
		p_Flash->Play();
	
	m_CurrentFrame=Value;
	
	CString Text;
	Text.Format(" 当前帧:%5d ",Value);
	m_StatusBar.SetPaneText(2,Text);
}

void CViewerFrame::OnShowAll() 
{
	p_Flash->SetScaleMode(0);	
}

void CViewerFrame::LoadMovie(BOOL BuildFlashIndexTable)
{
	if(BuildFlashIndexTable)
		::theApp.BuildFlashIndexTable();
	CString MovieURL=::theApp.GetMovieURL();
	p_Flash->SetMovie(MovieURL);
	::theApp.SetWindowTitle(MovieURL,FALSE);
	m_DlgBar.m_List.SetWindowText(MovieURL);
}

void CViewerFrame::OnTimer(UINT nIDEvent) 
{
	OnMovieForward();
	CFrameWnd::OnTimer(nIDEvent);
}

void CViewerFrame::ShowCurrentFrame(BOOL DragMode)
{
	if(DragMode)
		return;
	int Value=p_Flash->CurrentFrame();
	if(m_CurrentFrame==Value)
		return;
	
	if(Value<0)
		Value=0;
	
	CString Text;
	Text.Format(" 当前帧:%5d ",Value);
	m_StatusBar.SetPaneText(2,Text);
	
	m_DlgBar.m_Slider.SetPos(Value);
	
	m_CurrentFrame=Value;
}

void CViewerFrame::ShowFrames()
{
	if(p_Flash->GetReadyState()!=4)
		return;
	int Value=p_Flash->GetTotalFrames();
	if(m_Frames==Value)
		return;
	
	CString Text;
	Text.Format(" 总帧数:%5d ",Value);
	m_StatusBar.SetPaneText(3,Text);
	m_DlgBar.m_Slider.SetRange(0,Value-1,FALSE);
	m_Frames=Value;
}

void CViewerFrame::ShowProgress()
{
	int Value=p_Flash->PercentLoaded();
	if(m_Progress==Value)
		return;
	
	m_Progress=Value;
	
	if(Value==100)
	{
		m_StatusBar.SetPaneText(1,"0");
		m_StatusBar.SetPaneText(0,"动画文件装载完毕");
	}
	else
	{
		CString Text;
		Text.Format("%d",Value);
		m_StatusBar.SetPaneText(1,Text);
		m_StatusBar.SetPaneText(0,"正在装载动画文件...");
	}
}

void CViewerFrame::ClearAll()
{
	m_Frames=0;
	m_Progress=0;
	m_CurrentFrame=-1;
	
	m_StatusBar.SetPaneText(0,::theApp.m_MovieURL);
	m_StatusBar.SetPaneText(1,"0");
	m_StatusBar.SetPaneText(2," 当前帧:    0 ");
	m_StatusBar.SetPaneText(3," 总帧数:    0 ");
	
	m_DlgBar.m_Slider.SetRange(0,0,TRUE);
	m_DlgBar.m_Slider.SetPos(0);
}

void CViewerFrame::NoWait()
{
	if(m_Wait)
	{
		KillTimer(m_TimerID);
		m_Wait=FALSE;
	}
}

void CViewerFrame::OnExactIt() 
{
	p_Flash->SetScaleMode(2);	
}

void CViewerFrame::OnFullScreen() 
{
	if(m_FullScreen)
		EndFullScreen();
	else
		FullScreenShow();
}

void CViewerFrame::FullScreenShow()
{
	GetWindowPlacement(&m_OldWndPlacement);
	CRect WindowRect;
	GetWindowRect(&WindowRect);
	CRect ClientRect;
	RepositionBars(0,0xffff,AFX_IDW_PANE_FIRST,reposQuery,&ClientRect);
	ClientToScreen(&ClientRect);
	
	int nFullWidth=GetSystemMetrics(SM_CXSCREEN);
	int nFullHeight=GetSystemMetrics(SM_CYSCREEN);
	m_FullScreenRect.left=WindowRect.left-ClientRect.left-1;
	m_FullScreenRect.top=WindowRect.top-ClientRect.top-1;
	m_FullScreenRect.right=WindowRect.right-ClientRect.right+nFullWidth+2;
	m_FullScreenRect.bottom=WindowRect.bottom-ClientRect.bottom+nFullHeight+2;
	m_FullScreen=TRUE; 
	
	WINDOWPLACEMENT wndpl;
	wndpl.length=sizeof(WINDOWPLACEMENT);
	wndpl.flags=0;
	wndpl.showCmd=SW_SHOWNORMAL;
	wndpl.rcNormalPosition=m_FullScreenRect;
	
	ShowWindow(SW_HIDE);
	SetWindowPlacement(&wndpl);
}

void CViewerFrame::OnEndFullScreen() 
{
	if(m_FullScreen)
		EndFullScreen();	
}

void CViewerFrame::OnUpdateFullScreen(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_Flash->GetReadyState()==4);				
}

void CViewerFrame::EndFullScreen()
{
	m_FullScreen=FALSE;
	ShowWindow(SW_HIDE);
	SetWindowPlacement(&m_OldWndPlacement);
}

void CViewerFrame::OnUpdateZoomIn(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_Flash->GetReadyState()==4);
}

void CViewerFrame::OnUpdateZoomOut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_Flash->GetReadyState()==4);
}

void CViewerFrame::OnUpdateShowAll(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_Flash->GetReadyState()==4);
}

void CViewerFrame::OnUpdateExactIt(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_Flash->GetReadyState()==4);
}

void CViewerFrame::OnActualSize() 
{
	p_Flash->Zoom(0);
}

void CViewerFrame::OnUpdateActualSize(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_Flash->GetReadyState()==4);	
}

void CViewerFrame::OnHilite()
{
	LoadMovie();
}

void CViewerFrame::OnBackColor() 
{
	CColorDialog ColorDlg(p_Flash->GetBackgroundColor());
	if(ColorDlg.DoModal()==IDOK)
		p_Flash->SetBackgroundColor(ColorDlg.GetColor());
}

void CViewerFrame::OnHighQuality() 
{
	p_Flash->SetQuality2("High");	
}

void CViewerFrame::OnLowQuality() 
{
	p_Flash->SetQuality2("Low");	
}

void CViewerFrame::OnMediumQuality() 
{
	p_Flash->SetQuality2("Medium");	
}

void CViewerFrame::OnUpdateHighQuality(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!p_Flash->GetQuality2().CollateNoCase("High"));	
}

void CViewerFrame::OnUpdateLowQuality(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!p_Flash->GetQuality2().CollateNoCase("Low"));	
}

void CViewerFrame::OnUpdateMediumQuality(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!p_Flash->GetQuality2().CollateNoCase("Medium"));	
}

void CViewerFrame::OnMovieQuality() 
{
	p_Flash->SetQuality(!p_Flash->GetQuality());
}

void CViewerFrame::OnUpdateMovieQuality(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_Flash->GetReadyState()==4);	
}

void CViewerFrame::OnFileSaveNow() 
{
	int Count=m_SavePath.GetCount();
	if(Count)
		SaveNow(m_SavePath.GetAt(Count-1));
	else
		OnFileExportFlash();
}

void CViewerFrame::OnUpdateFileSaveNow(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_Flash->GetReadyState()==4);	
}

void CViewerFrame::OnFileExportFlash() 
{
	CFileDialog Dlg(FALSE,"swf",GetFileTitleFromFileName(p_Flash->GetMovie(),FALSE)+".swf",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"ShockwaveFlash动画文件(*.swf)|*.swf|所有文件(*.*)|*.*||");
	if(Dlg.DoModal()==IDOK)
	{
		CString FullPath=Dlg.GetPathName();
		p_Flash->SaveAs(FullPath);
		m_SavePath.Add(GetFilePathFromFileName(FullPath));
	}
}

void CViewerFrame::OnUpdateFileExportFlash(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(p_Flash->GetReadyState()==4);				
}

void CViewerFrame::OnFileExportHtml()
{
	C2HtmlDlg Dlg(p_Flash,::theApp.m_UserData.m_URLMode);
	Dlg.DoModal();	
}

void CViewerFrame::OnUpdateFileExportHtml(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_Flash->GetReadyState()==4);			
}

void CViewerFrame::OnHelpProduct()
{
	theApp.LoadMovie(theApp.m_ModuleFilePath+"sample.swf");	
}

void CViewerFrame::OnUpdateBackColor(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_Flash->GetReadyState()==4);			
}

void CViewerFrame::OnSlideShow() 
{
	::theApp.m_UserData.m_SlideShow=!::theApp.m_UserData.m_SlideShow;
}

void CViewerFrame::OnUpdateSlideShow(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(::theApp.m_UserData.m_SlideShow);	
}

BOOL CViewerFrame::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==0x0111&&pMsg->wParam>=0xff20&&pMsg->wParam<=0xff24)	
	{
		int Index=pMsg->wParam-0xff20;
		SaveNow(m_SavePath.GetAt(Index));
		return TRUE;
	}
	return CFrameWnd::PreTranslateMessage(pMsg);
}

void CViewerFrame::SaveNow(CString FullPath)
{
	if(FullPath.Right(1)!='\\')
		FullPath+='\\';
	p_Flash->SaveAs(FullPath+GetFileTitleFromFileName(p_Flash->GetMovie(),FALSE)+".swf");	
	m_SavePath.Add(FullPath);
}

void CViewerFrame::OnMovieBrowse() 
{
	::theApp.SwitchToBrowser();	
}
