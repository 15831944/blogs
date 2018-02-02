// FltDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "FltDlg.h"
#include "ReadPzkIni.h"
#include "MyFun.h"
#include "FltItemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern FltStru_ mFltItem;
extern bool bCloseWindow;
/////////////////////////////////////////////////////////////////////////////
// CFltDlg

IMPLEMENT_DYNCREATE(CFltDlg, CFormView)

CFltDlg::CFltDlg()
	: CFormView(CFltDlg::IDD)
{
	//{{AFX_DATA_INIT(CFltDlg)
	m_Edit1 = 0;
	//}}AFX_DATA_INIT
}

CFltDlg::~CFltDlg()
{
}

void CFltDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFltDlg)
	DDX_Control(pDX, IDC_LIST1, m_FltList);
	DDX_Text(pDX, IDC_EDIT1, m_Edit1);
	DDV_MinMaxInt(pDX, m_Edit1, 0, 4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFltDlg, CFormView)
	//{{AFX_MSG_MAP(CFltDlg)
	ON_BN_CLICKED(IDC_ADDITEM, OnAdditem)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_REMOVEITEM, OnRemoveitem)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
	ON_COMMAND(ID_ITEM_ADD, OnItemAdd)
	ON_COMMAND(ID_ITEM_EDIT, OnItemEdit)
	ON_COMMAND(ID_ITEM_REMOVE, OnItemRemove)
	ON_COMMAND(ID_ITEM_SAVE, OnItemSave)
	ON_BN_CLICKED(IDREVERT, OnRevert)
	ON_COMMAND(ID_ITEM_CANCEL, OnItemCancel)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFltDlg diagnostics

#ifdef _DEBUG
void CFltDlg::AssertValid() const
{
	CFormView::AssertValid();
}

void CFltDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFltDlg message handlers
void CFltDlg::InsertItems()
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

    list.cx = 100;
    list.pszText   = "故障名称";
    list.iSubItem = 1;
    //Inserts the column
    ::SendMessage(hWnd,LVM_INSERTCOLUMN,
        (WPARAM)1,(WPARAM)&list);

    list.cx = 70;
    list.pszText   = "故障索引";
    list.iSubItem = 2;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)2,(WPARAM)&list);

    list.cx = 120;
    list.pszText   = "相电流监测投退";
    list.iSubItem = 3;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)3,(WPARAM)&list);

    list.cx = 150;
    list.pszText   = "零序电流监测投退";
    list.iSubItem = 4;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)4,(WPARAM)&list);

	list.cx = 100;
    list.pszText   = "相电流定值";
    list.iSubItem = 5;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)5,(WPARAM)&list);

	list.cx = 100;
    list.pszText   = "零序电流定值";
    list.iSubItem = 6;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)6,(WPARAM)&list);

	list.cx = 150;
    list.pszText   = "正序电阻";
    list.iSubItem = 7;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)7,(WPARAM)&list);

	list.cx = 150;
    list.pszText   = "正序电抗";
    list.iSubItem = 8;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)8,(WPARAM)&list);

	list.cx = 120;
    list.pszText   = "零序电阻";
    list.iSubItem = 9;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)9,(WPARAM)&list);

	list.cx = 120;
    list.pszText   = "零序电抗";
    list.iSubItem = 9;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)9,(WPARAM)&list);

	for(i=0;i<mPzkIni.mFltBuf.FltNum;i++)
		for(j=0;j<11;j++)
			switch(j)
			{
			case 0:
				SetCell(hWnd,Str(i),i,j);
				break;
			case 1:
				SetCell(hWnd,mPzkIni.mFltBuf.pFlt[i].Name,i,j);
				break;
			case 2:
				SetCell(hWnd,Str(mPzkIni.mFltBuf.pFlt[i].FaultId),i,j);
				break;
			case 3:
				if(mPzkIni.mFltBuf.pFlt[i].bIpFaultEnable)
					SetCell(hWnd,"yes",i,j);
				else
					SetCell(hWnd,"no",i,j);
				break;
			case 4:
				if(mPzkIni.mFltBuf.pFlt[i].b3I0FaultEnable)
					SetCell(hWnd,"yes",i,j);
				else
					SetCell(hWnd,"no",i,j);
				break;
			case 5:
				SetCell(hWnd,Str(mPzkIni.mFltBuf.pFlt[i].IpValue),i,j);
				break;
			case 6:
				SetCell(hWnd,Str(mPzkIni.mFltBuf.pFlt[i].m3I0Value),i,j);
				break;
			case 7:
				SetCell(hWnd,Str(mPzkIni.mFltBuf.pFlt[i].PositiveResistance),i,j);
				break;
			case 8:
				SetCell(hWnd,Str(mPzkIni.mFltBuf.pFlt[i].PositiveReactance),i,j);
				break;
			case 9:
				SetCell(hWnd,Str(mPzkIni.mFltBuf.pFlt[i].ZeroResistance),i,j);
				break;
			case 10:
				//xMessageBox(Str(mPzkIni.mFltBuf.pFlt[i].ZeroReactance));
				SetCell(hWnd,Str(mPzkIni.mFltBuf.pFlt[i].ZeroReactance),i,j);
				break;
			}
}

void CFltDlg::SetCell(HWND hWnd1,
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

CString CFltDlg::GetItemText(
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

void CFltDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	m_Edit1 = mPzkIni.mFltBuf.FltNum;
	UpdateData(FALSE);

	mMenu.LoadMenu(IDR_ITEM_MENU);
	m_FltList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	InsertItems();
	bEverEdited = false;
}

void CFltDlg::OnAdditem()
{
	// TODO: Add your control notification handler code here
	CListCtrl *pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
	if(m_Edit1 >= mPzkIni.mFltBuf.FltMax)
	{
		MsgBox("已经达到故障最大个数，不能继续添加!");
		return;
	}

	mFltItem.Name = "";
	mFltItem.FaultId = 0;
	mFltItem.bIpFaultEnable = true;
	mFltItem.b3I0FaultEnable = true;
	mFltItem.IpValue = 0;
	mFltItem.m3I0Value = 0;
	mFltItem.PositiveResistance = 0;
	mFltItem.PositiveReactance = 0;
	mFltItem.ZeroResistance = 0;
	mFltItem.ZeroReactance = 0;

	CFltItemDlg tempdlg;
	if(tempdlg.DoModal() != TRUE)
		return;

	int ItemNum = pList->GetItemCount();
	pList->InsertItem(ItemNum,Str(ItemNum));
	pList->SetItemText(ItemNum,1,mFltItem.Name);
	pList->SetItemText(ItemNum,2,Str(mFltItem.FaultId));
	if (mFltItem.bIpFaultEnable)
		pList->SetItemText(ItemNum,3,"yes");
	else
		pList->SetItemText(ItemNum,3,"no");
	if (mFltItem.b3I0FaultEnable)
		pList->SetItemText(ItemNum,4,"yes");
	else
		pList->SetItemText(ItemNum,4,"no");
	pList->SetItemText(ItemNum,5,Str(mFltItem.IpValue));
	pList->SetItemText(ItemNum,6,Str(mFltItem.m3I0Value));
	pList->SetItemText(ItemNum,7,Str(mFltItem.PositiveResistance));
	pList->SetItemText(ItemNum,8,Str(mFltItem.PositiveReactance));
	pList->SetItemText(ItemNum,9,Str(mFltItem.ZeroResistance));
	pList->SetItemText(ItemNum,10,Str(mFltItem.ZeroReactance));

	m_Edit1 += 1;
	UpdateData(FALSE);
	bEverEdited = true;
}

void CFltDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST1);
    LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
	CListCtrl *pList = (CListCtrl *)GetDlgItem(IDC_LIST1);

    //get the row number
    nItem = temp->iItem;
    //get the column number
    nSubItem = temp->iSubItem;

    if(nSubItem == -1 || nItem == -1)
	{
        return ;
	}

	mFltItem.Name = GetItemText(hWnd1,nItem,1);
	mFltItem.FaultId = atoi(GetItemText(hWnd1,nItem,2));
	if(GetItemText(hWnd1,nItem,3) == "yes")
		mFltItem.bIpFaultEnable = true;
	else
		mFltItem.bIpFaultEnable = false;
	if(GetItemText(hWnd1,nItem,4) == "yes")
		mFltItem.b3I0FaultEnable = true;
	else
		mFltItem.b3I0FaultEnable = false;
	mFltItem.IpValue = atoi(GetItemText(hWnd1,nItem,5));
	mFltItem.m3I0Value = atoi(GetItemText(hWnd1,nItem,6));
	mFltItem.PositiveResistance = atoi(GetItemText(hWnd1,nItem,7));
	mFltItem.PositiveReactance = atoi(GetItemText(hWnd1,nItem,8));
	mFltItem.ZeroResistance = atoi(GetItemText(hWnd1,nItem,9));
	mFltItem.ZeroReactance = atoi(GetItemText(hWnd1,nItem,10));

	CFltItemDlg tempdlg;
	if(tempdlg.DoModal() != TRUE)
		return;

	pList->SetItemText(nItem,1,mFltItem.Name);
	pList->SetItemText(nItem,2,Str(mFltItem.FaultId));
	if (mFltItem.bIpFaultEnable)
		pList->SetItemText(nItem,3,"yes");
	else
		pList->SetItemText(nItem,3,"no");
	if (mFltItem.b3I0FaultEnable)
		pList->SetItemText(nItem,4,"yes");
	else
		pList->SetItemText(nItem,4,"no");
	pList->SetItemText(nItem,5,Str(mFltItem.IpValue));
	pList->SetItemText(nItem,6,Str(mFltItem.m3I0Value));
	pList->SetItemText(nItem,7,Str(mFltItem.PositiveResistance));
	pList->SetItemText(nItem,8,Str(mFltItem.PositiveReactance));
	pList->SetItemText(nItem,9,Str(mFltItem.ZeroResistance));
	pList->SetItemText(nItem,10,Str(mFltItem.ZeroReactance));

	bEverEdited = true;
	*pResult = 0;
}

void CFltDlg::OnRemoveitem()
{
	// TODO: Add your control notification handler code here
	int ItemNo;
	int ItemNum;
	CListCtrl *pList;
	POSITION pos;
	pList = (CListCtrl *)GetDlgItem(IDC_LIST1);

	pos = pList->GetFirstSelectedItemPosition();
	if(!pos)
		return;

	CString str,str1;
	str="你确定要删除Fault第";
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

	m_Edit1 = ItemNum;
	UpdateData(FALSE);
	bEverEdited = true;

}

void CFltDlg::OnEdit()
{
	// TODO: Add your control notification handler code here
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST1);
	CListCtrl *pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
	POSITION pos;
	pos = pList->GetFirstSelectedItemPosition();
	if(!pos)
		return;

    //get the row number
    nItem = pList->GetSelectionMark();

    if(nItem == -1)
	{
        return ;
	}

	mFltItem.Name = GetItemText(hWnd1,nItem,1);
	mFltItem.FaultId = atoi(GetItemText(hWnd1,nItem,2));
	if(GetItemText(hWnd1,nItem,3) == "yes")
		mFltItem.bIpFaultEnable = true;
	else
		mFltItem.bIpFaultEnable = false;
	if(GetItemText(hWnd1,nItem,4) == "yes")
		mFltItem.b3I0FaultEnable = true;
	else
		mFltItem.b3I0FaultEnable = false;
	mFltItem.IpValue = atoi(GetItemText(hWnd1,nItem,5));
	mFltItem.m3I0Value = atoi(GetItemText(hWnd1,nItem,6));
	mFltItem.PositiveResistance = atoi(GetItemText(hWnd1,nItem,7));
	mFltItem.PositiveReactance = atoi(GetItemText(hWnd1,nItem,8));
	mFltItem.ZeroResistance = atoi(GetItemText(hWnd1,nItem,9));
	mFltItem.ZeroReactance = atoi(GetItemText(hWnd1,nItem,10));

	CFltItemDlg tempdlg;
	if(tempdlg.DoModal() != TRUE)
		return;

	pList->SetItemText(nItem,1,mFltItem.Name);
	pList->SetItemText(nItem,2,Str(mFltItem.FaultId));
	if (mFltItem.bIpFaultEnable)
		pList->SetItemText(nItem,3,"yes");
	else
		pList->SetItemText(nItem,3,"no");
	if (mFltItem.b3I0FaultEnable)
		pList->SetItemText(nItem,4,"yes");
	else
		pList->SetItemText(nItem,4,"no");
	pList->SetItemText(nItem,5,Str(mFltItem.IpValue));
	pList->SetItemText(nItem,6,Str(mFltItem.m3I0Value));
	pList->SetItemText(nItem,7,Str(mFltItem.PositiveResistance));
	pList->SetItemText(nItem,8,Str(mFltItem.PositiveReactance));
	pList->SetItemText(nItem,9,Str(mFltItem.ZeroResistance));
	pList->SetItemText(nItem,10,Str(mFltItem.ZeroReactance));

	bEverEdited = true;
}

void CFltDlg::OnOK()
{
	// TODO: Add your control notification handler code here
	CListCtrl *pList;
	pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
	int ItemNum = pList->GetItemCount();

	HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST1);

	UpdateData(TRUE);
	mPzkIni.mFltBuf.FltNum = m_Edit1;
	for(int i=0; i<ItemNum ;i++)
	{
		mPzkIni.mFltBuf.pFlt[i].Name = GetItemText(hWnd1,i,1);
		mPzkIni.mFltBuf.pFlt[i].FaultId = atoi(GetItemText(hWnd1,i,2));
		if(GetItemText(hWnd1,i,3) == "yes")
			mPzkIni.mFltBuf.pFlt[i].bIpFaultEnable = true;
		else
			mPzkIni.mFltBuf.pFlt[i].bIpFaultEnable = false;
		if(GetItemText(hWnd1,i,4) == "yes")
		{

			mPzkIni.mFltBuf.pFlt[i].b3I0FaultEnable = true;
		}
		else
			mPzkIni.mFltBuf.pFlt[i].b3I0FaultEnable = false;
		mPzkIni.mFltBuf.pFlt[i].IpValue = atoi(GetItemText(hWnd1,i,5));
		mPzkIni.mFltBuf.pFlt[i].m3I0Value = atoi(GetItemText(hWnd1,i,6));
		mPzkIni.mFltBuf.pFlt[i].PositiveResistance = atoi(GetItemText(hWnd1,i,7));
		mPzkIni.mFltBuf.pFlt[i].PositiveReactance = atoi(GetItemText(hWnd1,i,8));
		mPzkIni.mFltBuf.pFlt[i].ZeroResistance = atoi(GetItemText(hWnd1,i,9));
		mPzkIni.mFltBuf.pFlt[i].ZeroReactance = atoi(GetItemText(hWnd1,i,10));
	}
	bEverEdited = false;
	mPzkIni.EverModified = true;
}

void CFltDlg::OnSave()
{
	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;
	CListCtrl *pList;
	pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
	int ItemNum = pList->GetItemCount();

	HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST1);

	UpdateData(TRUE);
	mPzkIni.mFltBuf.FltNum = m_Edit1;
	int i;
	for(i=0; i<mPzkIni.mFltBuf.FltMax; i++)
		mPzkIni.mFltBuf.pValid[i] = false;
	for(i=0; i<ItemNum ;i++)
	{
		mPzkIni.mFltBuf.pValid[i] = true;
		mPzkIni.mFltBuf.pFlt[i].Name = GetItemText(hWnd1,i,1);
		mPzkIni.mFltBuf.pFlt[i].FaultId = atoi(GetItemText(hWnd1,i,2));
		if(GetItemText(hWnd1,i,3) == "yes")
			mPzkIni.mFltBuf.pFlt[i].bIpFaultEnable = true;
		else
			mPzkIni.mFltBuf.pFlt[i].bIpFaultEnable = false;
		if(GetItemText(hWnd1,i,4) == "yes")
		{

			mPzkIni.mFltBuf.pFlt[i].b3I0FaultEnable = true;
		}
		else
			mPzkIni.mFltBuf.pFlt[i].b3I0FaultEnable = false;
		mPzkIni.mFltBuf.pFlt[i].IpValue = atoi(GetItemText(hWnd1,i,5));
		mPzkIni.mFltBuf.pFlt[i].m3I0Value = atoi(GetItemText(hWnd1,i,6));
		mPzkIni.mFltBuf.pFlt[i].PositiveResistance = atoi(GetItemText(hWnd1,i,7));
		mPzkIni.mFltBuf.pFlt[i].PositiveReactance = atoi(GetItemText(hWnd1,i,8));
		mPzkIni.mFltBuf.pFlt[i].ZeroResistance = atoi(GetItemText(hWnd1,i,9));
		mPzkIni.mFltBuf.pFlt[i].ZeroReactance = atoi(GetItemText(hWnd1,i,10));
	}
	bEverEdited = false;
	mPzkIni.EverModified = true;
}

void CFltDlg::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CPoint oPoint;//定义一个用于确定光标位置的位置
    GetCursorPos( &oPoint);//
	CMenu *hMenu;
	hMenu = mMenu.GetSubMenu(0);
	hMenu->TrackPopupMenu(TPM_LEFTALIGN,oPoint.x,oPoint.y,this,0);
	*pResult = 0;
}

void CFltDlg::OnItemAdd()
{
	// TODO: Add your command handler code here
	OnAdditem();
}

void CFltDlg::OnItemEdit()
{
	// TODO: Add your command handler code here
	OnEdit();
}

void CFltDlg::OnItemRemove()
{
	// TODO: Add your command handler code here
	OnRemoveitem();
}

void CFltDlg::OnItemSave()
{
	// TODO: Add your command handler code here
	OnSave();
}

BOOL CFltDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	int i;
	try
	{
		if(bEverEdited)
		{
			i = AfxMessageBox("您已经修改了故障参数配置，在退出该配置前确定要保存吗？",MB_YESNOCANCEL);
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

LRESULT CFltDlg::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)
{
	if(bEverEdited)
	{
		int i = AfxMessageBox("保存当前对故障参数配置所做的更改吗？",MB_YESNOCANCEL);
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

void CFltDlg::OnRevert()
{
	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;

	CListCtrl *pFltList = (CListCtrl *)GetDlgItem(IDC_LIST1);
	HWND hWnd = ::GetDlgItem(m_hWnd, IDC_LIST1);

	m_Edit1 = mPzkIni.mFltBuf.FltNum;
	UpdateData(FALSE);
	pFltList->DeleteAllItems();
	for(int i=0;i<mPzkIni.mFltBuf.FltNum;i++)
		for(int j=0;j<11;j++)
			switch(j)
			{
			case 0:
				SetCell(hWnd,Str(i),i,j);
				break;
			case 1:
				SetCell(hWnd,mPzkIni.mFltBuf.pFlt[i].Name,i,j);
				break;
			case 2:
				SetCell(hWnd,Str(mPzkIni.mFltBuf.pFlt[i].FaultId),i,j);
				break;
			case 3:
				if(mPzkIni.mFltBuf.pFlt[i].bIpFaultEnable)
					SetCell(hWnd,"yes",i,j);
				else
					SetCell(hWnd,"no",i,j);
				break;
			case 4:
				if(mPzkIni.mFltBuf.pFlt[i].b3I0FaultEnable)
					SetCell(hWnd,"yes",i,j);
				else
					SetCell(hWnd,"no",i,j);
				break;
			case 5:
				SetCell(hWnd,Str(mPzkIni.mFltBuf.pFlt[i].IpValue),i,j);
				break;
			case 6:
				SetCell(hWnd,Str(mPzkIni.mFltBuf.pFlt[i].m3I0Value),i,j);
				break;
			case 7:
				SetCell(hWnd,Str(mPzkIni.mFltBuf.pFlt[i].PositiveResistance),i,j);
				break;
			case 8:
				SetCell(hWnd,Str(mPzkIni.mFltBuf.pFlt[i].PositiveReactance),i,j);
				break;
			case 9:
				SetCell(hWnd,Str(mPzkIni.mFltBuf.pFlt[i].ZeroResistance),i,j);
				break;
			case 10:
				//xMessageBox(Str(mPzkIni.mFltBuf.pFlt[i].ZeroReactance));
				SetCell(hWnd,Str(mPzkIni.mFltBuf.pFlt[i].ZeroReactance),i,j);
				break;
			}
	bEverEdited = false;
}

LRESULT CFltDlg::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)
{
	OnRevert();
	return TRUE;
}

void CFltDlg::OnItemCancel()
{
	// TODO: Add your command handler code here
	OnRevert();
}
