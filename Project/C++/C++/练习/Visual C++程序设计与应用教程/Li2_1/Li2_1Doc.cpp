// Li2_1Doc.cpp : CLi2_1Doc ���ʵ��
//

#include "stdafx.h"
#include "Li2_1.h"

#include "Li2_1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLi2_1Doc

IMPLEMENT_DYNCREATE(CLi2_1Doc, CDocument)

BEGIN_MESSAGE_MAP(CLi2_1Doc, CDocument)
END_MESSAGE_MAP()


// CLi2_1Doc ����/����

CLi2_1Doc::CLi2_1Doc()
{
	// TODO: �ڴ����һ���Թ������

}

CLi2_1Doc::~CLi2_1Doc()
{
}

BOOL CLi2_1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CLi2_1Doc ���л�

void CLi2_1Doc::Serialize(CArchive& ar)
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


// CLi2_1Doc ���

#ifdef _DEBUG
void CLi2_1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLi2_1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLi2_1Doc ����
