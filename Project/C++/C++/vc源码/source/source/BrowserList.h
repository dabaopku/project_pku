#if !defined(AFX_BROWSERLIST_H__660A5E27_F2A2_4A56_BACD_A6147DA3285B__INCLUDED_)
#define AFX_BROWSERLIST_H__660A5E27_F2A2_4A56_BACD_A6147DA3285B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BrowserList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBrowserList view

class CBrowserList : public CView
{
protected:
	CBrowserList();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CBrowserList)

// Attributes
public:

// Operations
public:
	int m_FlashWidth;
	int m_FlashHeight;
	void ShowFileInfo();
	void Preview(CString Movie);
	void SetFileInfo(CString FileInfo);

	CBitmap m_Bitmap;
	int m_BitmapWidth;
	int m_BitmapHeight;

	CString m_FileInfo;
	CFlashWnd m_Preview;
	CShellList m_List;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrowserList)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBrowserList();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CBrowserList)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BROWSERLIST_H__660A5E27_F2A2_4A56_BACD_A6147DA3285B__INCLUDED_)
