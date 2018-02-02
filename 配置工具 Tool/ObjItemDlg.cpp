// ObjItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "ObjItemDlg.h"
#include "ReadPzkIni.h"
#include "MyFun.h"
#include "FaultCfgView.h"
#include "resource.h"
#include "ObjItemDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int LineNo;
extern CString lineNo_str;
extern bool flt_3I0;
extern bool flt1_Current;
extern bool flt2_Current;
extern bool byd_ZeroU;
extern bool byd_ZeroI;
extern bool byd_Voltage;
extern bool byd_Current;
/////////////////////////////////////////////////////////////////////////////
// CObjItemDlg dialog


CObjItemDlg::CObjItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CObjItemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CObjItemDlg)
	m_xianluhao = 0;
	//}}AFX_DATA_INIT
}


void CObjItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjItemDlg)
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_xianluhao);
	DDV_MinMaxInt(pDX, m_xianluhao, 0, 64);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CObjItemDlg, CDialog)
	//{{AFX_MSG_MAP(CObjItemDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjItemDlg message handlers

int CObjItemDlg::CheckNum(CString str)
{
	int NumFlag=0;//0 is ok
	bool FloatFlag=false;
	for(int i=0;i<str.GetLength();i++)
	{
		if((int)(str.GetAt(i))>=48 && (int)(str.GetAt(i))<=57)
			continue;
		else if(str.GetAt(i)=='.')
		{
			if(FloatFlag == false)
			{
				FloatFlag = true;
				continue;
			}
			else
			{
				NumFlag = 1;//����1��С����
				break;
			}
		}
		else
		{
			NumFlag = 2;//��������
			break;
		}
	}

	return NumFlag;
}

bool CObjItemDlg::Check(CString str)
{
	int flag=CheckNum(str);
	if(flag == 1)
	{
		AfxMessageBox("��������ȷ�����ݸ�ʽ!");
		return false;
	}
	else if(flag == 2)
	{
		AfxMessageBox("��������ȷ������!");
		return false;
	}
	else
		return true;

}



void CObjItemDlg::OnOK()
{
	// TODO: Add extra validation here
	CString str1,str2,str3,str4,str6,comb_str;
	//GetDlgItem(IDC_EDIT1)->GetWindowText(str1);
	int index=mPzkIni.ProtFile.Line[LineNo].LineCfg.LineNum;//������=��·����-1
	mPzkIni.ProtFile.Line[LineNo].ProtItem[index].Type=index;//��ŵ�����·����-1

	str1.Format("%d",index);
	mPzkIni.ProtFile.Line[LineNo].ProtItem[index].Name=str1;//��·��

	if((lineNo_str.Compare("����·I�ι�������"))==0 ||(lineNo_str.Compare("����ӵع�������"))==0)
	{
		GetDlgItem(IDC_EDIT4)->GetWindowText(str4);
		if(str4.IsEmpty())
		{
			AfxMessageBox("��ֵ����Ϊ��!");
			return ;
		}
		if(Check(str4) == false)
			return ;
		mPzkIni.ProtFile.Line[LineNo].ProtItem[index].Value1=atof(str4);//��ֵ

		GetDlgItem(IDC_EDIT5)->GetWindowText(str3);
		if(str3.IsEmpty())
		{
			AfxMessageBox("ʱ�䲻��Ϊ��!");
			return ;
		}
		if(Check(str3) == false)
			return ;
		mPzkIni.ProtFile.Line[LineNo].ProtItem[index].Time=atoi(str3);//ʱ��

		GetDlgItem(IDC_EDIT6)->GetWindowText(str6);
		if(str6.IsEmpty())
		{
			AfxMessageBox("��ֵ��λ����Ϊ��!");
			return ;
		}
		mPzkIni.ProtFile.Line[LineNo].ProtItem[index].Unit=str6;//��ֵ��λ
	}

	else
	{
		GetDlgItem(IDC_EDIT4)->GetWindowText(str4);
		if(str4.IsEmpty())
		{
			AfxMessageBox("����ֵ����Ϊ��!");
			return ;
		}
		if(Check(str4) == false)
			return ;
		mPzkIni.ProtFile.Line[LineNo].ProtItem[index].Value1=atof(str4);//����ֵ

		GetDlgItem(IDC_EDIT5)->GetWindowText(str3);
		if(str3.IsEmpty())
		{
			AfxMessageBox("����ֵ����Ϊ��!");
			return ;
		}
		if(Check(str3) == false)
			return ;
		mPzkIni.ProtFile.Line[LineNo].ProtItem[index].Value2=atof(str3);//����ֵ

		GetDlgItem(IDC_EDIT6)->GetWindowText(str6);
		if(str6.IsEmpty())
		{
			AfxMessageBox("ʱ�䲻��Ϊ��!");
			return ;
		}
		if(Check(str6) == false)
			return ;
		mPzkIni.ProtFile.Line[LineNo].ProtItem[index].Time=atof(str6);//ʱ��

		GetDlgItem(IDC_EDIT2)->GetWindowText(str2);
		if(str2.IsEmpty())
		{
			AfxMessageBox("��ֵ��λ����Ϊ��!");
			return ;
		}
		mPzkIni.ProtFile.Line[LineNo].ProtItem[index].Unit=str2;//��ֵ��λ
	}

	m_combo.GetLBText(m_combo.GetCurSel(),comb_str);
	if(comb_str.Compare("Ͷ��")==0)
		mPzkIni.ProtFile.Line[LineNo].ProtItem[index].Enable=255;
	else
		mPzkIni.ProtFile.Line[LineNo].ProtItem[index].Enable=0;


	CDialog::OnOK();
}

BOOL CObjItemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_combo.ResetContent();
	m_combo.AddString("Ͷ��");
	m_combo.AddString("�˳�");
	m_combo.SetCurSel(1);

//	GetDlgItem(IDC_EDIT4)->ShowWindow(FALSE); //IDC_EDIT1Ϊ�༭��ID��

	if((lineNo_str.Compare("����·I�ι�������"))==0 ||(lineNo_str.Compare("����ӵع�������"))==0)
	{
		GetDlgItem(IDC_STATIC22)->SetWindowText(" ��ֵ:");
		GetDlgItem(IDC_STATIC33)->SetWindowText(" ʱ��:");
		GetDlgItem(IDC_STATIC44)->SetWindowText(" ��ֵ��λ:");

		GetDlgItem(IDC_STATIC55)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT2)->ShowWindow(FALSE); //IDC_EDIT1Ϊ�༭��ID��
		UpdateData(false);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
