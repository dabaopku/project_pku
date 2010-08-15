// ShellTree.cpp : implementation file
//

#include "stdafx.h"
#include "FlashNow.h"
#include "BrowserFrame.h"
#include "ShellTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShellTree

CShellTree::CShellTree()
{
    p_List=NULL;
}

CShellTree::~CShellTree()
{
}


BEGIN_MESSAGE_MAP(CShellTree, CTreeCtrl)
//{{AFX_MSG_MAP(CShellTree)
ON_WM_CREATE()
ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemExpanding)
ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelChanged)
ON_NOTIFY_REFLECT(TVN_DELETEITEM, OnDeleteItem)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShellTree message handlers

void CShellTree::AssociateList(CShellList *pList)
{
    p_List=pList;
}

void CShellTree::SetImageList()
{
    CTreeCtrl::SetImageList(CShell::GetImageList(TRUE),TVSIL_NORMAL);
}

int CShellTree::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    SetImageList();	
    BuildTree();
    return 0;
}

HTREEITEM CShellTree::SetSelection(CString Path,BOOL Check)
{
    HTREEITEM Item=h_Desktop;
    
    if(!Path.IsEmpty()&&Path.Right(1)!='\\')
        Path+='\\';
    
    if(Check&&!IsValidPath(Path))
        return NULL;
    
    Path.MakeUpper();
    
    int Which=0;
    int BigMatch=0;
    
    for(int i=0;i<m_SpecialFolderCount;i++)
    {
        CString SpecialFolder=m_SpecialFolder[i];
        SpecialFolder.MakeUpper();
        if(Path.Find(SpecialFolder,0)>=0)
        {
            int Length=m_SpecialFolder[i].GetLength();
            if(Length>BigMatch)
            {
                BigMatch=Length;
                Which=i;
            }
        }
    }
    
    if(!BigMatch)
        return NULL;
    
    Item=h_SpecialFolder[Which];
    Expand(Item,TVE_EXPAND);
    
    int FullLength=Path.GetLength();
    
    for(i=BigMatch;i<FullLength;i++)
    {
        if(Path.GetAt(i)=='\\')
        {
            CString Folder=Path.Mid(BigMatch,i-BigMatch);
            BigMatch=i+1;
            Item=FindChild(Item,Folder);
            if(!Item)
                break;
            
            Expand(Item,TVE_EXPAND);
        }
    }
    
    if(Item)
    {		
        SelectItem(Item);
        return Item;
    }
    else
        return NULL;
}

void CShellTree::BuildTree()
{
    LPSHELLFOLDER	pDesktopShellFolder=NULL;
    HRESULT			hr;
    HTREEITEM hItem;
    
    h_Desktop=NULL;
    h_Computer=NULL;
    m_SpecialFolderCount=0;
    
    m_Building = TRUE;
    
    SetRedraw(FALSE);
    DeleteAllItems();
    
    hr=SHGetDesktopFolder(&pDesktopShellFolder);
    
    if (SUCCEEDED(hr))
    {
        LPITEMIDLIST pIDList;
        //get pIDList from CSIDL
        if(SUCCEEDED(SHGetSpecialFolderLocation(NULL,CSIDL_DESKTOP,&pIDList)))
        {
            h_Desktop=InsertItem(pDesktopShellFolder,NULL,pIDList,TVI_ROOT,NULL);
            
            LPMALLOC lpMalloc=NULL;
            if (FAILED(SHGetMalloc(&lpMalloc)))
                return;
            
            lpMalloc->Free(pIDList);  
            lpMalloc->Release();
        }
        
        if(!h_Desktop)
            h_Desktop=TVI_ROOT;
        
        FillTree(pDesktopShellFolder,NULL,h_Desktop);
        pDesktopShellFolder->Release();
    }
    
    FillSpecialFolders();
    hItem = GetRootItem();
    Expand(hItem,TVE_EXPAND);
    
    SetRedraw(TRUE);
    m_Building = FALSE;
}

/****************************************************************************
*
*  FUNCTION: FillTree( LPSHELLFOLDER pParentShellFolder,
*                      LPITEMIDLIST  pParentFullIDList,
*                      HTREEITEM     hParent)
*
*  PURPOSE: Fills a branch of the TreeView control.  Given the
*           shell folder, enumerate the subitems of this folder,
*           and add the appropriate items to the tree.
*
*  PARAMETERS:
*    pParentShellFolder         - Pointer to shell folder that we want to enumerate items 
*    pParentFullIDList        - Fully qualified item id list to the item that we are enumerating
*                   items for.  In other words, this is the pIDList to the item
*                   identified by the pParentShellFolder parameter.
*    hParent      - Parent node
*
*  COMMENTS:
*    This function enumerates the items in the folder identifed by pParentShellFolder.
*    Note that since we are filling the left hand pane, we will only add
*    items that are folders and/or have sub-folders.  We *could* put all
*    items in here if we wanted, but that's not the intent.
*
****************************************************************************/

void CShellTree::FillTree(LPSHELLFOLDER pParentShellFolder, LPITEMIDLIST pParentFullIDList, HTREEITEM hParent)
{
    if(!pParentShellFolder)
        return;
    HTREEITEM       hPrev = NULL;
    LPENUMIDLIST    lpe=NULL;
    LPITEMIDLIST    pIDList=NULL, pFullIDList=NULL;
    CShellTreeItemData *    pStid=NULL;
    LPMALLOC        lpMalloc=NULL;
    ULONG           ulFetched;
    HRESULT         hr;
    
    hr = SHGetMalloc(&lpMalloc);
    if (FAILED(hr))
        return;
    
    DWORD dwFlags = SHCONTF_FOLDERS;
    if( m_ShowHidden )
        dwFlags |= SHCONTF_INCLUDEHIDDEN;
    
    hr = pParentShellFolder->EnumObjects(GetSafeHwnd(), dwFlags, &lpe);
    
    if (SUCCEEDED(hr))
    {
        while (S_OK == lpe->Next(1, &pIDList, &ulFetched))
        {
            hPrev = InsertItem(pParentShellFolder,pParentFullIDList,pIDList,hParent,hPrev);
        }
        
        lpMalloc->Free(pIDList);
        pIDList=NULL;
    }
    
    if (lpe)  
        lpe->Release();
    
    if (lpMalloc) 
        lpMalloc->Release();
}

void CShellTree::OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
    CShellTreeItemData *   pStid;
    HRESULT        hr;
    LPSHELLFOLDER  pShellFolder=NULL;
    static char    szBuff[_MAX_PATH];
    TV_SORTCB      tvscb;
    
    NM_TREEVIEW* pnmtv = (NM_TREEVIEW*)pNMHDR;
    
    if ((pnmtv->itemNew.state & TVIS_EXPANDEDONCE))
        return;
    
    pStid=(CShellTreeItemData *)pnmtv->itemNew.lParam;
    if (pStid)
    {
        hr=pStid->m_pParentShellFolder->BindToObject(pStid->m_pIDList,
            0, IID_IShellFolder,(LPVOID *)&pShellFolder);
        
        if (SUCCEEDED(hr))
        {
            FillTree(pShellFolder,pStid->m_pFullIDList,pnmtv->itemNew.hItem);
        }
        
        tvscb.hParent     = pnmtv->itemNew.hItem;
        tvscb.lParam      = 0;
        tvscb.lpfnCompare = SortProc;
    }
    
    *pResult=0;
}

HTREEITEM CShellTree::InsertItem(LPSHELLFOLDER pParentShellFolder, LPITEMIDLIST pParentFullIDList,LPITEMIDLIST pIDList,HTREEITEM hParent,HTREEITEM hItem)
{
    TV_ITEM         tvi;
    TV_INSERTSTRUCT tvins;
    LPITEMIDLIST    pFullIDList=NULL;
    CShellTreeItemData *    pStid=NULL;
    LPMALLOC        lpMalloc=NULL;
    HRESULT         hr;
    char            szBuff[_MAX_PATH];
    
    hr = SHGetMalloc(&lpMalloc);
    if (FAILED(hr))
        return NULL;
    
    ULONG ulAttrs = SFGAO_HASSUBFOLDER | SFGAO_FOLDER;
    pParentShellFolder->GetAttributesOf(1, (const struct _ITEMIDLIST **)&pIDList, &ulAttrs);
    if (ulAttrs & SFGAO_FOLDER)
    {
        tvi.mask= TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
        if (ulAttrs & SFGAO_HASSUBFOLDER)
        {
            tvi.cChildren=1;
            tvi.mask |= TVIF_CHILDREN;
        }
        
        pStid = (CShellTreeItemData *)lpMalloc->Alloc(sizeof(CShellTreeItemData));
        if (!pStid)
        {
            lpMalloc->Release();
            return NULL;
        }
        
        if (!GetItemName(pParentShellFolder, pIDList, SHGDN_NORMAL, szBuff))
        {
            lpMalloc->Release();
            return NULL;
        }
        
        tvi.pszText    = szBuff;
        tvi.cchTextMax = _MAX_PATH;
        pFullIDList = ConcatPidl(pParentFullIDList, pIDList);
        
        pStid->m_pIDList = CopyPidl(lpMalloc, pIDList);
        
        tvi.iImage = GetItemIcon(pFullIDList, SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
        tvi.iSelectedImage = GetItemIcon(pFullIDList, SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON |	SHGFI_OPENICON);
        
        pStid->m_pParentShellFolder = pParentShellFolder;
        pParentShellFolder->AddRef();
        
        pStid->m_pFullIDList = ConcatPidl(pParentFullIDList, pIDList);
        
        tvi.lParam = (LPARAM)pStid;
        
        tvins.item         = tvi;
        tvins.hInsertAfter = hItem;
        tvins.hParent      = hParent;
        hItem = CTreeCtrl::InsertItem(&tvins);
        
        lpMalloc->Free(pFullIDList);  
        pFullIDList=NULL;
        
    }
    
    if (lpMalloc) 
        lpMalloc->Release();
    
    TV_SORTCB tvscb;
    tvscb.hParent=hParent;
    tvscb.lParam=0;
    tvscb.lpfnCompare=SortProc;
    
    SortChildrenCB(&tvscb);
    return hItem;
}

void CShellTree::OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
    if(m_Building)
        return;
    
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    
    if(!p_List||!p_List->GetSafeHwnd())
        return;
    
    CString FullPath=GetItemFullPath(pNMTreeView->itemNew.hItem);
    
    ::theApp.SetWindowTitle(FullPath,TRUE);	
    ::theApp.m_UserData.m_LastPath=FullPath;
    
    PopulateList(pNMTreeView->itemNew.hItem);
}

void CShellTree::OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    *pResult = 0;
    
    HRESULT        hr;
    LPMALLOC       lpMalloc;
    CShellTreeItemData *  pStid;
    
    pStid=(CShellTreeItemData *)pNMTreeView->itemOld.lParam;
    if(!pStid)
        return;
    
    hr=SHGetMalloc(&lpMalloc);
    if (FAILED(hr))
        return;
    
    pStid->m_pParentShellFolder->Release();
    lpMalloc->Free(pStid->m_pIDList);  
    lpMalloc->Free(pStid->m_pFullIDList);  
    lpMalloc->Free(pStid);  
    lpMalloc->Release();
    
    *pResult = 0;
}

//函数FindChild，在子项中查找指定目录项
//参数hParent，父目录
//参数pSlid，指定目录项的项数据
//返回查找结果，NULL为查找失败
HTREEITEM CShellTree::FindChild(HTREEITEM hParent, CShellListItemData *pSlid)
{
    //是否包含子项
    if (ItemHasChildren(hParent))
    {
        HTREEITEM hChildItem = GetChildItem(hParent);
        //查看所有子项
        while (hChildItem)
        {
            //比较子项内容
            if(!CompareStid(GetItemData(hChildItem),(LPARAM)pSlid))
                return hChildItem;
            hChildItem = GetNextItem(hChildItem, TVGN_NEXT);
        }
    }
    //查找失败，返回NULL
    return NULL;
}

CString CShellTree::GetItemFullPath(HTREEITEM Item)
{
    CString FullPath;
    
    CShellTreeItemData * pStid=(CShellTreeItemData *)GetItemData(Item);
    if(!pStid)
        return FullPath;
    TCHAR szBuff[_MAX_PATH];
    
    SHGetPathFromIDList(pStid->m_pFullIDList,szBuff);
    FullPath=szBuff;
    
    if(!FullPath.IsEmpty()&&FullPath.Right(1)!='\\')
        FullPath+='\\';
    
    return FullPath;
}

CString CShellTree::GetSelectedItemFullPath()
{
    return GetItemFullPath(GetSelectedItem());
}

void CShellTree::FillSpecialFolders()
{
    HTREEITEM Item;
    LPITEMIDLIST pComputerIDList;
    h_SpecialFolder[m_SpecialFolderCount]=h_Desktop;
    m_SpecialFolder[m_SpecialFolderCount++]=GetItemFullPath(h_Desktop);
    
    if(FAILED(SHGetSpecialFolderLocation(NULL,CSIDL_DRIVES,&pComputerIDList)))
        return;
    
    Item=GetChildItem(h_Desktop);
    while(Item)
    {
        LPARAM lparam=GetItemData(Item);
        
        if(!CompareStid(lparam,pComputerIDList))
            h_Computer=Item;
        else
        {
            m_SpecialFolder[m_SpecialFolderCount]=GetItemFullPath(Item);
            if(!m_SpecialFolder[m_SpecialFolderCount].IsEmpty())
                h_SpecialFolder[m_SpecialFolderCount++]=Item;
        }
        
        Item=this->GetNextSiblingItem(Item);
    }
    Expand(h_Computer,TVE_EXPAND);
    Item=GetChildItem(h_Computer);
    while(Item)
    {
        m_SpecialFolder[m_SpecialFolderCount]=GetItemFullPath(Item);
        if(!m_SpecialFolder[m_SpecialFolderCount].IsEmpty())
            h_SpecialFolder[m_SpecialFolderCount++]=Item;
        
        Item=this->GetNextSiblingItem(Item);
    }
    
    ASSERT(m_SpecialFolderCount<=26);
    
    LPMALLOC lpMalloc=NULL;
    if (FAILED(SHGetMalloc(&lpMalloc)))
        return;
    lpMalloc->Free(pComputerIDList);  
    lpMalloc->Release();
}

HTREEITEM CShellTree::FindChild(HTREEITEM hItem, CString Path)
{
    HTREEITEM hFound=GetChildItem(hItem);
    while (hFound)
    {
        CString Item=GetItemText(hFound);
        Item.MakeUpper();
        if(!Path.Compare(Item))
            return hFound;
        hFound=GetNextItem(hFound,TVGN_NEXT);
    }
    return NULL;
}

void CShellTree::Refresh()
{
    CString FullPath=GetSelectedItemFullPath();
    BuildTree();
    if(!SetSelection(FullPath))
        SelectRootItem();
}

void CShellTree::SelectRootItem()
{
    SelectItem(h_Computer);
}

void CShellTree::ItemUp()
{
    HTREEITEM hItem=GetSelectedItem();
    if(hItem)
    {
        hItem=GetParentItem(hItem);
        if(hItem)
            SelectItem(hItem);
    }
}

BOOL CShellTree::RootReached()
{
    HTREEITEM hItem=GetSelectedItem();
    return (!hItem||hItem==h_Desktop);
}

//函数PopulateList，展开指定目录项
//参数Item，指定目录项
void CShellTree::PopulateList(HTREEITEM Item)
{
    CShellTreeItemData *pStid;
    LPSHELLFOLDER pShellFolder = NULL;
    HRESULT hr;
    
    pStid = (CShellTreeItemData *)GetItemData(Item);
    if(pStid)
    {
        //顶级目录
        if(Item == h_Desktop)
        {
            p_List->PopulateList(pStid->m_pParentShellFolder,pStid,Item);
            return;
        }
        
        hr = pStid->m_pParentShellFolder->BindToObject(pStid->m_pIDList,
            0,IID_IShellFolder,(LPVOID *)&pShellFolder);
        
        //显示文件列表
        if(SUCCEEDED(hr))
            p_List->PopulateList(pShellFolder,pStid,Item);
    }
}
