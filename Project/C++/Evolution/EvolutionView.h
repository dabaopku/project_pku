// EvolutionView.h : CEvolutionView ��Ľӿ�
//


#pragma once
#include "afxwin.h"


class CEvolutionView : public CView
{
protected: // �������л�����
	CEvolutionView();
	DECLARE_DYNCREATE(CEvolutionView)

// ����
public:
	CEvolutionDoc* GetDocument() const;

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
	virtual ~CEvolutionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	CButton btStart;
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // EvolutionView.cpp �еĵ��԰汾
inline CEvolutionDoc* CEvolutionView::GetDocument() const
   { return reinterpret_cast<CEvolutionDoc*>(m_pDocument); }
#endif
