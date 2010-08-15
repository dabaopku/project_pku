#if !defined(AFX_REPLYMSGDLG_H__8752D947_79C1_4887_8A45_DF5947196E78__INCLUDED_)
#define AFX_REPLYMSGDLG_H__8752D947_79C1_4887_8A45_DF5947196E78__INCLUDED_

#include "SendMsgDlg.h"	// Added by ClassView
#include "MsgInfo.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReplyMsgDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReplyMsgDlg dialog

class CReplyMsgDlg : public CDialog
{
// Construction
public:
	CMsgInfo * m_pMsg;
	CReplyMsgDlg(CMsgInfo * pMsg, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReplyMsgDlg)
	enum { IDD = IDD_REPLY_MSG_DLG };
	CButton	m_UserFace;
	CString	m_Msg;
	CString	m_Address;
	CString	m_UserName;
	CString	m_MsgTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReplyMsgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReplyMsgDlg)
	afx_msg void OnReplyMsg();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPLYMSGDLG_H__8752D947_79C1_4887_8A45_DF5947196E78__INCLUDED_)
