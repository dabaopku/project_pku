// Li2_1View.cpp : CLi2_1View ���ʵ��
//

#include "stdafx.h"
#include "Li2_1.h"

#include "Li2_1Doc.h"
#include "Li2_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLi2_1View

IMPLEMENT_DYNCREATE(CLi2_1View, CView)

BEGIN_MESSAGE_MAP(CLi2_1View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_FILE_OPEN, &CLi2_1View::OnFileOpen)
	ON_COMMAND(ID_32771, &CLi2_1View::OnCompute)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CLi2_1View ����/����

CLi2_1View::CLi2_1View()
: x(0)
, y(0)
, m_string(_T(""))
{
	// TODO: �ڴ˴���ӹ������
	x = 50;
	y = 50;
	m_string.Empty();
}

CLi2_1View::~CLi2_1View()
{
}

BOOL CLi2_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CLi2_1View ����

void CLi2_1View::OnDraw(CDC* pDC)
{
	CLi2_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	pDC->TextOutW(x,y-15,L"���������ı�,�ƶ��ı�");
	pDC->TextOutW(x,y,m_string);
}


// CLi2_1View ��ӡ

BOOL CLi2_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CLi2_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CLi2_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CLi2_1View ���

#ifdef _DEBUG
void CLi2_1View::AssertValid() const
{
	CView::AssertValid();
}

void CLi2_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLi2_1Doc* CLi2_1View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLi2_1Doc)));
	return (CLi2_1Doc*)m_pDocument;
}
#endif //_DEBUG


// CLi2_1View ��Ϣ�������

void CLi2_1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	MessageBox(L"����Ҽ�������!",L"��ϲ��!",MB_ICONEXCLAMATION|MB_OK);
	CView::OnRButtonDown(nFlags, point);
}

void CLi2_1View::OnFileOpen()
{
	// TODO: �ڴ���������������
	MessageBox(L"�򿪲˵�������!",L"��ϲ��!",MB_ICONQUESTION|MB_OK);
}

void CLi2_1View::OnCompute()
{
	// TODO: �ڴ���������������
	CClientDC pDC(this);
	int sum=0;
	for(int i=1;i<=200;i++){
		sum+=i*i*i;
	}
	CString str;
	str.Format(L"����: %d",sum);
	m_string = L"1��200������"+str;
	pDC.TextOut(x,y,m_string);
}

void CLi2_1View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_string += (TCHAR)nChar;
	Invalidate();
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CLi2_1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nChar)
	{
	case VK_LEFT:
		x-=10;
		break;
	case VK_RIGHT:
		x+=10;
		break;
	case VK_UP:
		y-=10;
		break;
	case VK_DOWN:
		y+=10;
	}
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
