// EvolutionDoc.cpp : EvolutionDoc ���ʵ��
//

#include "stdafx.h"
#include "�������.h"

#include "EvolutionDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// EvolutionDoc

IMPLEMENT_DYNCREATE(EvolutionDoc, CDocument)

BEGIN_MESSAGE_MAP(EvolutionDoc, CDocument)
END_MESSAGE_MAP()


// EvolutionDoc ����/����

EvolutionDoc::EvolutionDoc()
{
	// TODO: �ڴ����һ���Թ������

}

EvolutionDoc::~EvolutionDoc()
{
}

BOOL EvolutionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// EvolutionDoc ���л�

void EvolutionDoc::Serialize(CArchive& ar)
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


// EvolutionDoc ���

#ifdef _DEBUG
void EvolutionDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void EvolutionDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// EvolutionDoc ����
