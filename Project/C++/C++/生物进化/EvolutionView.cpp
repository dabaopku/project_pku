// EvolutionView.cpp : CEvolutionView 类的实现
//

#include "stdafx.h"
#include "生物进化.h"

#include "EvolutionDoc.h"
#include "EvolutionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEvolutionView

IMPLEMENT_DYNCREATE(CEvolutionView, CView)

BEGIN_MESSAGE_MAP(CEvolutionView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CEvolutionView 构造/析构

CEvolutionView::CEvolutionView()
{
	// TODO: 在此处添加构造代码

}

CEvolutionView::~CEvolutionView()
{
}

BOOL CEvolutionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CEvolutionView 绘制

void CEvolutionView::OnDraw(CDC* /*pDC*/)
{
	EvolutionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CEvolutionView 打印

BOOL CEvolutionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CEvolutionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CEvolutionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CEvolutionView 诊断

#ifdef _DEBUG
void CEvolutionView::AssertValid() const
{
	CView::AssertValid();
}

void CEvolutionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

EvolutionDoc* CEvolutionView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(EvolutionDoc)));
	return (EvolutionDoc*)m_pDocument;
}
#endif //_DEBUG


// CEvolutionView 消息处理程序
