// CleanSameInfoDlg.h : 头文件
//
#include "string"
#include "set"
#include "fstream"
using namespace std;
#pragma once
void TakeoutFileName(const std::string & PathName, std::string & fileName);

// CCleanSameInfoDlg 对话框
class CCleanSameInfoDlg : public CDialog
{
// 构造
public:
	CCleanSameInfoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLEANSAMEINFO_DIALOG };

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
	CString inFileName;
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedZip();
	CString outFilePath;
	afx_msg void OnBnClickedOutput();
};
