#if !defined(AFX_FLASHWND_H__6204A93C_724C_460A_AAD2_05D8B9003258__INCLUDED_)
#define AFX_FLASHWND_H__6204A93C_724C_460A_AAD2_05D8B9003258__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FlashWnd.h : header file
//
#include "ShockwaveFlash.h"

/////////////////////////////////////////////////////////////////////////////
// CFlashWnd window

class CFlashWnd : public CShockwaveFlash
{
	// Construction
public:
	CFlashWnd();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlashWnd)
public:
	virtual BOOL Create(CWnd* pParentWnd,DWORD style=WS_CHILD|WS_VISIBLE);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	CString GetMovie();
	COLORREF GetBackgroundColor();
	void SetBackgroundColor(COLORREF BackColor);
	void SaveAs(CString FileName);
	BOOL DoSaveAs(CString FileName);
	int m_Type;
	CString m_DisplayName;
	CString m_TempFileName;
	BOOL SetMovie(CString Movie);
	virtual ~CFlashWnd();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CFlashWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLASHWND_H__6204A93C_724C_460A_AAD2_05D8B9003258__INCLUDED_)
