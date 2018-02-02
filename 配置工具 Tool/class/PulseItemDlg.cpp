// PulseItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "PulseItemDlg.h"
#include "myfun.h"
#include "Inistru.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

PulseStru_ mPulseItem;
/////////////////////////////////////////////////////////////////////////////
// CPulseItemDlg dialog


CPulseItemDlg::CPulseItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPulseItemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPulseItemDlg)
	m_name = _T("");
	m_InputAddr = 0;
	//}}AFX_DATA_INIT
}


void CPulseItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPulseItemDlg)
	DDX_Control(pDX, IDC_COMBO1, m_AccMode);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_InputAddr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPulseItemDlg, CDialog)
	//{{AFX_MSG_MAP(CPulseItemDlg)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnKillfocusEdit2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPulseItemDlg message handlers

void CPulseItemDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	mPulseItem.name = m_name;
	mPulseItem.InputAddr = m_InputAddr;
	mPulseItem.AccMode = m_AccMode.GetCurSel();

	CDialog::OnOK();
}

BOOL CPulseItemDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_name = mPulseItem.name;
	m_InputAddr = mPulseItem.InputAddr;
	m_AccMode.SetCurSel(mPulseItem.AccMode);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPulseItemDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CPulseItemDlg::OnChangeEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT2);
	char str[32];
	pEdit->GetWindowText(str,32);
	int i = atoi(str);//.GetBuffer(str.GetLength()));
	if( i > 65535)
	{
		AfxMessageBox("不允许输入大于65535的值!");
		pEdit->SetWindowText("65535");	
	}	
}

void CPulseItemDlg::OnKillfocusEdit2() 
{
	// TODO: Add your control notification handler code here
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT2);
	char str[32];
	pEdit->GetWindowText(str,32);
	if(strlen(str) == 0)
	{
		pEdit->SetWindowText("0");
		return;
	}
}
