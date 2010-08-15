// QiuXpEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Calculator.h"
#include "QiuXpEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQiuXpEdit

CQiuXpEdit::CQiuXpEdit()
{
}

CQiuXpEdit::~CQiuXpEdit()
{
}


BEGIN_MESSAGE_MAP(CQiuXpEdit, CEdit)
	//{{AFX_MSG_MAP(CQiuXpEdit)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQiuXpEdit message handlers

void CQiuXpEdit::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetWindowRect(rect);
	rect.left += 1;
	rect.right -= 1;
	rect.top += 1;
	rect.bottom -= 1;

	ScreenToClient(rect);
	dc.Draw3dRect(rect, RGB(0, 0, 255), RGB(0, 0, 255));
	Invalidate();
	Default();
}

