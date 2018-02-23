// DoItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "DoItemDlg.h"
#include "IniStru.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DoStru_ mDoItem;
/////////////////////////////////////////////////////////////////////////////
// CDoItemDlg dialog


CDoItemDlg::CDoItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDoItemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDoItemDlg)
	m_name = _T("");
	m_DOAddr = 0;
	//}}AFX_DATA_INIT
}


void CDoItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoItemDlg)
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_DOAddr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDoItemDlg, CDialog)
	//{{AFX_MSG_MAP(CDoItemDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoItemDlg message handlers

void CDoItemDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	mDoItem.name = m_name;
	mDoItem.DOAddr = m_DOAddr;
	CDialog::OnOK();
}

BOOL CDoItemDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_name = mDoItem.name;
	m_DOAddr = mDoItem.DOAddr;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
