// EvolutionDoc.cpp : EvolutionDoc 类的实现
//

#include "stdafx.h"
#include "生物进化.h"

#include "EvolutionDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// EvolutionDoc

IMPLEMENT_DYNCREATE(EvolutionDoc, CDocument)

BEGIN_MESSAGE_MAP(EvolutionDoc, CDocument)
END_MESSAGE_MAP()


// EvolutionDoc 构造/析构

EvolutionDoc::EvolutionDoc()
{
	// TODO: 在此添加一次性构造代码

}

EvolutionDoc::~EvolutionDoc()
{
}

BOOL EvolutionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// EvolutionDoc 序列化

void EvolutionDoc::Serialize(CArchive& ar)
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


// EvolutionDoc 诊断

#ifdef _DEBUG
void EvolutionDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void EvolutionDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// EvolutionDoc 命令
