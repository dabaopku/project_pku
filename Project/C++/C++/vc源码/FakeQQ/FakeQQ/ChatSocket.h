#if !defined(AFX_CHATSOCKET_H__B4567870_56D5_4297_8677_7016EB060E16__INCLUDED_)
#define AFX_CHATSOCKET_H__B4567870_56D5_4297_8677_7016EB060E16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatSocket.h : header file
//

#include "FakeQQDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CChatSocket command target
class CChatSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CChatSocket();
	virtual ~CChatSocket();

// Overrides
public:
	static UINT ThreadOnReceive(LPVOID pParam);
	CFakeQQDlg * m_pDlg;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CChatSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

struct CThreadData
{
	CChatSocket * m_pSocket;
	CMsgInfo * m_pMsg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATSOCKET_H__B4567870_56D5_4297_8677_7016EB060E16__INCLUDED_)
