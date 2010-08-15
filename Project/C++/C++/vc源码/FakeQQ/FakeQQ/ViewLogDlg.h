#if !defined(AFX_VIEWLOGDLG_H__7D4E1015_2722_46EF_80F6_B4F7F262CA24__INCLUDED_)
#define AFX_VIEWLOGDLG_H__7D4E1015_2722_46EF_80F6_B4F7F262CA24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewLogDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewLogDlg dialog

class CViewLogDlg : public CDialog
{
// Construction
public:
	void RefreshList();

	CViewLogDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CViewLogDlg)
	enum { IDD = IDD_VIEW_LOG };
	CButton	m_UserFace;
	CListCtrl	m_LogList;
	CString	m_ChatMsg;
	CString	m_UserName;
	CString	m_MsgTime;
	CString	m_Address;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewLogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewLogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemChangedLogList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClearLog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWLOGDLG_H__7D4E1015_2722_46EF_80F6_B4F7F262CA24__INCLUDED_)
