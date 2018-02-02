// PubDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "PubDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPubDlg

IMPLEMENT_DYNCREATE(CPubDlg, CFormView)

CPubDlg::CPubDlg()
	: CFormView(CPubDlg::IDD)
{
	//{{AFX_DATA_INIT(CPubDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPubDlg::~CPubDlg()
{
}

void CPubDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPubDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPubDlg, CFormView)
	//{{AFX_MSG_MAP(CPubDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPubDlg diagnostics

#ifdef _DEBUG
void CPubDlg::AssertValid() const
{
	CFormView::AssertValid();
}

void CPubDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPubDlg message handlers
