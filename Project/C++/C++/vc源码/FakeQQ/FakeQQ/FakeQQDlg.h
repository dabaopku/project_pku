// FakeQQDlg.h : header file
//

#if !defined(AFX_FAKEQQDLG_H__6F4A7499_1227_4886_AE99_D0B95059BCB2__INCLUDED_)
#define AFX_FAKEQQDLG_H__6F4A7499_1227_4886_AE99_D0B95059BCB2__INCLUDED_

#include "ReplyMsgDlg.h"	// Added by ClassView
#include "UserInfo.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFakeQQDlg dialog

class CFakeQQDlg : public CDialog
{
// Construction
public:

	CMutex m_Mutex;
	CImageList m_ImageList;
	bool SaveMsg(CMsgInfo * pMsg);
	int FindUser(CUserInfo * pUser);
	CMsgInfo * PopMsg();
	void PushMsg(CMsgInfo * pMsg);
	CPtrArray m_MsgQueue;
	~CFakeQQDlg();

	void BuildUserList();
	void FlashTrayIcon(HICON Icon, bool Flash = true);

	CPtrList m_UserInfoList;

	CFakeQQDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFakeQQDlg)
	enum { IDD = IDD_FAKEQQ_DIALOG };
	CStatic	m_ToolBarPane;
	CListCtrl	m_UserList;
	CString	m_Elapse;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFakeQQDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	HICON m_hIcon;
	HICON m_hFlashingTrayIcon;
	CToolBar m_ToolBar;
	CTime m_StartTime;
	UINT m_nDisplayTimerID;
	UINT m_nTrayIconFlashTimerID;
	UINT m_nTrayIconFlashTicks;

	NOTIFYICONDATA m_Nid;
	bool m_bHide;
	bool m_bTrayIconFlashing;

	// Generated message map functions
	//{{AFX_MSG(CFakeQQDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow();
	afx_msg void OnDblclkUserList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHideWindow();
	afx_msg void OnViewLog();
	afx_msg void OnShowLastChat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FAKEQQDLG_H__6F4A7499_1227_4886_AE99_D0B95059BCB2__INCLUDED_)
