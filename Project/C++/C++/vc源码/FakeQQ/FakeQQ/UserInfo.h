// UserInfo.h: interface for the CUserInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERINFO_H__1A518BA1_8BBD_4D71_8D0D_53CCD8961F3A__INCLUDED_)
#define AFX_USERINFO_H__1A518BA1_8BBD_4D71_8D0D_53CCD8961F3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUserInfo  
{
public:

	char m_UserName[20];
	char m_Ip[20];
	UINT m_Port;
	int m_Face;

	CUserInfo();
	virtual ~CUserInfo();

};

#endif // !defined(AFX_USERINFO_H__1A518BA1_8BBD_4D71_8D0D_53CCD8961F3A__INCLUDED_)
