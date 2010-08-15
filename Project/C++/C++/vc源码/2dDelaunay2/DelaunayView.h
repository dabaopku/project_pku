// DelaunayView.h : interface of the CDelaunayView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DELAUNAYVIEW_H__5118720F_461A_4394_A3F3_378620D61654__INCLUDED_)
#define AFX_DELAUNAYVIEW_H__5118720F_461A_4394_A3F3_378620D61654__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dataStruct.h"

class CDelaunayView : public CView
{
protected: // create from serialization only
	CDelaunayView();
	DECLARE_DYNCREATE(CDelaunayView)

// Attributes
public:
	CDelaunayDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDelaunayView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDelaunayView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDelaunayView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDelaunay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CPoint startPoint;
	int pointNumber;
    int Tricount, nCurTri;

	//创建种子三角形
	void createFirstTri(CObList* pointList, 
		                CObList* triList,
						PointCls* p1 = NULL);
    //扩展边p1, p2
	void enlargeEdge(PointCls *p1,
		             PointCls *p2,
					 PointCls *p3,
					 CObList* pointList,
					 CObList* triList);
	
	//循环扩展所有三角形
	void enlargeTri(CObList* pointList,
		            CObList* TriList);
    
	//如果有点不在最终的三角剖分中，继续创建种子三角形，
	//再重复扩展
	void continueEnlarge(CObList* pointList,
		                 CObList* TriList);
};

#ifndef _DEBUG  // debug version in DelaunayView.cpp
inline CDelaunayDoc* CDelaunayView::GetDocument()
   { return (CDelaunayDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELAUNAYVIEW_H__5118720F_461A_4394_A3F3_378620D61654__INCLUDED_)
