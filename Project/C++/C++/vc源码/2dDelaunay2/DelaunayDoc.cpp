// DelaunayDoc.cpp : implementation of the CDelaunayDoc class
//

#include "stdafx.h"
#include "Delaunay.h"

#include "DelaunayDoc.h"

#include "dataStruct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDelaunayDoc

IMPLEMENT_DYNCREATE(CDelaunayDoc, CDocument)

BEGIN_MESSAGE_MAP(CDelaunayDoc, CDocument)
	//{{AFX_MSG_MAP(CDelaunayDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDelaunayDoc construction/destruction

CDelaunayDoc::CDelaunayDoc()
{
	// TODO: add one-time construction code here
	PointList = new CObList(100);
//	EdgeList = new CObList(100);
	TriList = new CObList(100);
}

CDelaunayDoc::~CDelaunayDoc()
{
	POSITION pos1, pos2;//, pos3;
	PointCls* pa;
	pos1 = PointList->GetHeadPosition();
	while(pos1)
	{
		pa = (PointCls*)PointList->GetNext(pos1);;
		delete pa;
	}
	if(!PointList->IsEmpty())
		PointList->RemoveAll();
	
	TriAngle* pTri;
	pos2 = TriList->GetHeadPosition();
	while(pos2)
	{
		pTri = (TriAngle*)TriList->GetNext(pos2);
		delete pTri;
	}
	if(!TriList->IsEmpty())
		TriList->RemoveAll();
	
//	EdgeNode* pEdege;
//	pos3 = EdgeList->GetHeadPosition();
//	while(pos3)
//	{
//		pEdege = (EdgeNode*)EdgeList->GetNext(pos3);
//		delete pEdege;
//	}
//	if(!EdgeList->IsEmpty())
//		EdgeList->RemoveAll();

}

BOOL CDelaunayDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDelaunayDoc serialization

void CDelaunayDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDelaunayDoc diagnostics

#ifdef _DEBUG
void CDelaunayDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDelaunayDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDelaunayDoc commands
