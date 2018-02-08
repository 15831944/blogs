// Prop2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test.h"
#include "Prop2.h"
#include "afxdialogex.h"


// CProp2 �Ի���

IMPLEMENT_DYNAMIC(CProp2, CPropertyPage)

CProp2::CProp2()
	: CPropertyPage(CProp2::IDD)
{
	// �Ը�ѡ���Ա������ʼ��Ϊ��
	m_football   = false;
	m_basketball = false;
	m_volleyball = false;
	m_swim       = false;
}

CProp2::~CProp2()
{
}

void CProp2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_football);
	DDX_Check(pDX, IDC_CHECK2, m_basketball);
	DDX_Check(pDX, IDC_CHECK3, m_volleyball);
	DDX_Check(pDX, IDC_CHECK4, m_swim);
}


BEGIN_MESSAGE_MAP(CProp2, CPropertyPage)
END_MESSAGE_MAP()


// CProp2 ��Ϣ�������


BOOL CProp2::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	CPropertySheet *pSheet = (CPropertySheet *)GetParent();
	pSheet->SetWizardButtons(PSWIZB_NEXT | PSWIZB_BACK);

	return CPropertyPage::OnSetActive();
}


LRESULT CProp2::OnWizardNext()
{
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData();
	if (m_football || m_basketball || m_volleyball || m_swim)
	{
		return CPropertyPage::OnWizardNext();
	}
	else
	{
		MessageBox("��ѡ�������Ȥ����!");
		return -1;
	}
}
