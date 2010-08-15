// BrowserList.cpp : implementation file
//

#include "stdafx.h"
#include "flashnow.h"
#include "BrowserList.h"
#include "BrowserFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrowserList

IMPLEMENT_DYNCREATE(CBrowserList, CView)

CBrowserList::CBrowserList()
{
	m_FlashWidth=150;
	m_FlashHeight=150;
}

CBrowserList::~CBrowserList()
{
}


BEGIN_MESSAGE_MAP(CBrowserList, CView)
//{{AFX_MSG_MAP(CBrowserList)
ON_WM_CREATE()
ON_WM_SIZE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrowserList drawing

void CBrowserList::OnDraw(CDC* pDC)
{
	CRect Rect;
	GetClientRect(&Rect);
	
	if(Rect.Height()<LIST_HEIGHT_LIMIT)
		return;
	
	CDC MemDC; 
	MemDC.CreateCompatibleDC(pDC); 
	MemDC.SelectObject(&m_Bitmap);
	pDC->BitBlt((m_FlashWidth-m_BitmapWidth)/2+10,6,m_BitmapWidth,m_BitmapHeight,&MemDC,0,0,SRCCOPY);
	
	pDC->SelectStockObject(DEFAULT_GUI_FONT);
	MultiLineTextOut(pDC,10,80,16,m_FileInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CBrowserList diagnostics

#ifdef _DEBUG
void CBrowserList::AssertValid() const
{
	CView::AssertValid();
}

void CBrowserList::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBrowserList message handlers

int CBrowserList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_List.Create(WS_VISIBLE|WS_CHILD|TVS_HASLINES|TVS_LINESATROOT|
		TVS_HASBUTTONS|LVS_SHAREIMAGELISTS|LVS_EDITLABELS,
		CRect(0,0,0,0), this, IDR_SHELL_LIST))
	{
		TRACE0("Unable to create List view control.\n");
		return -1;
	}
	
	if (m_Preview.Create((CWnd *)this)==-1)
		return -1;
	CBrowserFrame *pFrame=(CBrowserFrame *)(GetParent()->GetParent()->GetParent());
	pFrame->p_List=&m_List;
	pFrame->p_Preview=&m_Preview;
	
	pFrame->p_Tree->AssociateList(&m_List);
	m_List.AssociateTree(pFrame->p_Tree);
	
	m_Bitmap.LoadBitmap(IDB_CAPTION);
	BITMAP Bitmap;
	m_Bitmap.GetBitmap(&Bitmap);
	m_BitmapWidth=Bitmap.bmWidth;
	m_BitmapHeight=Bitmap.bmHeight;
	
	return 0;
}

void CBrowserList::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if(cx<LIST_WIDTH_LIMIT||cy<LIST_HEIGHT_LIMIT)
	{
		if (m_Preview.GetSafeHwnd())
		{
			m_Preview.MoveWindow(0,0,0,0);
		}
		
		if (m_List.GetSafeHwnd())
		{
			m_List.MoveWindow(0,0,cx,cy);
		}
	}
	else
	{
		if (m_Preview.GetSafeHwnd())
		{
			m_Preview.MoveWindow(10,cy-m_FlashWidth-10,m_FlashWidth,m_FlashHeight);
		}
		
		if (m_List.GetSafeHwnd())
		{
			m_List.MoveWindow(m_FlashWidth+20,0,cx-m_FlashWidth-20,cy);
		}
	}
}

void CBrowserList::ShowFileInfo()
{
	CRect Rect;
	GetClientRect(&Rect);
	InvalidateRect(&CRect(0,0,Rect.Width()/3,Rect.Height()));
}

void CBrowserList::Preview(CString Movie)
{
	m_Preview.SetMovie(Movie);
	::theApp.m_MovieURL=Movie;
}

void CBrowserList::SetFileInfo(CString FileInfo)
{
	m_FileInfo=FileInfo;
	ShowFileInfo();
}
