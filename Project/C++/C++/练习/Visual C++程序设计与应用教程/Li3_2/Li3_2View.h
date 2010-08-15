// Li3_2View.h : CLi3_2View 类的接口
//


#pragma once


class CLi3_2View : public CView
{
protected: // 仅从序列化创建
	CLi3_2View();
	DECLARE_DYNCREATE(CLi3_2View)

// 属性
public:
	CLi3_2Doc* GetDocument() const;

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
	virtual ~CLi3_2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Li3_2View.cpp 中的调试版本
inline CLi3_2Doc* CLi3_2View::GetDocument() const
   { return reinterpret_cast<CLi3_2Doc*>(m_pDocument); }
#endif

