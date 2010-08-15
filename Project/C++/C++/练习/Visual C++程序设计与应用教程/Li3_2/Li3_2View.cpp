// Li3_2View.cpp : CLi3_2View 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CLi3_2View 构造/析构

CLi3_2View::CLi3_2View()
{
	// TODO: 在此处添加构造代码

}

CLi3_2View::~CLi3_2View()
{
}

BOOL CLi3_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CLi3_2View 绘制

void CLi3_2View::OnDraw(CDC* pDC)
{
	CLi3_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
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


// CLi3_2View 打印

BOOL CLi3_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CLi3_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CLi3_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CLi3_2View 诊断

#ifdef _DEBUG
void CLi3_2View::AssertValid() const
{
	CView::AssertValid();
}

void CLi3_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLi3_2Doc* CLi3_2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLi3_2Doc)));
	return (CLi3_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CLi3_2View 消息处理程序
