// Shell.cpp: implementation of the CShell class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "flashnow.h"
#include "Shell.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
HIMAGELIST CShell::h_SmallImageList=NULL;
HIMAGELIST CShell::h_LargeImageList=NULL;
CImageList CShell::m_SmallImageList;
CImageList CShell::m_LargeImageList;

CShell::CShell()
{
	m_ShowHidden=FALSE;
	m_Building=FALSE;
}

CShell::~CShell()
{
	if(h_SmallImageList)
	{
		m_SmallImageList.Detach();
		h_SmallImageList=NULL;
	}
	if(h_LargeImageList)
	{
		m_LargeImageList.Detach();
		h_LargeImageList=NULL;
	}
}

CImageList * CShell::GetImageList(BOOL Small)
{
	SHFILEINFO shFinfo;
	
	if(!Small)
	{
		if(h_LargeImageList)
			return &m_LargeImageList;
		
		h_LargeImageList=(HIMAGELIST)SHGetFileInfo("C:\\",
			0,
			&shFinfo,
			sizeof(shFinfo),
			SHGFI_SYSICONINDEX | 
			SHGFI_LARGEICON);
		if(!h_LargeImageList)
			return NULL;
		
		m_LargeImageList.Attach(h_LargeImageList);
		return &m_LargeImageList;		
	}
	
	else
	{
		if(h_SmallImageList)
			return &m_SmallImageList;
		
		h_SmallImageList=(HIMAGELIST)SHGetFileInfo("C:\\",
			0,
			&shFinfo,
			sizeof(shFinfo),
			SHGFI_SYSICONINDEX | 
			SHGFI_SMALLICON);
		if(!h_SmallImageList)
			return NULL;
		
		m_SmallImageList.Attach(h_SmallImageList);
		return &m_SmallImageList;
	}
}

LPITEMIDLIST CShell::ConcatPidl(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
{
    LPITEMIDLIST pidlNew;
    UINT cb1;
    UINT cb2;
	
    if (pidl1)
		cb1 = GetSize(pidl1) - sizeof(pidl1->mkid.cb);
    else
		cb1 = 0;
	
    cb2 = GetSize(pidl2);
	
    pidlNew = CreatePidl(cb1 + cb2);
    if (pidlNew)
    {
        if (pidl1)
			memcpy(pidlNew, pidl1, cb1);
        memcpy(((LPTSTR)pidlNew) + cb1, pidl2, cb2);
    }
    return pidlNew;
}

LPITEMIDLIST CShell::CreatePidl(UINT cbSize)
{
    LPMALLOC lpMalloc;
    HRESULT  hr;
    LPITEMIDLIST pidl=NULL;
	
    hr=SHGetMalloc(&lpMalloc);
	
    if (FAILED(hr))
		return 0;
	
    pidl=(LPITEMIDLIST)lpMalloc->Alloc(cbSize);
	
    if (pidl)
        memset(pidl, 0, cbSize);      // zero-init for external task   alloc
	
    if (lpMalloc) lpMalloc->Release();
	
    return pidl;
}

LPITEMIDLIST CShell::CopyPidl(LPMALLOC lpMalloc, LPITEMIDLIST lpi)
{
	LPITEMIDLIST lpiTemp;
	
	lpiTemp=(LPITEMIDLIST)lpMalloc->Alloc(lpi->mkid.cb+sizeof(lpi->mkid.cb));
	CopyMemory((PVOID)lpiTemp, (CONST VOID *)lpi, lpi->mkid.cb+sizeof(lpi->mkid.cb));
	
	return lpiTemp;
}

UINT CShell::GetSize(LPCITEMIDLIST pidl)
{
    UINT cbTotal = 0;
    if (pidl)
    {
        cbTotal += sizeof(pidl->mkid.cb);
        while (pidl->mkid.cb)
        {
            cbTotal += pidl->mkid.cb;
			LPTSTR lpMem=(LPTSTR)pidl;
			lpMem+=pidl->mkid.cb;
			pidl = (LPITEMIDLIST)lpMem;
        }
    }
	
    return cbTotal;
}

BOOL CShell::GetItemName(LPSHELLFOLDER lpsf, LPITEMIDLIST lpi, DWORD dwFlags, LPTSTR lpFriendlyName)
{
	BOOL   bSuccess=TRUE;
	STRRET str;
	
	if (NOERROR==lpsf->GetDisplayNameOf(lpi,dwFlags, &str))
	{
		switch (str.uType)
		{
		case STRRET_WSTR:
			WideCharToMultiByte(CP_ACP, 
				0,
				str.pOleStr,
				-1,
				lpFriendlyName,
				_MAX_PATH,
				NULL,
				NULL);
			
			break;
		case STRRET_OFFSET:
			lstrcpy(lpFriendlyName, (LPTSTR)lpi+str.uOffset);
			break;
		case STRRET_CSTR:
			lstrcpy(lpFriendlyName, (LPTSTR)str.cStr);
			break;
		default:
			bSuccess = FALSE;
			break;
		}
	}
	else
		bSuccess = FALSE;
	
	return bSuccess;
}

int CShell::GetItemIcon(LPITEMIDLIST lpi, UINT uFlags)
{
	SHFILEINFO    sfi;
	GetFileInfo(lpi,uFlags,&sfi);
	return sfi.iIcon;
}

void CShell::ShowHidden(BOOL Hidden)
{
	m_ShowHidden=Hidden;
}

void CShell::GetFileInfo(LPITEMIDLIST lpi, UINT uFlags, SHFILEINFO *psfi)
{
	SHGetFileInfo((LPCSTR)lpi, 
		0,
		psfi, 
		sizeof(SHFILEINFO), 
		uFlags);
}

int CShell::CompareStid(LPARAM lparam1, LPARAM lparam2)
{
    CShellTreeItemData * pStid=(CShellTreeItemData *)lparam2;
	
    return (short)CompareStid(lparam1,pStid->m_pIDList);
}

int CALLBACK CShell::SortProc(LPARAM lparam1, LPARAM lparam2, LPARAM lparamSort)
{
	return CompareStid(lparam1,lparam2);
}

int CShell::CompareStid(LPARAM lparam, LPCITEMIDLIST pIDList)
{
    CShellTreeItemData * pStid=(CShellTreeItemData *)lparam;
    HRESULT   hr;
	
    hr = pStid->m_pParentShellFolder->CompareIDs(0,pStid->m_pIDList,pIDList);
	
    if (FAILED(hr))
		return 0;
	
    return (short)SCODE_CODE(GetScode(hr));
}

BOOL CShell::IsValidPath(CString Path)
{
	Path+="*.*";
	CFileFind Finder;
	return Finder.FindFile(Path);
}

int CALLBACK CShell::Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	return 0;
}
