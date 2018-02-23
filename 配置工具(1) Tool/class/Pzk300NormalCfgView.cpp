// Pzk300NormalCfgView.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "ReadPzkIni.h"
#include "Pzk300NormalCfgView.h"
#include "MyFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define __VAL_TYPE1	1		//为了“门限系数”等几个配置项中数据显示时与实际值有一个比例系数

extern void ReadUnionData(Pzk300UnionStru *val, int datatype, CString KeyStr);
extern bool bCloseWindow;
/////////////////////////////////////////////////////////////////////////////
// CPzk300NormalCfgView

IMPLEMENT_DYNCREATE(CPzk300NormalCfgView, CFormView)

CPzk300NormalCfgView::CPzk300NormalCfgView()
	: CFormView(CPzk300NormalCfgView::IDD)
{
	//{{AFX_DATA_INIT(CPzk300NormalCfgView)
	//}}AFX_DATA_INIT
	bCurViewIsActive = false;
	bEverEdited = false;
}

CPzk300NormalCfgView::~CPzk300NormalCfgView()
{
}

void CPzk300NormalCfgView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPzk300NormalCfgView)
	DDX_Control(pDX, IDC_CANCEl, m_BN2);
	DDX_Control(pDX, IDC_SAVE, m_BN1);
	DDX_Control(pDX, IDC_COMBO1, m_Combo1);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPzk300NormalCfgView, CFormView)
	//{{AFX_MSG_MAP(CPzk300NormalCfgView)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT3, OnKillfocusEdit3)
	ON_CBN_KILLFOCUS(IDC_COMBO1, OnKillfocusCombo1)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_CANCEl, OnCANCEl)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
	ON_COMMAND(ID_300_ADD, On300Add)
	ON_COMMAND(ID_300_REMOVE, On300Remove)
	ON_COMMAND(ID_300_INSERT, On300Insert)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPzk300NormalCfgView diagnostics

#ifdef _DEBUG
void CPzk300NormalCfgView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPzk300NormalCfgView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

const CString DataTypes[] = {	"无类型",
//								"字节型",
//								"字型",
//								"双字型",
								"整型",
								"浮点型",
								"字符串"
};

#define CANNOT_EDIT		0
#define NORMAL_EDIT		1
#define NUMBER_EDIT		2
#define NORMAL_COMBO	3

#ifdef __SUPERMODE

	#define COL_NO		0
	#define COL_NAME	1
	#define COL_DEFINE	2
	#define COL_VALUE	3
	#define COL_VUINT	4
	#define COL_VTYPE	5
	#define COL_VMAX	6
	#define COL_VMIN	7
	#define COL_REMARK	8

	const EditInputTypes[] = {	CANNOT_EDIT,		//序号
								NORMAL_EDIT,		//名称
								NORMAL_EDIT,		//常量定义
								NUMBER_EDIT,		//定值
								NORMAL_EDIT,		//单位
								NORMAL_COMBO,		//数据类型
								NUMBER_EDIT,		//最大值
								NUMBER_EDIT,		//最小值
								NORMAL_EDIT,		//备注
							};
#else

	#define COL_NO		0
	#define COL_NAME	1
	#define COL_VALUE	2
	#define COL_VUINT	3
	#define COL_VTYPE	4
	#define COL_VMAX	5
	#define COL_VMIN	6
	#define COL_REMARK	7

	const EditInputTypes[] = {	CANNOT_EDIT,		//序号
								CANNOT_EDIT,		//名称
//								CANNOT_EDIT,		//常量定义
								NUMBER_EDIT,		//定值
								CANNOT_EDIT,		//单位
								CANNOT_EDIT,		//数据类型
								CANNOT_EDIT,		//最大值
								CANNOT_EDIT,		//最小值
								NORMAL_EDIT,		//备注
							};
#endif
/////////////////////////////////////////////////////////////////////////////
// CPzk300NormalCfgView message handlers

void CPzk300NormalCfgView::OnInitialUpdate()
{
	int i = 0;
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	mMenu.LoadMenu(IDR_MENU_EDIT_300);
	CFont *pfont = new CFont();
	pfont->CreateFont(13, 0, 0, 0,
         FW_NORMAL | FW_BOLD, FALSE, FALSE,
         FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
         DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, "宋体");
	bCurViewIsActive = true;
//	mNumberEdit.SubclassDlgItem(IDC_EDIT2, this);
	mFloatEdit.SubclassDlgItem(IDC_EDIT3,this);
	m_Edit1.SetFont(pfont);
	m_Edit2.SetFont(pfont);
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT3);
	pEdit->SetFont(pfont);
	m_Combo1.SetFont(pfont);
	CComboBox *pCombo = (CComboBox *)GetDlgItem(IDC_COMBO1);
	for(i=0; i<sizeof(DataTypes)/sizeof(CString); i++)
		pCombo->AddString(DataTypes[i]);
	m_List.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	CSize sz;
	sz.cx = sz.cy = 30;
	m_List.ApproximateViewRect(sz,1);
	m_List.InsertColumn(i++, "序号", LVCFMT_LEFT, 50, -1);
	m_List.InsertColumn(i++, "名称", LVCFMT_LEFT, 150, -1);
#ifdef __SUPERMODE
	m_List.InsertColumn(i++, "常量定义", LVCFMT_LEFT, 150, -1);
#endif
	m_List.InsertColumn(i++, "定值", LVCFMT_LEFT, 100, -1);
	m_List.InsertColumn(i++, "单位", LVCFMT_LEFT, 60, -1);
	m_List.InsertColumn(i++, "数据类型", LVCFMT_LEFT, 100, -1);
	m_List.InsertColumn(i++, "最大值", LVCFMT_LEFT, 80, -1);
	m_List.InsertColumn(i++, "最小值", LVCFMT_LEFT, 80, -1);
	m_List.InsertColumn(i++, "备注", LVCFMT_LEFT, 150, -1);

	LoadData();
}

CString CPzk300NormalCfgView::GetUnionValue(Pzk300UnionStru val, int datatype)
{
	CString str = "";
	switch(datatype)
	{
	case NO_TYPE:
		break;
	case INT_TYPE:
		str = Str(val.SetInt);//.Format("%d", val.SetInt);
		break;
	case FLOAT_TYPE:
		str = Str(val.SetFloat);//.Format("%f", val.SetFloat);
		break;
	case STR_TYPE:
		str = Str(val.SetStr);//.Format("%s", val.SetStr);
		break;
	default:
		break;
	}
	return str;
}

#ifdef __VAL_TYPE1
CString GetUnionValue1(Pzk300UnionStru val, int datatype, int rate)
{
	CString str = "";
	switch(datatype)
	{
	case NO_TYPE:
		break;
	case INT_TYPE:
		str = Str(val.SetInt / rate);//.Format("%d", val.SetInt / rate);
		break;
	case FLOAT_TYPE:
		str = Str(val.SetFloat / rate);//.Format("%0.2f", val.SetFloat / rate);
		break;
	case STR_TYPE:
		str.Format("%s", val.SetStr);
		break;
	default:
		break;
	}
	return str;
}
#endif
void CPzk300NormalCfgView::LoadData()
{
	int i,j;
	Pzk300CfgStruct val;
	m_List.DeleteAllItems();
	int rate = 1;
	for (i=0; i<mPzkIni.mPzk300NormalCfg.num; i++)
	{
		j = 1;
		val = mPzkIni.mPzk300NormalCfg.NormalCfg[i];
		m_List.InsertItem(i, Str(i),NULL);
		m_List.SetItemText(i, j++, val.ChinaName);
#ifdef __SUPERMODE
		m_List.SetItemText(i, j++, val.SetInputName);
#endif
		if(i == 8)
			rate = 10;
		else if(i == 9)
			rate = 100;
		else
			rate = 1;
#ifdef __VAL_TYPE1
		m_List.SetItemText(i, j++, GetUnionValue1(val.SetInputValue, val.SetInputDataStyle,rate));
#else
		m_List.SetItemText(i, j++, GetUnionValue(val.SetInputValue, val.SetInputDataStyle));
#endif
		m_List.SetItemText(i, j++, val.SetInputDataUnit);
		m_List.SetItemText(i, j++, DataTypes[val.SetInputDataStyle]);
#ifdef __VAL_TYPE1
		m_List.SetItemText(i, j++, GetUnionValue1(val.SetInputDataHLimit, val.SetInputDataStyle, rate));
#else
		m_List.SetItemText(i, j++, GetUnionValue(val.SetInputDataHLimit, val.SetInputDataStyle));
#endif
#ifdef __VAL_TYPE1
		m_List.SetItemText(i, j++, GetUnionValue1(val.SetInputDataLLimit, val.SetInputDataStyle, rate));
#else
		m_List.SetItemText(i, j++, GetUnionValue(val.SetInputDataLLimit, val.SetInputDataStyle));
#endif
		m_List.SetItemText(i, j++, val.Remark);
	}
}

void CPzk300NormalCfgView::OnSize(UINT nType, int cx, int cy)
{
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
	TRACE(Str(rect.bottom)+"\n");
	m_List.MoveWindow(&rect,TRUE);

	m_BN1.GetClientRect(&rect1);
	rect1.top = rect.bottom + 20;
	rect1.bottom = rect1.top + 28;
	rect1.left = rect.left + mWidth/2 - 200;
	rect1.right = rect1.left + 100;
	m_BN1.MoveWindow(&rect1,TRUE);

	m_BN2.GetClientRect(&rect1);
	rect1.top = rect.bottom + 20;
	rect1.bottom = rect1.top + 28;
	rect1.left = rect.left + mWidth/2 + 100;
	rect1.right = rect1.left + 100;
	m_BN2.MoveWindow(&rect1,TRUE);
}

int CPzk300NormalCfgView::GetDataTypeFromText(CString str)
{
	int i = 0;
	for(i=0; i<(sizeof(DataTypes)/sizeof(CString)); i++)
	{
		if(str.Compare(DataTypes[i]) == 0)
			break;
	}
	return i;
}

void CPzk300NormalCfgView::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
//	CEqTypeDlg mEqTypeDlg;
//	CCtrlWordDlg mCtrlWordDlg;
	int i;
	CEdit *pEdit;
	CComboBox *pCombo;
	CString str;

	Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST1);
    LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
    RECT rect;
	HWND pWnd;
    //get the row number
    nItem = temp->iItem;
    //get the column number
    nSubItem = temp->iSubItem;
	if(nItem < 0)
		return;
	str = m_List.GetItemText(nItem ,nSubItem);
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
		switch(GetDataTypeFromText(m_List.GetItemText(nItem, COL_VTYPE)))
		{
		case INT_TYPE:
			pWnd = ::GetDlgItem(m_hWnd, IDC_EDIT2);
			break;
		case FLOAT_TYPE:
			pWnd = ::GetDlgItem(m_hWnd, IDC_EDIT3);
			break;
		case NO_TYPE:
		case STR_TYPE:
		default:
			pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT1);
			break;
		}
		::SetWindowText(pWnd,str);
		break;
	case NORMAL_COMBO:
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO1);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO1);
		str = m_List.GetItemText(nItem, nSubItem);
		for(i=0; i<(sizeof(DataTypes)/sizeof(CString)); i++)
		{
			if(str.Compare(DataTypes[i]) == 0)
				break;
		}
		pCombo->SetCurSel(i);
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
		rect.right-rect.left,// - 3,
		rect.bottom-rect.top, NULL);
	::ShowWindow(pWnd,SW_SHOW);
	::SetFocus(pWnd);
	//Draw a Rectangle around the SubItem
	if(nSubItem != COL_VTYPE)
	{
//		::Rectangle(::GetDC(temp->hdr.hwndFrom),rect.left,rect.top-1,rect.right+2,rect.bottom-1);
//		::SetWindowText(pWnd,str);
	}
/*	else
	{
		if(str.Compare("True") == 0)
			m_Combo.SetCurSel(0);
		else
			m_Combo.SetCurSel(1);
	}
*/
	*pResult = 0;
}

void CPzk300NormalCfgView::OnKillfocusEdit1()
{
	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
	CString str;
	m_Edit1.GetWindowText(str);
	m_List.SetItemText(nItem,nSubItem,str);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT1),SW_HIDE);
	if(m_Edit1.GetModify() == TRUE)
		bEverEdited = true;
}

void CPzk300NormalCfgView::OnKillfocusEdit2()
{
	// TODO: Add your control notification handler code here
	CString str;
	CString showStr = "";
	int CurValue = myatoi(m_List.GetItemText(nItem, COL_VALUE));
	int HLimitValue = myatoi(m_List.GetItemText(nItem, COL_VMAX));
	int LLimitValue = myatoi(m_List.GetItemText(nItem, COL_VMIN));

	m_Edit2.GetWindowText(str);
	if(str.GetLength() == 0)
		str = "0";

	if(nSubItem == COL_VALUE)				//修改实际值
	{
		CurValue = myatoi(str);
		if(	(HLimitValue == 0) && (LLimitValue == 0) )
			goto PutIntToList;
		if(CurValue > HLimitValue)
		{
			showStr.Format("不能超过最大值%d",HLimitValue);
			str = Str(HLimitValue);
			bEverEdited = true;
		}
		else if(CurValue < LLimitValue)
		{
			showStr.Format("不能超过最小值%d",LLimitValue);
			str = Str(LLimitValue);
			bEverEdited = true;
		}
	}
	else if(nSubItem == COL_VMAX)			//修改最大值
	{
		HLimitValue = myatoi(str);
		if(	(HLimitValue == 0) && (LLimitValue == 0) )
			goto PutIntToList;
		if(HLimitValue < CurValue)
		{
			showStr.Format("最大值不能小于当前值%d", CurValue);
			str = Str(CurValue);
			bEverEdited = true;
		}
		else if(HLimitValue < LLimitValue)
		{
			showStr.Format("最大值不能小于最小值%d", LLimitValue);
			str = Str(LLimitValue);
			bEverEdited = true;
		}
	}
	else if(nSubItem == COL_VMIN)			//修改最小值
	{
		LLimitValue = myatoi(str);
		if(	(HLimitValue == 0) && (LLimitValue == 0) )
			goto PutIntToList;
		if(LLimitValue > CurValue)
		{
			showStr.Format("最大值不能大于当前值%d", CurValue);
			str = Str(CurValue);
			bEverEdited = true;
		}
		else if(LLimitValue > HLimitValue)
		{
			showStr.Format("最小值不能大于最大值%d", HLimitValue);
			str = Str(HLimitValue);
			bEverEdited = true;
		}
	}
PutIntToList:
	m_List.SetItemText(nItem,nSubItem,str);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT2),SW_HIDE);
	if(!showStr.IsEmpty())
		AfxMessageBox(showStr);

	this->PostMessage(WM_LBUTTONUP,NULL,NULL);
	if(m_Edit2.GetModify() == TRUE)
		bEverEdited = true;
}

void CPzk300NormalCfgView::OnKillfocusEdit3()
{
	// TODO: Add your control notification handler code here
	CString str;
	CString showStr = "";
//	str = m_List.GetItemText(nItem, COL_VALUE);
	float CurValue = (float)atof(m_List.GetItemText(nItem, COL_VALUE));
	float HLimitValue = (float)atof(m_List.GetItemText(nItem, COL_VMAX));
	float LLimitValue = (float)atof(m_List.GetItemText(nItem, COL_VMIN));

	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT3);
	pEdit->GetWindowText(str);
	if(str.GetLength() == 0)
		str = "0";

	if(nSubItem == COL_VALUE)					//修改定值
	{
		CurValue = (float)atof(str);
		if(	(HLimitValue == 0) && (LLimitValue == 0) )
			goto PutIntToList;

		if((CurValue - 0.0000001) > HLimitValue)
		{
			showStr.Format("不能超过最大值%f", HLimitValue);
			str = Str(HLimitValue);
			bEverEdited = true;
		}
		else if((CurValue + 0.0000001) < LLimitValue)
		{
			showStr.Format("不能小于最小值%f", LLimitValue);
			str = Str(LLimitValue);
			bEverEdited = true;
		}
	}
	else if(nSubItem == COL_VMAX)			//修改最大值
	{
		HLimitValue = (float)atof(str);
		if(	(HLimitValue == 0) && (LLimitValue == 0) )
			goto PutIntToList;

		if((HLimitValue + 0.0000001) < CurValue)
		{
			showStr.Format("最大值不能小于当前值%f", CurValue);
			str = Str(CurValue);
			bEverEdited = true;
		}
		else if((HLimitValue + 0.0000001) < LLimitValue)
		{
			showStr.Format("最大值不能小于最小值%f", LLimitValue);
			str = Str(LLimitValue);
			bEverEdited = true;
		}
	}
	else if(nSubItem == COL_VMIN)			//修改最小值
	{
		LLimitValue = (float)atof(str);
		if(	(HLimitValue == 0) && (LLimitValue == 0) )
			goto PutIntToList;

		if((LLimitValue - 0.0000001) > CurValue)
		{
			showStr.Format("最大值不能大于当前值%f", CurValue);
			str = Str(CurValue);
			bEverEdited = true;
		}
		else if((LLimitValue - 0.0000001) > HLimitValue)
		{
			showStr.Format("最小值不能大于最大值%f", HLimitValue);
			str = Str(HLimitValue);
			bEverEdited = true;
		}
	}
PutIntToList:
	m_List.SetItemText(nItem,nSubItem,str);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT3),SW_HIDE);
	if(!showStr.IsEmpty())
		AfxMessageBox(showStr);

	this->PostMessage(WM_LBUTTONUP,NULL,NULL);
	if(pEdit->GetModify() == TRUE)
		bEverEdited = true;
}

void CPzk300NormalCfgView::OnKillfocusCombo1()
{
	// TODO: Add your control notification handler code here
	int i = m_Combo1.GetCurSel();
	m_List.SetItemText(nItem,nSubItem,DataTypes[i]);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_COMBO1),SW_HIDE);
	bEverEdited = true;
}

#ifdef __VAL_TYPE1

void ReadUnionData1(Pzk300UnionStru *val, int datatype, CString KeyStr, int rate)
{
	switch(datatype)
	{
	case  NO_TYPE:
		strcpy((*val).SetStr,KeyStr.GetBuffer(KeyStr.GetLength()));
		break;
	case INT_TYPE:
		(*val).SetInt = myatoi(KeyStr) * rate;
		break;
	case FLOAT_TYPE:
		(*val).SetFloat = (float)atof(KeyStr) * rate;
		break;
	case STR_TYPE:
		strcpy((*val).SetStr,KeyStr.GetBuffer(KeyStr.GetLength()));
		break;
	default:
		strcpy((*val).SetStr,KeyStr.GetBuffer(KeyStr.GetLength()));
		break;
	}
}
#endif

void CPzk300NormalCfgView::OnSave()
{
	// TODO: Add your control notification handler code here
	CString str;
	int i;
	mPzkIni.mPzk300NormalCfg.num = m_List.GetItemCount();
	int rate = 1;
	if(mPzkIni.mPzk300NormalCfg.num > MAX_300_NORMAL_CFG)
	{
		str.Format("最大只允许配置%d个项目,所以只保存前%d项目",
					MAX_300_NORMAL_CFG,
					MAX_300_NORMAL_CFG);
		AfxMessageBox(str);
		mPzkIni.mPzk300NormalCfg.num = MAX_300_NORMAL_CFG;
	}

#ifdef __VAL_TYPE1
	for(i=0; i<mPzkIni.mPzk300NormalCfg.num; i++)
	{
		mPzkIni.mPzk300NormalCfg.NormalCfg[i].ChinaName = m_List.GetItemText(i, COL_NAME);
#ifdef __SUPERMODE
		mPzkIni.mPzk300NormalCfg.NormalCfg[i].SetInputName = m_List.GetItemText(i ,2);
#endif
		mPzkIni.mPzk300NormalCfg.NormalCfg[i].SetInputDataStyle = GetDataTypeFromText(m_List.GetItemText(i, COL_VTYPE));
		if(i==8)
			rate = 10;
		else if(i==9)
			rate = 100;
		else
			rate = 1;

		ReadUnionData1(&(mPzkIni.mPzk300NormalCfg.NormalCfg[i].SetInputValue),
						mPzkIni.mPzk300NormalCfg.NormalCfg[i].SetInputDataStyle,
						m_List.GetItemText(i, COL_VALUE),
						rate);

		ReadUnionData1(&(mPzkIni.mPzk300NormalCfg.NormalCfg[i].SetInputDataHLimit),
						mPzkIni.mPzk300NormalCfg.NormalCfg[i].SetInputDataStyle,
						m_List.GetItemText(i, COL_VMAX),
						rate);


		ReadUnionData1(&(mPzkIni.mPzk300NormalCfg.NormalCfg[i].SetInputDataLLimit),
						mPzkIni.mPzk300NormalCfg.NormalCfg[i].SetInputDataStyle,
						m_List.GetItemText(i, COL_VMIN),
						rate);

		mPzkIni.mPzk300NormalCfg.NormalCfg[i].Remark = m_List.GetItemText(i, COL_REMARK);
	}
#else
	for(i=0; i<mPzkIni.mPzk300NormalCfg.num; i++)
	{
		mPzkIni.mPzk300NormalCfg.NormalCfg[i].ChinaName = m_List.GetItemText(i, COL_NAME);
#ifdef __SUPERMODE
		mPzkIni.mPzk300NormalCfg.NormalCfg[i].SetInputName = m_List.GetItemText(i ,2);
#endif
		mPzkIni.mPzk300NormalCfg.NormalCfg[i].SetInputDataStyle = GetDataTypeFromText(m_List.GetItemText(i, COL_VTYPE));
		ReadUnionData(&(mPzkIni.mPzk300NormalCfg.NormalCfg[i].SetInputValue),
						mPzkIni.mPzk300NormalCfg.NormalCfg[i].SetInputDataStyle,
						m_List.GetItemText(i, COL_VALUE));
		mPzkIni.mPzk300NormalCfg.NormalCfg[i].SetInputDataUnit = m_List.GetItemText(i, 4);
		ReadUnionData(&(mPzkIni.mPzk300NormalCfg.NormalCfg[i].SetInputDataHLimit),
						mPzkIni.mPzk300NormalCfg.NormalCfg[i].SetInputDataStyle,
						m_List.GetItemText(i, COL_VMAX));
		ReadUnionData(&(mPzkIni.mPzk300NormalCfg.NormalCfg[i].SetInputDataLLimit),
						mPzkIni.mPzk300NormalCfg.NormalCfg[i].SetInputDataStyle,
						m_List.GetItemText(i, COL_VMIN));
		mPzkIni.mPzk300NormalCfg.NormalCfg[i].Remark = m_List.GetItemText(i, COL_REMARK);
	}
#endif
	bEverEdited = false;
	mPzkIni.EverModified = true;
}

void CPzk300NormalCfgView::OnCANCEl()
{
	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;
	LoadData();
	bEverEdited = false;
}

void CPzk300NormalCfgView::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult)
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

void CPzk300NormalCfgView::On300Add()
{
	// TODO: Add your command handler code here
	int mSelItem = m_List.GetItemCount();
	int i = 1;

	m_List.InsertItem(mSelItem, Str(mSelItem));
	m_List.SetItemText(mSelItem, i++, "");
#ifdef __SUPERMODE
	m_List.SetItemText(mSelItem, i++, "");
#endif
	m_List.SetItemText(mSelItem, i++, "0");
	m_List.SetItemText(mSelItem, i++, "无");
	m_List.SetItemText(mSelItem, i++, DataTypes[1]);
	m_List.SetItemText(mSelItem, i++, "0");
	m_List.SetItemText(mSelItem, i++, "0");
	m_List.SetItemText(mSelItem, i++, "备注");

	for(i=0; i<m_List.GetItemCount(); i++)
		m_List.SetItemText(i,0,Str(i));
	bEverEdited = true;
}

void CPzk300NormalCfgView::On300Remove()
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

void CPzk300NormalCfgView::On300Insert()
{
	// TODO: Add your command handler code here
	int mSelItem;
	int i = 1;
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if(!pos)
		mSelItem = m_List.GetItemCount();
	else
		mSelItem = m_List.GetSelectionMark();

	m_List.InsertItem(mSelItem, Str(mSelItem));
	m_List.SetItemText(mSelItem, i++, "");
#ifdef __SUPERMODE
	m_List.SetItemText(mSelItem, i++, "");
#endif
	m_List.SetItemText(mSelItem, i++, "0");
	m_List.SetItemText(mSelItem, i++, "无");
	m_List.SetItemText(mSelItem, i++, DataTypes[1]);
	m_List.SetItemText(mSelItem, i++, "0");
	m_List.SetItemText(mSelItem, i++, "0");
	m_List.SetItemText(mSelItem, i++, "备注");

	for(i=0; i<m_List.GetItemCount(); i++)
		m_List.SetItemText(i,0,Str(i));
	bEverEdited = true;
}

LRESULT CPzk300NormalCfgView::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)
{
//	OnCANCEl();
	return TRUE;
}

LRESULT CPzk300NormalCfgView::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)
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

BOOL CPzk300NormalCfgView::DestroyWindow()
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
