// Li3_6View.h : CLi3_6View ��Ľӿ�
//


#pragma once


class CLi3_6View : public CView
{
protected: // �������л�����
	CLi3_6View();
	DECLARE_DYNCREATE(CLi3_6View)

// ����
public:
	CLi3_6Doc* GetDocument() const;

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
	virtual ~CLi3_6View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // Li3_6View.cpp �еĵ��԰汾
inline CLi3_6Doc* CLi3_6View::GetDocument() const
   { return reinterpret_cast<CLi3_6Doc*>(m_pDocument); }
#endif

