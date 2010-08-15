// Delaunay.h : main header file for the DELAUNAY application
//

#if !defined(AFX_DELAUNAY_H__06BA8662_0A69_424A_8A5E_390923263AFC__INCLUDED_)
#define AFX_DELAUNAY_H__06BA8662_0A69_424A_8A5E_390923263AFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDelaunayApp:
// See Delaunay.cpp for the implementation of this class
//

class CDelaunayApp : public CWinApp
{
public:
	CDelaunayApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDelaunayApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDelaunayApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELAUNAY_H__06BA8662_0A69_424A_8A5E_390923263AFC__INCLUDED_)
