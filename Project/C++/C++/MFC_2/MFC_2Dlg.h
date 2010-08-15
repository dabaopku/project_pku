// MFC_2Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMFC_2Dlg �Ի���
class CMFC_2Dlg : public CDialog
{
// ����
public:
	CMFC_2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFC_2_DIALOG };

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
