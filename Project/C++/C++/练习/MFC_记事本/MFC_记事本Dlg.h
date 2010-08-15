// MFC_记事本Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include"string"
using std::string;

// CMFC_记事本Dlg 对话框
class CMFC_记事本Dlg : public CDialog
{
// 构造
public:
	CMFC_记事本Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFC__DIALOG };

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
	afx_msg void OnBnClickedButtonOpen();
	CEdit m_oTextEdit;
};
