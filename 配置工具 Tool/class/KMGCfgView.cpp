// KMGCfgView.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "KMGCfgView.h"
#include "stdafx.h"
#include "MyFun.h"
#include "ReadPzkIni.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CToolTipCtrl kmg_ToolTipCtr;//tooltips��ʾ

extern int KMG_Select[KMG_SWITCH_KIND][KMG_SELECT];//���Ź� ��ȡprot_select��������ݵ�����
extern int KMG_FACT_SELECT[KMG_SELECT];//ʵ�ʵ�ֵ��С

/////////////////////////////////////////////////////////////////////////////
// CKMGCfgView dialog

IMPLEMENT_DYNCREATE(CKMGCfgView, CFormView)//ͨ��DECLARE_DYNCREATE����ʹ��IMPLEMENT_DYNCREATE�꣬������CObject���������������ʱ�Զ�������class,baseclass

CKMGCfgView::CKMGCfgView()
: CFormView(CKMGCfgView::IDD)
{
	//{{AFX_DATA_INIT(CKMGCfgView)
	m_Version = _T("");
	m_Check1 = FALSE;
	m_Check2 = FALSE;
	m_Check3 = FALSE;
	m_Check4 = FALSE;
	m_Check5 = FALSE;
	m_SboNum = 0;
	m_SwitchNum = 0;
	m_Check6 = FALSE;
	bEverEdited = false;
	CMode = mPzkIni.KMGFile.Cfg.V_ConnectMode;
	m_FixActTime =  mPzkIni.KMGFile.Cfg.FixActTime;;
	//}}AFX_DATA_INIT
}


void CKMGCfgView::DoDataExchange(CDataExchange* pDX)//�Ի���������ȡ��
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKMGCfgView)
	DDX_Control(pDX, IDC_COMBO2, m_Enable);
	DDX_Control(pDX, IDC_EDIT3, m_Input);
	DDX_Control(pDX, IDC_LIST1, m_List1);
	DDX_Control(pDX, IDC_COMBO1, m_KMGType);
	DDX_Text(pDX, IDC_EDIT1, m_Version);
	DDX_Check(pDX, IDC_CHECK1, m_Check1);
	DDX_Check(pDX, IDC_CHECK2, m_Check2);
	DDX_Check(pDX, IDC_CHECK3, m_Check3);
	DDX_Check(pDX, IDC_CHECK4, m_Check4);
	DDX_Check(pDX, IDC_CHECK5, m_Check5);
	DDX_Text(pDX, IDC_EDIT4, m_SboNum);
	DDX_Text(pDX, IDC_EDIT5, m_SwitchNum);
	DDX_Check(pDX, IDC_CHECK6, m_Check6);
	DDX_Text(pDX, IDC_EDIT6, m_FixActTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKMGCfgView, CFormView)
	//{{AFX_MSG_MAP(CKMGCfgView)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_EN_KILLFOCUS(IDC_EDIT4, OnKillfocusEdit4)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	ON_EN_KILLFOCUS(IDC_EDIT5, OnKillfocusEdit5)
	ON_BN_CLICKED(IDC_BUTTON1, OnSave)
	ON_EN_KILLFOCUS(IDC_EDIT3, OnKillfocusEdit3)
	ON_CBN_KILLFOCUS(IDC_COMBO2, OnKillfocusCombo2)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_EN_KILLFOCUS(IDC_EDIT6, OnKillfocusEdit6)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit6)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)//��ϢID��ӳ��message�ĺ���
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)//���������ǰ�һ���Զ������Ϣ�͸���Ϣ����Ӧ������
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKMGCfgView message handlers
#ifdef _DEBUG
void CKMGCfgView::AssertValid() const
{
	CFormView::AssertValid();
}

void CKMGCfgView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG  AssertValid�����������жϱ��ʽ�ĺϷ��Ի���ȷ��,�������ȷ�򲻺Ϸ�����ֹ���򲢷�����Ӧ����ʾ��Ϣ ��AssertValid(t==0);//�����ж�t�Ƿ����0,���t!=0����ֹ����
//Dump����һ��������ʾdebug��Ϣ�ģ��亯���е�����һ����debugʱ����debug�����в��ܿ���



void CKMGCfgView::LoadKMGConfig()//������ʾ���ݣ��������͡����ݱ�
{
	int addItem;
	listArray[0]->DeleteAllItems();
	int type = m_KMGType.GetCurSel();//����������Ͽ������� 0Ϊ������ֵ�趨
	if(type ==0)
	{
		SwitchType=mPzkIni.KMGFileTemp.Line[type].LineCfg.Switch_Type;//��������
		if(SwitchType==0)//��·��ѡ��
		{
			((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);//����switchtype����ʾ��Ӧ��radio״̬
		}
		else if(SwitchType==1)//���ɿ���ѡ��
		{
			((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(1);
		}
		else if(SwitchType==2)//��ϵ���ѡ��
		{
			((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(1);
		}

		m_SboNum=mPzkIni.KMGFileTemp.Line[type].LineCfg.SBO_Num;//#��·SBO��
		m_SwitchNum=mPzkIni.KMGFileTemp.Line[type].LineCfg.Switch_Num;//#��·���غ�
		int index;
		for(int i=0; i<=KMG_FACT_SELECT[SwitchType]; i++)//ÿ�ֿ��������м������� ��KMG_FACT_SELECT��������0-9 1-3 2-3
		{
			index=KMG_Select[SwitchType][i];//switchtype���������� i:�ڼ�������
			addItem = listArray[0]->InsertItem(i, Str(i), 0);
			listArray[0]->SetItemData(addItem, mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Type);//?
			listArray[0]->SetItemText(addItem, 1, mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Name);
			if(mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Enable == 255)
			{
				listArray[0]->SetItemText(addItem, 2, "����");
			}
			else if(mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Enable == 1)
			{
				listArray[0]->SetItemText(addItem, 2, "�澯");
			}
			else if(mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Enable == 0)
			{
				listArray[0]->SetItemText(addItem, 2, "�˳�");
			}
			listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Value1));
			listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Time));
			listArray[0]->SetItemText(addItem, 5, mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Unit);
		}
	}
	else if(type ==1 || type ==2 || type ==3 || type ==4 || type==5 )
	{
		addItem = listArray[0]->InsertItem(0, Str(0), 0);
		listArray[0]->SetItemData(addItem, mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Line);
		if(mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Enable == 255)//KMGItem[0]?��ֻ��һ������
		{
			listArray[0]->SetItemText(addItem, 1, "Ͷ��");
		}
		else if(mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Enable == 0)
		{
			listArray[0]->SetItemText(addItem, 1, "�˳�");
		}
		listArray[0]->SetItemText(addItem, 2, Str(mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Value1));
		listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Value2));
		listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Time));
		listArray[0]->SetItemText(addItem, 5, mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Unit);
	}

	else if(type ==6 || type ==7)
	{
		addItem = listArray[0]->InsertItem(0, Str(0), 0);
		listArray[0]->SetItemData(addItem, mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Line);
		if(mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Enable == 255)
		{
			listArray[0]->SetItemText(addItem, 1, "Ͷ��");
		}
		else if(mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Enable == 0)
		{
			listArray[0]->SetItemText(addItem, 1, "�˳�");
		}
		listArray[0]->SetItemText(addItem, 2, Str(mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Value1));
	//	listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Value2));
		listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Time));
		listArray[0]->SetItemText(addItem, 4, mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Unit);

	}



  UpdateData(UPDATE_WRITE);//UpdateData(FALSE);��m_txt������ˢ�µ�����ؼ���ȥ��UpdateData(TRUE)�ǽ��ؼ���״̬����������ı�����

}

void CKMGCfgView::InitListCtrl()
{
	int i=0;
	CSize sz;
	sz.cx = sz.cy = 30;
//	listArray[0] = &m_List1;
	int type = m_KMGType.GetCurSel();

/***********��գ���������������*************/
/********http://bbs.csdn.net/topics/50390421*******/

	m_List1.DeleteAllItems();//�������listview
	int iCount,j=0;
	iCount = m_List1.GetHeaderCtrl()->GetItemCount();
	for(j = 0; j < iCount; j++)
	{
		m_List1.DeleteColumn(0);
	}
	for(j = 0; j < iCount; j++)
	{
		m_List1.GetHeaderCtrl()->DeleteItem(0);
	}

	listArray[0] = &m_List1;
	//listArray[0]->DeleteAllItems();

	if(type == 0)
	{
		listArray[0]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);//���õ�ǰ���б���ͼ�ؼ���չ����ʽ
		listArray[0]->ApproximateViewRect(sz,1);//ָ����ʾ�б���ͼ�ؼ�������Ŀ�Ⱥ͸߶�?
		listArray[0]->InsertColumn(i++, "���", LVCFMT_LEFT, 40, -1);//i++Ϊ�кţ����ݣ����У����
		listArray[0]->InsertColumn(i++, "����", LVCFMT_LEFT, 160, -1);
		listArray[0]->InsertColumn(i++, "����/�澯", LVCFMT_CENTER, 75, -1);
		listArray[0]->InsertColumn(i++, "��ֵ", LVCFMT_CENTER, 75, -1);
		listArray[0]->InsertColumn(i++, "ʱ��", LVCFMT_CENTER, 80, -1);
		listArray[0]->InsertColumn(i++, "��ֵ��λ/��ע", LVCFMT_CENTER, 141, -1);
	//	AfxMessageBox("111111111");
	}
	else if(type ==1 || type ==2 || type ==3 || type ==4 || type==5 )
	{
		listArray[0]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		listArray[0]->ApproximateViewRect(sz,1);//ApproximateViewRectָ����ʾ�б���ͼ�ؼ�������Ŀ�Ⱥ͸߶�
		listArray[0]->InsertColumn(i++, "��·��", LVCFMT_LEFT, 64, -1);
		listArray[0]->InsertColumn(i++, "Ͷ��/�˳�", LVCFMT_CENTER, 92, -1);
		listArray[0]->InsertColumn(i++, "����ֵ", LVCFMT_CENTER, 85, -1);
		listArray[0]->InsertColumn(i++, "����ֵ", LVCFMT_CENTER, 85, -1);
		listArray[0]->InsertColumn(i++, "ʱ��", LVCFMT_CENTER, 95, -1);
		listArray[0]->InsertColumn(i++, "��ֵ��λ/��ע", LVCFMT_CENTER, 151, -1);
	//	AfxMessageBox("2222222222222");
	}
	else if(type ==6 || type ==7)
	{
		listArray[0]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		listArray[0]->ApproximateViewRect(sz,1);
		listArray[0]->InsertColumn(i++, "��·��", LVCFMT_CENTER, 90, -1);
		listArray[0]->InsertColumn(i++, "Ͷ��/�˳�", LVCFMT_CENTER, 110, -1);
		listArray[0]->InsertColumn(i++, "��ֵ", LVCFMT_CENTER, 110, -1);
		listArray[0]->InsertColumn(i++, "ʱ��", LVCFMT_CENTER, 110, -1);
		listArray[0]->InsertColumn(i++, "��ֵ��λ/��ע", LVCFMT_CENTER, 152, -1);
	//	AfxMessageBox("333333333333");
	}

	CRect rect;//?
	listArray[0]->GetWindowRect(&rect);//�ú�������ָ�����ڵı߿���εĳߴ硣�óߴ����������Ļ�������Ͻǵ���Ļ���������

	rect.top -= 80;
	rect.bottom -= 80;

	LoadKMGConfig();

}

void CKMGCfgView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	//Ϊ�˷�ֹ���ֲ�һ�µ������ȷʵҲ���ֹ��ˡ�
	memcpy(&(mPzkIni.KMGFileTemp),&(mPzkIni.KMGFile),sizeof(KMGCfgStru));

	//��ʼΪ0, ��ɫ���
	GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE);

	GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);//��ѡ��������ֹ����
	GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK6)->EnableWindow(TRUE);


	kmg_ToolTipCtr.Create(this);//����ѹ���߷�ʽ�����ʾ
	kmg_ToolTipCtr.AddTool(GetDlgItem(IDC_RADIO4),_T("һ���ߵ�ѹUab���ն˵�U1a����,��һ���ߵ�ѹUcb���ն˵�U1c����"));//���
	kmg_ToolTipCtr.AddTool(GetDlgItem(IDC_RADIO5),_T("һ�������ѹ���ն˵�U1a/U1b/U1c,��һ�������ѹ���ն˵�U2a/U2b/U2c"));//���
	kmg_ToolTipCtr.AddTool(GetDlgItem(IDC_RADIO6),_T("�����ѹ���ն˵�U1a/U1b/U1c"));//���
	kmg_ToolTipCtr.SetMaxTipWidth(300);
	kmg_ToolTipCtr.Activate(TRUE);
	kmg_ToolTipCtr.SetDelayTime(TTDT_INITIAL, 0);
	kmg_ToolTipCtr.SetDelayTime(TTDT_AUTOPOP, 90000);


	m_KMGType.ResetContent();//Removes all items from a list box.
	m_KMGType.AddString("������ֵ�趨");
	m_KMGType.AddString("������·-Խ�޸澯��ֵ�趨");//�������ͣ���Ͽ��б��combo1
	m_KMGType.AddString("��ѹ��·-Խ�޸澯��ֵ�趨");
	m_KMGType.AddString("���������·-Խ�޸澯��ֵ�趨");
	m_KMGType.AddString("�����ѹ��·-Խ�޸澯��ֵ�趨");
	m_KMGType.AddString("�����ɸ澯��ֵ�趨");
	m_KMGType.AddString("����·��������");
	m_KMGType.AddString("����ӵع�������");
	m_KMGType.SetCurSel(0);//����������Ͽ���б����ѡ��һ���ַ�������Ҫʱ�б����������ʹ���ַ������б�Ŀ������� ���б��ǿɼ���ʱ �����༭�ؼ��� ���ı�����Ӧ�ر�Ϊѡ�е��ַ�������ǰ���б���е�ѡ�񽫲������ڡ���ǰѡ��Ϊ0

	m_Enable.ResetContent();//������ֵ�趨�� �����澯Ͷ����Ͽ��б��combo2
	m_Enable.AddString("����");
	m_Enable.AddString("�澯");
	m_Enable.AddString("�˳�");
	m_Enable.SetCurSel(0);

	GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);//�ú�������/��ָֹ���Ĵ��ڻ�ؼ��������ͼ��̵����룬���ò���ΪTRUE���򴰿ڱ�����
	GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);//RADIO3�أ�
	GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);//?
	GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);

	m_Version = mPzkIni.KMGFileTemp.Cfg.Version;//�汾��
//	m_PNumPerLine = mPzkIni.KMGFileTemp.Cfg.ProtNumPerLine;//ÿ����·���ٱ���

	if(mPzkIni.KMGFileTemp.Cfg.Prot_YXEnable == 255)//������ң��ʹ��
	{
		m_Check1 = true;//IDC_CHECK1��ֵ
	}
	else
	{
		m_Check1 = false;
	}
	if(mPzkIni.KMGFileTemp.Cfg.Prot_MsgEnable == 255)//������Ϣ�ϱ�ʹ��
	{
		m_Check2 = true;
	}
	else
	{
		m_Check2 = false;
	}
	if(mPzkIni.KMGFileTemp.Cfg.Byd_SOEEnable == 255)//Խ�޸澯SOEʹ��
	{
		m_Check3 = true;
	}
	else
	{
		m_Check3 = false;
	}
	if(mPzkIni.KMGFileTemp.Cfg.Flt_YXEnable == 255)//���ϼ������ϱ�ʹ��
	{
		m_Check4 = true;
	}
	else
	{
		m_Check4 = false;
	}
	if(mPzkIni.KMGFileTemp.Cfg.Flt_RepEnable == 255)//���ϱ����ϱ�ʹ��
	{
		m_Check5 = true;
	}
	else
	{
		m_Check5= false;
	}
	if(mPzkIni.KMGFileTemp.Cfg.Flt_RcwEnable == 255)//����¼��ʹ��
	{
		m_Check6 = true;
	}
	else
	{
		m_Check6= false;
	}

	//���߷�ʽ
	if(CMode==0)
		((CButton *)GetDlgItem(IDC_RADIO4))->SetCheck(1);
	else if(CMode ==1)
		((CButton *)GetDlgItem(IDC_RADIO5))->SetCheck(1);
	else if(CMode ==2)
		((CButton *)GetDlgItem(IDC_RADIO6))->SetCheck(1);

	UpdateData(UPDATE_WRITE);//ֵ���µ��ؼ�
	UpdateData(UPDATE_READ);//�ؼ���ֵ���µ�����
	InitListCtrl();//���ó�ʼ���б����

}


LRESULT CKMGCfgView::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)//?
{
//	OnCANCEl();
	return TRUE;
}

LRESULT CKMGCfgView::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)//?
{
	if(bEverEdited)//true or false
	{
		int i = AfxMessageBox("���浱ǰ�Ա����������������޸���",MB_YESNOCANCEL);
		if(i == IDYES)
			OnSave();
		else if(i == IDCANCEL)
		{
//			bCloseWindow = false;
			return FALSE;//?
		}
		else
			;//OnCancel();
	}
	return TRUE;
}

void CKMGCfgView::OnCheck1() //������ң��ʹ��
{
	bEverEdited = true;
	UpdateData(true);//���浽����
	if(m_Check1 == true)
	{
		mPzkIni.KMGFileTemp.Cfg.Prot_YXEnable=255;
	}
	else
	{
		mPzkIni.KMGFileTemp.Cfg.Prot_YXEnable=0;
	}

}

void CKMGCfgView::OnCheck2() //������Ϣ�ϱ�ʹ��
{
	bEverEdited = true;
	UpdateData(true);//���浽����
	if(m_Check2 == true)
	{
		mPzkIni.KMGFileTemp.Cfg.Prot_MsgEnable=255;
	}
	else
	{
		mPzkIni.KMGFileTemp.Cfg.Prot_MsgEnable=0;
	}
}

void CKMGCfgView::OnCheck3() //Խ�޸澯SOEʹ��
{
	bEverEdited = true;
	UpdateData(true);//���浽����
	if(m_Check3 == true)
	{
		mPzkIni.KMGFileTemp.Cfg.Byd_SOEEnable=255;
	}
	else
	{
		mPzkIni.KMGFileTemp.Cfg.Byd_SOEEnable=0;
	}

}

void CKMGCfgView::OnCheck4() //���ϼ������ϱ�ʹ��
{
	bEverEdited = true;
	UpdateData(true);//���浽����
	if(m_Check4 == true)
	{
		mPzkIni.KMGFileTemp.Cfg.Flt_YXEnable=255;
	}
	else
	{
		mPzkIni.KMGFileTemp.Cfg.Flt_YXEnable=0;
	}
}

void CKMGCfgView::OnCheck5() //���ϱ����ϱ�ʹ��
{
	bEverEdited = true;
	UpdateData(true);//���浽����
	if(m_Check5 == true)
	{
		mPzkIni.KMGFileTemp.Cfg.Flt_RepEnable=255;
	}
	else
	{
		mPzkIni.KMGFileTemp.Cfg.Flt_RepEnable=0;
	}
}

void CKMGCfgView::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString srr;
	CString CheckStr;
	bool Check;
	CString str;
	CComboBox *pCombo;
	HWND pWnd;
	Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST1);
    LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
    RECT rect;
    //get the row number
    nItem = temp->iItem;
    //get the column number
    nSubItem = temp->iSubItem;
	if(nItem < 0)
		return;
	if(nSubItem == 0)
		return;
	int type = m_KMGType.GetCurSel();//����������Ͽ������� 0Ϊ������ֵ�趨
	if(type ==0)
	{
		if(nSubItem == 2)
		{

			pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO2);
			pCombo = (CComboBox *)GetDlgItem(IDC_COMBO2);
			str = m_List1.GetItemText(nItem, nSubItem);
			if(str.Compare("����") == 0)
				pCombo->SetCurSel(0);
			else if(str.Compare("�澯") == 0)
				pCombo->SetCurSel(1);
			else if(str.Compare("�˳�") == 0)
				pCombo->SetCurSel(2);
		}
		else if(nSubItem == 3 || nSubItem == 4  )
		{
			pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT3);
			pCombo = (CComboBox *)GetDlgItem(IDC_EDIT3);
			m_Input.SetWindowText(m_List1.GetItemText(nItem, nSubItem));
		}
		else
			return;

	}
	if(type ==1 || type ==2 || type ==3 || type ==4 || type==5 )
	{
		if(nSubItem == 1)
		{

			pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO2);
			pCombo = (CComboBox *)GetDlgItem(IDC_COMBO2);
			str = m_List1.GetItemText(nItem, nSubItem);
			if(str.Compare("Ͷ��") == 0)
				pCombo->SetCurSel(0);
			else if(str.Compare("�˳�") == 0)
				pCombo->SetCurSel(1);
		}
		else if(nSubItem == 2 || nSubItem == 3 || nSubItem == 4  )
		{
			pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT3);
			pCombo = (CComboBox *)GetDlgItem(IDC_EDIT3);
			m_Input.SetWindowText(m_List1.GetItemText(nItem, nSubItem));
		}
		else
			return;
	}

	else if(type ==6 || type ==7)
	{
		if(nSubItem == 1)
		{

			pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO2);
			pCombo = (CComboBox *)GetDlgItem(IDC_COMBO2);
			str = m_List1.GetItemText(nItem, nSubItem);
			if(str.Compare("Ͷ��") == 0)
				pCombo->SetCurSel(0);
			else if(str.Compare("�˳�") == 0)
				pCombo->SetCurSel(1);
		}
		else if(nSubItem == 2 || nSubItem == 3 )
		{
			pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT3);
			pCombo = (CComboBox *)GetDlgItem(IDC_EDIT3);
			m_Input.SetWindowText(m_List1.GetItemText(nItem, nSubItem));
		}
		else
			return;
	}


//	if(nItem ==0)
	//	return;

	pCombo->SetItemHeight(-1,12);

    //Retrieve the text of the selected subItem
    //from the list

    RECT rect1,rect2;
    // this macro is used to retrieve the Rectanle
    // of the selected SubItem
    ListView_GetSubItemRect(hWnd1,temp->iItem,
        temp->iSubItem,LVIR_BOUNDS,&rect);
    //Get the Rectange of the listControl
    ::GetWindowRect(temp->hdr.hwndFrom,&rect1);
    //Get the Rectange of the Dialog
    ::GetWindowRect(m_hWnd,&rect2);

    int x=rect1.left-rect2.left;
    int y=rect1.top-rect2.top;

	::SetWindowPos(pWnd,
		HWND_TOP,rect.left+x+1,rect.top+y,
		rect.right-rect.left+4,
		rect.bottom-rect.top+3,NULL);
	::ShowWindow(pWnd,SW_SHOW);
	::SetFocus(pWnd);
	*pResult = 0;
}

void CKMGCfgView::OnSelchangeCombo1() //OnInitialUpdate���ǳ�ʼ״̬���˴�Ϊ����combo1
{
	// TODO: Add your control notification handler code here

	if(m_KMGType.GetCurSel()==0)//radio �������ͼ������ֹ
	{
		m_Enable.ResetContent();
		m_Enable.AddString("����");
		m_Enable.AddString("�澯");
		m_Enable.AddString("�˳�");
		GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO3)->EnableWindow(TRUE);
	}
	else
	{
		m_Enable.ResetContent();
		m_Enable.AddString("Ͷ��");
		m_Enable.AddString("�˳�");
		GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
	}

	int type = m_KMGType.GetCurSel();
	if(type == 0)// ���� 1 2 6  ��ѡ�򼤻����ֹ
	{
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE);

		GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(TRUE);

	}
	else if(type >=1 && type <=5 )//�澯 3
	{
		GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(FALSE);

		GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
	}
	else if( type == 6 || type == 7 )//���� 4 5
	{
		GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(FALSE);

		GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(TRUE);
	}


	InitListCtrl();//��ѡ��ѡ��ʱcomb1�������б���������ú�������������û�զ����
	LoadKMGConfig();

}

void CKMGCfgView::OnRadio1() //��������--��·�� �˴�Ϊѡ��radio����ֵ�����ú����ؼ���ʾ
{
	int type = m_KMGType.GetCurSel();
	mPzkIni.KMGFileTemp.Line[type].LineCfg.Switch_Type=0;
	SwitchType=0;
	LoadKMGConfig();
}


void CKMGCfgView::OnRadio2()//��������--���ɿ���
{
	int type = m_KMGType.GetCurSel();
	mPzkIni.KMGFileTemp.Line[type].LineCfg.Switch_Type=1;
	SwitchType=1;
	LoadKMGConfig();
}

void CKMGCfgView::OnChangeEdit4() //#��·SBO��
{
	bEverEdited = true;//�����仯
	UpdateData(true);//���浽����
	int type = m_KMGType.GetCurSel();
	mPzkIni.KMGFileTemp.Line[type].LineCfg.SBO_Num=m_SboNum;//#��·SBO��
}



void CKMGCfgView::OnKillfocusEdit4() //#��·SBO��
{
	UpdateData(UPDATE_READ);
	if(m_SboNum > 50)
	{
		AfxMessageBox("��·SBO�Ų��ܳ���"+Str(50));
		m_SboNum = 50;
		UpdateData(UPDATE_WRITE);
	}
	if(m_SboNum < 0)
	{
		AfxMessageBox("��·SBO�Ų���С��"+Str(0));
		m_SboNum = 0;
		UpdateData(UPDATE_WRITE);
	}
}

void CKMGCfgView::OnChangeEdit5() //��·���غ�
{
	bEverEdited = true;//�����仯
	UpdateData(true);//���浽����
	int type = m_KMGType.GetCurSel();
	mPzkIni.KMGFileTemp.Line[type].LineCfg.Switch_Num=m_SwitchNum;//��·���غ�

}

void CKMGCfgView::OnKillfocusEdit5() //��·���غ�
{
	UpdateData(UPDATE_READ);
	if(m_SwitchNum > 50)
	{
		AfxMessageBox("��·���غŲ��ܳ���"+Str(50));
		m_SwitchNum = 50;
		UpdateData(UPDATE_WRITE);
	}
	if(m_SwitchNum < 0)
	{
		AfxMessageBox("��·���غŲ���С��"+Str(0));
		m_SwitchNum = 0;
		UpdateData(UPDATE_WRITE);
	}
}

void CKMGCfgView::OnSave()
{
	UpdateData(true);//���浽����
	mPzkIni.KMGFile.Cfg.Version=mPzkIni.KMGFileTemp.Cfg.Version;//�汾�� ==��ʵû�仯
	//m_PNumPerLine = mPzkIni.SXJZSFileTemp.Cfg.ProtNumPerLine;//ÿ����·���ٱ��� ==û�仯
	mPzkIni.KMGFile.Cfg.Prot_YXEnable=mPzkIni.KMGFileTemp.Cfg.Prot_YXEnable;//������ң��ʹ��
	mPzkIni.KMGFile.Cfg.Prot_MsgEnable=mPzkIni.KMGFileTemp.Cfg.Prot_MsgEnable;//������Ϣ�ϱ�ʹ��
	mPzkIni.KMGFile.Cfg.Byd_SOEEnable=mPzkIni.KMGFileTemp.Cfg.Byd_SOEEnable;//Խ�޸澯SOEʹ��
	mPzkIni.KMGFile.Cfg.Flt_YXEnable=mPzkIni.KMGFileTemp.Cfg.Flt_YXEnable;//���ϼ������ϱ�ʹ��
	mPzkIni.KMGFile.Cfg.Flt_RepEnable=mPzkIni.KMGFileTemp.Cfg.Flt_RepEnable;//���ϱ����ϱ�ʹ��
	mPzkIni.KMGFile.Cfg.Flt_RcwEnable=mPzkIni.KMGFileTemp.Cfg.Flt_RcwEnable;//����¼��ʹ��

	mPzkIni.KMGFile.Cfg.FixActTime=m_FixActTime; //������������ʱ��
	mPzkIni.KMGFile.Cfg.V_ConnectMode=CMode;//���߷�ʽ

	int i;
	int j;
	for(i=0;i<8;i++)
	{
		if(i == 0 )
		{
			mPzkIni.KMGFile.Line[i].LineCfg.Switch_Type=mPzkIni.KMGFileTemp.Line[i].LineCfg.Switch_Type;//��������
			mPzkIni.KMGFile.Line[i].LineCfg.SBO_Num=mPzkIni.KMGFileTemp.Line[i].LineCfg.SBO_Num;//#��·SBO��
			mPzkIni.KMGFile.Line[i].LineCfg.Switch_Num=mPzkIni.KMGFileTemp.Line[i].LineCfg.Switch_Num;//#��·���غ�
			for(j=0;j<mPzkIni.KMGFileTemp.Cfg.ProtNumPerLine;j++)//ȫ������һ�� 0-ÿ����·������
			{
				mPzkIni.KMGFile.Line[i].KMGItem[j].Type = mPzkIni.KMGFileTemp.Line[i].KMGItem[j].Type;
				mPzkIni.KMGFile.Line[i].KMGItem[j].Name = mPzkIni.KMGFileTemp.Line[i].KMGItem[j].Name;
				mPzkIni.KMGFile.Line[i].KMGItem[j].Enable=mPzkIni.KMGFileTemp.Line[i].KMGItem[j].Enable;
				mPzkIni.KMGFile.Line[i].KMGItem[j].Value1 =mPzkIni.KMGFileTemp.Line[i].KMGItem[j].Value1;
				mPzkIni.KMGFile.Line[i].KMGItem[j].Time = mPzkIni.KMGFileTemp.Line[i].KMGItem[j].Time;
				mPzkIni.KMGFile.Line[i].KMGItem[j].Unit = mPzkIni.KMGFileTemp.Line[i].KMGItem[j].Unit;
			}
		}
		else if(i ==1 || i ==2 || i ==3 || i ==4 || i==5 )
		{
			mPzkIni.KMGFile.Line[i].KMGItem[0].Line = mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Line;
			mPzkIni.KMGFile.Line[i].KMGItem[0].Enable=mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Enable;
			mPzkIni.KMGFile.Line[i].KMGItem[0].Value1 = mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Value1;
			mPzkIni.KMGFile.Line[i].KMGItem[0].Value2 = mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Value2;
			mPzkIni.KMGFile.Line[i].KMGItem[0].Time = mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Time;
			mPzkIni.KMGFile.Line[i].KMGItem[0].Unit = mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Unit;
		}
		else if(i == 6 || i == 7)
		{
			mPzkIni.KMGFile.Line[i].KMGItem[0].Line = mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Line;
			mPzkIni.KMGFile.Line[i].KMGItem[0].Enable=mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Enable;
			mPzkIni.KMGFile.Line[i].KMGItem[0].Value1 = mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Value1;
			mPzkIni.KMGFile.Line[i].KMGItem[0].Time = mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Time;
			mPzkIni.KMGFile.Line[i].KMGItem[0].Unit = mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Unit;
		}

	}
		bEverEdited = false;
		mPzkIni.EverModified = true;
}

void CKMGCfgView::OnKillfocusEdit3()//�༭��������
{
	CString str;
	m_Input.GetWindowText(str);
	listArray[0]->SetItemText(nItem, nSubItem, str);
	int type = m_KMGType.GetCurSel();
	if(type == 0 )
	{
		int index = KMG_Select[SwitchType][nItem];//������������ĵ�ĳ�����ص��±�
		if(nSubItem == 3)
		{
			mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Value1=myatof(str);
		}
		else if(nSubItem == 4)
		{
			mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Time=myatof(str);

		}
	}
	else if(type ==1 || type ==2 || type ==3 || type ==4 || type==5 )
	{
		if(nSubItem == 2)
		{
			mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Value1=myatof(str);
		}
		else if(nSubItem == 3)
		{
			mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Value2=myatof(str);
		}
		else if(nSubItem == 4)
		{
			mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Time=myatof(str);
		}
	}
	else if(type == 6 || type == 7)
	{
		if(nSubItem == 2)
		{
			mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Value1=myatof(str);
		}
		else if(nSubItem == 3)
		{
			mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Time=myatof(str);
		}
	}

	m_Input.ShowWindow(SW_HIDE);
	bEverEdited = true;
}

void CKMGCfgView::OnKillfocusCombo2() //����/�澯/�˳� ���ѡ����Ͽ�ؼ���ʾ����ֵ
{

	int type = m_KMGType.GetCurSel();//�õ���ǰ��������
	int index = KMG_Select[SwitchType][nItem];//������������ĵ�ĳ�����ص��±�

	if(type == 0)
	{
		if(m_Enable.GetCurSel() == 0)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "����");
			mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Enable=255;
		}
		else if(m_Enable.GetCurSel() == 1)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "�澯");
			mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Enable=1;
		}
		else if(m_Enable.GetCurSel() == 2)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "�˳�");
			mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Enable=0;
		}
	}
	else
	{
		if(m_Enable.GetCurSel() == 0)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "Ͷ��");
			mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Enable=255;
		}
		else if(m_Enable.GetCurSel() == 1)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "�˳�");
			mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Enable=0;
		}

	}






	m_Enable.ShowWindow(SW_HIDE);
	bEverEdited = true;
}

void CKMGCfgView::OnButton2() //ȡ��
{
	int j;
	int i = m_KMGType.GetCurSel();//�õ���ǰ��������
	if(i == 0 )
	{
		mPzkIni.KMGFileTemp.Line[i].LineCfg.Switch_Type=mPzkIni.KMGFile.Line[i].LineCfg.Switch_Type;//��������
		mPzkIni.KMGFileTemp.Line[i].LineCfg.SBO_Num=mPzkIni.KMGFile.Line[i].LineCfg.SBO_Num;//#��·SBO��
		mPzkIni.KMGFileTemp.Line[i].LineCfg.Switch_Num=mPzkIni.KMGFile.Line[i].LineCfg.Switch_Num;//#��·���غ�
		for(j=0;j<mPzkIni.KMGFileTemp.Cfg.ProtNumPerLine;j++)//ȫ������һ�� 0-ÿ����·������
		{
			mPzkIni.KMGFileTemp.Line[i].KMGItem[j].Type = mPzkIni.KMGFile.Line[i].KMGItem[j].Type;
			mPzkIni.KMGFileTemp.Line[i].KMGItem[j].Name = mPzkIni.KMGFile.Line[i].KMGItem[j].Name;
			mPzkIni.KMGFileTemp.Line[i].KMGItem[j].Enable=mPzkIni.KMGFile.Line[i].KMGItem[j].Enable;
			mPzkIni.KMGFileTemp.Line[i].KMGItem[j].Value1 =mPzkIni.KMGFile.Line[i].KMGItem[j].Value1;
			mPzkIni.KMGFileTemp.Line[i].KMGItem[j].Time = mPzkIni.KMGFile.Line[i].KMGItem[j].Time;
			mPzkIni.KMGFileTemp.Line[i].KMGItem[j].Unit = mPzkIni.KMGFile.Line[i].KMGItem[j].Unit;
		}
	}
	else if(i ==1 || i ==2 || i ==3 || i ==4 || i==5 )
	{
		mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Line = mPzkIni.KMGFile.Line[i].KMGItem[0].Line;
		mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Enable=mPzkIni.KMGFile.Line[i].KMGItem[0].Enable;
		mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Value1 = mPzkIni.KMGFile.Line[i].KMGItem[0].Value1;
		mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Value2 = mPzkIni.KMGFile.Line[i].KMGItem[0].Value2;
		mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Time = mPzkIni.KMGFile.Line[i].KMGItem[0].Time;
		mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Unit = mPzkIni.KMGFile.Line[i].KMGItem[0].Unit;
	}
	else if(i == 6 || i == 7)
	{
		mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Line = mPzkIni.KMGFile.Line[i].KMGItem[0].Line;
		mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Enable=mPzkIni.KMGFile.Line[i].KMGItem[0].Enable;
		mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Value1 = mPzkIni.KMGFile.Line[i].KMGItem[0].Value1;
		mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Time = mPzkIni.KMGFile.Line[i].KMGItem[0].Time;
		mPzkIni.KMGFileTemp.Line[i].KMGItem[0].Unit = mPzkIni.KMGFile.Line[i].KMGItem[0].Unit;
	}
	else
		;

	LoadKMGConfig();
}

void CKMGCfgView::OnRadio3() //��������--��ϵ���
{
	// TODO: Add your control notification handler code here

	int type = m_KMGType.GetCurSel();
	mPzkIni.KMGFileTemp.Line[type].LineCfg.Switch_Type=2;
	SwitchType=2;
	LoadKMGConfig();


}

void CKMGCfgView::OnCheck6()// ����¼��ʹ��
{
	bEverEdited = true;
	UpdateData(true);//���浽����
	if(m_Check6 == true)
	{
		mPzkIni.KMGFileTemp.Cfg.Flt_RcwEnable=255;
	}
	else
	{
		mPzkIni.KMGFileTemp.Cfg.Flt_RcwEnable=0;
	}

}


BOOL CKMGCfgView::PreTranslateMessage(MSG* pMsg)//tooltip���ظ����ڵ� BOOL PreTranslateMessage(MSG* pMsg) ���ں����е��� m_tt.RelayEvent(pMsg)
{
	if(IsWindow(kmg_ToolTipCtr.m_hWnd))//ΪɶҪ���ж�
	{
		kmg_ToolTipCtr.RelayEvent(pMsg);
	}
	return CFormView::PreTranslateMessage(pMsg);

//CFormView
}

void CKMGCfgView::OnRadio4()
{
	bEverEdited = true;
	CMode=0;
}

void CKMGCfgView::OnRadio5()
{

	bEverEdited = true;
	CMode=1;
}

void CKMGCfgView::OnRadio6()
{
	bEverEdited = true;
	CMode=2;

}

void CKMGCfgView::OnKillfocusEdit6()
{
	// TODO: Add your control notification handler code here

	UpdateData(UPDATE_READ);
	if(m_FixActTime > 45)
	{
		AfxMessageBox("������ʱ�䲻�ܳ���"+Str(45)+Str("ms"));
		m_FixActTime = 45;
		UpdateData(UPDATE_WRITE);
	}
	if(m_FixActTime < 30)
	{
		AfxMessageBox("��С����ʱ�䲻��С��"+Str(30)+Str("ms"));
		m_FixActTime = 30;
		UpdateData(UPDATE_WRITE);
	}
}

void CKMGCfgView::OnChangeEdit6()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
}
