// Falut.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "Falut.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFalut dialog


CFalut::CFalut(CWnd* pParent /*=NULL*/)
	: CDialog(CFalut::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFalut)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}



void CFalut::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFalut)
	DDX_Control(pDX, IDC_TAB1, m_tab);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFalut, CDialog)
	//{{AFX_MSG_MAP(CFalut)
	ON_NOTIFY(NM_CLICK, IDC_LIST5, OnClickList5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFalut message handlers

BOOL CFalut::OnInitDialog() 
{
	
	CDialog::OnInitDialog();
    
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
				  
}

void CFalut::OnClickList5(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
