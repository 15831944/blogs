// Prop3.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test.h"
#include "Prop3.h"
#include "afxdialogex.h"


// CProp3 �Ի���

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


// CProp3 ��Ϣ�������


BOOL CProp3::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	CPropertySheet *pSheet = (CPropertySheet *)GetParent();
	pSheet->SetWizardButtons(PSWIZB_FINISH | PSWIZB_BACK);

	return CPropertyPage::OnSetActive();
}


BOOL CProp3::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CComboBox *pCombobox = (CComboBox *)GetDlgItem(IDC_COMBO3);
	pCombobox->AddString("1000Ԫ����");
	pCombobox->AddString("1000~2000Ԫ");
	pCombobox->AddString("2000~3000Ԫ");
	pCombobox->AddString("3000Ԫ����");
	pCombobox->SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


BOOL CProp3::OnWizardFinish()
{
	// TODO: �ڴ����ר�ô����/����û���
	int index;
	CComboBox *pCombobox = (CComboBox *)GetDlgItem(IDC_COMBO3);
	index = pCombobox->GetCurSel();
	pCombobox->GetLBText(index, m_srtSalary);
	return CPropertyPage::OnWizardFinish();
}
