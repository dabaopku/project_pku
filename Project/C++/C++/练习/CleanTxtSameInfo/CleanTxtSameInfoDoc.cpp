// CleanTxtSameInfoDoc.cpp : CCleanTxtSameInfoDoc 类的实现
//

#include "stdafx.h"
#include "CleanTxtSameInfo.h"

#include "CleanTxtSameInfoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCleanTxtSameInfoDoc

IMPLEMENT_DYNCREATE(CCleanTxtSameInfoDoc, CDocument)

BEGIN_MESSAGE_MAP(CCleanTxtSameInfoDoc, CDocument)
END_MESSAGE_MAP()


// CCleanTxtSameInfoDoc 构造/析构

CCleanTxtSameInfoDoc::CCleanTxtSameInfoDoc()
{
	// TODO: 在此添加一次性构造代码

}

CCleanTxtSameInfoDoc::~CCleanTxtSameInfoDoc()
{
}

BOOL CCleanTxtSameInfoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CCleanTxtSameInfoDoc 序列化

void CCleanTxtSameInfoDoc::Serialize(CArchive& ar)
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


// CCleanTxtSameInfoDoc 诊断

#ifdef _DEBUG
void CCleanTxtSameInfoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCleanTxtSameInfoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCleanTxtSameInfoDoc 命令
