// 36BML.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "36BML.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C36BML dialog


C36BML::C36BML(CWnd* pParent /*=NULL*/)
	: CDialog(C36BML::IDD, pParent)
{
	//{{AFX_DATA_INIT(C36BML)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void C36BML::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C36BML)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C36BML, CDialog)
	//{{AFX_MSG_MAP(C36BML)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C36BML message handlers
