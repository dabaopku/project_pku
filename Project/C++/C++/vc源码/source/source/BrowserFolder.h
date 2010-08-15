#if !defined(AFX_BROWSERFOLDER_H__9ADC085D_7FBE_4009_828A_B49742BB3F93__INCLUDED_)
#define AFX_BROWSERFOLDER_H__9ADC085D_7FBE_4009_828A_B49742BB3F93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BrowserFolder.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBrowserFolder view

class CBrowserFolder : public CView
{
protected:
	CBrowserFolder();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CBrowserFolder)

// Attributes
public:
	CShellTree m_Tree;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrowserFolder)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBrowserFolder();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CBrowserFolder)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BROWSERFOLDER_H__9ADC085D_7FBE_4009_828A_B49742BB3F93__INCLUDED_)
