#if !defined(AFX_SHELLLIST_H__B96C9FE6_0D01_42FB_B98E_5C04DF7120B1__INCLUDED_)
#define AFX_SHELLLIST_H__B96C9FE6_0D01_42FB_B98E_5C04DF7120B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShellList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShellList window
class CBrowserList;

class CShellList : public CListCtrl,public CShell
{
// Construction
public:
	CShellList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShellList)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_Refresh;
	virtual void OnItemRClick(int Item);
	BOOL m_ShowFlashOnly;
	void SetViewStyle();
	void Refresh();
	void OnItemAction(int Item);
	BOOL IsSelectedItem(int Which);
	int GetItemFlag(int Which);
	BOOL IsMovie(int Which);
	int GetItemFlag(SHFILEINFO sfi,CString FullPath);
	void SelectItem(int Which);
	int SetSelection(CString FullPath);
	virtual void OnItemSelected(int Which);
	virtual void OnItemDblClick(int Which);
	BOOL IsFolder(int nItem);
	void InsertSubItems(int Which,SHFILEINFO sfi,CString FullPath);
	BOOL GetViewStyle(int ViewStyle);
	int m_ViewStyle;
	void SetViewStyle(int ViewStyle);
	BOOL PopulateList(LPSHELLFOLDER pParentShellFolder,CShellTreeItemData * pStid,HTREEITEM hItem);
	void SetImageList();
	CShellTree * p_Tree;
	CShell m_Shell;
	void AssociateTree(CShellTree *pTree);
	
	int m_SelectedItem;

	HTREEITEM h_TreeItem;
	CImageList m_LargeList,m_SmallList;
	virtual ~CShellList();
	CString GetItemFullPath(int nItem);
	CString GetSelectedItemFullPath();
	void ShowFileInfo(CBrowserList *pList,int Which,CString FullPath);

	// Generated message map functions
protected:
	//{{AFX_MSG(CShellList)
	afx_msg void OnRClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemChanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHELLLIST_H__B96C9FE6_0D01_42FB_B98E_5C04DF7120B1__INCLUDED_)
