// ProgressStatusBar.cpp : implementation file
//

#include "stdafx.h"
#include "flashnow.h"
#include "ProgressStatusBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressStatusBar

CProgressStatusBar::CProgressStatusBar()
{
}

CProgressStatusBar::~CProgressStatusBar()
{
}


BEGIN_MESSAGE_MAP(CProgressStatusBar, CStatusBar)
//{{AFX_MSG_MAP(CProgressStatusBar)
// NOTE - the ClassWizard will add and remove mapping macros here.
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressStatusBar message handlers

void CProgressStatusBar::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	UINT ID,Style;
	int Width;
	GetPaneInfo(lpDrawItemStruct->itemID,ID,Style,Width);
	if(ID==ID_INDICATOR_LOADED)
	{
		CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);
		CRect Client(lpDrawItemStruct->rcItem);
		int Progress;
		sscanf((TCHAR *)lpDrawItemStruct->itemData,"%d",&Progress);
		CString Text=(TCHAR *)lpDrawItemStruct->itemData;
		Text+="%";
		dc.SetTextAlign(TA_CENTER);
		dc.FillSolidRect(Client.left,Client.top,(Client.Width())*Progress/100,Client.Height(),RGB(160,160,160));
		
		if(Progress)
		{
			dc.SetBkMode(TRANSPARENT);
			dc.TextOut(Client.left+Client.Width()/2,Client.top,Text);
		}
		dc.Detach();
		return;
	}
	CStatusBar::DrawItem(lpDrawItemStruct);
}
