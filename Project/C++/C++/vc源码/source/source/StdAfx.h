// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__675580E2_49B4_4408_945B_D681D5E82ED0__INCLUDED_)
#define AFX_STDAFX_H__675580E2_49B4_4408_945B_D681D5E82ED0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <atlbase.h>
#include <afxinet.h>
#include <winver.h>
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "FlashWnd.h"
#include "FlashOCX.h"
#include "Shell.h"
#include "ShellTree.h"
#include "ShellList.h"

#define BUFFER_SIZE 0x10000
#define SWF_OFFSET 0x5c000
#define CAPTION_HEIGHT 22
#define LIST_HEIGHT_LIMIT 340
#define LIST_WIDTH_LIMIT 320
#define VIEWER_WIDTH_LIMIT 500 

extern CString EXE_TYPE;
extern CString SWF_TYPE;

BOOL IsRemoteURL(CString URL);
CString GetTempFileName(CString Ext);
CString GetFilePathFromFileName(CString FileName);
CString GetFileTitleFromFileName(CString FileName,BOOL Ext=TRUE);

COLORREF Rgb2Bgr(COLORREF Color);

int MultiLineTextOut(CDC *pDC,int x,int y,int LineSpace,CString Text);
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__675580E2_49B4_4408_945B_D681D5E82ED0__INCLUDED_)
