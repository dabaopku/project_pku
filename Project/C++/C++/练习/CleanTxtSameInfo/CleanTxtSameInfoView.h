// CleanTxtSameInfoView.h : CCleanTxtSameInfoView ��Ľӿ�
//


#pragma once


class CCleanTxtSameInfoView : public CView
{
protected: // �������л�����
	CCleanTxtSameInfoView();
	DECLARE_DYNCREATE(CCleanTxtSameInfoView)

// ����
public:
	CCleanTxtSameInfoDoc* GetDocument() const;

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
	virtual ~CCleanTxtSameInfoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // CleanTxtSameInfoView.cpp �еĵ��԰汾
inline CCleanTxtSameInfoDoc* CCleanTxtSameInfoView::GetDocument() const
   { return reinterpret_cast<CCleanTxtSameInfoDoc*>(m_pDocument); }
#endif

