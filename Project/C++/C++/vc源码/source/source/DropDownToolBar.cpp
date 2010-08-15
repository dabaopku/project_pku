// DropDownToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "flashnow.h"
#include "DropDownToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDropDownToolBar

CDropDownToolBar::CDropDownToolBar()
{
	p_MenuID=NULL;
}

CDropDownToolBar::~CDropDownToolBar()
{
	if(p_MenuID)
		delete [] p_MenuID;
}


BEGIN_MESSAGE_MAP(CDropDownToolBar, CToolBar)
	//{{AFX_MSG_MAP(CDropDownToolBar)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_NOTIFY_REFLECT(TBN_DROPDOWN,OnDropDown)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDropDownToolBar message handlers

BOOL CDropDownToolBar::LoadToolBar(UINT nID)
{
	if(!CToolBar::LoadToolBar(nID))
			return FALSE;
	p_MenuID=new UINT [GetCount()];
	for(int i=0;i<GetCount();i++)
		p_MenuID[i]=0;
	return TRUE;
}

void CDropDownToolBar::SetDropDownButton(UINT nID, UINT nMenuID)
{
	int pos=CommandToIndex(nID);
	
	int iImage;
	UINT nStyle;
	
	p_MenuID[pos]=nMenuID;
	GetButtonInfo(pos,nID,nStyle,iImage);
	SetButtonInfo(pos,nID,nStyle|TBSTYLE_DROPDOWN,iImage);

	SendMessage(TB_SETEXTENDEDSTYLE,0,TBSTYLE_EX_DRAWDDARROWS);
}

void CDropDownToolBar::OnDropDown(LPNMTOOLBAR lpnmtb, LRESULT *result)
{
	OnDropDownButton(lpnmtb->iItem);
	*result=TBDDRET_DEFAULT;
}

void CDropDownToolBar::OnDropDownButton(UINT nID)
{
	int pos=CommandToIndex(nID);
	if(!p_MenuID[pos])
		return;

	CRect rect;
	GetItemRect(pos,&rect);
	ClientToScreen(&rect);
	
	CMenu Menu;
	Menu.LoadMenu(p_MenuID[pos]);
	CMenu* pMenu = Menu.GetSubMenu(0);
	pMenu->TrackPopupMenu(TPM_RIGHTBUTTON, rect.left, rect.bottom, this);
}
