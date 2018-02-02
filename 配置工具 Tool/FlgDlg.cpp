// FlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "FlgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlgDlg

IMPLEMENT_DYNCREATE(CFlgDlg, CFormView)

CFlgDlg::CFlgDlg()
	: CFormView(CFlgDlg::IDD)
{
	//{{AFX_DATA_INIT(CFlgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CFlgDlg::~CFlgDlg()
{
}

void CFlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlgDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFlgDlg, CFormView)
	//{{AFX_MSG_MAP(CFlgDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlgDlg diagnostics

#ifdef _DEBUG
void CFlgDlg::AssertValid() const
{
	CFormView::AssertValid();
}

void CFlgDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFlgDlg message handlers
