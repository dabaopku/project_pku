#if !defined(AFX_SENDMSGDLG_H__166062CD_41BB_4A34_BC40_6BCFD6BB66A2__INCLUDED_)
#define AFX_SENDMSGDLG_H__166062CD_41BB_4A34_BC40_6BCFD6BB66A2__INCLUDED_

#include "MsgInfo.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendMsgDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSendMsgDlg dialog

class CSendMsgDlg : public CDialog
{
// Construction
public:
	CSendMsgDlg(CUserInfo * pToUser = NULL, CWnd* pParent = NULL);   // standard constructor
	CUserInfo * m_pToUser;

// Dialog Data
	//{{AFX_DATA(CSendMsgDlg)
	enum { IDD = IDD_SEND_MSG_DLG };
	CEdit	m_ToPort;
	CEdit	m_ToIp;
	CString	m_Msg;
	CString	m_LocalIp;
	CString	m_LoginName;
	CString	m_ToUser;
	CString	m_UdpPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendMsgDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSendMsgDlg)
	afx_msg void OnSendMsg();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDMSGDLG_H__166062CD_41BB_4A34_BC40_6BCFD6BB66A2__INCLUDED_)
