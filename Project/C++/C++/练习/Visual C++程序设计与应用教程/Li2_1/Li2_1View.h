// Li2_1View.h : CLi2_1View ��Ľӿ�
//


#pragma once


class CLi2_1View : public CView
{
protected: // �������л�����
	CLi2_1View();
	DECLARE_DYNCREATE(CLi2_1View)

// ����
public:
	CLi2_1Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CLi2_1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // Li2_1View.cpp �еĵ��԰汾
inline CLi2_1Doc* CLi2_1View::GetDocument() const
   { return reinterpret_cast<CLi2_1Doc*>(m_pDocument); }
#endif

