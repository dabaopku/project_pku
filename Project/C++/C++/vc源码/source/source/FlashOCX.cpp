// FlashOCXRegister.cpp: implementation of the CFlashOCX class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FlashNow.h"
#include "FlashOCX.h"

#ifdef _DEBUG
#undef THIS_FILE
static TCHAR THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void CFlashOCX::Register()
{
	BOOL bResult=FALSE;
	TCHAR Path[_MAX_PATH];
	
	GetSystemDirectory(Path,_MAX_PATH);
	CString Target=Path;
	Target+="\\cswflash.ocx";
	CString Source=::theApp.m_ModuleFilePath+"cswflash.ocx";
	
	BOOL Result=FALSE;
	CString Warning;
	
	if(CopyFile((LPTSTR)(LPCTSTR)Source,Target,FALSE))
	{
		HMODULE hModule=LoadLibrary(Target);
		if(hModule)
		{
			FARPROC DLLRegisterServer=(FARPROC)GetProcAddress(hModule,"DllRegisterServer");
			if(DLLRegisterServer)
			{
				HRESULT regResult=DLLRegisterServer();
				if(regResult==NOERROR)
					Result=TRUE;
				else
					Warning="注册SWFlash控件时发生错误！";
			}
			FreeLibrary(hModule);
		}
	}
	else
		Warning="复制SWFlash控件文件时发生错误！\r\nFlashNow! 可能不能正常运行，请确认以下文件是否存在：\r\n" + Source;
	
	if(!Result)
		MessageBox(NULL,Warning,"警告",MB_OK|MB_ICONINFORMATION);
	
	m_Registered=Result;
}

CFlashOCX::CFlashOCX()
{
	CRegKey RegKey;
	DWORD Size=_MAX_PATH;
	TCHAR OCXPath[_MAX_PATH];
	if(RegKey.Open(HKEY_CLASSES_ROOT,"CLSID\\{D27CDB6E-AE6D-11cf-96B8-444553540000}\\InprocServer32")==ERROR_SUCCESS
		&&RegKey.QueryValue(OCXPath,"",&Size)==ERROR_SUCCESS)
	{
		RegKey.Close();
		m_OCXPath=OCXPath;
		m_OCXPath.MakeLower();

		if(!m_OCXPath.IsEmpty())
		{
			CFileStatus Status;
			if(CFile::GetStatus(m_OCXPath,Status))
			{
				m_Registered=TRUE;
				return;
			}
		}
	}

	m_Registered=FALSE;
}

BOOL CFlashOCX::IsChineseVersion()
{
	return (GetFileTitleFromFileName(m_OCXPath)=="cswflash.ocx");
}
