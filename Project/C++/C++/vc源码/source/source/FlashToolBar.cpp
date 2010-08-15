// FlashToolBar.cpp: implementation of the CFlashToolBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "flashnow.h"
#include "ViewerFrame.h"
#include "FlashToolBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFlashToolBar::CFlashToolBar()
{

}

CFlashToolBar::~CFlashToolBar()
{

}

void CFlashToolBar::OnDropDownButton(UINT nID)
{
	int pos=CommandToIndex(nID);

	CRect rect;
	GetItemRect(pos,&rect);
	ClientToScreen(&rect);
	
	if(nID==ID_MOVIE_QUALITY)
	{
		CMenu Menu;
		Menu.LoadMenu(IDM_QUALITY_POP);
		CMenu* pMenu = Menu.GetSubMenu(0);
		pMenu->TrackPopupMenu(TPM_RIGHTBUTTON, rect.left, rect.bottom,::theApp.p_Viewer);
		return;
	}
	CDropDownToolBar::OnDropDownButton(nID);
	return;
}
