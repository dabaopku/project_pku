// MainFrm.cpp : implementation of the CBrowserFrame class
//

#include "stdafx.h"
#include "FlashNow.h"
#include "LogoBar.h"
#include "BrowserFrame.h"
#include "ViewerFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrowserFrame

IMPLEMENT_DYNAMIC(CBrowserFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CBrowserFrame, CFrameWnd)
//{{AFX_MSG_MAP(CBrowserFrame)
ON_WM_CREATE()
ON_COMMAND(ID_VIEW_DETAILS, OnViewDetails)
ON_UPDATE_COMMAND_UI(ID_VIEW_DETAILS, OnUpdateViewDetails)
ON_COMMAND(ID_VIEW_LIST, OnViewList)
ON_UPDATE_COMMAND_UI(ID_VIEW_LIST, OnUpdateViewList)
ON_WM_CLOSE()
ON_COMMAND(ID_VIEW_HIDDEN_FILES, OnViewHiddenFiles)
ON_UPDATE_COMMAND_UI(ID_VIEW_HIDDEN_FILES, OnUpdateViewHiddenFiles)
ON_COMMAND(ID_VIEW_NEXT, OnViewNext)
ON_COMMAND(ID_VIEW_BACK, OnViewBack)
ON_UPDATE_COMMAND_UI(ID_VIEW_NEXT, OnUpdateViewNext)
ON_UPDATE_COMMAND_UI(ID_VIEW_BACK, OnUpdateViewBack)
ON_COMMAND(ID_FILE_UP, OnFileUp)
ON_UPDATE_COMMAND_UI(ID_FILE_UP, OnUpdateFileUp)
ON_COMMAND(ID_FILE_RENAME, OnFileRename)
ON_UPDATE_COMMAND_UI(ID_FILE_RENAME, OnUpdateFileRename)
ON_UPDATE_COMMAND_UI(ID_FILE_DELETE, OnUpdateFileDelete)
ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
ON_COMMAND(ID_VIEW_FLASH_ONLY, OnViewFlashOnly)
ON_UPDATE_COMMAND_UI(ID_VIEW_FLASH_ONLY, OnUpdateViewFlashOnly)
	ON_COMMAND(ID_VIEW_SMALLICON, OnViewSmallIcon)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SMALLICON, OnUpdateViewSmallIcon)
	ON_COMMAND(ID_VIEW_LARGEICON, OnViewLargeIcon)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LARGEICON, OnUpdateViewLargeIcon)
	ON_COMMAND(ID_MOVIE_VIEW, OnMovieView)
ON_COMMAND(ID_FILE_DELETE, OnFileDelete)
ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
		ID_INDICATOR_CAPS,
		ID_INDICATOR_NUM,
		ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CBrowserFrame construction/destruction

CBrowserFrame::CBrowserFrame()
{
	m_ShowHidden=FALSE;
	m_ShowFlashOnly=FALSE;
	m_Add=TRUE;
}

CBrowserFrame::~CBrowserFrame()
{
}

int CBrowserFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_ToolBar.CreateEx(this)||
		!m_ToolBar.LoadToolBar(IDR_BROWSER))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	m_ToolBar.SetDropDownButton(ID_VIEW_BACK,0);
	m_ToolBar.SetDropDownButton(ID_VIEW_NEXT,0);
	
	if (!m_StatusBar.Create(this) ||
		!m_StatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	if (!m_ReBar.Create(this) ||
		!m_ReBar.AddBar(&m_ToolBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}
	
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_ToolBar.SetBarStyle(m_ToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
	return 0;
}

BOOL CBrowserFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if(!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	cs.dwExStyle&=~WS_EX_CLIENTEDGE;
	cs.lpszClass=AfxRegisterWndClass(0,0,0,::theApp.LoadIcon(IDI_BROWSER));
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBrowserFrame diagnostics

#ifdef _DEBUG
void CBrowserFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CBrowserFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBrowserFrame message handlers


BOOL CBrowserFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	m_Splitter1.CreateStatic(this,1,2);
	m_Splitter2.CreateStatic(&m_Splitter1,2,1,WS_CHILD|WS_VISIBLE,m_Splitter1.IdFromRowCol(0,1));
	m_Splitter1.CreateView(0,0,RUNTIME_CLASS(CBrowserFolder),CSize(200,0),pContext);
	m_Splitter2.CreateView(0,0,RUNTIME_CLASS(CLogoBar),CSize(0,80),pContext);
	m_Splitter2.CreateView(1,0,RUNTIME_CLASS(CBrowserList),CSize(0,0),pContext);
	
	if(!p_Tree->SetSelection(::theApp.m_UserData.m_LastPath))
		p_Tree->SelectRootItem();
	return CFrameWnd::OnCreateClient(lpcs,pContext);
}

void CBrowserFrame::OnViewDetails() 
{
	p_List->SetViewStyle(3);
}

void CBrowserFrame::OnViewList()
{
	p_List->SetViewStyle(2);
}

void CBrowserFrame::OnUpdateViewDetails(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(p_List->GetViewStyle(3));
}

void CBrowserFrame::OnUpdateViewList(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(p_List->GetViewStyle(2));
}

void CBrowserFrame::OnClose() 
{
	CFrameWnd::OnClose();
	if(::theApp.p_Viewer)
	{
		::theApp.p_Viewer->DestroyWindow();
		::theApp.p_Viewer=NULL; 
	}
}

void CBrowserFrame::OnViewHiddenFiles() 
{
	m_ShowHidden=!m_ShowHidden;
	p_Tree->m_ShowHidden=m_ShowHidden;
	p_List->m_ShowHidden=m_ShowHidden;
	p_Tree->Refresh();
}

void CBrowserFrame::OnUpdateViewHiddenFiles(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_ShowHidden);
}

void CBrowserFrame::OnViewRefresh() 
{
	m_History.Clear();
	p_Tree->Refresh();
}

void CBrowserFrame::OnHilite()
{
	p_List->SetFocus();
	if(!::theApp.IsValidFlashIndex())
		return;
	int Index=::theApp.p_FlashIndex[::theApp.m_FlashIndex];
	if(p_List->m_SelectedItem!=Index)
		p_List->SelectItem(Index);
	else
		p_List->OnItemSelected(p_List->m_SelectedItem);
}

void CBrowserFrame::OnViewNext() 
{
	m_Add=FALSE;
	p_Tree->SelectItem(m_History.Next());
	m_Add=TRUE;
}

void CBrowserFrame::OnViewBack() 
{
	m_Add=FALSE;
	p_Tree->SelectItem(m_History.Back());
	m_Add=TRUE;
}

void CBrowserFrame::OnUpdateViewNext(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_History.TailReached());	
}

void CBrowserFrame::OnUpdateViewBack(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_History.HeadReached());	
}

BOOL CBrowserFrame::PreTranslateMessage(MSG* pMsg) 
{
	if(::theApp.m_Mode&&pMsg->message==WM_KEYUP)	
	{
		if(pMsg->wParam==VK_F5)
			OnViewRefresh();
	}
	if(pMsg->message==0x0111&&pMsg->wParam>=0xff00&&pMsg->wParam<=0xff08)	
	{
		int Index=pMsg->wParam-0xff00;
		CHistoryRecord *pRecord;
		pRecord=m_History.p_Current;
		HTREEITEM hItem=NULL;
		while(1)
		{
			pRecord=pRecord->p_Back;
			hItem=pRecord->h_Item;
			m_History.Back();
			if(!Index)
				break;
			if(m_History.IsHead(pRecord))
				break;
			Index--;
		}
		m_Add=FALSE;
		p_Tree->SelectItem(hItem);
		m_Add=TRUE;
		return TRUE;
	}
	
	if(pMsg->message==0x0111&&pMsg->wParam>=0xff10&&pMsg->wParam<=0xff18)
	{
		int Index=pMsg->wParam-0xff10;
		CHistoryRecord *pRecord;
		pRecord=m_History.p_Current;
		HTREEITEM hItem=NULL;
		while(1)
		{
			pRecord=pRecord->p_Next;
			hItem=pRecord->h_Item;
			m_History.Next();
			if(!Index)
				break;
			if(!pRecord)
				break;
			Index--;
		}
		m_Add=FALSE;
		p_Tree->SelectItem(hItem);
		m_Add=TRUE;
		return TRUE;
	}
	
	return CFrameWnd::PreTranslateMessage(pMsg);
}

void CBrowserFrame::AddHistoryRecord(HTREEITEM hItem)
{
	if(m_Add)
		m_History.Add(hItem);
}

void CBrowserFrame::OnFileUp() 
{
	p_Tree->ItemUp();
}

void CBrowserFrame::OnUpdateFileUp(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!p_Tree->RootReached());	
}

void CBrowserFrame::OnFileRename() 
{
	p_List->EditLabel(p_List->m_SelectedItem);	
}

void CBrowserFrame::OnUpdateFileRename(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_List->m_SelectedItem!=-1);	
}

void CBrowserFrame::OnFileDelete() 
{
	CString FullPath=p_List->GetSelectedItemFullPath();
	if(p_List->IsFolder(p_List->m_SelectedItem))
	{
		if(RemoveDirectory(FullPath))
			OnViewRefresh();
	}
	else
	{
		if(DeleteFile(FullPath))
			OnViewRefresh();
	}
}

void CBrowserFrame::OnUpdateFileDelete(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_List->m_SelectedItem!=-1);	
}

void CBrowserFrame::OnFileOpen() 
{
	p_List->OnItemAction(p_List->m_SelectedItem);
}

void CBrowserFrame::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(p_List->m_SelectedItem!=-1);	
}

void CBrowserFrame::OnViewFlashOnly() 
{
	m_ShowFlashOnly=!m_ShowFlashOnly;
	p_List->m_ShowFlashOnly=m_ShowFlashOnly;
	p_List->Refresh();
}

void CBrowserFrame::OnUpdateViewFlashOnly(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_ShowFlashOnly);	
}

void CBrowserFrame::OnViewSmallIcon() 
{
	p_List->SetViewStyle(1);
}

void CBrowserFrame::OnUpdateViewSmallIcon(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(p_List->GetViewStyle(1));
}

void CBrowserFrame::OnViewLargeIcon() 
{
	p_List->SetViewStyle(0);
}

void CBrowserFrame::OnUpdateViewLargeIcon(CCmdUI* pCmdUI) 
{	
	pCmdUI->SetCheck(p_List->GetViewStyle(0));
}

void CBrowserFrame::OnMovieView() 
{
	::theApp.SwitchToViewer();	
}
