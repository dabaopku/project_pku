// stdafx.cpp : source file that includes just the standard includes
//	FlashNow.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

CString EXE_TYPE=".exe";
CString SWF_TYPE=".swf";

BOOL IsRemoteURL(CString URL)
{
	return (URL.Left(7)=="http://");
}

COLORREF Rgb2Bgr(COLORREF Color)
{
	return (Color&0xff)<<16|(Color&0xff00)|(Color&0xff0000)>>16;
}

CString GetTempFileName(CString Ext)
{
	CString TempFileName;

	TCHAR TempPath[_MAX_PATH];
	GetTempPath(_MAX_PATH,TempPath);
	
	srand((unsigned)time(NULL));
	TempFileName.Format("%smovie%08d.%s",TempPath,rand(),Ext);
	return TempFileName;
}

CString GetFilePathFromFileName(CString FileName)
{
	int Where;
	Where=FileName.ReverseFind('\\');
	if(Where==-1)
		Where=FileName.ReverseFind('/');
	CString FilePath=FileName.Left(Where);
	return FilePath+'\\';
}

CString GetFileTitleFromFileName(CString FileName,BOOL Ext)
{
	int Where;
	Where=FileName.ReverseFind('\\');
	if(Where==-1)
		Where=FileName.ReverseFind('/');
	CString FileTitle=FileName.Right(FileName.GetLength()-1-Where);
	if(!Ext)
	{
		int Which=FileTitle.ReverseFind('.');
		if(Which!=-1)
			FileTitle=FileTitle.Left(Which);
	}
	return FileTitle;
}

int MultiLineTextOut(CDC *pDC,int x,int y,int LineSpace,CString Text)
{
	int Lines=0;
	int Length=Text.GetLength();
	int Start=0;
	for(int i=0;i<Length;i++)
	{
		if(Text.GetAt(i)=='\n')
		{
			Lines++;
			pDC->TextOut(x,y,Text.Mid(Start,i-Start));
			y+=LineSpace;
			Start=i+1;
		}
	}
	pDC->TextOut(x,y,Text.Mid(Start,i-Start));
	return Lines;
}