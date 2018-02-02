// ProtCfgView.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
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
int LineNo;
CString lineNo_str;

CFont   font1;
extern int NumberMax[7][1];//保存故障实际最大化配置数    0开始
//extern bool lizhen ;
extern bool flt_3I0;
extern bool flt1_Current;
extern bool flt2_Current;
extern bool byd_ZeroU;
extern bool byd_ZeroI;
extern bool byd_Voltage;
extern bool byd_Current;
CString FaultName[] = {	"过流保护",
							"失压保护",
							"联络备投",
							"FaultType3",
							"ZeroCurrent",

							"SmallI_3U0",
							"_SmallI_3I0",
							"重合闸",
							"过流后失压",
							"后加速",

							"Enable_PLC",
							"Z时限闭锁",
							"FaultType12",
							"FaultType13",
							"FaultType14",
							"FaultType15",

							"FaultType16",
							"FaultType17",
							"FaultType18",
							"FaultType19",
							"FaultType20"

							"FaultType21",
							"FaultType22",
							"FaultType23",
							"FaultType24",
							"FaultType25"

							"FaultType26",
							"FaultType27",
							"FaultType28",
							"FaultType29",
							"FaultType30"

							"FaultType31",
							"FaultType32"
};

/////////////////////////////////////////////////////////////////////////////
// CFaultCfgView

IMPLEMENT_DYNCREATE(CFaultCfgView, CFormView)

CFaultCfgView::CFaultCfgView()
	: CFormView(CFaultCfgView::IDD)
{
	//{{AFX_DATA_INIT(CFaultCfgView)
	m_Version = _T("");
	m_CreateTime = _T("");
	m_LineNum = 0;
	m_PNumPerLine = 0;
	m_SboNo = 0;
	m_SwitchNo = 0;
	m_Remote = 0;
	m_Local = 0;
//	m_SboNo[i] = mPzkIni.ProtFile.Cfg.FixActTime;
	m_SboNo = mPzkIni.ProtFile.Cfg.Switch_Remote;
	m_SwitchNo = mPzkIni.ProtFile.Cfg.Switch_Local;
	m_FixActTime = mPzkIni.ProtFile.Cfg.FixActTime;
	CMode = mPzkIni.ProtFile.Cfg.V_ConnectMode;
	//}}AFX_DATA_INIT
	bEverEdited = false;
	/*
	for(int i=0; i<_Max_Prot_Line; i++)
	{
	//	mSbo[i] = mPzkIni.ProtFile.Line[i].LineCfg.Line_Sbo;
		m_SboNo[i] = mPzkIni.ProtFile.Cfg.FixActTime;
	//	m_SboNo[i] = mPzkIni.ProtFile.Cfg.Switch_Remote;
		m_SwitchNo[i] = mPzkIni.ProtFile.Cfg.Switch_Local;
		mMode[i] = mPzkIni.ProtFile.Cfg.V_ConnectMode;
	}
	*/

}

CFaultCfgView::~CFaultCfgView()
{
}

void CFaultCfgView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFaultCfgView)
	DDX_Control(pDX, IDC_LIST9, m_List9);
	DDX_Control(pDX, IDC_LIST32, m_List32);
	DDX_Control(pDX, IDC_LIST31, m_List31);
	DDX_Control(pDX, IDC_LIST30, m_List30);
	DDX_Control(pDX, IDC_LIST29, m_List29);
	DDX_Control(pDX, IDC_LIST28, m_List28);
	DDX_Control(pDX, IDC_LIST27, m_List27);
	DDX_Control(pDX, IDC_LIST26, m_List26);
	DDX_Control(pDX, IDC_LIST25, m_List25);
	DDX_Control(pDX, IDC_LIST24, m_List24);
	DDX_Control(pDX, IDC_LIST23, m_List23);
	DDX_Control(pDX, IDC_LIST22, m_List22);
	DDX_Control(pDX, IDC_LIST21, m_List21);
	DDX_Control(pDX, IDC_LIST20, m_List20);
	DDX_Control(pDX, IDC_LIST19, m_List19);
	DDX_Control(pDX, IDC_LIST18, m_List18);
	DDX_Control(pDX, IDC_LIST17, m_List17);
	DDX_Control(pDX, IDC_LIST16, m_List16);
	DDX_Control(pDX, IDC_LIST15, m_List15);
	DDX_Control(pDX, IDC_LIST14, m_List14);
	DDX_Control(pDX, IDC_LIST13, m_List13);
	DDX_Control(pDX, IDC_LIST12, m_List12);
	DDX_Control(pDX, IDC_LIST11, m_List11);
	DDX_Control(pDX, IDC_LIST10, m_List10);
	DDX_Control(pDX, IDC_LIST8, m_List8);
	DDX_Control(pDX, IDC_LIST7, m_List7);
	DDX_Control(pDX, IDC_LIST6, m_List6);
	DDX_Control(pDX, IDC_EDIT9, m_Input);
	DDX_Control(pDX, IDC_COMBO3, m_Enable);
	DDX_Control(pDX, IDC_COMBO4, m_ProtType);
	DDX_Control(pDX, IDC_LIST5, m_List5);
	DDX_Control(pDX, IDC_LIST4, m_List4);
	DDX_Control(pDX, IDC_LIST3, m_List3);
	DDX_Control(pDX, IDC_LIST2, m_List2);
	DDX_Check(pDX, IDC_CHECK1, m_Check1);
	DDX_Check(pDX, IDC_CHECK2, m_Check2);
	DDX_Check(pDX, IDC_CHECK3, m_Check3);
	DDX_Control(pDX, IDC_COMBO2, m_ConnectMode);
	DDX_Control(pDX, IDC_COMBO1, m_LineNo);
	DDX_Control(pDX, IDC_LIST1, m_List1);
	DDX_Text(pDX, IDC_EDIT1, m_Version);
	DDX_Text(pDX, IDC_EDIT2, m_CreateTime);
	DDX_Text(pDX, IDC_EDIT3, m_LineNum);
	DDX_Text(pDX, IDC_EDIT4, m_PNumPerLine);
	DDX_Text(pDX, IDC_EDIT5, m_SboNo);
	DDX_Text(pDX, IDC_EDIT6, m_SwitchNo);
	DDX_Text(pDX, IDC_EDIT7, m_Remote);
	DDX_Text(pDX, IDC_EDIT8, m_Local);
	DDX_Text(pDX, IDC_EDIT21, m_FixActTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFaultCfgView, CFormView)
	//{{AFX_MSG_MAP(CFaultCfgView)
	ON_EN_KILLFOCUS(IDC_EDIT3, OnKillfocusEdit3)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, OnClickList2)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, OnClickList3)
	ON_NOTIFY(NM_CLICK, IDC_LIST4, OnClickList4)
	ON_NOTIFY(NM_CLICK, IDC_LIST5, OnClickList5)
	ON_BN_CLICKED(IDSAVE, OnSave)
	ON_EN_KILLFOCUS(IDC_EDIT4, OnKillfocusEdit4)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, OnChangeEdit8)
	ON_CBN_KILLFOCUS(IDC_COMBO3, OnKillfocusCombo3)
	ON_CBN_KILLFOCUS(IDC_COMBO4, OnKillfocusCombo4)
	ON_EN_KILLFOCUS(IDC_EDIT9, OnKillfocusEdit9)
	ON_EN_KILLFOCUS(IDC_EDIT5, OnKillfocusEdit5)
	ON_EN_KILLFOCUS(IDC_EDIT6, OnKillfocusEdit6)
	ON_EN_KILLFOCUS(IDC_EDIT7, OnKillfocusEdit7)
	ON_EN_KILLFOCUS(IDC_EDIT8, OnKillfocusEdit8)
	ON_CBN_KILLFOCUS(IDC_COMBO2, OnKillfocusCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_NOTIFY(NM_CLICK, IDC_LIST6, OnClickList6)
	ON_NOTIFY(NM_CLICK, IDC_LIST7, OnClickList7)
	ON_NOTIFY(NM_CLICK, IDC_LIST8, OnClickList8)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_CANCEl, OnCancel)
	ON_NOTIFY(NM_CLICK, IDC_LIST9, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST10, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST11, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST12, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST13, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST14, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST15, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST16, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST17, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST18, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST19, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST20, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST21, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST22, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST23, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST24, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST25, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST26, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST27, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST28, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST29, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST30, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST31, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST32, OnClickList8)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
//	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
//	ON_COMMAND(ID_MENUITEM32801, OnMenuitem32801)
//	ON_COMMAND(IDR_REMOVERTU,OnRemovertu)
//	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
//	ON_NOTIFY(NM_RCLICK, IDC_LIST2, OnRclickList1)
//	ON_NOTIFY(NM_RCLICK, IDC_LIST3, OnRclickList1)
//	ON_NOTIFY(NM_RCLICK, IDC_LIST4, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST5, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST6, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST7, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST8, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST9, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST10, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST11, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST12, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST13, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST14, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST15, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST16, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST17, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST18, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST19, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST20, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST21, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST22, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST23, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST24, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST25, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST26, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST27, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST28, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST29, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST30, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST31, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST32, OnRclickList1)

	//}}AFX_MSG_MAP
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFaultCfgView diagnostics

#ifdef _DEBUG
void CFaultCfgView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFaultCfgView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFaultCfgView message handlers
void CFaultCfgView::SetListFocus(int no)
{
	for(int i=0; i<7; i++)
	{
		if(i == no)
			listArray[i]->ShowWindow(SW_SHOW);
		else
			listArray[i]->ShowWindow(SW_HIDE);
	}
}

int CFaultCfgView::CheckNum(CString str)
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
				NumFlag = 1;//大于1个小数点
				break;
			}
		}
		else
		{
			NumFlag = 2;//不是数字
			break;
		}
	}

	return NumFlag;
}

void CFaultCfgView::OnRemovertu()
{
	int LineNo;
	int result;
	LineNo = m_LineNo.GetCurSel();
//	int i;
	//int iState;
	int nItemSelected=listArray[LineNo]->GetSelectedCount();//所选表项数
	int nItemCount=listArray[LineNo]->GetItemCount();//表项总数
	//if(nItemSelected<1)
	//	return;
//	for(i=nItemCount-1;i>=0;i--)
//	{
//		iState=listArray[LineNo]->GetItemState(i,LVIS_SELECTED);
//		if(iState==0)
//		{

	if(nItemCount>0)
	{

		result=AfxMessageBox("确定要删除最后一行吗？",MB_YESNO);
			if(result==IDYES)
			{
				listArray[LineNo]->DeleteItem(nItemCount-1);//删除最后一行
				mPzkIni.ProtFile.Line[LineNo].LineCfg.LineNum--;//总线路数加1 //各种赋值
				m_LineNum=mPzkIni.ProtFile.Line[LineNo].LineCfg.LineNum;//关联变量
				UpdateData(FALSE);//关联变量更新
				OnSave();
				LoadFaultConfig();
			}
	}
	else
	{
		AfxMessageBox("已达到最小值,不能再删除!");
	}

}

void CFaultCfgView::OnMenuitem32801()//添加一行消息执行函数
{

	CObjItemDlg tempdlg;
	LineNo = m_LineNo.GetCurSel();
	m_LineNo.GetLBText(LineNo,lineNo_str);
	//AfxMessageBox(lineNo_str);
	if(tempdlg.DoModal()==IDOK)
	{
		mPzkIni.ProtFile.Line[LineNo].LineCfg.LineNum++;//总线路数加1 //各种赋值
		m_LineNum=mPzkIni.ProtFile.Line[LineNo].LineCfg.LineNum;//关联变量
		UpdateData(FALSE);//关联变量更新
		LoadFaultConfig();//重新load
	}
}

void CFaultCfgView::LoadFaultConfig()//load各种
{
	int i;
	int addItem;
	CString str;
/*
	for(int LineNo=0; LineNo<3; LineNo++)
	{
		listArray[LineNo]->DeleteAllItems();
		for(i=0; i<mPzkIni.ProtFile.Line[LineNo].LineCfg.LineNum; i++)
		{
			addItem = listArray[LineNo]->InsertItem(i, Str(i), 0);
			listArray[LineNo]->SetItemData(addItem, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type);
			listArray[LineNo]->SetItemText(addItem, 1, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Name);//FaultName[mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type]);
			if(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Enable)
				listArray[LineNo]->SetItemText(addItem, 2, "投入");
			else
				listArray[LineNo]->SetItemText(addItem, 2, "退出");
			listArray[LineNo]->SetItemText(addItem, 3, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value1));
			listArray[LineNo]->SetItemText(addItem, 4, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value2));
			listArray[LineNo]->SetItemText(addItem, 5, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Time));
			//str.Format("%f",mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value1);
			//AfxMessageBox(str);
			listArray[LineNo]->SetItemText(addItem, 6, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Unit);
		}
	}
	for(LineNo=3; LineNo<6; LineNo++)
	{
		listArray[LineNo]->DeleteAllItems();
		for(i=0; i<mPzkIni.ProtFile.Line[LineNo].LineCfg.LineNum; i++)
		{
			addItem = listArray[LineNo]->InsertItem(i, Str(i), 0);
			listArray[LineNo]->SetItemData(addItem, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type);
			listArray[LineNo]->SetItemText(addItem, 1, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Name);//FaultName[mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type]);
			if(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Enable)
				listArray[LineNo]->SetItemText(addItem, 2, "投入");
			else
				listArray[LineNo]->SetItemText(addItem, 2, "退出");
			listArray[LineNo]->SetItemText(addItem, 3, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value1));
			//listArray[LineNo]->SetItemText(addItem, 4, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value2));
			listArray[LineNo]->SetItemText(addItem, 4, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Time));
			listArray[LineNo]->SetItemText(addItem, 5, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Unit);
		}
	}
*/
	bool flt_3I0_oldd = flt_3I0;
	bool flt1_Current_oldd = flt1_Current;
	bool flt2_Current_oldd = flt2_Current;
	bool byd_ZeroU_oldd = byd_ZeroU;
	bool byd_ZeroI_oldd = byd_ZeroI ;
	bool byd_Voltage_oldd =  byd_Voltage;
	bool byd_Current_oldd = byd_Current;

	for(int LineNo=0; LineNo<7; LineNo++)
	{
		if(byd_Current==true)
		{
			byd_Current=false;
			listArray[LineNo]->DeleteAllItems();
			for(i=0; i<mPzkIni.ProtFile.Line[LineNo].LineCfg.LineNum; i++)
			{
				addItem = listArray[LineNo]->InsertItem(i, Str(i), 0);
				listArray[LineNo]->SetItemData(addItem, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type);
				listArray[LineNo]->SetItemText(addItem, 1, Str(atoi(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Name)+1));//FaultName[mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type]);
				if(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Enable)
					listArray[LineNo]->SetItemText(addItem, 2, "投入");
				else
					listArray[LineNo]->SetItemText(addItem, 2, "退出");
				listArray[LineNo]->SetItemText(addItem, 3, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value1));
				listArray[LineNo]->SetItemText(addItem, 4, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value2));
				listArray[LineNo]->SetItemText(addItem, 5, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Time));
				//str.Format("%f",mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value1);
				//AfxMessageBox(str);
				listArray[LineNo]->SetItemText(addItem, 6, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Unit);
			}
		}

		else if(byd_Voltage==true)
		{
			byd_Voltage=false;
			listArray[LineNo]->DeleteAllItems();
			for(i=0; i<mPzkIni.ProtFile.Line[LineNo].LineCfg.LineNum; i++)
			{
				addItem = listArray[LineNo]->InsertItem(i, Str(i), 0);
				listArray[LineNo]->SetItemData(addItem, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type);
				listArray[LineNo]->SetItemText(addItem, 1, Str(atoi(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Name)+1));//FaultName[mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type]);
				if(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Enable)
					listArray[LineNo]->SetItemText(addItem, 2, "投入");
				else
					listArray[LineNo]->SetItemText(addItem, 2, "退出");
				listArray[LineNo]->SetItemText(addItem, 3, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value1));
				listArray[LineNo]->SetItemText(addItem, 4, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value2));
				listArray[LineNo]->SetItemText(addItem, 5, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Time));
				//str.Format("%f",mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value1);
				//AfxMessageBox(str);
				listArray[LineNo]->SetItemText(addItem, 6, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Unit);
			}
		}

		else if(byd_ZeroI==true)
		{
			byd_ZeroI=false;
			listArray[LineNo]->DeleteAllItems();
			for(i=0; i<mPzkIni.ProtFile.Line[LineNo].LineCfg.LineNum; i++)
			{
				addItem = listArray[LineNo]->InsertItem(i, Str(i), 0);
				listArray[LineNo]->SetItemData(addItem, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type);
				listArray[LineNo]->SetItemText(addItem, 1, Str(atoi(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Name)+1));//FaultName[mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type]);
				if(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Enable)
					listArray[LineNo]->SetItemText(addItem, 2, "投入");
				else
					listArray[LineNo]->SetItemText(addItem, 2, "退出");
				listArray[LineNo]->SetItemText(addItem, 3, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value1));
				listArray[LineNo]->SetItemText(addItem, 4, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value2));
				listArray[LineNo]->SetItemText(addItem, 5, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Time));
				//str.Format("%f",mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value1);
				//AfxMessageBox(str);
				listArray[LineNo]->SetItemText(addItem, 6, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Unit);
			}
		}

		else if(byd_ZeroU==true)
		{
			byd_ZeroU=false;
			listArray[LineNo]->DeleteAllItems();
			for(i=0; i<mPzkIni.ProtFile.Line[LineNo].LineCfg.LineNum; i++)
			{
				addItem = listArray[LineNo]->InsertItem(i, Str(i), 0);
				listArray[LineNo]->SetItemData(addItem, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type);
				listArray[LineNo]->SetItemText(addItem, 1, Str(atoi(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Name)+1));//FaultName[mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type]);
				if(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Enable)
					listArray[LineNo]->SetItemText(addItem, 2, "投入");
				else
					listArray[LineNo]->SetItemText(addItem, 2, "退出");
				listArray[LineNo]->SetItemText(addItem, 3, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value1));
				listArray[LineNo]->SetItemText(addItem, 4, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value2));
				listArray[LineNo]->SetItemText(addItem, 5, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Time));
				//str.Format("%f",mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value1);
				//AfxMessageBox(str);
				listArray[LineNo]->SetItemText(addItem, 6, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Unit);
			}
		}

		else if(flt1_Current==true)
		{
			flt1_Current=false;
			listArray[LineNo]->DeleteAllItems();
			for(i=0; i<mPzkIni.ProtFile.Line[LineNo].LineCfg.LineNum; i++)
			{
				addItem = listArray[LineNo]->InsertItem(i, Str(i), 0);
				listArray[LineNo]->SetItemData(addItem, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type);
				listArray[LineNo]->SetItemText(addItem, 1, Str(atoi(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Name)+1));//FaultName[mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type]);
				if(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Enable)
					listArray[LineNo]->SetItemText(addItem, 2, "投入");
				else
					listArray[LineNo]->SetItemText(addItem, 2, "退出");
				listArray[LineNo]->SetItemText(addItem, 3, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value1));
				//listArray[LineNo]->SetItemText(addItem, 4, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value2));
				listArray[LineNo]->SetItemText(addItem, 4, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Time));
				//str.Format("%f",mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value1);
				//AfxMessageBox(str);
				listArray[LineNo]->SetItemText(addItem, 5, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Unit);
			}
		}

		else if(flt2_Current==true)
		{
			flt2_Current=false;
			listArray[LineNo]->DeleteAllItems();
			for(i=0; i<mPzkIni.ProtFile.Line[LineNo].LineCfg.LineNum; i++)
			{
				addItem = listArray[LineNo]->InsertItem(i, Str(i), 0);
				listArray[LineNo]->SetItemData(addItem, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type);
				listArray[LineNo]->SetItemText(addItem, 1, Str(atoi(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Name)+1));//FaultName[mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type]);
				if(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Enable)
					listArray[LineNo]->SetItemText(addItem, 2, "投入");
				else
					listArray[LineNo]->SetItemText(addItem, 2, "退出");
				listArray[LineNo]->SetItemText(addItem, 3, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value1));
				//listArray[LineNo]->SetItemText(addItem, 4, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value2));
				listArray[LineNo]->SetItemText(addItem, 4, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Time));
				//str.Format("%f",mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value1);
				//AfxMessageBox(str);
				listArray[LineNo]->SetItemText(addItem, 5, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Unit);
			}
		}
		else if(flt_3I0==true)
		{
			flt_3I0=false;
			listArray[LineNo]->DeleteAllItems();
			for(i=0; i<mPzkIni.ProtFile.Line[LineNo].LineCfg.LineNum; i++)
			{
				addItem = listArray[LineNo]->InsertItem(i, Str(i), 0);
				listArray[LineNo]->SetItemData(addItem, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type);
				listArray[LineNo]->SetItemText(addItem, 1, Str(atoi(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Name)+1));//FaultName[mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type]);
				if(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Enable)
					listArray[LineNo]->SetItemText(addItem, 2, "投入");
				else
					listArray[LineNo]->SetItemText(addItem, 2, "退出");
				listArray[LineNo]->SetItemText(addItem, 3, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value1));
				//listArray[LineNo]->SetItemText(addItem, 4, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value2));
				listArray[LineNo]->SetItemText(addItem, 4, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Time));
				//str.Format("%f",mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value1);
				//AfxMessageBox(str);
				listArray[LineNo]->SetItemText(addItem, 5, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Unit);
			}
		}

	}//end for
	flt_3I0 = flt_3I0_oldd;
	flt1_Current = flt1_Current_oldd;
	flt2_Current = flt2_Current_oldd;
	byd_ZeroU = byd_ZeroU_oldd;
	byd_ZeroI = byd_ZeroI_oldd;
	byd_Voltage =  byd_Voltage_oldd;
	byd_Current = byd_Current_oldd;

	yulan();

}

void CFaultCfgView::InitListCtrl()
{
	int i=0;
	CSize sz;

	//int step=0;
	sz.cx = sz.cy = 30;

	m_LineNo.ResetContent();
	if(byd_Current == true)
		m_LineNo.AddString("电流回路-越限告警定值设定");
	if(byd_Voltage == true)
		m_LineNo.AddString("电压回路-越限告警定值设定");
	if(byd_ZeroI == true)
		m_LineNo.AddString("零序电流回路-越限告警定值设定");
	if(byd_ZeroU == true)
		m_LineNo.AddString("零序电压回路-越限告警定值设定");
	if(flt1_Current == true)
		m_LineNo.AddString("相间短路I段故障配置");
	if(flt2_Current == true)
		m_LineNo.AddString("相间短路II段故障配置");
	if(flt_3I0 == true)
		m_LineNo.AddString("单相接地故障配置");




/*	m_List1.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List1.ApproximateViewRect(sz,1);
	m_List1.InsertColumn(i++, "序号", LVCFMT_LEFT, 50, -1);
	m_List1.InsertColumn(i++, "名称", LVCFMT_LEFT, 120, -1);
	m_List1.InsertColumn(i++, "投/退", LVCFMT_CENTER, 80, -1);
	m_List1.InsertColumn(i++, "定值", LVCFMT_RIGHT, 100, -1);
	m_List1.InsertColumn(i++, "时间(ms)", LVCFMT_RIGHT, 100, -1);
	m_List1.InsertColumn(i++, "定值单位/备注", LVCFMT_RIGHT, 100, -1);

	i = 0;
	m_List2.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List2.ApproximateViewRect(sz,1);
	m_List2.InsertColumn(i++, "序号", LVCFMT_LEFT, 50, -1);
	m_List2.InsertColumn(i++, "名称", LVCFMT_LEFT, 120, -1);
	m_List2.InsertColumn(i++, "投/退", LVCFMT_CENTER, 80, -1);
	m_List2.InsertColumn(i++, "定值", LVCFMT_RIGHT, 100, -1);
	m_List2.InsertColumn(i++, "时间(ms)", LVCFMT_RIGHT, 100, -1);
	m_List2.InsertColumn(i++, "定值单位/备注", LVCFMT_RIGHT, 100, -1);

	i = 0;
	m_List3.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List3.ApproximateViewRect(sz,1);
	m_List3.InsertColumn(i++, "序号", LVCFMT_LEFT, 50, -1);
	m_List3.InsertColumn(i++, "名称", LVCFMT_LEFT, 120, -1);
	m_List3.InsertColumn(i++, "投/退", LVCFMT_CENTER, 80, -1);
	m_List3.InsertColumn(i++, "定值", LVCFMT_RIGHT, 100, -1);
	m_List3.InsertColumn(i++, "时间(ms)", LVCFMT_RIGHT, 100, -1);
	m_List3.InsertColumn(i++, "定值单位/备注", LVCFMT_RIGHT, 100, -1);

	i = 0;
	m_List4.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List4.ApproximateViewRect(sz,1);
	m_List4.InsertColumn(i++, "序号", LVCFMT_LEFT, 50, -1);
	m_List4.InsertColumn(i++, "名称", LVCFMT_LEFT, 120, -1);
	m_List4.InsertColumn(i++, "投/退", LVCFMT_CENTER, 80, -1);
	m_List4.InsertColumn(i++, "定值", LVCFMT_RIGHT, 100, -1);
	m_List4.InsertColumn(i++, "时间(ms)", LVCFMT_RIGHT, 100, -1);
	m_List4.InsertColumn(i++, "定值单位/备注", LVCFMT_RIGHT, 100, -1);

	i = 0;
	m_List5.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List5.ApproximateViewRect(sz,1);
	m_List5.InsertColumn(i++, "序号", LVCFMT_LEFT, 50, -1);
	m_List5.InsertColumn(i++, "名称", LVCFMT_LEFT, 120, -1);
	m_List5.InsertColumn(i++, "投/退", LVCFMT_CENTER, 80, -1);
	m_List5.InsertColumn(i++, "定值", LVCFMT_RIGHT, 100, -1);
	m_List5.InsertColumn(i++, "时间(ms)", LVCFMT_RIGHT, 100, -1);
	m_List5.InsertColumn(i++, "定值单位/备注", LVCFMT_RIGHT, 100, -1);

	i = 0;
	m_List5.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List5.ApproximateViewRect(sz,1);
	m_List5.InsertColumn(i++, "序号", LVCFMT_LEFT, 50, -1);
	m_List5.InsertColumn(i++, "名称", LVCFMT_LEFT, 120, -1);
	m_List5.InsertColumn(i++, "投/退", LVCFMT_CENTER, 80, -1);
	m_List5.InsertColumn(i++, "定值", LVCFMT_RIGHT, 100, -1);
	m_List5.InsertColumn(i++, "时间(ms)", LVCFMT_RIGHT, 100, -1);
	m_List5.InsertColumn(i++, "定值单位/备注", LVCFMT_RIGHT, 100, -1);

	i = 0;
	m_List5.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List5.ApproximateViewRect(sz,1);
	m_List5.InsertColumn(i++, "序号", LVCFMT_LEFT, 50, -1);
	m_List5.InsertColumn(i++, "名称", LVCFMT_LEFT, 120, -1);
	m_List5.InsertColumn(i++, "投/退", LVCFMT_CENTER, 80, -1);
	m_List5.InsertColumn(i++, "定值", LVCFMT_RIGHT, 100, -1);
	m_List5.InsertColumn(i++, "时间(ms)", LVCFMT_RIGHT, 100, -1);
	m_List5.InsertColumn(i++, "定值单位/备注", LVCFMT_RIGHT, 100, -1);

	i = 0;
	m_List5.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List5.ApproximateViewRect(sz,1);
	m_List5.InsertColumn(i++, "序号", LVCFMT_LEFT, 50, -1);
	m_List5.InsertColumn(i++, "名称", LVCFMT_LEFT, 120, -1);
	m_List5.InsertColumn(i++, "投/退", LVCFMT_CENTER, 80, -1);
	m_List5.InsertColumn(i++, "定值", LVCFMT_RIGHT, 100, -1);
	m_List5.InsertColumn(i++, "时间(ms)", LVCFMT_RIGHT, 100, -1);
	m_List5.InsertColumn(i++, "定值单位/备注", LVCFMT_RIGHT, 100, -1);
*/
	listArray[0] = &m_List1;
	listArray[1] = &m_List2;
	listArray[2] = &m_List3;
	listArray[3] = &m_List4;
	listArray[4] = &m_List5;
	listArray[5] = &m_List6;
	listArray[6] = &m_List7;
	listArray[7] = &m_List8;
	listArray[8] = &m_List9;
	listArray[9] = &m_List10;
	listArray[10] = &m_List11;
	listArray[11] = &m_List12;
	listArray[12] = &m_List13;
	listArray[13] = &m_List14;
	listArray[14] = &m_List15;
	listArray[15] = &m_List16;
	listArray[16] = &m_List17;
	listArray[17] = &m_List18;
	listArray[18] = &m_List19;
	listArray[19] = &m_List20;
	listArray[20] = &m_List21;
	listArray[21] = &m_List22;
	listArray[22] = &m_List23;
	listArray[23] = &m_List24;
	listArray[24] = &m_List25;
	listArray[25] = &m_List26;
	listArray[26] = &m_List27;
	listArray[27] = &m_List28;
	listArray[28] = &m_List29;
	listArray[29] = &m_List30;
	listArray[30] = &m_List31;
	listArray[31] = &m_List32;
/*
	for(int j=0; j<3; j++)
	{
		listArray[j]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		listArray[j]->ApproximateViewRect(sz,1);
		listArray[j]->InsertColumn(i++, "序号", LVCFMT_LEFT, 55, -1);
		listArray[j]->InsertColumn(i++, "线路号", LVCFMT_LEFT, 55, -1);
		listArray[j]->InsertColumn(i++, "投/退", LVCFMT_CENTER, 80, -1);
		listArray[j]->InsertColumn(i++, "上限值", LVCFMT_RIGHT, 85, -1);
		listArray[j]->InsertColumn(i++, "下限值", LVCFMT_RIGHT, 85, -1);
		listArray[j]->InsertColumn(i++, "时间(s)", LVCFMT_RIGHT, 80, -1);
		listArray[j]->InsertColumn(i++, "定值单位(s)/备注", LVCFMT_RIGHT, 132, -1);
	}
	for(j=3; j<6; j++)
	{
		listArray[j]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		listArray[j]->ApproximateViewRect(sz,1);
		listArray[j]->InsertColumn(i++, "序号", LVCFMT_LEFT, 85, -1);
		listArray[j]->InsertColumn(i++, "线路号", LVCFMT_LEFT, 85, -1);
		listArray[j]->InsertColumn(i++, "投/退", LVCFMT_CENTER, 85, -1);
		listArray[j]->InsertColumn(i++, "定值", LVCFMT_RIGHT, 85, -1);
		listArray[j]->InsertColumn(i++, "时间(s)", LVCFMT_RIGHT, 85, -1);
		listArray[j]->InsertColumn(i++, "定值单位/备注", LVCFMT_RIGHT, 145, -1);
	}

*/

	bool flt_3I0_old = flt_3I0;
	bool flt1_Current_old = flt1_Current;
	bool flt2_Current_old = flt2_Current;
	bool byd_ZeroU_old = byd_ZeroU;
	bool byd_ZeroI_old = byd_ZeroI ;
	bool byd_Voltage_old =  byd_Voltage;
	bool byd_Current_old = byd_Current;

	for(int j=0;j<7;j++)
	{
		if(byd_Current==true)
		{
			byd_Current=false;
			listArray[j]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			listArray[j]->ApproximateViewRect(sz,1);
			listArray[j]->InsertColumn(i++, "序号", LVCFMT_LEFT, 55, -1);
			listArray[j]->InsertColumn(i++, "线路号", LVCFMT_LEFT, 55, -1);
			listArray[j]->InsertColumn(i++, "投/退", LVCFMT_CENTER, 80, -1);
			listArray[j]->InsertColumn(i++, "上限值", LVCFMT_RIGHT, 85, -1);
			listArray[j]->InsertColumn(i++, "下限值", LVCFMT_RIGHT, 85, -1);
			listArray[j]->InsertColumn(i++, "时间(s)", LVCFMT_RIGHT, 80, -1);
			listArray[j]->InsertColumn(i++, "定值单位/备注", LVCFMT_RIGHT, 132, -1);
		}
		else if(byd_Voltage==true)
		{
			byd_Voltage=false;
			listArray[j]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			listArray[j]->ApproximateViewRect(sz,1);
			listArray[j]->InsertColumn(i++, "序号", LVCFMT_LEFT, 55, -1);
			listArray[j]->InsertColumn(i++, "线路号", LVCFMT_LEFT, 55, -1);
			listArray[j]->InsertColumn(i++, "投/退", LVCFMT_CENTER, 80, -1);
			listArray[j]->InsertColumn(i++, "上限值", LVCFMT_RIGHT, 85, -1);
			listArray[j]->InsertColumn(i++, "下限值", LVCFMT_RIGHT, 85, -1);
			listArray[j]->InsertColumn(i++, "时间(s)", LVCFMT_RIGHT, 80, -1);
			listArray[j]->InsertColumn(i++, "定值单位/备注", LVCFMT_RIGHT, 132, -1);
		}
		else if(byd_ZeroI==true)
		{
			//AfxMessageBox("c");
			byd_ZeroI=false;
			listArray[j]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			listArray[j]->ApproximateViewRect(sz,1);
			listArray[j]->InsertColumn(i++, "序号", LVCFMT_LEFT, 55, -1);
			listArray[j]->InsertColumn(i++, "线路号", LVCFMT_LEFT, 55, -1);
			listArray[j]->InsertColumn(i++, "投/退", LVCFMT_CENTER, 80, -1);
			listArray[j]->InsertColumn(i++, "上限值", LVCFMT_RIGHT, 85, -1);
			listArray[j]->InsertColumn(i++, "下限值", LVCFMT_RIGHT, 85, -1);
			listArray[j]->InsertColumn(i++, "时间(s)", LVCFMT_RIGHT, 80, -1);
			listArray[j]->InsertColumn(i++, "定值单位/备注", LVCFMT_RIGHT, 132, -1);
		}
		else if(byd_ZeroU==true)
		{
			//AfxMessageBox("d");
			byd_ZeroU=false;
			listArray[j]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			listArray[j]->ApproximateViewRect(sz,1);
			listArray[j]->InsertColumn(i++, "序号", LVCFMT_LEFT, 55, -1);
			listArray[j]->InsertColumn(i++, "线路号", LVCFMT_LEFT, 55, -1);
			listArray[j]->InsertColumn(i++, "投/退", LVCFMT_CENTER, 80, -1);
			listArray[j]->InsertColumn(i++, "上限值", LVCFMT_RIGHT, 85, -1);
			listArray[j]->InsertColumn(i++, "下限值", LVCFMT_RIGHT, 85, -1);
			listArray[j]->InsertColumn(i++, "时间(s)", LVCFMT_RIGHT, 80, -1);
			listArray[j]->InsertColumn(i++, "定值单位/备注", LVCFMT_RIGHT, 132, -1);
		}
		else if(flt1_Current==true)
		{
			//AfxMessageBox("e");
			flt1_Current=false;
			listArray[j]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			listArray[j]->ApproximateViewRect(sz,1);
			listArray[j]->InsertColumn(i++, "序号", LVCFMT_LEFT, 85, -1);
			listArray[j]->InsertColumn(i++, "线路号", LVCFMT_LEFT, 85, -1);
			listArray[j]->InsertColumn(i++, "投/退", LVCFMT_CENTER, 85, -1);
			listArray[j]->InsertColumn(i++, "定值", LVCFMT_RIGHT, 85, -1);
			listArray[j]->InsertColumn(i++, "时间(s)", LVCFMT_RIGHT, 85, -1);
			listArray[j]->InsertColumn(i++, "定值单位/备注", LVCFMT_RIGHT, 145, -1);
		}
		else if(flt2_Current==true)
		{
			//AfxMessageBox("e");
			flt2_Current=false;
			listArray[j]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			listArray[j]->ApproximateViewRect(sz,1);
			listArray[j]->InsertColumn(i++, "序号", LVCFMT_LEFT, 85, -1);
			listArray[j]->InsertColumn(i++, "线路号", LVCFMT_LEFT, 85, -1);
			listArray[j]->InsertColumn(i++, "投/退", LVCFMT_CENTER, 85, -1);
			listArray[j]->InsertColumn(i++, "定值", LVCFMT_RIGHT, 85, -1);
			listArray[j]->InsertColumn(i++, "时间(s)", LVCFMT_RIGHT, 85, -1);
			listArray[j]->InsertColumn(i++, "定值单位/备注", LVCFMT_RIGHT, 145, -1);
		}

		else if(flt_3I0==true)
		{
			//AfxMessageBox("f");
			flt_3I0=false;
			listArray[j]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			listArray[j]->ApproximateViewRect(sz,1);
			listArray[j]->InsertColumn(i++, "序号", LVCFMT_LEFT, 85, -1);
			listArray[j]->InsertColumn(i++, "线路号", LVCFMT_LEFT, 85, -1);
			listArray[j]->InsertColumn(i++, "投/退", LVCFMT_CENTER, 85, -1);
			listArray[j]->InsertColumn(i++, "定值", LVCFMT_RIGHT, 85, -1);
			listArray[j]->InsertColumn(i++, "时间(s)", LVCFMT_RIGHT, 85, -1);
			listArray[j]->InsertColumn(i++, "定值单位/备注", LVCFMT_RIGHT, 145, -1);
		}
	}

	 flt_3I0 = flt_3I0_old;
	 flt1_Current = flt1_Current_old;
	 flt2_Current = flt2_Current_old;
	 byd_ZeroU = byd_ZeroU_old;
	 byd_ZeroI = byd_ZeroI_old;
	 byd_Voltage =  byd_Voltage_old;
	 byd_Current = byd_Current_old;




	CRect rect;
	listArray[0]->GetWindowRect(&rect);
//	listArray[0]->GetWindowRgn
//	rect.top -= 71;
//	rect.bottom -= 71;
	rect.top -= 80;
	rect.bottom -= 80;
	for(i=0; i<_Max_Prot_Line; i++)
		listArray[i]->MoveWindow(rect, TRUE);
	LoadFaultConfig();
}

void CFaultCfgView::OnInitialUpdate()
{
	int i = 0;
	CFormView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	m_ConnectMode.AddString("联络简化接线模式(以Uab为一侧电压，Ucb为另一侧电压)");
	m_ConnectMode.AddString("联络完全接线模式(以2J12为一侧电压，2J13为另一侧电压)");
	m_ConnectMode.AddString("非典型接线模式(以Ua、Uc为一侧电压，Ub、2J13-1为另一侧电压)");
	m_ConnectMode.AddString("典型接线模式(以2J12为一侧电压)");

	m_ConnectMode.SetCurSel(CMode);

//for(i=0; i<_Max_Prot_Line; i++)
//	for(i=0; i<32; i++)
//		m_ProtType.AddString(FaultName[i]);

	m_Version = mPzkIni.ProtFile.Cfg.Version;
	m_CreateTime = mPzkIni.ProtFile.Cfg.CreateTime;
	m_PNumPerLine = mPzkIni.ProtFile.Cfg.LineNum;

	if(mPzkIni.ProtFile.Cfg.Byd_SOEEnble == 255)
		m_Check1 = true;
	else
		m_Check1 = false;
	if(mPzkIni.ProtFile.Cfg.Flt_YXEnble == 255)
		m_Check2 = true;
	else
		m_Check2 = false;
	if(mPzkIni.ProtFile.Cfg.Flt_RepEnble == 255)
		m_Check3 = true;
	else
		m_Check3 = false;

	m_LineNum = mPzkIni.ProtFile.Line[0].LineCfg.LineNum;

	UpdateData(UPDATE_WRITE);
	InitListCtrl();


	SetListFocus(0);
	m_LineNo.SetCurSel(0);

	//OnSelchangeCombo1();
}

void CFaultCfgView::OnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	int LineNo;
//	int i;

//	int addItem;

	LineNo = m_LineNo.GetCurSel();
	m_LineNum = mPzkIni.ProtFile.Line[LineNo].LineCfg.LineNum;

	m_SboNo = mSbo[LineNo];//mPzkIni.ProtFile.Line[LineNo].LineCfg.Line_Sbo;
	m_SwitchNo = mSwitch[LineNo];//mPzkIni.ProtFile.Line[LineNo].LineCfg.Line_Switch;
	m_Remote = mRemote[LineNo];//mPzkIni.ProtFile.Line[LineNo].LineCfg.Line_Switch_Remote;
	m_Local = mLocal[LineNo];//mPzkIni.ProtFile.Line[LineNo].LineCfg.Line_Switch_Local;
//	m_ConnectMode.SetCurSel(CMode);//mPzkIni.ProtFile.Line[LineNo].LineCfg.V_ConnectMode);


	UpdateData(UPDATE_WRITE);

	SetListFocus(LineNo);
}

void CFaultCfgView::OnKillfocusEdit3()
{
	// TODO: Add your control notification handler code here
	//int LineNo;

	UpdateData(true);
	LineNo = m_LineNo.GetCurSel();//第几条线路


	if(m_LineNum > NumberMax[LineNo][0]+1)
	{
		AfxMessageBox("最大线路数不能超过"+Str(NumberMax[LineNo][0]+1)+"条!");
		m_LineNum = NumberMax[LineNo][0]+1;
		UpdateData(UPDATE_WRITE);
	}

	if(m_LineNum < 0)
	{
		AfxMessageBox("最小线路数不能小于"+Str(0)+"条!");
		m_LineNum = 1;
		UpdateData(UPDATE_WRITE);//控件显示
	}

	mPzkIni.ProtFile.Line[LineNo].LineCfg.LineNum = m_LineNum;//当前线路数
	LoadFaultConfig();
	SetListFocus(LineNo);

	//m_LineNo.ResetContent();
	//if(m_LineNum > 0)
	//{
	//	CString formatStr;
	//	for(int i=1; i<=m_LineNum; i++)
	//	{
	//		formatStr.Format("线路%d", i);
	//		m_LineNo.AddString(formatStr);
	//	}
	//	if( (m_LineNo.GetCount() > CurLine) && (CurLine > 0) )
	//		m_LineNo.SetCurSel(CurLine);
	//	else
	//	{
	//		m_LineNo.SetCurSel(0);
		//	OnSelchangeCombo1();
	//	}
	//}
	//else
	//{
	//	if(CurLine >= 0)
	//		listArray[CurLine]->ShowWindow(SW_HIDE);
	//}
	//*/





}

void CFaultCfgView::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	CString index_str;
	int index = m_LineNo.GetCurSel();
	m_LineNo.GetLBText(index,index_str);
	if((index_str.Compare("相间短路I段故障配置"))==0 ||(index_str.Compare("单相接地故障配置"))==0 ||(index_str.Compare("相间短路II段故障配置"))==0)
		index = 5;
	else
		index = 6;
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

	if(nSubItem == 1)
	{
		return;
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO4);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO4);
		pCombo->SetCurSel(m_List1.GetItemData(nItem));
	}
	else if(nSubItem == 2)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO3);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO3);
		str = m_List1.GetItemText(nItem, nSubItem);
		if(str.Compare("投入") == 0)
			pCombo->SetCurSel(0);
		else
			pCombo->SetCurSel(1);
	}
	else if(nSubItem != index)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT9);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT9);
		m_Input.SetWindowText(m_List1.GetItemText(nItem, nSubItem));
	}
	else
		return;
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

void CFaultCfgView::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	CMenu menu,*pSubMenu;//定义下面要用到的cmenu对象
    menu.LoadMenu(IDR_RTU_MENU);//装载自定义的右键菜单
    pSubMenu=menu.GetSubMenu(0);//获取第一个弹出菜单，所以第一个菜单必须有子菜单
    CPoint oPoint;//定义一个用于确定光标位置的位置
    GetCursorPos(&oPoint);//获取当前光标的位置，以便使得菜单可以跟随光标
    pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,oPoint.x,oPoint.y,this);   //在指定位置显示弹出菜单
	*pResult = 0;
}
void CFaultCfgView::OnClickList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CString index_str;
	int index = m_LineNo.GetCurSel();
	m_LineNo.GetLBText(index,index_str);
	if((index_str.Compare("相间短路I段故障配置"))==0 ||(index_str.Compare("单相接地故障配置"))==0 ||(index_str.Compare("相间短路II段故障配置"))==0)
		index = 5;
	else
		index = 6;
	CString str;
	CComboBox *pCombo;
	HWND pWnd;
	Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST2);
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

	if(nSubItem == 1)
	{
		return;
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO4);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO4);
		pCombo->SetCurSel(m_List2.GetItemData(nItem));
	}
	else if(nSubItem == 2)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO3);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO3);
		str = m_List2.GetItemText(nItem, nSubItem);
		if(str.Compare("投入") == 0)
			pCombo->SetCurSel(0);
		else
			pCombo->SetCurSel(1);
	}
	else if(nSubItem != index)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT9);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT9);
		m_Input.SetWindowText(m_List2.GetItemText(nItem, nSubItem));
	}
	else
		return;

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

void CFaultCfgView::OnClickList3(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CString index_str;
	int index = m_LineNo.GetCurSel();
	m_LineNo.GetLBText(index,index_str);
	if((index_str.Compare("相间短路I段故障配置"))==0 ||(index_str.Compare("单相接地故障配置"))==0 ||(index_str.Compare("相间短路II段故障配置"))==0)
		index = 5;
	else
		index = 6;
	CString str;
	CComboBox *pCombo;
	HWND pWnd;
	Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST3);
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

	if(nSubItem == 1)
	{
		return;
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO4);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO4);
		pCombo->SetCurSel(m_List3.GetItemData(nItem));
	}
	else if(nSubItem == 2)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO3);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO3);
		str = m_List3.GetItemText(nItem, nSubItem);
		if(str.Compare("投入") == 0)
			pCombo->SetCurSel(0);
		else
			pCombo->SetCurSel(1);
	}
	else if(nSubItem != index)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT9);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT9);
		m_Input.SetWindowText(m_List3.GetItemText(nItem, nSubItem));
	}
	else
		return;

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

void CFaultCfgView::OnClickList4(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CString index_str;
	int index = m_LineNo.GetCurSel();
	m_LineNo.GetLBText(index,index_str);
	if((index_str.Compare("相间短路I段故障配置"))==0 ||(index_str.Compare("单相接地故障配置"))==0 ||(index_str.Compare("相间短路II段故障配置"))==0)
		index = 5;
	else
		index = 6;
	CString str;
	CComboBox *pCombo;
	HWND pWnd;
	Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST4);
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

	if(nSubItem == 1)
	{
		return;
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO4);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO4);
		pCombo->SetCurSel(m_List4.GetItemData(nItem));
	}
	else if(nSubItem == 2)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO3);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO3);
		str = m_List4.GetItemText(nItem, nSubItem);
		if(str.Compare("投入") == 0)
			pCombo->SetCurSel(0);
		else
			pCombo->SetCurSel(1);
	}
	else if(nSubItem != index)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT9);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT9);
		m_Input.SetWindowText(m_List4.GetItemText(nItem, nSubItem));
	}
	else
		return;

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

void CFaultCfgView::OnClickList5(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CString index_str;
	int index = m_LineNo.GetCurSel();
	m_LineNo.GetLBText(index,index_str);
	if((index_str.Compare("相间短路I段故障配置"))==0 ||(index_str.Compare("单相接地故障配置"))==0 ||(index_str.Compare("相间短路II段故障配置"))==0)		index = 5;
	else
		index = 6;
	CString str;
	CComboBox *pCombo;
	HWND pWnd;
	Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST5);
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

	if(nSubItem == 1)
	{
		return;
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO4);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO4);
		pCombo->SetCurSel(m_List5.GetItemData(nItem));
	}
	else if(nSubItem == 2)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO3);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO3);
		str = m_List5.GetItemText(nItem, nSubItem);
		if(str.Compare("投入") == 0)
			pCombo->SetCurSel(0);
		else
			pCombo->SetCurSel(1);
	}
	else if(nSubItem != index)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT9);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT9);
		m_Input.SetWindowText(m_List5.GetItemText(nItem, nSubItem));
	}
	else
		return;

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

LRESULT CFaultCfgView::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)
{
//	OnCANCEl();
	return TRUE;
}

LRESULT CFaultCfgView::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)
{
	if(bEverEdited)
	{
		int i = AfxMessageBox("保存当前对保护项配置所做的修改吗？",MB_YESNOCANCEL);
		if(i == IDYES)
			OnSave();
		else if(i == IDCANCEL)
		{
//			bCloseWindow = false;
			return FALSE;
		}
		else
			;//OnCancel();
	}
	return TRUE;
}

void CFaultCfgView::OnSave()
{
	// TODO: Add your control notification handler code here
	int i,j;
	CString str;

	UpdateData(UPDATE_READ);
	mPzkIni.ProtFile.Cfg.Version = m_Version;
	mPzkIni.ProtFile.Cfg.CreateTime = m_CreateTime;

	if(m_Check1 == true)
	{
		mPzkIni.ProtFile.Cfg.Byd_SOEEnble = 255;
	}
	else
	{
		mPzkIni.ProtFile.Cfg.Byd_SOEEnble = 0;
	}
	if(m_Check2 == true)
	{
		mPzkIni.ProtFile.Cfg.Flt_YXEnble = 255;
	}
	else
	{
		mPzkIni.ProtFile.Cfg.Flt_YXEnble = 0;
	}
	if(m_Check3 == true)
	{
		mPzkIni.ProtFile.Cfg.Flt_RepEnble = 255;
	}
	else
	{
		mPzkIni.ProtFile.Cfg.Flt_RepEnble = 0;
	}

		/*     旧有保护方式字的配置，在每一个线路里面配置远方就地、接线方式等配置
		mPzkIni.ProtFile.Line[i].LineCfg.Line_Sbo = mSbo[i];
		mPzkIni.ProtFile.Line[i].LineCfg.Line_Switch = mSwitch[i];
		mPzkIni.ProtFile.Line[i].LineCfg.Line_Switch_Remote = mRemote[i];
		mPzkIni.ProtFile.Line[i].LineCfg.Line_Switch_Local = mLocal[i];
		mPzkIni.ProtFile.Line[i].LineCfg.V_ConnectMode = mMode[i];
		*/

	/*
    for(i = 0; i < 3; i++)
	{
		for(j = 0; j < mPzkIni.ProtFile.Line[i].LineCfg.LineNum; j++)
		{
			mPzkIni.ProtFile.Line[i].ProtItem[j].Name = listArray[i]->GetItemText(j,1);
			//mPzkIni.ProtFile.Line[i].ProtItem[j].Type = myatoi(listArray[i]->GetItemText(j,1));//by lz 2015/1/8
			mPzkIni.ProtFile.Line[i].ProtItem[j].Enable = (listArray[i]->GetItemText(j,2) == "投入")? 255 : 0;
			mPzkIni.ProtFile.Line[i].ProtItem[j].Value1 = myatof(listArray[i]->GetItemText(j,3));
			mPzkIni.ProtFile.Line[i].ProtItem[j].Value2 = myatof(listArray[i]->GetItemText(j,4));
			mPzkIni.ProtFile.Line[i].ProtItem[j].Time = myatof(listArray[i]->GetItemText(j,5));
		}
	}
	for(i = 3; i < 6; i++)
	{
		for(j = 0; j < mPzkIni.ProtFile.Line[i].LineCfg.LineNum; j++)
		{
			mPzkIni.ProtFile.Line[i].ProtItem[j].Name = listArray[i]->GetItemText(j,1);
			//mPzkIni.ProtFile.Line[i].ProtItem[j].Type = myatoi(listArray[i]->GetItemText(j,1));//by lz 2015/1/8
			mPzkIni.ProtFile.Line[i].ProtItem[j].Enable = (listArray[i]->GetItemText(j,2) == "投入")? 255 : 0;
			mPzkIni.ProtFile.Line[i].ProtItem[j].Value1 = myatof(listArray[i]->GetItemText(j,3));
			mPzkIni.ProtFile.Line[i].ProtItem[j].Time = myatof(listArray[i]->GetItemText(j,4));
		}
	}

	*/

	bool flt_3I0_oldd = flt_3I0;
	bool flt1_Current_oldd = flt1_Current;
	bool flt2_Current_oldd = flt2_Current;
	bool byd_ZeroU_oldd = byd_ZeroU;
	bool byd_ZeroI_oldd = byd_ZeroI ;
	bool byd_Voltage_oldd =  byd_Voltage;
	bool byd_Current_oldd = byd_Current;
	for(i = 0; i < 7; i++)
	{
		if(byd_Current==true)
		{
			byd_Current=false;
			for(j = 0; j < mPzkIni.ProtFile.Line[i].LineCfg.LineNum; j++)
			{
				mPzkIni.ProtFile.Line[i].ProtItem[j].Name = Str(atoi(listArray[i]->GetItemText(j,1))-1);
				//mPzkIni.ProtFile.Line[i].ProtItem[j].Type = myatoi(listArray[i]->GetItemText(j,1));//by lz 2015/1/8
				mPzkIni.ProtFile.Line[i].ProtItem[j].Enable = (listArray[i]->GetItemText(j,2) == "投入")? 255 : 0;
				mPzkIni.ProtFile.Line[i].ProtItem[j].Value1 = myatof(listArray[i]->GetItemText(j,3));
				mPzkIni.ProtFile.Line[i].ProtItem[j].Value2 = myatof(listArray[i]->GetItemText(j,4));
				mPzkIni.ProtFile.Line[i].ProtItem[j].Time = myatof(listArray[i]->GetItemText(j,5));
			}
		}
		else if(byd_Voltage==true)
		{
			byd_Voltage=false;
			for(j = 0; j < mPzkIni.ProtFile.Line[i].LineCfg.LineNum; j++)
			{
				mPzkIni.ProtFile.Line[i].ProtItem[j].Name = Str(atoi(listArray[i]->GetItemText(j,1))-1);
				//mPzkIni.ProtFile.Line[i].ProtItem[j].Type = myatoi(listArray[i]->GetItemText(j,1));//by lz 2015/1/8
				mPzkIni.ProtFile.Line[i].ProtItem[j].Enable = (listArray[i]->GetItemText(j,2) == "投入")? 255 : 0;
				mPzkIni.ProtFile.Line[i].ProtItem[j].Value1 = myatof(listArray[i]->GetItemText(j,3));
				mPzkIni.ProtFile.Line[i].ProtItem[j].Value2 = myatof(listArray[i]->GetItemText(j,4));
				mPzkIni.ProtFile.Line[i].ProtItem[j].Time = myatof(listArray[i]->GetItemText(j,5));
			}
		}
		else if(byd_ZeroI==true)
		{
			byd_ZeroI=false;
			for(j = 0; j < mPzkIni.ProtFile.Line[i].LineCfg.LineNum; j++)
			{
				mPzkIni.ProtFile.Line[i].ProtItem[j].Name = Str(atoi(listArray[i]->GetItemText(j,1))-1);
				//mPzkIni.ProtFile.Line[i].ProtItem[j].Type = myatoi(listArray[i]->GetItemText(j,1));//by lz 2015/1/8
				mPzkIni.ProtFile.Line[i].ProtItem[j].Enable = (listArray[i]->GetItemText(j,2) == "投入")? 255 : 0;
				mPzkIni.ProtFile.Line[i].ProtItem[j].Value1 = myatof(listArray[i]->GetItemText(j,3));
				mPzkIni.ProtFile.Line[i].ProtItem[j].Value2 = myatof(listArray[i]->GetItemText(j,4));
				mPzkIni.ProtFile.Line[i].ProtItem[j].Time = myatof(listArray[i]->GetItemText(j,5));
			}
		}
		else if(byd_ZeroU==true)
		{
			byd_ZeroU=false;
			for(j = 0; j < mPzkIni.ProtFile.Line[i].LineCfg.LineNum; j++)
			{
				mPzkIni.ProtFile.Line[i].ProtItem[j].Name = Str(atoi(listArray[i]->GetItemText(j,1))-1);
				//mPzkIni.ProtFile.Line[i].ProtItem[j].Type = myatoi(listArray[i]->GetItemText(j,1));//by lz 2015/1/8
				mPzkIni.ProtFile.Line[i].ProtItem[j].Enable = (listArray[i]->GetItemText(j,2) == "投入")? 255 : 0;
				mPzkIni.ProtFile.Line[i].ProtItem[j].Value1 = myatof(listArray[i]->GetItemText(j,3));
				mPzkIni.ProtFile.Line[i].ProtItem[j].Value2 = myatof(listArray[i]->GetItemText(j,4));
				mPzkIni.ProtFile.Line[i].ProtItem[j].Time = myatof(listArray[i]->GetItemText(j,5));
			}
		}
		else if(flt1_Current==true)
		{
			flt1_Current=false;
			for(j = 0; j < mPzkIni.ProtFile.Line[i].LineCfg.LineNum; j++)
			{
				mPzkIni.ProtFile.Line[i].ProtItem[j].Name = Str(atoi(listArray[i]->GetItemText(j,1))-1);
				//mPzkIni.ProtFile.Line[i].ProtItem[j].Type = myatoi(listArray[i]->GetItemText(j,1));//by lz 2015/1/8
				mPzkIni.ProtFile.Line[i].ProtItem[j].Enable = (listArray[i]->GetItemText(j,2) == "投入")? 255 : 0;
				mPzkIni.ProtFile.Line[i].ProtItem[j].Value1 = myatof(listArray[i]->GetItemText(j,3));
				mPzkIni.ProtFile.Line[i].ProtItem[j].Time = myatof(listArray[i]->GetItemText(j,4));
			}
		}
		else if(flt2_Current==true)
		{
			flt2_Current=false;
			for(j = 0; j < mPzkIni.ProtFile.Line[i].LineCfg.LineNum; j++)
			{
				mPzkIni.ProtFile.Line[i].ProtItem[j].Name = Str(atoi(listArray[i]->GetItemText(j,1))-1);
				//mPzkIni.ProtFile.Line[i].ProtItem[j].Type = myatoi(listArray[i]->GetItemText(j,1));//by lz 2015/1/8
				mPzkIni.ProtFile.Line[i].ProtItem[j].Enable = (listArray[i]->GetItemText(j,2) == "投入")? 255 : 0;
				mPzkIni.ProtFile.Line[i].ProtItem[j].Value1 = myatof(listArray[i]->GetItemText(j,3));
				mPzkIni.ProtFile.Line[i].ProtItem[j].Time = myatof(listArray[i]->GetItemText(j,4));
			}
		}
		else if(flt_3I0==true)
		{
			flt_3I0=false;
			for(j = 0; j < mPzkIni.ProtFile.Line[i].LineCfg.LineNum; j++)
			{
				mPzkIni.ProtFile.Line[i].ProtItem[j].Name = Str(atoi(listArray[i]->GetItemText(j,1))-1);
				//mPzkIni.ProtFile.Line[i].ProtItem[j].Type = myatoi(listArray[i]->GetItemText(j,1));//by lz 2015/1/8
				mPzkIni.ProtFile.Line[i].ProtItem[j].Enable = (listArray[i]->GetItemText(j,2) == "投入")? 255 : 0;
				mPzkIni.ProtFile.Line[i].ProtItem[j].Value1 = myatof(listArray[i]->GetItemText(j,3));
				mPzkIni.ProtFile.Line[i].ProtItem[j].Time = myatof(listArray[i]->GetItemText(j,4));
			}
		}
	}

	 flt_3I0 = flt_3I0_oldd;
	 flt1_Current = flt1_Current_oldd;
	 flt2_Current = flt2_Current_oldd;
	 byd_ZeroU = byd_ZeroU_oldd;
	 byd_ZeroI = byd_ZeroI_oldd;
	 byd_Voltage =  byd_Voltage_oldd;
	 byd_Current = byd_Current_oldd;



	bEverEdited = false;
	mPzkIni.EverModified = true;
	yulan();
}

void CFaultCfgView::OnCancel()
{
	// TODO: Add your control notification handler code here
	int i;

	m_Version = mPzkIni.ProtFile.Cfg.Version;
	m_CreateTime = mPzkIni.ProtFile.Cfg.CreateTime;
	m_LineNum = mPzkIni.ProtFile.Cfg.LineNum;
	m_PNumPerLine = mPzkIni.ProtFile.Cfg.PNPL;

	for(i=0; i<5; i++)
	{
		mSbo[i] = mPzkIni.ProtFile.Line[i].LineCfg.Line_Sbo;
		mSwitch[i] = mPzkIni.ProtFile.Line[i].LineCfg.Line_Switch;
		mRemote[i] = mPzkIni.ProtFile.Line[i].LineCfg.Line_Switch_Remote;
		mLocal[i] = mPzkIni.ProtFile.Line[i].LineCfg.Line_Switch_Local;
		mMode[i] = mPzkIni.ProtFile.Line[i].LineCfg.V_ConnectMode;
	}

	UpdateData(UPDATE_WRITE);

//	if(m_LineNum > 0)
//	{
//		CString formatStr;
//		m_LineNo.ResetContent();
//		for(i=1; i<=m_LineNum; i++)
//		{
//			formatStr.Format("线路%d", i);
//			m_LineNo.AddString(formatStr);
//		}
//		SetListFocus(0);
//		m_LineNo.SetCurSel(0);
//	}
//	else
	SetListFocus(-1);
	LoadFaultConfig();
	OnSelchangeCombo1();
	bEverEdited = false;
}

void CFaultCfgView::OnKillfocusEdit4()
{
	// TODO: Add your control notification handler code here
	UpdateData(UPDATE_READ);
	if(m_PNumPerLine > 32)
	{
		AfxMessageBox("每条线路的最大保护数不能超过32个!");
		m_PNumPerLine = 32;
		UpdateData(UPDATE_WRITE);
	}
	int LineNo;
	int addItem;
	for(LineNo=0; LineNo<5; LineNo++)
	{
		listArray[LineNo]->DeleteAllItems();
		for(int i=0; i<7; i++)
		{
			addItem = listArray[LineNo]->InsertItem(i, Str(i), 0);
			listArray[LineNo]->SetItemData(addItem, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type);
			listArray[LineNo]->SetItemText(addItem, 1, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Name);//FaultName[mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type]);
			if(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Enable)
				listArray[LineNo]->SetItemText(addItem, 2, "投入");
			else
				listArray[LineNo]->SetItemText(addItem, 2, "FASLE");
			listArray[LineNo]->SetItemText(addItem, 3, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value1));
			listArray[LineNo]->SetItemText(addItem, 4, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Time));
			listArray[LineNo]->SetItemText(addItem, 5, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Unit);
		}
	}
	bEverEdited = false;
}

void CFaultCfgView::OnChangeEdit1()
{
	bEverEdited = true;
}

void CFaultCfgView::OnChangeEdit2()
{
	bEverEdited = true;
}

void CFaultCfgView::OnChangeEdit3()
{

	bEverEdited = true;
}

void CFaultCfgView::OnChangeEdit4()
{
	bEverEdited = true;
}

void CFaultCfgView::OnChangeEdit5()
{
	bEverEdited = true;
}
void CFaultCfgView::OnChangeEdit6()
{
	bEverEdited = true;
}

void CFaultCfgView::OnChangeEdit7()
{
	bEverEdited = true;
}

void CFaultCfgView::OnChangeEdit8()
{
	bEverEdited = true;
}

void CFaultCfgView::OnKillfocusCombo3()
{
	// TODO: Add your control notification handler code here
	if(m_Enable.GetCurSel() == 0)
		listArray[m_LineNo.GetCurSel()]->SetItemText(nItem, nSubItem, "投入");
	else
		listArray[m_LineNo.GetCurSel()]->SetItemText(nItem, nSubItem, "退出");
	m_Enable.ShowWindow(SW_HIDE);
	bEverEdited = true;
}

void CFaultCfgView::OnKillfocusCombo4()
{
	// TODO: Add your control notification handler code here
	int LineNo = m_LineNo.GetCurSel();
	listArray[m_LineNo.GetCurSel()]->SetItemText(nItem, nSubItem, FaultName[m_ProtType.GetCurSel()]);
	listArray[m_LineNo.GetCurSel()]->SetItemData(nItem, m_ProtType.GetCurSel());
	listArray[m_LineNo.GetCurSel()]->SetItemText(nItem, 5, mPzkIni.ProtFile.Line[LineNo].ProtItem[m_ProtType.GetCurSel()].Unit);
	m_ProtType.ShowWindow(SW_HIDE);
	bEverEdited = true;
}

void CFaultCfgView::OnKillfocusEdit9()
{
	// TODO: Add your control notification handler code here
	CString str;
	m_Input.GetWindowText(str);
	int flag = CheckNum(str);
	if(flag ==1)
	{
		AfxMessageBox("请输入正确的数据格式!");
	}
	else if(flag == 2)
	{
		AfxMessageBox("请输入正确的数字!");
	}
	else
	{
		listArray[m_LineNo.GetCurSel()]->SetItemText(nItem, nSubItem, str);
		m_Input.ShowWindow(SW_HIDE);
		bEverEdited = true;
	}
}

void CFaultCfgView::OnKillfocusEdit5()
{
	// TODO: Add your control notification handler code here
	int LineNo = m_LineNo.GetCurSel();
	if(LineNo < 0)
		return;
	UpdateData(UPDATE_READ);
	mSbo[LineNo] = m_SboNo;
}

void CFaultCfgView::OnKillfocusEdit6()
{
	// TODO: Add your control notification handler code here
	int LineNo = m_LineNo.GetCurSel();
	if(LineNo < 0)
		return;
	UpdateData(UPDATE_READ);
	mSwitch[LineNo] = m_SwitchNo;
}

void CFaultCfgView::OnKillfocusEdit7()
{
	// TODO: Add your control notification handler code here
	int LineNo = m_LineNo.GetCurSel();
	if(LineNo < 0)
		return;
	UpdateData(UPDATE_READ);
	mRemote[LineNo] = m_Remote;
}

void CFaultCfgView::OnKillfocusEdit8()
{
	// TODO: Add your control notification handler code here
	int LineNo = m_LineNo.GetCurSel();
	if(LineNo < 0)
		return;
	UpdateData(UPDATE_READ);
	mLocal[LineNo] = m_Local;
}

void CFaultCfgView::OnKillfocusCombo2()
{
	// TODO: Add your control notification handler code here
	int LineNo = m_LineNo.GetCurSel();
	if(LineNo < 0)
		return;
	mMode[LineNo] = m_ConnectMode.GetCurSel();
}

void CFaultCfgView::OnSelchangeCombo2()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CFaultCfgView::OnClickList6(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	CString index_str;
	int index = m_LineNo.GetCurSel();
	m_LineNo.GetLBText(index,index_str);
	if((index_str.Compare("相间短路I段故障配置"))==0 ||(index_str.Compare("单相接地故障配置"))==0 ||(index_str.Compare("相间短路II段故障配置"))==0)		index = 5;
	else
		index = 6;
	CString str;
	CComboBox *pCombo;
	HWND pWnd;
	Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST6);
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

	if(nSubItem == 1)
	{
		return;
	}
	else if(nSubItem == 2)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO3);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO3);
		str = m_List6.GetItemText(nItem, nSubItem);
		if(str.Compare("投入") == 0)
			pCombo->SetCurSel(0);
		else
			pCombo->SetCurSel(1);
	}
	else if(nSubItem != index)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT9);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT9);
		m_Input.SetWindowText(m_List6.GetItemText(nItem, nSubItem));
	}
	else
		return;

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

void CFaultCfgView::OnClickList7(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CString index_str;
	int index = m_LineNo.GetCurSel();
	m_LineNo.GetLBText(index,index_str);
	if((index_str.Compare("相间短路I段故障配置"))==0 ||(index_str.Compare("单相接地故障配置"))==0 ||(index_str.Compare("相间短路II段故障配置"))==0)		index = 5;
	else
		index = 6;
	CString str;
	CComboBox *pCombo;
	HWND pWnd;
	Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST7);
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

	if(nSubItem == 1)
	{
		return;
	}
	else if(nSubItem == 2)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO3);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO3);
		str = m_List7.GetItemText(nItem, nSubItem);
		if(str.Compare("投入") == 0)
			pCombo->SetCurSel(0);
		else
			pCombo->SetCurSel(1);
	}
	else if(nSubItem != index)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT9);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT9);
		m_Input.SetWindowText(m_List7.GetItemText(nItem, nSubItem));
	}
	else
		return;

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

void CFaultCfgView::OnClickList8(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CString str;
	CComboBox *pCombo;
	HWND pWnd;
	Invalidate();
	//HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST8);
	int LineNo = m_LineNo.GetCurSel();
	if( (LineNo < 0) || (LineNo >= _Max_Prot_Line) )
		return;
	HWND hWnd1 = listArray[LineNo]->m_hWnd;
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

	if(nSubItem == 1)
	{
		return;

	}
	else if(nSubItem == 2)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO3);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO3);
		str = listArray[LineNo]->GetItemText(nItem, nSubItem);
		if(str.Compare("投入") == 0)
			pCombo->SetCurSel(0);
		else
			pCombo->SetCurSel(1);
	}
	else if(nSubItem != 5)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT9);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT9);
		m_Input.SetWindowText(listArray[LineNo]->GetItemText(nItem, nSubItem));
	}
	else
		return;

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

void CFaultCfgView::OnCheck1()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CFaultCfgView::OnCheck2()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CFaultCfgView::OnCheck3()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CFaultCfgView::yulan()
{


	int i;
	int j;
	CString str;
	CString str1;
	CString str2;


	/*
	if(byd_Voltage == true)
	m_LineNo.AddString("电压回路-越限告警定值设定");
	if(byd_ZeroI == true)
	m_LineNo.AddString("零序电流回路-越限告警定值设定");
	if(byd_ZeroU == true)
	m_LineNo.AddString("零序电压回路-越限告警定值设定");
	if(flt1_Current == true)
	m_LineNo.AddString("相间短路I段故障配置");
	if(flt2_Current == true)
	m_LineNo.AddString("相间短路II段故障配置");
	if(flt_3I0 == true)
	m_LineNo.AddString("单相接地故障配置");
	*/
	//str.Format("线路%d", LineIndex+1);

	bool flt_3I0_1 = flt_3I0;
	bool flt1_Current_1 = flt1_Current;
	bool flt2_Current_1 = flt2_Current;
	bool byd_ZeroU_1 = byd_ZeroU;
	bool byd_ZeroI_1 = byd_ZeroI ;
	bool byd_Voltage_1 =  byd_Voltage;
	bool byd_Current_1 = byd_Current;

	for(i = 0; i < 7; i++)
	{
		if(byd_Current_1==true)
		{
			str+="电流回路-越限告警定值设定";
			str+="\r\n";
			str += "线路数      投/退      上限值      下限值    时间";
			str += "\r\n";
			for(j = 0; j < mPzkIni.ProtFile.Line[i].LineCfg.LineNum; j++)
			{
				str +="线路";
				str += Str(atoi(mPzkIni.ProtFile.Line[i].ProtItem[j].Name)+1);
				str += "        ";
				if(mPzkIni.ProtFile.Line[i].ProtItem[j].Enable == 0)
				{
					str += "退出         ";
				}
				else
				{
					str += "投入         ";
				}
				str += Str(mPzkIni.ProtFile.Line[i].ProtItem[j].Value1);
				str += "          ";
				str += Str(mPzkIni.ProtFile.Line[i].ProtItem[j].Value2);
				str += "        ";
				str += Str(mPzkIni.ProtFile.Line[i].ProtItem[j].Time);
				str += "\r\n";
			}
			byd_Current_1 = false;
			str += "\r\n";
		}

		else if(byd_Voltage_1==true)
		{
			str+="电压回路-越限告警定值设定";
			str+="\r\n";
			str += "线路数      投/退      上限值      下限值    时间";
			str += "\r\n";
			for(j = 0; j < mPzkIni.ProtFile.Line[i].LineCfg.LineNum; j++)
			{
				str +="线路";
				str += Str(atoi(mPzkIni.ProtFile.Line[i].ProtItem[j].Name)+1);
				str += "        ";
				if(mPzkIni.ProtFile.Line[i].ProtItem[j].Enable == 0)
				{
					str += "退出         ";
				}
				else
				{
					str += "投入         ";
				}
				str += Str(mPzkIni.ProtFile.Line[i].ProtItem[j].Value1);
				str += "           ";
				str += Str(mPzkIni.ProtFile.Line[i].ProtItem[j].Value2);
				str += "         ";
				str += Str(mPzkIni.ProtFile.Line[i].ProtItem[j].Time);
				str += "\r\n";
			}
			byd_Voltage_1=false;
			str += "\r\n";
		}
		else if(byd_ZeroI_1==true)
		{
			str+="零序电流回路-越限告警定值设定";
			str+="\r\n";
			str += "线路数      投/退      上限值      下限值    时间";
			str += "\r\n";
			for(j = 0; j < mPzkIni.ProtFile.Line[i].LineCfg.LineNum; j++)
			{
				str +="线路";
				str += Str(atoi(mPzkIni.ProtFile.Line[i].ProtItem[j].Name)+1);
				str += "        ";
				if(mPzkIni.ProtFile.Line[i].ProtItem[j].Enable == 0)
				{
					str += "退出         ";
				}
				else //本来读取文件时，就直接读取0和255就行，结果做了转换(布尔)，但是保存时候还弄成了
					//0和255那种保存，就是说 0永远是退出，但是投入刚开始会是1，保存时候会是255
				{
					str += "投入         ";
				}
				str += Str(mPzkIni.ProtFile.Line[i].ProtItem[j].Value1);
				str += "           ";
				str += Str(mPzkIni.ProtFile.Line[i].ProtItem[j].Value2);
				str += "         ";
				str += Str(mPzkIni.ProtFile.Line[i].ProtItem[j].Time);
				str += "\r\n";
			}
			byd_ZeroI_1=false;
			str += "\r\n";
		}

		else if(byd_ZeroU_1==true)
		{
			str+="零序电压回路-越限告警定值设定";
			str+="\r\n";

			str += "线路数      投/退      上限值      下限值    时间";
			str += "\r\n";
			for(j = 0; j < mPzkIni.ProtFile.Line[i].LineCfg.LineNum; j++)
			{
				str +="线路";
				str += Str(atoi(mPzkIni.ProtFile.Line[i].ProtItem[j].Name)+1);
				str += "        ";
				if(mPzkIni.ProtFile.Line[i].ProtItem[j].Enable == 0)
				{
					str += "退出         ";
				}
				else //本来读取文件时，就直接读取0和255就行，结果做了转换(布尔)，但是保存时候还弄成了
					//0和255那种保存，就是说 0永远是退出，但是投入刚开始会是1，保存时候会是255
				{
					str += "投入         ";
				}
				str += Str(mPzkIni.ProtFile.Line[i].ProtItem[j].Value1);
				str += "           ";
				str += Str(mPzkIni.ProtFile.Line[i].ProtItem[j].Value2);
				str += "         ";
				str += Str(mPzkIni.ProtFile.Line[i].ProtItem[j].Time);
				str += "\r\n";
			}
			byd_ZeroU_1=false;
			str += "\r\n";
		}

		else if(flt1_Current_1==true)
		{
			str+="相间短路I段故障配置";
			str+="\r\n";

			str += "线路数      投/退       定值            时间";
			str += "\r\n";
			for(j = 0; j < mPzkIni.ProtFile.Line[i].LineCfg.LineNum; j++)
			{
				str +="线路";
				str += Str(atoi(mPzkIni.ProtFile.Line[i].ProtItem[j].Name)+1);
				str += "        ";
				if(mPzkIni.ProtFile.Line[i].ProtItem[j].Enable == 0)
				{
					str += "退出         ";
				}
				else //本来读取文件时，就直接读取0和255就行，结果做了转换(布尔)，但是保存时候还弄成了
					//0和255那种保存，就是说 0永远是退出，但是投入刚开始会是1，保存时候会是255
				{
					str += "投入         ";
				}
				str += Str(mPzkIni.ProtFile.Line[i].ProtItem[j].Value1);
				str += "             ";
				str += Str(mPzkIni.ProtFile.Line[i].ProtItem[j].Time);
				str += "\r\n";
			}
			flt1_Current_1=false;
			str += "\r\n";
		}

		else if(flt2_Current_1==true)
		{
			str+="相间短路II段故障配置";
			str+="\r\n";

			str += "线路数      投/退       定值            时间";
			str += "\r\n";
			for(j = 0; j < mPzkIni.ProtFile.Line[i].LineCfg.LineNum; j++)
			{
				str +="线路";
				str += Str(atoi(mPzkIni.ProtFile.Line[i].ProtItem[j].Name)+1);
				str += "        ";
				if(mPzkIni.ProtFile.Line[i].ProtItem[j].Enable == 0)
				{
					str += "退出         ";
				}
				else //本来读取文件时，就直接读取0和255就行，结果做了转换(布尔)，但是保存时候还弄成了
					//0和255那种保存，就是说 0永远是退出，但是投入刚开始会是1，保存时候会是255
				{
					str += "投入         ";
				}
				str += Str(mPzkIni.ProtFile.Line[i].ProtItem[j].Value1);
				str += "             ";
				str += Str(mPzkIni.ProtFile.Line[i].ProtItem[j].Time);
				str += "\r\n";
			}
			flt2_Current_1=false;
			str += "\r\n";
		}
		else if(flt_3I0_1==true)
		{
			str+="单相接地故障配置";
			str+="\r\n";

			str += "线路数      投/退       定值            时间";
			str += "\r\n";
			for(j = 0; j < mPzkIni.ProtFile.Line[i].LineCfg.LineNum; j++)
			{
				str +="线路";
				str += Str(atoi(mPzkIni.ProtFile.Line[i].ProtItem[j].Name)+1);
				str += "        ";
				if(mPzkIni.ProtFile.Line[i].ProtItem[j].Enable == 0)
				{
					str += "退出         ";
				}
				else //本来读取文件时，就直接读取0和255就行，结果做了转换(布尔)，但是保存时候还弄成了
					//0和255那种保存，就是说 0永远是退出，但是投入刚开始会是1，保存时候会是255
				{
					str += "投入         ";
				}
				str += Str(mPzkIni.ProtFile.Line[i].ProtItem[j].Value1);
				str += "             ";
				str += Str(mPzkIni.ProtFile.Line[i].ProtItem[j].Time);
				str += "\r\n";
			}
			flt_3I0_1=false;
		}

	}


	CEdit*pEdt=(CEdit*)GetDlgItem(IDC_EDIT10);
	font1.CreatePointFont(100,"Arial");
	pEdt->SetFont(&font1);
	SetDlgItemText(IDC_EDIT10,str);





}
