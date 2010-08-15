#if !defined(AFX_QIUXPEDIT_H__AA3BA55D_63D3_4B50_9CB7_5ED770F3C32E__INCLUDED_)
#define AFX_QIUXPEDIT_H__AA3BA55D_63D3_4B50_9CB7_5ED770F3C32E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QiuXpEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQiuXpEdit window

class CQiuXpEdit : public CEdit
{
// Construction
public:
	CQiuXpEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQiuXpEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CQiuXpEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CQiuXpEdit)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QIUXPEDIT_H__AA3BA55D_63D3_4B50_9CB7_5ED770F3C32E__INCLUDED_)
