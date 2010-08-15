// MainFrm.h : interface of the CBrowserFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__08CC877D_3C43_46B4_8D24_5B55D8E2E5A0__INCLUDED_)
#define AFX_MAINFRM_H__08CC877D_3C43_46B4_8D24_5B55D8E2E5A0__INCLUDED_

#include "History.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BrowserFolder.h"
#include "BrowserList.h"
#include "NavigatorToolBar.h"

class CBrowserFrame : public CFrameWnd
{
public:
	CBrowserFrame();
protected: 
	DECLARE_DYNAMIC(CBrowserFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrowserFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_Add;
	void AddHistoryRecord(HTREEITEM hItem);
	CHistory m_History;
	void OnHilite();
	CShellList * p_List;
	CShellTree * p_Tree;
	CFlashWnd *p_Preview;
	virtual ~CBrowserFrame();
	afx_msg void OnViewRefresh();
	afx_msg void OnFileDelete();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	BOOL m_ShowHidden;
	BOOL m_ShowFlashOnly;
	CStatusBar  m_StatusBar;
	CNavigatorToolBar m_ToolBar;
	CReBar    m_ReBar;
	CSplitterWnd  m_Splitter1;
	CSplitterWnd  m_Splitter2;

// Generated message map functions
protected:
	//{{AFX_MSG(CBrowserFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewDetails();
	afx_msg void OnUpdateViewDetails(CCmdUI* pCmdUI);
	afx_msg void OnViewList();
	afx_msg void OnUpdateViewList(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnViewHiddenFiles();
	afx_msg void OnUpdateViewHiddenFiles(CCmdUI* pCmdUI);
	afx_msg void OnViewNext();
	afx_msg void OnViewBack();
	afx_msg void OnUpdateViewNext(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewBack(CCmdUI* pCmdUI);
	afx_msg void OnFileUp();
	afx_msg void OnUpdateFileUp(CCmdUI* pCmdUI);
	afx_msg void OnFileRename();
	afx_msg void OnUpdateFileRename(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileDelete(CCmdUI* pCmdUI);
	afx_msg void OnFileOpen();
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnViewFlashOnly();
	afx_msg void OnUpdateViewFlashOnly(CCmdUI* pCmdUI);
	afx_msg void OnViewSmallIcon();
	afx_msg void OnUpdateViewSmallIcon(CCmdUI* pCmdUI);
	afx_msg void OnViewLargeIcon();
	afx_msg void OnUpdateViewLargeIcon(CCmdUI* pCmdUI);
	afx_msg void OnMovieView();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__08CC877D_3C43_46B4_8D24_5B55D8E2E5A0__INCLUDED_)
