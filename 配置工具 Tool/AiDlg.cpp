// AiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "AiDlg.h"
#include "ReadPzkIni.h"
#include "MyFun.h"
#include "AiItemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern AiInputStru_ mAiItem;

extern bool bCloseWindow;
/////////////////////////////////////////////////////////////////////////////
// CAiDlg

IMPLEMENT_DYNCREATE(CAiDlg, CFormView)

CAiDlg::CAiDlg()
	: CFormView(CAiDlg::IDD)
{
	//{{AFX_DATA_INIT(CAiDlg)
	m_AiNum = 0;
	//}}AFX_DATA_INIT
}

CAiDlg::~CAiDlg()
{
}

void CAiDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAiDlg)
	DDX_Control(pDX, IDC_COMBO3, m_Combo3);
	DDX_Control(pDX, IDC_COMBO2, m_Combo2);
	DDX_Control(pDX, IDC_COMBO1, m_Combo1);
	DDX_Text(pDX, IDC_EDIT11, m_AiNum);
	DDV_MinMaxInt(pDX, m_AiNum, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAiDlg, CFormView)
	//{{AFX_MSG_MAP(CAiDlg)
	ON_WM_CREATE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_ADDITEM, OnAdditem)
	ON_BN_CLICKED(IDC_REMOVEITEM, OnRemoveitem)
	ON_BN_CLICKED(IDC_EDITITEM, OnEdititem)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_COMMAND(ID_ITEM_ADD, OnItemAdd)
	ON_COMMAND(ID_ITEM_EDIT, OnItemEdit)
	ON_COMMAND(ID_ITEM_REMOVE, OnItemRemove)
	ON_COMMAND(ID_ITEM_SAVE, OnItemSave)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, OnSelchangeCombo3)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_BN_CLICKED(IDREVERT, OnRevert)
	ON_COMMAND(ID_ITEM_CANCEL, OnItemCancel)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAiDlg diagnostics

#ifdef _DEBUG
void CAiDlg::AssertValid() const
{
	CFormView::AssertValid();
}

void CAiDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAiDlg message handlers
void CAiDlg::InsertItems()
{
	int i,j;
	CString str;
    HWND hWnd = ::GetDlgItem(m_hWnd, IDC_LIST1);

    // Set the LVCOLUMN structure with the required
    // column information
    LVCOLUMN list;
    list.mask =  LVCF_TEXT |LVCF_WIDTH|
        LVCF_FMT |LVCF_SUBITEM;
    list.fmt = LVCFMT_LEFT;

    list.cx = 50;
    list.pszText   = "No.";
    list.iSubItem = 0;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)0,(WPARAM)&list);

    list.cx = 110;
    list.pszText   = "名称";
    list.iSubItem = 1;
    //Inserts the column
    ::SendMessage(hWnd,LVM_INSERTCOLUMN,
        (WPARAM)1,(WPARAM)&list);

    list.cx = 80;
    list.pszText   = "有效标志";
    list.iSubItem = 2;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)2,(WPARAM)&list);

    list.cx = 100;
    list.pszText   = "线路号";
    list.iSubItem = 3;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)3,(WPARAM)&list);

    list.cx = 80;
    list.pszText   = "数据类型";
    list.iSubItem = 4;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)4,(WPARAM)&list);

	list.cx = 100;
    list.pszText   = "额定值";
    list.iSubItem = 5;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)5,(WPARAM)&list);

	list.cx = 100;
    list.pszText   = "输入最大值";
    list.iSubItem = 6;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)6,(WPARAM)&list);

	list.cx = 100;
    list.pszText   = "输入最小值";
    list.iSubItem = 7;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)7,(WPARAM)&list);

	list.cx = 100;
    list.pszText   = "关联线路号";
    list.iSubItem = 8;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)8,(WPARAM)&list);

	for(i=0;i<mPzkIni.mAiBuf.AiNum;i++)
		for(j=0;j<9;j++)
			switch(j)
			{
			case 0:
				SetCell(hWnd,Str(i),i,j);
				break;
			case 1:
				SetCell(hWnd,mPzkIni.mAiBuf.pAi[i].name,i,j);
				break;
			case 2:
				if(mPzkIni.mAiBuf.pAi[i].valid)
					SetCell(hWnd,"yes",i,j);
				else
					SetCell(hWnd,"no",i,j);
				break;
			case 3:
				SetCell(hWnd,Str(mPzkIni.mAiBuf.pAi[i].LineNum),i,j);
				break;
			case 4:
				switch(mPzkIni.mAiBuf.pAi[i].type)
				{
				case 1:
					SetCell(hWnd,"电流",i,j);
					break;
				case 2:
					SetCell(hWnd,"电压",i,j);
					break;
				case 3:
					SetCell(hWnd,"直流",i,j);
					break;
				default:
					SetCell(hWnd,"不确定类型",i,j);
				}
				break;
			case 5:
				str.Format("%f",mPzkIni.mAiBuf.pAi[i].rating);
				SetCell(hWnd,str,i,j);
				break;
			case 6:
				SetCell(hWnd,Str(mPzkIni.mAiBuf.pAi[i].MaxValue),i,j);
				break;
			case 7:
				SetCell(hWnd,Str(mPzkIni.mAiBuf.pAi[i].MinValue),i,j);
				break;
			case 8:
				SetCell(hWnd,Str(mPzkIni.mAiBuf.pAi[i].RelateLine),i,j);
			}

}

void CAiDlg::SetCell(HWND hWnd1,
        CString value, int nRow, int nCol)
{
    TCHAR     szString [256];
    wsprintf(szString,value ,0);

    //Fill the LVITEM structure with the
    //values given as parameters.
    LVITEM lvItem;
    lvItem.mask = LVIF_TEXT;
    lvItem.iItem = nRow;
    lvItem.pszText = szString;
    lvItem.iSubItem = nCol;
    if(nCol >0)
        //set the value of listItem
        ::SendMessage(hWnd1,LVM_SETITEM,
            (WPARAM)0,(WPARAM)&lvItem);
    else
        //Insert the value into List
        ListView_InsertItem(hWnd1,&lvItem);

}

CString CAiDlg::GetItemText(
    HWND hWnd, int nItem, int nSubItem) const
{
    LVITEM lvi;
    memset(&lvi, 0, sizeof(LVITEM));
    lvi.iSubItem = nSubItem;
    CString str;
    int nLen = 128;
    int nRes;
    do
    {
        nLen *= 2;
        lvi.cchTextMax = nLen;
        lvi.pszText = str.GetBufferSetLength(nLen);
        nRes  = (int)::SendMessage(hWnd,
            LVM_GETITEMTEXT, (WPARAM)nItem,
            (LPARAM)&lvi);
    } while (nRes == nLen-1);
    str.ReleaseBuffer();
    return str;
}

BOOL CAiDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

int CAiDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here
	/*
	m_Combo1.AddString("50");
	m_Combo1.AddString("60");

	m_Combo2.AddString("0-没有连接");
	m_Combo2.AddString("1-4线，Y 形，3元件");
	m_Combo2.AddString("2-4线，Y 形，2 1/2U元件");
	m_Combo2.AddString("3-4线，Y 形，2 1/2U元件，3I0");
	m_Combo2.AddString("4-4线，Y 形，2 1/2I元件");
	m_Combo2.AddString("5-3线，△形，2元件");
	m_Combo2.AddString("6-3线，△形，2 1/2I元件");
	m_Combo2.AddString("7-3线，△形，3元件");
	m_Combo2.AddString("8-3线，△形，2元件，3I0");
	m_Combo2.AddString("9-3线，△形，2元件，3I0，3U0");
	m_Combo2.AddString("10-3线，△形，2 1/2I元件，3U0");

	m_Combo3.AddString("ABC 正序");
	m_Combo3.AddString("ACB 负序");
*/
	return 0;
}

void CAiDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	mMenu.LoadMenu(IDR_ITEM_MENU);

	pAiList = (CListCtrl *)GetDlgItem(IDC_LIST1);
	pInEdit = (CEdit *)GetDlgItem(IDC_EDIT1);
	pInCombo = (CComboBox *)GetDlgItem(IDC_COMBO4);
	pInCombo->AddString("yes");
	pInCombo->AddString("no");
	if (mPzkIni.mIopCfg.Frequency == 50)
		m_Combo1.SetCurSel(0);
	else
		m_Combo1.SetCurSel(1);
	m_Combo2.SetCurSel(mPzkIni.mIopCfg.SequenceType);
	m_Combo3.SetCurSel(mPzkIni.mIopCfg.ConnectMode);

	m_AiNum = mPzkIni.mIopCfg.AnalogInputNum;
	UpdateData(FALSE);

	pAiList->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	InsertItems();
	bEverEdited = false;
	// TODO: Add your specialized code here and/or call the base class

}

void CAiDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST1);
    LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
	CListCtrl *pList;
	pList = (CListCtrl *)GetDlgItem(IDC_LIST1);

    //get the row number
    nItem = temp->iItem;
    //get the column number
    nSubItem = temp->iSubItem;

    if(nSubItem == -1 || nItem == -1)
	{
        return ;
	}

    CString str = GetItemText(hWnd1,nItem,1);
	mAiItem.name = str;
	str = GetItemText(hWnd1,nItem,2);
	if (str == "yes")
		mAiItem.valid = true;
	else
		mAiItem.valid = false;
	str = GetItemText(hWnd1,nItem,3);
	mAiItem.LineNum = atoi(str);
//	str = GetItemText(hWnd1,nItem,4);
//	mAiItem.type = atoi(str);
	str = GetItemText(hWnd1,nItem,4);
	if(str.Compare("电流") == 0)
		mAiItem.type = 1;
	else if(str.Compare("电压") == 0)
		mAiItem.type = 2;
	else if(str.Compare("直流") == 0)
		mAiItem.type = 3;
	else
		mAiItem.type = 0;
	str = GetItemText(hWnd1,nItem,5);
	mAiItem.rating = (float)atof(str);
	str = GetItemText(hWnd1,nItem,6);
	mAiItem.MaxValue = atoi(str);
	str = GetItemText(hWnd1,nItem,7);
	mAiItem.MinValue = atoi(str);
	str = GetItemText(hWnd1,nItem,8);
	mAiItem.RelateLine = atoi(str);

	CAiItemDlg tempdlg;
	if( tempdlg.DoModal() != TRUE)
		return;

	pList->SetItemText(nItem,1,mAiItem.name);
	if(mAiItem.valid)
		pList->SetItemText(nItem,2,"yes");
	else
		pList->SetItemText(nItem,2,"no");
	pList->SetItemText(nItem,3,Str(mAiItem.LineNum));
//	pList->SetItemText(nItem,4,Str(mAiItem.type));
	switch(mAiItem.type)
	{
	case 1:
		pList->SetItemText(nItem,4,"电流");
		break;
	case 2:
		pList->SetItemText(nItem,4,"电压");
		break;
	case 3:
		pList->SetItemText(nItem,4,"直流");
		break;
	default:
		pList->SetItemText(nItem,4,"不确定类型");
	}
	str.Format(_T("%f"),mAiItem.rating);
	pList->SetItemText(nItem,5,str);
	pList->SetItemText(nItem,6,Str(mAiItem.MaxValue));
	pList->SetItemText(nItem,7,Str(mAiItem.MinValue));
	pList->SetItemText(nItem,8,Str(mAiItem.RelateLine));
	bEverEdited = true;

	*pResult = 0;
}


void CAiDlg::OnAdditem()
{
	// TODO: Add your control notification handler code here
	int ItemNum;
	CListCtrl *pList;
	pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
	ItemNum = pList->GetItemCount();
	if (ItemNum >= mPzkIni.mAiBuf.AiMax)
	{
		MsgBox("已经达到Ai最大数量，不能继续添加");
		return;
	}

	mAiItem.name = "";
	mAiItem.valid = true;
	mAiItem.LineNum = 0;
	mAiItem.type = 1;
	mAiItem.rating = 0;
	mAiItem.MaxValue = 0;
	mAiItem.MinValue = 0;
	mAiItem.RelateLine = 0;

	CAiItemDlg tempdlg;
	if( tempdlg.DoModal() != TRUE)
		return;

	pList->InsertItem(ItemNum,Str(ItemNum),NULL);
	pList->SetItemText(ItemNum,1,mAiItem.name);
	if(mAiItem.valid)
		pList->SetItemText(ItemNum,2,"yes");
	else
		pList->SetItemText(ItemNum,2,"no");
	pList->SetItemText(ItemNum,3,Str(mAiItem.LineNum));
	//pList->SetItemText(ItemNum,4,Str(mAiItem.type));
	switch(mAiItem.type)
	{
	case 1:
		pList->SetItemText(ItemNum,4,"电流");
		break;
	case 2:
		pList->SetItemText(ItemNum,4,"电压");
		break;
	case 3:
		pList->SetItemText(ItemNum,4,"直流");
		break;
	default:
		pList->SetItemText(ItemNum,4,"不确定类型");
	}
	CString str;
	str.Format(_T("%f"),mAiItem.rating);
	pList->SetItemText(ItemNum,5,str);
	pList->SetItemText(ItemNum,6,Str(mAiItem.MaxValue));
	pList->SetItemText(ItemNum,7,Str(mAiItem.MinValue));
	pList->SetItemText(ItemNum,8,Str(mAiItem.RelateLine));

	m_AiNum += 1;
	UpdateData(FALSE);
	bEverEdited = true;
}

void CAiDlg::OnRemoveitem()
{
	// TODO: Add your control notification handler code here
	int ItemNo;
	int ItemNum;
	CListCtrl *pList;
	pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
/*
	ItemNo = pList->GetSelectionMark();
	if(ItemNo < 0)
		return;
	pList->DeleteItem(ItemNo);
*/
	POSITION pos = pList->GetFirstSelectedItemPosition();
	if(!pos)
		return;
	CString str,str1;
	str="你确定要删除Ai第";
	while (pos)
	{
	   ItemNo = pList->GetNextSelectedItem(pos);
	   str1.Format("%d",ItemNo);
//	   pList->DeleteItem(ItemNo);
//	   pos = pList->GetFirstSelectedItemPosition();
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

	m_AiNum = ItemNum;
	UpdateData(FALSE);
	bEverEdited = true;

	return;
}

void CAiDlg::OnEdititem()
{
	// TODO: Add your control notification handler code here
	CListCtrl *pList;
	pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
	nItem = pList->GetSelectionMark();
	POSITION pos;
	pos = pList->GetFirstSelectedItemPosition();
	if(!pos)
		return;

	HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST1);

    if(nItem == -1)
	{
        return ;
	}

    CString str = GetItemText(hWnd1,nItem,1);
	mAiItem.name = str;
	str = GetItemText(hWnd1,nItem,2);
	if (str == "yes")
		mAiItem.valid = true;
	else
		mAiItem.valid = false;
	str = GetItemText(hWnd1,nItem,3);
	mAiItem.LineNum = atoi(str);
	str = GetItemText(hWnd1,nItem,4);
	if(str.Compare("电流") == 0)
		mAiItem.type = 1;
	else if(str.Compare("电压") == 0)
		mAiItem.type = 2;
	else if(str.Compare("直流") == 0)
		mAiItem.type = 3;
	else
		mAiItem.type = 0;
	str = GetItemText(hWnd1,nItem,5);
	mAiItem.rating = (float)atof(str);
	str = GetItemText(hWnd1,nItem,6);
	mAiItem.MaxValue = atoi(str);
	str = GetItemText(hWnd1,nItem,7);
	mAiItem.MinValue = atoi(str);
	str = GetItemText(hWnd1,nItem,8);
	mAiItem.RelateLine = atoi(str);

	CAiItemDlg tempdlg;
	if( tempdlg.DoModal() != TRUE)
		return;

	pList->SetItemText(nItem,1,mAiItem.name);
	if(mAiItem.valid)
		pList->SetItemText(nItem,2,"yes");
	else
		pList->SetItemText(nItem,2,"no");
	pList->SetItemText(nItem,3,Str(mAiItem.LineNum));
	//pList->SetItemText(nItem,4,Str(mAiItem.type));
	switch(mAiItem.type)
	{
	case 1:
		pList->SetItemText(nItem,4,"电流");
		break;
	case 2:
		pList->SetItemText(nItem,4,"电压");
		break;
	case 3:
		pList->SetItemText(nItem,4,"直流");
		break;
	default:
		pList->SetItemText(nItem,4,"不确定类型");
	}
	str.Format(_T("%f"),mAiItem.rating);
	pList->SetItemText(nItem,5,str);
	pList->SetItemText(nItem,6,Str(mAiItem.MaxValue));
	pList->SetItemText(nItem,7,Str(mAiItem.MinValue));
	pList->SetItemText(nItem,8,Str(mAiItem.RelateLine));
	bEverEdited = true;

	return;
}

void CAiDlg::OnSave()
{
	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;
	CListCtrl *pList;
	CString str;
	pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
	int ItemNum = pList->GetItemCount();

	HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST1);

	UpdateData(TRUE);

	if(m_Combo1.GetCurSel() == 0)
		mPzkIni.mIopCfg.Frequency = 50;
	else
		mPzkIni.mIopCfg.Frequency = 60;
	mPzkIni.mIopCfg.SequenceType = m_Combo2.GetCurSel();
	mPzkIni.mIopCfg.ConnectMode = m_Combo3.GetCurSel();

	mPzkIni.mAiBuf.AiNum = m_AiNum;
	mPzkIni.mIopCfg.AnalogInputNum = m_AiNum;

	for(int i=0; i<mPzkIni.mAiBuf.AiMax; i++)
		mPzkIni.mAiBuf.pValid[i] = false;

	for(i=0; i<ItemNum ;i++)
	{
		mPzkIni.mAiBuf.pValid[i] = true;
		mPzkIni.mAiBuf.pAi[i].name = GetItemText(hWnd1,i,1);
		if(GetItemText(hWnd1,i,2) == "yes")
			mPzkIni.mAiBuf.pAi[i].valid = true;
		else
			mPzkIni.mAiBuf.pAi[i].valid = false;
		mPzkIni.mAiBuf.pAi[i].LineNum = atoi(GetItemText(hWnd1,i,3));
		//mPzkIni.mAiBuf.pAi[i].type = atoi(GetItemText(hWnd1,i,4));
		str = GetItemText(hWnd1,i,4);
		if(str.Compare("电流") == 0)
			mPzkIni.mAiBuf.pAi[i].type = 1;
		else if(str.Compare("电压") == 0)
			mPzkIni.mAiBuf.pAi[i].type = 2;
		else if(str.Compare("直流") == 0)
			mPzkIni.mAiBuf.pAi[i].type = 3;
		else
			mAiItem.type = 0;
		mPzkIni.mAiBuf.pAi[i].rating = (float)atof(GetItemText(hWnd1,i,5));
		mPzkIni.mAiBuf.pAi[i].MaxValue = atoi(GetItemText(hWnd1,i,6));
		mPzkIni.mAiBuf.pAi[i].MinValue = atoi(GetItemText(hWnd1,i,7));
		mPzkIni.mAiBuf.pAi[i].RelateLine = atoi(GetItemText(hWnd1,i,8));
	}
	bEverEdited = false;
	mPzkIni.EverModified = true;
}

void CAiDlg::OnItemAdd()
{
	// TODO: Add your command handler code here
	OnAdditem();
}

void CAiDlg::OnItemEdit()
{
	// TODO: Add your command handler code here
	OnEdititem();
}

void CAiDlg::OnItemRemove()
{
	// TODO: Add your command handler code here
	OnRemoveitem();
}

void CAiDlg::OnItemSave()
{
	// TODO: Add your command handler code here
	OnSave();
}

void CAiDlg::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CPoint oPoint;//定义一个用于确定光标位置的位置
    GetCursorPos( &oPoint);//
	CMenu *hMenu;
	hMenu = mMenu.GetSubMenu(0);
	hMenu->TrackPopupMenu(TPM_LEFTALIGN,oPoint.x,oPoint.y,this,0);
	*pResult = 0;
}

BOOL CAiDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	int i;
	try
	{
		if(bEverEdited)
		{
			i = AfxMessageBox("您已经修改了交流输入量配置，在退出该配置前确定要保存吗？",MB_YESNOCANCEL);
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

	catch(CException e)
	{
		throw;
	}

}

void CAiDlg::OnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CAiDlg::OnSelchangeCombo2()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CAiDlg::OnSelchangeCombo3()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CAiDlg::OnFileSave()
{
	// TODO: Add your command handler code here
	OnSave();
}

LRESULT CAiDlg::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)
{
	if(bEverEdited)
	{
		int i = AfxMessageBox("保存当前对交流输入量配置所做的修改吗？",MB_YESNOCANCEL);
		if(i == IDYES)
			OnSave();
		else if(i == IDCANCEL)
		{
//			bCloseWindow = false;
			return FALSE;
		}
		else
			OnRevert();
	}
	bEverEdited = false;
	return TRUE;
}

void CAiDlg::OnRevert()
{
	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;

	pAiList = (CListCtrl *)GetDlgItem(IDC_LIST1);
    HWND hWnd = ::GetDlgItem(m_hWnd, IDC_LIST1);
	if (mPzkIni.mIopCfg.Frequency == 50)
		m_Combo1.SetCurSel(0);
	else
		m_Combo1.SetCurSel(1);
	m_Combo2.SetCurSel(mPzkIni.mIopCfg.SequenceType);
	m_Combo3.SetCurSel(mPzkIni.mIopCfg.ConnectMode);

	m_AiNum = mPzkIni.mIopCfg.AnalogInputNum;
	UpdateData(FALSE);

	CString str;
	pAiList->DeleteAllItems();
	for(int i=0;i<mPzkIni.mAiBuf.AiNum;i++)
		for(int j=0;j<9;j++)
			switch(j)
			{
			case 0:
				SetCell(hWnd,Str(i),i,j);
				break;
			case 1:
				SetCell(hWnd,mPzkIni.mAiBuf.pAi[i].name,i,j);
				break;
			case 2:
				if(mPzkIni.mAiBuf.pAi[i].valid)
					SetCell(hWnd,"yes",i,j);
				else
					SetCell(hWnd,"no",i,j);
				break;
			case 3:
				SetCell(hWnd,Str(mPzkIni.mAiBuf.pAi[i].LineNum),i,j);
				break;
			case 4:
				switch(mPzkIni.mAiBuf.pAi[i].type)
				{
				case 1:
					SetCell(hWnd,"电流",i,j);
					break;
				case 2:
					SetCell(hWnd,"电压",i,j);
					break;
				case 3:
					SetCell(hWnd,"直流",i,j);
					break;
				default:
					SetCell(hWnd,"不确定类型",i,j);
				}
				//SetCell(hWnd,Str(mPzkIni.mAiBuf.pAi[i].type),i,j);
				break;
			case 5:
				str.Format("%f",mPzkIni.mAiBuf.pAi[i].rating);
				SetCell(hWnd,str,i,j);
				break;
			case 6:
				SetCell(hWnd,Str(mPzkIni.mAiBuf.pAi[i].MaxValue),i,j);
				break;
			case 7:
				SetCell(hWnd,Str(mPzkIni.mAiBuf.pAi[i].MinValue),i,j);
				break;
			case 8:
				SetCell(hWnd,Str(mPzkIni.mAiBuf.pAi[i].RelateLine),i,j);
			}
	bEverEdited = false;
}

LRESULT CAiDlg::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)
{
	OnRevert();
	return TRUE;
}

void CAiDlg::OnItemCancel()
{
	// TODO: Add your command handler code here
	OnRevert();
}
