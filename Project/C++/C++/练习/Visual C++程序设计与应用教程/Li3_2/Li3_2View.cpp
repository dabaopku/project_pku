// Li3_2View.cpp : CLi3_2View ���ʵ��
//

#include "stdafx.h"
#include "Li3_2.h"

#include "Li3_2Doc.h"
#include "Li3_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLi3_2View

IMPLEMENT_DYNCREATE(CLi3_2View, CView)

BEGIN_MESSAGE_MAP(CLi3_2View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CLi3_2View ����/����

CLi3_2View::CLi3_2View()
{
	// TODO: �ڴ˴���ӹ������

}

CLi3_2View::~CLi3_2View()
{
}

BOOL CLi3_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CLi3_2View ����

void CLi3_2View::OnDraw(CDC* pDC)
{
	CLi3_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	pDC->RoundRect(100,120,234,345,40,40);
	CPen *Penold,Pennew;
	CBrush *Brushold,Brushnew;
	int HatchStyle[]={HS_BDIAGONAL,HS_CROSS,HS_FDIAGONAL};
	COLORREF Clr[]={RGB(255,0,0),RGB(0,160,0),RGB(0,0,255),RGB(200,250,0)};
	int Penstyle[]={PS_SOLID,PS_DOT,PS_DASHDOT,PS_DASH,PS_DASHDOTDOT,PS_INSIDEFRAME};
	for(int i=0;i<6;i++){
		Pennew.CreatePen(Penstyle[i],0.5,Clr[0]);
		if(i>=3) Brushnew.CreateSolidBrush(Clr[i-2]);
		else Brushnew.CreateHatchBrush(HatchStyle[i],RGB(128,36,88));
		Brushold=pDC->SelectObject(&Brushnew);
		Penold=pDC->SelectObject(&Pennew);
		pDC->Rectangle(100+100*i,40+40*i,150+111*i,80+80*i);
		pDC->SelectObject(Brushold);
		pDC->SelectObject(Penold);
		Brushnew.DeleteObject();
		Pennew.DeleteObject();

	}

}


// CLi3_2View ��ӡ

BOOL CLi3_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CLi3_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CLi3_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CLi3_2View ���

#ifdef _DEBUG
void CLi3_2View::AssertValid() const
{
	CView::AssertValid();
}

void CLi3_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLi3_2Doc* CLi3_2View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLi3_2Doc)));
	return (CLi3_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CLi3_2View ��Ϣ�������
