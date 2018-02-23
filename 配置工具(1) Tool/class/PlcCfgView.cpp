// PlcCfgView.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "ReadPzkIni.h"
#include "PlcCfgView.h"
#include "MyFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlcCfgView

IMPLEMENT_DYNCREATE(CPlcCfgView, CFormView)

CPlcCfgView::CPlcCfgView()
	: CFormView(CPlcCfgView::IDD)
{
	//{{AFX_DATA_INIT(CPlcCfgView)
	m_Total = 0;
	m_InNum = 0;
	m_Out1 = 0;
	m_Out2 = 0;
	m_T1 = 0;
	m_T2 = 0;
	m_T3 = 0;
	m_T4 = 0;
	m_T5 = 0;
	m_T6 = 0;
	m_Value1 = 0;
	m_Time1 = 0;
	m_Value2 = 0;
	m_Time2 = 0;
	m_Check1 = FALSE;
	m_Check2 = FALSE;
	m_Check3 = FALSE;
	m_PlcEnable = FALSE;
	m_AutoBztValue = 0;
	m_AutoBztTime = 0;
	m_AutoBztEnable = FALSE;
	m_TripTime = 0;
	m_CloseTime = 0;
	m_CheckVol = FALSE;
	m_BztCheckVol = FALSE;
	m_RecloseDelay = 0;
	m_LogicVol = 0;
	//}}AFX_DATA_INIT
	bEverEdited = false;
}

CPlcCfgView::~CPlcCfgView()
{
}

void CPlcCfgView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlcCfgView)
	DDX_Control(pDX, IDC_EDITBOX, m_Editbox);
	DDX_Control(pDX, IDC_COMBO1, m_ComBo1);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Text(pDX, IDC_EDIT1, m_Total);
	DDX_Text(pDX, IDC_EDIT2, m_InNum);
	DDX_Text(pDX, IDC_EDIT3, m_Out1);
	DDX_Text(pDX, IDC_EDIT4, m_Out2);
	DDX_Text(pDX, IDC_EDIT5, m_T1);
	DDX_Text(pDX, IDC_EDIT6, m_T2);
	DDX_Text(pDX, IDC_EDIT7, m_T3);
	DDX_Text(pDX, IDC_EDIT8, m_T4);
	DDX_Text(pDX, IDC_EDIT9, m_T5);
	DDX_Text(pDX, IDC_EDIT10, m_T6);
	DDX_Text(pDX, IDC_EDIT11, m_Value1);
	DDX_Text(pDX, IDC_EDIT12, m_Time1);
	DDX_Text(pDX, IDC_EDIT13, m_Value2);
	DDX_Text(pDX, IDC_EDIT14, m_Time2);
	DDX_Check(pDX, IDC_CHECK1, m_Check1);
	DDX_Check(pDX, IDC_CHECK2, m_Check2);
	DDX_Check(pDX, IDC_CHECK3, m_Check3);
	DDX_Check(pDX, IDC_CHECK4, m_PlcEnable);
	DDX_Text(pDX, IDC_EDIT15, m_AutoBztValue);
	DDX_Text(pDX, IDC_EDIT16, m_AutoBztTime);
	DDX_Check(pDX, IDC_CHECK5, m_AutoBztEnable);
	DDX_Text(pDX, IDC_EDIT17, m_TripTime);
	DDX_Text(pDX, IDC_EDIT18, m_CloseTime);
	DDX_Check(pDX, IDC_CHECK6, m_CheckVol);
	DDX_Check(pDX, IDC_CHECK7, m_BztCheckVol);
	DDX_Text(pDX, IDC_EDITBOX, m_RecloseDelay);
	DDX_Text(pDX, IDC_EDIT20, m_LogicVol);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlcCfgView, CFormView)
	//{{AFX_MSG_MAP(CPlcCfgView)
	ON_EN_KILLFOCUS(IDC_EDIT12, OnKillfocusEdit12)
	ON_EN_KILLFOCUS(IDC_EDIT13, OnKillfocusEdit13)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT3, OnKillfocusEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT4, OnKillfocusEdit4)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_CANCEl, OnCANCEl)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_CBN_KILLFOCUS(IDC_COMBO1, OnKillfocusCombo1)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, OnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT9, OnChangeEdit9)
	ON_EN_CHANGE(IDC_EDIT10, OnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT11, OnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT12, OnChangeEdit12)
	ON_EN_CHANGE(IDC_EDIT13, OnChangeEdit13)
	ON_EN_CHANGE(IDC_EDIT14, OnChangeEdit14)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_EN_CHANGE(IDC_EDIT15, OnChangeEdit15)
	ON_EN_CHANGE(IDC_EDIT16, OnChangeEdit16)
	ON_EN_CHANGE(IDC_EDIT17, OnChangeEdit17)
	ON_EN_CHANGE(IDC_EDIT18, OnChangeEdit18)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_EN_KILLFOCUS(IDC_EDITBOX, OnKillfocusEditbox)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlcCfgView diagnostics

#ifdef _DEBUG
void CPlcCfgView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPlcCfgView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

bool CPlcCfgView::GetRecloseEnable(CString sEnable)
{
	if(sEnable.Compare("投入") == 0)
		return true;
	else
		return false;
}

bool CPlcCfgView::GetCheckVoltage(CString sEnable)
{
	if(sEnable.Compare("投入") == 0)
		return true;
	else
		return false;
}

void CPlcCfgView::ResetRelcose(int pIn, int pOut1, int pOut2,
				  int In,  int Out1,  int Out2)
{
	PlcRecStru nRec, pRec;
//	bool PRecloseEnable[32];
//	bool NRecloseEnable[32];
	int i = 1;	//从进线开始
	int state = 0;	//0:in, 1:out1, 2:out2

	memset(nRec.ReClose, false, 32);
	while(i < 32)
	{
		pRec.ReClose[i] = GetRecloseEnable(m_List.GetItemText(i-1, 2));
		i++;
	}

	memcpy(nRec.ReClose+1, pRec.ReClose+1, In);
	memcpy(nRec.ReClose+1+In, pRec.ReClose+1+pIn, pOut1);
	memcpy(nRec.ReClose+1+In+Out1, pRec.ReClose+1+pIn+pOut1, pOut2);

	i = 1;
	memset(nRec.CheckVol, false, 32);
	while(i < 32)
	{
		pRec.CheckVol[i] = GetCheckVoltage(m_List.GetItemText(i-1, 3));
		i++;
	}

	memcpy(nRec.CheckVol+1, pRec.CheckVol+1, In);
	memcpy(nRec.CheckVol+1+In, pRec.CheckVol+1+pIn, pOut1);
	memcpy(nRec.CheckVol+1+In+Out1, pRec.CheckVol+1+pIn+pOut1, pOut2);

	i = 1;
	memset(nRec.RecloseDelay, 0, 32);
	while(i < 32)
	{
		pRec.RecloseDelay[i] = atoi(m_List.GetItemText(i-1, 4));
		i++;
	}

	memcpy(nRec.RecloseDelay+1, pRec.RecloseDelay+1, In*2);
	memcpy(nRec.RecloseDelay+1+In, pRec.RecloseDelay+1+pIn, pOut1*2);
	memcpy(nRec.RecloseDelay+1+In+Out1, pRec.RecloseDelay+1+pIn+pOut1, pOut2*2);

	UpdateList(nRec);
}
/////////////////////////////////////////////////////////////////////////////
// CPlcCfgView message handlers
void CPlcCfgView::UpdateList(PlcRecStru ReCloseCfg)
{
	CString formatStr;
	int addItem;
	m_List.DeleteAllItems();
	for(int i=1; i<m_Total; i++)
	{
		if(i <= m_InNum)
			formatStr.Format("进线%d重合闸投/退", i);
		else if( i <= (m_InNum + m_Out1) )
			formatStr.Format("出线1-%d重合闸投/退", i - m_InNum);	//为什么+1，因为出线序号从1开始
		else
			formatStr.Format("出线2-%d重合闸投/退", i - m_Out1 - m_InNum);
		addItem = m_List.InsertItem(i, Str(i), 0);
		m_List.SetItemText(addItem, 1, formatStr);
//投/退
		if(ReCloseCfg.ReClose[i])
			m_List.SetItemText(addItem, 2, "投入");
		else
			m_List.SetItemText(addItem, 2, "退出");
//重合前判电压？
		if(ReCloseCfg.CheckVol[i])
			m_List.SetItemText(addItem, 3, "投入");
		else
			m_List.SetItemText(addItem, 3, "退出");
//重合闸时间
		m_List.SetItemText(addItem, 4, Str((int)ReCloseCfg.RecloseDelay[i]));
	}
}

void CPlcCfgView::LoadData()
{
	m_PlcEnable = mPzkIni.PlcFile.Cfg.PlcEnable;
	m_Total = mPzkIni.PlcFile.Cfg.UnitTotal;
	Save_InNum = m_InNum = mPzkIni.PlcFile.Cfg.InNum;
	Save_Out1 = m_Out1 = mPzkIni.PlcFile.Cfg.OutNum1;
	Save_Out2 = m_Out2 = mPzkIni.PlcFile.Cfg.OutNum2;
	m_CheckVol = mPzkIni.PlcFile.Cfg.RecloseCheckVol;
	m_BztCheckVol = mPzkIni.PlcFile.Cfg.BztCheckVol;
	m_LogicVol = mPzkIni.PlcFile.Cfg.LogicVol;

	m_T1 = mPzkIni.PlcFile.Delay.InRecloseTime;
	m_T2 = mPzkIni.PlcFile.Delay.OutRecloseTime;
	m_T3 = mPzkIni.PlcFile.Delay.InReclose2Time;
	m_T4 = mPzkIni.PlcFile.Delay.ConnectTime;
	m_T5 = mPzkIni.PlcFile.Delay.t5;
	m_T6 = mPzkIni.PlcFile.Delay.t6;

	m_Check1 = (BOOL)mPzkIni.PlcFile.LVProt.Enable1;
	m_Value1 = mPzkIni.PlcFile.LVProt.Value1;
	m_Time1 = mPzkIni.PlcFile.LVProt.Delay1;
	m_Check2 = (BOOL)mPzkIni.PlcFile.LVProt.Enable2;
	m_Value2 = mPzkIni.PlcFile.LVProt.Value2;
	m_Time2 = mPzkIni.PlcFile.LVProt.Delay2;

	m_AutoBztEnable = mPzkIni.PlcFile.AutoBzt.Enable;
	m_AutoBztValue = mPzkIni.PlcFile.AutoBzt.Value;
	m_AutoBztTime = mPzkIni.PlcFile.AutoBzt.Delay;

	m_TripTime = mPzkIni.PlcFile.CtrlTime.TripTime;
	m_CloseTime = mPzkIni.PlcFile.CtrlTime.CloseTime;

	m_Check3 = (BOOL)mPzkIni.PlcFile.Bzt.ConnectEnable;

	UpdateData(UPDATE_WRITE);
	UpdateList(mPzkIni.PlcFile.Reclose);
}

void CPlcCfgView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	int i = 0;
	m_List.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List.InsertColumn(i++, "序号", LVCFMT_LEFT, 45, -1);
	m_List.InsertColumn(i++, "名称", LVCFMT_LEFT, 145, -1);
	m_List.InsertColumn(i++, "投/退", LVCFMT_CENTER, 80, -1);
	m_List.InsertColumn(i++, "做出线时重合前判电压", LVCFMT_CENTER, 200, -1);
	m_List.InsertColumn(i++, "重合闸时限(ms)", LVCFMT_LEFT, 110, -1);

	mPzkIni.PlcFile.Cfg.UnitTotal = 1 +
								mPzkIni.PlcFile.Cfg.InNum +
								mPzkIni.PlcFile.Cfg.OutNum1 +
								mPzkIni.PlcFile.Cfg.OutNum2;

	LoadData();
}

void CPlcCfgView::OnKillfocusEdit12()
{
	// TODO: Add your control notification handler code here

}

void CPlcCfgView::OnKillfocusEdit13()
{
	// TODO: Add your control notification handler code here

}

void CPlcCfgView::OnKillfocusEdit2()
{
	// TODO: Add your control notification handler code here
	UpdateData(UPDATE_READ);
	if(m_InNum > 2)
		m_InNum = 2;
	m_Total = 1 + m_InNum + m_Out1 + m_Out2;
	if(m_Total > 32)
	{
		m_Total = 32;
		m_InNum = m_Total - 1 - m_Out1 - m_Out2;
	}
	UpdateData(UPDATE_WRITE);
	if(Save_InNum != m_InNum)
		ResetRelcose(Save_InNum, Save_Out1, Save_Out2, m_InNum, Save_Out1, Save_Out2);
	Save_InNum = m_InNum;
}

void CPlcCfgView::OnKillfocusEdit3()
{
	// TODO: Add your control notification handler code here
	UpdateData(UPDATE_READ);
	m_Total = 1 + m_InNum + m_Out1 + m_Out2;
	if(m_Total > 32)
	{
		m_Total = 32;
		m_Out1 = m_Total - 1 - m_InNum - m_Out2;
	}
	UpdateData(UPDATE_WRITE);
	CString str1;
	str1.Format("%d",m_Out1);
	AfxMessageBox(str1);
	if(Save_Out1 != m_Out1)
		ResetRelcose(Save_InNum, Save_Out1, Save_Out2, Save_InNum, m_Out1, Save_Out2);
	Save_Out1 = m_Out1;
}

void CPlcCfgView::OnKillfocusEdit4()
{
	// TODO: Add your control notification handler code here
	UpdateData(UPDATE_READ);
	m_Total = 1 + m_InNum + m_Out1 + m_Out2;
	AfxMessageBox("111111");
	if(m_Total > 32)
	{
		m_Total = 32;
		m_Out2 = m_Total - 1 - m_InNum - m_Out1;
	}
	UpdateData(UPDATE_WRITE);
//	AfxMessageBox("总控单元数不得超过32个!");
	if(Save_Out2 != m_Out2)
		ResetRelcose(Save_InNum, Save_Out1, Save_Out2, Save_InNum, Save_Out1, m_Out2);
	Save_Out2 = m_Out2;
}

void CPlcCfgView::OnSave()
{
	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;

	UpdateData(UPDATE_READ);

	mPzkIni.PlcFile.Cfg.PlcEnable = (m_PlcEnable)? true : false;
	mPzkIni.PlcFile.Cfg.UnitTotal = m_Total;
	mPzkIni.PlcFile.Cfg.InNum = m_InNum;
	mPzkIni.PlcFile.Cfg.OutNum1 = m_Out1;
	mPzkIni.PlcFile.Cfg.OutNum2 = m_Out2;
	mPzkIni.PlcFile.Cfg.RecloseCheckVol = (m_CheckVol)? true : false;
	mPzkIni.PlcFile.Cfg.BztCheckVol = (m_BztCheckVol)? true : false;
	mPzkIni.PlcFile.Cfg.LogicVol = m_LogicVol;

	mPzkIni.PlcFile.Delay.InRecloseTime = m_T1;
	mPzkIni.PlcFile.Delay.OutRecloseTime = m_T2;
	mPzkIni.PlcFile.Delay.InReclose2Time = m_T3;
	mPzkIni.PlcFile.Delay.ConnectTime = m_T4;
	mPzkIni.PlcFile.Delay.t5 = m_T5;
	mPzkIni.PlcFile.Delay.t6 = m_T6;

	mPzkIni.PlcFile.LVProt.Enable1 = (m_Check1)? true : false;
	mPzkIni.PlcFile.LVProt.Value1 = m_Value1;
	mPzkIni.PlcFile.LVProt.Delay1 = m_Time1;
	mPzkIni.PlcFile.LVProt.Enable2 = (m_Check2)? true : false;
	mPzkIni.PlcFile.LVProt.Value2 = m_Value2;
	mPzkIni.PlcFile.LVProt.Delay2 = m_Time2;

	mPzkIni.PlcFile.AutoBzt.Enable = (m_AutoBztEnable)? true : false;
	mPzkIni.PlcFile.AutoBzt.Value = m_AutoBztValue;
	mPzkIni.PlcFile.AutoBzt.Delay = m_AutoBztTime;

	mPzkIni.PlcFile.CtrlTime.TripTime = m_TripTime;
	mPzkIni.PlcFile.CtrlTime.CloseTime = m_CloseTime;

	mPzkIni.PlcFile.Bzt.ConnectEnable = (m_Check3)? true : false;

/*	int num = m_List.GetItemCount();
	for(int i=0; i<num; i++)
	{
		if(m_List.GetItemText(i, 2) == "投入")
			mPzkIni.PlcFile.Reclose.ReClose[i+1] = true;
		else
			mPzkIni.PlcFile.Reclose.ReClose[i+1] = false;

		if(m_List.GetItemText(i, 3) == "投入")
			mPzkIni.PlcFile.Reclose.CheckVol[i+1] = true;
		else
			mPzkIni.PlcFile.Reclose.CheckVol[i+1] = false;

		mPzkIni.PlcFile.Reclose.RecloseDelay[i+1] = (unsigned short)atoi(m_List.GetItemText(i, 4));
	}

	bEverEdited = false;
	mPzkIni.EverModified = true;*/
}

void CPlcCfgView::OnCANCEl()
{
	// TODO: Add your control notification handler code here
	LoadData();
	bEverEdited = false;
}

void CPlcCfgView::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
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
	if( (nSubItem != 2) && (nSubItem != 3) && (nSubItem != 4) )
		return;

	if( nSubItem != 4)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO1);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO1);
		if(m_List.GetItemText(nItem, nSubItem) == "投入")
			pCombo->SetCurSel(0);
		else
			pCombo->SetCurSel(1);

		pCombo->SetItemHeight(-1,12);
	}
	else
	{
		pWnd = ::GetDlgItem(m_hWnd, IDC_EDITBOX);
		CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDITBOX);
		pEdit->SetWindowText(m_List.GetItemText(nItem, nSubItem));
	}
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

void CPlcCfgView::OnKillfocusCombo1()
{
	// TODO: Add your control notification handler code here
	int i = m_ComBo1.GetCurSel();
	if(i == 0)
		m_List.SetItemText(nItem, nSubItem, "投入");
	else
		m_List.SetItemText(nItem, nSubItem, "退出");
	m_ComBo1.ShowWindow(SW_HIDE);
}

LRESULT CPlcCfgView::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)
{
//	OnCANCEl();
	return TRUE;
}

LRESULT CPlcCfgView::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)
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

void CPlcCfgView::OnChangeEdit1()
{
	bEverEdited = true;
}

void CPlcCfgView::OnChangeEdit2()
{
	bEverEdited = true;
}

void CPlcCfgView::OnChangeEdit3()
{
	bEverEdited = true;
}

void CPlcCfgView::OnChangeEdit4()
{
	bEverEdited = true;
}

void CPlcCfgView::OnChangeEdit5()
{
	bEverEdited = true;
}

void CPlcCfgView::OnChangeEdit6()
{
	bEverEdited = true;
}

void CPlcCfgView::OnChangeEdit7()
{
	bEverEdited = true;
}

void CPlcCfgView::OnChangeEdit8()
{
	bEverEdited = true;
}

void CPlcCfgView::OnChangeEdit9()
{
	bEverEdited = true;
}

void CPlcCfgView::OnChangeEdit10()
{
	bEverEdited = true;
}

void CPlcCfgView::OnChangeEdit11()
{
	bEverEdited = true;
}

void CPlcCfgView::OnChangeEdit12()
{
	bEverEdited = true;
}

void CPlcCfgView::OnChangeEdit13()
{
	bEverEdited = true;
}

void CPlcCfgView::OnChangeEdit14()
{
	bEverEdited = true;
}

void CPlcCfgView::OnCheck1()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPlcCfgView::OnCheck2()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPlcCfgView::OnCheck3()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPlcCfgView::OnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPlcCfgView::OnCheck4()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPlcCfgView::OnCheck5()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPlcCfgView::OnChangeEdit15()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here

	bEverEdited = true;
}

void CPlcCfgView::OnChangeEdit16()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here

	bEverEdited = true;
}

void CPlcCfgView::OnChangeEdit17()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here

	bEverEdited = true;
}

void CPlcCfgView::OnChangeEdit18()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here

	bEverEdited = true;
}

void CPlcCfgView::OnCheck6()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPlcCfgView::OnCheck7()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPlcCfgView::OnKillfocusEditbox()
{
	// TODO: Add your control notification handler code here
	CString str;
	m_Editbox.GetWindowText(str);
	m_List.SetItemText(nItem, nSubItem, Str(atoi(str)));
	m_Editbox.ShowWindow(SW_HIDE);
	bEverEdited = true;
}
