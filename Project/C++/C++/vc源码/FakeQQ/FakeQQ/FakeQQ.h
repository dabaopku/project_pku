// FakeQQ.h : main header file for the FAKEQQ application
//

#if !defined(AFX_FAKEQQ_H__20F407F4_F2D9_451D_BCFE_2E2991039E75__INCLUDED_)
#define AFX_FAKEQQ_H__20F407F4_F2D9_451D_BCFE_2E2991039E75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"	// main symbols
#include "LoginDlg.h"	// Added by ClassView
#include "ChatSocket.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CFakeQQApp:
// See FakeQQ.cpp for the implementation of this class
//
extern HICON FaceIcon[5];
extern HICON MyFaceIcon;
extern CChatSocket ChatSocket;
extern CUserInfo MyInfo;
extern CDatabase ChatDB;

class CFakeQQApp : public CWinApp
{
public:
	bool DBReady();
	CFakeQQApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFakeQQApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFakeQQApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CString GetLocalIp();
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FAKEQQ_H__20F407F4_F2D9_451D_BCFE_2E2991039E75__INCLUDED_)
