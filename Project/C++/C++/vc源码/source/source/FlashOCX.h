// FlashOCXRegister.h: interface for the CFlashOCX class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLASHOCXREGISTER_H__893A2425_3EFB_11D5_953D_F7A78B699621__INCLUDED_)
#define AFX_FLASHOCXREGISTER_H__893A2425_3EFB_11D5_953D_F7A78B699621__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFlashOCX
{
public:
	CFlashOCX();
	CString m_OCXPath;
	BOOL m_Registered;
	void Register();
	BOOL IsChineseVersion();
};

#endif // !defined(AFX_FLASHOCXREGISTER_H__893A2425_3EFB_11D5_953D_F7A78B699621__INCLUDED_)
