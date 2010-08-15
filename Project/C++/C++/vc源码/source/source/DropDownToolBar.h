#if !defined(AFX_DROPDOWNTOOLBAR_H__9F581592_1687_4D12_8D4F_5048713474FC__INCLUDED_)
#define AFX_DROPDOWNTOOLBAR_H__9F581592_1687_4D12_8D4F_5048713474FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DropDownToolBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDropDownToolBar window

class CDropDownToolBar : public CToolBar
{
// Construction
public:
	CDropDownToolBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDropDownToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void OnDropDownButton(UINT nID);
	void SetDropDownButton(UINT nID,UINT nMenuID);
	UINT * p_MenuID;
	BOOL LoadToolBar(UINT nID);
	virtual ~CDropDownToolBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDropDownToolBar)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg void OnDropDown(LPNMTOOLBAR pNotifyStruct, LRESULT* result);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DROPDOWNTOOLBAR_H__9F581592_1687_4D12_8D4F_5048713474FC__INCLUDED_)
