// SxJzsCfgView.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "SxJzsCfgView.h"
#include "ReadPzkIni.h"
#include "MyFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFont   font;
CToolTipCtrl m_ToolTipCtrl123;

int LINE_AGO;

int CHZ_flag=0;
/////////////////////////////////////////////////////////////////////////////
// CSxJzsCfgView
extern SXJZS_FACT_LINE;
extern int SXJZS_Select[SWITCH_KIND][SELECT];//���˼���ʽ ��ȡprot_select��������ݵ�����
extern int SXJZS_FACT_SELECT[SELECT];//ʵ�ʵ�ֵ��С
IMPLEMENT_DYNCREATE(CSxJzsCfgView, CFormView)

CSxJzsCfgView::CSxJzsCfgView()
	: CFormView(CSxJzsCfgView::IDD)
{
	//{{AFX_DATA_INIT(CSxJzsCfgView)
	m_SboNum = 0;
	m_Version = _T("");
	m_LineNum = 0;
	m_PNumPerLine = 0;
	m_Check5 = FALSE;
	m_Check6 = FALSE;
	m_SwitchNum = 0;
	m_Check1 = FALSE;
	m_Check2 = FALSE;
	m_Check3 = FALSE;
	m_Check4 = FALSE;
	m_Check7 = FALSE;
	m_FixActTime = 0;
	m_ZXCHZTime = 0;
	m_FZXCHZTime = 0;
	m_strEdit = _T("");
	m_LeftDTUNum = 0;
	//}}AFX_DATA_INIT
	bEverEdited = false;
}

CSxJzsCfgView::~CSxJzsCfgView()
{
}

void CSxJzsCfgView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSxJzsCfgView)
	DDX_Control(pDX, IDC_COMBO2, m_LineType);
	DDX_Control(pDX, IDC_COMBO3, m_LineNo);
	DDX_Control(pDX, IDC_COMBO5, m_Enable);
	DDX_Control(pDX, IDC_EDIT3, m_Input);
	DDX_Control(pDX, IDC_LIST1, m_List1);
	DDX_Text(pDX, IDC_EDIT1, m_SboNum);
	DDX_Text(pDX, IDC_EDIT4, m_Version);
	DDX_Text(pDX, IDC_EDIT5, m_LineNum);
	DDX_Text(pDX, IDC_EDIT7, m_PNumPerLine);
	DDX_Check(pDX, IDC_CHECK5, m_Check5);
	DDX_Check(pDX, IDC_CHECK6, m_Check6);
	DDX_Text(pDX, IDC_EDIT2, m_SwitchNum);
	DDX_Check(pDX, IDC_CHECK1, m_Check1);
	DDX_Check(pDX, IDC_CHECK2, m_Check2);
	DDX_Check(pDX, IDC_CHECK3, m_Check3);
	DDX_Check(pDX, IDC_CHECK4, m_Check4);
	DDX_Check(pDX, IDC_CHECK7, m_Check7);
	DDX_Text(pDX, IDC_EDIT6, m_FixActTime);
	DDX_Text(pDX, IDC_EDIT8, m_ZXCHZTime);
	DDX_Text(pDX, IDC_EDIT9, m_FZXCHZTime);
	DDX_Text(pDX, IDC_EDIT11, m_strEdit);
	DDX_Text(pDX, IDC_EDIT13, m_LeftDTUNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSxJzsCfgView, CFormView)
	//{{AFX_MSG_MAP(CSxJzsCfgView)
	ON_BN_CLICKED(IDC_BUTTON1, OnSave)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_CBN_SELCHANGE(IDC_COMBO3, OnSelchangeCombo3)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnKillfocusEdit2)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	ON_EN_KILLFOCUS(IDC_EDIT5, OnKillfocusEdit5)
	ON_CBN_KILLFOCUS(IDC_COMBO5, OnKillfocusCombo5)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_CBN_KILLFOCUS(IDC_COMBO2, OnKillfocusCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO4, OnSelchangeCombo4)
	ON_EN_KILLFOCUS(IDC_EDIT3, OnKillfocusEdit3)
	ON_BN_CLICKED(IDC_BUTTON2, OnCANCEl)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit6)
	ON_EN_KILLFOCUS(IDC_EDIT6, OnKillfocusEdit6)
	ON_NOTIFY(NM_KILLFOCUS, IDC_LIST1, OnKillfocusList1)
	ON_EN_CHANGE(IDC_EDIT8, OnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT9, OnChangeEdit9)
	ON_EN_KILLFOCUS(IDC_EDIT8, OnKillfocusEdit8)
	ON_EN_KILLFOCUS(IDC_EDIT9, OnKillfocusEdit9)
	ON_CBN_SELCHANGE(IDC_COMBO5, OnSelchangeCombo5)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_EN_CHANGE(IDC_EDIT11, OnChangeEdit11)
	ON_CBN_KILLFOCUS(IDC_COMBO3, OnKillfocusCombo3)
	ON_CBN_SETFOCUS(IDC_COMBO3, OnSetfocusCombo3)
	ON_EN_CHANGE(IDC_EDIT13, OnChangeEdit13)
	ON_EN_KILLFOCUS(IDC_EDIT13, OnKillfocusEdit13)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_EN_KILLFOCUS(IDC_EDIT11, OnKillfocusEdit11)
	//}}AFX_MSG_MAP

	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSxJzsCfgView diagnostics

#ifdef _DEBUG
void CSxJzsCfgView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSxJzsCfgView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSxJzsCfgView message handlers
void CSxJzsCfgView::InitListCtrl()
{
	int i=0;
	CSize sz;
	sz.cx = sz.cy = 30;
	listArray[0] = &m_List1;
	for(int j=0; j<=0; j++)
	{
		listArray[j]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		listArray[j]->ApproximateViewRect(sz,1);
		listArray[j]->InsertColumn(i++, "���", LVCFMT_LEFT, 40, -1);
		listArray[j]->InsertColumn(i++, "����", LVCFMT_LEFT, 130, -1);
		listArray[j]->InsertColumn(i++, "����/�澯", LVCFMT_CENTER, 80, -1);
		listArray[j]->InsertColumn(i++, "��ֵ(A/V)", LVCFMT_RIGHT, 80, -1);
		listArray[j]->InsertColumn(i++, "ʱ��(s)", LVCFMT_RIGHT, 90, -1);
		listArray[j]->InsertColumn(i++, "����/��ע", LVCFMT_RIGHT, 151, -1);
	}

	CRect rect;
	listArray[0]->GetWindowRect(&rect);

	rect.top -= 80;
	rect.bottom -= 80;

//	AfxMessageBox("001");
	LoadSxjzsConfig(0);
}

void CSxJzsCfgView::LoadSxjzsConfig(int LineNo)
{
	int i;
	bool gaojing_flag=false;//���޸澯��־λ
	   bool dongzuo_flag=false;//���޶�����־λ

	bool flag=false;
	bool flag1=false;//�����˳���־λ
	int StartIndex,EndIndex;
	int addItem;

		// TODO: Add your control notification handler code here
//	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��


	m_ZXCHZTime=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.ZXCHZTime;//�����غ�բʱ��
	m_FZXCHZTime=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.FZXCHZTime;//��֧���غ�բʱ��

//	CString cs;
//	cs.Format("m_FZXCHZTime=%d",mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.ZXCHZTime);
//	AfxMessageBox(cs);


	m_strEdit = mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Name;
	LineType=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type;
//	m_LineType.SetCurSel(LineType);//#��·����:0-����;1-��֧��


	SwitchType=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type;
//		CString cs;
//	cs.Format("��������%d",SwitchType);
//	AfxMessageBox(cs);
//	m_SwitchType.SetCurSel(SwitchType);//��������(0-��·��, 1-���ɿ���)

	CString ccc;
	ccc.Format(" type= %d ",SwitchType);
	SetDlgItemText(IDC_EDIT12,ccc);

//	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type;
//		SwitchType=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type;
//	Sleep(10);
	if(SwitchType ==0 )
	{
		((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(1);
		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(0);
		((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	}
	else if(SwitchType ==1 )
	{
		((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(0);
		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(1);
		((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	}
	else if(SwitchType ==2 )
	{
		((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(0);
		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(0);
		((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(1);
	}

	m_SboNum=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.SBO_Num;//#��·SBO��

	m_SwitchNum=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Num;//#��·���غ�

	if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CxLogicFlag == 255)//#�г����߼�
	{
		m_Check1 = true;
	}
	else
	{
		m_Check1 = false;
	}


	if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255)//�غ�ʹ��
	{
		m_Check2 = true;
		GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		if(LineType == 0)//�غ�բʹ�ܲ��� ��·Ϊ����ʱ�Ż� �г����߼�
		GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
	}
	else
	{
		m_Check2 = false;
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
	}


//	CString cs;
//	cs.Format("������%d",SwitchType);
//	AfxMessageBox(cs);

	if( (SwitchType == 1) )//ѡ���غ�բ���ҿ�������Ϊ���ɿ��� //Ϊ���ؿ��������仯ʱ,����������
	{
		if(m_Check2 == true)
		{//			CString cs;
//	cs.Format("%d",SwitchType);
//	AfxMessageBox(cs);
		AfxMessageBox("��������Ϊ���ɿ���ʱ���������غ�բ!");
		}
	//	m_Check2=false;
	//	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable = 0;
	//	GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);

	}

		//SXJZS_FACT_SELECT ������ ��ʾ�ĸ���
		//SXJZS_Select ��ʾĳ���������������
		for(i=0;i<SXJZS_FACT_SELECT[SwitchType];i++)//ԭ����<= ���һ�����ж��ˣ���˱����<
		{
			int j=SXJZS_Select[SwitchType][i];
			if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==1)
			{
				gaojing_flag=true;//���ڸ澯
			}

		}

		for(i=0;i<SXJZS_FACT_SELECT[SwitchType];i++)//ԭ����<= ���һ�����ж��ˣ���˱����<
		{
			int j=SXJZS_Select[SwitchType][i];
			if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==255)
			{
				dongzuo_flag=true;//���ڶ���
			}

		}

		if( gaojing_flag == true && dongzuo_flag== true)
		{
				AfxMessageBox("�澯����������ͬʱ����!");
		}
	/*
	else if(m_Enable.GetCurSel() == 2)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "�˳�");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=0;

		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255)//�غ�ʹ��
		{
			GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		}

		for(i=0;i<=SXJZS_FACT_SELECT[m_SwitchType.GetCurSel()];i++)
		{
			int j=SXJZS_Select[m_SwitchType.GetCurSel()][i];
			if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==1)
			{
				GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
				GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
				GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
			}

		}
	}
	*/

	if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PHaveV_Flag  == 255)//�غ�բ����ѹ��־
	{
		m_Check3 = true;
	}
	else
	{
		m_Check3 = false;
	}

	if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PSwitchStatus  == 255)//�п���λ��
	{
		m_Check4 = true;
	}
	else
	{
		m_Check4 = false;
	}


	UpdateData(UPDATE_WRITE);
	listArray[0]->DeleteAllItems();


/*
	if(SwitchType == 0)//��·��
	{
		StartIndex =0;
		EndIndex=4;
	}
	else if(SwitchType == 1)//���ɿ���
	{
		StartIndex =4;
		EndIndex=5;
	}
	else if(SwitchType == 2)//��ϵ��� �۶���
	{
		StartIndex=0;
		EndIndex=0;
	}
*/
/*
	for(i=0; i<num; i++,StartIndex++)
	{
		addItem = listArray[0]->InsertItem(i, Str(i), 0);
		listArray[0]->SetItemData(addItem, mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Type);
		listArray[0]->SetItemText(addItem, 1, mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Name);
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Enable == 255)
			listArray[0]->SetItemText(addItem, 2, "����");
		else if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Enable == 1)
			listArray[0]->SetItemText(addItem, 2, "�澯");
		else if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Enable == 0)
			listArray[0]->SetItemText(addItem, 2, "�˳�");
		listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Value));
		listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Time));
		listArray[0]->SetItemText(addItem, 5, mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Unit);
	}
*/
	int index;
	bool zuhedianqi_have_dongzuo=false;//��ϵ������ж��� �� ��������
	for(i=0; i<=SXJZS_FACT_SELECT[SwitchType]; i++)//ÿ�ֿ��������м�������
	{
		index=SXJZS_Select[SwitchType][i];//switchtype���������� i:�ڼ�������
		addItem = listArray[0]->InsertItem(i, Str(i), 0);
		listArray[0]->SetItemData(addItem, mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Type);
		listArray[0]->SetItemText(addItem, 1, mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Name);
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable == 255)
		{
			listArray[0]->SetItemText(addItem, 2, "����");
			if(SwitchType == 2 && index !=5)
			{
				zuhedianqi_have_dongzuo = true;//��ϵ����к��ж���ѡ��
			}
		}

		else if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable == 1)
		{
			listArray[0]->SetItemText(addItem, 2, "�澯");
			//��ʱ��index�� prot���.��0��ʼ��
			if((SwitchType ==0  && index != 5) || (SwitchType ==1 && index != 5) ||(SwitchType ==2 && index !=5 ))//�����4�Ļ�����ֱ�Ӻ��Ե��ˣ����ü�����
			{
				flag=true;//�и澯
			}
		}
		else if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable == 0)
		{
			listArray[0]->SetItemText(addItem, 2, "�˳�");
			flag1=true;//���˳�

		}
		listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Value));
		listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Time));
		listArray[0]->SetItemText(addItem, 5, mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Unit);
	}

	if(flag==true)//�и澯 ȫ�����
	{
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		CHZ_flag=0;
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
	}
	else //if(flag==false)////�޸澯
	{
		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		CHZ_flag=0xff;
	}


	if(zuhedianqi_have_dongzuo == true)
	{
		AfxMessageBox("��ϵ����в��ܺ��ж���ѡ������ı�!");
	}


	if(LineType == 0)//����
	{
	//	GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);//�г����߼� ʹ��
		((CButton *)GetDlgItem(IDC_RADIO4))->SetCheck(1);
		((CButton *)GetDlgItem(IDC_RADIO5))->SetCheck(0);


		GetDlgItem(IDC_STATIC_EDIT8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_EDIT81)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT8)->ShowWindow(true);
		SetDlgItemText(IDC_STATIC_EDIT9,"���߹���Ϊ���غ�բʱ��");


		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);

		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255  && CHZ_flag == 0xff )//�غ�ʹ�ܲ���û���
		{
			GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
		}
	}
	else//��֧��
	{
		GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);//�г����߼� ��ʹ��
		((CButton *)GetDlgItem(IDC_RADIO5))->SetCheck(1);
		((CButton *)GetDlgItem(IDC_RADIO4))->SetCheck(0);

		GetDlgItem(IDC_STATIC_EDIT8)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_EDIT81)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT8)->ShowWindow(false);

		SetDlgItemText(IDC_STATIC_EDIT9,"     ��֧���غ�բʱ��");

		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255  && CHZ_flag == 0xff )//�غ�ʹ�ܲ���û���
		{
			GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
		}


	}

	/*

	if(flag1==true && flag==true)
	{
		AfxMessageBox("�澯����������ͬʱ����");
	}
	*/


	/*******************************
	Ԥ�����ܵ�ʵ��
  *********************************/
	yulan();

}
void CSxJzsCfgView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

//	m_LineType.ResetContent();
//	m_LineType.AddString("����");
//	m_LineType.AddString("��֧��");

//	m_SwitchType.ResetContent();
//	m_SwitchType.AddString("��·��");
//	m_SwitchType.AddString("���ɿ���");
//	m_SwitchType.AddString("��ϵ���(���ɿ���+�۶���)");


//	SXJZSCfgStru SXJZSFile;
//	SXJZSCfgStru SXJZSFileTemp;

	//Ϊ�˷�ֹ���ֲ�һ�µ������ȷʵҲ���ֹ��ˡ�
	memcpy(&(mPzkIni.SXJZSFileTemp),&(mPzkIni.SXJZSFile),sizeof(SXJZSCfgStru));

	m_ToolTipCtrl123.Create(this);
	m_ToolTipCtrl123.AddTool(GetDlgItem(IDC_CHECK1),_T("���ط�λ ��������!"));//���
	m_ToolTipCtrl123.AddTool(GetDlgItem(IDC_COMBO3),_T("��·1-12Ϊ��࣬��·13-24Ϊ�Ҳ�"));//���
//	m_ToolTipCtrl123.AddTool(GetDlgItem(IDC_RADIO7),_T("���Ҳ��12����·"));//���
	m_ToolTipCtrl123.AddTool(GetDlgItem(IDC_EDIT11),_T("��·�����20���ַ�"));//���
	m_ToolTipCtrl123.AddTool(GetDlgItem(IDC_STATIC_TISHI),_T("�澯ʱ���߼���������"));//���

	m_ToolTipCtrl123.SetMaxTipWidth(300);
	m_ToolTipCtrl123.Activate(TRUE);
	m_ToolTipCtrl123.SetDelayTime(TTDT_INITIAL, 0);
	m_ToolTipCtrl123.SetDelayTime(TTDT_AUTOPOP, 90000);


	m_Version = mPzkIni.SXJZSFileTemp.Cfg.Version;//�汾��
	m_LineNum = mPzkIni.SXJZSFileTemp.Cfg.ProtLineNum;//��·��
	m_PNumPerLine = mPzkIni.SXJZSFileTemp.Cfg.ProtNumPerLine;//ÿ����·���ٱ���
	m_FixActTime = mPzkIni.SXJZSFileTemp.Cfg.FixActTime;//��������ʱ��
	m_LeftDTUNum = mPzkIni.SXJZSFileTemp.Cfg.LeftDTUNum;//�����·��


	//CString cs;
	//cs.Format("???? %d %d %d ",mPzkIni.SXJZSFile.Cfg.LeftDTUNum,mPzkIni.SXJZSFileTemp.Cfg.LeftDTUNum,m_LeftDTUNum);
	//AfxMessageBox(cs);


	if(mPzkIni.SXJZSFileTemp.Cfg.Prot_YXEnable == 255)//������ң��ʹ��
	{
		m_Check5 = true;
	}
	else
	{
		m_Check5 = false;
	}
	if(mPzkIni.SXJZSFileTemp.Cfg.Prot_MsgEnable == 255)//������Ϣ�ϱ�ʹ��
	{
		m_Check6 = true;
	}
	else
	{
		m_Check6 = false;
	}
	if(mPzkIni.SXJZSFileTemp.Cfg.PLC_Enable == 255)//PLCͶ��
	{
		m_Check7 = true;
	}
	else
	{
		m_Check7 = false;
	}

	if(mPzkIni.SXJZSFileTemp.Cfg.MxType == 0)//��ĸ��
	{
		((CButton *)GetDlgItem(IDC_RADIO6))->SetCheck(1);
		((CButton *)GetDlgItem(IDC_RADIO7))->SetCheck(0);

	//	GetDlgItem(IDC_STATIC_LeftDTUNum)->ShowWindow(SW_SHOW);
	//	GetDlgItem(IDC_EDIT13)->ShowWindow(true);
	//	GetDlgItem(IDC_EDIT13)->EnableWindow(TRUE);
	}
	else if(mPzkIni.SXJZSFileTemp.Cfg.MxType == 1)//˫ĸ��
	{
		((CButton *)GetDlgItem(IDC_RADIO6))->SetCheck(0);
		((CButton *)GetDlgItem(IDC_RADIO7))->SetCheck(1);

	//	GetDlgItem(IDC_STATIC_LeftDTUNum)->ShowWindow(SW_HIDE);
		//GetDlgItem(IDC_EDIT13)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_EDIT13)->ShowWindow(false);
	}

//	m_Local = mPzkIni.ProtFile.Line[0].LineCfg.Line_Switch;
	UpdateData(UPDATE_WRITE);
	InitListCtrl();


	int i;

	if(m_LineNum > 0)
	{
		CString formatStr;
		m_LineNo.ResetContent();
		for(i=1; i<=m_LineNum; i++)
		{
			formatStr.Format("��·%d", i);
			m_LineNo.AddString(formatStr);
		}
		m_LineNo.SetCurSel(0);
	}


}

void CSxJzsCfgView::OnSave()
{
	// TODO: Add your control notification handler code here

	UpdateData(true);//���浽����
	int i;
	int LineNo;
	LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��


	if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type == 2)//��ϵ����к��ж�������ô����
	{
		for(i=0;i<SXJZS_FACT_SELECT[mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type];i++)//ԭ����<= ���һ�����ж��ˣ���˱����<
		{
			int j=SXJZS_Select[mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type][i];
			if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==255)
			{
				//���ڶ���
				AfxMessageBox("��ϵ����в��ܴ��ڶ���!");
				return ;
			}

		}
	}

	mPzkIni.SXJZSFile.Cfg.Version=mPzkIni.SXJZSFileTemp.Cfg.Version;//�汾�� ==��ʵû�仯
	mPzkIni.SXJZSFile.Cfg.ProtLineNum=mPzkIni.SXJZSFileTemp.Cfg.ProtLineNum;//��·��
	//m_PNumPerLine = mPzkIni.SXJZSFileTemp.Cfg.ProtNumPerLine;//ÿ����·���ٱ��� ==û�仯
	mPzkIni.SXJZSFile.Cfg.Prot_YXEnable=mPzkIni.SXJZSFileTemp.Cfg.Prot_YXEnable;//������ң��ʹ��
	mPzkIni.SXJZSFile.Cfg.Prot_MsgEnable=mPzkIni.SXJZSFileTemp.Cfg.Prot_MsgEnable;//������Ϣ�ϱ�ʹ��
	mPzkIni.SXJZSFile.Cfg.PLC_Enable =mPzkIni.SXJZSFileTemp.Cfg.PLC_Enable; //PLCͶ��
	mPzkIni.SXJZSFile.Cfg.FixActTime =mPzkIni.SXJZSFileTemp.Cfg.FixActTime; //������������ʱ��
//	mPzkIni.SXJZSFile.Cfg.ZXCHZTime =mPzkIni.SXJZSFileTemp.Cfg.ZXCHZTime; //�����غ�բʱ��
//  mPzkIni.SXJZSFile.Cfg.FZXCHZTime =mPzkIni.SXJZSFileTemp.Cfg.FZXCHZTime; //��֧���غ�բʱ��

	mPzkIni.SXJZSFile.Cfg.MxType =mPzkIni.SXJZSFileTemp.Cfg.MxType; //ĸ������
	mPzkIni.SXJZSFile.Cfg.LeftDTUNum =mPzkIni.SXJZSFileTemp.Cfg.LeftDTUNum; //�����·��



//	for(LineNo=0;LineNo<SXJZS_FACT_LINE+1;LineNo++)//������·����һ��
	{
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.ZXCHZTime =mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.ZXCHZTime; //�����غ�բʱ��
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.FZXCHZTime=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.FZXCHZTime; //��֧���غ�բʱ��
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Line_Name=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Name;
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Line_Type=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type;//��·����
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.CxLogicFlag=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CxLogicFlag;//�г����߼�
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.CHZ_Enable=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable;//�غ�բʹ��
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.PHaveV_Flag=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PHaveV_Flag;//�е�ѹ
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.PSwitchStatus=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PSwitchStatus;//�п���λ��
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Switch_Type=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type;//��������
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.SBO_Num=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.SBO_Num;//#��·SBO��
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Switch_Num=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Num;//��·���غ�

		for(i=0;i<m_PNumPerLine;i++)//ȫ������һ�� 0-ÿ����·������
		{
			mPzkIni.SXJZSFile.Line[LineNo].SXJZSItem[i].Type = mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[i].Type;
			mPzkIni.SXJZSFile.Line[LineNo].SXJZSItem[i].Enable=mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[i].Enable;
			mPzkIni.SXJZSFile.Line[LineNo].SXJZSItem[i].Value = mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[i].Value;
			mPzkIni.SXJZSFile.Line[LineNo].SXJZSItem[i].Time = mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[i].Time;
		}
	}

	bEverEdited = false;
	mPzkIni.EverModified = true;
	yulan();

}
void CSxJzsCfgView::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
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
	UpdateData(true);
	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��

	if(nItem < 0)
		return;

	if(nSubItem == 0)
		return;

	if(nSubItem == 1)
	{
		return;
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO4);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO4);
		pCombo->SetCurSel(m_List1.GetItemData(nItem));
	}
	else if(nSubItem == 2)
	{


		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type == 2) //��ϵ���
		{

		//	AfxMessageBox("����ϵ���");
			pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO5);
			pCombo = (CComboBox *)GetDlgItem(IDC_COMBO5);
			str = m_List1.GetItemText(nItem, nSubItem);
			m_Enable.ResetContent();
			m_Enable.AddString(_T("�澯"));
			 m_Enable.AddString(_T("�˳�"));
		//	 UpdateData(FALSE);

			if(str.Compare("�澯") == 0)
				pCombo->SetCurSel(0);

			else if(str.Compare("�˳�") == 0)
				pCombo->SetCurSel(1);

		}

		else if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type!= 2) //������ϵ���
		{
		//	AfxMessageBox("������ϵ���");
			CString css;
			css.Format("xianluhao   %d",LineNo);
		//	AfxMessageBox(css);
			pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO5);
			pCombo = (CComboBox *)GetDlgItem(IDC_COMBO5);
			str = m_List1.GetItemText(nItem, nSubItem);

			m_Enable.ResetContent();
			m_Enable.AddString(_T("����"));
			m_Enable.AddString(_T("�澯"));
			 m_Enable.AddString(_T("�˳�"));
		//	 UpdateData(FALSE);

			if(str.Compare("����") == 0)
				pCombo->SetCurSel(0);
			if(str.Compare("�澯") == 0)
				pCombo->SetCurSel(1);
			else if(str.Compare("�˳�") == 0)
				pCombo->SetCurSel(2);

		}

	}
	else if(nSubItem != 5 )
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT3);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT3);
		m_Input.SetWindowText(m_List1.GetItemText(nItem, nSubItem));
	}
	else
		return;

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

void CSxJzsCfgView::OnChangeEdit1() //��·SBO��
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;//�����仯

}

void CSxJzsCfgView::OnKillfocusEdit1()
{
	// TODO: Add your control notification handler code here
	UpdateData(UPDATE_READ);
	if(m_SboNum > 23)
	{
		AfxMessageBox("��·SBO�Ų��ܳ���"+Str(23));
		m_SboNum = 23;
		UpdateData(UPDATE_WRITE);
	}
	if(m_SboNum < 0)
	{
		AfxMessageBox("��·SBO�Ų���С��"+Str(0));
		m_SboNum = 0;
		UpdateData(UPDATE_WRITE);
	}

	UpdateData(true);//���浽����
	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.SBO_Num=m_SboNum;//#��·SBO��
}

/*
	�����Ÿı䣬�����洢����Ϊ�������¼�ʱ����·���Ѿ��ı䣬��˱���ʱ���Ǵ����ֵ��
	��� ��д�� edit ʧȥ����ʱ������ ok
*/
void CSxJzsCfgView::OnSelchangeCombo3() //��·�������ı�
{
	// TODO: Add your control notification handler code here
//	OnCANCEl();


	UpdateData(true);//�ӽ��浽����
	int LineNo;
	LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��

	int abc=LINE_AGO;
	CString str1;
	CString str2;
	str2.Format("%d",LINE_AGO+1);
	str1+="�Ƿ񱣴�� ��·";
	str1+=str2;
	str1+=" ���޸�?";


//	CString ee;
//	ee.Format("LINE_AGO= %d",LINE_AGO);
//	AfxMessageBox(ee);

	if(bEverEdited &&(LineNo != LINE_AGO))
	{
		int i = AfxMessageBox(str1,MB_YESNO);
		if(i == IDYES)
		{
			OnSaveAgo(abc);
		}
		else if(i == IDNO)
		{

			OnCANCElAgo(abc);
		}

	}



/*	//listarray �洢
	int i;
	int StartIndex,EndIndex;
	if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type==0)//��·��
	{
		StartIndex=0;
		EndIndex=4;

	}
	else if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type==1)//���ɿ���
	{
		StartIndex=4;
		EndIndex=5;
	}

	int num=EndIndex-StartIndex;

	for(i=0;i<num;i++,StartIndex++)
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Type = listArray[0]->GetItemData(i);
			//CString cs;
			//cs.Format("%d",nItem);
			//AfxMessageBox(listArray[0]->GetItemText(i,2));
		if(listArray[0]->GetItemText(i,2) == "����")
		{
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Enable = 255;

		}
		else if(listArray[0]->GetItemText(i,2) == "�澯")
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Enable = 1;
		else if(listArray[0]->GetItemText(i,2) == "�˳�")
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Enable = 0;
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Value = myatof(listArray[0]->GetItemText(i,3));
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Time = myatof(listArray[0]->GetItemText(i,4));

	}

  */
	//	AfxMessageBox("002");

	LoadSxjzsConfig(LineNo);

}

void CSxJzsCfgView::OnCheck5() //������ң��ʹ��
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	UpdateData(true);
	if(m_Check5 ==true)
	{
		mPzkIni.SXJZSFileTemp.Cfg.Prot_YXEnable =255;
	}
	else
	{
		mPzkIni.SXJZSFileTemp.Cfg.Prot_YXEnable =0;
	}

}

void CSxJzsCfgView::OnCheck6() //������Ϣ�ϱ�ʹ��
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	UpdateData(true);
	if(m_Check6 == true)
	{
		mPzkIni.SXJZSFileTemp.Cfg.Prot_MsgEnable = 255;
	}
	else
	{
		mPzkIni.SXJZSFileTemp.Cfg.Prot_MsgEnable = 0;
	}
}



void CSxJzsCfgView::OnCheck2() //�غ�ʹ��
{
	// TODO: Add your control notification handler code here

	bEverEdited = true;
	UpdateData(true);
	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��
	int i=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type;
	if(m_Check2 == true && SwitchType==1)//ѡ���غ�բ���ҿ�������Ϊ���ɿ���
	{
		AfxMessageBox("��������Ϊ���ɿ���ʱ���������غ�բ!");
		m_Check2=false;
	}
	if(m_Check2 == true)
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable=255;
		GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		if(i==0)//����
			GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);


		GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
	}
	else
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable=0;
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
	}
	UpdateData(false);

}

void CSxJzsCfgView::OnCheck3()//�ж��Ƿ���ѹ
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	UpdateData(true);//���浽����

	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��
	if(m_Check3 == true)
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PHaveV_Flag=255;
	}
	else
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PHaveV_Flag=0;
	}
}

void CSxJzsCfgView::OnCheck4() //�п���λ��
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	UpdateData(true);//���浽����
	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��
	if(m_Check4 == true)
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PSwitchStatus=255;
	}
	else
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PSwitchStatus=0;
	}
}

void CSxJzsCfgView::OnCheck1() //�г����߼�
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	UpdateData(true);//���浽����
	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��
	if(m_Check1 == true)
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CxLogicFlag=255;
	}
	else
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CxLogicFlag=0;
	}
}

void CSxJzsCfgView::OnChangeEdit2() //��·���غ�
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;//�����仯

}

void CSxJzsCfgView::OnKillfocusEdit2()
{
	// TODO: Add your control notification handler code here
	UpdateData(UPDATE_READ);
	if(m_SwitchNum > 128)
	{
		AfxMessageBox("��·���غŲ��ܳ���"+Str(128));
		m_SwitchNum = 128;
		UpdateData(UPDATE_WRITE);
	}
	if(m_SwitchNum < 0)
	{
		AfxMessageBox("��·���غŲ���С��"+Str(0));
		m_SwitchNum = 0;
		UpdateData(UPDATE_WRITE);
	}

	UpdateData(true);//���浽����
	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Num=m_SwitchNum;//��·���غ�
}

void CSxJzsCfgView::OnChangeEdit5()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
	UpdateData(true);//���浽����


}

void CSxJzsCfgView::OnKillfocusEdit5()
{

	int CurLine = m_LineNo.GetCurSel();

	UpdateData(UPDATE_READ);
	if(m_LineNum > (SXJZS_FACT_LINE+1))//��Ŵ�0 ��ʼ��ԭ��
	{
		AfxMessageBox("�����·�����ܳ���"+Str(SXJZS_FACT_LINE+1)+Str("��!"));
		m_LineNum = SXJZS_FACT_LINE+1;
		UpdateData(UPDATE_WRITE);
	}

	if(m_LineNum <= 0)
	{
		AfxMessageBox("��С��·������С��"+Str(1)+Str("��!"));
		m_LineNum = 1;
		UpdateData(UPDATE_WRITE);
	}
	mPzkIni.SXJZSFileTemp.Cfg.ProtLineNum=m_LineNum ;//��·��
	m_LineNo.ResetContent();
	if(m_LineNum > 0)
	{
		CString formatStr;
		for(int i=1; i<=m_LineNum; i++)
		{
			formatStr.Format("��·%d", i);
			m_LineNo.AddString(formatStr);
		}
	}
	m_LineNo.SetCurSel(0);
//		AfxMessageBox("003");
	LoadSxjzsConfig(0);

}

void CSxJzsCfgView::OnKillfocusCombo5() //+4 ����
{

//	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��
//	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type=crazy ;//��������

//	AfxMessageBox("kaokaokao");
	// TODO: Add your control notification handler code here
/*
	if(m_SwitchType.GetCurSel()==0)//��·��
	{
		if(m_Enable.GetCurSel() == 0)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "����");
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem].Enable=255;
		}
		else if(m_Enable.GetCurSel() == 1)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "�澯");
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem].Enable=1;
		}
		else if(m_Enable.GetCurSel() == 2)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "�˳�");
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem].Enable=0;
		}
	}
	else if(m_SwitchType.GetCurSel()==1)//���ɿ��� +4+4
	{
		if(m_Enable.GetCurSel() == 0)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "����");
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem+4].Enable=255;
		}
		else if(m_Enable.GetCurSel() == 1)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "�澯");
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem+4].Enable=1;
		}
		else if(m_Enable.GetCurSel() == 2)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "�˳�");
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem+4].Enable=0;
		}
	}
	else if(m_SwitchType.GetCurSel()==2)//��ϵ��� �۶���
	{
		if(m_Enable.GetCurSel() == 0)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "����");
		//	mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem+4].Enable=255;
		}
		else if(m_Enable.GetCurSel() == 1)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "�澯");
		//	mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem+4].Enable=1;
		}
		else if(m_Enable.GetCurSel() == 2)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "�˳�");
		//	mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem+4].Enable=0;
		}

	}
*/

/*
	bool flag=false;
	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��
	int index = SXJZS_Select[m_SwitchType.GetCurSel()][nItem];//������������ĵ�ĳ�����ص��±�
//	CString cs;
//	cs.Format("%d",nItem);
//	AfxMessageBox(cs);
	int i;

	if(m_Enable.GetCurSel() == 0)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "����");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=255;


		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255)//�غ�ʹ��
		{

			GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		}

		//SXJZS_FACT_SELECT ������ ��ʾ�ĸ���
		//SXJZS_Select ��ʾĳ���������������
		for(i=0;i<=SXJZS_FACT_SELECT[m_SwitchType.GetCurSel()];i++)
		{
			int j=SXJZS_Select[m_SwitchType.GetCurSel()][i];
			if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==1)
			{
				flag=true;//���ڸ澯
				GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
				GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
				GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
			}

		}
	}
	else if(m_Enable.GetCurSel() == 1)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "�澯");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=1;
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		for(i=0;i<=SXJZS_FACT_SELECT[m_SwitchType.GetCurSel()];i++)
		{
			int j=SXJZS_Select[m_SwitchType.GetCurSel()][i];
			if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==255)
			{
				flag=true;//���ڶ���
			}
		}

	}
	else if(m_Enable.GetCurSel() == 2)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "�˳�");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=0;

		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255)//�غ�ʹ��
		{
			GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		}

		for(i=0;i<=SXJZS_FACT_SELECT[m_SwitchType.GetCurSel()];i++)
		{
			int j=SXJZS_Select[m_SwitchType.GetCurSel()][i];
			if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==1)
			{
				GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
				GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
				GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
			}

		}
	}

	m_Enable.ShowWindow(SW_HIDE);
	bEverEdited = true;
//	if(flag==true && (nItem!=-1))//-1 ��
//	{
//		AfxMessageBox("�澯����������ͬʱ����!");
//	}

//	if(flag==true)
////	{
//		for(i=0;i<=SXJZS_FACT_SELECT[m_SwitchType.GetCurSel()];i++)
//		{
//			int j=SXJZS_Select[m_SwitchType.GetCurSel()][i];
//			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable=mPzkIni.SXJZSFile.Line[LineNo].SXJZSItem[j].Enable;
//		}
//		LoadSxjzsConfig(LineNo);
//	}
//	m_Enable.SetCurSel(2);
*/



/*
	bool flag=false;
	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��
	int index = SXJZS_Select[mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type][nItem];//������������ĵ�ĳ�����ص��±�
//	CString cs;
//	cs.Format("%d",mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type);
//	AfxMessageBox(cs);
	int i;

if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type !=2)//���Ǹ��ɿ���
{
	if(m_Enable.GetCurSel() == 0)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "����");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=255;
	}
	else if(m_Enable.GetCurSel() == 1)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "�澯");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=1;
	}
	else if(m_Enable.GetCurSel() == 2)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "�˳�");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=0;
	}
}
else if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type ==2)//�Ǹ��ɿ���
{

	if(m_Enable.GetCurSel() == 0)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "�澯");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=1;
	}
	else if(m_Enable.GetCurSel() == 1)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "�˳�");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=0;
	}
}




	m_Enable.ShowWindow(SW_HIDE);
	bEverEdited = true;
	LoadSxjzsConfig(LineNo);
*/

}



void CSxJzsCfgView::OnSelchangeCombo2() //��·����
{
	// TODO: Add your control notification handler code here
/*
	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��
	UpdateData(true);//���浽����
	int i=m_LineType.GetCurSel();
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type=i;
	if(i==0)//����
	{
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable==255)
			GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
	}
	else
		GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);


	bEverEdited = true;
*/
}

void CSxJzsCfgView::OnKillfocusCombo2()
{
	// TODO: Add your control notification handler code here
//	int i=m_LineType.GetCurSel();
//	if(i==0)//����
//		GetDlgItem(IDC_CHECK1)->ShowWindow(SW_SHOW);
//	else
//		GetDlgItem(IDC_CHECK1)->ShowWindow(SW_HIDE);


}

void CSxJzsCfgView::OnSelchangeCombo4() //��������
{
	// TODO: Add your control notification handler code here
	//int i=m_SwitchType.GetCurSel();
/*
	bEverEdited = true;
	int LineNo;
	UpdateData(true);//���浽���� //�������͸ı�
	LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��

	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type=m_SwitchType.GetCurSel();
	LoadSxjzsConfig(LineNo);
*/

}


LRESULT CSxJzsCfgView::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)
{
//	OnCANCEl();
	return TRUE;
}

LRESULT CSxJzsCfgView::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)
{
	if(bEverEdited)
	{
		int i = AfxMessageBox("���浱ǰ�Ա����������������޸���",MB_YESNOCANCEL);
		if(i == IDYES)
			OnSave();
		else if(i == IDCANCEL)
		{
//			bCloseWindow = false;
			return FALSE;
		}
		else
		;//	OnCANCEl();
	}
	return TRUE;
}


void CSxJzsCfgView::OnKillfocusEdit3() //���ֱ༭ʧȥ����
{
	// TODO: Add your control notification handler code here
	CString str;
	m_Input.GetWindowText(str);
	listArray[0]->SetItemText(nItem, nSubItem, str);

	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��

/*
	if(m_SwitchType.GetCurSel()==0)//��·��
	{
		if( nSubItem == 3)
		{
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem].Value=myatof(str);
		}
		else if(nSubItem == 4)
		{
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem].Time=myatof(str);
		}
	}
	else if(m_SwitchType.GetCurSel()==1)//���ɿ��� +4+4
	{
		if(nSubItem == 3)
		{
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem+4].Value=myatof(str);
		}
		else if(nSubItem == 4)
		{
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem+4].Time=myatof(str);
		}
	}
	else if(m_SwitchType.GetCurSel()==2)//��ϵ��� �۶���
	{
		if(nSubItem == 3)
		{
		//	mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem+4].Value=myatof(str);
		}
		else if(nSubItem == 4)
		{
		//	mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem+4].time=myatof(str);
		}
	}
*/

	int index = SXJZS_Select[SwitchType][nItem];//������������ĵ�ĳ�����ص��±�
	if(nSubItem == 3)
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Value=myatof(str);
	}
	else if(nSubItem == 4)
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Time=myatof(str);

	}

	m_Input.ShowWindow(SW_HIDE);
	bEverEdited = true;

}

void CSxJzsCfgView::OnCANCEl()
{
	// TODO: Add your control notification handler code here
		UpdateData(true);//���浽����
/*
	mPzkIni.SXJZSFileTemp.Cfg.Version=mPzkIni.SXJZSFile.Cfg.Version;//�汾�� ==��ʵû�仯
	mPzkIni.SXJZSFileTemp.Cfg.ProtLineNum=mPzkIni.SXJZSFile.Cfg.ProtLineNum;//��·��
	//m_PNumPerLine = mPzkIni.SXJZSFileTemp.Cfg.ProtNumPerLine;//ÿ����·���ٱ��� ==û�仯
	mPzkIni.SXJZSFileTemp.Cfg.Prot_YXEnable=mPzkIni.SXJZSFile.Cfg.Prot_YXEnable;//������ң��ʹ��
	mPzkIni.SXJZSFileTemp.Cfg.Prot_MsgEnable=mPzkIni.SXJZSFile.Cfg.Prot_MsgEnable;//������Ϣ�ϱ�ʹ��
	mPzkIni.SXJZSFileTemp.Cfg.Byd_SOEEnable =mPzkIni.SXJZSFile.Cfg.Byd_SOEEnable; //Խ�޸澯SOEʹ��
	mPzkIni.SXJZSFileTemp.Cfg.Flt_YXEnable = mPzkIni.SXJZSFile.Cfg.Flt_YXEnable;// ���ϼ������ϱ�ʹ��
	mPzkIni.SXJZSFileTemp.Cfg.Flt_RepEnable = mPzkIni.SXJZSFile.Cfg.Flt_RepEnable;//���ϱ����ϱ�ʹ��
*/
	int i;
	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.ZXCHZTime=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.ZXCHZTime;
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.FZXCHZTime=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.FZXCHZTime;
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Line_Type;//��·����
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CxLogicFlag=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.CxLogicFlag;//�г����߼�
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.CHZ_Enable;//�غ�բʹ��
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PHaveV_Flag=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.PHaveV_Flag;//�е�ѹ
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PSwitchStatus=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.PSwitchStatus;//�п���λ��
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Switch_Type;//��������
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.SBO_Num=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.SBO_Num;//#��·SBO��
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Num=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Switch_Num;//��·���غ�
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Name=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Line_Name;
	for(i=0;i<m_PNumPerLine;i++)//ȫ������һ�� 0-ÿ����·������
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[i].Type = mPzkIni.SXJZSFile.Line[LineNo].SXJZSItem[i].Type;
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[i].Enable=mPzkIni.SXJZSFile.Line[LineNo].SXJZSItem[i].Enable;
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[i].Value = mPzkIni.SXJZSFile.Line[LineNo].SXJZSItem[i].Value;
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[i].Time = mPzkIni.SXJZSFile.Line[LineNo].SXJZSItem[i].Time;
	}
//		AfxMessageBox("006");
	LoadSxjzsConfig(LineNo);

}

void CSxJzsCfgView::OnCheck7()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	UpdateData(true);
	if(m_Check7 ==true)
	{
		mPzkIni.SXJZSFileTemp.Cfg.PLC_Enable =255;
	}
	else
	{
		mPzkIni.SXJZSFileTemp.Cfg.PLC_Enable =0;
	}
}

void CSxJzsCfgView::OnChangeEdit6()
{
	bEverEdited = true;
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here

}

void CSxJzsCfgView::OnKillfocusEdit6()
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
	mPzkIni.SXJZSFileTemp.Cfg.FixActTime=m_FixActTime; //������������ʱ��
}

void CSxJzsCfgView::OnKillfocusList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

/*
	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��

	bool flag=false;
	bool flag1=false;
	int i;
	for(i=0;i<=SXJZS_FACT_SELECT[m_SwitchType.GetCurSel()];i++)
	{
		int j=SXJZS_Select[m_SwitchType.GetCurSel()][i];
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==1)
		{
			flag=true;//���ڸ澯
		}
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==255)
		{
			flag1=true;
		}
	}
	if(flag==true && flag1==true)
	{
		AfxMessageBox("�澯����������ͬʱ����");
	}
*/
//	*pResult = 0;
}

void CSxJzsCfgView::OnChangeEdit8()
{
	bEverEdited = true;
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here

}

void CSxJzsCfgView::OnChangeEdit9()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CSxJzsCfgView::OnKillfocusEdit8()
{
	// TODO: Add your control notification handler code here
	UpdateData(UPDATE_READ);
	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��

	if(m_ZXCHZTime > 60)
	{
		AfxMessageBox("���߹���Ϊ���غ�բʱ�䲻�ܳ���"+Str(60)+Str("s"));
		m_ZXCHZTime = 60;

		UpdateData(UPDATE_WRITE);
	}
	if(m_ZXCHZTime < 0)
	{
		AfxMessageBox("���߹���Ϊ���غ�բʱ�䲻��С��"+Str(0)+Str("s"));
		m_ZXCHZTime = 0;
		UpdateData(UPDATE_WRITE);
	}

	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.ZXCHZTime=m_ZXCHZTime;
}

void CSxJzsCfgView::OnKillfocusEdit9()
{
	// TODO: Add your control notification handler code here
	UpdateData(UPDATE_READ);
	 int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��
//	int min = mPzkIni.SXJZSFileTemp.Cfg.ZXCHZTime+3;


	if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type ==0 )//Ϊ����ʱ
	{
		if(m_FZXCHZTime > 60)//���ܳ��� 60;
		{
			AfxMessageBox("���߹���Ϊ���غ�բʱ�䲻�ܳ���"+Str(60)+Str("s"));
			m_FZXCHZTime = 60;
			UpdateData(UPDATE_WRITE);
		}
		if(m_FZXCHZTime < 0)
		{
			AfxMessageBox("���߹���Ϊ���غ�բʱ�䲻��С��"+Str(0)+Str("s"));
			m_FZXCHZTime = 0;
			UpdateData(UPDATE_WRITE);
		}
	}
	else
	{
		if(m_FZXCHZTime > 60)//���ܳ��� 60;
		{
			AfxMessageBox("��֧���غ�բʱ�䲻�ܳ���"+Str(60)+Str("s"));
			m_FZXCHZTime = 60;
			UpdateData(UPDATE_WRITE);
		}
		if(m_FZXCHZTime < 0)
		{
			AfxMessageBox("��֧���غ�բʱ�䲻��С��"+Str(0)+Str("s"));
			m_FZXCHZTime = 0;
			UpdateData(UPDATE_WRITE);
		}
	}
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.FZXCHZTime=m_FZXCHZTime;
}

void CSxJzsCfgView::OnSelchangeCombo5()
{
	// TODO: Add your control notification handler code here
	bool flag=false;
//	UpdateData(true);
	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��
	int index = SXJZS_Select[SwitchType][nItem];//������������ĵ�ĳ�����ص��±�
	CString cs;
	cs.Format("%d",nItem);
//	AfxMessageBox(cs);
	int i;

	UpdateData(false);

//	CString cs;
//	cs.Format("aaaaaaaaaaaaa%d",m_Enable.GetCurSel());
//	AfxMessageBox(cs);


if((SwitchType == 0) || (SwitchType ==1) ) //���� ��ϵ���
{
	if(m_Enable.GetCurSel() == 0)
	{
		//AfxMessageBox("...");
		listArray[0]->SetItemText(nItem, nSubItem, "����");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=255;


		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		CHZ_flag=0xff;
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255)//�غ�ʹ��
		{

			GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
		}

		//SXJZS_FACT_SELECT ������ ��ʾ�ĸ���
		//SXJZS_Select ��ʾĳ���������������
		CString cs;
		cs.Format("switchtype = %d",SwitchType);
	//	AfxMessageBox(cs);

			CString css;
	//	css.Format("SXJZS_FACT_SELECT[SwitchType] = %d",SXJZS_FACT_SELECT[SwitchType]);
	//	AfxMessageBox(css);


	//�������һ�������ǰ�߼�������Ϊ �澯�Ļ������һ������Ϊ����,��ô�ͻ����ǰ�߼���������
	//	�и澯�����Ծ͵��������ˡ�����취�ǣ�����ǵ�4������ô�Ͳ����ˣ���զզ��
		if((SwitchType ==0  && nItem != 4) || (SwitchType ==1 && nItem != 1) ||(SwitchType ==2 && nItem !=3 ))//�����4�Ļ�����ֱ�Ӻ��Ե��ˣ����ü�����

		{
			for(i=0;i<SXJZS_FACT_SELECT[SwitchType];i++)//ԭ����<= ���һ�����ж��ˣ���˱����<
			{
				int j=SXJZS_Select[SwitchType][i];
				if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==1)
				{
					flag=true;//���ڸ澯
					GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
					CHZ_flag=0;
					GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
					GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
					GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
					GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
					GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);

				}

			}
		}
	}
	else if(m_Enable.GetCurSel() == 1)
	{
	//		AfxMessageBox("!!!");
		listArray[0]->SetItemText(nItem, nSubItem, "�澯");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=1;

		if((SwitchType ==0  && nItem != 4) || (SwitchType ==1 && nItem != 1) ||(SwitchType ==2 && nItem !=3 ))//������4���ٱ��
		{
			GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
			CHZ_flag=0;
			GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		}
			//�������һ�������ǰ�߼�������Ϊ �澯�Ļ������һ������Ϊ����,��ô�ͻ����ǰ�߼���������
	//	�и澯�����Ծ͵��������ˡ�����취�ǣ�����ǵ�4������ô�Ͳ����ˣ���զզ��
		if((SwitchType ==0  && nItem != 4) || (SwitchType ==1 && nItem != 1) ||(SwitchType ==2 && nItem !=3 ))//�����4�Ļ�����ֱ�Ӻ��Ե��ˣ����ü�����
		{
			for(i=0;i<SXJZS_FACT_SELECT[SwitchType];i++)//ԭ����<= ���һ�����ж��ˣ���˱����<
			{
				int j=SXJZS_Select[SwitchType][i];
				if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==255)
				{
					flag=true;//���ڶ���
				}
			}
		}
	}

	else if(m_Enable.GetCurSel() == 2)
	{
	//	AfxMessageBox("???");
		listArray[0]->SetItemText(nItem, nSubItem, "�˳�");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=0;

		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		CHZ_flag=0xff;
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255)//�غ�ʹ��
		{
			GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		}

//		for(i=0;i<SXJZS_FACT_SELECT[SwitchType];i++)//ԭ����<= ���һ�����ж��ˣ���˱����<
//		{
//			int j=SXJZS_Select[SwitchType][i];
//			if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==1)
//			{
//				GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
//				GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
//				GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
//			}

//		}
	}

//&& (nItem!=-1)
	if(flag==true )//-1 ��
	{
		AfxMessageBox("�澯����������ͬʱ����!");
	}

   m_List1.SetFocus();
   m_Enable.ShowWindow(SW_HIDE);//��仰�ı��˿�������\/��

   bEverEdited = true;
}


else
//if(SwitchType == 2) // ��ϵ���
{

	 if(m_Enable.GetCurSel() == 0)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "�澯");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=1;
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		CHZ_flag=0;
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);

	}
	else if(m_Enable.GetCurSel() == 1)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "�˳�");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=0;

		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		CHZ_flag=0xff;
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255)//�غ�ʹ��
		{
			GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		}

		for(i=0;i<SXJZS_FACT_SELECT[SwitchType]-1;i++)//ԭ����<= ���һ�����ж��ˣ���˱����<
		{
			int j=SXJZS_Select[SwitchType][i];
			if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==1)
			{
				GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
				CHZ_flag=0;
				GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
				GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
			}

		}
	}


	m_List1.SetFocus();
	m_Enable.ShowWindow(SW_HIDE);

	bEverEdited = true;
//	CString ccc;
//	ccc.Format(" type= %d",mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type);
//	SetDlgItemText(IDC_EDIT10,ccc);
}
//	m_Enable.ShowWindow(SW_HIDE);
//	bEverEdited = true;

//	if(flag==true)
////	{
//		for(i=0;i<=SXJZS_FACT_SELECT[m_SwitchType.GetCurSel()];i++)
//		{
//			int j=SXJZS_Select[m_SwitchType.GetCurSel()][i];
//			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable=mPzkIni.SXJZSFile.Line[LineNo].SXJZSItem[j].Enable;
//		}
//		LoadSxjzsConfig(LineNo);
//	}
//	m_Enable.SetCurSel(2);
}

void CSxJzsCfgView::OnSelchangeCombo1()
{
/*
	// TODO: Add your control notification handler code here
	bool flag=false;
	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��
	int index = SXJZS_Select[mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type][nItem];//������������ĵ�ĳ�����ص��±�
//	CString cs;
//	cs.Format("%d",nItem);
//	AfxMessageBox(cs);
	int i;

	if(m_Enable.GetCurSel() == 0)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "�澯");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=1;


		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255)//�غ�ʹ��
		{

			GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		}

		//SXJZS_FACT_SELECT ������ ��ʾ�ĸ���
		//SXJZS_Select ��ʾĳ���������������
		/*
		for(i=0;i<=SXJZS_FACT_SELECT[m_SwitchType.GetCurSel()];i++)
		{
			int j=SXJZS_Select[m_SwitchType.GetCurSel()][i];
			if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==1)
			{
				flag=true;//���ڸ澯
				GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
				GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
				GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
			}

		}
		*/
/*
	}
	else if(m_Enable.GetCurSel() == 1)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "�澯");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=1;
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		for(i=0;i<=SXJZS_FACT_SELECT[mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type];i++)
		{
			int j=SXJZS_Select[mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type][i];
			if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==255)
			{
				flag=true;//���ڶ���
			}
		}

	}

	m_Enable.ShowWindow(SW_HIDE);
	bEverEdited = true;
*/
}

void CSxJzsCfgView::OnRadio1()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	int LineNo;
//	UpdateData(true);//���浽���� //�������͸ı�
	LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��

	CString cs;
	cs.Format("line11 == %d",LineNo);
//	AfxMessageBox(cs);
//	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type=0;
//		AfxMessageBox("��·��");
	LoadSxjzsConfig(LineNo);
//	LoadSxjzsConfig(LineNo);
}

void CSxJzsCfgView::OnRadio2()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	int LineNo;
//	UpdateData(true);//���浽���� //�������͸ı�
	LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��
	CString cs;
	cs.Format("line22 == %d",LineNo);
//	AfxMessageBox(cs);
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type=1;
//		AfxMessageBox("���ɿ���");
	LoadSxjzsConfig(LineNo);
//	LoadSxjzsConfig(LineNo);
}

void CSxJzsCfgView::OnRadio3()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	int LineNo;
//	UpdateData(true);//���浽���� //�������͸ı�
	LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��

	CString cs;
	cs.Format("line33 == %d",LineNo);
//	AfxMessageBox(cs);

	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type=2;
//		AfxMessageBox("��ϵ���");
	LoadSxjzsConfig(LineNo);
//	LoadSxjzsConfig(LineNo);
}





/**********************************
Ԥ�����ܵ�ʵ��
*************************************/
void CSxJzsCfgView::yulan()
{


	int LineIndex;//��·���
	int k;
	int index111;
	CString str;
	CString str1;
	CString str2;

	for(LineIndex=0;LineIndex<mPzkIni.SXJZSFile.Cfg.ProtLineNum ;LineIndex++)//N����·
	{


		//str.Format("��·%d", LineIndex+1);

		str+="��·";
		str+=Str(LineIndex+1);
		str+=" (";
		str+=mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Line_Name;
		str+=" )";
	//	str+="��·����Ϊ:";
		str+="    ";
		if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Line_Type ==0)//����
		{
			str+="����";
			str+="\r\n";

			if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.CHZ_Enable==255)
				str+="�غ�բ     Ͷ��";
			if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.CHZ_Enable==0)
				str+="�غ�բ     δͶ��";


			str+="\r\n";
			str+="��    ��     ";
			if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Type ==0)//��·��
			{
				str+="��·��";
			}
			else if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Type ==1)//���ɿ���
			{
				str+="���ɿ���";
			}
			else if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Type ==2)//��ϵ���(���ɿ���+�۶���)
			{
				str+="��ϵ���(���ɿ���+�۶���)";
			}

			str+="\r\n";
			str+="ң�غ�    ";
			str+=Str(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.SBO_Num);

			str+="\r\n";
			str+="ң�ź�    ";
			str+=Str(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Num);

			str+="\r\n";
			str+="����Ϊ���غ�բʱ��     ";
			str+=Str(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.ZXCHZTime);
			str+="s";
			str+="\r\n";

			str+="����Ϊ���غ�բʱ��     ";
			str+=Str(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.FZXCHZTime);
			str+="s";
			str+="\r\n";

		}
		else if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Line_Type ==1)//��֧��
		{
			str+="��֧��";
			str+="\r\n";

			if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.CHZ_Enable==255)
				str+="�غ�բ     Ͷ��";
			if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.CHZ_Enable==0)
				str+="�غ�բ     δͶ��";


			str+="\r\n";
			str+="��    ��     ";
			if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Type ==0)//��·��
			{
				str+="��·��";
			}
			else if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Type ==1)//���ɿ���
			{
				str+="���ɿ���";
			}
			else if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Type ==2)//��ϵ���(���ɿ���+�۶���)
			{
				str+="��ϵ���(���ɿ���+�۶���)";
			}

			str+="\r\n";
			str+="ң�غ�    ";
			str+=Str(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.SBO_Num);

			str+="\r\n";
			str+="ң�ź�    ";
			str+=Str(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Num);

			str+="\r\n";
			str+="��֧���غ�բʱ��     ";
			str+=Str(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.FZXCHZTime);
			str+="s";


			str+="\r\n";
		}

		//str+="��������Ϊ:";
		for(k=0; k<=SXJZS_FACT_SELECT[mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Type]; k++)//ÿ�ֿ��������м�������
		{
			index111=SXJZS_Select[mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Type][k];//switchtype���������� i:�ڼ�������

			str+=mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Name;
			str+="  ";


			if(mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Name.Compare("������ʧѹ") == 0)
			str+="        ";

			if(mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Name.Compare("����ٱ���") == 0)
			str+="          ";
			if(mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Name.Compare("ʧѹ����") == 0)
			str+="              ";
			if(mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Name.Compare("�����������") == 0)
			str+="      ";
			if(mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Name.Compare("������ʧѹ") == 0)
			str+="  ";

			if(mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Enable == 255)
			{
				str+="����";
			}
			else if(mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Enable == 1)
			{
				str+="�澯";
			}
			else if(mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Enable == 0)
			{
				str+="�˳�";
			}

			str+="  ";
			str+="��ֵ:";
			str1.Format("%5.2f",mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Value);
		    //Str+=Str(mPzkIni.SXJZSFileTemp.Line[LineIndex].SXJZSItem[index111].Value);
			str+=str1;

			str+="  ";
			str+="ʱ��:";
			//Str+=Str(mPzkIni.SXJZSFileTemp.Line[LineIndex].SXJZSItem[index111].Time);
			str2.Format("%5.2f",mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Time);
			str+=str2;

		//	listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Time));
		//	listArray[0]->SetItemText(addItem, 5, mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Unit);
			str+="\r\n";
		}

		str+="\r\n";

		CEdit*pEdt=(CEdit*)GetDlgItem(IDC_EDIT10);
		font.CreatePointFont(100,"Arial");
		pEdt->SetFont(&font);
		SetDlgItemText(IDC_EDIT10,str);

	}



}

void CSxJzsCfgView::OnRadio4() //����
{
	// TODO: Add your control notification handler code here
		UpdateData(true);//���浽����
	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��


//	int i=m_LineType.GetCurSel();
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type=0;
//	if(i==0)//����
//	{

		GetDlgItem(IDC_STATIC_EDIT8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_EDIT81)->ShowWindow(SW_SHOW);
	//	GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT8)->ShowWindow(true);

		SetDlgItemText(IDC_STATIC_EDIT9,"���߹���Ϊ���غ�բʱ��");

		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable==255 && CHZ_flag == 0xff)
		{
			GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);//�����߼�ʹ��
			GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
		}
//	}
//	else
//		GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);



	//ȫ�����⣬�ÿ���������ɫ
	SwitchType=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type;

	if(SwitchType ==0 )
	{
		((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(1);
		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(0);
		((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	}
	else if(SwitchType ==1 )
	{
		((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(0);
		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(1);
		((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	}
	else if(SwitchType ==2 )
	{
		((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(0);
		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(0);
		((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(1);
	}

	bEverEdited = true;
}

void CSxJzsCfgView::OnRadio5() //��֧��
{
	// TODO: Add your control notification handler code here
	UpdateData(true);//���浽����
	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��

	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type=1;
	GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);//�����߼����
	bEverEdited = true;

	GetDlgItem(IDC_STATIC_EDIT8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_EDIT81)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_EDIT8)->ShowWindow(false);

	SetDlgItemText(IDC_STATIC_EDIT9,"     ��֧���غ�բʱ��");



	if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable==255 && CHZ_flag == 0xff)
	{
		GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);//
		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
	}



	SwitchType=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type;

	if(SwitchType ==0 )
	{
		((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(1);
		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(0);
		((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	}
	else if(SwitchType ==1 )
	{
		((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(0);
		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(1);
		((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	}
	else if(SwitchType ==2 )
	{
		((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(0);
		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(0);
		((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(1);
	}
}

void CSxJzsCfgView::OnChangeEdit11()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
		int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��
		bEverEdited = true;
	UpdateData(TRUE);
	int nLen = strlen(m_strEdit);
	if(nLen>20)//20���ַ���10������
	{
		MessageBox("�����������!","��������",MB_OK);
		m_strEdit=m_strEdit.Left(20);//��ȡ20���ַ�
	}
	else
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Name=m_strEdit;
	}
}

BOOL CSxJzsCfgView::PreTranslateMessage(MSG* pMsg)
{
//	AfxMessageBox("000");
//	ASSERT(pMsg != NULL);
//if (pMsg->message == WM_MOUSEMOVE )//|| pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_LBUTTONUP)
//	if (pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_LBUTTONUP)

	//AfxMessageBox("000");
//	if(pMsg->message == WM_MOUSEMOVE)

	//m_ToolTipCtrl2.RelayEvent(pMsg);
	//m_ToolTipCtrl3.RelayEvent(pMsg);

	if(IsWindow(m_ToolTipCtrl123.m_hWnd))
	{
		m_ToolTipCtrl123.RelayEvent(pMsg);
	}
	 //	m_ToolTipCtrl1.RelayEvent(pMsg);
	return CFormView::PreTranslateMessage(pMsg);

//CFormView
}

void CSxJzsCfgView::OnKillfocusCombo3()
{
	// TODO: Add your control notification handler code here

//	INDEX_TEMP = m_LineNo.GetCurSel();//�õ���ǰ��·��


}

void CSxJzsCfgView::OnSetfocusCombo3()
{
	// TODO: Add your control notification handler code here

	LINE_AGO = m_LineNo.GetCurSel();//�õ�ǰ��·��

//	CString cs;
//	cs.Format("hhhhhhhhh = %d",LINE_AGO);
//	AfxMessageBox(cs);

//	m_LineNo.GetCurSel();//�õ���ǰ��·��
}


void CSxJzsCfgView::OnSaveAgo(int LineNo) //������ǰ��
{
	// TODO: Add your control notification handler code here

//	UpdateData(true);//���浽����
	int i;
//	int LineNo;
//	LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��
//	for(LineNo=0;LineNo<SXJZS_FACT_LINE+1;LineNo++)//������·����һ��
	{

	//	CString cs;
	//	cs.Format("vvvvvv = %d",LineNo);
	//	AfxMessageBox(cs);
	//	LineNo= LineNo-1;
		CString cs;
		cs.Format("��ϵ����в��ܴ��ڶ���,������·%d������!",LineNo+1);

		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type == 2)//��ϵ����к��ж�������ô����
		{
			for(i=0;i<SXJZS_FACT_SELECT[mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type];i++)//ԭ����<= ���һ�����ж��ˣ���˱����<
			{
				int j=SXJZS_Select[mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type][i];
				if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==255)
				{
					//���ڶ���
					AfxMessageBox(cs);
					return ;
				}

			}
		}

		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.ZXCHZTime=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.ZXCHZTime;
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.FZXCHZTime=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.FZXCHZTime;


		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Line_Name=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Name;
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Line_Type=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type;//��·����
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.CxLogicFlag=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CxLogicFlag;//�г����߼�
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.CHZ_Enable=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable;//�غ�բʹ��
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.PHaveV_Flag=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PHaveV_Flag;//�е�ѹ
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.PSwitchStatus=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PSwitchStatus;//�п���λ��
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Switch_Type=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type;//��������
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.SBO_Num=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.SBO_Num;//#��·SBO��
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Switch_Num=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Num;//��·���غ�

		for(i=0;i<m_PNumPerLine;i++)//ȫ������һ�� 0-ÿ����·������
		{
			mPzkIni.SXJZSFile.Line[LineNo].SXJZSItem[i].Type = mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[i].Type;
			mPzkIni.SXJZSFile.Line[LineNo].SXJZSItem[i].Enable=mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[i].Enable;
			mPzkIni.SXJZSFile.Line[LineNo].SXJZSItem[i].Value = mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[i].Value;
			mPzkIni.SXJZSFile.Line[LineNo].SXJZSItem[i].Time = mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[i].Time;
		}
	}

	bEverEdited = false;
	mPzkIni.EverModified = true;
	yulan();

}


void CSxJzsCfgView::OnCANCElAgo(int LineNo)
{
	// TODO: Add your control notification handler code here
	//	UpdateData(true);//���浽����
/*
	mPzkIni.SXJZSFileTemp.Cfg.Version=mPzkIni.SXJZSFile.Cfg.Version;//�汾�� ==��ʵû�仯
	mPzkIni.SXJZSFileTemp.Cfg.ProtLineNum=mPzkIni.SXJZSFile.Cfg.ProtLineNum;//��·��
	//m_PNumPerLine = mPzkIni.SXJZSFileTemp.Cfg.ProtNumPerLine;//ÿ����·���ٱ��� ==û�仯
	mPzkIni.SXJZSFileTemp.Cfg.Prot_YXEnable=mPzkIni.SXJZSFile.Cfg.Prot_YXEnable;//������ң��ʹ��
	mPzkIni.SXJZSFileTemp.Cfg.Prot_MsgEnable=mPzkIni.SXJZSFile.Cfg.Prot_MsgEnable;//������Ϣ�ϱ�ʹ��
	mPzkIni.SXJZSFileTemp.Cfg.Byd_SOEEnable =mPzkIni.SXJZSFile.Cfg.Byd_SOEEnable; //Խ�޸澯SOEʹ��
	mPzkIni.SXJZSFileTemp.Cfg.Flt_YXEnable = mPzkIni.SXJZSFile.Cfg.Flt_YXEnable;// ���ϼ������ϱ�ʹ��
	mPzkIni.SXJZSFileTemp.Cfg.Flt_RepEnable = mPzkIni.SXJZSFile.Cfg.Flt_RepEnable;//���ϱ����ϱ�ʹ��
*/

	int i;
//	LineNo= LineNo-1;//>???Ϊʲô��1����֣���

	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.ZXCHZTime=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.ZXCHZTime;//��·����
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.FZXCHZTime=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.FZXCHZTime;//��·����


	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Line_Type;//��·����
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CxLogicFlag=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.CxLogicFlag;//�г����߼�
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.CHZ_Enable;//�غ�բʹ��
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PHaveV_Flag=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.PHaveV_Flag;//�е�ѹ
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PSwitchStatus=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.PSwitchStatus;//�п���λ��
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Switch_Type;//��������
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.SBO_Num=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.SBO_Num;//#��·SBO��
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Num=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Switch_Num;//��·���غ�
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Name=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Line_Name;

//	CString cs;
//	cs.Format("aaaaaaaaaaaaaaa====%d",LineNo);
//	AfxMessageBox(cs);

//	AfxMessageBox(mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Line_Name);

	for(i=0;i<m_PNumPerLine;i++)//ȫ������һ�� 0-ÿ����·������
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[i].Type = mPzkIni.SXJZSFile.Line[LineNo].SXJZSItem[i].Type;
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[i].Enable=mPzkIni.SXJZSFile.Line[LineNo].SXJZSItem[i].Enable;
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[i].Value = mPzkIni.SXJZSFile.Line[LineNo].SXJZSItem[i].Value;
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[i].Time = mPzkIni.SXJZSFile.Line[LineNo].SXJZSItem[i].Time;
	}
bEverEdited = false;
	//	AfxMessageBox("006");
	//LoadSxjzsConfig(LineNo);

}

void CSxJzsCfgView::OnChangeEdit13()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;

}

void CSxJzsCfgView::OnKillfocusEdit13() //�����·��
{
	// TODO: Add your control notification handler code here

	UpdateData(UPDATE_READ);
	if(m_LeftDTUNum > 24)
	{
		AfxMessageBox("�����·�����ܳ���"+Str(24));
		m_LeftDTUNum = 24;
		UpdateData(UPDATE_WRITE);
	}
	if(m_LeftDTUNum < 0)
	{
		AfxMessageBox("�����·������С��"+Str(0));
		m_LeftDTUNum = 0;
		UpdateData(UPDATE_WRITE);
	}

	UpdateData(true);//���浽����
	mPzkIni.SXJZSFileTemp.Cfg.LeftDTUNum =m_LeftDTUNum; //�����·��
}

void CSxJzsCfgView::OnRadio6() //��ĸ��
{
	// TODO: Add your control notification handler code here

	bEverEdited = true;
	mPzkIni.SXJZSFileTemp.Cfg.MxType = 0;

//	GetDlgItem(IDC_STATIC_LeftDTUNum)->ShowWindow(SW_SHOW);
//	GetDlgItem(IDC_EDIT13)->ShowWindow(true);
//	GetDlgItem(IDC_EDIT13)->EnableWindow(TRUE);
}

void CSxJzsCfgView::OnRadio7() //˫ĸ��
{
	// TODO: Add your control notification handler code here

	bEverEdited = true;
	mPzkIni.SXJZSFileTemp.Cfg.MxType = 1;

//	GetDlgItem(IDC_STATIC_LeftDTUNum)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_EDIT13)->EnableWindow(FALSE);
//	GetDlgItem(IDC_EDIT13)->ShowWindow(false);
}

void CSxJzsCfgView::OnKillfocusEdit11()
{
	// TODO: Add your control notification handler code here

	int LineNo = m_LineNo.GetCurSel();//�õ���ǰ��·��

	UpdateData(TRUE);
	int nLen = strlen(m_strEdit);

	 if(nLen == 0 )//==0
	{
		AfxMessageBox("��·������Ϊ��!");
	}
}
