// ViewerClient.cpp : implementation file
//

#include "stdafx.h"
#include "FlashNow.h"
#include "ViewerFrame.h"
#include "ViewerClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewerClient

IMPLEMENT_DYNCREATE(CViewerClient, CWnd)

CViewerClient::CViewerClient()
{
}

BEGIN_MESSAGE_MAP(CViewerClient, CWnd)
//{{AFX_MSG_MAP(CViewerClient)
ON_WM_CREATE()
ON_WM_SIZE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewerClient drawing

void CViewerClient::OnDraw(CDC* pDC)
{
}

/////////////////////////////////////////////////////////////////////////////
// CViewerClient diagnostics

#ifdef _DEBUG
void CViewerClient::AssertValid() const
{
	CWnd::AssertValid();
}

void CViewerClient::Dump(CDumpContext& dc) const
{
	CWnd::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewerClient message handlers

int CViewerClient::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (m_Flash.Create((CWnd *)this)==-1)
		return -1;
	CViewerFrame *p_Frame=(CViewerFrame *)GetParent();
	p_Frame->p_Flash=&m_Flash;
	
	return 0;
}

BOOL CViewerClient::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.dwExStyle|=WS_EX_CLIENTEDGE;
	cs.style&=~WS_BORDER;
	
	return CWnd::PreCreateWindow(cs);
}

void CViewerClient::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	if(m_Flash.GetSafeHwnd())	
		m_Flash.MoveWindow(0,0,cx,cy);
}

BOOL CViewerClient::PreTranslateMessage(MSG* pMsg) 
{
	if(::theApp.m_UserData.m_DoubleClick&&pMsg->message==WM_LBUTTONDBLCLK)
	{
		((CViewerFrame *)GetParent())->OnFullScreen();
	}
	return CWnd::PreTranslateMessage(pMsg);
}
