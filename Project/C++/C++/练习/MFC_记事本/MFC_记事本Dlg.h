// MFC_���±�Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include"string"
using std::string;

// CMFC_���±�Dlg �Ի���
class CMFC_���±�Dlg : public CDialog
{
// ����
public:
	CMFC_���±�Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFC__DIALOG };

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
	afx_msg void OnBnClickedButtonOpen();
	CEdit m_oTextEdit;
};
