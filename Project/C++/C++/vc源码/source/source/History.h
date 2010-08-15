// History.h: interface for the CHistory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HISTORY_H__7450AFF1_86B3_4D39_9B31_17860ED7F4AD__INCLUDED_)
#define AFX_HISTORY_H__7450AFF1_86B3_4D39_9B31_17860ED7F4AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStringQueue
{
public:
	void SaveList();
	void LoadList();
	BOOL IsEmpty();
	int Increase(int Index);
	int Find(CString One);
	void Swap(int IndexA,int IndexB);
	int GetCount();
	CString GetAt(int Index);
	int m_Tail;
	int m_Head;
	void Add(CString One);
	CString * p_List;
	~CStringQueue();
	CStringQueue(int Limit=5);
	int m_Limit;
};

class CHistoryRecord
{
public:
	CHistoryRecord();
	HTREEITEM h_Item;
	CHistoryRecord *p_Back;
	CHistoryRecord *p_Next;
};

class CHistory  
{
public:
	void Clear();
	BOOL IsHead(CHistoryRecord *pRecord);
	HTREEITEM Back();
	HTREEITEM Next();
	BOOL HeadReached();
	BOOL TailReached();
	void Clear(CHistoryRecord *From);
	void Add(HTREEITEM hItem);
	CHistoryRecord * p_Current;
	CHistoryRecord m_Head;
	CHistory();
	virtual ~CHistory();
};

#endif // !defined(AFX_HISTORY_H__7450AFF1_86B3_4D39_9B31_17860ED7F4AD__INCLUDED_)
