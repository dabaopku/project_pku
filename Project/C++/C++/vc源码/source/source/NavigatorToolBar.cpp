// NavigatorToolBar.cpp: implementation of the CNavigatorToolBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FlashNow.h"
#include "History.h"
#include "BrowserFrame.h"
#include "NavigatorToolBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNavigatorToolBar::CNavigatorToolBar()
{

}

CNavigatorToolBar::~CNavigatorToolBar()
{

}

void CNavigatorToolBar::OnDropDownButton(UINT nID)
{
	int pos=CommandToIndex(nID);

	CRect rect;
	GetItemRect(pos,&rect);
	ClientToScreen(&rect);

	if(nID==ID_VIEW_BACK)
	{	
		CMenu Menu;
		Menu.LoadMenu(IDM_NAVIGATOR_POP);
		CMenu* pMenu = Menu.GetSubMenu(0);
		pMenu->RemoveMenu(0,MF_BYPOSITION);
		CHistoryRecord *pRecord;
		CBrowserFrame *pFrame=::theApp.p_Browser;
		pRecord=pFrame->m_History.p_Current->p_Back;
		int Count=0;
		while(1)
		{
			CString FullPath=pFrame->p_Tree->GetItemText(pRecord->h_Item);
			pMenu->InsertMenu(Count,MF_BYPOSITION,0xff00+Count,FullPath);
			if(Count==8)
				break;
			if(pFrame->m_History.IsHead(pRecord))
				break;
			Count++;
			pRecord=pRecord->p_Back;
		}
		pMenu->TrackPopupMenu(TPM_RIGHTBUTTON, rect.left, rect.bottom, this);
		return;
	}
	if(nID==ID_VIEW_NEXT)
	{
		CMenu Menu;
		Menu.LoadMenu(IDM_NAVIGATOR_POP);
		CMenu* pMenu = Menu.GetSubMenu(0);
		pMenu->RemoveMenu(0,MF_BYPOSITION);
		CHistoryRecord *pRecord;
		CBrowserFrame *pFrame=::theApp.p_Browser;
		pRecord=pFrame->m_History.p_Current->p_Next;
		int Count=0;
		while(pRecord)
		{
			CString FullPath=pFrame->p_Tree->GetItemText(pRecord->h_Item);
			pMenu->InsertMenu(Count,MF_BYPOSITION,0xff10+Count,FullPath);
			if(Count==8)
				break;
			Count++;
			pRecord=pRecord->p_Next;
		}
		pMenu->TrackPopupMenu(TPM_RIGHTBUTTON, rect.left, rect.bottom, this);
		return;
	}
	CDropDownToolBar::OnDropDownButton(nID);
	return;
}
