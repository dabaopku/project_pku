// EvolutionView.h : CEvolutionView 类的接口
//


#pragma once
#include "afxwin.h"


class CEvolutionView : public CView
{
protected: // 仅从序列化创建
	CEvolutionView();
	DECLARE_DYNCREATE(CEvolutionView)

// 属性
public:
	CEvolutionDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CEvolutionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	CButton btStart;
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // EvolutionView.cpp 中的调试版本
inline CEvolutionDoc* CEvolutionView::GetDocument() const
   { return reinterpret_cast<CEvolutionDoc*>(m_pDocument); }
#endif

