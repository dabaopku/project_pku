// ShellList.cpp : implementation file
//

#include "stdafx.h"
#include "flashnow.h"
#include "ShellList.h"
#include "BrowserList.h"
#include "BrowserFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShellList

CShellList::CShellList()
{
    p_Tree=NULL;
    h_TreeItem=NULL;
    m_ViewStyle=2;
    m_Refresh=FALSE;
    m_ShowFlashOnly=FALSE;
}

CShellList::~CShellList()
{
    m_LargeList.Detach();
    m_SmallList.Detach();
}


BEGIN_MESSAGE_MAP(CShellList, CListCtrl)
//{{AFX_MSG_MAP(CShellList)
ON_NOTIFY_REFLECT(NM_RCLICK, OnRClick)
ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblClick)
ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemChanged)
ON_WM_CREATE()
ON_NOTIFY_REFLECT(LVN_DELETEITEM, OnDeleteItem)
ON_WM_CHAR()
ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndLabelEdit)
ON_WM_KEYUP()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShellList message handlers

void CShellList::OnRClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    HD_NOTIFY *phdn=(HD_NOTIFY *)pNMHDR;
    if(phdn->iItem<0)
    {
        POINT pt;
        GetCursorPos(&pt);
        
        CMenu Menu;
        Menu.LoadMenu(IDM_LIST_POP);
        CMenu* pMenu = Menu.GetSubMenu(0);
        pMenu->TrackPopupMenu(TPM_RIGHTBUTTON,pt.x,pt.y,::theApp.p_Browser);
    }
    else
    {
        OnItemRClick(phdn->iItem);
    }
}

void CShellList::OnDblClick(NMHDR* pNMHDR, LRESULT* pResult)
{
    HD_NOTIFY *phdn=(HD_NOTIFY *)pNMHDR;
    if(phdn->iItem<0)
        return;
    m_SelectedItem=phdn->iItem;
    OnItemAction(m_SelectedItem);
    *pResult=0;
}

void CShellList::OnItemChanged(NMHDR *pNMHDR, LRESULT *pResult)
{
    if(m_Building)
        return;
    HD_NOTIFY *phdn=(HD_NOTIFY *)pNMHDR;
    if(phdn->iItem<0)
        return;
    if(!IsSelectedItem(phdn->iItem))
        return;
    m_SelectedItem=phdn->iItem;
    OnItemSelected(phdn->iItem);
    *pResult=0;
}

CString CShellList::GetSelectedItemFullPath()
{
    return GetItemFullPath(m_SelectedItem);
}

void CShellList::ShowFileInfo(CBrowserList *pList,int Which,CString FullPath)
{
    CString FileInfo;	
    FileInfo+=""+GetItemText(Which,0);
    FileInfo+="\n"+GetItemText(Which,2);
    FileInfo+="\n\n"+GetItemText(Which,1);
    
    DWORD fa=GetFileAttributes(FullPath);
    if(fa!=-1)
    {
        CString Property;
        if((fa & FILE_ATTRIBUTE_SYSTEM ) == FILE_ATTRIBUTE_SYSTEM )
            Property+=" 系统";
        if((fa & FILE_ATTRIBUTE_READONLY ) == FILE_ATTRIBUTE_READONLY )
            Property+=" 只读";
        if((fa & FILE_ATTRIBUTE_HIDDEN ) == FILE_ATTRIBUTE_HIDDEN )
            Property+=" 隐藏";
        
        FileInfo+="\n修改时间: "+GetItemText(Which,3);
        FileInfo+="\n属性:"+(Property.IsEmpty()?" (正常)":Property);
    }
    
    pList->SetFileInfo(FileInfo);
}

void CShellList::AssociateTree(CShellTree *pTree)
{
    p_Tree=pTree;
}

int CShellList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CListCtrl::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    InsertColumn(0,"名称",LVCFMT_LEFT,120);
    InsertColumn(1,"大小",LVCFMT_RIGHT,60);
    InsertColumn(2,"类型",LVCFMT_LEFT,100);
    InsertColumn(3,"修改时间",LVCFMT_LEFT,100);
    
    SetImageList();
    return 0;
}

void CShellList::SetImageList()
{
    CListCtrl::SetImageList(CShell::GetImageList(FALSE),LVSIL_NORMAL);
    CListCtrl::SetImageList(CShell::GetImageList(TRUE),LVSIL_SMALL);
}

//函数PopulateList，展开指定目录项
//参数pParentShellFolder，父目录
//参数pStid，指定目录项的项数据
//参数hItem，指定目录项
//返回操作结果，TRUE/FALSE
BOOL CShellList::PopulateList(LPSHELLFOLDER pParentShellFolder,CShellTreeItemData * pStid,HTREEITEM hItem)
{
    LV_ITEM lvi;
    int nPos = 0; 
    LPENUMIDLIST lpe = NULL;
    LPITEMIDLIST pIDList = NULL,pFullIDList = NULL;
    LPMALLOC lpMalloc = NULL;
    ULONG ulFetched;
    HRESULT hr;
    TCHAR szBuff[_MAX_PATH];
    SHFILEINFO sfi;
    CShellListItemData * pSlid = NULL;
    CString FullPath;
    CString DisplayName;
    
    m_Building = TRUE;
    
    SetRedraw(FALSE);
    
    CBrowserList *pList = (CBrowserList *)GetParent();
    pList->Preview("");
    
    SetViewStyle();
    DeleteAllItems();
    
    m_SelectedItem = -1;
    
    //分配内存
    hr = SHGetMalloc(&lpMalloc);
    if (FAILED(hr))
        return FALSE;
    
    //设置显示标志
    DWORD dwFlags = SHCONTF_FOLDERS | SHCONTF_NONFOLDERS;
    if( m_ShowHidden )
        dwFlags |= SHCONTF_INCLUDEHIDDEN;
    
    hr = pParentShellFolder->EnumObjects(GetSafeHwnd(), dwFlags, &lpe);
    h_TreeItem = hItem;
    
    if (SUCCEEDED(hr))
    {
        //枚举父目录下的文件
        while (S_OK == lpe->Next(1, &pIDList, &ulFetched))
        {
            pSlid = (CShellListItemData *)lpMalloc->Alloc(sizeof(CShellListItemData));
            if (!pSlid)
                goto Done;
            
            //获取文件属性
            ULONG ulAttrs = SFGAO_FOLDER ;
            
            pParentShellFolder->GetAttributesOf(1, (const struct _ITEMIDLIST **)&pIDList, &ulAttrs);
            pSlid->m_Attribute = ulAttrs;
            
            pFullIDList=ConcatPidl(pStid->m_pFullIDList,pIDList);
            
            pSlid->m_pParentShellFolder = pParentShellFolder;
            pParentShellFolder->AddRef();
            
            pSlid->m_pIDList = CopyPidl(lpMalloc, pIDList);
            
            GetFileInfo(pFullIDList,SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_TYPENAME | SHGFI_ATTRIBUTES,&sfi);
            lvi.iImage = sfi.iIcon; 
            pSlid->m_pFullIDList = ConcatPidl(pStid->m_pFullIDList, pIDList);
            
            SHGetPathFromIDList(pSlid->m_pFullIDList,szBuff);
            FullPath = szBuff;
            pSlid->m_Flag = GetItemFlag(sfi,FullPath);
            
            if (!GetItemName(pParentShellFolder, pIDList, SHGDN_NORMAL, szBuff))
                goto Done;
            
            lvi.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_PARAM;
            lvi.iItem = nPos;
            lvi.iSubItem = 0;
            lvi.pszText = szBuff;
            lvi.cchTextMax = _MAX_PATH;
            lvi.lParam = (LPARAM)pSlid;
            //添加至文件列表
            nPos = CListCtrl::InsertItem(&lvi);
            
            if(m_ShowFlashOnly&&(pSlid->m_Attribute & SFGAO_FOLDER) != SFGAO_FOLDER&&!pSlid->m_Flag)
            {
                DeleteItem(nPos);
            }
            else
            {
                InsertSubItems(nPos,sfi,FullPath);
                nPos++;
            }
            lpMalloc->Free(pFullIDList);  
            pFullIDList=0;
        }		
    }
    
Done:
    
    //释放内存
    if (lpe)  
        lpe->Release();
    
    if (lpMalloc) 
        lpMalloc->Release();
    
    m_Building = FALSE;
    
    if(!m_Refresh)
        ::theApp.p_Browser->AddHistoryRecord(hItem);
    SortItems(SortProc, (LPARAM)this);
    
    SetRedraw(TRUE);
    
    return TRUE;
}

void CShellList::OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult) 
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    HRESULT hr;
    LPMALLOC lpMalloc;
    CShellListItemData *   pSlid = (CShellListItemData *)pNMListView->lParam;
    
    if(!pSlid)
        return;
    
    hr=SHGetMalloc(&lpMalloc);
    if (FAILED(hr)) 
        return;
    
    lpMalloc->Free(pSlid->m_pIDList);  
    lpMalloc->Free(pSlid->m_pFullIDList);  
    lpMalloc->Free(pSlid);  
    lpMalloc->Release();
    
    *pResult = 0;
}

void CShellList::SetViewStyle(int ViewStyle)
{
    if(m_ViewStyle!=ViewStyle)
    {
        m_ViewStyle=ViewStyle;
        Refresh();
    }
}

BOOL CShellList::GetViewStyle(int ViewStyle)
{
    return (m_ViewStyle==ViewStyle);
}

void CShellList::InsertSubItems(int Which,SHFILEINFO sfi,CString FullPath)
{
    //AssociateTree() should be called before
    ASSERT(p_Tree);
    
    CFileFind Finder;
    CString Path;
    SetItemText(Which,2,sfi.szTypeName);
    
    Path=GetItemFullPath(Which);
    if(Finder.FindFile(Path))
    {
        Finder.FindNextFile();
        CString Text;
        DWORD Size;
        CTime Time;
        Size=Finder.GetLength();
        if((sfi.dwAttributes & SFGAO_FOLDER) != SFGAO_FOLDER)
        {
            Text.Format("%ldKB",(Size+1023)/1024);
            SetItemText(Which,1,Text);
        }
        Finder.GetLastWriteTime(Time);
        Text.Format("%04d-%02d-%02d %02d:%02d",Time.GetYear(),Time.GetMonth(),Time.GetDay(),Time.GetHour(),Time.GetMinute());
        SetItemText(Which,3,Text);
    }
}

CString CShellList::GetItemFullPath(int Which)
{
    CString FullPath;
    CShellListItemData * pSlid=(CShellListItemData *)GetItemData(Which);
    if(!pSlid)
        return FullPath;
    TCHAR szBuff[_MAX_PATH];
    
    SHGetPathFromIDList(pSlid->m_pFullIDList,szBuff);
    FullPath=szBuff;
    return FullPath;
}

BOOL CShellList::IsFolder(int Which)
{
    LV_ITEM lvi;
    lvi.mask = LVIF_PARAM;
    lvi.iItem = Which;
    lvi.iSubItem = 0;
    
    if (!GetItem(&lvi))
        return FALSE;
    
    CShellListItemData * pSlid=(CShellListItemData *)lvi.lParam;
    
    return ((pSlid->m_Attribute & SFGAO_FOLDER) == SFGAO_FOLDER);
}

void CShellList::OnItemDblClick(int Which)
{
    if(!IsMovie(Which))
    {
        CString FullPath=GetItemFullPath(Which);
        ShellExecute(NULL,"open",FullPath,NULL,NULL,SW_SHOW);
    }
    else
        ::theApp.SwitchToViewer();
}

void CShellList::OnItemSelected(int Which)
{
    if(!IsWindowVisible())
        return;
    CBrowserList *pList=(CBrowserList *)GetParent();
    CString FullPath=GetItemFullPath(Which);
    ShowFileInfo(pList,Which,FullPath);
    pList->Preview(IsMovie(Which)?FullPath:"");
}

int CShellList::SetSelection(CString FullPath)
{
    CString Title=GetFileTitleFromFileName(FullPath);
    int Which=-1;
    for(int i=0;i<GetItemCount();i++)
    {
        if(IsMovie(i)&&!Title.CompareNoCase(GetFileTitleFromFileName(GetItemFullPath(i))))
        {
            Which=i;
            break;
        }
    }
    SelectItem(Which);
    return Which;
}

void CShellList::SelectItem(int Which)
{
    SetItemState(Which,LVIS_SELECTED|LVIS_FOCUSED,0xff);
}

int CShellList::GetItemFlag(SHFILEINFO sfi,CString FullPath)
{
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    
    if((sfi.dwAttributes & SFGAO_FOLDER) == SFGAO_FOLDER)
        return 0;
    
    _splitpath(FullPath,drive,dir,fname,ext);
    if(!SWF_TYPE.CompareNoCase(ext))
        return 1;
    if(!EXE_TYPE.CompareNoCase(ext))
    {
        CFile File;
        TCHAR Mark[4];
        if(File.Open(FullPath,CFile::modeRead))
        {
            File.Seek(SWF_OFFSET,CFile::begin);
            if(File.Read(Mark,3))
            {
                Mark[3]='\0';
                if(!strcmp(Mark,"FWS"))
                    return 2;
            }
        }
    }
    return 0;
}

BOOL CShellList::IsMovie(int Which)
{
    if(Which<0||Which>=GetItemCount())
        return FALSE;
    return GetItemFlag(Which);
}

int CShellList::GetItemFlag(int Which)
{
    CShellListItemData * pSlid=(CShellListItemData *)GetItemData(Which);
    if(!pSlid)
        return 0;
    return pSlid->m_Flag;
}

BOOL CShellList::IsSelectedItem(int Which)
{
    return(GetItemState(Which,LVIS_SELECTED)==LVIS_SELECTED);
}

void CShellList::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    if(nChar==VK_RETURN)
    {
        OnItemAction(m_SelectedItem);
    }
    CListCtrl::OnChar(nChar, nRepCnt, nFlags);
}

void CShellList::OnItemAction(int Item)
{
    CShellListItemData * pSlid=(CShellListItemData *)GetItemData(Item);
    
    if ((pSlid->m_Attribute & SFGAO_FOLDER) == SFGAO_FOLDER) 
    {
        p_Tree->Expand(h_TreeItem,TVE_EXPAND);
        HTREEITEM hChildItem=p_Tree->FindChild(h_TreeItem,pSlid);
        if(hChildItem)
            p_Tree->SelectItem(hChildItem);
    }
    else
    {
        OnItemDblClick(Item);
    }
}

void CShellList::OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult) 
{
    LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
    CString Text=pDispInfo->item.pszText;
    HD_NOTIFY *phdn=(HD_NOTIFY *)pNMHDR;
    if(phdn->iItem<0)
        return;
    
    if(!Text.IsEmpty()&&MoveFile(GetSelectedItemFullPath(),p_Tree->GetItemFullPath(h_TreeItem)+Text))
    {
        ::theApp.p_Browser->OnViewRefresh();
    }
    *pResult = 0;
}

void CShellList::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    if(m_SelectedItem!=-1&&nChar==VK_DELETE)	
    {
        ::theApp.p_Browser->OnFileDelete();
    }
    CListCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CShellList::Refresh()
{
    if(!h_TreeItem)
        return;
    m_Refresh=TRUE;
    p_Tree->PopulateList(h_TreeItem);	
    m_Refresh=FALSE;
}

void CShellList::SetViewStyle()
{
    DWORD Style;
    switch(m_ViewStyle)
    {
    case 0:Style=LVS_ICON;
        break;
    case 3:Style=LVS_REPORT;
        break;
    case 2:Style=LVS_LIST;
        break;
    case 1:Style=LVS_SMALLICON;
        break;
    }
    ModifyStyle(LVS_TYPEMASK,Style);
}

void CShellList::OnItemRClick(int Item)
{
    POINT pt;
    GetCursorPos(&pt);
    
    CMenu Menu;
    Menu.LoadMenu(IDM_ITEM_POP);
    CMenu* pMenu = Menu.GetSubMenu(0);
    pMenu->TrackPopupMenu(TPM_RIGHTBUTTON,pt.x,pt.y,::theApp.p_Browser);
}
