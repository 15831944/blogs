// Pzk300ProCfgView.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "ReadPzkIni.h"
#include "MyFun.h"
#include "Pzk300ProCfgView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern bool bCloseWindow;

#define CANNOT_EDIT		0
#define NORMAL_EDIT		1
#define NUMBER_EDIT		2
#define NORMAL_COMBO	3

#define COL_NO		0
#define COL_NAME	1
#define COL_ENABLE	2
#define COL_VALUE	3
#define COL_VUINT	4
#define COL_VMAX	5
#define COL_VMIN	6
#define COL_TIME	7
#define COL_TUNIT	8
#define COL_TMAX	9
#define COL_TMIN	10

#ifdef __SUPERMODE
const EditInputTypes[] = {	CANNOT_EDIT,		//序号
							NORMAL_EDIT,		//名称
							NORMAL_COMBO,		//投退
							NUMBER_EDIT,		//定值
							NORMAL_EDIT,		//单位
							NUMBER_EDIT,		//最大值
							NUMBER_EDIT,		//最小值
							NUMBER_EDIT,		//延时
							NORMAL_EDIT,		//单位
						    NUMBER_EDIT,       	//最大值
                            NUMBER_EDIT,    	//最小值
};
#else
const EditInputTypes[] = {	CANNOT_EDIT,		//序号
							CANNOT_EDIT,		//名称
							NORMAL_COMBO,		//投退
							NUMBER_EDIT,		//定值
							CANNOT_EDIT,		//单位
							CANNOT_EDIT,		//最大值
							CANNOT_EDIT,		//最小值
							NUMBER_EDIT,		//延时
							CANNOT_EDIT,		//单位
						    CANNOT_EDIT,       	//最大值
                            CANNOT_EDIT,    	//最小值
};
#endif
/////////////////////////////////////////////////////////////////////////////
// CPzk300ProCfgView

IMPLEMENT_DYNCREATE(CPzk300ProCfgView, CFormView)

CPzk300ProCfgView::CPzk300ProCfgView()
	: CFormView(CPzk300ProCfgView::IDD)
{
	//{{AFX_DATA_INIT(CPzk300ProCfgView)
	//}}AFX_DATA_INIT
	bCurViewIsActive = false;
	bEverEdited = false;
}

CPzk300ProCfgView::~CPzk300ProCfgView()
{
}

void CPzk300ProCfgView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPzk300ProCfgView)
	DDX_Control(pDX, IDC_CANCEl, m_BN2);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_COMBO1, m_Combo1);
	DDX_Control(pDX, IDC_SAVE, m_BN1);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPzk300ProCfgView, CFormView)
	//{{AFX_MSG_MAP(CPzk300ProCfgView)
	ON_COMMAND(ID_300_ADD, On300Add)
	ON_COMMAND(ID_300_INSERT, On300Insert)
	ON_COMMAND(ID_300_REMOVE, On300Remove)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_WM_SIZE()
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnKillfocusEdit2)
	ON_CBN_KILLFOCUS(IDC_COMBO1, OnKillfocusCombo1)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_CANCEl, OnCANCEl)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
	ON_NOTIFY(WM_HSCROLL, IDC_LIST1, OnHScrollList1)
	ON_NOTIFY(WM_VSCROLL, IDC_LIST1, OnVScrollList1)
	ON_WM_LBUTTONUP()
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPzk300ProCfgView diagnostics

#ifdef _DEBUG
void CPzk300ProCfgView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPzk300ProCfgView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPzk300ProCfgView message handlers

void CPzk300ProCfgView::On300Add()
{
	// TODO: Add your command handler code here
	int mSelItem = m_List.GetItemCount();

	m_List.InsertItem(mSelItem, Str(mSelItem));
	m_List.SetItemText(mSelItem, COL_NAME,	 "");
	m_List.SetItemText(mSelItem, COL_ENABLE, "FASLE");
	m_List.SetItemText(mSelItem, COL_VALUE,	 "0");
	m_List.SetItemText(mSelItem, COL_VUINT,	 "无");
	m_List.SetItemText(mSelItem, COL_VMAX,	 "0");
	m_List.SetItemText(mSelItem, COL_VMIN,	 "0");
	m_List.SetItemText(mSelItem, COL_TIME,	 "0");
	m_List.SetItemText(mSelItem, COL_TUNIT,	 "无");
	m_List.SetItemText(mSelItem, COL_TMAX,	 "0");
	m_List.SetItemText(mSelItem, COL_TMIN,	 "0");

	for(int i=0; i<m_List.GetItemCount(); i++)
		m_List.SetItemText(i,0,Str(i));
	bEverEdited = true;
}

void CPzk300ProCfgView::On300Insert()
{
	// TODO: Add your command handler code here
	int mSelItem;
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if(!pos)
		mSelItem = m_List.GetItemCount();
	else
		mSelItem = m_List.GetSelectionMark();

	m_List.InsertItem(mSelItem, Str(mSelItem));
	m_List.SetItemText(mSelItem, COL_NAME, "");
	m_List.SetItemText(mSelItem, COL_ENABLE, "FASLE");
	m_List.SetItemText(mSelItem, COL_VALUE, "0");
	m_List.SetItemText(mSelItem, COL_VUINT, "无");
	m_List.SetItemText(mSelItem, COL_VMAX, "0");
	m_List.SetItemText(mSelItem, COL_VMIN, "0");
	m_List.SetItemText(mSelItem, COL_TIME, "0");
	m_List.SetItemText(mSelItem, COL_TUNIT, "无");
	m_List.SetItemText(mSelItem, COL_TMAX, "0");
	m_List.SetItemText(mSelItem, COL_TMIN, "0");

	for(int i=0; i<m_List.GetItemCount(); i++)
		m_List.SetItemText(i,0,Str(i));
	bEverEdited = true;
}

void CPzk300ProCfgView::On300Remove()
{
	// TODO: Add your command handler code here
	int ItemNo;
	int ItemNum;
	CListCtrl *pList;
	pList = (CListCtrl *)GetDlgItem(IDC_LIST1);

	POSITION pos = pList->GetFirstSelectedItemPosition();
	if(!pos)
		return;
	CString str,str1;
	str="你确定要删除第";
	while (pos)
	{
	   ItemNo = pList->GetNextSelectedItem(pos);
	   str1.Format("%d",ItemNo);
	   if(pos)
		   str1 += ",";
	   str+=str1;
	}
	str+= "项吗?";

	int OkNo = AfxMessageBox(str,MB_YESNO);
	if(OkNo != IDYES)
		return;

	pos = pList->GetFirstSelectedItemPosition();
	while (pos)
	{
	   ItemNo = pList->GetNextSelectedItem(pos);
	   pList->DeleteItem(ItemNo);
	   pos = pList->GetFirstSelectedItemPosition();
	}

	ItemNum = pList->GetItemCount();
	for(int i=0;i<ItemNum;i++)
		pList->SetItemText(i,0,Str(i));

	UpdateData(FALSE);
	bEverEdited = true;
}

void CPzk300ProCfgView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	bCurViewIsActive = true;
	mMenu.LoadMenu(IDR_MENU_EDIT_300);
	CFont *pfont = new CFont();
	pfont->CreateFont(13, 0, 0, 0,
         FW_NORMAL | FW_BOLD, FALSE, FALSE,
         FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
         DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, "宋体");
	m_Edit1.SetFont(pfont);
	m_Edit2.SetFont(pfont);
	m_Combo1.SetFont(pfont);
	m_List.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List.InsertColumn(COL_NO, "序号", LVCFMT_LEFT, 50, -1);
	m_List.InsertColumn(COL_NAME, "名称", LVCFMT_LEFT, 100, -1);
	m_List.InsertColumn(COL_ENABLE, "投退", LVCFMT_LEFT, 80, -1);
	m_List.InsertColumn(COL_VALUE, "定值", LVCFMT_LEFT, 80, -1);
	m_List.InsertColumn(COL_VUINT, "单位", LVCFMT_LEFT, 50, -1);
	m_List.InsertColumn(COL_VMAX, "最大值", LVCFMT_LEFT, 80, -1);
	m_List.InsertColumn(COL_VMIN, "最小值", LVCFMT_LEFT, 80, -1);
	m_List.InsertColumn(COL_TIME, "延时", LVCFMT_LEFT, 80, -1);
	m_List.InsertColumn(COL_TUNIT, "单位", LVCFMT_LEFT, 50, -1);
	m_List.InsertColumn(COL_TMAX, "最大值", LVCFMT_LEFT, 80, -1);
	m_List.InsertColumn(COL_TMIN, "最小值", LVCFMT_LEFT, 80, -1);

	LoadData();
}

void CPzk300ProCfgView::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CString str;
	CComboBox *pCombo;
	CEdit *pEdit;
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
	str = m_List.GetItemText(nItem, nSubItem);
    switch(EditInputTypes[nSubItem])
	{
	case CANNOT_EDIT:
		return;
	case NORMAL_EDIT:
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT1);
		pEdit = (CEdit *)GetDlgItem(IDC_EDIT1);
		pEdit->SetWindowText(str);
		break;
	case NUMBER_EDIT:
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT2);
		::SetWindowText(pWnd,str);
		break;
	case NORMAL_COMBO:
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO1);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO1);
		str = m_List.GetItemText(nItem, nSubItem);
		if(str.Compare("TRUE") == 0)
			pCombo->SetCurSel(0);
		else
			pCombo->SetCurSel(1);
		pCombo->SetItemHeight(-1,15);
		break;
	default:
		return;
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
		HWND_TOP,rect.left+x+3,rect.top+y+2,
		rect.right-rect.left,
		rect.bottom-rect.top - 1,NULL);
	::ShowWindow(pWnd,SW_SHOW);
	::SetFocus(pWnd);
	//Draw a Rectangle around the SubItem
//	::Rectangle(::GetDC(temp->hdr.hwndFrom),
//		rect.left,rect.top-1,rect.right,rect.bottom);
	//Set the listItem text in the EditBox
//	::SetWindowText(::GetDlgItem(m_hWnd,mEdit),str);

	*pResult = 0;
}

void CPzk300ProCfgView::LoadData()
{
	int i;
	Pzk300ProItemCfgStru val;
	m_List.DeleteAllItems();
	for (i=0; i<mPzkIni.mPzk300ProCfg.num; i++)
	{
		val = mPzkIni.mPzk300ProCfg.ProcCfg[i];
		m_List.InsertItem(i, Str(i),NULL);
		m_List.SetItemText(i, COL_NAME, val.ProtectName);
		if(val.ProtectEnable % 2)
			m_List.SetItemText(i, COL_ENABLE, "FALSE");
		else
			m_List.SetItemText(i, COL_ENABLE, "TRUE");
		m_List.SetItemText(i, COL_VALUE, Str(val.ProtectValue));
		m_List.SetItemText(i, COL_VUINT, val.ProtectValueUnit);
		m_List.SetItemText(i, COL_VMAX, Str(val.ProtectValueHLimit));
		m_List.SetItemText(i, COL_VMIN, Str(val.ProtectValueLLimit));
		m_List.SetItemText(i, COL_TIME, Str(val.ProtectTime));
		m_List.SetItemText(i, COL_TUNIT, val.ProtectTimeUnit);
		m_List.SetItemText(i, COL_TMAX, Str(val.ProtectTimeHLimit));
		m_List.SetItemText(i, COL_TMIN, Str(val.ProtectTimeLLimit));
	}
}

void CPzk300ProCfgView::OnSize(UINT nType, int cx, int cy)
{
	if(cx < 400)
		cx = 400;
	if(cy < 400)
		cy = 400;

	CFormView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if(!bCurViewIsActive)
		return;

	RECT rect,rect1;
	int mWidth;
	bool bChgH,bChgW;

	rect.top = 25;
	rect.left = 20;
	rect.bottom = cy - 80;
	rect.right = cx - 40;

	bChgW = (rect.right - rect.left) > 400;
	bChgH = (rect.bottom - rect.top) > 400;
	if(!(bChgW || bChgH))
		return;

	if(!bChgH) rect.bottom = rect.top + 300;
	if(!bChgW) rect.right = rect.left + 400;

	mWidth = rect.right - rect.left;
	m_List.MoveWindow(&rect,FALSE);
//	m_BN1.SetWindowPos(NULL, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,SWP_SHOWWINDOW);

	m_BN1.GetClientRect(&rect1);
	rect1.top = rect.bottom + 20;
	rect1.bottom = rect1.top + 28;
	rect1.left = rect.left + mWidth/2 - 200;
	rect1.right = rect1.left + 100;
	m_BN1.MoveWindow(&rect1,TRUE);
//	m_BN1.SetWindowPos(NULL, rect1.left, rect1.top, mWidth/2-200, 100,SWP_SHOWWINDOW);

	m_BN2.GetClientRect(&rect1);
	rect1.top = rect.bottom + 20;
	rect1.bottom = rect1.top + 28;
	rect1.left = rect.left + mWidth/2 + 100;
	rect1.right = rect1.left + 100;
	m_BN2.MoveWindow(&rect1,TRUE);
//	m_BN2.SetWindowPos(NULL, rect1.left, rect1.top, mWidth/2+100, 100,SWP_SHOWWINDOW);
}

void CPzk300ProCfgView::OnKillfocusEdit1()
{
	// TODO: Add your control notification handler code here
	CString str;
	m_Edit1.GetWindowText(str);
	m_List.SetItemText(nItem, nSubItem, str);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT1),SW_HIDE);
	if(m_Edit1.GetModify() == TRUE)
		bEverEdited = true;
}


UINT tt1(LPVOID para);

void CPzk300ProCfgView::OnKillfocusEdit2()
{
	// TODO: Add your control notification handler code here
	CString showStr="", str = "";
	int CurVal = myatoi(m_List.GetItemText(nItem, COL_VALUE));
	int ValMax = myatoi(m_List.GetItemText(nItem, COL_VMAX));
	int ValMin = myatoi(m_List.GetItemText(nItem, COL_VMIN));
	int CurTime = myatoi(m_List.GetItemText(nItem, COL_TIME));
	int TimeMax = myatoi(m_List.GetItemText(nItem, COL_TMAX));
	int TimeMin = myatoi(m_List.GetItemText(nItem, COL_TMIN));

	m_Edit2.GetWindowText(str);
	if(str.GetLength() == 0)
		str = "0";

	switch(nSubItem)
	{
	case COL_VALUE:
		CurVal = myatoi(str);
		if((ValMax == 0)  && (ValMin == 0))
			break;
		if(CurVal > ValMax)
		{
			showStr.Format("不能大于最大值%d", ValMax);
			str.Format("%d", ValMax);
		}
		else if(CurVal < ValMin)
		{
			showStr.Format("不能小于最小值%d", ValMin);
			str.Format("%d", ValMin);
		}
		break;
	case COL_VMAX:
		ValMax = myatoi(str);
		if((ValMax == 0)  && (ValMin == 0))
			break;
		if(ValMax < CurVal)
		{
			showStr.Format("不能小于当前值%d", CurVal);
			str.Format("%d", CurVal);
		}
		break;
	case COL_VMIN:
		ValMin = myatoi(str);
		if((ValMax == 0)  && (ValMin == 0))
			break;
		if(ValMin > CurVal)
		{
			showStr.Format("不能大于当前值%d", CurVal);
			str.Format("%d", CurVal);
		}
		break;
	case COL_TIME:
		CurTime = myatoi(str);
		if((TimeMax == 0)  && (TimeMin == 0))
			break;
		if(CurTime > TimeMax)
		{
			showStr.Format("不能大于最大值%d", TimeMax);
			str.Format("%d", TimeMax);
		}
		else if(CurVal < TimeMin)
		{
			showStr.Format("不能小于最小值%d", TimeMin);
			str.Format("%d", TimeMin);
		}
		break;
	case COL_TMAX:
		TimeMax = myatoi(str);
		if((TimeMax == 0)  && (TimeMin == 0))
			break;
		if(TimeMax < CurTime)
		{
			showStr.Format("不能小于当前值%d", CurTime);
			str.Format("%d", CurTime);
		}
		break;
	case COL_TMIN:
		TimeMin = myatoi(str);
		if((TimeMax == 0)  && (TimeMin == 0))
			break;
		if(TimeMin > CurTime)
		{
			showStr.Format("不能大于当前值%d", CurTime);
			str.Format("%d", CurTime);
		}
		break;
	default:
		break;
	}
	m_List.SetItemText(nItem,nSubItem,str);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT2),SW_HIDE);
	if(!showStr.IsEmpty())
		AfxMessageBox(showStr);

	this->PostMessage(WM_LBUTTONUP,NULL,NULL);
	if(m_Edit2.GetModify())
		bEverEdited = true;
}

void CPzk300ProCfgView::OnKillfocusCombo1()
{
	// TODO: Add your control notification handler code here
	if(m_Combo1.GetCurSel() == 0)
		m_List.SetItemText(nItem, nSubItem, "TRUE");
	else
		m_List.SetItemText(nItem, nSubItem, "FALSE");
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_COMBO1),SW_HIDE);
//	bEverEdited = true;
//	this->SendMessage(WM_LBUTTONUP,NULL,NULL);
}

void CPzk300ProCfgView::OnSave()
{
	// TODO: Add your control notification handler code here
	CString str;
	int i;
	Pzk300ProItemCfgStru *val;
	mPzkIni.mPzk300ProCfg.num = m_List.GetItemCount();
	if(mPzkIni.mPzk300NormalCfg.num > MAX_300_PRO_CFG)
	{
		str.Format("最大只允许配置%d个项目,所以只保存前%d项目",
					MAX_300_PRO_CFG,
					MAX_300_PRO_CFG);
		AfxMessageBox(str);
		mPzkIni.mPzk300ProCfg.num = MAX_300_PRO_CFG;
	}

	for(i=0; i<mPzkIni.mPzk300ProCfg.num; i++)
	{
		val = &(mPzkIni.mPzk300ProCfg.ProcCfg[i]);
		val->ProtectName = m_List.GetItemText(i, COL_NAME);
		if(m_List.GetItemText(i ,COL_ENABLE) == "TRUE")
			val->ProtectEnable = 2;
		else
			val->ProtectEnable = 1;
		val->ProtectValue = myatoi(m_List.GetItemText(i, COL_VALUE));
		val->ProtectValueUnit = m_List.GetItemText(i ,COL_VUINT);
		val->ProtectValueHLimit = myatoi(m_List.GetItemText(i ,COL_VMAX));
		val->ProtectValueLLimit = myatoi(m_List.GetItemText(i, COL_VMIN));
		val->ProtectTime = myatoi(m_List.GetItemText(i ,COL_TIME));
		val->ProtectTimeUnit = m_List.GetItemText(i ,COL_TUNIT);
		val->ProtectTimeHLimit = myatoi(m_List.GetItemText(i, COL_TMAX));
		val->ProtectTimeLLimit = myatoi(m_List.GetItemText(i, COL_TMIN));
	}
	bEverEdited = false;
	mPzkIni.EverModified = true;
}

void CPzk300ProCfgView::OnCANCEl()
{
	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;
	bEverEdited = false;
	LoadData();
}

LRESULT CPzk300ProCfgView::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)
{
//	OnCANCEl();
	return TRUE;
}

LRESULT CPzk300ProCfgView::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)
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
			OnCANCEl();
	}
	bEverEdited = false;
	return TRUE;
}

void CPzk300ProCfgView::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
#ifndef __SUPERMODE
	return;
#endif
	CPoint oPoint;//定义一个用于确定光标位置的位置
    GetCursorPos( &oPoint);//
	CMenu *hMenu;
	hMenu = mMenu.GetSubMenu(0);
	hMenu->TrackPopupMenu(TPM_LEFTALIGN,oPoint.x,oPoint.y,this,0);
	*pResult = 0;
}

BOOL CPzk300ProCfgView::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	int i;
	if(bEverEdited)
	{
		i = AfxMessageBox("您已经修改了保护参数配置，在退出该配置前确定要保存吗？",MB_YESNOCANCEL);
		if(i == IDYES)
			OnSave();
		else if(i == IDCANCEL)
		{
			bCloseWindow = false;
			return FALSE;
		}
	}

	return CFormView::DestroyWindow();
}

void CPzk300ProCfgView::OnHScrollList1(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	if (GetFocus() != this)
	{
		SetFocus();
	}

	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CPzk300ProCfgView::OnVScrollList1(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	if (GetFocus() != this)
	{
		SetFocus();
	}

	CFormView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CPzk300ProCfgView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CFormView::OnLButtonUp(nFlags, point);
}

void CPzk300ProCfgView::OnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}
