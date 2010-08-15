// Li3_6View.cpp : CLi3_6View ���ʵ��
//

#include "stdafx.h"
#include "Li3_6.h"

#include "Li3_6Doc.h"
#include "Li3_6View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLi3_6View

IMPLEMENT_DYNCREATE(CLi3_6View, CView)

BEGIN_MESSAGE_MAP(CLi3_6View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CLi3_6View::On32771)
	ON_COMMAND(ID_32772, &CLi3_6View::On32772)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CLi3_6View ����/����

CLi3_6View::CLi3_6View()
: x(0)
, y(0)
, m_string(_T(""))
{
	// TODO: �ڴ˴���ӹ������

}

CLi3_6View::~CLi3_6View()
{
	
}

BOOL CLi3_6View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CLi3_6View ����

void CLi3_6View::OnDraw(CDC* pDC)
{
	CLi3_6Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

}


// CLi3_6View ��ӡ

BOOL CLi3_6View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CLi3_6View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CLi3_6View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CLi3_6View ���

#ifdef _DEBUG
void CLi3_6View::AssertValid() const
{
	CView::AssertValid();
}

void CLi3_6View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLi3_6Doc* CLi3_6View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLi3_6Doc)));
	return (CLi3_6Doc*)m_pDocument;
}
#endif //_DEBUG


// CLi3_6View ��Ϣ�������

void CLi3_6View::On32771()
{
	// TODO: �ڴ���������������
	CClientDC  pDC(this);
	LOGFONT lf;												//�������Զ���
	CFont NewFont,*OldFont;
	CBrush NewBrush, *OldBrush;
	//��ȡ�������
	pDC.GetCurrentFont()->GetLogFont(&lf);
	lf.lfCharSet=DEFAULT_CHARSET;
	lf.lfHeight=-120;
	lf.lfWidth=0;
	strcpy(lf.lfFaceName,"����");

	NewFont.CreateFontIndirect(&lf);
	OldFont=pDC.SelectObject(&NewFont);
	pDC.SetBkMode(TRANSPARENT);

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1);

	NewBrush.CreatePatternBrush(&bitmap);
	OldBrush=pDC.SelectObject(&NewBrush);
	pDC.BeginPath();
	pDC.TextOutA(20,180,"λͼ�ı�");
	pDC.EndPath();
	pDC.StrokeAndFillPath();
	pDC.SelectObject(OldBrush);
	pDC.SelectObject(OldFont);
	NewBrush.DeleteObject();
	NewFont.DeleteObject();
}

void CLi3_6View::On32772()
{
	// TODO: �ڴ���������������
	SetTimer(1,100,NULL);
	x=300;
	y=300;
	m_string="���ǹ����ı�";
}

void CLi3_6View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this);
	x-=10;
	if(x<0) x=600;
	dc.TextOutA(x,y,m_string);
	dc.TextOutA(x,y,m_string);
	CView::OnTimer(nIDEvent);
}
