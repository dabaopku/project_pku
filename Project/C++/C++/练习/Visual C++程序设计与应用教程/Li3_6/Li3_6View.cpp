// Li3_6View.cpp : CLi3_6View 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CLi3_6View::On32771)
	ON_COMMAND(ID_32772, &CLi3_6View::On32772)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CLi3_6View 构造/析构

CLi3_6View::CLi3_6View()
: x(0)
, y(0)
, m_string(_T(""))
{
	// TODO: 在此处添加构造代码

}

CLi3_6View::~CLi3_6View()
{
	
}

BOOL CLi3_6View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CLi3_6View 绘制

void CLi3_6View::OnDraw(CDC* pDC)
{
	CLi3_6Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

}


// CLi3_6View 打印

BOOL CLi3_6View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CLi3_6View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CLi3_6View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CLi3_6View 诊断

#ifdef _DEBUG
void CLi3_6View::AssertValid() const
{
	CView::AssertValid();
}

void CLi3_6View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLi3_6Doc* CLi3_6View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLi3_6Doc)));
	return (CLi3_6Doc*)m_pDocument;
}
#endif //_DEBUG


// CLi3_6View 消息处理程序

void CLi3_6View::On32771()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC  pDC(this);
	LOGFONT lf;												//字体属性对象
	CFont NewFont,*OldFont;
	CBrush NewBrush, *OldBrush;
	//获取字体参数
	pDC.GetCurrentFont()->GetLogFont(&lf);
	lf.lfCharSet=DEFAULT_CHARSET;
	lf.lfHeight=-120;
	lf.lfWidth=0;
	strcpy(lf.lfFaceName,"隶书");

	NewFont.CreateFontIndirect(&lf);
	OldFont=pDC.SelectObject(&NewFont);
	pDC.SetBkMode(TRANSPARENT);

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1);

	NewBrush.CreatePatternBrush(&bitmap);
	OldBrush=pDC.SelectObject(&NewBrush);
	pDC.BeginPath();
	pDC.TextOutA(20,180,"位图文本");
	pDC.EndPath();
	pDC.StrokeAndFillPath();
	pDC.SelectObject(OldBrush);
	pDC.SelectObject(OldFont);
	NewBrush.DeleteObject();
	NewFont.DeleteObject();
}

void CLi3_6View::On32772()
{
	// TODO: 在此添加命令处理程序代码
	SetTimer(1,100,NULL);
	x=300;
	y=300;
	m_string="这是滚动文本";
}

void CLi3_6View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	x-=10;
	if(x<0) x=600;
	dc.TextOutA(x,y,m_string);
	dc.TextOutA(x,y,m_string);
	CView::OnTimer(nIDEvent);
}
