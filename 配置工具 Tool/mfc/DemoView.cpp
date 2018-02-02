// DemoView.cpp : implementation of the CDemoView class
//

#include "stdafx.h"
#include "Demo.h"
#include "MyFun.h"
//#include "DemoDoc.h"
#include "DemoView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CView *pOldView;
/////////////////////////////////////////////////////////////////////////////
// CDemoView

IMPLEMENT_DYNCREATE(CDemoView, CView)

BEGIN_MESSAGE_MAP(CDemoView, CView)
	//{{AFX_MSG_MAP(CDemoView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoView construction/destruction
UINT CDemoView::RunStr(LPVOID para)
{
	CDemoView *pthis = (CDemoView *)para;
//	CDC  *pDc = (CDC *)para;
	int strlen = pthis->m_strWelcome.GetLength()*8;
	int strhei = 8;
	int addx,addy;
	pthis->m_cx = pthis->m_cy = 0;
	addx = 4;
	addy = 2;

	while(pthis->m_bIsRuning)
	{
		if(pthis->m_cx<0)
			pthis->m_cx = 0;
		if(pthis->m_cy<0)
			pthis->m_cy = 0;
		pthis->Invalidate();
		pthis->m_cx+=addx;
		pthis->m_cy+=addy;
		if( (pthis->m_cx + strlen) >= (pthis->m_rect.right) || (pthis->m_cx <= 0))
		{
			addx = -addx;
		}
		if((pthis->m_cy + strhei) >= (pthis->m_rect.bottom) || (pthis->m_cy <= 0))
		{
			addy = -addy;
		}
		Sleep(20);
		TRACE(Str(pthis->m_cx)+" "+Str(pthis->m_cy)+"\n");
	}

	return TRUE;
}

CDemoView::CDemoView()
{
	// TODO: add construction code here
	m_bIsRuning = false;
	m_strWelcome = "欢迎使用MK保护故障配置编辑工具";
}

CDemoView::~CDemoView()
{
	m_bIsRuning = false;
}

BOOL CDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView drawing

void CDemoView::OnDraw(CDC* pDC)
{
//	CDemoDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//	RECT rect;
/*
	GetClientRect(&rect);
	int cx,cy;
	cy = (rect.bottom - rect.top)/2 + rect.top - 5;
	cx = (rect.right - rect.left)/2 + rect.left - 115;
//	CDC *dc = pDC;//GetDC();
//	CFont *font = dc->GetCurrentFont();
	if (!m_bIsRuning)
	{
		m_bIsRuning = true;
		AfxBeginThread(CDemoView::RunStr,this);
	}
	//pDC->TextOut(cx,cy,"欢迎使用PZK300方式字编辑工具!");
*/

	/* 设置欢迎字符串的字体 */
	int		height = 30;//(m_totalLog.cy / 10) / 5;  // 1/5 of box size
	CFont    *font, *oldFont;
	font = new CFont();
    font->CreateFont(height, 0, 0, 0,
         FW_NORMAL, FALSE, FALSE,
         FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
         DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, "宋体");//"Arial");
	oldFont = pDC->SelectObject(font);

	/* 在中间位置显示欢迎字符串 */
	RECT rect;
	GetClientRect(&rect);
	int cx,cy;
	cy = (rect.bottom - rect.top)/2 + rect.top;
	cx = (rect.right - rect.left)/2 + rect.left - 150;
	pDC->TextOut(cx,cy,m_strWelcome);
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView diagnostics

#ifdef _DEBUG
void CDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDemoDoc* CDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoDoc)));
	return (CDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoView message handlers

void CDemoView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	//GetClientRect(&m_rect);

	if (!m_bIsRuning)
	{
		m_bIsRuning = true;
//		AfxBeginThread(CDemoView::RunStr,this);
	}
	// TODO: Add your specialized code here and/or call the base class
}

void CDemoView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	//GetWindowRect(&m_rect);
	GetClientRect(&m_rect);
	// TODO: Add your message handler code here

}
