// ChooseFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "IniStru.h"
#include "ChooseFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChooseFileDlg dialog


CChooseFileDlg::CChooseFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChooseFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseFileDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CChooseFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseFileDlg)
	DDX_Control(pDX, IDC_COMBO2, m_GongCheng);
	DDX_Control(pDX, IDC_COMBO1, m_FileType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseFileDlg, CDialog)
	//{{AFX_MSG_MAP(CChooseFileDlg)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseFileDlg message handlers

void CChooseFileDlg::OnOK() 
{
	// TODO: Add extra validation here
/*
	CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_COMBO1);
	switch(pCombo->GetCurSel())
	{
	case 0:
		*fileType = PROTECT_FILE;
		break;
	case 1:
		*fileType = FAULT_FILE;
		break;
	case 2:
		*fileType = SXJZS_FILE;
		break;
	case 3:
		*fileType = SXPLC_FILE;
		break;
	case 4:
		*fileType = ZJPLC_FILE;
		break;
	case 5:
		*fileType = JZSLG_FILE;
		break;
	case 6:
		*fileType = MLPLC_FILE;
		break;
	default:
		break;
	}
*/

	if(CMode == 1)//��׼�ļ�
	{
		if(m_GongCheng.GetCurSel()==0)//PZK-56B��׼�ļ�
		{
			if(m_FileType.GetCurSel()==0)
			{
				*fileType = PROTECT_FILE;	//�����ļ�
			}
			else if(m_FileType.GetCurSel()==1)
			{
				*fileType = FAULT_FILE;	//�����ļ�
			}
		}
		else if(m_GongCheng.GetCurSel()==1)//DTS-500��׼�ļ�
		{
			if(m_FileType.GetCurSel()==0)
			{
				*fileType = PROTECT_FILE;	//�����ļ�
			}
			else if(m_FileType.GetCurSel()==1)
			{
				*fileType = FAULT_FILE;	//�����ļ�
			}
			
		}
		else if(m_GongCheng.GetCurSel()==2)//PZK-56K��׼�ļ�
		{
			if(m_FileType.GetCurSel()==0)
			{
				*fileType = PROTECT_FILE;	//�����ļ�
			}
			else if(m_FileType.GetCurSel()==1)
			{
				*fileType = FAULT_FILE;	//�����ļ�
			}
			
		}
		
		else if(m_GongCheng.GetCurSel()==3)//���Ź���׼�ļ�
		{
			if(m_FileType.GetCurSel()==0)
			{
				*fileType = KMG_FILE;	//���Ź��ļ�
			}
		}
	}
	
	else if(CMode == 2)//�����ļ�
	{
		if(m_GongCheng.GetCurSel()==0)//���˼���ʽ�����ļ�
		{
			if(m_FileType.GetCurSel()==0)
			{
				*fileType = SXJZS_FILE;
			}
		}
		else if(m_GongCheng.GetCurSel()==1)//����Һ�������ļ�
		{
			if(m_FileType.GetCurSel()==0)
			{
				*fileType = SXYJ_FILE;
			}
		}
	}

	CDialog::OnOK();
}

BOOL CChooseFileDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	GetDlgItem(IDC_COMBO1)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO2)->EnableWindow(FALSE);

	m_FileType.SetCurSel(0);
	m_GongCheng.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CChooseFileDlg::DoModal(int *FileType)
{
	fileType = FileType;
	return CDialog::DoModal();
}

int CChooseFileDlg::DoModal() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DoModal();
}

void CChooseFileDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CChooseFileDlg::OnSelchangeCombo2() 
{
	// TODO: Add your control notification handler code here
	if(CMode ==1)//��׼�ļ�
	{
		if(m_GongCheng.GetCurSel()==0)//PZK-56B��׼�ļ�
		{
			GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);//
			m_FileType.ResetContent();
			m_FileType.AddString("���������ļ�");
			m_FileType.AddString("���������ļ�");
			m_FileType.SetCurSel(0);
		}
		else if(m_GongCheng.GetCurSel()==1)//DTS-500��׼�ļ�
		{
			GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);//
			m_FileType.ResetContent();
			m_FileType.AddString("���������ļ�");
			m_FileType.AddString("���������ļ�");
			m_FileType.SetCurSel(0);
		}
		else if(m_GongCheng.GetCurSel()==2)//PZK-56K��׼�ļ�
		{
			GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);//
			m_FileType.ResetContent();
			m_FileType.AddString("���������ļ�");
			m_FileType.AddString("���������ļ�");
			m_FileType.SetCurSel(0);
		}
		else if(m_GongCheng.GetCurSel()==3)//���Ź���׼�ļ�
		{
			GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);//
			m_FileType.ResetContent();
			m_FileType.AddString("�������������ļ�");
			m_FileType.SetCurSel(0);

		}
	}
	if(CMode ==2)//����
	{
		if(m_GongCheng.GetCurSel()==0)//����PZK-56K����ʽ����
		{
			GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);//
			m_FileType.ResetContent();
			m_FileType.AddString("����PLC����ʽ�����ļ�");
			m_FileType.SetCurSel(0);
		}
		else if(m_GongCheng.GetCurSel()==1)//����Һ����ʾ
		{
			GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);//
			m_FileType.ResetContent();
			m_FileType.AddString("����Һ�������ļ�");
			m_FileType.SetCurSel(0);

		}
	
	}

}

void CChooseFileDlg::OnRadio1() //��׼�ļ�
{
	// TODO: Add your control notification handler code here
	((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(0);//2 ��� 
	CMode = 1;
	
	GetDlgItem(IDC_COMBO2)->EnableWindow(TRUE);//
	m_GongCheng.ResetContent();
	m_GongCheng.AddString("PZK-56B��׼�汾");
	m_GongCheng.AddString("DTS-500��׼�汾");
	m_GongCheng.AddString("PZK-56K��׼�汾");
	m_GongCheng.AddString("PZK-560F/L��׼�汾");
	m_GongCheng.SetCurSel(0);
	
	GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);//
	m_FileType.ResetContent();
	m_FileType.AddString("���������ļ�");
	m_FileType.AddString("���������ļ�");
	m_FileType.SetCurSel(0);

}

void CChooseFileDlg::OnRadio2() //�����ļ�
{
	// TODO: Add your control notification handler code here
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(0);//2 ���
	CMode = 2;
	
	GetDlgItem(IDC_COMBO2)->EnableWindow(TRUE);//
	m_GongCheng.ResetContent();
	m_GongCheng.AddString("����PZK-56K����ʽ����");
	m_GongCheng.AddString("����PZK-56KҺ����ʾ");
	m_GongCheng.SetCurSel(0);

	GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);//
	m_FileType.ResetContent();
	m_FileType.AddString("����PLC����ʽ�����ļ�");
	m_FileType.SetCurSel(0);
}
