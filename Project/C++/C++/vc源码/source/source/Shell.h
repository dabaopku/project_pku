// Shell.h: interface for the CShell class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHELL_H__6D15D05C_CD8B_4422_BFAF_D0A70F36E352__INCLUDED_)
#define AFX_SHELL_H__6D15D05C_CD8B_4422_BFAF_D0A70F36E352__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct CShellTreeItemData	//Shell�ļ�Ŀ¼����������
{
    LPSHELLFOLDER m_pParentShellFolder;	//ָ�򸸼�Ŀ¼��ָ��
    LPITEMIDLIST m_pIDList;	//ID List
    LPITEMIDLIST m_pFullIDList;	//������ID List
};

struct CShellListItemData: public CShellTreeItemData	//Shell�ļ��б���������
{
    ULONG m_Attribute;	//�ļ�����
    int m_Flag;	//������־λ
};

class CShell	//Shell�ļ�������
{
public:
    
    //����
    
    BOOL m_ShowHidden;	//�Ƿ���ʾ�����ļ�
    BOOL m_Building;	//�Ƿ����ڹ�����ͼ
    
    static HIMAGELIST h_SmallImageList;
    static HIMAGELIST h_LargeImageList;
    static CImageList m_SmallImageList;
    static CImageList m_LargeImageList;
    
    //����
    
    static int CALLBACK Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
    BOOL IsValidPath(CString Path);
    static int CompareStid(LPARAM lparam,LPCITEMIDLIST pIDList);
    static int CALLBACK SortProc(LPARAM lparam1, LPARAM lparam2, LPARAM lparamSort);
    static int CompareStid(LPARAM lparam1, LPARAM lparam2);
    void GetFileInfo(LPITEMIDLIST lpi, UINT uFlags,SHFILEINFO * psfi);
    void ShowHidden(BOOL Hidden=TRUE);
    int GetItemIcon(LPITEMIDLIST lpi, UINT uFlags);
    BOOL GetItemName(LPSHELLFOLDER lpsf, LPITEMIDLIST lpi, DWORD dwFlags, LPTSTR lpFriendlyName);
    UINT GetSize(LPCITEMIDLIST pidl);
    LPITEMIDLIST CopyPidl(LPMALLOC lpMalloc, LPITEMIDLIST lpi);
    LPITEMIDLIST CreatePidl(UINT cbSize);
    LPITEMIDLIST ConcatPidl(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2);
    CShell();
    virtual ~CShell();
    CImageList * GetImageList(BOOL Small);
};

#endif // !defined(AFX_SHELL_H__6D15D05C_CD8B_4422_BFAF_D0A70F36E352__INCLUDED_)
