// FlashToolBar.h: interface for the CFlashToolBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLASHTOOLBAR_H__F0A79E27_9206_4F31_BF38_E5EE4CAF3B6E__INCLUDED_)
#define AFX_FLASHTOOLBAR_H__F0A79E27_9206_4F31_BF38_E5EE4CAF3B6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DropDownToolBar.h"

class CFlashToolBar:public CDropDownToolBar
{
public:
	void OnDropDownButton(UINT nID);
	CFlashToolBar();
	virtual ~CFlashToolBar();
};

#endif // !defined(AFX_FLASHTOOLBAR_H__F0A79E27_9206_4F31_BF38_E5EE4CAF3B6E__INCLUDED_)
