// Prop3.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "Prop3.h"
#include "afxdialogex.h"


// CProp3 对话框

IMPLEMENT_DYNAMIC(CProp3, CPropertyPage)

CProp3::CProp3()
	: CPropertyPage(CProp3::IDD)
	, m_srtSalary(_T(""))
{

}

CProp3::~CProp3()
{
}

void CProp3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProp3, CPropertyPage)
END_MESSAGE_MAP()


// CProp3 消息处理程序


BOOL CProp3::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	CPropertySheet *pSheet = (CPropertySheet *)GetParent();
	pSheet->SetWizardButtons(PSWIZB_FINISH | PSWIZB_BACK);

	return CPropertyPage::OnSetActive();
}


BOOL CProp3::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CComboBox *pCombobox = (CComboBox *)GetDlgItem(IDC_COMBO3);
	pCombobox->AddString("1000元以下");
	pCombobox->AddString("1000~2000元");
	pCombobox->AddString("2000~3000元");
	pCombobox->AddString("3000元以上");
	pCombobox->SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CProp3::OnWizardFinish()
{
	// TODO: 在此添加专用代码和/或调用基类
	int index;
	CComboBox *pCombobox = (CComboBox *)GetDlgItem(IDC_COMBO3);
	index = pCombobox->GetCurSel();
	pCombobox->GetLBText(index, m_srtSalary);
	return CPropertyPage::OnWizardFinish();
}
