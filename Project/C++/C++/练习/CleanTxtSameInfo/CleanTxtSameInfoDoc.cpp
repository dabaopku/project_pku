// CleanTxtSameInfoDoc.cpp : CCleanTxtSameInfoDoc ���ʵ��
//

#include "stdafx.h"
#include "CleanTxtSameInfo.h"

#include "CleanTxtSameInfoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCleanTxtSameInfoDoc

IMPLEMENT_DYNCREATE(CCleanTxtSameInfoDoc, CDocument)

BEGIN_MESSAGE_MAP(CCleanTxtSameInfoDoc, CDocument)
END_MESSAGE_MAP()


// CCleanTxtSameInfoDoc ����/����

CCleanTxtSameInfoDoc::CCleanTxtSameInfoDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CCleanTxtSameInfoDoc::~CCleanTxtSameInfoDoc()
{
}

BOOL CCleanTxtSameInfoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CCleanTxtSameInfoDoc ���л�

void CCleanTxtSameInfoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CCleanTxtSameInfoDoc ���

#ifdef _DEBUG
void CCleanTxtSameInfoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCleanTxtSameInfoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCleanTxtSameInfoDoc ����
