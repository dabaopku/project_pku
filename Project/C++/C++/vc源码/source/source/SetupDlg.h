#if !defined(AFX_SETUPDLG_H__76D701A3_4B1B_11D5_953D_C12A6E8DBB23__INCLUDED_)
#define AFX_SETUPDLG_H__76D701A3_4B1B_11D5_953D_C12A6E8DBB23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetUpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog

class CSetupDlg : public CDialog
{
// Construction
public:
	CSetupDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetupDlg)
	enum { IDD = IDD_SETUP };
	CListBox	m_URLList;
	CButton	m_ClearAll;
	CButton	m_DeleteItem;
	BOOL	m_DoubleClick;
	BOOL	m_Loop;
	BOOL	m_URLMode;
	BOOL	m_SlideShow;
	BOOL	m_ShowAbout;
	int		m_Elapse;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetupDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelChangeUrlList();
	afx_msg void OnDeleteItem();
	afx_msg void OnClearAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPDLG_H__76D701A3_4B1B_11D5_953D_C12A6E8DBB23__INCLUDED_)
