#if !defined(AFX_PROPERTYDLG_H__76D701A4_4B1B_11D5_953D_C12A6E8DBB23__INCLUDED_)
#define AFX_PROPERTYDLG_H__76D701A4_4B1B_11D5_953D_C12A6E8DBB23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropertyDlg dialog

class CPropertyDlg : public CDialog
{
// Construction
public:
	int m_Frames;
	CPropertyDlg(int Frames);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPropertyDlg)
	enum { IDD = IDD_PROPERTY };
	CString	m_CreateTime;
	CString	m_FileName;
	CString	m_FileSize;
	CString	m_ModifyTime;
	CString	m_TotalFrame;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropertyDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYDLG_H__76D701A4_4B1B_11D5_953D_C12A6E8DBB23__INCLUDED_)
