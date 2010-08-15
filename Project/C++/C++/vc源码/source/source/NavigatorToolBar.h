// NavigatorToolBar.h: interface for the CNavigatorToolBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NAVIGATORTOOLBAR_H__8BC64959_4813_48FE_BC01_E19F1F457205__INCLUDED_)
#define AFX_NAVIGATORTOOLBAR_H__8BC64959_4813_48FE_BC01_E19F1F457205__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DropDownToolBar.h"

class CNavigatorToolBar : public CDropDownToolBar
{
public:
	void OnDropDownButton(UINT nID);
	CNavigatorToolBar();
	virtual ~CNavigatorToolBar();
};

#endif // !defined(AFX_NAVIGATORTOOLBAR_H__8BC64959_4813_48FE_BC01_E19F1F457205__INCLUDED_)
