// CleanSameInfoDlg.h : ͷ�ļ�
//
#include "string"
#include "set"
#include "fstream"
using namespace std;
#pragma once
void TakeoutFileName(const std::string & PathName, std::string & fileName);

// CCleanSameInfoDlg �Ի���
class CCleanSameInfoDlg : public CDialog
{
// ����
public:
	CCleanSameInfoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLEANSAMEINFO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
