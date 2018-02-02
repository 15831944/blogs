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

	if(CMode == 1)//标准文件
	{
		if(m_GongCheng.GetCurSel()==0)//PZK-56B标准文件
		{
			if(m_FileType.GetCurSel()==0)
			{
				*fileType = PROTECT_FILE;	//保护文件
			}
			else if(m_FileType.GetCurSel()==1)
			{
				*fileType = FAULT_FILE;	//故障文件
			}
		}
		else if(m_GongCheng.GetCurSel()==1)//DTS-500标准文件
		{
			if(m_FileType.GetCurSel()==0)
			{
				*fileType = PROTECT_FILE;	//保护文件
			}
			else if(m_FileType.GetCurSel()==1)
			{
				*fileType = FAULT_FILE;	//故障文件
			}
			
		}
		else if(m_GongCheng.GetCurSel()==2)//PZK-56K标准文件
		{
			if(m_FileType.GetCurSel()==0)
			{
				*fileType = PROTECT_FILE;	//保护文件
			}
			else if(m_FileType.GetCurSel()==1)
			{
				*fileType = FAULT_FILE;	//故障文件
			}
			
		}
		
		else if(m_GongCheng.GetCurSel()==3)//看门狗标准文件
		{
			if(m_FileType.GetCurSel()==0)
			{
				*fileType = KMG_FILE;	//看门狗文件
			}
		}
	}
	
	else if(CMode == 2)//工程文件
	{
		if(m_GongCheng.GetCurSel()==0)//绍兴集中式工程文件
		{
			if(m_FileType.GetCurSel()==0)
			{
				*fileType = SXJZS_FILE;
			}
		}
		else if(m_GongCheng.GetCurSel()==1)//绍兴液晶配置文件
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
	if(CMode ==1)//标准文件
	{
		if(m_GongCheng.GetCurSel()==0)//PZK-56B标准文件
		{
			GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);//
			m_FileType.ResetContent();
			m_FileType.AddString("保护配置文件");
			m_FileType.AddString("故障配置文件");
			m_FileType.SetCurSel(0);
		}
		else if(m_GongCheng.GetCurSel()==1)//DTS-500标准文件
		{
			GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);//
			m_FileType.ResetContent();
			m_FileType.AddString("保护配置文件");
			m_FileType.AddString("故障配置文件");
			m_FileType.SetCurSel(0);
		}
		else if(m_GongCheng.GetCurSel()==2)//PZK-56K标准文件
		{
			GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);//
			m_FileType.ResetContent();
			m_FileType.AddString("保护配置文件");
			m_FileType.AddString("故障配置文件");
			m_FileType.SetCurSel(0);
		}
		else if(m_GongCheng.GetCurSel()==3)//看门狗标准文件
		{
			GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);//
			m_FileType.ResetContent();
			m_FileType.AddString("保护故障配置文件");
			m_FileType.SetCurSel(0);

		}
	}
	if(CMode ==2)//工程
	{
		if(m_GongCheng.GetCurSel()==0)//绍兴PZK-56K集中式保护
		{
			GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);//
			m_FileType.ResetContent();
			m_FileType.AddString("绍兴PLC集中式保护文件");
			m_FileType.SetCurSel(0);
		}
		else if(m_GongCheng.GetCurSel()==1)//绍兴液晶显示
		{
			GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);//
			m_FileType.ResetContent();
			m_FileType.AddString("绍兴液晶配置文件");
			m_FileType.SetCurSel(0);

		}
	
	}

}

void CChooseFileDlg::OnRadio1() //标准文件
{
	// TODO: Add your control notification handler code here
	((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(0);//2 变灰 
	CMode = 1;
	
	GetDlgItem(IDC_COMBO2)->EnableWindow(TRUE);//
	m_GongCheng.ResetContent();
	m_GongCheng.AddString("PZK-56B标准版本");
	m_GongCheng.AddString("DTS-500标准版本");
	m_GongCheng.AddString("PZK-56K标准版本");
	m_GongCheng.AddString("PZK-560F/L标准版本");
	m_GongCheng.SetCurSel(0);
	
	GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);//
	m_FileType.ResetContent();
	m_FileType.AddString("保护配置文件");
	m_FileType.AddString("故障配置文件");
	m_FileType.SetCurSel(0);

}

void CChooseFileDlg::OnRadio2() //工程文件
{
	// TODO: Add your control notification handler code here
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(0);//2 变灰
	CMode = 2;
	
	GetDlgItem(IDC_COMBO2)->EnableWindow(TRUE);//
	m_GongCheng.ResetContent();
	m_GongCheng.AddString("绍兴PZK-56K集中式保护");
	m_GongCheng.AddString("绍兴PZK-56K液晶显示");
	m_GongCheng.SetCurSel(0);

	GetDlgItem(IDC_COMBO1)->EnableWindow(TRUE);//
	m_FileType.ResetContent();
	m_FileType.AddString("绍兴PLC集中式保护文件");
	m_FileType.SetCurSel(0);
}
