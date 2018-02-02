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

CToolTipCtrl kmg_ToolTipCtr;//tooltips提示

extern int KMG_Select[KMG_SWITCH_KIND][KMG_SELECT];//看门狗 读取prot_select里面的数据到数组
extern int KMG_FACT_SELECT[KMG_SELECT];//实际的值大小

/////////////////////////////////////////////////////////////////////////////
// CKMGCfgView dialog

IMPLEMENT_DYNCREATE(CKMGCfgView, CFormView)//通过DECLARE_DYNCREATE宏来使用IMPLEMENT_DYNCREATE宏，以允许CObject派生类对象在运行时自动建立。class,baseclass

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


void CKMGCfgView::DoDataExchange(CDataExchange* pDX)//对话框数据提取、
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
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)//消息ID和映射message的函数
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)//它的作用是绑定一个自定义的消息和该消息的响应函数。
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
#endif //_DEBUG  AssertValid函数是用来判断表达式的合法性或正确性,如果不正确或不合法则终止程序并返回相应的提示信息 如AssertValid(t==0);//用来判断t是否等于0,如果t!=0则终止程序
//Dump函数一般用来显示debug信息的，其函数中的内容一般在debug时，在debug窗口中才能看到



void CKMGCfgView::LoadKMGConfig()//工具显示数据：开关类型、数据表
{
	int addItem;
	listArray[0]->DeleteAllItems();
	int type = m_KMGType.GetCurSel();//故障类型组合框内容项 0为保护定值设定
	if(type ==0)
	{
		SwitchType=mPzkIni.KMGFileTemp.Line[type].LineCfg.Switch_Type;//开关类型
		if(SwitchType==0)//断路器选中
		{
			((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);//根据switchtype，显示相应的radio状态
		}
		else if(SwitchType==1)//负荷开关选中
		{
			((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(1);
		}
		else if(SwitchType==2)//组合电器选中
		{
			((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(1);
		}

		m_SboNum=mPzkIni.KMGFileTemp.Line[type].LineCfg.SBO_Num;//#线路SBO号
		m_SwitchNum=mPzkIni.KMGFileTemp.Line[type].LineCfg.Switch_Num;//#线路开关号
		int index;
		for(int i=0; i<=KMG_FACT_SELECT[SwitchType]; i++)//每种开关类型有几个数据 ，KMG_FACT_SELECT哪里来，0-9 1-3 2-3
		{
			index=KMG_Select[SwitchType][i];//switchtype：开关类型 i:第几个数据
			addItem = listArray[0]->InsertItem(i, Str(i), 0);
			listArray[0]->SetItemData(addItem, mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Type);//?
			listArray[0]->SetItemText(addItem, 1, mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Name);
			if(mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Enable == 255)
			{
				listArray[0]->SetItemText(addItem, 2, "动作");
			}
			else if(mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Enable == 1)
			{
				listArray[0]->SetItemText(addItem, 2, "告警");
			}
			else if(mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Enable == 0)
			{
				listArray[0]->SetItemText(addItem, 2, "退出");
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
		if(mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Enable == 255)//KMGItem[0]?，只有一行数据
		{
			listArray[0]->SetItemText(addItem, 1, "投入");
		}
		else if(mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Enable == 0)
		{
			listArray[0]->SetItemText(addItem, 1, "退出");
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
			listArray[0]->SetItemText(addItem, 1, "投入");
		}
		else if(mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Enable == 0)
		{
			listArray[0]->SetItemText(addItem, 1, "退出");
		}
		listArray[0]->SetItemText(addItem, 2, Str(mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Value1));
	//	listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Value2));
		listArray[0]->SetItemText(addItem, 3, Str(mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Time));
		listArray[0]->SetItemText(addItem, 4, mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Unit);

	}



  UpdateData(UPDATE_WRITE);//UpdateData(FALSE);把m_txt的数据刷新到画面控件上去。UpdateData(TRUE)是将控件的状态传给其关联的变量，

}

void CKMGCfgView::InitListCtrl()
{
	int i=0;
	CSize sz;
	sz.cx = sz.cy = 30;
//	listArray[0] = &m_List1;
	int type = m_KMGType.GetCurSel();

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
		listArray[0]->InsertColumn(i++, "序号", LVCFMT_LEFT, 40, -1);//i++为列号，内容，居中，宽度
		listArray[0]->InsertColumn(i++, "名称", LVCFMT_LEFT, 160, -1);
		listArray[0]->InsertColumn(i++, "动作/告警", LVCFMT_CENTER, 75, -1);
		listArray[0]->InsertColumn(i++, "定值", LVCFMT_CENTER, 75, -1);
		listArray[0]->InsertColumn(i++, "时间", LVCFMT_CENTER, 80, -1);
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
	else if(type ==6 || type ==7)
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

	CRect rect;//?
	listArray[0]->GetWindowRect(&rect);//该函数返回指定窗口的边框矩形的尺寸。该尺寸以相对于屏幕坐标左上角的屏幕坐标给出。

	rect.top -= 80;
	rect.bottom -= 80;

	LoadKMGConfig();

}

void CKMGCfgView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	//为了防止出现不一致的情况，确实也出现过了。
	memcpy(&(mPzkIni.KMGFileTemp),&(mPzkIni.KMGFile),sizeof(KMGCfgStru));

	//初始为0, 颜色变灰
	GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE);

	GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);//复选框允许或禁止输入
	GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK6)->EnableWindow(TRUE);


	kmg_ToolTipCtr.Create(this);//给电压接线方式添加提示
	kmg_ToolTipCtr.AddTool(GetDlgItem(IDC_RADIO4),_T("一侧线电压Uab接终端的U1a端子,另一侧线电压Ucb接终端的U1c端子"));//添加
	kmg_ToolTipCtr.AddTool(GetDlgItem(IDC_RADIO5),_T("一侧三相电压接终端的U1a/U1b/U1c,另一侧三相电压接终端的U2a/U2b/U2c"));//添加
	kmg_ToolTipCtr.AddTool(GetDlgItem(IDC_RADIO6),_T("三相电压接终端的U1a/U1b/U1c"));//添加
	kmg_ToolTipCtr.SetMaxTipWidth(300);
	kmg_ToolTipCtr.Activate(TRUE);
	kmg_ToolTipCtr.SetDelayTime(TTDT_INITIAL, 0);
	kmg_ToolTipCtr.SetDelayTime(TTDT_AUTOPOP, 90000);


	m_KMGType.ResetContent();//Removes all items from a list box.
	m_KMGType.AddString("保护定值设定");
	m_KMGType.AddString("电流回路-越限告警定值设定");//故障类型：组合框列表框combo1
	m_KMGType.AddString("电压回路-越限告警定值设定");
	m_KMGType.AddString("零序电流回路-越限告警定值设定");
	m_KMGType.AddString("零序电压回路-越限告警定值设定");
	m_KMGType.AddString("过负荷告警定值设定");
	m_KMGType.AddString("相间短路故障配置");
	m_KMGType.AddString("单相接地故障配置");
	m_KMGType.SetCurSel(0);//本函数在组合框的列表框中选择一个字符串。必要时列表框会滚动，以使该字符串在列表的可视区内 （列表是可见的时 ）。编辑控件中 的文本将相应地变为选中的字符串。此前在列表框中的选择将不复存在。当前选项为0

	m_Enable.ResetContent();//保护定值设定中 动作告警投退组合框列表框combo2
	m_Enable.AddString("动作");
	m_Enable.AddString("告警");
	m_Enable.AddString("退出");
	m_Enable.SetCurSel(0);

	GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);//该函数允许/禁止指定的窗口或控件接受鼠标和键盘的输入，若该参数为TRUE，则窗口被允许
	GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);//RADIO3呢？
	GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);//?
	GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);

	m_Version = mPzkIni.KMGFileTemp.Cfg.Version;//版本号
//	m_PNumPerLine = mPzkIni.KMGFileTemp.Cfg.ProtNumPerLine;//每条线路多少保护

	if(mPzkIni.KMGFileTemp.Cfg.Prot_YXEnable == 255)//保护虚遥信使能
	{
		m_Check1 = true;//IDC_CHECK1的值
	}
	else
	{
		m_Check1 = false;
	}
	if(mPzkIni.KMGFileTemp.Cfg.Prot_MsgEnable == 255)//保护信息上报使能
	{
		m_Check2 = true;
	}
	else
	{
		m_Check2 = false;
	}
	if(mPzkIni.KMGFileTemp.Cfg.Byd_SOEEnable == 255)//越限告警SOE使能
	{
		m_Check3 = true;
	}
	else
	{
		m_Check3 = false;
	}
	if(mPzkIni.KMGFileTemp.Cfg.Flt_YXEnable == 255)//故障检测分相上报使能
	{
		m_Check4 = true;
	}
	else
	{
		m_Check4 = false;
	}
	if(mPzkIni.KMGFileTemp.Cfg.Flt_RepEnable == 255)//故障报文上报使能
	{
		m_Check5 = true;
	}
	else
	{
		m_Check5= false;
	}
	if(mPzkIni.KMGFileTemp.Cfg.Flt_RcwEnable == 255)//故障录波使能
	{
		m_Check6 = true;
	}
	else
	{
		m_Check6= false;
	}

	//接线方式
	if(CMode==0)
		((CButton *)GetDlgItem(IDC_RADIO4))->SetCheck(1);
	else if(CMode ==1)
		((CButton *)GetDlgItem(IDC_RADIO5))->SetCheck(1);
	else if(CMode ==2)
		((CButton *)GetDlgItem(IDC_RADIO6))->SetCheck(1);

	UpdateData(UPDATE_WRITE);//值更新到控件
	UpdateData(UPDATE_READ);//控件的值更新到变量
	InitListCtrl();//调用初始化列表框函数

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
		int i = AfxMessageBox("保存当前对保护项配置所做的修改吗？",MB_YESNOCANCEL);
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

void CKMGCfgView::OnCheck1() //保护虚遥信使能
{
	bEverEdited = true;
	UpdateData(true);//界面到程序
	if(m_Check1 == true)
	{
		mPzkIni.KMGFileTemp.Cfg.Prot_YXEnable=255;
	}
	else
	{
		mPzkIni.KMGFileTemp.Cfg.Prot_YXEnable=0;
	}

}

void CKMGCfgView::OnCheck2() //保护信息上报使能
{
	bEverEdited = true;
	UpdateData(true);//界面到程序
	if(m_Check2 == true)
	{
		mPzkIni.KMGFileTemp.Cfg.Prot_MsgEnable=255;
	}
	else
	{
		mPzkIni.KMGFileTemp.Cfg.Prot_MsgEnable=0;
	}
}

void CKMGCfgView::OnCheck3() //越限告警SOE使能
{
	bEverEdited = true;
	UpdateData(true);//界面到程序
	if(m_Check3 == true)
	{
		mPzkIni.KMGFileTemp.Cfg.Byd_SOEEnable=255;
	}
	else
	{
		mPzkIni.KMGFileTemp.Cfg.Byd_SOEEnable=0;
	}

}

void CKMGCfgView::OnCheck4() //故障检测分相上报使能
{
	bEverEdited = true;
	UpdateData(true);//界面到程序
	if(m_Check4 == true)
	{
		mPzkIni.KMGFileTemp.Cfg.Flt_YXEnable=255;
	}
	else
	{
		mPzkIni.KMGFileTemp.Cfg.Flt_YXEnable=0;
	}
}

void CKMGCfgView::OnCheck5() //故障报文上报使能
{
	bEverEdited = true;
	UpdateData(true);//界面到程序
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
	int type = m_KMGType.GetCurSel();//故障类型组合框内容项 0为保护定值设定
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
			if(str.Compare("投入") == 0)
				pCombo->SetCurSel(0);
			else if(str.Compare("退出") == 0)
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
			if(str.Compare("投入") == 0)
				pCombo->SetCurSel(0);
			else if(str.Compare("退出") == 0)
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

void CKMGCfgView::OnSelchangeCombo1() //OnInitialUpdate中是初始状态，此处为更改combo1
{
	// TODO: Add your control notification handler code here

	if(m_KMGType.GetCurSel()==0)//radio 开关类型激活与禁止
	{
		m_Enable.ResetContent();
		m_Enable.AddString("动作");
		m_Enable.AddString("告警");
		m_Enable.AddString("退出");
		GetDlgItem(IDC_RADIO1)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(TRUE);
		GetDlgItem(IDC_RADIO3)->EnableWindow(TRUE);
	}
	else
	{
		m_Enable.ResetContent();
		m_Enable.AddString("投入");
		m_Enable.AddString("退出");
		GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE);
	}

	int type = m_KMGType.GetCurSel();
	if(type == 0)// 保护 1 2 6  复选框激活与禁止
	{
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE);

		GetDlgItem(IDC_CHECK1)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(TRUE);

	}
	else if(type >=1 && type <=5 )//告警 3
	{
		GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(FALSE);

		GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
	}
	else if( type == 6 || type == 7 )//故障 4 5
	{
		GetDlgItem(IDC_CHECK1)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK3)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHECK6)->EnableWindow(FALSE);

		GetDlgItem(IDC_CHECK4)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK5)->EnableWindow(TRUE);
	}


	InitListCtrl();//当选择复选框时comb1，调用列表框函数和配置函数，如果不调用会咋样？
	LoadKMGConfig();

}

void CKMGCfgView::OnRadio1() //开关类型--断路器 此处为选择radio，赋值，调用函数控件显示
{
	int type = m_KMGType.GetCurSel();
	mPzkIni.KMGFileTemp.Line[type].LineCfg.Switch_Type=0;
	SwitchType=0;
	LoadKMGConfig();
}


void CKMGCfgView::OnRadio2()//开关类型--负荷开关
{
	int type = m_KMGType.GetCurSel();
	mPzkIni.KMGFileTemp.Line[type].LineCfg.Switch_Type=1;
	SwitchType=1;
	LoadKMGConfig();
}

void CKMGCfgView::OnChangeEdit4() //#线路SBO号
{
	bEverEdited = true;//产生变化
	UpdateData(true);//界面到程序
	int type = m_KMGType.GetCurSel();
	mPzkIni.KMGFileTemp.Line[type].LineCfg.SBO_Num=m_SboNum;//#线路SBO号
}



void CKMGCfgView::OnKillfocusEdit4() //#线路SBO号
{
	UpdateData(UPDATE_READ);
	if(m_SboNum > 50)
	{
		AfxMessageBox("线路SBO号不能超过"+Str(50));
		m_SboNum = 50;
		UpdateData(UPDATE_WRITE);
	}
	if(m_SboNum < 0)
	{
		AfxMessageBox("线路SBO号不能小于"+Str(0));
		m_SboNum = 0;
		UpdateData(UPDATE_WRITE);
	}
}

void CKMGCfgView::OnChangeEdit5() //线路开关号
{
	bEverEdited = true;//产生变化
	UpdateData(true);//界面到程序
	int type = m_KMGType.GetCurSel();
	mPzkIni.KMGFileTemp.Line[type].LineCfg.Switch_Num=m_SwitchNum;//线路开关号

}

void CKMGCfgView::OnKillfocusEdit5() //线路开关号
{
	UpdateData(UPDATE_READ);
	if(m_SwitchNum > 50)
	{
		AfxMessageBox("线路开关号不能超过"+Str(50));
		m_SwitchNum = 50;
		UpdateData(UPDATE_WRITE);
	}
	if(m_SwitchNum < 0)
	{
		AfxMessageBox("线路开关号不能小于"+Str(0));
		m_SwitchNum = 0;
		UpdateData(UPDATE_WRITE);
	}
}

void CKMGCfgView::OnSave()
{
	UpdateData(true);//界面到变量
	mPzkIni.KMGFile.Cfg.Version=mPzkIni.KMGFileTemp.Cfg.Version;//版本号 ==其实没变化
	//m_PNumPerLine = mPzkIni.SXJZSFileTemp.Cfg.ProtNumPerLine;//每条线路多少保护 ==没变化
	mPzkIni.KMGFile.Cfg.Prot_YXEnable=mPzkIni.KMGFileTemp.Cfg.Prot_YXEnable;//保护虚遥信使能
	mPzkIni.KMGFile.Cfg.Prot_MsgEnable=mPzkIni.KMGFileTemp.Cfg.Prot_MsgEnable;//保护信息上报使能
	mPzkIni.KMGFile.Cfg.Byd_SOEEnable=mPzkIni.KMGFileTemp.Cfg.Byd_SOEEnable;//越限告警SOE使能
	mPzkIni.KMGFile.Cfg.Flt_YXEnable=mPzkIni.KMGFileTemp.Cfg.Flt_YXEnable;//故障检测分相上报使能
	mPzkIni.KMGFile.Cfg.Flt_RepEnable=mPzkIni.KMGFileTemp.Cfg.Flt_RepEnable;//故障报文上报使能
	mPzkIni.KMGFile.Cfg.Flt_RcwEnable=mPzkIni.KMGFileTemp.Cfg.Flt_RcwEnable;//故障录波使能

	mPzkIni.KMGFile.Cfg.FixActTime=m_FixActTime; //保护动作固有时间
	mPzkIni.KMGFile.Cfg.V_ConnectMode=CMode;//接线方式

	int i;
	int j;
	for(i=0;i<8;i++)
	{
		if(i == 0 )
		{
			mPzkIni.KMGFile.Line[i].LineCfg.Switch_Type=mPzkIni.KMGFileTemp.Line[i].LineCfg.Switch_Type;//开关类型
			mPzkIni.KMGFile.Line[i].LineCfg.SBO_Num=mPzkIni.KMGFileTemp.Line[i].LineCfg.SBO_Num;//#线路SBO号
			mPzkIni.KMGFile.Line[i].LineCfg.Switch_Num=mPzkIni.KMGFileTemp.Line[i].LineCfg.Switch_Num;//#线路开关号
			for(j=0;j<mPzkIni.KMGFileTemp.Cfg.ProtNumPerLine;j++)//全部保存一遍 0-每条线路保护数
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

void CKMGCfgView::OnKillfocusEdit3()//编辑各种内容
{
	CString str;
	m_Input.GetWindowText(str);
	listArray[0]->SetItemText(nItem, nSubItem, str);
	int type = m_KMGType.GetCurSel();
	if(type == 0 )
	{
		int index = KMG_Select[SwitchType][nItem];//保存数据数组的第某个开关的下标
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

void CKMGCfgView::OnKillfocusCombo2() //动作/告警/退出 鼠标选择组合框控件显示，赋值
{

	int type = m_KMGType.GetCurSel();//得到当前故障类型
	int index = KMG_Select[SwitchType][nItem];//保存数据数组的第某个开关的下标

	if(type == 0)
	{
		if(m_Enable.GetCurSel() == 0)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "动作");
			mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Enable=255;
		}
		else if(m_Enable.GetCurSel() == 1)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "告警");
			mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Enable=1;
		}
		else if(m_Enable.GetCurSel() == 2)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "退出");
			mPzkIni.KMGFileTemp.Line[type].KMGItem[index].Enable=0;
		}
	}
	else
	{
		if(m_Enable.GetCurSel() == 0)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "投入");
			mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Enable=255;
		}
		else if(m_Enable.GetCurSel() == 1)
		{
			listArray[0]->SetItemText(nItem, nSubItem, "退出");
			mPzkIni.KMGFileTemp.Line[type].KMGItem[0].Enable=0;
		}

	}






	m_Enable.ShowWindow(SW_HIDE);
	bEverEdited = true;
}

void CKMGCfgView::OnButton2() //取消
{
	int j;
	int i = m_KMGType.GetCurSel();//得到当前故障类型
	if(i == 0 )
	{
		mPzkIni.KMGFileTemp.Line[i].LineCfg.Switch_Type=mPzkIni.KMGFile.Line[i].LineCfg.Switch_Type;//开关类型
		mPzkIni.KMGFileTemp.Line[i].LineCfg.SBO_Num=mPzkIni.KMGFile.Line[i].LineCfg.SBO_Num;//#线路SBO号
		mPzkIni.KMGFileTemp.Line[i].LineCfg.Switch_Num=mPzkIni.KMGFile.Line[i].LineCfg.Switch_Num;//#线路开关号
		for(j=0;j<mPzkIni.KMGFileTemp.Cfg.ProtNumPerLine;j++)//全部保存一遍 0-每条线路保护数
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

void CKMGCfgView::OnRadio3() //开关类型--组合电器
{
	// TODO: Add your control notification handler code here

	int type = m_KMGType.GetCurSel();
	mPzkIni.KMGFileTemp.Line[type].LineCfg.Switch_Type=2;
	SwitchType=2;
	LoadKMGConfig();


}

void CKMGCfgView::OnCheck6()// 故障录波使能
{
	bEverEdited = true;
	UpdateData(true);//界面到程序
	if(m_Check6 == true)
	{
		mPzkIni.KMGFileTemp.Cfg.Flt_RcwEnable=255;
	}
	else
	{
		mPzkIni.KMGFileTemp.Cfg.Flt_RcwEnable=0;
	}

}


BOOL CKMGCfgView::PreTranslateMessage(MSG* pMsg)//tooltip重载父窗口的 BOOL PreTranslateMessage(MSG* pMsg) ，在函数中调用 m_tt.RelayEvent(pMsg)
{
	if(IsWindow(kmg_ToolTipCtr.m_hWnd))//为啥要加判断
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

void CKMGCfgView::OnChangeEdit6()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
}
