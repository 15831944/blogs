// TempClass.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "TempClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTempClass

IMPLEMENT_DYNCREATE(CTempClass, CFormView)

CTempClass::CTempClass()
	: CFormView(CTempClass::IDD)
{
	//{{AFX_DATA_INIT(CTempClass)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CTempClass::~CTempClass()
{
}

void CTempClass::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTempClass)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTempClass, CFormView)
	//{{AFX_MSG_MAP(CTempClass)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTempClass diagnostics

#ifdef _DEBUG
void CTempClass::AssertValid() const
{
	CFormView::AssertValid();
}

void CTempClass::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTempClass message handlers
