// FocusScrollListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "FocusScrollListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFocusScrollListCtrl

CFocusScrollListCtrl::CFocusScrollListCtrl()
{
}

CFocusScrollListCtrl::~CFocusScrollListCtrl()
{
}


BEGIN_MESSAGE_MAP(CFocusScrollListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CFocusScrollListCtrl)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFocusScrollListCtrl message handlers

void CFocusScrollListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	if (GetFocus() != this)
	{
		SetFocus();
	}
	
	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CFocusScrollListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	if (GetFocus() != this)
	{
		SetFocus();
	}
	
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}
