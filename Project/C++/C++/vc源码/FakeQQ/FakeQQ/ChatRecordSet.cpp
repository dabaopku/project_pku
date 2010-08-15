// ChatRecordSet.cpp : implementation file
//

#include "stdafx.h"
#include "fakeqq.h"
#include "ChatRecordSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatRecordSet

IMPLEMENT_DYNAMIC(CChatRecordSet, CRecordset)

CChatRecordSet::CChatRecordSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CChatRecordSet)
	m_ID = 0;
	m_UserName = _T("");
	m_Address = _T("");
	m_UserFace = 0;
	m_ChatMsg = _T("");
	m_MsgTime = 0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CChatRecordSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=FakeQQ");
}

CString CChatRecordSet::GetDefaultSQL()
{
	return _T("[chat]");
}

void CChatRecordSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CChatRecordSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[UserName]"), m_UserName);
	RFX_Text(pFX, _T("[Address]"), m_Address);
	RFX_Long(pFX, _T("[UserFace]"), m_UserFace);
	RFX_Text(pFX, _T("[ChatMsg]"), m_ChatMsg);
	RFX_Long(pFX, _T("[MsgTime]"), m_MsgTime);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CChatRecordSet diagnostics

#ifdef _DEBUG
void CChatRecordSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CChatRecordSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
