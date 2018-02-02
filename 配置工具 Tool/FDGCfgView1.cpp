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

extern int FDG_Select[FDG_MODE_KIND][FDG_SELECT];//分段狗 读取prot_select里面的数据到数组
extern int FDG_FACT_SELECT[FDG_SELECT];//每种类型保护数量

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
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)//消息ID和映射message的函数-拷贝4-16
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)//它的作用是绑定一个自定义的消息和该消息的响应函数。拷贝4-16

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
	int type = m_FDGType.GetCurSel();//故障类型组合框内容项 0为保护定值设定
	if(type ==0)
	{
		if(DMode==0 && SType==0)//分段模式电压时间型保护列表显示
		{
			ProType=0;
			for(int i=0; i<FDG_FACT_SELECT[ProType]; i++)//每种开关类型有几个数据 <=right?
			{
				index=FDG_Select[ProType][i];//ProType：5种保护类型 i:第几个数据
				addItem = listArray[0]->InsertItem(i, Str(i), 0);
				listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Type);//?
				listArray[0]->SetItemText(addItem, 1, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Name);
				if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 255)
				{
					listArray[0]->SetItemText(addItem, 2, "动作");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 1)
				{
					listArray[0]->SetItemText(addItem, 2, "告警");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 0)
				{
					listArray[0]->SetItemText(addItem, 2, "退出");
				}
				listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Value));
				listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time1));
				listArray[0]->SetItemText(addItem, 5, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time2));
				listArray[0]->SetItemText(addItem, 6, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Unit);
			}
		}

		if(DMode==0 && SType==1)//分段模式电压电流时间型保护列表显示
		{
			ProType=1;
			for(int i=0; i<FDG_FACT_SELECT[ProType]; i++)//每种开关类型有几个数据
			{
				index=FDG_Select[ProType][i];//
				addItem = listArray[0]->InsertItem(i, Str(i), 0);
				listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Type);//?
				listArray[0]->SetItemText(addItem, 1, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Name);
				if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 255)
				{
					listArray[0]->SetItemText(addItem, 2, "动作");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 1)
				{
					listArray[0]->SetItemText(addItem, 2, "告警");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 0)
				{
					listArray[0]->SetItemText(addItem, 2, "退出");
				}
				listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Value));
				listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time1));
				listArray[0]->SetItemText(addItem, 5, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time2));
				listArray[0]->SetItemText(addItem, 6, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Unit);
			}
		}

		if(DMode==0 && SType==2)//分段模式自适应综合型型保护列表显示
		{
			ProType=2;
			for(int i=0; i<FDG_FACT_SELECT[ProType]; i++)//每种开关类型有几个数据
			{
				index=FDG_Select[ProType][i];
				addItem = listArray[0]->InsertItem(i, Str(i), 0);
				listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Type);//?
				listArray[0]->SetItemText(addItem, 1, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Name);
				if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 255)
				{
					listArray[0]->SetItemText(addItem, 2, "动作");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 1)
				{
					listArray[0]->SetItemText(addItem, 2, "告警");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 0)
				{
					listArray[0]->SetItemText(addItem, 2, "退出");
				}
				listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Value));
				listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time1));
				listArray[0]->SetItemText(addItem, 5, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time2));
				listArray[0]->SetItemText(addItem, 6, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Unit);
			}
		}

		if(DMode==0 && SType==3)//分段模式电流型保护列表显示
		{
			ProType=3;
			for(int i=0; i<=FDG_FACT_SELECT[ProType]; i++)//每种开关类型有几个数据
			{
				index=FDG_Select[ProType][i];//
				addItem = listArray[0]->InsertItem(i, Str(i), 0);
				listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Type);//?
				listArray[0]->SetItemText(addItem, 1, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Name);
				if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 255)
				{
					listArray[0]->SetItemText(addItem, 2, "动作");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 1)
				{
					listArray[0]->SetItemText(addItem, 2, "告警");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 0)
				{
					listArray[0]->SetItemText(addItem, 2, "退出");
				}
				listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Value));
				listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time1));
				listArray[0]->SetItemText(addItem, 5, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Time2));
				listArray[0]->SetItemText(addItem, 6, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Unit);
			}
		}

		if(DMode==1)//联络模式保护列表显示
		{
			ProType=4;
			for(int i=0; i<=FDG_FACT_SELECT[ProType]; i++)//每种开关类型有几个数据
			{
				index=FDG_Select[ProType][i];//
				addItem = listArray[0]->InsertItem(i, Str(i), 0);
				listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Type);//?
				listArray[0]->SetItemText(addItem, 1, mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Name);
				if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 255)
				{
					listArray[0]->SetItemText(addItem, 2, "动作");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 1)
				{
					listArray[0]->SetItemText(addItem, 2, "告警");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable == 0)
				{
					listArray[0]->SetItemText(addItem, 2, "退出");
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
			listArray[0]->SetItemText(addItem, 1, "投入");
		}
		else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Enable == 0)
		{
			listArray[0]->SetItemText(addItem, 1, "退出");
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
			listArray[0]->SetItemText(addItem, 1, "投入");
		}
		else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Enable == 0)
		{
			listArray[0]->SetItemText(addItem, 1, "退出");
		}
		listArray[0]->SetItemText(addItem, 2, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Value));
		listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Time1));//读的时候注意下比其他item少一个
		listArray[0]->SetItemText(addItem, 4, mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Unit);

	}
	else if(type ==9)//电压时间逻辑配置list数据
	{
		LjNum=mPzkIni.FDGFileTemp.Cfg.VTimePerLine;
		for(int i=0; i<LjNum; i++)//每种开关类型有几个数据 <=?
			{
				addItem = listArray[0]->InsertItem(i, Str(i), 0);
				listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Type);//?
				listArray[0]->SetItemText(addItem, 1, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Name);
				if(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Enable == 255)
				{
					listArray[0]->SetItemText(addItem, 2, "投入");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Enable == 0)
				{
					listArray[0]->SetItemText(addItem, 2, "退出");
				}
				listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Value));
				listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Time1));
				listArray[0]->SetItemText(addItem, 5, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Time2));
				listArray[0]->SetItemText(addItem, 6, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Unit);
			}
	}

	else if(type ==10)//电压电流逻辑配置list数据
	{
		LjNum=mPzkIni.FDGFileTemp.Cfg.VITimePerLine;
		for(int i=0; i<=LjNum; i++)//每种开关类型有几个数据 <=?
			{
				addItem = listArray[0]->InsertItem(i, Str(i), 0);
				listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Type);//?
				listArray[0]->SetItemText(addItem, 1, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Name);
				if(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Enable == 255)
				{
					listArray[0]->SetItemText(addItem, 2, "投入");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Enable == 0)
				{
					listArray[0]->SetItemText(addItem, 2, "退出");
				}
				listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Value));
				listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Time1));
				listArray[0]->SetItemText(addItem, 5, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Time2));
				listArray[0]->SetItemText(addItem, 6, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Unit);
			}
	}

	else if(type ==11)//自适应综合逻辑配置list数据
	{
		LjNum=mPzkIni.FDGFileTemp.Cfg.SelfAdaptionPerLine;
		for(int i=0; i<LjNum; i++)//每种开关类型有几个数据 <=?
			{
				addItem = listArray[0]->InsertItem(i, Str(i), 0);
				listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Type);//?
				listArray[0]->SetItemText(addItem, 1, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Name);
				if(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Enable == 255)
				{
					listArray[0]->SetItemText(addItem, 2, "投入");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Enable == 0)
				{
					listArray[0]->SetItemText(addItem, 2, "退出");
				}
				listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Value));
				listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Time1));
				listArray[0]->SetItemText(addItem, 5, Str(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Time2));
				listArray[0]->SetItemText(addItem, 6, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Unit);
			}
	}

	else if(type ==12)//联络合闸逻辑配置list数据
	{
		LjNum=mPzkIni.FDGFileTemp.Cfg.LLSwitchPerLine;
		for(int i=0; i<LjNum; i++)//每种开关类型有几个数据 <=?
			{
				addItem = listArray[0]->InsertItem(i, Str(i), 0);
				listArray[0]->SetItemData(addItem, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Type);//?
				listArray[0]->SetItemText(addItem, 1, mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Name);
				if(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Enable == 255)
				{
					listArray[0]->SetItemText(addItem, 2, "投入");
				}
				else if(mPzkIni.FDGFileTemp.Line[type].FDGItem[i].Enable == 0)
				{
					listArray[0]->SetItemText(addItem, 2, "退出");
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

/***********清空，否则会产生下拉框*************/
/********http://bbs.csdn.net/topics/50390421*******/

	m_List1.DeleteAllItems();//首先清空listview
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
		listArray[0]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);//设置当前的列表视图控件扩展的样式
		listArray[0]->ApproximateViewRect(sz,1);//指定显示列表视图控件项所需的宽度和高度?
		listArray[0]->InsertColumn(i++, "序号", LVCFMT_LEFT, 45, -1);//i++为列号，内容，居中，宽度
		listArray[0]->InsertColumn(i++, "名称", LVCFMT_LEFT, 160, -1);
		listArray[0]->InsertColumn(i++, "动作/告警", LVCFMT_CENTER, 85, -1);
		listArray[0]->InsertColumn(i++, "定值", LVCFMT_CENTER, 90, -1);
		listArray[0]->InsertColumn(i++, "时间1", LVCFMT_CENTER, 90, -1);
		listArray[0]->InsertColumn(i++, "时间2", LVCFMT_CENTER, 90, -1);
		listArray[0]->InsertColumn(i++, "定值单位/备注", LVCFMT_CENTER, 141, -1);
	//	AfxMessageBox("111111111");
	}
	else if(type ==1 || type ==2 || type ==3 || type ==4 || type==5 )
	{
		listArray[0]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		listArray[0]->ApproximateViewRect(sz,1);//ApproximateViewRect指定显示列表视图控件项所需的宽度和高度
		listArray[0]->InsertColumn(i++, "线路号", LVCFMT_LEFT, 64, -1);
		listArray[0]->InsertColumn(i++, "投入/退出", LVCFMT_CENTER, 92, -1);
		listArray[0]->InsertColumn(i++, "上限值", LVCFMT_CENTER, 85, -1);
		listArray[0]->InsertColumn(i++, "下限值", LVCFMT_CENTER, 85, -1);
		listArray[0]->InsertColumn(i++, "时间", LVCFMT_CENTER, 95, -1);
		listArray[0]->InsertColumn(i++, "定值单位/备注", LVCFMT_CENTER, 151, -1);
	//	AfxMessageBox("2222222222222");
	}
	else if(type ==6 || type ==7 || type ==8)
	{
		listArray[0]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		listArray[0]->ApproximateViewRect(sz,1);
		listArray[0]->InsertColumn(i++, "线路号", LVCFMT_CENTER, 90, -1);
		listArray[0]->InsertColumn(i++, "投入/退出", LVCFMT_CENTER, 110, -1);
		listArray[0]->InsertColumn(i++, "定值", LVCFMT_CENTER, 110, -1);
		listArray[0]->InsertColumn(i++, "时间", LVCFMT_CENTER, 110, -1);
		listArray[0]->InsertColumn(i++, "定值单位/备注", LVCFMT_CENTER, 152, -1);
	//	AfxMessageBox("333333333333");
	}
	else if(type ==9 || type ==10 || type ==11 || type==12)
	{
		listArray[0]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		listArray[0]->ApproximateViewRect(sz,1);
		listArray[0]->InsertColumn(i++, "序号", LVCFMT_LEFT, 45, -1);//i++为列号，内容，居中，宽度
		listArray[0]->InsertColumn(i++, "名称", LVCFMT_LEFT, 160, -1);
		listArray[0]->InsertColumn(i++, "投入/退出", LVCFMT_CENTER, 85, -1);
		listArray[0]->InsertColumn(i++, "定值", LVCFMT_CENTER, 90, -1);
		listArray[0]->InsertColumn(i++, "时间1", LVCFMT_CENTER, 90, -1);
		listArray[0]->InsertColumn(i++, "时间2", LVCFMT_CENTER, 90, -1);
		listArray[0]->InsertColumn(i++, "定值单位/备注", LVCFMT_CENTER, 141, -1);
	//	AfxMessageBox("44444444444");
	}


	CRect rect;//?
	listArray[0]->GetWindowRect(&rect);//该函数返回指定窗口的边框矩形的尺寸。该尺寸以相对于屏幕坐标左上角的屏幕坐标给出。

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
	m_FDGType.AddString("保护定值设定");
	m_FDGType.AddString("电流回路-越限告警定值设定");//故障类型：组合框列表框combo1
	m_FDGType.AddString("电压回路-越限告警定值设定");
	m_FDGType.AddString("零序电流回路-越限告警定值设定");
	m_FDGType.AddString("零序电压回路-越限告警定值设定");
	m_FDGType.AddString("过负荷告警定值设定");
	m_FDGType.AddString("相间短路I段故障配置");
	m_FDGType.AddString("相间短路II段故障配置");
	m_FDGType.AddString("单相接地故障配置");
	m_FDGType.AddString("电压时间型逻辑配置");
	m_FDGType.AddString("电压电流型逻辑配置");
	m_FDGType.AddString("自适应综合型逻辑配置");
	m_FDGType.AddString("联络合闸逻辑配置");
	m_FDGType.SetCurSel(0);

	m_Enable.ResetContent();//保护定值设定中 动作告警投退组合框列表框combo2
	m_Enable.AddString("动作");
	m_Enable.AddString("告警");
	m_Enable.AddString("退出");
	m_Enable.SetCurSel(0);

	GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO3)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO4)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO5)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO6)->EnableWindow(TRUE);

///////////接线方式/////////////////////////////////////////////////////

	if(CMode==0)
		((CButton *)GetDlgItem(IDC_RADIO13))->SetCheck(1);
	else if(CMode ==1)
		((CButton *)GetDlgItem(IDC_RADIO14))->SetCheck(1);
	else
		((CButton *)GetDlgItem(IDC_RADIO15))->SetCheck(1);

///////////使能/////////////////////////////////////////////////////

	if(mPzkIni.FDGFileTemp.Cfg.Prot_YXEnable == 255)//保护虚遥信使能
	{
		m_Check1 = true;//IDC_CHECK1的值
	}
	else
	{
		m_Check1 = false;
	}
	if(mPzkIni.FDGFileTemp.Cfg.Prot_MsgEnable == 255)//保护信息上报使能
	{
		m_Check2 = true;
	}
	else
	{
		m_Check2 = false;
	}
	if(mPzkIni.FDGFileTemp.Cfg.Flt_RcwEnable == 255)//故障录波使能
	{
		m_Check3 = true;
	}
	else
	{
		m_Check3 = false;
	}
	if(mPzkIni.FDGFileTemp.Cfg.Byd_SOEEnable == 255)//越限告警SOE使能
	{
		m_Check4 = true;
	}
	else
	{
		m_Check4 = false;
	}
	if(mPzkIni.FDGFileTemp.Cfg.Flt_YXEnable == 255)//故障检测分相上报使能
	{
		m_Check5 = true;
	}
	else
	{
		m_Check5 = false;
	}
	if(mPzkIni.FDGFileTemp.Cfg.Flt_RepEnable == 255)//故障报文上报使能
	{
		m_Check6 = true;
	}
	else
	{
		m_Check6 = false;
	}

/////////////控制器模式////////////

	DMode=mPzkIni.FDGFileTemp.Cfg.DeviceMode;
	if(DMode==0)//分段模式
	{
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	}
	else//联络模式
	{
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(1);
	}

////////////控制器类型//////////////////////////////

	SType=mPzkIni.FDGFileTemp.Cfg.SelectType;
	if(SType==0)//电压时间型
	{
		((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(1);
	}
	else if(SType==1)//电压电流型
	{
		((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(1);
	}
	else if(SType==2)//自适应型
	{
		((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(1);
	}
	else//电流型
	{
		((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(1);
	}

////////////自适应综合型模式//////////////////////////

	AType=mPzkIni.FDGFileTemp.Cfg.AdpSmlType;
	if(AType==0)//选线模式
	{
		((CButton*)GetDlgItem(IDC_RADIO7))->SetCheck(1);
	}
	else if(AType==1)//选段模式
	{
		((CButton*)GetDlgItem(IDC_RADIO8))->SetCheck(1);
	}
	else			//分支线模式
	{
		((CButton*)GetDlgItem(IDC_RADIO9))->SetCheck(1);
	}

////////////开关类型///////////////////////////////////

	SwType=mPzkIni.FDGFileTemp.Cfg.SwitchType;
	if(SwType==0)//断路器
	{
		((CButton*)GetDlgItem(IDC_RADIO10))->SetCheck(1);
	}
	else if(SwType==1)//负荷开关
	{
		((CButton*)GetDlgItem(IDC_RADIO11))->SetCheck(1);
	}
	else			//组合电器
	{
		((CButton*)GetDlgItem(IDC_RADIO12))->SetCheck(1);
	}

	UpdateData(UPDATE_WRITE);//值更新到控件
	UpdateData(UPDATE_READ);//控件的值更新到变量
	InitListCtrl();//调用初始化列表框函数
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
		int i = AfxMessageBox("保存当前对保护项配置所做的修改吗？",MB_YESNOCANCEL);
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

void CFDGCfgView::OnCheck1() //保护虚遥信使能
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	UpdateData(true);//界面到控件变量
	if(m_Check1 == true)
	{
		mPzkIni.FDGFileTemp.Cfg.Prot_YXEnable=255;
	}
	else
	{
		mPzkIni.FDGFileTemp.Cfg.Prot_YXEnable=0;
	}
}

void CFDGCfgView::OnCheck2() //保护信息上报使能
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	UpdateData(true);//界面到控件变量
	if(m_Check2 == true)
	{
		mPzkIni.FDGFileTemp.Cfg.Prot_MsgEnable=255;
	}
	else
	{
		mPzkIni.FDGFileTemp.Cfg.Prot_MsgEnable=0;
	}
}

void CFDGCfgView::OnCheck3() //故障录波使能
{
	// TODO: Add your control notification handler code here

	bEverEdited = true;
	UpdateData(true);//界面到控件变量
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
	UpdateData(true);//界面到控件变量
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
	UpdateData(true);//界面到程序
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
	UpdateData(true);//界面到程序
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
		AfxMessageBox("最大固有时间不能超过"+Str(45)+Str("ms"));
		m_FixActTime = 45;
		UpdateData(UPDATE_WRITE);
	}
	if(m_FixActTime < 30)
	{
		AfxMessageBox("最小固有时间不能小于"+Str(30)+Str("ms"));
		m_FixActTime = 30;
		UpdateData(UPDATE_WRITE);
	}
}

void CFDGCfgView::OnButton1()
{
	// TODO: Add your control notification handler code here
	int j;
	int i = m_FDGType.GetCurSel();//得到当前故障类型
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
	UpdateData(true);//界面到变量
	mPzkIni.FDGFile.Cfg.SwitchType=mPzkIni.FDGFileTemp.Cfg.SwitchType;
	mPzkIni.FDGFile.Cfg.DeviceMode=mPzkIni.FDGFileTemp.Cfg.DeviceMode;
	mPzkIni.FDGFile.Cfg.SelectType=mPzkIni.FDGFileTemp.Cfg.SelectType;
	mPzkIni.FDGFile.Cfg.AdpSmlType=	mPzkIni.FDGFileTemp.Cfg.AdpSmlType;
	mPzkIni.FDGFile.Cfg.V_ConnectMode=mPzkIni.FDGFileTemp.Cfg.V_ConnectMode;
	mPzkIni.FDGFile.Cfg.Prot_YXEnable=mPzkIni.FDGFileTemp.Cfg.Prot_YXEnable;//保护虚遥信使能
	mPzkIni.FDGFile.Cfg.Prot_MsgEnable=mPzkIni.FDGFileTemp.Cfg.Prot_MsgEnable;//保护信息上报使能
	mPzkIni.FDGFile.Cfg.Byd_SOEEnable=mPzkIni.FDGFileTemp.Cfg.Byd_SOEEnable;//越限告警SOE使能
	mPzkIni.FDGFile.Cfg.Flt_YXEnable=mPzkIni.FDGFileTemp.Cfg.Flt_YXEnable;//故障检测分相上报使能
	mPzkIni.FDGFile.Cfg.Flt_RepEnable=mPzkIni.FDGFileTemp.Cfg.Flt_RepEnable;//故障报文上报使能
	mPzkIni.FDGFile.Cfg.Flt_RcwEnable=mPzkIni.FDGFileTemp.Cfg.Flt_RcwEnable;//故障录波使能
	mPzkIni.FDGFile.Cfg.FixActTime=m_FixActTime; //保护动作固有时间

	int i;
	int j;
	for(i=0;i<13;i++)
	{
		if(i == 0 )
		{
			for(j=0;j<mPzkIni.FDGFileTemp.Cfg.ProtNumPerLine;j++)//全部保存一遍 0-每条线路保护数
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
	int type = m_FDGType.GetCurSel();//故障类型组合框内容项 0为保护定值设定
	if(type ==0)
	{
		if(nSubItem == 2)
		{

			pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO2);
			pCombo = (CComboBox *)GetDlgItem(IDC_COMBO2);
			str = m_List1.GetItemText(nItem, nSubItem);
			if(str.Compare("动作") == 0)
				pCombo->SetCurSel(0);
			else if(str.Compare("告警") == 0)
				pCombo->SetCurSel(1);
			else if(str.Compare("退出") == 0)
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
			if(str.Compare("投入") == 0)
				pCombo->SetCurSel(0);
			else if(str.Compare("退出") == 0)
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
			if(str.Compare("投入") == 0)
				pCombo->SetCurSel(0);
			else if(str.Compare("退出") == 0)
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
			if(str.Compare("投入") == 0)
				pCombo->SetCurSel(0);
			else if(str.Compare("退出") == 0)
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
		if(DMode==0 && SType==0)//分段模式电压时间型
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
		else if(DMode==0 && SType==1)//分段模式电压电流型
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
		else if(DMode==0 && SType==2)//分段模式自适应综合型
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
		else if(DMode==0 && SType==3)//分段模式电流型
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
		else if(DMode==1)//分段模式电流型
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
	int ProType;//得到当前故障类型
	//保存数据数组的第某个开关的下标

	if(type == 0)
	{
		if(DMode==0 && SType==0)//分段模式电压时间型
		{
			ProType=0;
			index = FDG_Select[ProType][nItem];
			if(m_Enable.GetCurSel() == 0)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "动作");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=255;
			}
			else if(m_Enable.GetCurSel() == 1)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "告警");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=1;
			}
			else if(m_Enable.GetCurSel() == 2)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "退出");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=0;
			}
		}
		else if(DMode==0 && SType==1)//分段模式电压电流型
		{
			ProType=1;
			index = FDG_Select[ProType][nItem];
			if(m_Enable.GetCurSel() == 0)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "动作");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=255;
			}
			else if(m_Enable.GetCurSel() == 1)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "告警");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=1;
			}
			else if(m_Enable.GetCurSel() == 2)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "退出");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=0;
			}
		}
		else if(DMode==0 && SType==2)//分段模式自适应综合型
		{
			ProType=2;
			index = FDG_Select[ProType][nItem];
			if(m_Enable.GetCurSel() == 0)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "动作");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=255;
			}
			else if(m_Enable.GetCurSel() == 1)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "告警");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=1;
			}
			else if(m_Enable.GetCurSel() == 2)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "退出");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=0;
			}
		}
		else if(DMode==0 && SType==3)//分段模式电流型
		{
			ProType=3;
			index = FDG_Select[ProType][nItem];
			if(m_Enable.GetCurSel() == 0)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "动作");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=255;
			}
			else if(m_Enable.GetCurSel() == 1)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "告警");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=1;
			}
			else if(m_Enable.GetCurSel() == 2)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "退出");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=0;
			}
		}
		else if(DMode==1)//联络模式保护
		{
			ProType=4;
			index = FDG_Select[ProType][nItem];
			if(m_Enable.GetCurSel() == 0)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "动作");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=255;
			}
			else if(m_Enable.GetCurSel() == 1)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "告警");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=1;
			}
			else if(m_Enable.GetCurSel() == 2)
			{
				listArray[0]->SetItemText(nItem, nSubItem, "退出");
				mPzkIni.FDGFileTemp.Line[type].FDGItem[index].Enable=0;
			}
		}
	}
	else if(type == 9 || type == 10 || type == 11 || type == 12)
	{
		if(m_Enable.GetCurSel() == 0)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "投入");
			mPzkIni.FDGFileTemp.Line[type].FDGItem[nItem].Enable=255;
		}
		else if(m_Enable.GetCurSel() == 1)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "退出");
			mPzkIni.FDGFileTemp.Line[type].FDGItem[nItem].Enable=0;
		}

	}
	else
	{
		if(m_Enable.GetCurSel() == 0)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "投入");
			mPzkIni.FDGFileTemp.Line[type].FDGItem[0].Enable=255;
		}
		else if(m_Enable.GetCurSel() == 1)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "退出");
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
	if(type ==0)//radio 开关类型激活与禁止
	{
		m_Enable.ResetContent();
		m_Enable.AddString("动作");
		m_Enable.AddString("告警");
		m_Enable.AddString("退出");

	}
	else
	{
		m_Enable.ResetContent();
		m_Enable.AddString("投入");
		m_Enable.AddString("退出");

	}

	if(type == 0)// 保护  复选框激活与禁止
	{
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(FALSE);

		GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);

	}
	else if(type >=1 && type <=5 )//告警 3
	{
		GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(FALSE);

		GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
	}
	else if( type == 6 || type == 7 || type == 8 )//故障
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
			AfxMessageBox("此控制器类型不需要配置此项");
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
			AfxMessageBox("此控制器类型不需要配置此项");
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
			AfxMessageBox("此控制器类型不需要配置此项");
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
			AfxMessageBox("此控制器类型不需要配置此项");
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
