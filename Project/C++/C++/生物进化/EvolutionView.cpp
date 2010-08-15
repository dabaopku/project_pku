// EvolutionView.cpp : CEvolutionView ���ʵ��
//

#include "stdafx.h"
#include "�������.h"

#include "EvolutionDoc.h"
#include "EvolutionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEvolutionView

IMPLEMENT_DYNCREATE(CEvolutionView, CView)

BEGIN_MESSAGE_MAP(CEvolutionView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CEvolutionView ����/����

CEvolutionView::CEvolutionView()
{
	// TODO: �ڴ˴���ӹ������

}

CEvolutionView::~CEvolutionView()
{
}

BOOL CEvolutionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CEvolutionView ����

void CEvolutionView::OnDraw(CDC* /*pDC*/)
{
	EvolutionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CEvolutionView ��ӡ

BOOL CEvolutionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CEvolutionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CEvolutionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CEvolutionView ���

#ifdef _DEBUG
void CEvolutionView::AssertValid() const
{
	CView::AssertValid();
}

void CEvolutionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

EvolutionDoc* CEvolutionView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(EvolutionDoc)));
	return (EvolutionDoc*)m_pDocument;
}
#endif //_DEBUG


// CEvolutionView ��Ϣ�������
