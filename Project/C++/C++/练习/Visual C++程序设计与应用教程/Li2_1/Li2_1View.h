// Li2_1View.h : CLi2_1View 类的接口
//


#pragma once


class CLi2_1View : public CView
{
protected: // 仅从序列化创建
	CLi2_1View();
	DECLARE_DYNCREATE(CLi2_1View)

// 属性
public:
	CLi2_1Doc* GetDocument() const;

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
	virtual ~CLi2_1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnFileOpen();
	afx_msg void OnCompute();
	int x;
	int y;
	CString m_string;
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // Li2_1View.cpp 中的调试版本
inline CLi2_1Doc* CLi2_1View::GetDocument() const
   { return reinterpret_cast<CLi2_1Doc*>(m_pDocument); }
#endif

