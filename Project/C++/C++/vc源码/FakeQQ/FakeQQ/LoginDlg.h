#if !defined(AFX_LOGINDLG_H__75F3D9B5_86E2_42BB_AAED_D32A71EADBB7__INCLUDED_)
#define AFX_LOGINDLG_H__75F3D9B5_86E2_42BB_AAED_D32A71EADBB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog

class CLoginDlg : public CDialog
{
// Construction
public:
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_LOGIN_DLG };
	CComboBox	m_FaceList;
	CStatic	m_UserFace;
	CString	m_LoginName;
	UINT	m_UdpPort;
	CString	m_LocalIp;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoginDlg)
	afx_msg void OnSelchangeFaceList();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__75F3D9B5_86E2_42BB_AAED_D32A71EADBB7__INCLUDED_)
