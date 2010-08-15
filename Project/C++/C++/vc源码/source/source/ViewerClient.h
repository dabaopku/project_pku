#if !defined(AFX_VIEWERCLIENT_H__67B0FF01_26C7_40BB_B7D0_6373DD4EF626__INCLUDED_)
#define AFX_VIEWERCLIENT_H__67B0FF01_26C7_40BB_B7D0_6373DD4EF626__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewerClient.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewerClient view

class CViewerClient : public CWnd
{
protected:
	DECLARE_DYNCREATE(CViewerClient)

// Attributes
public:
	CFlashWnd m_Flash;

// Operations
public:
	CViewerClient();           // protected constructor used by dynamic creation

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewerClient)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewerClient)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWERCLIENT_H__67B0FF01_26C7_40BB_B7D0_6373DD4EF626__INCLUDED_)
