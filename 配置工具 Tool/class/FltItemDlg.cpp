// FltItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "FltItemDlg.h"
#include "IniStru.h"
#include "MyFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

FltStru_ mFltItem;
/////////////////////////////////////////////////////////////////////////////
// CFltItemDlg dialog


CFltItemDlg::CFltItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFltItemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFltItemDlg)
	m_name = _T("");
	m_FaultId = 0;
	m_IpValue = 0;
	m_3I0Value = 0;
	m_PositiveResistance = 0;
	m_PositiveReactance = 0;
	m_ZeroResistance = 0;
	m_ZeroReactance = 0;
	//}}AFX_DATA_INIT
}


void CFltItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFltItemDlg)
	DDX_Control(pDX, IDC_COMBO2, m_3I0FaultEnable);
	DDX_Control(pDX, IDC_COMBO1, m_IpFaultEnable);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_FaultId);
	DDX_Text(pDX, IDC_EDIT3, m_IpValue);
	DDX_Text(pDX, IDC_EDIT4, m_3I0Value);
	DDX_Text(pDX, IDC_EDIT5, m_PositiveResistance);
	DDX_Text(pDX, IDC_EDIT6, m_PositiveReactance);
	DDX_Text(pDX, IDC_EDIT7, m_ZeroResistance);
	DDX_Text(pDX, IDC_EDIT8, m_ZeroReactance);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFltItemDlg, CDialog)
	//{{AFX_MSG_MAP(CFltItemDlg)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, OnChangeEdit8)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT3, OnKillfocusEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT4, OnKillfocusEdit4)
	ON_EN_KILLFOCUS(IDC_EDIT5, OnKillfocusEdit5)
	ON_EN_KILLFOCUS(IDC_EDIT6, OnKillfocusEdit6)
	ON_EN_KILLFOCUS(IDC_EDIT7, OnKillfocusEdit7)
	ON_EN_KILLFOCUS(IDC_EDIT8, OnKillfocusEdit8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFltItemDlg message handlers

BOOL CFltItemDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_name = mFltItem.Name;
	m_FaultId = mFltItem.FaultId;
	if(mFltItem.bIpFaultEnable)
		m_IpFaultEnable.SetCurSel(0);
	else
		m_IpFaultEnable.SetCurSel(1);
	if(mFltItem.b3I0FaultEnable)
		m_3I0FaultEnable.SetCurSel(0);
	else
		m_3I0FaultEnable.SetCurSel(1);
	m_IpValue = mFltItem.IpValue;
	m_3I0Value = mFltItem.m3I0Value;
	m_PositiveResistance = mFltItem.PositiveResistance;
	m_PositiveReactance = mFltItem.PositiveReactance;
	m_ZeroResistance = mFltItem.ZeroResistance;
	m_ZeroReactance = mFltItem.ZeroReactance;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFltItemDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	mFltItem.Name = m_name;
	mFltItem.FaultId = m_FaultId;
	if (m_IpFaultEnable.GetCurSel() == 0) 
		mFltItem.bIpFaultEnable = true;
	else
		mFltItem.bIpFaultEnable = false;
	if (m_3I0FaultEnable.GetCurSel() == 0)
		mFltItem.b3I0FaultEnable = true;
	else
		mFltItem.b3I0FaultEnable = false;
	mFltItem.IpValue = m_IpValue;
	mFltItem.m3I0Value = m_3I0Value;
	mFltItem.PositiveResistance = m_PositiveResistance;
	mFltItem.PositiveReactance = m_PositiveReactance;
	mFltItem.ZeroResistance = m_ZeroResistance;
	mFltItem.ZeroReactance = m_ZeroReactance;

	CDialog::OnOK();
}

void CFltItemDlg::OnChangeEdit2() 
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

void CFltItemDlg::OnChangeEdit3() 
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

void CFltItemDlg::OnChangeEdit4() 
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

void CFltItemDlg::OnChangeEdit5() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT5);
	char str[32];
	pEdit->GetWindowText(str,32);
	int i = atoi(str);//.GetBuffer(str.GetLength()));
	if( i > 65535)
	{
		AfxMessageBox("不允许输入大于65535的值!");
		pEdit->SetWindowText("65535");	
	}
}

void CFltItemDlg::OnChangeEdit6() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT6);
	char str[32];
	pEdit->GetWindowText(str,32);
	int i = atoi(str);//.GetBuffer(str.GetLength()));
	if( i > 65535)
	{
		AfxMessageBox("不允许输入大于65535的值!");
		pEdit->SetWindowText("65535");	
	}
}

void CFltItemDlg::OnChangeEdit7() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT7);
	char str[32];
	pEdit->GetWindowText(str,32);
	int i = atoi(str);//.GetBuffer(str.GetLength()));
	if( i > 65535)
	{
		AfxMessageBox("不允许输入大于65535的值!");
		pEdit->SetWindowText("65535");	
	}
}

void CFltItemDlg::OnChangeEdit8() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT8);
	char str[32];
	pEdit->GetWindowText(str,32);
	int i = atoi(str);//.GetBuffer(str.GetLength()));
	if( i > 65535)
	{
		AfxMessageBox("不允许输入大于65535的值!");
		pEdit->SetWindowText("65535");	
	}
}

void CFltItemDlg::OnKillfocusEdit2() 
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

void CFltItemDlg::OnKillfocusEdit3() 
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

void CFltItemDlg::OnKillfocusEdit4() 
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

void CFltItemDlg::OnKillfocusEdit5() 
{
	// TODO: Add your control notification handler code here
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT5);
	char str[32];
	pEdit->GetWindowText(str,32);
	if(strlen(str) == 0)
	{
		pEdit->SetWindowText("0");
		return;
	}	
}

void CFltItemDlg::OnKillfocusEdit6() 
{
	// TODO: Add your control notification handler code here
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT6);
	char str[32];
	pEdit->GetWindowText(str,32);
	if(strlen(str) == 0)
	{
		pEdit->SetWindowText("0");
		return;
	}	
}

void CFltItemDlg::OnKillfocusEdit7() 
{
	// TODO: Add your control notification handler code here
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT7);
	char str[32];
	pEdit->GetWindowText(str,32);
	if(strlen(str) == 0)
	{
		pEdit->SetWindowText("0");
		return;
	}	
}

void CFltItemDlg::OnKillfocusEdit8() 
{
	// TODO: Add your control notification handler code here
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT8);
	char str[32];
	pEdit->GetWindowText(str,32);
	if(strlen(str) == 0)
	{
		pEdit->SetWindowText("0");
		return;
	}	
}
