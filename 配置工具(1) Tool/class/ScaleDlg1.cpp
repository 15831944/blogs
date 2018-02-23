// ScaleDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "ReadPzkIni.h"
#include "ScaleDlg1.h"
#include "MyFun.h"
#include "ScaleItemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern ScaleStru_ mScaleItem;
extern bool bCloseWindow;
/////////////////////////////////////////////////////////////////////////////
// CScaleDlg1

IMPLEMENT_DYNCREATE(CScaleDlg1, CFormView)

CScaleDlg1::CScaleDlg1()
	: CFormView(CScaleDlg1::IDD)
{
	//{{AFX_DATA_INIT(CScaleDlg1)
	m_ScaleNum = 0;
	m_Input = _T("");
	//}}AFX_DATA_INIT
}

CScaleDlg1::~CScaleDlg1()
{
}

void CScaleDlg1::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScaleDlg1)
	DDX_Control(pDX, IDC_LIST1, m_List1);
	DDX_Text(pDX, IDC_EDIT1, m_ScaleNum);
	DDX_Text(pDX, IDC_EDIT2, m_Input);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScaleDlg1, CFormView)
	//{{AFX_MSG_MAP(CScaleDlg1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnKillfocusEdit2)
	ON_BN_CLICKED(IDSAVE, OnSave)
	ON_BN_CLICKED(IDC_ADDITEM, OnAdditem)
	ON_BN_CLICKED(IDC_REMOVEITEM, OnRemoveitem)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_BN_CLICKED(IDREVERT, OnRevert)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
	ON_BN_CLICKED(IDC_EDITITEM, OnEdititem)
	ON_COMMAND(ID_ITEM_ADD, OnItemAdd)
	ON_COMMAND(ID_ITEM_EDIT, OnItemEdit)
	ON_COMMAND(ID_ITEM_REMOVE, OnItemRemove)
	ON_COMMAND(ID_ITEM_CANCEL, OnItemCancel)
	ON_COMMAND(ID_ITEM_SAVE, OnItemSave)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScaleDlg1 diagnostics

#ifdef _DEBUG
void CScaleDlg1::AssertValid() const
{
	CFormView::AssertValid();
}

void CScaleDlg1::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScaleDlg1 message handlers
CString CScaleDlg1::GetItemText(
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

void CScaleDlg1::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	mMenu.LoadMenu(IDR_ITEM_MENU);
	m_ScaleNum = mPzkIni.mScaleBuf.ScaleNum;
	UpdateData(FALSE);
	m_List1.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List1.InsertColumn(0,"序号",LVCFMT_LEFT,50,-1);
	m_List1.InsertColumn(1,"名称",LVCFMT_LEFT,150,-1);
	m_List1.InsertColumn(2,"工程最大值",LVCFMT_LEFT,100,-1);
	m_List1.InsertColumn(3,"工程最小值",LVCFMT_LEFT,100,-1);
	m_List1.InsertColumn(4,"用户最大值",LVCFMT_LEFT,100,-1);
	m_List1.InsertColumn(5,"用户最小值",LVCFMT_LEFT,100,-1);
	for(int i=0;i<m_ScaleNum;i++)
	{
		m_List1.InsertItem(i,Str(i));
		m_List1.SetItemText(i,1,mPzkIni.mScaleBuf.pScale[i].name);
		m_List1.SetItemText(i,2,Str(mPzkIni.mScaleBuf.pScale[i].HWMaxVal));
		m_List1.SetItemText(i,3,Str(mPzkIni.mScaleBuf.pScale[i].HWMinVal));
		m_List1.SetItemText(i,4,Str(mPzkIni.mScaleBuf.pScale[i].UserMaxVal));
		m_List1.SetItemText(i,5,Str(mPzkIni.mScaleBuf.pScale[i].UserMinVal));
	}
	bEverEdited = false;
}

void CScaleDlg1::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
/*	Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST1);
    LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
    RECT rect;
    //get the row number
    nItem = temp->iItem;
    //get the column number
    nSubItem = temp->iSubItem;

    if(nSubItem == 0 || nSubItem == -1 || nItem == -1)
	{
        return ;
	}
    //Retrieve the text of the selected subItem
    //from the list
    CString str = GetItemText(hWnd1,nItem ,
		nSubItem);

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

	::SetWindowPos(::GetDlgItem(m_hWnd,IDC_EDIT2),
		HWND_TOP,rect.left+x+4,rect.top+y+4,
		rect.right-rect.left - 3,
		rect.bottom-rect.top - 3,NULL);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT2),SW_SHOW);
	::SetFocus(::GetDlgItem(m_hWnd,IDC_EDIT2));
	//Draw a Rectangle around the SubItem
	::Rectangle(::GetDC(temp->hdr.hwndFrom),
		rect.left,rect.top-1,rect.right,rect.bottom);
	//Set the listItem text in the EditBox
	::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT2),str);
*/
	*pResult = 0;
}

void CScaleDlg1::OnKillfocusEdit2()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString str = m_Input;
	CListCtrl *pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
	if(nSubItem > 1)
		if (str.IsEmpty())
			str = "0";
	pList->SetItemText(nItem,nSubItem,str);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT2),SW_HIDE);
}

void CScaleDlg1::OnSave()
{
	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;
	UpdateData(TRUE);
	mPzkIni.mScaleBuf.ScaleNum = m_ScaleNum;

	for(int i=0; i<mPzkIni.mScaleBuf.ScaleMax; i++)
		mPzkIni.mScaleBuf.pValid[i] = false;

	for(i=0;i<m_ScaleNum;i++)
	{
		mPzkIni.mScaleBuf.pValid[i] = true;
		mPzkIni.mScaleBuf.pScale[i].name = m_List1.GetItemText(i,1);
		mPzkIni.mScaleBuf.pScale[i].HWMaxVal = myatoi(m_List1.GetItemText(i,2));
		mPzkIni.mScaleBuf.pScale[i].HWMinVal = myatoi(m_List1.GetItemText(i,3));
		mPzkIni.mScaleBuf.pScale[i].UserMaxVal = myatoi(m_List1.GetItemText(i,4));
		mPzkIni.mScaleBuf.pScale[i].UserMinVal = myatoi(m_List1.GetItemText(i,5));
	}
	bEverEdited = false;
}

void CScaleDlg1::OnAdditem()
{
	// TODO: Add your control notification handler code here
/*	int ItemCount = m_List1.GetItemCount();
	m_List1.InsertItem(ItemCount,Str(ItemCount));
	m_List1.SetItemText(ItemCount,1,"");
	m_List1.SetItemText(ItemCount,2,"0");
	m_List1.SetItemText(ItemCount,3,"0");
	m_List1.SetItemText(ItemCount,4,"0");
	m_List1.SetItemText(ItemCount,5,"0");

	m_ScaleNum += 1;

	UpdateData(FALSE);

	bEverEdited = true;
*/
	int ItemCount = m_List1.GetItemCount();
	ItemCount = m_List1.GetItemCount();
	if (ItemCount >= mPzkIni.mScaleBuf.ScaleMax)
	{
		MsgBox("已经达到Scale最大数量，不能继续添加");
		return;
	}

	mScaleItem.name = "";
	mScaleItem.HWMaxVal = 0;
	mScaleItem.HWMinVal = 0;
	mScaleItem.UserMaxVal = 0;
	mScaleItem.UserMinVal = 0;

	CScaleItemDlg tempdlg;
	if(tempdlg.DoModal() != TRUE)
		return;

	m_List1.InsertItem(ItemCount,Str(ItemCount),NULL);
	m_List1.SetItemText(ItemCount,1,mScaleItem.name);
	m_List1.SetItemText(ItemCount,2,Str(mScaleItem.HWMaxVal));
	m_List1.SetItemText(ItemCount,3,Str(mScaleItem.HWMinVal));
	m_List1.SetItemText(ItemCount,4,Str(mScaleItem.UserMaxVal));
	m_List1.SetItemText(ItemCount,5,Str(mScaleItem.UserMinVal));

	m_ScaleNum += 1;
	UpdateData(FALSE);

	bEverEdited = true;
}

void CScaleDlg1::OnRemoveitem()
{
	// TODO: Add your control notification handler code here
	int ItemNo;
	int ItemNum;
	CListCtrl *pList;
	pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
	POSITION pos;
/*	ItemNo = pList->GetSelectionMark();
	int OkNo = AfxMessageBox("你确定要删除吗?",MB_YESNO);
	if(OkNo != IDYES)
		return;

	pList->DeleteItem(ItemNo);
*/
	pos = pList->GetFirstSelectedItemPosition();
	if(!pos)
		return;

	CString str,str1;
	str="你确定要删除Scale第";
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

	m_ScaleNum = ItemNum;
	UpdateData(FALSE);

	bEverEdited = true;
}

LRESULT CScaleDlg1::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)
{
	if(bEverEdited)
	{
		int i = AfxMessageBox("保存当前对转换参数配置所做的更改吗？",MB_YESNOCANCEL);
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

BOOL CScaleDlg1::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	int i;

	try
	{
		if(bEverEdited)
		{
			i = AfxMessageBox("您已经修改了转换参数配置，在退出该配置前确定要保存吗？",MB_YESNOCANCEL);
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

void CScaleDlg1::OnChangeEdit2()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CScaleDlg1::OnRevert()
{
	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;

	m_ScaleNum = mPzkIni.mScaleBuf.ScaleNum;
	UpdateData(FALSE);

	m_List1.DeleteAllItems();
	for(int i=0;i<m_ScaleNum;i++)
	{
		m_List1.InsertItem(i,Str(i));
		m_List1.SetItemText(i,1,mPzkIni.mScaleBuf.pScale[i].name);
		m_List1.SetItemText(i,2,Str(mPzkIni.mScaleBuf.pScale[i].HWMaxVal));
		m_List1.SetItemText(i,3,Str(mPzkIni.mScaleBuf.pScale[i].HWMinVal));
		m_List1.SetItemText(i,4,Str(mPzkIni.mScaleBuf.pScale[i].UserMaxVal));
		m_List1.SetItemText(i,5,Str(mPzkIni.mScaleBuf.pScale[i].UserMinVal));
	}
	bEverEdited = false;
}

LRESULT CScaleDlg1::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)
{
	OnRevert();
	return TRUE;
}

void CScaleDlg1::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_List1.GetFirstSelectedItemPosition();
	if(!pos)
		return;
	int SelItem = m_List1.GetSelectionMark();
	if(SelItem < 0)
		return;

	mScaleItem.name = m_List1.GetItemText(SelItem,1);
	mScaleItem.HWMaxVal = atoi(m_List1.GetItemText(SelItem,2));
	mScaleItem.HWMinVal = atoi(m_List1.GetItemText(SelItem,3));
	mScaleItem.UserMaxVal = atoi(m_List1.GetItemText(SelItem,4));
	mScaleItem.UserMinVal = atoi(m_List1.GetItemText(SelItem,5));

	CScaleItemDlg tempdlg;
	if(tempdlg.DoModal() != TRUE)
		return;

	m_List1.SetItemText(SelItem,1,mScaleItem.name);
	m_List1.SetItemText(SelItem,2,Str(mScaleItem.HWMaxVal));
	m_List1.SetItemText(SelItem,3,Str(mScaleItem.HWMinVal));
	m_List1.SetItemText(SelItem,4,Str(mScaleItem.UserMaxVal));
	m_List1.SetItemText(SelItem,5,Str(mScaleItem.UserMinVal));

	bEverEdited = true;
	*pResult = 0;
}

void CScaleDlg1::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CPoint oPoint;//定义一个用于确定光标位置的位置
    GetCursorPos( &oPoint);//
	mSubMenu = mMenu.GetSubMenu(0);
	mSubMenu->TrackPopupMenu(TPM_LEFTALIGN,oPoint.x,oPoint.y,this,0);

	*pResult = 0;
}

void CScaleDlg1::OnEdititem()
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	pos = m_List1.GetFirstSelectedItemPosition();
	if(!pos)
		return;

	int SelItem = m_List1.GetSelectionMark();
	if(SelItem < 0)
		return;

	mScaleItem.name = m_List1.GetItemText(SelItem,1);
	mScaleItem.HWMaxVal = atoi(m_List1.GetItemText(SelItem,2));
	mScaleItem.HWMinVal = atoi(m_List1.GetItemText(SelItem,3));
	mScaleItem.UserMaxVal = atoi(m_List1.GetItemText(SelItem,4));
	mScaleItem.UserMinVal = atoi(m_List1.GetItemText(SelItem,5));

	CScaleItemDlg tempdlg;
	if(tempdlg.DoModal() != TRUE)
		return;

	m_List1.SetItemText(SelItem,1,mScaleItem.name);
	m_List1.SetItemText(SelItem,2,Str(mScaleItem.HWMaxVal));
	m_List1.SetItemText(SelItem,3,Str(mScaleItem.HWMinVal));
	m_List1.SetItemText(SelItem,4,Str(mScaleItem.UserMaxVal));
	m_List1.SetItemText(SelItem,5,Str(mScaleItem.UserMinVal));

	bEverEdited = true;
}

void CScaleDlg1::OnItemAdd()
{
	// TODO: Add your command handler code here
	OnAdditem();
}

void CScaleDlg1::OnItemEdit()
{
	// TODO: Add your command handler code here
	OnEdititem();
}

void CScaleDlg1::OnItemRemove()
{
	// TODO: Add your command handler code here
	OnRemoveitem();
}

void CScaleDlg1::OnItemCancel()
{
	// TODO: Add your command handler code here
	OnRevert();
}

void CScaleDlg1::OnItemSave()
{
	// TODO: Add your command handler code here
	OnSave();
}
