// ViewerToolBar.h: interface for the CViewerToolBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEWERTOOLBAR_H__28053453_8DE7_41D2_A975_746379DB9E34__INCLUDED_)
#define AFX_VIEWERTOOLBAR_H__28053453_8DE7_41D2_A975_746379DB9E34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DropDownToolBar.h"

class CViewerToolBar : public CDropDownToolBar  
{
public:
	void OnDropDownButton(UINT nID);
	CViewerToolBar();
	virtual ~CViewerToolBar();
};

#endif // !defined(AFX_VIEWERTOOLBAR_H__28053453_8DE7_41D2_A975_746379DB9E34__INCLUDED_)
