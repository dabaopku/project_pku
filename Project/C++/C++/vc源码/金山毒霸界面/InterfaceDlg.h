// InterfaceDlg.h : header file
//

#if !defined(AFX_INTERFACEDLG_H__6E3D99E4_2A08_4694_A3D3_2A4EF3C54AA9__INCLUDED_)
#define AFX_INTERFACEDLG_H__6E3D99E4_2A08_4694_A3D3_2A4EF3C54AA9__INCLUDED_
#include "ColorStatic.h"
#include "ColorButton.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CInterfaceDlg dialog

class CInterfaceDlg : public CDialog
{
// Construction
public:
	CBitmap m_bmpBackground;
	CColorButton m_ColorBtn3;
	CColorButton m_ColorBtn2;
	CColorButton m_ColorBtn1;
	CColorStatic m_Static10;
	CColorStatic m_Static9;
	CColorStatic m_Static8;
	CColorStatic m_Static7;
	CColorStatic m_Static6;
	CColorStatic m_Static5;
	CColorStatic m_Static4;
	CColorStatic m_Link3;
	CColorStatic m_Link2;
	CColorStatic m_Link1;
	BOOL m_bEnable;
	CInterfaceDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CInterfaceDlg)
	enum { IDD = IDD_INTERFACE_DIALOG };
	CBitmapButton	m_HomeBtn;
	CListCtrl	m_List;
	CBitmapButton	m_StartBtn;
	CBitmapButton	m_CloseBtn;
	CBitmapButton	m_BitmapBtn;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterfaceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CInterfaceDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClosebtn();
	afx_msg void OnStartbtn();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBitmapbtn();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERFACEDLG_H__6E3D99E4_2A08_4694_A3D3_2A4EF3C54AA9__INCLUDED_)
