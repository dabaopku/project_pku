// RMSDlg.h : header file
//

#if !defined(AFX_RMSDLG_H__046C627A_9FE0_49B4_98F7_A67F54092C3C__INCLUDED_)
#define AFX_RMSDLG_H__046C627A_9FE0_49B4_98F7_A67F54092C3C__INCLUDED_

#include "Picture.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRMSDlg dialog

class CRMSDlg : public CDialog
{
// Construction
public:
	void Search();

	CPicture m_Pic;

	CDC     memDC;
	CRect   rect;
  	_variant_t	varBLOB,vtxt;
    // int m_nCurrentSel;
  //  BYTE *pBuffer;

	_RecordsetPtr m_pRecordset;			// 记录集连接接口指针	

	CRMSDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRMSDlg)
	enum { IDD = IDD_RMS_DIALOG };
	CString	m_Txt;
	CString	m_word;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRMSDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRMSDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOK();
	afx_msg void OnButton_in();
	afx_msg void OnButton_out();
	afx_msg void OnButton_pre();
	afx_msg void OnButton_next();
	afx_msg void OnButton_del();
	afx_msg void OnButton_Fileout();
	afx_msg void OnButton_File_In();
	afx_msg void OnButton_File_Del();
	afx_msg void OnButton_Find();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RMSDLG_H__046C627A_9FE0_49B4_98F7_A67F54092C3C__INCLUDED_)
