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
extern int SXJZS_Select[SWITCH_KIND][SELECT];//绍兴集中式 读取prot_select里面的数据到数组
extern int SXJZS_FACT_SELECT[SELECT];//实际的值大小
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
		listArray[j]->InsertColumn(i++, "序号", LVCFMT_LEFT, 40, -1);
		listArray[j]->InsertColumn(i++, "名称", LVCFMT_LEFT, 130, -1);
		listArray[j]->InsertColumn(i++, "动作/告警", LVCFMT_CENTER, 80, -1);
		listArray[j]->InsertColumn(i++, "定值(A/V)", LVCFMT_RIGHT, 80, -1);
		listArray[j]->InsertColumn(i++, "时间(s)", LVCFMT_RIGHT, 90, -1);
		listArray[j]->InsertColumn(i++, "精度/备注", LVCFMT_RIGHT, 151, -1);
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
	bool gaojing_flag=false;//有无告警标志位
	   bool dongzuo_flag=false;//有无动作标志位

	bool flag=false;
	bool flag1=false;//有无退出标志位
	int StartIndex,EndIndex;
	int addItem;

		// TODO: Add your control notification handler code here
//	int LineNo = m_LineNo.GetCurSel();//得到当前线路号


	m_ZXCHZTime=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.ZXCHZTime;//主线重合闸时间
	m_FZXCHZTime=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.FZXCHZTime;//分支线重合闸时间

//	CString cs;
//	cs.Format("m_FZXCHZTime=%d",mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.ZXCHZTime);
//	AfxMessageBox(cs);


	m_strEdit = mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Name;
	LineType=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type;
//	m_LineType.SetCurSel(LineType);//#线路类型:0-主线;1-分支线


	SwitchType=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type;
//		CString cs;
//	cs.Format("开关类型%d",SwitchType);
//	AfxMessageBox(cs);
//	m_SwitchType.SetCurSel(SwitchType);//开关类型(0-断路器, 1-负荷开关)

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

	m_SboNum=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.SBO_Num;//#线路SBO号

	m_SwitchNum=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Num;//#线路开关号

	if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CxLogicFlag == 255)//#判出线逻辑
	{
		m_Check1 = true;
	}
	else
	{
		m_Check1 = false;
	}


	if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255)//重合使能
	{
		m_Check2 = true;
		GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		if(LineType == 0)//重合闸使能并且 线路为主线时才会 判出线逻辑
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
//	cs.Format("现在是%d",SwitchType);
//	AfxMessageBox(cs);

	if( (SwitchType == 1) )//选中重合闸并且开关类型为负荷开关 //为开关开关下拉变化时,触发此条件
	{
		if(m_Check2 == true)
		{//			CString cs;
//	cs.Format("%d",SwitchType);
//	AfxMessageBox(cs);
		AfxMessageBox("开关类型为负荷开关时不能启动重合闸!");
		}
	//	m_Check2=false;
	//	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable = 0;
	//	GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
	//	GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);

	}

		//SXJZS_FACT_SELECT 数组存放 显示的个数
		//SXJZS_Select 显示某个开关里面的数字
		for(i=0;i<SXJZS_FACT_SELECT[SwitchType];i++)//原来是<= 最后一个不判断了，因此变成了<
		{
			int j=SXJZS_Select[SwitchType][i];
			if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==1)
			{
				gaojing_flag=true;//存在告警
			}

		}

		for(i=0;i<SXJZS_FACT_SELECT[SwitchType];i++)//原来是<= 最后一个不判断了，因此变成了<
		{
			int j=SXJZS_Select[SwitchType][i];
			if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==255)
			{
				dongzuo_flag=true;//存在动作
			}

		}

		if( gaojing_flag == true && dongzuo_flag== true)
		{
				AfxMessageBox("告警、动作不能同时存在!");
		}
	/*
	else if(m_Enable.GetCurSel() == 2)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "退出");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=0;

		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255)//重合使能
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

	if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PHaveV_Flag  == 255)//重合闸判有压标志
	{
		m_Check3 = true;
	}
	else
	{
		m_Check3 = false;
	}

	if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PSwitchStatus  == 255)//判开关位置
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
	if(SwitchType == 0)//断路器
	{
		StartIndex =0;
		EndIndex=4;
	}
	else if(SwitchType == 1)//负荷开关
	{
		StartIndex =4;
		EndIndex=5;
	}
	else if(SwitchType == 2)//组合电器 熔断器
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
			listArray[0]->SetItemText(addItem, 2, "动作");
		else if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Enable == 1)
			listArray[0]->SetItemText(addItem, 2, "告警");
		else if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Enable == 0)
			listArray[0]->SetItemText(addItem, 2, "退出");
		listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Value));
		listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Time));
		listArray[0]->SetItemText(addItem, 5, mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Unit);
	}
*/
	int index;
	bool zuhedianqi_have_dongzuo=false;//组合电器含有动作 则 弹出窗口
	for(i=0; i<=SXJZS_FACT_SELECT[SwitchType]; i++)//每种开关类型有几个数据
	{
		index=SXJZS_Select[SwitchType][i];//switchtype：开关类型 i:第几个数据
		addItem = listArray[0]->InsertItem(i, Str(i), 0);
		listArray[0]->SetItemData(addItem, mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Type);
		listArray[0]->SetItemText(addItem, 1, mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Name);
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable == 255)
		{
			listArray[0]->SetItemText(addItem, 2, "动作");
			if(SwitchType == 2 && index !=5)
			{
				zuhedianqi_have_dongzuo = true;//组合电器中含有动作选项
			}
		}

		else if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable == 1)
		{
			listArray[0]->SetItemText(addItem, 2, "告警");
			//此时的index是 prot序号.从0开始的
			if((SwitchType ==0  && index != 5) || (SwitchType ==1 && index != 5) ||(SwitchType ==2 && index !=5 ))//如果是4的话，就直接忽略掉了，不用检索了
			{
				flag=true;//有告警
			}
		}
		else if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable == 0)
		{
			listArray[0]->SetItemText(addItem, 2, "退出");
			flag1=true;//有退出

		}
		listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Value));
		listArray[0]->SetItemText(addItem, 4, Str(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Time));
		listArray[0]->SetItemText(addItem, 5, mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Unit);
	}

	if(flag==true)//有告警 全部变灰
	{
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		CHZ_flag=0;
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
	}
	else //if(flag==false)////无告警
	{
		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		CHZ_flag=0xff;
	}


	if(zuhedianqi_have_dongzuo == true)
	{
		AfxMessageBox("组合电器中不能含有动作选项，请检查文本!");
	}


	if(LineType == 0)//主线
	{
	//	GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);//判出线逻辑 使能
		((CButton *)GetDlgItem(IDC_RADIO4))->SetCheck(1);
		((CButton *)GetDlgItem(IDC_RADIO5))->SetCheck(0);


		GetDlgItem(IDC_STATIC_EDIT8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_EDIT81)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT8)->ShowWindow(true);
		SetDlgItemText(IDC_STATIC_EDIT9,"主线功率为正重合闸时间");


		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);

		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255  && CHZ_flag == 0xff )//重合使能并且没变灰
		{
			GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
		}
	}
	else//分支线
	{
		GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);//判出线逻辑 不使能
		((CButton *)GetDlgItem(IDC_RADIO5))->SetCheck(1);
		((CButton *)GetDlgItem(IDC_RADIO4))->SetCheck(0);

		GetDlgItem(IDC_STATIC_EDIT8)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_EDIT81)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT8)->ShowWindow(false);

		SetDlgItemText(IDC_STATIC_EDIT9,"     分支线重合闸时间");

		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255  && CHZ_flag == 0xff )//重合使能并且没变灰
		{
			GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
		}


	}

	/*

	if(flag1==true && flag==true)
	{
		AfxMessageBox("告警、动作不能同时出现");
	}
	*/


	/*******************************
	预览功能的实现
  *********************************/
	yulan();

}
void CSxJzsCfgView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

//	m_LineType.ResetContent();
//	m_LineType.AddString("主线");
//	m_LineType.AddString("分支线");

//	m_SwitchType.ResetContent();
//	m_SwitchType.AddString("断路器");
//	m_SwitchType.AddString("负荷开关");
//	m_SwitchType.AddString("组合电器(负荷开关+熔断器)");


//	SXJZSCfgStru SXJZSFile;
//	SXJZSCfgStru SXJZSFileTemp;

	//为了防止出现不一致的情况，确实也出现过了。
	memcpy(&(mPzkIni.SXJZSFileTemp),&(mPzkIni.SXJZSFile),sizeof(SXJZSCfgStru));

	m_ToolTipCtrl123.Create(this);
	m_ToolTipCtrl123.AddTool(GetDlgItem(IDC_CHECK1),_T("开关分位 保护动作!"));//添加
	m_ToolTipCtrl123.AddTool(GetDlgItem(IDC_COMBO3),_T("线路1-12为左侧，线路13-24为右侧"));//添加
//	m_ToolTipCtrl123.AddTool(GetDlgItem(IDC_RADIO7),_T("左右侧各12条线路"));//添加
	m_ToolTipCtrl123.AddTool(GetDlgItem(IDC_EDIT11),_T("线路名最多20个字符"));//添加
	m_ToolTipCtrl123.AddTool(GetDlgItem(IDC_STATIC_TISHI),_T("告警时，逻辑不能配置"));//添加

	m_ToolTipCtrl123.SetMaxTipWidth(300);
	m_ToolTipCtrl123.Activate(TRUE);
	m_ToolTipCtrl123.SetDelayTime(TTDT_INITIAL, 0);
	m_ToolTipCtrl123.SetDelayTime(TTDT_AUTOPOP, 90000);


	m_Version = mPzkIni.SXJZSFileTemp.Cfg.Version;//版本号
	m_LineNum = mPzkIni.SXJZSFileTemp.Cfg.ProtLineNum;//线路号
	m_PNumPerLine = mPzkIni.SXJZSFileTemp.Cfg.ProtNumPerLine;//每条线路多少保护
	m_FixActTime = mPzkIni.SXJZSFileTemp.Cfg.FixActTime;//保护动作时间
	m_LeftDTUNum = mPzkIni.SXJZSFileTemp.Cfg.LeftDTUNum;//左侧线路数


	//CString cs;
	//cs.Format("???? %d %d %d ",mPzkIni.SXJZSFile.Cfg.LeftDTUNum,mPzkIni.SXJZSFileTemp.Cfg.LeftDTUNum,m_LeftDTUNum);
	//AfxMessageBox(cs);


	if(mPzkIni.SXJZSFileTemp.Cfg.Prot_YXEnable == 255)//保护虚遥信使能
	{
		m_Check5 = true;
	}
	else
	{
		m_Check5 = false;
	}
	if(mPzkIni.SXJZSFileTemp.Cfg.Prot_MsgEnable == 255)//保护信息上报使能
	{
		m_Check6 = true;
	}
	else
	{
		m_Check6 = false;
	}
	if(mPzkIni.SXJZSFileTemp.Cfg.PLC_Enable == 255)//PLC投入
	{
		m_Check7 = true;
	}
	else
	{
		m_Check7 = false;
	}

	if(mPzkIni.SXJZSFileTemp.Cfg.MxType == 0)//单母线
	{
		((CButton *)GetDlgItem(IDC_RADIO6))->SetCheck(1);
		((CButton *)GetDlgItem(IDC_RADIO7))->SetCheck(0);

	//	GetDlgItem(IDC_STATIC_LeftDTUNum)->ShowWindow(SW_SHOW);
	//	GetDlgItem(IDC_EDIT13)->ShowWindow(true);
	//	GetDlgItem(IDC_EDIT13)->EnableWindow(TRUE);
	}
	else if(mPzkIni.SXJZSFileTemp.Cfg.MxType == 1)//双母线
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
			formatStr.Format("线路%d", i);
			m_LineNo.AddString(formatStr);
		}
		m_LineNo.SetCurSel(0);
	}


}

void CSxJzsCfgView::OnSave()
{
	// TODO: Add your control notification handler code here

	UpdateData(true);//界面到变量
	int i;
	int LineNo;
	LineNo = m_LineNo.GetCurSel();//得到当前线路号


	if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type == 2)//组合电器中含有动作，那么弹框
	{
		for(i=0;i<SXJZS_FACT_SELECT[mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type];i++)//原来是<= 最后一个不判断了，因此变成了<
		{
			int j=SXJZS_Select[mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type][i];
			if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==255)
			{
				//存在动作
				AfxMessageBox("组合电器中不能存在动作!");
				return ;
			}

		}
	}

	mPzkIni.SXJZSFile.Cfg.Version=mPzkIni.SXJZSFileTemp.Cfg.Version;//版本号 ==其实没变化
	mPzkIni.SXJZSFile.Cfg.ProtLineNum=mPzkIni.SXJZSFileTemp.Cfg.ProtLineNum;//线路号
	//m_PNumPerLine = mPzkIni.SXJZSFileTemp.Cfg.ProtNumPerLine;//每条线路多少保护 ==没变化
	mPzkIni.SXJZSFile.Cfg.Prot_YXEnable=mPzkIni.SXJZSFileTemp.Cfg.Prot_YXEnable;//保护虚遥信使能
	mPzkIni.SXJZSFile.Cfg.Prot_MsgEnable=mPzkIni.SXJZSFileTemp.Cfg.Prot_MsgEnable;//保护信息上报使能
	mPzkIni.SXJZSFile.Cfg.PLC_Enable =mPzkIni.SXJZSFileTemp.Cfg.PLC_Enable; //PLC投入
	mPzkIni.SXJZSFile.Cfg.FixActTime =mPzkIni.SXJZSFileTemp.Cfg.FixActTime; //保护动作固有时间
//	mPzkIni.SXJZSFile.Cfg.ZXCHZTime =mPzkIni.SXJZSFileTemp.Cfg.ZXCHZTime; //主线重合闸时间
//  mPzkIni.SXJZSFile.Cfg.FZXCHZTime =mPzkIni.SXJZSFileTemp.Cfg.FZXCHZTime; //分支线重合闸时间

	mPzkIni.SXJZSFile.Cfg.MxType =mPzkIni.SXJZSFileTemp.Cfg.MxType; //母线类型
	mPzkIni.SXJZSFile.Cfg.LeftDTUNum =mPzkIni.SXJZSFileTemp.Cfg.LeftDTUNum; //左侧线路数



//	for(LineNo=0;LineNo<SXJZS_FACT_LINE+1;LineNo++)//所有线路保存一次
	{
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.ZXCHZTime =mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.ZXCHZTime; //主线重合闸时间
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.FZXCHZTime=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.FZXCHZTime; //分支线重合闸时间
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Line_Name=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Name;
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Line_Type=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type;//线路类型
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.CxLogicFlag=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CxLogicFlag;//判出线逻辑
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.CHZ_Enable=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable;//重合闸使能
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.PHaveV_Flag=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PHaveV_Flag;//判电压
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.PSwitchStatus=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PSwitchStatus;//判开关位置
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Switch_Type=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type;//开关类型
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.SBO_Num=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.SBO_Num;//#线路SBO号
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Switch_Num=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Num;//线路开关号

		for(i=0;i<m_PNumPerLine;i++)//全部保存一遍 0-每条线路保护数
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
	int LineNo = m_LineNo.GetCurSel();//得到当前线路号

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


		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type == 2) //组合电器
		{

		//	AfxMessageBox("是组合电器");
			pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO5);
			pCombo = (CComboBox *)GetDlgItem(IDC_COMBO5);
			str = m_List1.GetItemText(nItem, nSubItem);
			m_Enable.ResetContent();
			m_Enable.AddString(_T("告警"));
			 m_Enable.AddString(_T("退出"));
		//	 UpdateData(FALSE);

			if(str.Compare("告警") == 0)
				pCombo->SetCurSel(0);

			else if(str.Compare("退出") == 0)
				pCombo->SetCurSel(1);

		}

		else if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type!= 2) //不是组合电器
		{
		//	AfxMessageBox("不是组合电器");
			CString css;
			css.Format("xianluhao   %d",LineNo);
		//	AfxMessageBox(css);
			pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO5);
			pCombo = (CComboBox *)GetDlgItem(IDC_COMBO5);
			str = m_List1.GetItemText(nItem, nSubItem);

			m_Enable.ResetContent();
			m_Enable.AddString(_T("动作"));
			m_Enable.AddString(_T("告警"));
			 m_Enable.AddString(_T("退出"));
		//	 UpdateData(FALSE);

			if(str.Compare("动作") == 0)
				pCombo->SetCurSel(0);
			if(str.Compare("告警") == 0)
				pCombo->SetCurSel(1);
			else if(str.Compare("退出") == 0)
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

void CSxJzsCfgView::OnChangeEdit1() //线路SBO号
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;//产生变化

}

void CSxJzsCfgView::OnKillfocusEdit1()
{
	// TODO: Add your control notification handler code here
	UpdateData(UPDATE_READ);
	if(m_SboNum > 23)
	{
		AfxMessageBox("线路SBO号不能超过"+Str(23));
		m_SboNum = 23;
		UpdateData(UPDATE_WRITE);
	}
	if(m_SboNum < 0)
	{
		AfxMessageBox("线路SBO号不能小于"+Str(0));
		m_SboNum = 0;
		UpdateData(UPDATE_WRITE);
	}

	UpdateData(true);//界面到程序
	int LineNo = m_LineNo.GetCurSel();//得到当前线路号
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.SBO_Num=m_SboNum;//#线路SBO号
}

/*
	下拉号改变，并不存储，因为触发此事件时，线路号已经改变，因此保存时会是错误的值，
	因此 改写在 edit 失去焦点时，保护 ok
*/
void CSxJzsCfgView::OnSelchangeCombo3() //线路号下拉改变
{
	// TODO: Add your control notification handler code here
//	OnCANCEl();


	UpdateData(true);//从界面到程序
	int LineNo;
	LineNo = m_LineNo.GetCurSel();//得到当前线路号

	int abc=LINE_AGO;
	CString str1;
	CString str2;
	str2.Format("%d",LINE_AGO+1);
	str1+="是否保存对 线路";
	str1+=str2;
	str1+=" 的修改?";


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



/*	//listarray 存储
	int i;
	int StartIndex,EndIndex;
	if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type==0)//断路器
	{
		StartIndex=0;
		EndIndex=4;

	}
	else if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type==1)//负荷开关
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
		if(listArray[0]->GetItemText(i,2) == "动作")
		{
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Enable = 255;

		}
		else if(listArray[0]->GetItemText(i,2) == "告警")
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Enable = 1;
		else if(listArray[0]->GetItemText(i,2) == "退出")
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Enable = 0;
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Value = myatof(listArray[0]->GetItemText(i,3));
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[StartIndex].Time = myatof(listArray[0]->GetItemText(i,4));

	}

  */
	//	AfxMessageBox("002");

	LoadSxjzsConfig(LineNo);

}

void CSxJzsCfgView::OnCheck5() //保护虚遥信使能
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

void CSxJzsCfgView::OnCheck6() //保护信息上报使能
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



void CSxJzsCfgView::OnCheck2() //重合使能
{
	// TODO: Add your control notification handler code here

	bEverEdited = true;
	UpdateData(true);
	int LineNo = m_LineNo.GetCurSel();//得到当前线路号
	int i=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type;
	if(m_Check2 == true && SwitchType==1)//选中重合闸并且开关类型为负荷开关
	{
		AfxMessageBox("开关类型为负荷开关时不能启动重合闸!");
		m_Check2=false;
	}
	if(m_Check2 == true)
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable=255;
		GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		if(i==0)//主线
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

void CSxJzsCfgView::OnCheck3()//判断是否有压
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	UpdateData(true);//界面到程序

	int LineNo = m_LineNo.GetCurSel();//得到当前线路号
	if(m_Check3 == true)
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PHaveV_Flag=255;
	}
	else
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PHaveV_Flag=0;
	}
}

void CSxJzsCfgView::OnCheck4() //判开关位置
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	UpdateData(true);//界面到程序
	int LineNo = m_LineNo.GetCurSel();//得到当前线路号
	if(m_Check4 == true)
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PSwitchStatus=255;
	}
	else
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PSwitchStatus=0;
	}
}

void CSxJzsCfgView::OnCheck1() //判出线逻辑
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	UpdateData(true);//界面到程序
	int LineNo = m_LineNo.GetCurSel();//得到当前线路号
	if(m_Check1 == true)
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CxLogicFlag=255;
	}
	else
	{
		mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CxLogicFlag=0;
	}
}

void CSxJzsCfgView::OnChangeEdit2() //线路开关号
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;//产生变化

}

void CSxJzsCfgView::OnKillfocusEdit2()
{
	// TODO: Add your control notification handler code here
	UpdateData(UPDATE_READ);
	if(m_SwitchNum > 128)
	{
		AfxMessageBox("线路开关号不能超过"+Str(128));
		m_SwitchNum = 128;
		UpdateData(UPDATE_WRITE);
	}
	if(m_SwitchNum < 0)
	{
		AfxMessageBox("线路开关号不能小于"+Str(0));
		m_SwitchNum = 0;
		UpdateData(UPDATE_WRITE);
	}

	UpdateData(true);//界面到程序
	int LineNo = m_LineNo.GetCurSel();//得到当前线路号
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Num=m_SwitchNum;//线路开关号
}

void CSxJzsCfgView::OnChangeEdit5()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
	UpdateData(true);//界面到程序


}

void CSxJzsCfgView::OnKillfocusEdit5()
{

	int CurLine = m_LineNo.GetCurSel();

	UpdateData(UPDATE_READ);
	if(m_LineNum > (SXJZS_FACT_LINE+1))//序号从0 开始的原因
	{
		AfxMessageBox("最大线路数不能超过"+Str(SXJZS_FACT_LINE+1)+Str("条!"));
		m_LineNum = SXJZS_FACT_LINE+1;
		UpdateData(UPDATE_WRITE);
	}

	if(m_LineNum <= 0)
	{
		AfxMessageBox("最小线路数不能小于"+Str(1)+Str("条!"));
		m_LineNum = 1;
		UpdateData(UPDATE_WRITE);
	}
	mPzkIni.SXJZSFileTemp.Cfg.ProtLineNum=m_LineNum ;//线路号
	m_LineNo.ResetContent();
	if(m_LineNum > 0)
	{
		CString formatStr;
		for(int i=1; i<=m_LineNum; i++)
		{
			formatStr.Format("线路%d", i);
			m_LineNo.AddString(formatStr);
		}
	}
	m_LineNo.SetCurSel(0);
//		AfxMessageBox("003");
	LoadSxjzsConfig(0);

}

void CSxJzsCfgView::OnKillfocusCombo5() //+4 错错错
{

//	int LineNo = m_LineNo.GetCurSel();//得到当前线路号
//	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type=crazy ;//开关类型

//	AfxMessageBox("kaokaokao");
	// TODO: Add your control notification handler code here
/*
	if(m_SwitchType.GetCurSel()==0)//断路器
	{
		if(m_Enable.GetCurSel() == 0)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "动作");
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem].Enable=255;
		}
		else if(m_Enable.GetCurSel() == 1)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "告警");
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem].Enable=1;
		}
		else if(m_Enable.GetCurSel() == 2)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "退出");
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem].Enable=0;
		}
	}
	else if(m_SwitchType.GetCurSel()==1)//负荷开关 +4+4
	{
		if(m_Enable.GetCurSel() == 0)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "动作");
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem+4].Enable=255;
		}
		else if(m_Enable.GetCurSel() == 1)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "告警");
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem+4].Enable=1;
		}
		else if(m_Enable.GetCurSel() == 2)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "退出");
			mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem+4].Enable=0;
		}
	}
	else if(m_SwitchType.GetCurSel()==2)//组合电气 熔断器
	{
		if(m_Enable.GetCurSel() == 0)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "动作");
		//	mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem+4].Enable=255;
		}
		else if(m_Enable.GetCurSel() == 1)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "告警");
		//	mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem+4].Enable=1;
		}
		else if(m_Enable.GetCurSel() == 2)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "退出");
		//	mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[nItem+4].Enable=0;
		}

	}
*/

/*
	bool flag=false;
	int LineNo = m_LineNo.GetCurSel();//得到当前线路号
	int index = SXJZS_Select[m_SwitchType.GetCurSel()][nItem];//保存数据数组的第某个开关的下标
//	CString cs;
//	cs.Format("%d",nItem);
//	AfxMessageBox(cs);
	int i;

	if(m_Enable.GetCurSel() == 0)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "动作");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=255;


		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255)//重合使能
		{

			GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		}

		//SXJZS_FACT_SELECT 数组存放 显示的个数
		//SXJZS_Select 显示某个开关里面的数字
		for(i=0;i<=SXJZS_FACT_SELECT[m_SwitchType.GetCurSel()];i++)
		{
			int j=SXJZS_Select[m_SwitchType.GetCurSel()][i];
			if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==1)
			{
				flag=true;//存在告警
				GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
				GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
				GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
			}

		}
	}
	else if(m_Enable.GetCurSel() == 1)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "告警");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=1;
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		for(i=0;i<=SXJZS_FACT_SELECT[m_SwitchType.GetCurSel()];i++)
		{
			int j=SXJZS_Select[m_SwitchType.GetCurSel()][i];
			if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==255)
			{
				flag=true;//存在动作
			}
		}

	}
	else if(m_Enable.GetCurSel() == 2)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "退出");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=0;

		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255)//重合使能
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
//	if(flag==true && (nItem!=-1))//-1 行
//	{
//		AfxMessageBox("告警、动作不能同时存在!");
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
	int LineNo = m_LineNo.GetCurSel();//得到当前线路号
	int index = SXJZS_Select[mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type][nItem];//保存数据数组的第某个开关的下标
//	CString cs;
//	cs.Format("%d",mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type);
//	AfxMessageBox(cs);
	int i;

if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type !=2)//不是负荷开关
{
	if(m_Enable.GetCurSel() == 0)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "动作");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=255;
	}
	else if(m_Enable.GetCurSel() == 1)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "告警");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=1;
	}
	else if(m_Enable.GetCurSel() == 2)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "退出");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=0;
	}
}
else if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type ==2)//是负荷开关
{

	if(m_Enable.GetCurSel() == 0)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "告警");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=1;
	}
	else if(m_Enable.GetCurSel() == 1)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "退出");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=0;
	}
}




	m_Enable.ShowWindow(SW_HIDE);
	bEverEdited = true;
	LoadSxjzsConfig(LineNo);
*/

}



void CSxJzsCfgView::OnSelchangeCombo2() //线路类型
{
	// TODO: Add your control notification handler code here
/*
	int LineNo = m_LineNo.GetCurSel();//得到当前线路号
	UpdateData(true);//界面到程序
	int i=m_LineType.GetCurSel();
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type=i;
	if(i==0)//主线
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
//	if(i==0)//主线
//		GetDlgItem(IDC_CHECK1)->ShowWindow(SW_SHOW);
//	else
//		GetDlgItem(IDC_CHECK1)->ShowWindow(SW_HIDE);


}

void CSxJzsCfgView::OnSelchangeCombo4() //开关类型
{
	// TODO: Add your control notification handler code here
	//int i=m_SwitchType.GetCurSel();
/*
	bEverEdited = true;
	int LineNo;
	UpdateData(true);//界面到程序 //开关类型改变
	LineNo = m_LineNo.GetCurSel();//得到当前线路号

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
		int i = AfxMessageBox("保存当前对保护项配置所做的修改吗？",MB_YESNOCANCEL);
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


void CSxJzsCfgView::OnKillfocusEdit3() //各种编辑失去焦点
{
	// TODO: Add your control notification handler code here
	CString str;
	m_Input.GetWindowText(str);
	listArray[0]->SetItemText(nItem, nSubItem, str);

	int LineNo = m_LineNo.GetCurSel();//得到当前线路号

/*
	if(m_SwitchType.GetCurSel()==0)//断路器
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
	else if(m_SwitchType.GetCurSel()==1)//负荷开关 +4+4
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
	else if(m_SwitchType.GetCurSel()==2)//组合电气 熔断器
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

	int index = SXJZS_Select[SwitchType][nItem];//保存数据数组的第某个开关的下标
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
		UpdateData(true);//界面到变量
/*
	mPzkIni.SXJZSFileTemp.Cfg.Version=mPzkIni.SXJZSFile.Cfg.Version;//版本号 ==其实没变化
	mPzkIni.SXJZSFileTemp.Cfg.ProtLineNum=mPzkIni.SXJZSFile.Cfg.ProtLineNum;//线路号
	//m_PNumPerLine = mPzkIni.SXJZSFileTemp.Cfg.ProtNumPerLine;//每条线路多少保护 ==没变化
	mPzkIni.SXJZSFileTemp.Cfg.Prot_YXEnable=mPzkIni.SXJZSFile.Cfg.Prot_YXEnable;//保护虚遥信使能
	mPzkIni.SXJZSFileTemp.Cfg.Prot_MsgEnable=mPzkIni.SXJZSFile.Cfg.Prot_MsgEnable;//保护信息上报使能
	mPzkIni.SXJZSFileTemp.Cfg.Byd_SOEEnable =mPzkIni.SXJZSFile.Cfg.Byd_SOEEnable; //越限告警SOE使能
	mPzkIni.SXJZSFileTemp.Cfg.Flt_YXEnable = mPzkIni.SXJZSFile.Cfg.Flt_YXEnable;// 故障检测分相上报使能
	mPzkIni.SXJZSFileTemp.Cfg.Flt_RepEnable = mPzkIni.SXJZSFile.Cfg.Flt_RepEnable;//故障报文上报使能
*/
	int i;
	int LineNo = m_LineNo.GetCurSel();//得到当前线路号
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.ZXCHZTime=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.ZXCHZTime;
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.FZXCHZTime=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.FZXCHZTime;
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Line_Type;//线路类型
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CxLogicFlag=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.CxLogicFlag;//判出线逻辑
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.CHZ_Enable;//重合闸使能
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PHaveV_Flag=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.PHaveV_Flag;//判电压
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PSwitchStatus=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.PSwitchStatus;//判开关位置
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Switch_Type;//开关类型
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.SBO_Num=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.SBO_Num;//#线路SBO号
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Num=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Switch_Num;//线路开关号
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Name=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Line_Name;
	for(i=0;i<m_PNumPerLine;i++)//全部保存一遍 0-每条线路保护数
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
	mPzkIni.SXJZSFileTemp.Cfg.FixActTime=m_FixActTime; //保护动作固有时间
}

void CSxJzsCfgView::OnKillfocusList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

/*
	int LineNo = m_LineNo.GetCurSel();//得到当前线路号

	bool flag=false;
	bool flag1=false;
	int i;
	for(i=0;i<=SXJZS_FACT_SELECT[m_SwitchType.GetCurSel()];i++)
	{
		int j=SXJZS_Select[m_SwitchType.GetCurSel()][i];
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==1)
		{
			flag=true;//存在告警
		}
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==255)
		{
			flag1=true;
		}
	}
	if(flag==true && flag1==true)
	{
		AfxMessageBox("告警、动作不能同时存在");
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
	int LineNo = m_LineNo.GetCurSel();//得到当前线路号

	if(m_ZXCHZTime > 60)
	{
		AfxMessageBox("主线功率为负重合闸时间不能超过"+Str(60)+Str("s"));
		m_ZXCHZTime = 60;

		UpdateData(UPDATE_WRITE);
	}
	if(m_ZXCHZTime < 0)
	{
		AfxMessageBox("主线功率为负重合闸时间不能小于"+Str(0)+Str("s"));
		m_ZXCHZTime = 0;
		UpdateData(UPDATE_WRITE);
	}

	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.ZXCHZTime=m_ZXCHZTime;
}

void CSxJzsCfgView::OnKillfocusEdit9()
{
	// TODO: Add your control notification handler code here
	UpdateData(UPDATE_READ);
	 int LineNo = m_LineNo.GetCurSel();//得到当前线路号
//	int min = mPzkIni.SXJZSFileTemp.Cfg.ZXCHZTime+3;


	if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type ==0 )//为主线时
	{
		if(m_FZXCHZTime > 60)//不能超过 60;
		{
			AfxMessageBox("主线功率为正重合闸时间不能超过"+Str(60)+Str("s"));
			m_FZXCHZTime = 60;
			UpdateData(UPDATE_WRITE);
		}
		if(m_FZXCHZTime < 0)
		{
			AfxMessageBox("主线功率为正重合闸时间不能小于"+Str(0)+Str("s"));
			m_FZXCHZTime = 0;
			UpdateData(UPDATE_WRITE);
		}
	}
	else
	{
		if(m_FZXCHZTime > 60)//不能超过 60;
		{
			AfxMessageBox("分支线重合闸时间不能超过"+Str(60)+Str("s"));
			m_FZXCHZTime = 60;
			UpdateData(UPDATE_WRITE);
		}
		if(m_FZXCHZTime < 0)
		{
			AfxMessageBox("分支线重合闸时间不能小于"+Str(0)+Str("s"));
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
	int LineNo = m_LineNo.GetCurSel();//得到当前线路号
	int index = SXJZS_Select[SwitchType][nItem];//保存数据数组的第某个开关的下标
	CString cs;
	cs.Format("%d",nItem);
//	AfxMessageBox(cs);
	int i;

	UpdateData(false);

//	CString cs;
//	cs.Format("aaaaaaaaaaaaa%d",m_Enable.GetCurSel());
//	AfxMessageBox(cs);


if((SwitchType == 0) || (SwitchType ==1) ) //不是 组合电器
{
	if(m_Enable.GetCurSel() == 0)
	{
		//AfxMessageBox("...");
		listArray[0]->SetItemText(nItem, nSubItem, "动作");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=255;


		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		CHZ_flag=0xff;
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255)//重合使能
		{

			GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
		}

		//SXJZS_FACT_SELECT 数组存放 显示的个数
		//SXJZS_Select 显示某个开关里面的数字
		CString cs;
		cs.Format("switchtype = %d",SwitchType);
	//	AfxMessageBox(cs);

			CString css;
	//	css.Format("SXJZS_FACT_SELECT[SwitchType] = %d",SXJZS_FACT_SELECT[SwitchType]);
	//	AfxMessageBox(css);


	//这是最后一个，如果前边几个设置为 告警的话，最后一个设置为动作,那么就会检索前边几个，正好
	//	有告警，所以就弹出窗口了。解决办法是，如果是第4个，那么就不判了，爱咋咋地
		if((SwitchType ==0  && nItem != 4) || (SwitchType ==1 && nItem != 1) ||(SwitchType ==2 && nItem !=3 ))//如果是4的话，就直接忽略掉了，不用检索了

		{
			for(i=0;i<SXJZS_FACT_SELECT[SwitchType];i++)//原来是<= 最后一个不判断了，因此变成了<
			{
				int j=SXJZS_Select[SwitchType][i];
				if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==1)
				{
					flag=true;//存在告警
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
		listArray[0]->SetItemText(nItem, nSubItem, "告警");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=1;

		if((SwitchType ==0  && nItem != 4) || (SwitchType ==1 && nItem != 1) ||(SwitchType ==2 && nItem !=3 ))//不等于4，再变灰
		{
			GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
			CHZ_flag=0;
			GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
			GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		}
			//这是最后一个，如果前边几个设置为 告警的话，最后一个设置为动作,那么就会检索前边几个，正好
	//	有告警，所以就弹出窗口了。解决办法是，如果是第4个，那么就不判了，爱咋咋地
		if((SwitchType ==0  && nItem != 4) || (SwitchType ==1 && nItem != 1) ||(SwitchType ==2 && nItem !=3 ))//如果是4的话，就直接忽略掉了，不用检索了
		{
			for(i=0;i<SXJZS_FACT_SELECT[SwitchType];i++)//原来是<= 最后一个不判断了，因此变成了<
			{
				int j=SXJZS_Select[SwitchType][i];
				if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==255)
				{
					flag=true;//存在动作
				}
			}
		}
	}

	else if(m_Enable.GetCurSel() == 2)
	{
	//	AfxMessageBox("???");
		listArray[0]->SetItemText(nItem, nSubItem, "退出");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=0;

		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		CHZ_flag=0xff;
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255)//重合使能
		{
			GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		}

//		for(i=0;i<SXJZS_FACT_SELECT[SwitchType];i++)//原来是<= 最后一个不判断了，因此变成了<
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
	if(flag==true )//-1 行
	{
		AfxMessageBox("告警、动作不能同时存在!");
	}

   m_List1.SetFocus();
   m_Enable.ShowWindow(SW_HIDE);//这句话改变了开关类型\/？

   bEverEdited = true;
}


else
//if(SwitchType == 2) // 组合电器
{

	 if(m_Enable.GetCurSel() == 0)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "告警");
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
		listArray[0]->SetItemText(nItem, nSubItem, "退出");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=0;

		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		CHZ_flag=0xff;
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255)//重合使能
		{
			GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		}

		for(i=0;i<SXJZS_FACT_SELECT[SwitchType]-1;i++)//原来是<= 最后一个不判断了，因此变成了<
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
	int LineNo = m_LineNo.GetCurSel();//得到当前线路号
	int index = SXJZS_Select[mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type][nItem];//保存数据数组的第某个开关的下标
//	CString cs;
//	cs.Format("%d",nItem);
//	AfxMessageBox(cs);
	int i;

	if(m_Enable.GetCurSel() == 0)
	{
		listArray[0]->SetItemText(nItem, nSubItem, "告警");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=1;


		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable == 255)//重合使能
		{

			GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
			GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		}

		//SXJZS_FACT_SELECT 数组存放 显示的个数
		//SXJZS_Select 显示某个开关里面的数字
		/*
		for(i=0;i<=SXJZS_FACT_SELECT[m_SwitchType.GetCurSel()];i++)
		{
			int j=SXJZS_Select[m_SwitchType.GetCurSel()][i];
			if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==1)
			{
				flag=true;//存在告警
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
		listArray[0]->SetItemText(nItem, nSubItem, "告警");
		mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[index].Enable=1;
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		for(i=0;i<=SXJZS_FACT_SELECT[mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type];i++)
		{
			int j=SXJZS_Select[mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type][i];
			if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==255)
			{
				flag=true;//存在动作
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
//	UpdateData(true);//界面到程序 //开关类型改变
	LineNo = m_LineNo.GetCurSel();//得到当前线路号

	CString cs;
	cs.Format("line11 == %d",LineNo);
//	AfxMessageBox(cs);
//	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type=0;
//		AfxMessageBox("断路器");
	LoadSxjzsConfig(LineNo);
//	LoadSxjzsConfig(LineNo);
}

void CSxJzsCfgView::OnRadio2()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	int LineNo;
//	UpdateData(true);//界面到程序 //开关类型改变
	LineNo = m_LineNo.GetCurSel();//得到当前线路号
	CString cs;
	cs.Format("line22 == %d",LineNo);
//	AfxMessageBox(cs);
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type=1;
//		AfxMessageBox("负荷开关");
	LoadSxjzsConfig(LineNo);
//	LoadSxjzsConfig(LineNo);
}

void CSxJzsCfgView::OnRadio3()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	int LineNo;
//	UpdateData(true);//界面到程序 //开关类型改变
	LineNo = m_LineNo.GetCurSel();//得到当前线路号

	CString cs;
	cs.Format("line33 == %d",LineNo);
//	AfxMessageBox(cs);

	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type=2;
//		AfxMessageBox("组合电器");
	LoadSxjzsConfig(LineNo);
//	LoadSxjzsConfig(LineNo);
}





/**********************************
预览功能的实现
*************************************/
void CSxJzsCfgView::yulan()
{


	int LineIndex;//线路序号
	int k;
	int index111;
	CString str;
	CString str1;
	CString str2;

	for(LineIndex=0;LineIndex<mPzkIni.SXJZSFile.Cfg.ProtLineNum ;LineIndex++)//N条线路
	{


		//str.Format("线路%d", LineIndex+1);

		str+="线路";
		str+=Str(LineIndex+1);
		str+=" (";
		str+=mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Line_Name;
		str+=" )";
	//	str+="线路类型为:";
		str+="    ";
		if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Line_Type ==0)//主线
		{
			str+="主线";
			str+="\r\n";

			if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.CHZ_Enable==255)
				str+="重合闸     投入";
			if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.CHZ_Enable==0)
				str+="重合闸     未投入";


			str+="\r\n";
			str+="类    型     ";
			if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Type ==0)//断路器
			{
				str+="断路器";
			}
			else if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Type ==1)//负荷开关
			{
				str+="负荷开关";
			}
			else if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Type ==2)//组合电器(负荷开关+熔断器)
			{
				str+="组合电器(负荷开关+熔断器)";
			}

			str+="\r\n";
			str+="遥控号    ";
			str+=Str(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.SBO_Num);

			str+="\r\n";
			str+="遥信号    ";
			str+=Str(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Num);

			str+="\r\n";
			str+="功率为负重合闸时间     ";
			str+=Str(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.ZXCHZTime);
			str+="s";
			str+="\r\n";

			str+="功率为正重合闸时间     ";
			str+=Str(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.FZXCHZTime);
			str+="s";
			str+="\r\n";

		}
		else if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Line_Type ==1)//分支线
		{
			str+="分支线";
			str+="\r\n";

			if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.CHZ_Enable==255)
				str+="重合闸     投入";
			if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.CHZ_Enable==0)
				str+="重合闸     未投入";


			str+="\r\n";
			str+="类    型     ";
			if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Type ==0)//断路器
			{
				str+="断路器";
			}
			else if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Type ==1)//负荷开关
			{
				str+="负荷开关";
			}
			else if(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Type ==2)//组合电器(负荷开关+熔断器)
			{
				str+="组合电器(负荷开关+熔断器)";
			}

			str+="\r\n";
			str+="遥控号    ";
			str+=Str(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.SBO_Num);

			str+="\r\n";
			str+="遥信号    ";
			str+=Str(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Num);

			str+="\r\n";
			str+="分支线重合闸时间     ";
			str+=Str(mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.FZXCHZTime);
			str+="s";


			str+="\r\n";
		}

		//str+="保护类型为:";
		for(k=0; k<=SXJZS_FACT_SELECT[mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Type]; k++)//每种开关类型有几个数据
		{
			index111=SXJZS_Select[mPzkIni.SXJZSFile.Line[LineIndex].LineCfg.Switch_Type][k];//switchtype：开关类型 i:第几个数据

			str+=mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Name;
			str+="  ";


			if(mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Name.Compare("过流后失压") == 0)
			str+="        ";

			if(mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Name.Compare("后加速保护") == 0)
			str+="          ";
			if(mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Name.Compare("失压保护") == 0)
			str+="              ";
			if(mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Name.Compare("零序过流保护") == 0)
			str+="      ";
			if(mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Name.Compare("过流后失压") == 0)
			str+="  ";

			if(mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Enable == 255)
			{
				str+="动作";
			}
			else if(mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Enable == 1)
			{
				str+="告警";
			}
			else if(mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Enable == 0)
			{
				str+="退出";
			}

			str+="  ";
			str+="定值:";
			str1.Format("%5.2f",mPzkIni.SXJZSFile.Line[LineIndex].SXJZSItem[index111].Value);
		    //Str+=Str(mPzkIni.SXJZSFileTemp.Line[LineIndex].SXJZSItem[index111].Value);
			str+=str1;

			str+="  ";
			str+="时间:";
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

void CSxJzsCfgView::OnRadio4() //主线
{
	// TODO: Add your control notification handler code here
		UpdateData(true);//界面到程序
	int LineNo = m_LineNo.GetCurSel();//得到当前线路号


//	int i=m_LineType.GetCurSel();
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type=0;
//	if(i==0)//主线
//	{

		GetDlgItem(IDC_STATIC_EDIT8)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_EDIT81)->ShowWindow(SW_SHOW);
	//	GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT8)->ShowWindow(true);

		SetDlgItemText(IDC_STATIC_EDIT9,"主线功率为正重合闸时间");

		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable==255 && CHZ_flag == 0xff)
		{
			GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);//出线逻辑使能
			GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
		}
//	}
//	else
//		GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);



	//全部互斥，让开关类型着色
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

void CSxJzsCfgView::OnRadio5() //分支线
{
	// TODO: Add your control notification handler code here
	UpdateData(true);//界面到程序
	int LineNo = m_LineNo.GetCurSel();//得到当前线路号

	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type=1;
	GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);//出线逻辑变灰
	bEverEdited = true;

	GetDlgItem(IDC_STATIC_EDIT8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_EDIT81)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_EDIT8)->ShowWindow(false);

	SetDlgItemText(IDC_STATIC_EDIT9,"     分支线重合闸时间");



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
		int LineNo = m_LineNo.GetCurSel();//得到当前线路号
		bEverEdited = true;
	UpdateData(TRUE);
	int nLen = strlen(m_strEdit);
	if(nLen>20)//20个字符，10个汉字
	{
		MessageBox("数据输入过长!","长度有误",MB_OK);
		m_strEdit=m_strEdit.Left(20);//截取20个字符
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

//	INDEX_TEMP = m_LineNo.GetCurSel();//得到当前线路号


}

void CSxJzsCfgView::OnSetfocusCombo3()
{
	// TODO: Add your control notification handler code here

	LINE_AGO = m_LineNo.GetCurSel();//得到前线路号

//	CString cs;
//	cs.Format("hhhhhhhhh = %d",LINE_AGO);
//	AfxMessageBox(cs);

//	m_LineNo.GetCurSel();//得到当前线路号
}


void CSxJzsCfgView::OnSaveAgo(int LineNo) //保存以前的
{
	// TODO: Add your control notification handler code here

//	UpdateData(true);//界面到变量
	int i;
//	int LineNo;
//	LineNo = m_LineNo.GetCurSel();//得到当前线路号
//	for(LineNo=0;LineNo<SXJZS_FACT_LINE+1;LineNo++)//所有线路保存一次
	{

	//	CString cs;
	//	cs.Format("vvvvvv = %d",LineNo);
	//	AfxMessageBox(cs);
	//	LineNo= LineNo-1;
		CString cs;
		cs.Format("组合电器中不能存在动作,请检查线路%d的配置!",LineNo+1);

		if(mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type == 2)//组合电器中含有动作，那么弹框
		{
			for(i=0;i<SXJZS_FACT_SELECT[mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type];i++)//原来是<= 最后一个不判断了，因此变成了<
			{
				int j=SXJZS_Select[mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type][i];
				if(mPzkIni.SXJZSFileTemp.Line[LineNo].SXJZSItem[j].Enable==255)
				{
					//存在动作
					AfxMessageBox(cs);
					return ;
				}

			}
		}

		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.ZXCHZTime=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.ZXCHZTime;
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.FZXCHZTime=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.FZXCHZTime;


		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Line_Name=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Name;
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Line_Type=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type;//线路类型
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.CxLogicFlag=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CxLogicFlag;//判出线逻辑
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.CHZ_Enable=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable;//重合闸使能
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.PHaveV_Flag=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PHaveV_Flag;//判电压
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.PSwitchStatus=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PSwitchStatus;//判开关位置
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Switch_Type=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type;//开关类型
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.SBO_Num=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.SBO_Num;//#线路SBO号
		mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Switch_Num=mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Num;//线路开关号

		for(i=0;i<m_PNumPerLine;i++)//全部保存一遍 0-每条线路保护数
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
	//	UpdateData(true);//界面到变量
/*
	mPzkIni.SXJZSFileTemp.Cfg.Version=mPzkIni.SXJZSFile.Cfg.Version;//版本号 ==其实没变化
	mPzkIni.SXJZSFileTemp.Cfg.ProtLineNum=mPzkIni.SXJZSFile.Cfg.ProtLineNum;//线路号
	//m_PNumPerLine = mPzkIni.SXJZSFileTemp.Cfg.ProtNumPerLine;//每条线路多少保护 ==没变化
	mPzkIni.SXJZSFileTemp.Cfg.Prot_YXEnable=mPzkIni.SXJZSFile.Cfg.Prot_YXEnable;//保护虚遥信使能
	mPzkIni.SXJZSFileTemp.Cfg.Prot_MsgEnable=mPzkIni.SXJZSFile.Cfg.Prot_MsgEnable;//保护信息上报使能
	mPzkIni.SXJZSFileTemp.Cfg.Byd_SOEEnable =mPzkIni.SXJZSFile.Cfg.Byd_SOEEnable; //越限告警SOE使能
	mPzkIni.SXJZSFileTemp.Cfg.Flt_YXEnable = mPzkIni.SXJZSFile.Cfg.Flt_YXEnable;// 故障检测分相上报使能
	mPzkIni.SXJZSFileTemp.Cfg.Flt_RepEnable = mPzkIni.SXJZSFile.Cfg.Flt_RepEnable;//故障报文上报使能
*/

	int i;
//	LineNo= LineNo-1;//>???为什么减1，奇怪？？

	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.ZXCHZTime=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.ZXCHZTime;//线路类型
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.FZXCHZTime=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.FZXCHZTime;//线路类型


	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Type=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Line_Type;//线路类型
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CxLogicFlag=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.CxLogicFlag;//判出线逻辑
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.CHZ_Enable=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.CHZ_Enable;//重合闸使能
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PHaveV_Flag=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.PHaveV_Flag;//判电压
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.PSwitchStatus=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.PSwitchStatus;//判开关位置
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Type=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Switch_Type;//开关类型
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.SBO_Num=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.SBO_Num;//#线路SBO号
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Switch_Num=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Switch_Num;//线路开关号
	mPzkIni.SXJZSFileTemp.Line[LineNo].LineCfg.Line_Name=mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Line_Name;

//	CString cs;
//	cs.Format("aaaaaaaaaaaaaaa====%d",LineNo);
//	AfxMessageBox(cs);

//	AfxMessageBox(mPzkIni.SXJZSFile.Line[LineNo].LineCfg.Line_Name);

	for(i=0;i<m_PNumPerLine;i++)//全部保存一遍 0-每条线路保护数
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

void CSxJzsCfgView::OnKillfocusEdit13() //左侧线路数
{
	// TODO: Add your control notification handler code here

	UpdateData(UPDATE_READ);
	if(m_LeftDTUNum > 24)
	{
		AfxMessageBox("左侧线路数不能超过"+Str(24));
		m_LeftDTUNum = 24;
		UpdateData(UPDATE_WRITE);
	}
	if(m_LeftDTUNum < 0)
	{
		AfxMessageBox("左侧线路数不能小于"+Str(0));
		m_LeftDTUNum = 0;
		UpdateData(UPDATE_WRITE);
	}

	UpdateData(true);//界面到程序
	mPzkIni.SXJZSFileTemp.Cfg.LeftDTUNum =m_LeftDTUNum; //左侧线路数
}

void CSxJzsCfgView::OnRadio6() //单母线
{
	// TODO: Add your control notification handler code here

	bEverEdited = true;
	mPzkIni.SXJZSFileTemp.Cfg.MxType = 0;

//	GetDlgItem(IDC_STATIC_LeftDTUNum)->ShowWindow(SW_SHOW);
//	GetDlgItem(IDC_EDIT13)->ShowWindow(true);
//	GetDlgItem(IDC_EDIT13)->EnableWindow(TRUE);
}

void CSxJzsCfgView::OnRadio7() //双母线
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

	int LineNo = m_LineNo.GetCurSel();//得到当前线路号

	UpdateData(TRUE);
	int nLen = strlen(m_strEdit);

	 if(nLen == 0 )//==0
	{
		AfxMessageBox("线路名不能为空!");
	}
}
