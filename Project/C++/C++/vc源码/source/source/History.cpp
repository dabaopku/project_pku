// History.cpp: implementation of the CHistory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "flashnow.h"
#include "History.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHistory::CHistory()
{
	p_Current=&m_Head;
	p_Current->p_Back=&m_Head;
}

CHistory::~CHistory()
{
	Clear();
}

CHistoryRecord::CHistoryRecord()
{
	p_Back=p_Next=NULL;
}

void CHistory::Add(HTREEITEM hItem)
{
	Clear(p_Current);
	CHistoryRecord *pRecord=new CHistoryRecord();
	pRecord->h_Item=hItem;
	p_Current->p_Next=pRecord;
	pRecord->p_Back=p_Current;

	p_Current=pRecord;
}

void CHistory::Clear(CHistoryRecord *From)
{
	p_Current=From;
	CHistoryRecord *Next=From->p_Next;
	while(Next)
	{
		CHistoryRecord *Temp=Next->p_Next;
		delete Next;
		Next=Temp;
	}
	p_Current->p_Next=NULL;
}

BOOL CHistory::TailReached()
{
	return(!p_Current->p_Next);
}

BOOL CHistory::HeadReached()
{
	return IsHead(p_Current);
}

HTREEITEM CHistory::Next()
{
	p_Current=p_Current->p_Next;
	return p_Current->h_Item;
}

HTREEITEM CHistory::Back()
{
	p_Current=p_Current->p_Back;
	return p_Current->h_Item;
}

BOOL CHistory::IsHead(CHistoryRecord *pRecord)
{
	return(pRecord->p_Back==&m_Head);
}

void CHistory::Clear()
{
	Clear(&m_Head);
}

CStringQueue::CStringQueue(int Limit)
{
	m_Limit=Limit;
	m_Head=0;
	m_Tail=-1;
	p_List=new CString [Limit];

	LoadList();
}

CStringQueue::~CStringQueue()
{
	SaveList();
	delete [] p_List;
}

void CStringQueue::Add(CString One)
{
	if(!IsEmpty()&&!One.CompareNoCase(p_List[m_Tail]))
		return;
	int Pos=Find(One);
	if(Pos!=-1)
	{
		Swap(Pos,m_Tail);
		return;
	}
	BOOL Empty=IsEmpty();
	m_Tail=Increase(m_Tail);
	p_List[m_Tail]=One;
	if(!Empty&&m_Tail<=m_Head)
		m_Head=Increase(m_Head);
}

CString CStringQueue::GetAt(int Index)
{
	ASSERT(!IsEmpty());

	Index=m_Head+Index;
	if(Index>=m_Limit)
		Index-=m_Limit;
	
	return p_List[Index];
}

int CStringQueue::GetCount()
{
	if(IsEmpty())
		return 0;
	if(m_Tail<m_Head)
		return m_Limit;
	return m_Tail-m_Head+1;
}

void CStringQueue::Swap(int IndexA, int IndexB)
{
	CString Temp;
	Temp=p_List[IndexA];
	p_List[IndexA]=p_List[IndexB];
	p_List[IndexB]=Temp;
}

int CStringQueue::Find(CString One)
{
	if(IsEmpty())
		return -1;
	int Index=m_Head;
	while(1)
	{
		if(!One.CompareNoCase(p_List[Index]))
			return Index;
		if(Index==m_Tail)
			break;
		Index=Increase(Index);
	}
	return -1;
}

int CStringQueue::Increase(int Index)
{
	Index++;
	if(Index==m_Limit)
		Index=0;
	return Index;
}

BOOL CStringQueue::IsEmpty()
{
	return (m_Tail==-1);
}

void CStringQueue::LoadList()
{
	TCHAR *p=::theApp.m_UserData.m_SavePath,*cp;
	cp=p;
	while(*p)
	{
		if(*p==';')
		{
			*p='\0';
			Add(cp);
			cp=p+1;
		}
		p++;
	}
}

void CStringQueue::SaveList()
{
	::theApp.m_UserData.m_SavePath[0]='\0';
	int Count=GetCount();
	if(Count)
	{
		for(int i=0;i<Count;i++)
		{
			CString Item;
			Item=GetAt(i)+';';
			strcat(::theApp.m_UserData.m_SavePath,Item);
		}
	}
}
