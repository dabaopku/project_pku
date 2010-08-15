#if !defined(AFX_VIEWERFRAME_H__7888C227_8274_4A49_BAA4_AF9C364F4F58__INCLUDED_)
#define AFX_VIEWERFRAME_H__7888C227_8274_4A49_BAA4_AF9C364F4F58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewerFrame.h : header file
//
#include "FormBar.h"
#include "ViewerClient.h"
#include "History.h"
#include "FlashToolBar.h"
#include "ViewerToolBar.h"
#include "ProgressStatusBar.h"

/////////////////////////////////////////////////////////////////////////////
// CViewerFrame frame

class CViewerFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CViewerFrame)
		
public:
	CViewerFrame();           // protected constructor used by dynamic creation
	
	// Operations
public:
	void SaveNow(CString FullPath);
	void OnHilite();
	void EndFullScreen();
	void FullScreenShow();
	void NoWait();
	void ClearAll();
	void ShowProgress();
	void ShowFrames();
	void ShowCurrentFrame(BOOL DragMode);
	void LoadMovie(BOOL BuildFlashIndexTable=TRUE);
	void SetCurrentFrame(int Value);
	CFlashWnd * p_Flash;
	WINDOWPLACEMENT m_OldWndPlacement;
	BOOL m_FullScreen;
	CRect m_FullScreenRect;
	
	UINT m_TimerID;
	BOOL m_Wait;
	int m_Frames,m_CurrentFrame,m_Progress;
	CStringQueue m_SavePath;

	CProgressStatusBar m_StatusBar;
	CViewerToolBar m_ToolBar;
	CFlashToolBar m_FlashToolBar;
	CReBar m_ReBar;
	CFormBar m_DlgBar;
	CViewerClient m_View;
	afx_msg void OnFullScreen();
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewerFrame)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	virtual ~CViewerFrame();
	
	// Generated message map functions
	//{{AFX_MSG(CViewerFrame)
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnFileProperty();
	afx_msg void OnFileOpen();
	afx_msg void OnUpdateFileProperty(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMovieForward(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFrameBack(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFrameEnd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFrameForward(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFrameRewind(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMovieBack(CCmdUI* pCmdUI);
	afx_msg void OnMovieForward();
	afx_msg void OnMovieTail();
	afx_msg void OnMovieStop();
	afx_msg void OnUpdateMovieStop(CCmdUI* pCmdUI);
	afx_msg void OnMoviePlay();
	afx_msg void OnUpdateMoviePlay(CCmdUI* pCmdUI);
	afx_msg void OnMovieLoop();
	afx_msg void OnUpdateMovieLoop(CCmdUI* pCmdUI);
	afx_msg void OnMovieHead();
	afx_msg void OnMovieBack();
	afx_msg void OnFrameRewind();
	afx_msg void OnFrameForward();
	afx_msg void OnFrameEnd();
	afx_msg void OnFrameBack();
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnShowAll();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnExactIt();
	afx_msg void OnEndFullScreen();
	afx_msg void OnUpdateFullScreen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomIn(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomOut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateExactIt(CCmdUI* pCmdUI);
	afx_msg void OnActualSize();
	afx_msg void OnUpdateActualSize(CCmdUI* pCmdUI);
	afx_msg void OnBackColor();
	afx_msg void OnHighQuality();
	afx_msg void OnLowQuality();
	afx_msg void OnMediumQuality();
	afx_msg void OnUpdateHighQuality(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLowQuality(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMediumQuality(CCmdUI* pCmdUI);
	afx_msg void OnMovieQuality();
	afx_msg void OnUpdateMovieQuality(CCmdUI* pCmdUI);
	afx_msg void OnFileSaveNow();
	afx_msg void OnUpdateFileSaveNow(CCmdUI* pCmdUI);
	afx_msg void OnFileExportFlash();
	afx_msg void OnUpdateFileExportFlash(CCmdUI* pCmdUI);
	afx_msg void OnFileExportHtml();
	afx_msg void OnUpdateFileExportHtml(CCmdUI* pCmdUI);
	afx_msg void OnHelpProduct();
	afx_msg void OnUpdateBackColor(CCmdUI* pCmdUI);
	afx_msg void OnSlideShow();
	afx_msg void OnUpdateSlideShow(CCmdUI* pCmdUI);
	afx_msg void OnMovieBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWERFRAME_H__7888C227_8274_4A49_BAA4_AF9C364F4F58__INCLUDED_)
