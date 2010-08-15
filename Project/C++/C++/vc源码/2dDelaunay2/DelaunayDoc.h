// DelaunayDoc.h : interface of the CDelaunayDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DELAUNAYDOC_H__943DCAA3_A8BF_4E97_B63E_9101CC144902__INCLUDED_)
#define AFX_DELAUNAYDOC_H__943DCAA3_A8BF_4E97_B63E_9101CC144902__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "dataStruct.h"

class CDelaunayDoc : public CDocument
{
protected: // create from serialization only
	CDelaunayDoc();
	DECLARE_DYNCREATE(CDelaunayDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDelaunayDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDelaunayDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDelaunayDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


public:
	CObList* PointArray;
	CObList* PointList;
//	CObList* EdgeList;
	CObList* TriList;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELAUNAYDOC_H__943DCAA3_A8BF_4E97_B63E_9101CC144902__INCLUDED_)
