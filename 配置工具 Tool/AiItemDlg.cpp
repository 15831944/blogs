// AiItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "AiItemDlg.h"
#include "IniStru.h"
#include "myfun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

AiInputStru_ mAiItem;
/////////////////////////////////////////////////////////////////////////////
// CAiItemDlg dialog

CAiItemDlg::CAiItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAiItemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAiItemDlg)
	m_name = _T("");
	m_LineNum = 0;
	m_MaxValue = 0;
	m_MinValue = 0;
	m_rating = 0.0f;
	m_RelateLine = 0;
	//}}AFX_DATA_INIT
}


void CAiItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAiItemDlg)
	DDX_Control(pDX, IDC_COMBO2, m_type);
	DDX_Control(pDX, IDC_COMBO1, m_valid);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_LineNum);
	DDX_Text(pDX, IDC_EDIT5, m_MaxValue);
	DDX_Text(pDX, IDC_EDIT6, m_MinValue);
	DDX_Text(pDX, IDC_EDIT4, m_rating);
	DDX_Text(pDX, IDC_EDIT7, m_RelateLine);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAiItemDlg, CDialog)
	//{{AFX_MSG_MAP(CAiItemDlg)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeEdit7)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT5, OnKillfocusEdit5)
	ON_EN_KILLFOCUS(IDC_EDIT6, OnKillfocusEdit6)
	ON_EN_KILLFOCUS(IDC_EDIT4, OnKillfocusEdit4)
	ON_EN_KILLFOCUS(IDC_EDIT7, OnKillfocusEdit7)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAiItemDlg message handlers

BOOL CAiItemDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	mNumberEdit.SubclassDlgItem(IDC_EDIT4,this);

	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT1);

	m_name = mAiItem.name;
	if(mAiItem.valid)
		m_valid.SetCurSel(0);
	else
		m_valid.SetCurSel(1);
	m_LineNum = mAiItem.LineNum;
	if(mAiItem.type<1 || mAiItem.type > 3)
		return FALSE;
	m_type.SetCurSel(mAiItem.type-1);
	m_rating = mAiItem.rating;
	m_MaxValue = mAiItem.MaxValue;
	m_MinValue = mAiItem.MinValue;
	m_RelateLine = mAiItem.RelateLine;

	UpdateData(FALSE);
	pEdit->SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAiItemDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	mAiItem.name = m_name;
	if(m_valid.GetCurSel() == 0)
		mAiItem.valid = true;
	else
		mAiItem.valid = false;
	mAiItem.LineNum = m_LineNum;
	mAiItem.type = m_type.GetCurSel()+1;
	mAiItem.rating = m_rating;
	mAiItem.MaxValue = m_MaxValue;
	mAiItem.MinValue = m_MinValue;
	mAiItem.RelateLine = m_RelateLine;

	CDialog::OnOK();
}

void CAiItemDlg::OnChangeEdit2() 
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
	if( i > 0xffffff)
	{
		i = 0xffffff;
		pEdit->SetWindowText(Str(i));
		AfxMessageBox("不允许输入大于16777215的值!");
	}
}

void CAiItemDlg::OnChangeEdit4() 
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
	if( i > 0xffffff)
	{
		i = 0xffffff;
		pEdit->SetWindowText(Str(i));
		AfxMessageBox("不允许输入大于16777215的值!");
	}	
}

void CAiItemDlg::OnChangeEdit5() 
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
	if( i > 0xffffff)
	{
		i = 0xffffff;
		pEdit->SetWindowText(Str(i));
		AfxMessageBox("不允许输入大于16777215的值!");
	}	
}

void CAiItemDlg::OnChangeEdit6() 
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
	if( i > 0xffffff)
	{
		i = 0xffffff;
		pEdit->SetWindowText(Str(i));
		AfxMessageBox("不允许输入大于16777215的值!");
	}	
}

void CAiItemDlg::OnChangeEdit7() 
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
	if( i > 0xffffff)
	{
		i = 0xffffff;
		pEdit->SetWindowText(Str(i));
		AfxMessageBox("不允许输入大于16777215的值!");
	}	
}

void CAiItemDlg::OnKillfocusEdit2() 
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

void CAiItemDlg::OnKillfocusEdit5() 
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

void CAiItemDlg::OnKillfocusEdit6() 
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

void CAiItemDlg::OnKillfocusEdit4() 
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

void CAiItemDlg::OnKillfocusEdit7() 
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
