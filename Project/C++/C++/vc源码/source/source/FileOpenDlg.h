//{{AFX_INCLUDES()
#include "FlashWnd.h"
//}}AFX_INCLUDES
#if !defined(AFX_FILEOPENDLG_H__C5229844_4C49_11D5_953D_FD3FEE7AAD23__INCLUDED_)
#define AFX_FILEOPENDLG_H__C5229844_4C49_11D5_953D_FD3FEE7AAD23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileOpenDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileOpenDlg dialog

class CFileOpenDlg : public CFileDialog
{
	DECLARE_DYNAMIC(CFileOpenDlg)
public:
	CWnd m_Container;
	void DoDataExchange(CDataExchange *pDX);
	void OnFileNameChange();
// Construction
	CFileOpenDlg(BOOL bOpenFileDialog,LPCTSTR lpszDefExt,LPCTSTR lpszFileName=NULL,DWORD dwFlags=OFN_HIDEREADONLY,LPCTSTR lpszFilter=NULL,CWnd *pParentWnd=NULL);

// Dialog Data
	CFlashWnd	m_Flash;
	//{{AFX_DATA(CFileOpenDlg)
	enum { IDD=IDD_FILE_OPEN };
	CString	m_Path;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileOpenDlg)
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFileOpenDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEOPENDLG_H__C5229844_4C49_11D5_953D_FD3FEE7AAD23__INCLUDED_)
