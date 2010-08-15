// EvolutionDoc.cpp : CEvolutionDoc 类的实现
//

#include "stdafx.h"
#include "Evolution.h"

#include "EvolutionDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEvolutionDoc

IMPLEMENT_DYNCREATE(CEvolutionDoc, CDocument)

BEGIN_MESSAGE_MAP(CEvolutionDoc, CDocument)
END_MESSAGE_MAP()


// CEvolutionDoc 构造/析构

CEvolutionDoc::CEvolutionDoc()
{
	// TODO: 在此添加一次性构造代码

}

CEvolutionDoc::~CEvolutionDoc()
{
}

BOOL CEvolutionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CEvolutionDoc 序列化

void CEvolutionDoc::Serialize(CArchive& ar)
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


// CEvolutionDoc 诊断

#ifdef _DEBUG
void CEvolutionDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEvolutionDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEvolutionDoc 命令
