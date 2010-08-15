// CleanTxtSameInfoView.cpp : CCleanTxtSameInfoView 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCleanTxtSameInfoView 构造/析构

CCleanTxtSameInfoView::CCleanTxtSameInfoView()
{
	// TODO: 在此处添加构造代码

}

CCleanTxtSameInfoView::~CCleanTxtSameInfoView()
{
}

BOOL CCleanTxtSameInfoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCleanTxtSameInfoView 绘制

void CCleanTxtSameInfoView::OnDraw(CDC* /*pDC*/)
{
	CCleanTxtSameInfoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CCleanTxtSameInfoView 打印

BOOL CCleanTxtSameInfoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCleanTxtSameInfoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCleanTxtSameInfoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CCleanTxtSameInfoView 诊断

#ifdef _DEBUG
void CCleanTxtSameInfoView::AssertValid() const
{
	CView::AssertValid();
}

void CCleanTxtSameInfoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCleanTxtSameInfoDoc* CCleanTxtSameInfoView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCleanTxtSameInfoDoc)));
	return (CCleanTxtSameInfoDoc*)m_pDocument;
}
#endif //_DEBUG


// CCleanTxtSameInfoView 消息处理程序
