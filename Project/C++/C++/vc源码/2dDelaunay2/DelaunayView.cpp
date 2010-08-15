// DelaunayView.cpp : implementation of the CDelaunayView class
//

#include "stdafx.h"
#include "Delaunay.h"

#include "DelaunayDoc.h"
#include "DelaunayView.h"

#include <strstrea.h>
#include "dataStruct.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDelaunayView

IMPLEMENT_DYNCREATE(CDelaunayView, CView)

BEGIN_MESSAGE_MAP(CDelaunayView, CView)
	//{{AFX_MSG_MAP(CDelaunayView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_DELAUNAY, OnDelaunay)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDelaunayView construction/destruction

CDelaunayView::CDelaunayView()
{
	// TODO: add construction code here
    startPoint.x = 0;
	startPoint.y = 0;
	pointNumber = 0;
	Tricount = nCurTri = 0;
}

CDelaunayView::~CDelaunayView()
{
}

BOOL CDelaunayView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDelaunayView drawing

void CDelaunayView::OnDraw(CDC* pDC)
{
	CDelaunayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	POSITION pos1;
	TriAngle* pTri;
	PointCls *p4, *p5, *p6;	

	if(pDoc->PointList->GetCount())
	{
		pos1 = pDoc->PointList->GetHeadPosition();
		while(pos1 != NULL)
		{
			PointCls* pa = (PointCls*)pDoc->PointList->GetNext(pos1);

			pDC->SetPixel(pa->x, pa->y, RGB(255, 0, 0));
		}

//		createFirstTri(pDoc->PointList,
//			           pDoc->TriList);
//
//		POSITION pos4, pos5;
//		pos4 = pDoc->TriList->GetHeadPosition();
//		TriAngle* pTriSeed = (TriAngle*)pDoc->TriList->GetAt(pos4);
//
//		pos5 = pDoc->PointList->GetHeadPosition();
//		while(pos5 != NULL)
//		{
//			PointCls* pa = (PointCls*)pDoc->PointList->GetNext(pos5);
//
//			if(pa->index == pTriSeed->index[0])
//			{
//				p1 = pa;
//			}
//			if(pa->index == pTriSeed->index[1])
//			{
//				p2 = pa;
//			}
//			if(pa->index == pTriSeed->index[2])
//			{
//				p3 = pa;
//			}
//		}
//		enlargeEdge(p1, p2, p3, pDoc->PointList, pDoc->TriList);
//
//		enlargeTri(pDoc->PointList, pDoc->TriList);
//
//		continueEnlarge(pDoc->PointList, pDoc->TriList);
	}
	if(pDoc->TriList->GetCount())
	{
		POSITION pos8 = pDoc->TriList->GetHeadPosition();
		while(pos8 != NULL)
		{
			pTri = (TriAngle*)pDoc->TriList->GetNext(pos8);			

			POSITION pos9 = pDoc->PointList->GetHeadPosition();
			while(pos9 != NULL)
			{
				PointCls* pa = (PointCls*)pDoc->PointList->GetNext(pos9);

				if(pa->index == pTri->index[0])
				{
					p4 = pa;
				}
				if(pa->index == pTri->index[1])
				{
					p5 = pa;
				}
				if(pa->index == pTri->index[2])
				{
					p6 = pa;
				}
			}			
			pDC->MoveTo(p4->x, p4->y);
			pDC->LineTo(p5->x, p5->y);
			pDC->MoveTo(p5->x, p5->y);
			pDC->LineTo(p6->x, p6->y);
			pDC->MoveTo(p6->x, p6->y);
			pDC->LineTo(p4->x, p4->y);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDelaunayView printing

BOOL CDelaunayView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDelaunayView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDelaunayView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDelaunayView diagnostics

#ifdef _DEBUG
void CDelaunayView::AssertValid() const
{
	CView::AssertValid();
}

void CDelaunayView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDelaunayDoc* CDelaunayView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDelaunayDoc)));
	return (CDelaunayDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDelaunayView message handlers

void CDelaunayView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDelaunayDoc* pDoc = GetDocument();
	
	startPoint = point;
	PointCls* p = new PointCls(point.x, point.y, pointNumber);
	pDoc->PointList->AddTail(p);
	pointNumber++;

	CClientDC dc(this);
	dc.SetPixel(point, RGB(255, 0, 0));

	CView::OnLButtonDown(nFlags, point);
}

//计算两个向量之间的夹角
//两个向量分别为(x1[0], x1[1]),(x2[0], x2[1])
double  GetAngle(double x1[2],
			     double x2[2])
{
	double temp;
	double norm1,norm2;
	norm1 = sqrt(x1[ 0 ] * x1[ 0 ] + x1[ 1 ] * x1[ 1 ]);
	norm2 = sqrt(x2[ 0 ] * x2[ 0 ] + x2[ 1 ] * x2[ 1 ]);
	temp = x1[ 0 ] * x2[ 0 ] + x1[ 1 ] * x2[ 1 ];
	if(norm1 == 0 || norm2 == 0)
	{
		return 0;
	}
	else
	{
		temp = temp / (norm1 * norm2);
		if(temp > 1.0)
		{
			temp = 1.0;
		}
		else if(temp < -1.0)
		{
			temp = -1.0;
		}
		return acos(temp);
	}	
}

void CDelaunayView::createFirstTri(CObList* pointList, 
								   CObList* triList,
								   PointCls* p1)
{
	POSITION pos1, pos4, pos5, pos6, pos7, pos8;
	PointCls *p2, *p3;
	double distance = 1e20;
	double maxAngle = 0.0;
	bool inside1 = false;
	bool inside2 = false;

	bool again = false;
	
	pos1 = pointList->GetHeadPosition(); 
	if(p1 == NULL)
	{
		p1 = (PointCls*)pointList->GetNext(pos1);
	}
	else
	{
		again = true;
	}

	if(p1->vertex)//p1的所有边的使用次数均为2
		return;
//////////////////////////////////////////////////////////////////////
	//在点表中寻找距离p1最近的点p2
	while(pos1 != NULL)
	{
		pos4 = pos1;
		PointCls* pa = (PointCls*)pointList->GetNext(pos1);
		if(pa->vertex)
			continue;
//		if(again)
//		{
//			if(!pa->intri)
//				continue;
//		}
		double tempDis = sqrt((pa->x - p1->x) * (pa->x - p1->x) +
			(pa->y - p1->y) * (pa->y - p1->y));
		if(tempDis < distance
			&& tempDis > 0)
		{
			inside1 = true;
			distance = tempDis;
			pos5 = pos4;
		}
	}
	if(inside1)
	{
		p2 = (PointCls*)pointList->GetAt(pos5);
	}
	else
		return;
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
	//在点表中寻找与p1，p2所成夹角最大的点
	if(p2->intri)
	{
		pos6 = pointList->GetHeadPosition();
		while(pos6 != NULL)
		{
			pos7 = pos6;
			PointCls* p = (PointCls*)pointList->GetNext(pos6);

			POSITION position1, position2, position3;
			bool inEdgeList = false;
			position1 = p2->edgeList->GetHeadPosition();
			while(position1 != NULL)
			{
				position2 = position1;
				EdgeNode* pTemp = (EdgeNode*)p2->edgeList->GetNext(position1);
				if(pTemp->index == p->index)
				{
					inEdgeList = true;
					position3 = position2;
					break;
				}
			}
			if(!inEdgeList)
				continue;
			else
			{
				if(p->vertex)
					continue;
				
				double x1[2], x2[2];
				x1[0] = p1->x - p->x;
				x1[1] = p1->y - p->y;
				x2[0] = p2->x - p->x;
				x2[1] = p2->y - p->y;
				double angle = GetAngle(x1, x2);
				if(angle > maxAngle)
				{
					inside2 = true;
					maxAngle = angle;
					pos8 = pos7;
				}
			}
		}
		if(inside2)
		{
			p3 = (PointCls*)pointList->GetAt(pos8);
		}
		else
			return;
	}
	else
	{
		pos6 = pointList->GetHeadPosition(); 
		while(pos6 != NULL)
		{
			pos7 = pos6;
			PointCls* p = (PointCls*)pointList->GetNext(pos6);
			if(p->vertex)
				continue;
			double x1[2], x2[2];
			x1[0] = p1->x - p->x;
			x1[1] = p1->y - p->y;
			x2[0] = p2->x - p->x;
			x2[1] = p2->y - p->y;
			double angle = GetAngle(x1, x2);
			if(angle > maxAngle)
			{
				inside2 = true;
				maxAngle = angle;
				pos8 = pos7;
			}
		}
		if(inside2)
		{
			p3 = (PointCls*)pointList->GetAt(pos8);
		}
		else
			return;
	}
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
	//处理p1, p2, p3是当前三角剖分中的点的情形
	if(p1->intri && p2->intri && p3->intri)//p1, p2, p3都在当前剖分中
		return;
	else if(!p1->intri && p2->intri && p3->intri)
	{
		POSITION pos41, pos42, pos43;
		EdgeNode* pEdge10;
		bool inside6 = false;
		pos41 = p2->edgeList->GetHeadPosition();
		while(pos41 != NULL)
		{
			pos42 = pos41;
			EdgeNode* pEdge = (EdgeNode*)p2->edgeList->GetNext(pos41);
			if(pEdge->index == p3->index)
			{
				inside6 = true;
				pos43 = pos42;
				break;
			}
		}		
		
		if(inside6)
		{
			pEdge10 = (EdgeNode*)p2->edgeList->GetAt(pos43);
			pEdge10->nCount++;
		}
		else
		{
			EdgeNode* pEdge11 = new EdgeNode(p3->index, 1);
			p2->edgeList->AddTail(pEdge11);
		}

		POSITION pos51, pos52, pos53;
		EdgeNode* pEdge12;
		bool inside7 = false;
		pos51 = p3->edgeList->GetHeadPosition();
		while(pos51 != NULL)
		{
			pos52 = pos51;
			EdgeNode* pEdge = (EdgeNode*)p3->edgeList->GetNext(pos51);
			if(pEdge->index == p2->index)
			{
				inside7 = true;
				pos53 = pos52;
				break;
			}
		}		
		
		if(inside7)
		{
			pEdge12 = (EdgeNode*)p3->edgeList->GetAt(pos53);
			pEdge12->nCount++;
		}
		else
		{
			EdgeNode* pEdge13 = new EdgeNode(p2->index, 1);
			p3->edgeList->AddTail(pEdge13);
		}

		EdgeNode* pEdge1 = new EdgeNode(p2->index, 1);
	    EdgeNode* pEdge2 = new EdgeNode(p3->index, 1);
		EdgeNode* pEdge3 = new EdgeNode(p1->index, 1);
		EdgeNode* pEdge4 = new EdgeNode(p1->index, 1);

		p1->edgeList->AddTail(pEdge1);
	    p1->edgeList->AddTail(pEdge2);

		p2->edgeList->AddTail(pEdge3);
		p3->edgeList->AddTail(pEdge4);
	}
	else if(p1->intri && !p2->intri && p3->intri)
	{
		POSITION pos41, pos42, pos43;
		EdgeNode* pEdge10;
		bool inside6 = false;
		pos41 = p1->edgeList->GetHeadPosition();
		while(pos41 != NULL)
		{
			pos42 = pos41;
			EdgeNode* pEdge = (EdgeNode*)p1->edgeList->GetNext(pos41);
			if(pEdge->index == p3->index)
			{
				inside6 = true;
				pos43 = pos42;
				break;
			}
		}		
		
		if(inside6)
		{
			pEdge10 = (EdgeNode*)p1->edgeList->GetAt(pos43);
			pEdge10->nCount++;
		}
		else
		{
			EdgeNode* pEdge11 = new EdgeNode(p3->index, 1);
			p1->edgeList->AddTail(pEdge11);
		}

		POSITION pos51, pos52, pos53;
		EdgeNode* pEdge12;
		bool inside7 = false;
		pos51 = p3->edgeList->GetHeadPosition();
		while(pos51 != NULL)
		{
			pos52 = pos51;
			EdgeNode* pEdge = (EdgeNode*)p3->edgeList->GetNext(pos51);
			if(pEdge->index == p1->index)
			{
				inside7 = true;
				pos53 = pos52;
				break;
			}
		}		
		
		if(inside7)
		{
			pEdge12 = (EdgeNode*)p3->edgeList->GetAt(pos53);
			pEdge12->nCount++;
		}
		else
		{
			EdgeNode* pEdge13 = new EdgeNode(p1->index, 1);
			p3->edgeList->AddTail(pEdge13);
		}

		EdgeNode* pEdge1 = new EdgeNode(p1->index, 1);
	    EdgeNode* pEdge2 = new EdgeNode(p3->index, 1);
		EdgeNode* pEdge3 = new EdgeNode(p2->index, 1);
		EdgeNode* pEdge4 = new EdgeNode(p2->index, 1);

		p2->edgeList->AddTail(pEdge1);
	    p2->edgeList->AddTail(pEdge2);

		p1->edgeList->AddTail(pEdge3);
		p3->edgeList->AddTail(pEdge4);
	}
	else if(p1->intri && p2->intri && !p3->intri)
	{
		POSITION pos41, pos42, pos43;
		EdgeNode* pEdge10;
		bool inside6 = false;
		pos41 = p1->edgeList->GetHeadPosition();
		while(pos41 != NULL)
		{
			pos42 = pos41;
			EdgeNode* pEdge = (EdgeNode*)p1->edgeList->GetNext(pos41);
			if(pEdge->index == p2->index)
			{
				inside6 = true;
				pos43 = pos42;
				break;
			}
		}		
		
		if(inside6)
		{
			pEdge10 = (EdgeNode*)p1->edgeList->GetAt(pos43);
			pEdge10->nCount++;
		}
		else
		{
			EdgeNode* pEdge11 = new EdgeNode(p2->index, 1);
			p1->edgeList->AddTail(pEdge11);
		}

		POSITION pos51, pos52, pos53;
		EdgeNode* pEdge12;
		bool inside7 = false;
		pos51 = p2->edgeList->GetHeadPosition();
		while(pos51 != NULL)
		{
			pos52 = pos51;
			EdgeNode* pEdge = (EdgeNode*)p2->edgeList->GetNext(pos51);
			if(pEdge->index == p1->index)
			{
				inside7 = true;
				pos53 = pos52;
				break;
			}
		}		
		
		if(inside7)
		{
			pEdge12 = (EdgeNode*)p2->edgeList->GetAt(pos53);
			pEdge12->nCount++;
		}
		else
		{
			EdgeNode* pEdge13 = new EdgeNode(p1->index, 1);
			p2->edgeList->AddTail(pEdge13);
		}

		EdgeNode* pEdge1 = new EdgeNode(p1->index, 1);
	    EdgeNode* pEdge2 = new EdgeNode(p2->index, 1);
		EdgeNode* pEdge3 = new EdgeNode(p3->index, 1);
		EdgeNode* pEdge4 = new EdgeNode(p3->index, 1);

		p3->edgeList->AddTail(pEdge1);
	    p3->edgeList->AddTail(pEdge2);

		p1->edgeList->AddTail(pEdge3);
		p2->edgeList->AddTail(pEdge4);
	}
	else
	{
		EdgeNode* pEdge1 = new EdgeNode(p2->index, 1);
		EdgeNode* pEdge2 = new EdgeNode(p3->index, 1);
		EdgeNode* pEdge3 = new EdgeNode(p1->index, 1);
		EdgeNode* pEdge4 = new EdgeNode(p2->index, 1);
		EdgeNode* pEdge5 = new EdgeNode(p3->index, 1);
		EdgeNode* pEdge6 = new EdgeNode(p1->index, 1);

		p1->edgeList->AddTail(pEdge1);
		p1->edgeList->AddTail(pEdge5);

		p2->edgeList->AddTail(pEdge2);
		p2->edgeList->AddTail(pEdge6);
		
		p3->edgeList->AddTail(pEdge3);
		p3->edgeList->AddTail(pEdge4);
	}
//////////////////////////////////////////////////////////////////////
	p1->intri = true;
	p2->intri = true;
	p3->intri = true;	

	TriAngle* pTri = new TriAngle(p1->index, 
		                          p2->index, 
								  p3->index);
	triList->AddTail(pTri);

	Tricount++;
}

void CDelaunayView::enlargeEdge(PointCls *p1, 
								PointCls *p2,
								PointCls *p3,
								CObList* pointList,
								CObList* triList)
{
	POSITION pos1, pos2, pos3;
	EdgeNode* pEdge1 = NULL;
	bool inside = false;
	pos1 = p1->edgeList->GetHeadPosition();
	while(pos1 != NULL)
	{
		pos2 = pos1;
		EdgeNode* pEdge = (EdgeNode*)p1->edgeList->GetNext(pos1);
		if(pEdge->index == p2->index)
		{
			inside = true;
			pos3 = pos2;
			break;
		}
	}
	if(inside)
	{
		pEdge1 = (EdgeNode*)p1->edgeList->GetAt(pos3);
	}
	else
		return;

	if(inside && (2 == pEdge1->nCount))
		return;

	POSITION pos4, pos5, pos6;
	double maxAngle = 0.0;
	PointCls* p4 = NULL;
	bool flag = false;
	pos4 = pointList->GetHeadPosition();
	while(pos4 != NULL)
	{
		pos5 = pos4;
		
		PointCls* pTemp = (PointCls*)pointList->GetNext(pos4);
		if(pTemp->vertex)
			continue;
		
		double y1, y2;
		double ratio = (double)(p2->y - p1->y) / (p2->x - p1->x);
		y1 = p1->y + ratio * (p3->x - p1->x);
		y2 = p1->y + ratio * (pTemp->x - p1->x);
		if(pTemp == p1
		   || pTemp == p2)
		   continue;
		else if((p3->y >= y1 && pTemp->y >= y2)//判断pTemp是否与p3同侧
			    || (y1 >= p3->y && y2 >= pTemp->y))
				continue;
		else
		{
			POSITION pos7, pos8, pos9, pos10;
			bool inside1 = false;
			bool inside2 = false;
			EdgeNode* pEdge3 = NULL;
			EdgeNode* pEdge4 = NULL;
			pos7 = pTemp->edgeList->GetHeadPosition();
			while(pos7 != NULL)
			{
				pos8 = pos7;
				EdgeNode* pEdge = (EdgeNode*)pTemp->edgeList->GetNext(pos7);
				if(pEdge->index == p1->index
				   || pEdge->index == p2->index)
				{
					if(pEdge->index == p1->index)
					{
						inside1 = true;
						pos9 = pos8;
					}
					else
					{
						inside2 = true;
						pos10 = pos8;
					}
				}
			}
			if(inside1)
			{
				pEdge3 = (EdgeNode*)pTemp->edgeList->GetAt(pos9);
				if(2 == pEdge3->nCount)
					continue;
			}
			if(inside2)
			{
				pEdge4 = (EdgeNode*)pTemp->edgeList->GetAt(pos10);
				if(2 == pEdge4->nCount)
					continue;
			}
		}

		double x1[2], x2[2];
		x1[0] = p1->x - pTemp->x;
		x1[1] = p1->y - pTemp->y;
		x2[0] = p2->x - pTemp->x;
		x2[1] = p2->y - pTemp->y;
		double angle = GetAngle(x1, x2);
		if(angle > maxAngle)
		{
			maxAngle = angle;
			pos6 = pos5;
			flag = true;
		}
	}
	if(flag)
	{
		p4 = (PointCls*)pointList->GetAt(pos6);
	}

	if(p4 != NULL)
	{
		//update p1->edgeList
		if( pEdge1!= NULL)
		{
			pEdge1->nCount++;
		}

		POSITION pos11, pos12, pos13;
		EdgeNode* pEdge5;
		bool inside3 = false;
		pos11 = p1->edgeList->GetHeadPosition();
		while(pos11 != NULL)
		{
			pos12 = pos11;
			EdgeNode* pEdge = (EdgeNode*)p1->edgeList->GetNext(pos11);
			if(pEdge->index == p4->index)
			{
				inside3 = true;
				pos13 = pos12;
				break;
			}
		}		
		
		if(inside3)
		{
			pEdge5 = (EdgeNode*)p1->edgeList->GetAt(pos13);
			pEdge5->nCount++;
		}
		else
		{
			EdgeNode* pEdge6 = new EdgeNode(p4->index, 1);
			p1->edgeList->AddTail(pEdge6);
		}

		//遍历p1的边表，若所有结点的边使用次数都为2，则将p1从点链PointList中删除。
        POSITION pos61;
		int number1 = 0;
		int number2 = 0;
		pos61 = p1->edgeList->GetHeadPosition();
		while(pos61 != NULL)
		{
			EdgeNode* pEdge = (EdgeNode*)p1->edgeList->GetNext(pos61);
			if(2 == pEdge->nCount)
			{
				number1++;
			}
			number2++;
		}
		if(number1 == number2)
		{
			p1->vertex = true;
		}

		//update p2->edgeList
		POSITION pos21, pos22, pos23;
		EdgeNode* pEdge7;
		bool inside4 = false;
		pos21 = p2->edgeList->GetHeadPosition();
		while(pos21 != NULL)
		{
			pos22 = pos21;
			EdgeNode* pEdge = (EdgeNode*)p2->edgeList->GetNext(pos21);
			if(pEdge->index == p1->index)
			{
				inside4 = true;
				pos23 = pos22;
				break;
			}
		}
		if(inside4)
		{
			pEdge7 = (EdgeNode*)p2->edgeList->GetAt(pos23);
			pEdge7->nCount++;
		}

		POSITION pos31, pos32, pos33;
		EdgeNode* pEdge8;
		bool inside5 = false;
		pos31 = p2->edgeList->GetHeadPosition();
		while(pos31 != NULL)
		{
			pos32 = pos31;
			EdgeNode* pEdge = (EdgeNode*)p2->edgeList->GetNext(pos31);
			if(pEdge->index == p4->index)
			{
				inside5 = true;
				pos33 = pos32;
				break;
			}
		}		
		
		if(inside5)
		{
			pEdge8 = (EdgeNode*)p2->edgeList->GetAt(pos33);
			pEdge8->nCount++;
		}
		else
		{
			EdgeNode* pEdge9 = new EdgeNode(p4->index, 1);
			p2->edgeList->AddTail(pEdge9);
		}

		//遍历p2的边表，若所有结点的边使用次数都为2，则将p2从点链PointList中删除。
        POSITION pos71, pos72;
		int number3 = 0;
		int number4 = 0;
		pos71 = p2->edgeList->GetHeadPosition();
		while(pos71 != NULL)
		{
			pos72 = pos71;
			EdgeNode* pEdge = (EdgeNode*)p2->edgeList->GetNext(pos71);
			if(2 == pEdge->nCount)
			{
				number3++;
			}
			number4++;
		}
		if(number3 == number4)
		{
			p2->vertex = true;
		}

		//update p4->edgeList
		POSITION pos41, pos42, pos43;
		EdgeNode* pEdge10;
		bool inside6 = false;
		pos41 = p4->edgeList->GetHeadPosition();
		while(pos41 != NULL)
		{
			pos42 = pos41;
			EdgeNode* pEdge = (EdgeNode*)p4->edgeList->GetNext(pos41);
			if(pEdge->index == p1->index)
			{
				inside6 = true;
				pos43 = pos42;
				break;
			}
		}		
		
		if(inside6)
		{
			pEdge10 = (EdgeNode*)p4->edgeList->GetAt(pos43);
			pEdge10->nCount++;
		}
		else
		{
			EdgeNode* pEdge11 = new EdgeNode(p1->index, 1);
			p4->edgeList->AddTail(pEdge11);
		}

		POSITION pos51, pos52, pos53;
		EdgeNode* pEdge12;
		bool inside7 = false;
		pos51 = p4->edgeList->GetHeadPosition();
		while(pos51 != NULL)
		{
			pos52 = pos51;
			EdgeNode* pEdge = (EdgeNode*)p4->edgeList->GetNext(pos51);
			if(pEdge->index == p2->index)
			{
				inside7 = true;
				pos53 = pos52;
				break;
			}
		}		
		
		if(inside7)
		{
			pEdge12 = (EdgeNode*)p4->edgeList->GetAt(pos53);
			pEdge12->nCount++;
		}
		else
		{
			EdgeNode* pEdge13 = new EdgeNode(p2->index, 1);
			p4->edgeList->AddTail(pEdge13);
		}

		//遍历p4的边表，若所有结点的边使用次数都为2，则将p4从点链PointList中删除。
        POSITION pos81, pos82;
		int number5 = 0;
		int number6 = 0;
		pos81 = p4->edgeList->GetHeadPosition();
		while(pos81 != NULL)
		{
			pos82 = pos81;
			EdgeNode* pEdge = (EdgeNode*)p4->edgeList->GetNext(pos81);
			if(2 == pEdge->nCount)
			{
				number5++;
			}
			number6++;
		}
		if(number5 == number6)
		{
			p4->vertex = true;
		}


		//加入新三角形
		TriAngle* pTri = new TriAngle(p1->index, 
			p2->index, 
			p4->index);
		triList->AddTail(pTri);

		p4->intri = true;
		
		Tricount++;
	}
}

void CDelaunayView::enlargeTri(CObList* pointList,
							   CObList* TriList)
{
	POSITION pos1, pos2, pos3;
	PointCls *p1, *p2, *p3;
	p1 = p2 = p3 = NULL;
	TriAngle* pTri;

	pos1 = TriList->GetHeadPosition();	
	while(pos1 != NULL)
	{
		pos3 = pos1;
		pTri = (TriAngle*)TriList->GetNext(pos1);			
		
		if(!pTri->enlarge)
		{
			pos2 = pointList->GetHeadPosition();
			while(pos2 != NULL)
			{
				PointCls* pa = (PointCls*)pointList->GetNext(pos2);
				
				if(pa->index == pTri->index[0])
				{
					p1 = pa;
				}
				if(pa->index == pTri->index[1])
				{
					p2 = pa;
				}
				if(pa->index == pTri->index[2])
				{
					p3 = pa;
				}			
			}
			if(p1 == NULL || p2 == NULL || p3 == NULL)
				return;
			enlargeEdge(p2, p3, p1, pointList, TriList);
			enlargeEdge(p3, p1, p2, pointList, TriList);

			pTri->enlarge = true;
		}		
	}
}

void CDelaunayView::continueEnlarge(CObList* pointList,
		                            CObList* TriList)
{
	POSITION pos1, pos2, pos3;
	PointCls *p, *p1, *p2, *p3;
	p1 = p2 = p3 = NULL;
	
	pos1 = pointList->GetHeadPosition();
	
	while(pos1 != NULL)
	{
		p = (PointCls*)pointList->GetNext(pos1);
		if(p->intri)
			continue;
		else
		{
			createFirstTri(pointList,
				TriList,
				p);
			
			TriAngle *pTriSeed, *ptri;
			pTriSeed = NULL;
			
			pos2 = TriList->GetHeadPosition();
			while(pos2 != NULL)
			{
				ptri = (TriAngle*)TriList->GetNext(pos2);
				
				if(ptri->enlarge)
					continue;
				else
				{
					pTriSeed = ptri;
					pos3 = pointList->GetHeadPosition();
					while(pos3 != NULL)
					{
						PointCls* pa = (PointCls*)pointList->GetNext(pos3);
						
						if(pa->vertex)
							continue;
						
						if(pa->index == pTriSeed->index[0])
						{
							p1 = pa;
						}
						if(pa->index == pTriSeed->index[1])
						{
							p2 = pa;
						}
						if(pa->index == pTriSeed->index[2])
						{
							p3 = pa;
						}
					}
					if(p1 == NULL || p2 == NULL || p3 == NULL)
						return;
					
					enlargeEdge(p1, p2, p3, pointList, TriList);
					
					enlargeTri(pointList, TriList);					
				}
			}			
		}
	}	
}

void CDelaunayView::OnDelaunay() 
{
	// TODO: Add your command handler code here
	CDelaunayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	

	if(!pDoc->PointList->GetCount())
	{
		char str[100];
		ostrstream osr(str,100);		
		osr<<"请用鼠标左键在窗口里选择要进行三角剖分的顶点"<<'\n'
			<<"                  谢谢合作"<<'\0';
		CString output(str);
		MessageBox(output);
		return;
	}

	PointCls *p1, *p2, *p3;	
	POSITION pos4, pos5;

	createFirstTri(pDoc->PointList,
			       pDoc->TriList);
	
	pos4 = pDoc->TriList->GetHeadPosition();
	TriAngle* pTriSeed = (TriAngle*)pDoc->TriList->GetAt(pos4);

	pos5 = pDoc->PointList->GetHeadPosition();
	while(pos5 != NULL)
	{
		PointCls* pa = (PointCls*)pDoc->PointList->GetNext(pos5);

		if(pa->index == pTriSeed->index[0])
		{
			p1 = pa;
		}
		if(pa->index == pTriSeed->index[1])
		{
			p2 = pa;
		}
		if(pa->index == pTriSeed->index[2])
		{
			p3 = pa;
		}
	}
	enlargeEdge(p1, p2, p3, pDoc->PointList, pDoc->TriList);

	enlargeTri(pDoc->PointList, pDoc->TriList);

	continueEnlarge(pDoc->PointList, pDoc->TriList);

	Invalidate();
}
