// Li2_1Doc.cpp : CLi2_1Doc 类的实现
//

#include "stdafx.h"
#include "Li2_1.h"

#include "Li2_1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLi2_1Doc

IMPLEMENT_DYNCREATE(CLi2_1Doc, CDocument)

BEGIN_MESSAGE_MAP(CLi2_1Doc, CDocument)
END_MESSAGE_MAP()


// CLi2_1Doc 构造/析构

CLi2_1Doc::CLi2_1Doc()
{
	// TODO: 在此添加一次性构造代码

}

CLi2_1Doc::~CLi2_1Doc()
{
}

BOOL CLi2_1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CLi2_1Doc 序列化

void CLi2_1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CLi2_1Doc 诊断

#ifdef _DEBUG
void CLi2_1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLi2_1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLi2_1Doc 命令
