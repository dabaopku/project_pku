// MsgInfo.h: interface for the CMsgInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGINFO_H__A3CCEDAC_E0D0_44B2_99B7_27B774DDC367__INCLUDED_)
#define AFX_MSGINFO_H__A3CCEDAC_E0D0_44B2_99B7_27B774DDC367__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UserInfo.h"

class CMsgInfo 
{
public:

	CUserInfo m_FromUser;
	char m_Msg[250];
	long m_Time;

	CMsgInfo();
	virtual ~CMsgInfo();

};

#endif // !defined(AFX_MSGINFO_H__A3CCEDAC_E0D0_44B2_99B7_27B774DDC367__INCLUDED_)
