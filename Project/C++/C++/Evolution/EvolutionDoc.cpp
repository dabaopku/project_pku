// EvolutionDoc.cpp : CEvolutionDoc ���ʵ��
//

#include "stdafx.h"
#include "Evolution.h"

#include "EvolutionDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEvolutionDoc

IMPLEMENT_DYNCREATE(CEvolutionDoc, CDocument)

BEGIN_MESSAGE_MAP(CEvolutionDoc, CDocument)
END_MESSAGE_MAP()


// CEvolutionDoc ����/����

CEvolutionDoc::CEvolutionDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CEvolutionDoc::~CEvolutionDoc()
{
}

BOOL CEvolutionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CEvolutionDoc ���л�

void CEvolutionDoc::Serialize(CArchive& ar)
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


// CEvolutionDoc ���

#ifdef _DEBUG
void CEvolutionDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEvolutionDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEvolutionDoc ����
