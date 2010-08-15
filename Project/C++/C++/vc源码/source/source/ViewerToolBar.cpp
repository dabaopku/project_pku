// ViewerToolBar.cpp: implementation of the CViewerToolBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "History.h"
#include "FlashNow.h"
#include "ViewerFrame.h"
#include "ViewerToolBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CViewerToolBar::CViewerToolBar()
{

}

CViewerToolBar::~CViewerToolBar()
{

}

void CViewerToolBar::OnDropDownButton(UINT nID)
{
	int pos=CommandToIndex(nID);

	CRect rect;
	GetItemRect(pos,&rect);
	ClientToScreen(&rect);

	if(nID==ID_FILE_SAVE_NOW)
	{	
		CMenu Menu;
		Menu.LoadMenu(IDM_SAVEPATH_POP);
		CMenu* pMenu = Menu.GetSubMenu(0);
		CStringQueue *pList=&(::theApp.p_Viewer->m_SavePath);
		int Count=pList->GetCount();
		if(Count)
		{
			for(int i=0;i<Count;i++)
			{
				pMenu->InsertMenu(0,MF_BYPOSITION,0xff20+i,pList->GetAt(i));
			}
		}
		else
			pMenu->RemoveMenu(0,MF_BYPOSITION);
		pMenu->TrackPopupMenu(TPM_RIGHTBUTTON, rect.left, rect.bottom, this);
		return;
	}
}
