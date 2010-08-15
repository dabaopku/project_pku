// Li2_1View.cpp : CLi2_1View 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_FILE_OPEN, &CLi2_1View::OnFileOpen)
	ON_COMMAND(ID_32771, &CLi2_1View::OnCompute)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CLi2_1View 构造/析构

CLi2_1View::CLi2_1View()
: x(0)
, y(0)
, m_string(_T(""))
{
	// TODO: 在此处添加构造代码
	x = 50;
	y = 50;
	m_string.Empty();
}

CLi2_1View::~CLi2_1View()
{
}

BOOL CLi2_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CLi2_1View 绘制

void CLi2_1View::OnDraw(CDC* pDC)
{
	CLi2_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	pDC->TextOutW(x,y-15,L"可以输入文本,移动文本");
	pDC->TextOutW(x,y,m_string);
}


// CLi2_1View 打印

BOOL CLi2_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CLi2_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CLi2_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CLi2_1View 诊断

#ifdef _DEBUG
void CLi2_1View::AssertValid() const
{
	CView::AssertValid();
}

void CLi2_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLi2_1Doc* CLi2_1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLi2_1Doc)));
	return (CLi2_1Doc*)m_pDocument;
}
#endif //_DEBUG


// CLi2_1View 消息处理程序

void CLi2_1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	MessageBox(L"鼠标右键被按下!",L"恭喜你!",MB_ICONEXCLAMATION|MB_OK);
	CView::OnRButtonDown(nFlags, point);
}

void CLi2_1View::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(L"打开菜单被单击!",L"恭喜你!",MB_ICONQUESTION|MB_OK);
}

void CLi2_1View::OnCompute()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC pDC(this);
	int sum=0;
	for(int i=1;i<=200;i++){
		sum+=i*i*i;
	}
	CString str;
	str.Format(L"和是: %d",sum);
	m_string = L"1到200的立方"+str;
	pDC.TextOut(x,y,m_string);
}

void CLi2_1View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_string += (TCHAR)nChar;
	Invalidate();
	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CLi2_1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
