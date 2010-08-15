#if !defined(AFX_CHATRECORDSET_H__38CB6A2C_8206_4397_9E2F_6D1FEB244C29__INCLUDED_)
#define AFX_CHATRECORDSET_H__38CB6A2C_8206_4397_9E2F_6D1FEB244C29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatRecordSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChatRecordSet recordset

class CChatRecordSet : public CRecordset
{
public:
	CChatRecordSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CChatRecordSet)

// Field/Param Data
	//{{AFX_FIELD(CChatRecordSet, CRecordset)
	long	m_ID;
	CString	m_UserName;
	CString	m_Address;
	long	m_UserFace;
	CString	m_ChatMsg;
	long	m_MsgTime;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatRecordSet)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATRECORDSET_H__38CB6A2C_8206_4397_9E2F_6D1FEB244C29__INCLUDED_)
