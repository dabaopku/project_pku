// Li3_2Doc.cpp : CLi3_2Doc ���ʵ��
//

#include "stdafx.h"
#include "Li3_2.h"

#include "Li3_2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLi3_2Doc

IMPLEMENT_DYNCREATE(CLi3_2Doc, CDocument)

BEGIN_MESSAGE_MAP(CLi3_2Doc, CDocument)
END_MESSAGE_MAP()


// CLi3_2Doc ����/����

CLi3_2Doc::CLi3_2Doc()
{
	// TODO: �ڴ����һ���Թ������

}

CLi3_2Doc::~CLi3_2Doc()
{
}

BOOL CLi3_2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CLi3_2Doc ���л�

void CLi3_2Doc::Serialize(CArchive& ar)
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


// CLi3_2Doc ���

#ifdef _DEBUG
void CLi3_2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLi3_2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLi3_2Doc ����
