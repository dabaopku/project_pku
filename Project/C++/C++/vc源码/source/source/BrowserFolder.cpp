// BrowserFolder.cpp : implementation file
//

#include "stdafx.h"
#include "flashnow.h"
#include "BrowserFrame.h"
#include "BrowserFolder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrowserFolder

IMPLEMENT_DYNCREATE(CBrowserFolder, CView)

CBrowserFolder::CBrowserFolder()
{
}

CBrowserFolder::~CBrowserFolder()
{
}


BEGIN_MESSAGE_MAP(CBrowserFolder, CView)
//{{AFX_MSG_MAP(CBrowserFolder)
ON_WM_CREATE()
ON_WM_SIZE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrowserFolder drawing

void CBrowserFolder::OnDraw(CDC* pDC)
{
}

/////////////////////////////////////////////////////////////////////////////
// CBrowserFolder diagnostics

#ifdef _DEBUG
void CBrowserFolder::AssertValid() const
{
	CView::AssertValid();
}

void CBrowserFolder::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBrowserFolder message handlers

int CBrowserFolder::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_Tree.Create(WS_VISIBLE|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS,CRect(0,0,0,0),this,IDR_SHELL_TREE))
	{
		TRACE0("Unable to create tree view control.\n");
		return -1;
	}
	
	CBrowserFrame *pFrame=(CBrowserFrame *)(GetParent()->GetParent());
	pFrame->p_Tree=&m_Tree;
	
	return 0;
}

void CBrowserFolder::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	if(m_Tree.GetSafeHwnd())
		m_Tree.MoveWindow(0,0,cx,cy);
}
