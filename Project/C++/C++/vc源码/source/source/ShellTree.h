#if !defined(AFX_SHELLTREE_H__DF774B19_641D_4E47_B163_E7F6A1EA8963__INCLUDED_)
#define AFX_SHELLTREE_H__DF774B19_641D_4E47_B163_E7F6A1EA8963__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShellTree.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShellTree window
class CShellList;

enum FindAttribs
{
	SHELL_DRIVE = 1,
	SHELL_FOLDER = 2
};

class CShellTree : public CTreeCtrl,public CShell
{
public:
	
	// Construction
	CShellTree();
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShellTree)
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	void PopulateList(HTREEITEM Item);
	BOOL RootReached();
	void ItemUp();
	void SelectRootItem();
	void Refresh();
	HTREEITEM FindChild(HTREEITEM hItem,CString Path);
	void FillSpecialFolders();
	CString GetItemFullPath(HTREEITEM Item);
	HTREEITEM FindChild(HTREEITEM hParent,CShellListItemData *pSlid);
	HTREEITEM h_Desktop;
	HTREEITEM h_Computer;

	HTREEITEM h_SpecialFolder[26];
	CString m_SpecialFolder[26];
	int m_SpecialFolderCount;
	
	HTREEITEM InsertItem(LPSHELLFOLDER pParentShellFolder, LPITEMIDLIST pParentFullIDList,LPITEMIDLIST pIDList,HTREEITEM hParent,HTREEITEM hItem);
	void FillTree(LPSHELLFOLDER pParentShellFolder, LPITEMIDLIST pParentFullIDList, HTREEITEM hParent);
	void BuildTree();
	HTREEITEM SetSelection(CString FindPath,BOOL Check=FALSE);
	void SetImageList();
	CShellList * p_List;
	CString GetSelectedItemFullPath();
	void AssociateList(CShellList *pList);
	virtual ~CShellTree();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CShellTree)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHELLTREE_H__DF774B19_641D_4E47_B163_E7F6A1EA8963__INCLUDED_)
