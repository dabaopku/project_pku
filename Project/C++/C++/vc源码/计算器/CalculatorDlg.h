// CalculatorDlg.h : header file
//

#if !defined(AFX_CALCULATORDLG_H__97B7A407_D58F_11D2_A71D_871618317B60__INCLUDED_)
#define AFX_CALCULATORDLG_H__97B7A407_D58F_11D2_A71D_871618317B60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "math.h"
#include "QiuXpButton.h"
#include "Qiuxpedit.h"
/////////////////////////////////////////////////////////////////////////////
// CCalculatorDlg dialog

class CCalculatorDlg : public CDialog
{
// Construction
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// standard constructor
    double number1,number2;
	int NumberState,OperationState,DotState;
	int t;
	void Calculator ();

// Dialog Data
	//{{AFX_DATA(CCalculatorDlg)
	enum { IDD = IDD_CALCULATOR_DIALOG };
	CQiuXpEdit	m_edit1;
	CQiuXpButton	m_button33;
	CQiuXpButton	m_button32;
	CQiuXpButton	m_button31;
	CQiuXpButton	m_button30;
	CQiuXpButton	m_button29;
	CQiuXpButton	m_button28;
	CQiuXpButton	m_button27;
	CQiuXpButton	m_button26;
	CQiuXpButton	m_button25;
	CQiuXpButton	m_button24;
	CQiuXpButton	m_button23;
	CQiuXpButton	m_button22;
	CQiuXpButton	m_button21;
	CQiuXpButton	m_button20;
	CQiuXpButton	m_button19;
	CQiuXpButton	m_button18;
	CQiuXpButton	m_button17;
	CQiuXpButton	m_button16;
	CQiuXpButton	m_button15;
	CQiuXpButton	m_button14;
	CQiuXpButton	m_button13;
	CQiuXpButton	m_button12;
	CQiuXpButton	m_button11;
	CQiuXpButton	m_button10;
	CQiuXpButton	m_button09;
	CQiuXpButton	m_button08;
	CQiuXpButton	m_button07;
	CQiuXpButton	m_button06;
	CQiuXpButton	m_button05;
	CQiuXpButton	m_button04;
	CQiuXpButton	m_button03;
	CQiuXpButton	m_button02;
	CQiuXpButton	m_button01;
	CQiuXpButton	m_button6;
	CQiuXpButton	m_button5;
	CQiuXpButton	m_button4;
	CQiuXpButton	m_button3;
	CQiuXpButton	m_button2;
	CQiuXpButton	m_button1;
	double	m_number;
	CString	m_sExpress;
	int		m_nResult;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalculatorDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CMenu m_Menu;
	bool m_bExp;
	// Generated message map functions
	//{{AFX_MSG(CCalculatorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLoadskin();
	afx_msg void OnAppAbout();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnNumberKey(UINT nID);
	afx_msg void OnOperationKey(UINT nID);
	afx_msg void OnOptExp();
	afx_msg void OnUpdateOptExp(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCULATORDLG_H__97B7A407_D58F_11D2_A71D_871618317B60__INCLUDED_)
