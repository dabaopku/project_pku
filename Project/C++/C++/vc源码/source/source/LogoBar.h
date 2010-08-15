#if !defined(AFX_LOGOBAR_H__6797F701_EE23_4688_BA14_92A1ED6B2E87__INCLUDED_)
#define AFX_LOGOBAR_H__6797F701_EE23_4688_BA14_92A1ED6B2E87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogoBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogoBar view

class CLogoBar : public CView
{
protected:
	CLogoBar();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLogoBar)

// Attributes
public:

// Operations
public:
	CFlashWnd m_Logo;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogoBar)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLogoBar();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CLogoBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGOBAR_H__6797F701_EE23_4688_BA14_92A1ED6B2E87__INCLUDED_)
