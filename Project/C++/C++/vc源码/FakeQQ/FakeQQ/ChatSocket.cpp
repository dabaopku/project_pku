// ChatSocket.cpp : implementation file
//

#include "stdafx.h"
#include "FakeQQ.h"
#include "MsgInfo.h"
#include "ChatSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatSocket

CChatSocket::CChatSocket()
{
}

CChatSocket::~CChatSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CChatSocket, CSocket)
	//{{AFX_MSG_MAP(CChatSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CChatSocket member functions

void CChatSocket::OnReceive(int nErrorCode) 
{
	CMsgInfo * pMsg = new CMsgInfo();
	CString FromIp;
	UINT FromPort;
	if(ReceiveFrom(pMsg, sizeof(CMsgInfo), FromIp, FromPort) != SOCKET_ERROR)
	{
		PlaySound("msg.wav", NULL, SND_FILENAME | SND_ASYNC);

		strcpy(pMsg->m_FromUser.m_Ip, FromIp);
		pMsg->m_FromUser.m_Port = FromPort;

		CThreadData * pData = new CThreadData();
		pData->m_pMsg = pMsg;
		pData->m_pSocket = this;

		AfxBeginThread(ThreadOnReceive, pData);	
	}
	CSocket::OnReceive(nErrorCode);
}

UINT CChatSocket::ThreadOnReceive(LPVOID pParam)
{
		//将消息压入消息队列

		CThreadData * pData = (CThreadData *)pParam;
		pData->m_pSocket->m_pDlg->PushMsg(pData->m_pMsg);

		delete pData;
		return 0;
}
