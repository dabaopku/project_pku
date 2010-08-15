// Li3_6Doc.cpp : CLi3_6Doc 类的实现
//

#include "stdafx.h"
#include "Li3_6.h"

#include "Li3_6Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLi3_6Doc

IMPLEMENT_DYNCREATE(CLi3_6Doc, CDocument)

BEGIN_MESSAGE_MAP(CLi3_6Doc, CDocument)
END_MESSAGE_MAP()


// CLi3_6Doc 构造/析构

CLi3_6Doc::CLi3_6Doc()
{
	// TODO: 在此添加一次性构造代码

}

CLi3_6Doc::~CLi3_6Doc()
{
}

BOOL CLi3_6Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CLi3_6Doc 序列化

void CLi3_6Doc::Serialize(CArchive& ar)
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


// CLi3_6Doc 诊断

#ifdef _DEBUG
void CLi3_6Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLi3_6Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLi3_6Doc 命令
