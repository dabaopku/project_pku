// FlashNow.h : main header file for the FLASHNOW application
//

#if !defined(AFX_FLASHNOW_H__BEBC2CAC_2D25_4D76_8B27_875B157552E1__INCLUDED_)
#define AFX_FLASHNOW_H__BEBC2CAC_2D25_4D76_8B27_875B157552E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "FlashOCX.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CFlashNowApp:
// See FlashNow.cpp for the implementation of this class
//
class CBrowserFrame;
class CViewerFrame;

class CUserData
{
public:
	BOOL m_ShowAbout;
	CUserData();
	~CUserData();
	int m_Elapse;
	int m_RunTimes;
	BOOL m_Loop;
	BOOL m_URLMode;
	BOOL m_DoubleClick;
	BOOL m_SlideShow;
	TCHAR m_SavePath[2000];
	TCHAR m_TypedURLs[6000];
	CString m_LastPath;
};

class CFlashNowApp : public CWinApp
{
public:
	enum EMode{VIEWER,BROWSER};
	
	EMode m_Mode;
	CString m_Path;
	CString m_Title[2];
	WINDOWPLACEMENT m_Placement;

	CFlashNowApp();
	virtual ~CFlashNowApp();
	CBrowserFrame*  p_Browser;
	CViewerFrame*  p_Viewer;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlashNowApp)
	public:
	virtual BOOL InitInstance();
	virtual CWnd* GetMainWnd();
	virtual int ExitInstance();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// Implementation

public:
	CFlashOCX m_FlashOCX;
	void CheckFlashOCX();
	void BuildFlashIndexTable();
	BOOL IsValidFlashIndex();
	CString GetMovieURL();

	CString m_MovieURL;

	int m_FlashIndex;
	int m_FlashCount;
	int *p_FlashIndex;

	CString m_ModuleFilePath;
	CString m_ModuleFileName;
	CUserData m_UserData;

	void SetWindowTitle(CString Title,BOOL BrowserMode);
	void SwitchToViewer();
	void SwitchToBrowser();

	int AttachFile(CString FileName);
	int AttachFolder(CString Path);

	void LoadMovie(CString URL);
	//{{AFX_MSG(CFlashNowApp)
	afx_msg void OnAppAbout();
	afx_msg void OnSendSuggestion();
	afx_msg void OnToolSetup();
	afx_msg void OnOcxRegister();
	afx_msg void OnHelpManual();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CFlashNowApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLASHNOW_H__BEBC2CAC_2D25_4D76_8B27_875B157552E1__INCLUDED_)
