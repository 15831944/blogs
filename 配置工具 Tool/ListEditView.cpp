// ListEditView.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "ListEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListEditView

IMPLEMENT_DYNCREATE(CListEditView, CListView)

CListEditView::CListEditView()
{
}

CListEditView::~CListEditView()
{
}


BEGIN_MESSAGE_MAP(CListEditView, CListView)
	//{{AFX_MSG_MAP(CListEditView)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListEditView drawing

void CListEditView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CListEditView diagnostics

#ifdef _DEBUG
void CListEditView::AssertValid() const
{
	CListView::AssertValid();
}

void CListEditView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListEditView message handlers

void CListEditView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CListView::OnPrint(pDC, pInfo);
}

void CListEditView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CListView::OnPaint() for painting messages
}

void CListEditView::OnSetFocus(CWnd* pOldWnd) 
{
	CListView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	
}

void CListEditView::OnKillFocus(CWnd* pNewWnd) 
{
	CListView::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	
}

void CListEditView::OnSize(UINT nType, int cx, int cy) 
{
	CListView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}
