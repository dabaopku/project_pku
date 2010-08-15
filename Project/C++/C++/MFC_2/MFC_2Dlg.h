// MFC_2Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMFC_2Dlg 对话框
class CMFC_2Dlg : public CDialog
{
// 构造
public:
	CMFC_2Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFC_2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeList1();
	CEdit m_oNameEdit;
	CSliderCtrl m_oSalarySlider;
	CEdit m_oSalaryEdit;
	CComboBox m_oJobCombox;
	CListBox m_oEmployeeList;
	afx_msg void OnBnClickedButton1();
protected:
	TCHAR* GetInfJob(int ID);
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
