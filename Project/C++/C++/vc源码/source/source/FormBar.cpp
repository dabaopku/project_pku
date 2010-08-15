// FormBar.cpp : implementation file
//

#include "stdafx.h"
#include "flashnow.h"
#include "FormBar.h"
#include "ViewerFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormBar dialog


CFormBar::CFormBar(CWnd* pParent /*=NULL*/)
{
	m_DragMode=FALSE;
	//{{AFX_DATA_INIT(CFormBar)
	//}}AFX_DATA_INIT
}


BEGIN_MESSAGE_MAP(CFormBar, CDialogBar)
//{{AFX_MSG_MAP(CFormBar)
ON_WM_HSCROLL()
ON_CBN_EDITCHANGE(IDC_URL_LIST,OnEditChange)
ON_CBN_SELENDOK(IDC_URL_LIST,OnSelectItem)
ON_WM_DESTROY()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormBar message handlers
void CFormBar::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	switch(nSBCode)
	{
	case TB_THUMBTRACK:
		m_DragMode=TRUE;
		::theApp.p_Viewer->NoWait();
		break;
	case TB_ENDTRACK:
		m_DragMode=FALSE;
		break;
	}
	if(nSBCode!=TB_ENDTRACK)
		::theApp.p_Viewer->SetCurrentFrame(nPos);
	CDialogBar::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CFormBar::LoadList()
{
	m_List.ResetContent();
	
	TCHAR *p=::theApp.m_UserData.m_TypedURLs,*cp;
	cp=p;
	while(*p)
	{
		if(*p==';')
		{
			*p='\0';
			InsertItem(cp);
			cp=p+1;
		}
		p++;
	}
	m_List.SetCurSel(0);
}

void CFormBar::OnEditChange()
{
	if (!m_AutoComplete) 
		return;
	CString Text;
	m_List.GetWindowText(Text);
	int nLength=Text.GetLength();
	
	DWORD dwCurSel=m_List.GetEditSel();
	WORD dStart=LOWORD(dwCurSel);
	WORD dEnd=HIWORD(dwCurSel);
	
	if(m_List.SelectString(-1,Text)==CB_ERR)
	{
		m_List.SetWindowText(Text);
		if(dwCurSel!=CB_ERR)
			m_List.SetEditSel(dStart,dEnd);
	}
	
	m_List.GetWindowText(Text);
	
	if(dEnd<nLength&&dwCurSel!=CB_ERR)
		m_List.SetEditSel(dStart,dEnd);
	else
		m_List.SetEditSel(nLength,-1);
}

void CFormBar::OnSelectItem()
{
	CString Text;
	m_List.GetLBText(m_List.GetCurSel(),Text);
	::theApp.LoadMovie(Text);
}

BOOL CFormBar::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN)
	{
		CWnd *pWnd=m_List.GetWindow(GW_CHILD);
		
		if(pWnd->m_hWnd==pMsg->hwnd)
		{
			CString Text;
			switch(pMsg->wParam)
			{
			case VK_RETURN:
				m_List.GetWindowText(Text);
				if(!Text.IsEmpty())
				{
					InsertItem(Text);
					::theApp.LoadMovie(Text);
				}
				
			case VK_DELETE:
			case VK_BACK:
				m_AutoComplete=FALSE;
				break;
			default:
				m_AutoComplete=TRUE;
				break;
			}
		}
	}
	return CDialogBar::PreTranslateMessage(pMsg);
}

void CFormBar::SaveList()
{
	::theApp.m_UserData.m_TypedURLs[0]='\0';
	CString Item;
	for(int i=0;i<m_List.GetCount();i++)
	{
		m_List.GetLBText(i,Item);
		Item+=';';
		strcat(::theApp.m_UserData.m_TypedURLs,Item);
	}
}

CFormBar::~CFormBar()
{
}

void CFormBar::DoDataExchange(CDataExchange* pDX) 
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormBar)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CFormBar::ResizeSlider()
{
	if(m_Slider.GetSafeHwnd())
	{
		CRect Rect;
		CRect ViewRect;
		CRect BarRect;
		
		GetWindowRect(&BarRect);
		::theApp.p_Viewer->GetWindowRect(&ViewRect);
		m_Slider.GetWindowRect(&Rect);
		
		m_Slider.MoveWindow(Rect.left-BarRect.left,Rect.top-BarRect.top,ViewRect.right-10-Rect.left,Rect.Height());
	}
}

void CFormBar::OnInitDialog()
{
	CWnd *pWnd;
	
	pWnd=GetDlgItem(IDC_URL_LIST);
	ASSERT(pWnd);
	m_List.Attach(pWnd->m_hWnd);
	
	pWnd=GetDlgItem(IDC_FRAME_SLIDER);
	m_Slider.Attach(pWnd->m_hWnd);
	
	LoadList();
}

void CFormBar::OnDestroy() 
{
	CDialogBar::OnDestroy();
	SaveList();
	m_List.Detach();
	m_Slider.Detach();	
}

void CFormBar::InsertItem(CString URL)
{
	if(m_List.GetCount()>100)
		return;
	if(!URL.IsEmpty()&&m_List.FindString(-1,URL)==LB_ERR)
	{
		m_List.AddString(URL);
		m_LastURL="";
	}
}
