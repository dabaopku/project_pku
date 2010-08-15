// LogoBar.cpp : implementation file
//

#include "stdafx.h"
#include "flashnow.h"
#include "LogoBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogoBar

IMPLEMENT_DYNCREATE(CLogoBar, CView)

CLogoBar::CLogoBar()
{
}

CLogoBar::~CLogoBar()
{
}


BEGIN_MESSAGE_MAP(CLogoBar, CView)
//{{AFX_MSG_MAP(CLogoBar)
ON_WM_CREATE()
ON_WM_SIZE()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogoBar drawing

void CLogoBar::OnDraw(CDC* pDC)
{
}

/////////////////////////////////////////////////////////////////////////////
// CLogoBar diagnostics

#ifdef _DEBUG
void CLogoBar::AssertValid() const
{
	CView::AssertValid();
}

void CLogoBar::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLogoBar message handlers

int CLogoBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (m_Logo.Create((CWnd *)this,WS_CHILD|WS_BORDER|WS_VISIBLE)==-1)
		return -1;	
	
	CString m_Movie;
	m_Movie.LoadString(IDS_LOGO_URL);
	m_Logo.SetMovie(m_Movie);
	m_Logo.SetMenu(FALSE);
	return 0;
}

void CLogoBar::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	if (m_Logo.GetSafeHwnd())
	{
		m_Logo.MoveWindow(20,10,cx-40,cy-20);
	}	
}
