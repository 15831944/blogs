// ScaleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "ScaleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScaleDlg

IMPLEMENT_DYNCREATE(CScaleDlg, CFormView)

CScaleDlg::CScaleDlg()
	: CFormView(CScaleDlg::IDD)
{
	//{{AFX_DATA_INIT(CScaleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CScaleDlg::~CScaleDlg()
{
}

void CScaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScaleDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScaleDlg, CFormView)
	//{{AFX_MSG_MAP(CScaleDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScaleDlg diagnostics

#ifdef _DEBUG
void CScaleDlg::AssertValid() const
{
	CFormView::AssertValid();
}

void CScaleDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScaleDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CScaleDlg

IMPLEMENT_DYNCREATE(CScaleDlg, CFormView)

CScaleDlg::CScaleDlg()
	: CFormView(CScaleDlg::IDD)
{
	//{{AFX_DATA_INIT(CScaleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CScaleDlg::~CScaleDlg()
{
}

void CScaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScaleDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScaleDlg, CFormView)
	//{{AFX_MSG_MAP(CScaleDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScaleDlg diagnostics

#ifdef _DEBUG
void CScaleDlg::AssertValid() const
{
	CFormView::AssertValid();
}

void CScaleDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScaleDlg message handlers
