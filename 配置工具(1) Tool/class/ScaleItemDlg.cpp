// ScaleItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "ScaleItemDlg.h"
#include "MyFun.h"
#include "IniStru.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

ScaleStru_ mScaleItem;
/////////////////////////////////////////////////////////////////////////////
// CScaleItemDlg dialog

CScaleItemDlg::CScaleItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScaleItemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScaleItemDlg)
	m_name = _T("");
	m_HWMaxVal = 0;
	m_HWMinVal = 0;
	m_UserMaxVal = 0;
	m_UserMinVal = 0;
	//}}AFX_DATA_INIT
}


void CScaleItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScaleItemDlg)
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_HWMaxVal);
	DDX_Text(pDX, IDC_EDIT3, m_HWMinVal);
	DDX_Text(pDX, IDC_EDIT4, m_UserMaxVal);
	DDX_Text(pDX, IDC_EDIT5, m_UserMinVal);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScaleItemDlg, CDialog)
	//{{AFX_MSG_MAP(CScaleItemDlg)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT3, OnKillfocusEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT4, OnKillfocusEdit4)
	ON_EN_KILLFOCUS(IDC_EDIT5, OnKillfocusEdit5)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScaleItemDlg message handlers

BOOL CScaleItemDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_name = mScaleItem.name;
	m_HWMaxVal = mScaleItem.HWMaxVal;
	m_HWMinVal = mScaleItem.HWMinVal;
	m_UserMaxVal = mScaleItem.UserMaxVal;
	m_UserMinVal = mScaleItem.UserMinVal;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CScaleItemDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	mScaleItem.name = m_name;
	mScaleItem.HWMaxVal = m_HWMaxVal;
	mScaleItem.HWMinVal = m_HWMinVal;
	mScaleItem.UserMaxVal = m_UserMaxVal;
	mScaleItem.UserMinVal = m_UserMinVal;

	CDialog::OnOK();
}

void CScaleItemDlg::OnKillfocusEdit2() 
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

void CScaleItemDlg::OnKillfocusEdit3() 
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

void CScaleItemDlg::OnKillfocusEdit4() 
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

void CScaleItemDlg::OnKillfocusEdit5() 
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

void CScaleItemDlg::OnChangeEdit2() 
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
	if( i > 65536)
	{
		AfxMessageBox("不允许输入大于65536的值!");
		pEdit->SetWindowText("65536");		
	}	
}

void CScaleItemDlg::OnChangeEdit3() 
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
	if( i > 65536)
	{
		AfxMessageBox("不允许输入大于65536的值!");
		pEdit->SetWindowText("65536");
	}	
}

void CScaleItemDlg::OnChangeEdit4() 
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
	if( i > 65536)
	{
		AfxMessageBox("不允许输入大于65536的值!");
		pEdit->SetWindowText("65536");
	}	
}

void CScaleItemDlg::OnChangeEdit5() 
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
	if( i > 65536)
	{
		AfxMessageBox("不允许输入大于65536的值!");
		pEdit->SetWindowText("65536");
	}
}
