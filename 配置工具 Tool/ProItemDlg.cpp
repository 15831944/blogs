// ProItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "ProItemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProItemDlg dialog


CProItemDlg::CProItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProItemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProItemDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CProItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProItemDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProItemDlg, CDialog)
	//{{AFX_MSG_MAP(CProItemDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProItemDlg message handlers

void CProItemDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
