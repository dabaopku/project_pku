// CleanTxtSameInfoView.cpp : CCleanTxtSameInfoView ���ʵ��
//

#include "stdafx.h"
#include "CleanTxtSameInfo.h"

#include "CleanTxtSameInfoDoc.h"
#include "CleanTxtSameInfoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCleanTxtSameInfoView

IMPLEMENT_DYNCREATE(CCleanTxtSameInfoView, CView)

BEGIN_MESSAGE_MAP(CCleanTxtSameInfoView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCleanTxtSameInfoView ����/����

CCleanTxtSameInfoView::CCleanTxtSameInfoView()
{
	// TODO: �ڴ˴���ӹ������

}

CCleanTxtSameInfoView::~CCleanTxtSameInfoView()
{
}

BOOL CCleanTxtSameInfoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CCleanTxtSameInfoView ����

void CCleanTxtSameInfoView::OnDraw(CDC* /*pDC*/)
{
	CCleanTxtSameInfoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CCleanTxtSameInfoView ��ӡ

BOOL CCleanTxtSameInfoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CCleanTxtSameInfoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CCleanTxtSameInfoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CCleanTxtSameInfoView ���

#ifdef _DEBUG
void CCleanTxtSameInfoView::AssertValid() const
{
	CView::AssertValid();
}

void CCleanTxtSameInfoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCleanTxtSameInfoDoc* CCleanTxtSameInfoView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCleanTxtSameInfoDoc)));
	return (CCleanTxtSameInfoDoc*)m_pDocument;
}
#endif //_DEBUG


// CCleanTxtSameInfoView ��Ϣ�������
