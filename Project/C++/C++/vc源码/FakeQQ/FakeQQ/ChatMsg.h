// ChatMsg.h: interface for the CChatMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHATMSG_H__3D458214_9DB1_4385_B881_E96F4FC89FB0__INCLUDED_)
#define AFX_CHATMSG_H__3D458214_9DB1_4385_B881_E96F4FC89FB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CChatMsg
{
public:
	char m_FromIp[20];
	char m_FromUser[20];
	UINT m_FromPort;
	char m_Msg[100];
	CChatMsg();
	virtual ~CChatMsg();

};

#endif // !defined(AFX_CHATMSG_H__3D458214_9DB1_4385_B881_E96F4FC89FB0__INCLUDED_)
