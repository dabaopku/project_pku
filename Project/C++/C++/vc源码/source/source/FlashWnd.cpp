// FlashWnd.cpp : implementation file
//

#include "stdafx.h"
#include "flashnow.h"
#include "FlashWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlashWnd

CFlashWnd::CFlashWnd()
{
	m_Type=0;
	m_TempFileName=GetTempFileName(SWF_TYPE);
}

CFlashWnd::~CFlashWnd()
{
}


BEGIN_MESSAGE_MAP(CFlashWnd, CWnd)
	//{{AFX_MSG_MAP(CFlashWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFlashWnd message handlers
BOOL CFlashWnd::Create(CWnd* pParentWnd,DWORD style)
{
	CRect Client;
	pParentWnd->GetClientRect(&Client);
	if(!CShockwaveFlash::Create("ShockwaveFlash",style,Client,pParentWnd,0))
		return FALSE;	
	SetBackgroundColor(GetSysColor(COLOR_WINDOW));
	return TRUE;
}

BOOL CFlashWnd::SetMovie(CString FolderPath)
{
	m_DisplayName=FolderPath;
	CShockwaveFlash::SetMovie("");
	CShockwaveFlash::SetBackgroundColor(GetSysColor(COLOR_WINDOW));
	CShockwaveFlash::SetBGColor("");

	if(FolderPath=="")
		return FALSE;

	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath(FolderPath,drive,dir,fname,ext);
	if(!SWF_TYPE.CompareNoCase(ext))
	{
		CShockwaveFlash::SetMovie(FolderPath);
		return TRUE;
	}
	if(!EXE_TYPE.CompareNoCase(ext))
	{
		CFile File;
		CFile TmpFile;

		TCHAR Mark[4];
		if(File.Open(FolderPath,CFile::modeRead))
		{
			File.Seek(SWF_OFFSET,CFile::begin);
			if(File.Read(Mark,3))
			{
				Mark[3]='\0';
				if(!strcmp(Mark,"FWS"))
				{
					if(TmpFile.Open(m_TempFileName,CFile::modeCreate|CFile::modeWrite))
					{
						char Buffer[BUFFER_SIZE];
						File.Seek(SWF_OFFSET,CFile::begin);
						while(1)
						{
							int Count=File.Read(Buffer,BUFFER_SIZE);
							if(Count)
								TmpFile.Write(Buffer,Count);
							if(Count<BUFFER_SIZE)
								break;
						}
						TmpFile.Close();
						CShockwaveFlash::SetMovie(m_TempFileName);
						DeleteFile(m_TempFileName);
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

BOOL CFlashWnd::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_RBUTTONDOWN)	
	{
		if(!GetMenu()||GetReadyState()!=4)
			pMsg->message=0;
	}
	return CWnd::PreTranslateMessage(pMsg);
}

void CFlashWnd::SaveAs(CString FileName)
{
	if(!DoSaveAs(FileName))
	{
		CString Warning="保存如下文件时发生错误：\n";
		Warning+=FileName;
	
		::MessageBox(NULL,Warning,"警告",MB_OK|MB_ICONINFORMATION);
	}
}

void CFlashWnd::SetBackgroundColor(COLORREF BackColor)
{
	CShockwaveFlash::SetBackgroundColor(Rgb2Bgr(BackColor));
}

COLORREF CFlashWnd::GetBackgroundColor()
{
	return Rgb2Bgr(CShockwaveFlash::GetBackgroundColor());
}

CString CFlashWnd::GetMovie()
{
	return m_DisplayName;
}

BOOL CFlashWnd::DoSaveAs(CString FileName)
{
	CString Source=GetMovie();
	CFile File;
	if(!IsRemoteURL(Source))
	{
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];

		_splitpath(Source,drive,dir,fname,ext);
		if(!SWF_TYPE.CompareNoCase(ext))
		{
			return CopyFile(Source,FileName,FALSE);
		}

		if(!EXE_TYPE.CompareNoCase(ext))
		{
			CFile File;
			CFile Target;

			TCHAR Mark[4];
			if(File.Open(Source,CFile::modeRead))
			{
				File.Seek(SWF_OFFSET,CFile::begin);
				if(File.Read(Mark,3))
				{
					Mark[3]='\0';
					if(!strcmp(Mark,"FWS"))
					{
						if(Target.Open(FileName,CFile::modeCreate|CFile::modeWrite))
						{
							File.Seek(SWF_OFFSET,CFile::begin);
							char Buffer[BUFFER_SIZE];
							while(1)
							{
								int Count=File.Read(Buffer,BUFFER_SIZE);
								if(Count)
									Target.Write(Buffer,Count);
								if(Count<BUFFER_SIZE)
									break;
							}
							Target.Close();
							return TRUE;
						}
					}
				}
			}
		}
		return FALSE;
	}
	CInternetSession Session;
	char Buffer[BUFFER_SIZE];
	CString Headers;
	CHttpFile *pFile;
	pFile=(CHttpFile *)Session.OpenURL(Source);
	if(pFile)
	{
		pFile->AddRequestHeaders(Headers);
		CFile Target;
		if(Target.Open(FileName,CFile::modeCreate|CFile::modeWrite))
		{
			while(1)
			{
				int Count=pFile->Read(Buffer,BUFFER_SIZE);
				if(Count)
					Target.Write(Buffer,Count);
				if(Count<BUFFER_SIZE)
					break;
			}
			Target.Close();
			delete pFile;
			Session.Close();
			return TRUE;
		}
	}
	return FALSE;
}
