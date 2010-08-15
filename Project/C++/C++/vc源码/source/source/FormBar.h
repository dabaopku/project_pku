#if !defined(AFX_FORMBAR_H__A9D59740_4B72_11D5_953D_DE260E80AB23__INCLUDED_)
#define AFX_FORMBAR_H__A9D59740_4B72_11D5_953D_DE260E80AB23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormBar dialog
class CViewerClient;

class CFormBar : public CDialogBar
{
// Construction
public:
	void InsertItem(CString URL);
	virtual void OnInitDialog();
	CSliderCtrl m_Slider;
	CString m_LastURL;
	CComboBox m_List;
	void ResizeSlider();
	~CFormBar();
	void SaveList();
	BOOL m_AutoComplete;
	void LoadList();
	BOOL m_DragMode;
	CFormBar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFormBar)
	enum { IDD = IDD_VIEWER };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormBar)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFormBar)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEditChange();
	afx_msg void OnSelectItem();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMBAR_H__A9D59740_4B72_11D5_953D_DE260E80AB23__INCLUDED_)
