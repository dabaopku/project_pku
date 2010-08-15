#if !defined(AFX_2HTMLDLG_H__76D701A5_4B1B_11D5_953D_C12A6E8DBB23__INCLUDED_)
#define AFX_2HTMLDLG_H__76D701A5_4B1B_11D5_953D_C12A6E8DBB23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 2HtmlDlg.h : header file
//
#include "FlashWnd.h"

/////////////////////////////////////////////////////////////////////////////
// C2HtmlDlg dialog

class C2HtmlDlg : public CDialog
{
	// Construction
public:
	~C2HtmlDlg();
	CString m_TempFileName;
	void SaveCodes(CString FileName);
	void UpdateCode();
	CFlashWnd * p_Flash;
	C2HtmlDlg(CFlashWnd *pFlash,BOOL URLMode);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(C2HtmlDlg)
	enum { IDD = IDD_2HTML };
	CString	m_Code;
	CString	m_Title;
	BOOL	m_URLMode;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C2HtmlDlg)
public:
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(C2HtmlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCopy();
	afx_msg void OnMoviePath();
	afx_msg void OnChangeHtmlTitle();
	afx_msg void OnSave();
	afx_msg void OnPreview();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_2HTMLDLG_H__76D701A5_4B1B_11D5_953D_C12A6E8DBB23__INCLUDED_)
