// ProDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "ProDlg.h"
#include "ReadPzkIni.h"
#include "MyFun.h"
#include "ProItemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern ProStru_ mProItem;
extern bool bCloseWindow;
/////////////////////////////////////////////////////////////////////////////
// CProDlg

IMPLEMENT_DYNCREATE(CProDlg, CFormView)

CProDlg::CProDlg()
	: CFormView(CProDlg::IDD)
{
	//{{AFX_DATA_INIT(CProDlg)
	m_Edit1 = 0;
	//}}AFX_DATA_INIT
}

CProDlg::~CProDlg()
{
}

void CProDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProDlg)
	DDX_Control(pDX, IDC_LIST1, m_ProList);
	DDX_Text(pDX, IDC_EDIT1, m_Edit1);
	DDV_MinMaxInt(pDX, m_Edit1, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProDlg, CFormView)
	//{{AFX_MSG_MAP(CProDlg)
	ON_BN_CLICKED(IDC_ITEM_ADD, OnItemAdd)
	ON_BN_CLICKED(IDC_ITEM_REMOVE, OnItemRemove)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_ITEM_EDIT, OnItemEdit)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
	ON_COMMAND(ID_ITEM_SAVE, OnItemSave)
	ON_BN_CLICKED(IDREVERT, OnRevert)
	ON_COMMAND(ID_ITEM_ADD, OnItemAdd)
	ON_COMMAND(ID_ITEM_EDIT, OnItemEdit)
	ON_COMMAND(ID_ITEM_REMOVE, OnItemRemove)
	ON_COMMAND(ID_ITEM_CANCEL, OnItemCancel)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProDlg diagnostics
void CProDlg::InsertItems()
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
    list.pszText   = "保护名称";
    list.iSubItem = 1;
    //Inserts the column
    ::SendMessage(hWnd,LVM_INSERTCOLUMN,
        (WPARAM)1,(WPARAM)&list);

    list.cx = 100;
    list.pszText   = "保护索引";
    list.iSubItem = 2;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)2,(WPARAM)&list);

    list.cx = 100;
    list.pszText   = "保护投退";
    list.iSubItem = 3;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)3,(WPARAM)&list);

    list.cx = 100;
    list.pszText   = "保护定值";
    list.iSubItem = 4;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)4,(WPARAM)&list);

	list.cx = 100;
    list.pszText   = "保护延时";
    list.iSubItem = 5;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)5,(WPARAM)&list);

	list.cx = 100;
    list.pszText   = "杂项";
    list.iSubItem = 6;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)6,(WPARAM)&list);

	for(i=0;i<mPzkIni.mProBuf.ProNum ;i++)
		for(j=0;j<7;j++)
			switch(j)
			{
			case 0:
				SetCell(hWnd,Str(i),i,j);
				break;
			case 1:
				SetCell(hWnd,mPzkIni.mProBuf.pPro[i].Name,i,j);
				break;
			case 2:
				SetCell(hWnd,Str(mPzkIni.mProBuf.pPro[i].ProtectId),i,j);
				break;
			case 3:
				if(mPzkIni.mProBuf.pPro[i].Enable)
					SetCell(hWnd,"yes",i,j);
				else
					SetCell(hWnd,"no",i,j);
				break;
			case 4:
				SetCell(hWnd,Str(mPzkIni.mProBuf.pPro[i].Value),i,j);
				break;
			case 5:
				SetCell(hWnd,Str(mPzkIni.mProBuf.pPro[i].DelayTime),i,j);
				break;
			case 6:
				SetCell(hWnd,Str(mPzkIni.mProBuf.pPro[i].Misc),i,j);
				break;
			}

}

void CProDlg::SetCell(HWND hWnd1,
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

CString CProDlg::GetItemText(
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

#ifdef _DEBUG
void CProDlg::AssertValid() const
{
	CFormView::AssertValid();
}

void CProDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProDlg message handlers

void CProDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	m_Edit1 = mPzkIni.mProBuf.ProNum;
	UpdateData(FALSE);

	mMenu.LoadMenu(IDR_ITEM_MENU);
	m_ProList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	InsertItems();
	bEverEdited = false;
}

void CProDlg::OnItemAdd()
{
	// TODO: Add your control notification handler code here

	int ItemNum;
	CListCtrl *pList;
	pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
	ItemNum = pList->GetItemCount();
	if (ItemNum >= mPzkIni.mProBuf.ProMax)
	{
		MsgBox("已经达到保护最大数量，不能继续添加");
		return;
	}

	mProItem.Name = "";
	mProItem.ProtectId = 0;
	mProItem.Enable = true;
	mProItem.Misc = 0;
	mProItem.DelayTime = 0;
	mProItem.Value = 0;

	CProItemDlg tempdlg;
	if(tempdlg.DoModal() != TRUE)
		return;

	pList->InsertItem(ItemNum,Str(ItemNum),NULL);
	pList->SetItemText(ItemNum,1,mProItem.Name);
	pList->SetItemText(ItemNum,2,Str(mProItem.ProtectId));
	if(mProItem.Enable)
		pList->SetItemText(ItemNum,3,"yes");
	else
		pList->SetItemText(ItemNum,3,"no");
	pList->SetItemText(ItemNum,4,Str(mProItem.Value));
	pList->SetItemText(ItemNum,5,Str(mProItem.DelayTime));
	pList->SetItemText(ItemNum,6,Str(mProItem.Misc));

	m_Edit1 += 1;
	UpdateData(FALSE);
	bEverEdited = true;

	return;
}

void CProDlg::OnItemRemove()
{
	// TODO: Add your control notification handler code here
	int ItemNo;
	int ItemNum;
	CListCtrl *pList;
	pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
	POSITION pos;
/*	ItemNo = pList->GetSelectionMark();
	if(ItemNo < 0)
		return;

	CString str;
	str.Format("你确定要删除Protect第%d项吗?",ItemNo);
	int OkNo = AfxMessageBox(str,MB_YESNO);
	if(OkNo != IDYES)
		return;

	pList->DeleteItem(ItemNo);
*/
	pos = pList->GetFirstSelectedItemPosition();
	if(!pos)
		return;

	CString str,str1;
	str="你确定要删除Protect第";
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

void CProDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
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

    mProItem.Name = GetItemText(hWnd1,nItem,1);
	mProItem.ProtectId = atoi(GetItemText(hWnd1,nItem,2));
	if(GetItemText(hWnd1,nItem,3) == "yes")
		mProItem.Enable = true;
	else
		mProItem.Enable = false;
	mProItem.Value = atoi(GetItemText(hWnd1,nItem,4));
	mProItem.DelayTime = atoi(GetItemText(hWnd1,nItem,5));
	mProItem.Misc = atoi(GetItemText(hWnd1,nItem,6));

	CProItemDlg tempdlg;
	if( tempdlg.DoModal() != TRUE)
		return;

	pList->SetItemText(nItem,1,mProItem.Name);
	pList->SetItemText(nItem,2,Str(mProItem.ProtectId));
	if(mProItem.Enable)
		pList->SetItemText(nItem,3,"yes");
	else
		pList->SetItemText(nItem,3,"no");
	pList->SetItemText(nItem,4,Str(mProItem.Value));
	pList->SetItemText(nItem,5,Str(mProItem.DelayTime));
	pList->SetItemText(nItem,6,Str(mProItem.Misc));
	bEverEdited = true;

	*pResult = 0;

}

void CProDlg::OnItemEdit()
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

    if(nSubItem == -1 || nItem == -1)
	{
        return ;
	}

    mProItem.Name = GetItemText(hWnd1,nItem,1);
	mProItem.ProtectId = atoi(GetItemText(hWnd1,nItem,2));
	if(GetItemText(hWnd1,nItem,3) == "yes")
		mProItem.Enable = true;
	else
		mProItem.Enable = false;
	mProItem.Value = atoi(GetItemText(hWnd1,nItem,3));
	mProItem.DelayTime = atoi(GetItemText(hWnd1,nItem,4));
	mProItem.Misc = atoi(GetItemText(hWnd1,nItem,5));

	CProItemDlg tempdlg;
	if( tempdlg.DoModal() != TRUE)
		return;

	pList->SetItemText(nItem,1,mProItem.Name);
	pList->SetItemText(nItem,2,Str(mProItem.ProtectId));
	if(mProItem.Enable)
		pList->SetItemText(nItem,3,"yes");
	else
		pList->SetItemText(nItem,3,"no");
	pList->SetItemText(nItem,4,Str(mProItem.Value));
	pList->SetItemText(nItem,5,Str(mProItem.DelayTime));
	pList->SetItemText(nItem,6,Str(mProItem.Misc));

	bEverEdited = true;
}

void CProDlg::OnOK()
{
	// TODO: Add your control notification handler code here
	mPzkIni.mProBuf.ProNum = m_Edit1;
	CListCtrl *pList;
	pList = (CListCtrl *)GetDlgItem(IDC_LIST1);

	HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST1);

	UpdateData(TRUE);
	for(int i=0 ;i<m_Edit1 ;i++)
	{
		mPzkIni.mProBuf.pPro[i].Name = GetItemText(hWnd1,i,1);
		mPzkIni.mProBuf.pPro[i].ProtectId = atoi(GetItemText(hWnd1,i,2));
		if(GetItemText(hWnd1,i,3) == "yes")
			mPzkIni.mProBuf.pPro[i].Enable = true;
		else
			mPzkIni.mProBuf.pPro[i].Enable = false;
		mPzkIni.mProBuf.pPro[i].Value = atoi(GetItemText(hWnd1,i,4));
		mPzkIni.mProBuf.pPro[i].DelayTime = atoi(GetItemText(hWnd1,i,5));
		mPzkIni.mProBuf.pPro[i].Misc = atoi(GetItemText(hWnd1,i,6));
	}
	bEverEdited = true;
}

void CProDlg::OnSave()
{
	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;
	CListCtrl *pList;
	pList = (CListCtrl *)GetDlgItem(IDC_LIST1);

	HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST1);

	UpdateData(TRUE);
	mPzkIni.mProBuf.ProNum = m_Edit1;
	mPzkIni.mIopCfg.ProtectNum = m_Edit1;
	int i;
	for(i=0; i<mPzkIni.mProBuf.ProMax; i++)
		mPzkIni.mProBuf.pValid[i] = false;
	for(i=0 ;i<m_Edit1 ;i++)
	{
		mPzkIni.mProBuf.pValid[i] = true;
		mPzkIni.mProBuf.pPro[i].Name = GetItemText(hWnd1,i,1);
		mPzkIni.mProBuf.pPro[i].ProtectId = atoi(GetItemText(hWnd1,i,2));
		if(GetItemText(hWnd1,i,3) == "yes")
			mPzkIni.mProBuf.pPro[i].Enable = true;
		else
			mPzkIni.mProBuf.pPro[i].Enable = false;
		mPzkIni.mProBuf.pPro[i].Value = atoi(GetItemText(hWnd1,i,4));
		mPzkIni.mProBuf.pPro[i].DelayTime = atoi(GetItemText(hWnd1,i,5));
		mPzkIni.mProBuf.pPro[i].Misc = atoi(GetItemText(hWnd1,i,6));
	}
	bEverEdited = false;
	mPzkIni.EverModified = true;
}

void CProDlg::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CPoint oPoint;//定义一个用于确定光标位置的位置
    GetCursorPos( &oPoint);//
	CMenu *hMenu;
	hMenu = mMenu.GetSubMenu(0);
	hMenu->TrackPopupMenu(TPM_LEFTALIGN,oPoint.x,oPoint.y,this,0);
	*pResult = 0;
}

void CProDlg::OnItemSave()
{
	// TODO: Add your command handler code here
	OnSave();
}


BOOL CProDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	int i;
	try
	{
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

	catch(CException* e)
	{
		throw;
	}

}

LRESULT CProDlg::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)
{
	if(bEverEdited)
	{
		int i = AfxMessageBox("保存当前对保护参数配置所做的更改吗？",MB_YESNOCANCEL);
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

void CProDlg::OnRevert()
{
	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;

	int i,j;
	CString str;
	CListCtrl *pProList = (CListCtrl *)GetDlgItem(IDC_LIST1);
    HWND hWnd = ::GetDlgItem(m_hWnd, IDC_LIST1);
	m_Edit1 = mPzkIni.mProBuf.ProNum;
	UpdateData(FALSE);

	pProList->DeleteAllItems();
	for(i=0;i<mPzkIni.mProBuf.ProNum ;i++)
		for(j=0;j<7;j++)
			switch(j)
			{
			case 0:
				SetCell(hWnd,Str(i),i,j);
				break;
			case 1:
				SetCell(hWnd,mPzkIni.mProBuf.pPro[i].Name,i,j);
				break;
			case 2:
				SetCell(hWnd,Str(mPzkIni.mProBuf.pPro[i].ProtectId),i,j);
				break;
			case 3:
				if(mPzkIni.mProBuf.pPro[i].Enable)
					SetCell(hWnd,"yes",i,j);
				else
					SetCell(hWnd,"no",i,j);
				break;
			case 4:
				SetCell(hWnd,Str(mPzkIni.mProBuf.pPro[i].Value),i,j);
				break;
			case 5:
				SetCell(hWnd,Str(mPzkIni.mProBuf.pPro[i].DelayTime),i,j);
				break;
			case 6:
				SetCell(hWnd,Str(mPzkIni.mProBuf.pPro[i].Misc),i,j);
				break;
			}
	bEverEdited = false;
}

LRESULT CProDlg::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)
{
	OnRevert();
	return TRUE;
}

void CProDlg::OnItemCancel()
{
	// TODO: Add your command handler code here
	OnRevert();
}
