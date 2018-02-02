// SboItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "SboItemDlg.h"
#include "IniStru.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SboStru_ mSboItem;
/////////////////////////////////////////////////////////////////////////////
// CSboItemDlg dialog

CSboItemDlg::CSboItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSboItemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSboItemDlg)
	m_name = _T("");
	m_SboId = 0;
	m_tpw = 0;
	m_cpw = 0;
	//}}AFX_DATA_INIT
}


void CSboItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSboItemDlg)
	DDX_Control(pDX, IDC_COMBO1, m_valid);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_SboId);
	DDX_Text(pDX, IDC_EDIT3, m_tpw);
	DDX_Text(pDX, IDC_EDIT4, m_cpw);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSboItemDlg, CDialog)
	//{{AFX_MSG_MAP(CSboItemDlg)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT3, OnKillfocusEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT4, OnKillfocusEdit4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSboItemDlg message handlers

BOOL CSboItemDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_name = mSboItem.name;
	if (mSboItem.valid)
		m_valid.SetCurSel(0);
	else
		m_valid.SetCurSel(1);
	m_SboId = mSboItem.SboId;
	m_tpw = mSboItem.TripPulseWidth;
	m_cpw = mSboItem.ClosePulseWidth;

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSboItemDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	mSboItem.name = m_name;
	if(m_valid.GetCurSel() == 0)
		mSboItem.valid = true;
	else
		mSboItem.valid = false;
	mSboItem.SboId = m_SboId;
	mSboItem.TripPulseWidth = m_tpw;
	mSboItem.ClosePulseWidth = m_cpw;

	CDialog::OnOK();
}

void CSboItemDlg::OnChangeEdit2() 
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
	if( i > 255)
	{
		AfxMessageBox("不允许输入大于255的值!");
		pEdit->SetWindowText("255");	
	}	
}

void CSboItemDlg::OnChangeEdit3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT3);
	char str[32];
	pEdit->GetWindowText(str,32);
	int i = atoi(str);//.GetBuffer(str.GetLength()));
	if( i > 65535)
	{
		AfxMessageBox("不允许输入大于65535的值!");
		pEdit->SetWindowText("65535");	
	}	
}

void CSboItemDlg::OnChangeEdit4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT4);
	char str[32];
	pEdit->GetWindowText(str,32);
	int i = atoi(str);//.GetBuffer(str.GetLength()));
	if( i > 65535)
	{
		AfxMessageBox("不允许输入大于65535的值!");
		pEdit->SetWindowText("65535");	
	}	
}

void CSboItemDlg::OnKillfocusEdit2() 
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

void CSboItemDlg::OnKillfocusEdit3() 
{
	// TODO: Add your control notification handler code here
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT3);
	char str[32];
	pEdit->GetWindowText(str,32);
	if(strlen(str) == 0)
	{
		pEdit->SetWindowText("0");
		return;
	}	
}

void CSboItemDlg::OnKillfocusEdit4() 
{
	// TODO: Add your control notification handler code here
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT4);
	char str[32];
	pEdit->GetWindowText(str,32);
	if(strlen(str) == 0)
	{
		pEdit->SetWindowText("0");
		return;
	}	
}
