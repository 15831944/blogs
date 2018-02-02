// FDGCfgView1.cpp : implementation file
//
#include "stdafx.h"
#include "demo.h"
#include "FDGCfgView1.h"
#include "MyFun.h"
#include "ReadPzkIni.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int FDG_Select[FDG_MODE_KIND][FDG_SELECT];//�ֶι� ��ȡprot_select��������ݵ�����
extern int FDG_FACT_SELECT[FDG_SELECT];//ÿ�����ͱ�������

/////////////////////////////////////////////////////////////////////////////
// CFDGCfgView

IMPLEMENT_DYNCREATE(CFDGCfgView, CFormView)

CFDGCfgView::CFDGCfgView()
	: CFormView(CFDGCfgView::IDD)
{
	//{{AFX_DATA_INIT(CFDGCfgView)
	m_Check1 = FALSE;
	m_Check2 = FALSE;
	m_Check3 = FALSE;
	m_Check4 = FALSE;
	m_Check5 = FALSE;
	m_Check6 = FALSE;
	m_FixActTime = mPzkIni.FDGFile.Cfg.FixActTime;
	CMode = mPzkIni.FDGFile.Cfg.V_ConnectMode;
	bEverEdited = false;
	//}}AFX_DATA_INIT
}

CFDGCfgView::~CFDGCfgView()
{
}

void CFDGCfgView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFDGCfgView)
	DDX_Control(pDX, IDC_EDIT2, m_Input);
	DDX_Control(pDX, IDC_COMBO2, m_Enable);
	DDX_Control(pDX, IDC_COMBO1, m_FDGType);
	DDX_Control(pDX, IDC_LIST1, m_List1);
	DDX_Check(pDX, IDC_CHECK1, m_Check1);
	DDX_Check(pDX, IDC_CHECK2, m_Check2);
	DDX_Check(pDX, IDC_CHECK3, m_Check3);
	DDX_Check(pDX, IDC_CHECK4, m_Check4);
	DDX_Check(pDX, IDC_CHECK5, m_Check5);
	DDX_Check(pDX, IDC_CHECK6, m_Check6);
	DDX_Text(pDX, IDC_EDIT1, m_FixActTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFDGCfgView, CFormView)
	//{{AFX_MSG_MAP(CFDGCfgView)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_BN_CLICKED(IDC_RADIO8, OnRadio8)
	ON_BN_CLICKED(IDC_RADIO9, OnRadio9)
	ON_BN_CLICKED(IDC_RADIO10, OnRadio10)
	ON_BN_CLICKED(IDC_RADIO11, OnRadio11)
	ON_BN_CLICKED(IDC_RADIO12, OnRadio12)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_RADIO13, OnRadio13)
	ON_BN_CLICKED(IDC_RADIO14, OnRadio14)
	ON_BN_CLICKED(IDC_RADIO15, OnRadio15)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_CBN_KILLFOCUS(IDC_COMBO2, OnKillfocusCombo2)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnKillfocusEdit2)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)//��ϢID��ӳ��message�ĺ���-����4-16
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)//���������ǰ�һ���Զ������Ϣ�͸���Ϣ����Ӧ����������4-16

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFDGCfgView diagnostics

#ifdef _DEBUG
void CFDGCfgView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFDGCfgView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////

void CFDGCfgView::LoadFDGConfig()
{
	int addItem, ProType, index, LjNum;
	listArray[0]->DeleteAllItems();
	int type = m_FDGType.GetCurSel();//����������Ͽ������� 0Ϊ������ֵ�趨
	if(type ==0)
	{
		if(DMode==0 && SType==0)//�ֶ�ģʽ��ѹʱ���ͱ����б���ʾ
		{
			ProType=0;
			for(int i=0; i<FDG_FACT_SELECT[ProType]; i++)//ÿ�ֿ��������м������� <=right?
			{
				index=FDG_Select[ProType][i];//ProType��5�ֱ������� i:�ڼ�������
				addItem = listArray[0]->InsertItem(i, Str(i), 0);
				listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Type);//?
				listArray[0]->SetItemText(addItem, 1, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Name);
				if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 255)
				{
					listArray[0]->SetItemText(addItem, 2, "����");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 1)
				{
					listArray[0]->SetItemText(addItem, 2, "�澯");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 0)
				{
					listArray[0]->SetItemText(addItem, 2, "�˳�");
				}
				listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Value));
				listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time1));
				listArray[0]->SetItemText(addItem, 5, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time2));
				listArray[0]->SetItemText(addItem, 6, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Unit);
			}
		}

		if(DMode==0 && SType==1)//�ֶ�ģʽ��ѹ����ʱ���ͱ����б���ʾ
		{
			ProType=1;
			for(int i=0; i<FDG_FACT_SELECT[ProType]; i++)//ÿ�ֿ��������м�������
			{
				index=FDG_Select[ProType][i];//
				addItem = listArray[0]->InsertItem(i, Str(i), 0);
				listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Type);//?
				listArray[0]->SetItemText(addItem, 1, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Name);
				if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 255)
				{
					listArray[0]->SetItemText(addItem, 2, "����");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 1)
				{
					listArray[0]->SetItemText(addItem, 2, "�澯");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 0)
				{
					listArray[0]->SetItemText(addItem, 2, "�˳�");
				}
				listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Value));
				listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time1));
				listArray[0]->SetItemText(addItem, 5, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time2));
				listArray[0]->SetItemText(addItem, 6, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Unit);
			}
		}

		if(DMode==0 && SType==2)//�ֶ�ģʽ����Ӧ�ۺ����ͱ����б���ʾ
		{
			ProType=2;
			for(int i=0; i<FDG_FACT_SELECT[ProType]; i++)//ÿ�ֿ��������м�������
			{
				index=FDG_Select[ProType][i];
				addItem = listArray[0]->InsertItem(i, Str(i), 0);
				listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Type);//?
				listArray[0]->SetItemText(addItem, 1, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Name);
				if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 255)
				{
					listArray[0]->SetItemText(addItem, 2, "����");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 1)
				{
					listArray[0]->SetItemText(addItem, 2, "�澯");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 0)
				{
					listArray[0]->SetItemText(addItem, 2, "�˳�");
				}
				listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Value));
				listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time1));
				listArray[0]->SetItemText(addItem, 5, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time2));
				listArray[0]->SetItemText(addItem, 6, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Unit);
			}
		}

		if(DMode==0 && SType==3)//�ֶ�ģʽ�����ͱ����б���ʾ
		{
			ProType=3;
			for(int i=0; i<=FDG_FACT_SELECT[ProType]; i++)//ÿ�ֿ��������м�������
			{
				index=FDG_Select[ProType][i];//
				addItem = listArray[0]->InsertItem(i, Str(i), 0);
				listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Type);//?
				listArray[0]->SetItemText(addItem, 1, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Name);
				if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 255)
				{
					listArray[0]->SetItemText(addItem, 2, "����");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 1)
				{
					listArray[0]->SetItemText(addItem, 2, "�澯");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 0)
				{
					listArray[0]->SetItemText(addItem, 2, "�˳�");
				}
				listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Value));
				listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time1));
				listArray[0]->SetItemText(addItem, 5, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time2));
				listArray[0]->SetItemText(addItem, 6, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Unit);
			}
		}

		if(DMode==1)//����ģʽ�����б���ʾ
		{
			ProType=4;
			for(int i=0; i<=FDG_FACT_SELECT[ProType]; i++)//ÿ�ֿ��������м�������
			{
				index=FDG_Select[ProType][i];//
				addItem = listArray[0]->InsertItem(i, Str(i), 0);
				listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Type);//?
				listArray[0]->SetItemText(addItem, 1, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Name);
				if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 255)
				{
					listArray[0]->SetItemText(addItem, 2, "����");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 1)
				{
					listArray[0]->SetItemText(addItem, 2, "�澯");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 0)
				{
					listArray[0]->SetItemText(addItem, 2, "�˳�");
				}
				listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Value));
				listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time1));
				listArray[0]->SetItemText(addItem, 5, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time2));
				listArray[0]->SetItemText(addItem, 6, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Unit);
			}
		}
	}
	else if(type ==1 || type ==2 || type ==3 || type ==4 || type==5 )
	{
		addItem = listArray[0]->InsertItem(0, Str(0), 0);
		listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Line);
		if(mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Enable == 255)
		{
			listArray[0]->SetItemText(addItem, 1, "Ͷ��");
		}
		else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Enable == 0)
		{
			listArray[0]->SetItemText(addItem, 1, "�˳�");
		}
		listArray[0]->SetItemText(addItem, 2, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Value));
		listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Time1));
		listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Time2));
		listArray[0]->SetItemText(addItem, 5, mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Unit);
	}

	else if(type ==6 || type ==7 || type ==8)
	{
		addItem = listArray[0]->InsertItem(0, Str(0), 0);
		listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Line);
		if(mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Enable == 255)
		{
			listArray[0]->SetItemText(addItem, 1, "Ͷ��");
		}
		else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Enable == 0)
		{
			listArray[0]->SetItemText(addItem, 1, "�˳�");
		}
		listArray[0]->SetItemText(addItem, 2, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Value));
		listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Time1));//����ʱ��ע���±�����item��һ��
		listArray[0]->SetItemText(addItem, 4, mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Unit);

	}
	else if(type ==9)//��ѹʱ���߼�����list����
	{
		LjNum=mPzkIni.FDGFileTemp.Cfg.VTimePerLine;
		for(int i=0; i<LjNum; i++)//ÿ�ֿ��������м������� <=?
			{
				addItem = listArray[0]->InsertItem(i, Str(i), 0);
				listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Type);//?
				listArray[0]->SetItemText(addItem, 1, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Name);
				if(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Enable == 255)
				{
					listArray[0]->SetItemText(addItem, 2, "Ͷ��");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Enable == 0)
				{
					listArray[0]->SetItemText(addItem, 2, "�˳�");
				}
				listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Value));
				listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Time1));
				listArray[0]->SetItemText(addItem, 5, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Time2));
				listArray[0]->SetItemText(addItem, 6, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Unit);
			}
	}

	else if(type ==10)//��ѹ�����߼�����list����
	{
		LjNum=mPzkIni.FDGFileTemp.Cfg.VITimePerLine;
		for(int i=0; i<=LjNum; i++)//ÿ�ֿ��������м������� <=?
			{
				addItem = listArray[0]->InsertItem(i, Str(i), 0);
				listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Type);//?
				listArray[0]->SetItemText(addItem, 1, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Name);
				if(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Enable == 255)
				{
					listArray[0]->SetItemText(addItem, 2, "Ͷ��");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Enable == 0)
				{
					listArray[0]->SetItemText(addItem, 2, "�˳�");
				}
				listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Value));
				listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Time1));
				listArray[0]->SetItemText(addItem, 5, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Time2));
				listArray[0]->SetItemText(addItem, 6, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Unit);
			}
	}

	else if(type ==11)//����Ӧ�ۺ��߼�����list����
	{
		LjNum=mPzkIni.FDGFileTemp.Cfg.SelfAdaptionPerLine;
		for(int i=0; i<LjNum; i++)//ÿ�ֿ��������м������� <=?
			{
				addItem = listArray[0]->InsertItem(i, Str(i), 0);
				listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Type);//?
				listArray[0]->SetItemText(addItem, 1, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Name);
				if(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Enable == 255)
				{
					listArray[0]->SetItemText(addItem, 2, "Ͷ��");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Enable == 0)
				{
					listArray[0]->SetItemText(addItem, 2, "�˳�");
				}
				listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Value));
				listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Time1));
				listArray[0]->SetItemText(addItem, 5, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Time2));
				listArray[0]->SetItemText(addItem, 6, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Unit);
			}
	}

	else if(type ==12)//�����բ�߼�����list����
	{
		LjNum=mPzkIni.FDGFileTemp.Cfg.LLSwitchPerLine;
		for(int i=0; i<LjNum; i++)//ÿ�ֿ��������м������� <=?
			{
				addItem = listArray[0]->InsertItem(i, Str(i), 0);
				listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Type);//?
				listArray[0]->SetItemText(addItem, 1, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Name);
				if(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Enable == 255)
				{
					listArray[0]->SetItemText(addItem, 2, "Ͷ��");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Enable == 0)
				{
					listArray[0]->SetItemText(addItem, 2, "�˳�");
				}
				listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Value));
				listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Time1));
				listArray[0]->SetItemText(addItem, 5, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Time2));
				listArray[0]->SetItemText(addItem, 6, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Unit);
			}
	}

  UpdateData(UPDATE_WRITE);

}

void CFDGCfgView::InitListCtrl()
{
	int i=0;
	CSize sz;
	sz.cx = sz.cy = 30;
//	listArray[0] = &m_List1;
	int type = m_FDGType.GetCurSel();

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
		listArray[0]->InsertColumn(i++, "���", LVCFMT_LEFT, 45, -1);//i++Ϊ�кţ����ݣ����У����
		listArray[0]->InsertColumn(i++, "����", LVCFMT_LEFT, 160, -1);
		listArray[0]->InsertColumn(i++, "����/�澯", LVCFMT_CENTER, 85, -1);
		listArray[0]->InsertColumn(i++, "��ֵ", LVCFMT_CENTER, 90, -1);
		listArray[0]->InsertColumn(i++, "ʱ��1", LVCFMT_CENTER, 90, -1);
		listArray[0]->InsertColumn(i++, "ʱ��2", LVCFMT_CENTER, 90, -1);
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
	else if(type ==6 || type ==7 || type ==8)
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
	else if(type ==9 || type ==10 || type ==11 || type==12)
	{
		listArray[0]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		listArray[0]->ApproximateViewRect(sz,1);
		listArray[0]->InsertColumn(i++, "���", LVCFMT_LEFT, 45, -1);//i++Ϊ�кţ����ݣ����У����
		listArray[0]->InsertColumn(i++, "����", LVCFMT_LEFT, 160, -1);
		listArray[0]->InsertColumn(i++, "Ͷ��/�˳�", LVCFMT_CENTER, 85, -1);
		listArray[0]->InsertColumn(i++, "��ֵ", LVCFMT_CENTER, 90, -1);
		listArray[0]->InsertColumn(i++, "ʱ��1", LVCFMT_CENTER, 90, -1);
		listArray[0]->InsertColumn(i++, "ʱ��2", LVCFMT_CENTER, 90, -1);
		listArray[0]->InsertColumn(i++, "��ֵ��λ/��ע", LVCFMT_CENTER, 141, -1);
	//	AfxMessageBox("44444444444");
	}


	CRect rect;//?
	listArray[0]->GetWindowRect(&rect);//�ú�������ָ�����ڵı߿���εĳߴ硣�óߴ����������Ļ�������Ͻǵ���Ļ���������

	rect.top -= 80;
	rect.bottom -= 80;

	LoadFDGConfig();
}

void CFDGCfgView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	memcpy(&(mPzkIni.FDGFileTemp),&(mPzkIni.FDGFile),sizeof(FDGCfgStru));

	GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);

	GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK6)->EnableWindow(FALSE);

	m_FDGType.ResetContent();//Removes all items from a list box.
	m_FDGType.AddString("������ֵ�趨");
	m_FDGType.AddString("������·-Խ�޸澯��ֵ�趨");//�������ͣ���Ͽ��б��combo1
	m_FDGType.AddString("��ѹ��·-Խ�޸澯��ֵ�趨");
	m_FDGType.AddString("���������·-Խ�޸澯��ֵ�趨");
	m_FDGType.AddString("�����ѹ��·-Խ�޸澯��ֵ�趨");
	m_FDGType.AddString("�����ɸ澯��ֵ�趨");
	m_FDGType.AddString("����·I�ι�������");
	m_FDGType.AddString("����·II�ι�������");
	m_FDGType.AddString("����ӵع�������");
	m_FDGType.AddString("��ѹʱ�����߼�����");
	m_FDGType.AddString("��ѹ�������߼�����");
	m_FDGType.AddString("����Ӧ�ۺ����߼�����");
	m_FDGType.AddString("�����բ�߼�����");
	m_FDGType.SetCurSel(0);

	m_Enable.ResetContent();//������ֵ�趨�� �����澯Ͷ����Ͽ��б��combo2
	m_Enable.AddString("����");
	m_Enable.AddString("�澯");
	m_Enable.AddString("�˳�");
	m_Enable.SetCurSel(0);

	GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO3)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO4)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO5)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO6)->EnableWindow(TRUE);

///////////���߷�ʽ/////////////////////////////////////////////////////

	if(CMode==0)
		((CButton *)GetDlgItem(IDC_RADIO13))->SetCheck(1);
	else if(CMode ==1)
		((CButton *)GetDlgItem(IDC_RADIO14))->SetCheck(1);
	else
		((CButton *)GetDlgItem(IDC_RADIO15))->SetCheck(1);

///////////ʹ��/////////////////////////////////////////////////////

	if(mPzkIni.FDGFileTemp.Cfg.Prot_YXEnable == 255)//������ң��ʹ��
	{
		m_Check1 = true;//IDC_CHECK1��ֵ
	}
	else
	{
		m_Check1 = false;
	}
	if(mPzkIni.FDGFileTemp.Cfg.Prot_MsgEnable == 255)//������Ϣ�ϱ�ʹ��
	{
		m_Check2 = true;
	}
	else
	{
		m_Check2 = false;
	}
	if(mPzkIni.FDGFileTemp.Cfg.Flt_RcwEnable == 255)//����¼��ʹ��
	{
		m_Check3 = true;
	}
	else
	{
		m_Check3 = false;
	}
	if(mPzkIni.FDGFileTemp.Cfg.Byd_SOEEnable == 255)//Խ�޸澯SOEʹ��
	{
		m_Check4 = true;
	}
	else
	{
		m_Check4 = false;
	}
	if(mPzkIni.FDGFileTemp.Cfg.Flt_YXEnable == 255)//���ϼ������ϱ�ʹ��
	{
		m_Check5 = true;
	}
	else
	{
		m_Check5 = false;
	}
	if(mPzkIni.FDGFileTemp.Cfg.Flt_RepEnable == 255)//���ϱ����ϱ�ʹ��
	{
		m_Check6 = true;
	}
	else
	{
		m_Check6 = false;
	}

/////////////������ģʽ////////////

	DMode=mPzkIni.FDGFileTemp.Cfg.DeviceMode;
	if(DMode==0)//�ֶ�ģʽ
	{
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	}
	else//����ģʽ
	{
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(1);
	}

////////////����������//////////////////////////////

	SType=mPzkIni.FDGFileTemp.Cfg.SelectType;
	if(SType==0)//��ѹʱ����
	{
		((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(1);
	}
	else if(SType==1)//��ѹ������
	{
		((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(1);
	}
	else if(SType==2)//����Ӧ��
	{
		((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(1);
	}
	else//������
	{
		((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(1);
	}

////////////����Ӧ�ۺ���ģʽ//////////////////////////

	AType=mPzkIni.FDGFileTemp.Cfg.AdpSmlType;
	if(AType==0)//ѡ��ģʽ
	{
		((CButton*)GetDlgItem(IDC_RADIO7))->SetCheck(1);
	}
	else if(AType==1)//ѡ��ģʽ
	{
		((CButton*)GetDlgItem(IDC_RADIO8))->SetCheck(1);
	}
	else			//��֧��ģʽ
	{
		((CButton*)GetDlgItem(IDC_RADIO9))->SetCheck(1);
	}

////////////��������///////////////////////////////////

	SwType=mPzkIni.FDGFileTemp.Cfg.SwitchType;
	if(SwType==0)//��·��
	{
		((CButton*)GetDlgItem(IDC_RADIO10))->SetCheck(1);
	}
	else if(SwType==1)//���ɿ���
	{
		((CButton*)GetDlgItem(IDC_RADIO11))->SetCheck(1);
	}
	else			//��ϵ���
	{
		((CButton*)GetDlgItem(IDC_RADIO12))->SetCheck(1);
	}

	UpdateData(UPDATE_WRITE);//ֵ���µ��ؼ�
	UpdateData(UPDATE_READ);//�ؼ���ֵ���µ�����
	InitListCtrl();//���ó�ʼ���б����
}

LRESULT CFDGCfgView::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)//?
{
//	OnCANCEl();
	return TRUE;
}

LRESULT CFDGCfgView::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)//?
{
	if(bEverEdited)//true or false
	{
		int i = AfxMessageBox("���浱ǰ�Ա����������������޸���",MB_YESNOCANCEL);
		if(i == IDYES)
			OnButton2();
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
// CFDGCfgView message handlers

void CFDGCfgView::OnRadio1()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	int type = m_FDGType.GetCurSel();
	mPzkIni.FDGFileTemp.Cfg.DeviceMode=0;
	DMode=0;
 	LoadFDGConfig();
}

void CFDGCfgView::OnRadio2()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	int type = m_FDGType.GetCurSel();
	mPzkIni.FDGFileTemp.Cfg.DeviceMode=1;
	DMode=1;
 	LoadFDGConfig();
}

void CFDGCfgView::OnRadio3()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	int type = m_FDGType.GetCurSel();
	mPzkIni.FDGFileTemp.Cfg.SelectType=0;
	SType=0;
	GetDlgItem(IDC_RADIO7)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO8)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO9)->EnableWindow(FALSE);
	LoadFDGConfig();
}

void CFDGCfgView::OnRadio4()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	int type = m_FDGType.GetCurSel();
	mPzkIni.FDGFileTemp.Cfg.SelectType=1;
	SType=1;
	GetDlgItem(IDC_RADIO7)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO8)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO9)->EnableWindow(FALSE);
	LoadFDGConfig();
}

void CFDGCfgView::OnRadio5()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	int type = m_FDGType.GetCurSel();
	mPzkIni.FDGFileTemp.Cfg.SelectType=2;
	SType=2;
	GetDlgItem(IDC_RADIO7)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO8)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO9)->EnableWindow(TRUE);
	LoadFDGConfig();
}

void CFDGCfgView::OnRadio6()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	int type = m_FDGType.GetCurSel();
	mPzkIni.FDGFileTemp.Cfg.SelectType=3;
	SType=3;
	GetDlgItem(IDC_RADIO7)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO8)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO9)->EnableWindow(FALSE);
	LoadFDGConfig();
}

void CFDGCfgView::OnRadio7()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	mPzkIni.FDGFileTemp.Cfg.AdpSmlType=0;
}

void CFDGCfgView::OnRadio8()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	mPzkIni.FDGFileTemp.Cfg.AdpSmlType=1;
}

void CFDGCfgView::OnRadio9()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	mPzkIni.FDGFileTemp.Cfg.AdpSmlType=2;
}

void CFDGCfgView::OnRadio10()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	mPzkIni.FDGFileTemp.Cfg.SwitchType=0;
}

void CFDGCfgView::OnRadio11()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	mPzkIni.FDGFileTemp.Cfg.SwitchType=1;
}

void CFDGCfgView::OnRadio12()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	mPzkIni.FDGFileTemp.Cfg.SwitchType=2;
}

void CFDGCfgView::OnCheck1() //������ң��ʹ��
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	UpdateData(true);//���浽�ؼ�����
	if(m_Check1 == true)
	{
		mPzkIni.FDGFileTemp.Cfg.Prot_YXEnable=255;
	}
	else
	{
		mPzkIni.FDGFileTemp.Cfg.Prot_YXEnable=0;
	}
}

void CFDGCfgView::OnCheck2() //������Ϣ�ϱ�ʹ��
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	UpdateData(true);//���浽�ؼ�����
	if(m_Check2 == true)
	{
		mPzkIni.FDGFileTemp.Cfg.Prot_MsgEnable=255;
	}
	else
	{
		mPzkIni.FDGFileTemp.Cfg.Prot_MsgEnable=0;
	}
}

void CFDGCfgView::OnCheck3() //����¼��ʹ��
{
	// TODO: Add your control notification handler code here

	bEverEdited = true;
	UpdateData(true);//���浽�ؼ�����
	if(m_Check3 == true)
	{
		mPzkIni.FDGFileTemp.Cfg.Flt_RcwEnable=255;
	}
	else
	{
		mPzkIni.FDGFileTemp.Cfg.Flt_RcwEnable=0;
	}
}

void CFDGCfgView::OnCheck4()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	UpdateData(true);//���浽�ؼ�����
	if(m_Check4 == true)
	{
		mPzkIni.FDGFileTemp.Cfg.Byd_SOEEnable=255;
	}
	else
	{
		mPzkIni.FDGFileTemp.Cfg.Byd_SOEEnable=0;
	}
}

void CFDGCfgView::OnCheck5()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	UpdateData(true);//���浽����
	if(m_Check5 == true)
	{
		mPzkIni.FDGFileTemp.Cfg.Flt_YXEnable=255;
	}
	else
	{
		mPzkIni.FDGFileTemp.Cfg.Flt_YXEnable=0;
	}
}

void CFDGCfgView::OnCheck6()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	UpdateData(true);//���浽����
	if(m_Check6 == true)
	{
		mPzkIni.FDGFileTemp.Cfg.Flt_RepEnable=255;
	}
	else
	{
		mPzkIni.FDGFileTemp.Cfg.Flt_RepEnable=0;
	}
}

void CFDGCfgView::OnRadio13()
{
	// TODO: Add your control notification handler code here

	bEverEdited = true;
	mPzkIni.FDGFileTemp.Cfg.V_ConnectMode=0;
}

void CFDGCfgView::OnRadio14()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	mPzkIni.FDGFileTemp.Cfg.V_ConnectMode=1;
}

void CFDGCfgView::OnRadio15()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	mPzkIni.FDGFileTemp.Cfg.V_ConnectMode=2;
}


void CFDGCfgView::OnChangeEdit1()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
	UpdateData(true);
	mPzkIni.FDGFile.Cfg.FixActTime=m_FixActTime;
}

void CFDGCfgView::OnKillfocusEdit1()
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

void CFDGCfgView::OnButton1()
{
	// TODO: Add your control notification handler code here
	int j;
	int i = m_FDGType.GetCurSel();//�õ���ǰ��������
	if(i == 0 )
	{

		for(j=0;j<mPzkIni.FDGFileTemp.Cfg.ProtNumPerLine;j++)
		{
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Type = mPzkIni.FDGFile.Line[i].FDGItem[j].Type;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Name = mPzkIni.FDGFile.Line[i].FDGItem[j].Name;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Enable=mPzkIni.FDGFile.Line[i].FDGItem[j].Enable;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Value =mPzkIni.FDGFile.Line[i].FDGItem[j].Value;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time1 = mPzkIni.FDGFile.Line[i].FDGItem[j].Time1;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time2 = mPzkIni.FDGFile.Line[i].FDGItem[j].Time2;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Unit = mPzkIni.FDGFile.Line[i].FDGItem[j].Unit;
		}
	}
	else if(i ==1 || i ==2 || i ==3 || i ==4 || i==5 )
	{
		mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Line = mPzkIni.FDGFile.Line[i].FDGItem[0].Line;
		mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Enable=mPzkIni.FDGFile.Line[i].FDGItem[0].Enable;
		mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Value = mPzkIni.FDGFile.Line[i].FDGItem[0].Value;
		mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Time1 = mPzkIni.FDGFile.Line[i].FDGItem[0].Time1;
		mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Time2 = mPzkIni.FDGFile.Line[i].FDGItem[0].Time2;
		mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Unit = mPzkIni.FDGFile.Line[i].FDGItem[0].Unit;
	}
	else if(i == 6 || i == 7 || i == 8 )
	{
		mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Line = mPzkIni.FDGFile.Line[i].FDGItem[0].Line;
		mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Enable=mPzkIni.FDGFile.Line[i].FDGItem[0].Enable;
		mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Value = mPzkIni.FDGFile.Line[i].FDGItem[0].Value;
		mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Time1 = mPzkIni.FDGFile.Line[i].FDGItem[0].Time1;
		mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Unit = mPzkIni.FDGFile.Line[i].FDGItem[0].Unit;
	}
	else if(i == 9)
	{
		for(j=0;j<mPzkIni.FDGFileTemp.Cfg.VTimePerLine;j++)
		{
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Type = mPzkIni.FDGFile.Line[i].FDGItem[j].Type;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Name = mPzkIni.FDGFile.Line[i].FDGItem[j].Name;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Enable=mPzkIni.FDGFile.Line[i].FDGItem[j].Enable;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Value =mPzkIni.FDGFile.Line[i].FDGItem[j].Value;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time1 = mPzkIni.FDGFile.Line[i].FDGItem[j].Time1;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time2 = mPzkIni.FDGFile.Line[i].FDGItem[j].Time2;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Unit = mPzkIni.FDGFile.Line[i].FDGItem[j].Unit;
		}
	}
	else if(i == 10)
	{
		for(j=0;j<mPzkIni.FDGFileTemp.Cfg.VITimePerLine;j++)
		{
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Type = mPzkIni.FDGFile.Line[i].FDGItem[j].Type;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Name = mPzkIni.FDGFile.Line[i].FDGItem[j].Name;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Enable=mPzkIni.FDGFile.Line[i].FDGItem[j].Enable;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Value =mPzkIni.FDGFile.Line[i].FDGItem[j].Value;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time1 = mPzkIni.FDGFile.Line[i].FDGItem[j].Time1;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time2 = mPzkIni.FDGFile.Line[i].FDGItem[j].Time2;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Unit = mPzkIni.FDGFile.Line[i].FDGItem[j].Unit;
		}
	}
	else if(i == 11)
	{
		for(j=0;j<mPzkIni.FDGFileTemp.Cfg.SelfAdaptionPerLine;j++)
		{
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Type = mPzkIni.FDGFile.Line[i].FDGItem[j].Type;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Name = mPzkIni.FDGFile.Line[i].FDGItem[j].Name;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Enable=mPzkIni.FDGFile.Line[i].FDGItem[j].Enable;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Value =mPzkIni.FDGFile.Line[i].FDGItem[j].Value;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time1 = mPzkIni.FDGFile.Line[i].FDGItem[j].Time1;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time2 = mPzkIni.FDGFile.Line[i].FDGItem[j].Time2;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Unit = mPzkIni.FDGFile.Line[i].FDGItem[j].Unit;
		}
	}
	else if(i == 12)
	{
		for(j=0;j<mPzkIni.FDGFileTemp.Cfg.LLSwitchPerLine;j++)
		{
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Type = mPzkIni.FDGFile.Line[i].FDGItem[j].Type;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Name = mPzkIni.FDGFile.Line[i].FDGItem[j].Name;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Enable=mPzkIni.FDGFile.Line[i].FDGItem[j].Enable;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Value =mPzkIni.FDGFile.Line[i].FDGItem[j].Value;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time1 = mPzkIni.FDGFile.Line[i].FDGItem[j].Time1;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time2 = mPzkIni.FDGFile.Line[i].FDGItem[j].Time2;
			mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Unit = mPzkIni.FDGFile.Line[i].FDGItem[j].Unit;
		}
	}
	LoadFDGConfig();
}

void CFDGCfgView::OnButton2()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);//���浽����
	mPzkIni.FDGFile.Cfg.SwitchType=mPzkIni.FDGFileTemp.Cfg.SwitchType;
	mPzkIni.FDGFile.Cfg.DeviceMode=mPzkIni.FDGFileTemp.Cfg.DeviceMode;
	mPzkIni.FDGFile.Cfg.SelectType=mPzkIni.FDGFileTemp.Cfg.SelectType;
	mPzkIni.FDGFile.Cfg.AdpSmlType=	mPzkIni.FDGFileTemp.Cfg.AdpSmlType;
	mPzkIni.FDGFile.Cfg.V_ConnectMode=mPzkIni.FDGFileTemp.Cfg.V_ConnectMode;
	mPzkIni.FDGFile.Cfg.Prot_YXEnable=mPzkIni.FDGFileTemp.Cfg.Prot_YXEnable;//������ң��ʹ��
	mPzkIni.FDGFile.Cfg.Prot_MsgEnable=mPzkIni.FDGFileTemp.Cfg.Prot_MsgEnable;//������Ϣ�ϱ�ʹ��
	mPzkIni.FDGFile.Cfg.Byd_SOEEnable=mPzkIni.FDGFileTemp.Cfg.Byd_SOEEnable;//Խ�޸澯SOEʹ��
	mPzkIni.FDGFile.Cfg.Flt_YXEnable=mPzkIni.FDGFileTemp.Cfg.Flt_YXEnable;//���ϼ������ϱ�ʹ��
	mPzkIni.FDGFile.Cfg.Flt_RepEnable=mPzkIni.FDGFileTemp.Cfg.Flt_RepEnable;//���ϱ����ϱ�ʹ��
	mPzkIni.FDGFile.Cfg.Flt_RcwEnable=mPzkIni.FDGFileTemp.Cfg.Flt_RcwEnable;//����¼��ʹ��
	mPzkIni.FDGFile.Cfg.FixActTime=m_FixActTime; //������������ʱ��

	int i;
	int j;
	for(i=0;i<13;i++)
	{
		if(i == 0 )
		{
			for(j=0;j<mPzkIni.FDGFileTemp.Cfg.ProtNumPerLine;j++)//ȫ������һ�� 0-ÿ����·������
			{
				mPzkIni.FDGFile.Line[i].FDGItem[j].Type = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Type;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Name = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Name;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Enable=mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Enable;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Value =mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Value;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Time1 = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time1;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Time2 = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time2;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Unit = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Unit;
			}
		}
		else if(i ==1 || i ==2 || i ==3 || i ==4 || i==5 )
		{
			mPzkIni.FDGFile.Line[i].FDGItem[0].Line = mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Line;
			mPzkIni.FDGFile.Line[i].FDGItem[0].Enable=mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Enable;
			mPzkIni.FDGFile.Line[i].FDGItem[0].Value= mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Value;
			mPzkIni.FDGFile.Line[i].FDGItem[0].Time1= mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Time1;
			mPzkIni.FDGFile.Line[i].FDGItem[0].Time2= mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Time2;
			mPzkIni.FDGFile.Line[i].FDGItem[0].Unit = mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Unit;
		}
		else if(i == 6 || i == 7 || i == 8 )
		{
			mPzkIni.FDGFile.Line[i].FDGItem[0].Line = mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Line;
			mPzkIni.FDGFile.Line[i].FDGItem[0].Enable=mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Enable;
			mPzkIni.FDGFile.Line[i].FDGItem[0].Value= mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Value;
			mPzkIni.FDGFile.Line[i].FDGItem[0].Time1= mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Time1;
			mPzkIni.FDGFile.Line[i].FDGItem[0].Unit = mPzkIni.FDGFileTemp.Line[i].FDGItem[0].Unit;
		}
		else if(i == 9 )
		{
			for(j=0;j<mPzkIni.FDGFileTemp.Cfg.VTimePerLine;j++)
			{
				mPzkIni.FDGFile.Line[i].FDGItem[j].Type = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Type;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Name = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Name;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Enable=mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Enable;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Value =mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Value;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Time1 = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time1;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Time2 = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time2;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Unit = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Unit;
			}
		}
		else if(i == 10 )
		{
			for(j=0;j<mPzkIni.FDGFileTemp.Cfg.VITimePerLine;j++)
			{
				mPzkIni.FDGFile.Line[i].FDGItem[j].Type = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Type;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Name = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Name;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Enable=mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Enable;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Value =mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Value;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Time1 = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time1;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Time2 = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time2;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Unit = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Unit;
			}
		}
		else if(i == 11 )
		{
			for(j=0;j<mPzkIni.FDGFileTemp.Cfg.SelfAdaptionPerLine;j++)
			{
				mPzkIni.FDGFile.Line[i].FDGItem[j].Type = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Type;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Name = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Name;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Enable=mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Enable;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Value =mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Value;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Time1 = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time1;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Time2 = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time2;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Unit = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Unit;
			}
		}
		else if(i == 12 )
		{
			for(j=0;j<mPzkIni.FDGFileTemp.Cfg.LLSwitchPerLine;j++)
			{
				mPzkIni.FDGFile.Line[i].FDGItem[j].Type = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Type;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Name = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Name;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Enable=mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Enable;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Value =mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Value;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Time1 = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time1;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Time2 = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Time2;
				mPzkIni.FDGFile.Line[i].FDGItem[j].Unit = mPzkIni.FDGFileTemp.Line[i].FDGItem[j].Unit;
			}
		}
	}

		bEverEdited = false;
		mPzkIni.EverModified = true;
}

void CFDGCfgView::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult)
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
	if(nItem < 0)
		return;
	if(nSubItem == 0)
		return;
	int type = m_FDGType.GetCurSel();//����������Ͽ������� 0Ϊ������ֵ�趨
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
		else if(nSubItem == 3 || nSubItem == 4 || nSubItem == 5  )
		{
			pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT2);
			pCombo = (CComboBox *)GetDlgItem(IDC_EDIT2);
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
			pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT2);
			pCombo = (CComboBox *)GetDlgItem(IDC_EDIT2);
			m_Input.SetWindowText(m_List1.GetItemText(nItem, nSubItem));
		}
		else
			return;
	}

	else if(type ==6 || type ==7 || type ==8 )
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
			pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT2);
			pCombo = (CComboBox *)GetDlgItem(IDC_EDIT2);
			m_Input.SetWindowText(m_List1.GetItemText(nItem, nSubItem));
		}
		else
			return;
	}
	else if(type ==9 || type ==10 || type ==11 || type == 12 )
	{
		if(nSubItem == 2)
		{

			pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO2);
			pCombo = (CComboBox *)GetDlgItem(IDC_COMBO2);
			str = m_List1.GetItemText(nItem, nSubItem);
			if(str.Compare("Ͷ��") == 0)
				pCombo->SetCurSel(0);
			else if(str.Compare("�˳�") == 0)
				pCombo->SetCurSel(1);
		}
		else if(nSubItem == 3 || nSubItem == 4 || nSubItem == 5  )
		{
			pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT2);
			pCombo = (CComboBox *)GetDlgItem(IDC_EDIT2);
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

void CFDGCfgView::OnKillfocusEdit2()
{
	// TODO: Add your control notification handler code here

	CString str;
	m_Input.GetWindowText(str);
	listArray[0]->SetItemText(nItem, nSubItem, str);
	int type = m_FDGType.GetCurSel(), ProType, index;
	if(type == 0 )
	{
		if(DMode==0 && SType==0)//�ֶ�ģʽ��ѹʱ����
		{
			ProType=0;
			index = FDG_Select[ProType][nItem];
			if(nSubItem == 3)
			{
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Value=myatof(str);
			}
			else if(nSubItem == 4)
			{
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time1=myatof(str);
			}
			else if(nSubItem == 5)
			{
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time2=myatof(str);
			}
		}
		else if(DMode==0 && SType==1)//�ֶ�ģʽ��ѹ������
		{
			ProType=1;
			index = FDG_Select[ProType][nItem];
			if(nSubItem == 3)
			{
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Value=myatof(str);
			}
			else if(nSubItem == 4)
			{
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time1=myatof(str);
			}
			else if(nSubItem == 5)
			{
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time2=myatof(str);
			}

		}
		else if(DMode==0 && SType==2)//�ֶ�ģʽ����Ӧ�ۺ���
		{
			ProType=2;
			index = FDG_Select[ProType][nItem];
			if(nSubItem == 3)
			{
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Value=myatof(str);
			}
			else if(nSubItem == 4)
			{
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time1=myatof(str);
			}
			else if(nSubItem == 5)
			{
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time2=myatof(str);
			}

		}
		else if(DMode==0 && SType==3)//�ֶ�ģʽ������
		{
			ProType=3;
			index = FDG_Select[ProType][nItem];
			if(nSubItem == 3)
			{
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Value=myatof(str);
			}
			else if(nSubItem == 4)
			{
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time1=myatof(str);
			}
			else if(nSubItem == 5)
			{
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time2=myatof(str);
			}

		}
		else if(DMode==1)//�ֶ�ģʽ������
		{
			ProType=4;
			index = FDG_Select[ProType][nItem];
			if(nSubItem == 3)
			{
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Value=myatof(str);
			}
			else if(nSubItem == 4)
			{
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time1=myatof(str);
			}
			else if(nSubItem == 5)
			{
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time2=myatof(str);
			}

		}

	}
	else if(type ==1 || type ==2 || type ==3 || type ==4 || type==5 )
	{
		if(nSubItem == 2)
		{
			mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Value=myatof(str);
		}
		else if(nSubItem == 3)
		{
			mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Time1=myatof(str);
		}
		else if(nSubItem == 4)
		{
			mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Time2=myatof(str);
		}
	}
	else if(type == 6 || type == 7 || type == 8)
	{
		if(nSubItem == 2)
		{
			mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Value=myatof(str);
		}
		else if(nSubItem == 3)
		{
			mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Time1=myatof(str);
		}
	}

	else if(type == 9 || type == 10 || type == 11 || type == 12)
	{
		if(nSubItem == 3)
		{
			mPzkIni.FDGFileTemp.Line[type].FDGItem[nItem].Value=myatof(str);
		}
		else if(nSubItem == 4)
		{
			mPzkIni.FDGFileTemp.Line[type].FDGItem[nItem].Time1=myatof(str);
		}
		else if(nSubItem == 5)
		{
			mPzkIni.FDGFileTemp.Line[type].FDGItem[nItem].Time2=myatof(str);
		}
	}

	m_Input.ShowWindow(SW_HIDE);
	bEverEdited = true;

}


void CFDGCfgView::OnKillfocusCombo2()
{
	// TODO: Add your control notification handler code here

	int type = m_FDGType.GetCurSel(),index;
	int ProType;//�õ���ǰ��������
	//������������ĵ�ĳ�����ص��±�

	if(type == 0)
	{
		if(DMode==0 && SType==0)//�ֶ�ģʽ��ѹʱ����
		{
			ProType=0;
			index = FDG_Select[ProType][nItem];
			if(m_Enable.GetCurSel() == 0)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "����");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=255;
			}
			else if(m_Enable.GetCurSel() == 1)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "�澯");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=1;
			}
			else if(m_Enable.GetCurSel() == 2)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "�˳�");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=0;
			}
		}
		else if(DMode==0 && SType==1)//�ֶ�ģʽ��ѹ������
		{
			ProType=1;
			index = FDG_Select[ProType][nItem];
			if(m_Enable.GetCurSel() == 0)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "����");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=255;
			}
			else if(m_Enable.GetCurSel() == 1)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "�澯");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=1;
			}
			else if(m_Enable.GetCurSel() == 2)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "�˳�");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=0;
			}
		}
		else if(DMode==0 && SType==2)//�ֶ�ģʽ����Ӧ�ۺ���
		{
			ProType=2;
			index = FDG_Select[ProType][nItem];
			if(m_Enable.GetCurSel() == 0)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "����");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=255;
			}
			else if(m_Enable.GetCurSel() == 1)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "�澯");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=1;
			}
			else if(m_Enable.GetCurSel() == 2)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "�˳�");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=0;
			}
		}
		else if(DMode==0 && SType==3)//�ֶ�ģʽ������
		{
			ProType=3;
			index = FDG_Select[ProType][nItem];
			if(m_Enable.GetCurSel() == 0)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "����");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=255;
			}
			else if(m_Enable.GetCurSel() == 1)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "�澯");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=1;
			}
			else if(m_Enable.GetCurSel() == 2)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "�˳�");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=0;
			}
		}
		else if(DMode==1)//����ģʽ����
		{
			ProType=4;
			index = FDG_Select[ProType][nItem];
			if(m_Enable.GetCurSel() == 0)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "����");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=255;
			}
			else if(m_Enable.GetCurSel() == 1)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "�澯");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=1;
			}
			else if(m_Enable.GetCurSel() == 2)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "�˳�");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=0;
			}
		}
	}
	else if(type == 9 || type == 10 || type == 11 || type == 12)
	{
		if(m_Enable.GetCurSel() == 0)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "Ͷ��");
			mPzkIni.FDGFileTemp.Line[type].FDGItem[nItem].Enable=255;
		}
		else if(m_Enable.GetCurSel() == 1)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "�˳�");
			mPzkIni.FDGFileTemp.Line[type].FDGItem[nItem].Enable=0;
		}

	}
	else
	{
		if(m_Enable.GetCurSel() == 0)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "Ͷ��");
			mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Enable=255;
		}
		else if(m_Enable.GetCurSel() == 1)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "�˳�");
			mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Enable=0;
		}

	}

	m_Enable.ShowWindow(SW_HIDE);
	bEverEdited = true;

}

void CFDGCfgView::OnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	int type = m_FDGType.GetCurSel();
	if(type ==0)//radio �������ͼ������ֹ
	{
		m_Enable.ResetContent();
		m_Enable.AddString("����");
		m_Enable.AddString("�澯");
		m_Enable.AddString("�˳�");

	}
	else
	{
		m_Enable.ResetContent();
		m_Enable.AddString("Ͷ��");
		m_Enable.AddString("�˳�");

	}

	if(type == 0)// ����  ��ѡ�򼤻����ֹ
	{
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(FALSE);

		GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);

	}
	else if(type >=1 && type <=5 )//�澯 3
	{
		GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(FALSE);

		GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
	}
	else if( type == 6 || type == 7 || type == 8 )//����
	{
		GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);

		GetDlgItem(IDC_CHECK6)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(TRUE);
	}
	else if( type == 9 )//
	{

		if( DMode != 0 || SType !=0 )
		{
			AfxMessageBox("�˿��������Ͳ���Ҫ���ô���");
		}
		GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(FALSE);

	}
	else if( type == 10 )//
	{

		if( DMode != 0 || SType !=1 )
		{
			AfxMessageBox("�˿��������Ͳ���Ҫ���ô���");
		}
		GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(FALSE);
	}

	else if( type == 11 )//
	{

		if( DMode != 0 || SType !=2 )
		{
			AfxMessageBox("�˿��������Ͳ���Ҫ���ô���");
		}
		GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(FALSE);
	}
	else if( type == 12 )//
	{
		if( DMode != 1 )
		{
			AfxMessageBox("�˿��������Ͳ���Ҫ���ô���");
		}
		GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(FALSE);
	}

	InitListCtrl();//
}
