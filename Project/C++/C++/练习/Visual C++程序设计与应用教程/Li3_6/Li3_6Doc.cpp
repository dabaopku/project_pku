// Li3_6Doc.cpp : CLi3_6Doc ���ʵ��
//

#include "stdafx.h"
#include "Li3_6.h"

#include "Li3_6Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLi3_6Doc

IMPLEMENT_DYNCREATE(CLi3_6Doc, CDocument)

BEGIN_MESSAGE_MAP(CLi3_6Doc, CDocument)
END_MESSAGE_MAP()


// CLi3_6Doc ����/����

CLi3_6Doc::CLi3_6Doc()
{
	// TODO: �ڴ����һ���Թ������

}

CLi3_6Doc::~CLi3_6Doc()
{
}

BOOL CLi3_6Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CLi3_6Doc ���л�

void CLi3_6Doc::Serialize(CArchive& ar)
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


// CLi3_6Doc ���

#ifdef _DEBUG
void CLi3_6Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLi3_6Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLi3_6Doc ����
