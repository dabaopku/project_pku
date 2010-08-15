// Li3_6View.h : CLi3_6View 类的接口
//


#pragma once


class CLi3_6View : public CView
{
protected: // 仅从序列化创建
	CLi3_6View();
	DECLARE_DYNCREATE(CLi3_6View)

// 属性
public:
	CLi3_6Doc* GetDocument() const;

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
	virtual ~CLi3_6View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void On32771();
	afx_msg void On32772();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int x;
	int y;
	CString m_string;
};

#ifndef _DEBUG  // Li3_6View.cpp 中的调试版本
inline CLi3_6Doc* CLi3_6View::GetDocument() const
   { return reinterpret_cast<CLi3_6Doc*>(m_pDocument); }
#endif

