// DoSboDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "DoSboDlg.h"
#include "myfun.h"
#include "ReadPzkIni.h"
#include "SboItemDlg.h"
#include "DoItemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int SEL_NONE = 0;
const int SEL_SBO  = 1;
const int SEL_DO   = 2;

extern SboStru_ mSboItem;
extern DoStru_ mDoItem;

extern bool bCloseWindow;
/////////////////////////////////////////////////////////////////////////////
// CDoSboDlg

IMPLEMENT_DYNCREATE(CDoSboDlg, CFormView)

CDoSboDlg::CDoSboDlg()
	: CFormView(CDoSboDlg::IDD)
{
	//{{AFX_DATA_INIT(CDoSboDlg)
	m_SboWaitTime = 0;
	m_SboNum = 0;
	m_DoNum = 0;
	//}}AFX_DATA_INIT
	mSelControl = SEL_NONE;
}

CDoSboDlg::~CDoSboDlg()
{
}

void CDoSboDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoSboDlg)
	DDX_Control(pDX, IDC_LIST2, m_DoList);
	DDX_Control(pDX, IDC_LIST1, m_SboList);
	DDX_Text(pDX, IDC_EDIT1, m_SboWaitTime);
	DDX_Text(pDX, IDC_EDIT2, m_SboNum);
	DDX_Text(pDX, IDC_EDIT3, m_DoNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDoSboDlg, CFormView)
	//{{AFX_MSG_MAP(CDoSboDlg)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkList2)
	ON_NOTIFY(NM_SETFOCUS, IDC_LIST1, OnSetfocusList1)
	ON_NOTIFY(NM_SETFOCUS, IDC_LIST2, OnSetfocusList2)
	ON_BN_CLICKED(IDC_ADDITEM, OnAdditem)
	ON_BN_CLICKED(IDC_REMOVEITEM, OnRemoveitem)
	ON_BN_CLICKED(IDC_EDITITEM, OnEdititem)
	ON_BN_CLICKED(IDSAVE, OnSave)
	ON_COMMAND(ID_ITEM_ADD, OnItemAdd)
	ON_COMMAND(ID_ITEM_EDIT, OnItemEdit)
	ON_COMMAND(ID_ITEM_SAVE, OnItemSave)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, OnRclickList2)
	ON_COMMAND(ID_ITEM_REMOVE, OnItemRemove)
	ON_BN_CLICKED(IDREVERT, OnRevert)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_COMMAND(ID_ITEM_CANCEL, OnItemCancel)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoSboDlg diagnostics

#ifdef _DEBUG
void CDoSboDlg::AssertValid() const
{
	CFormView::AssertValid();
}

void CDoSboDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void CDoSboDlg::InsertItems()
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
    list.pszText   = "SBO名称";
    list.iSubItem = 1;
    //Inserts the column
    ::SendMessage(hWnd,LVM_INSERTCOLUMN,
        (WPARAM)1,(WPARAM)&list);

    list.cx = 80;
    list.pszText   = "SBO号";
    list.iSubItem = 2;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)2,(WPARAM)&list);

    list.cx = 100;
    list.pszText   = "有效标志";
    list.iSubItem = 3;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)3,(WPARAM)&list);

    list.cx = 150;
    list.pszText   = "分闸脉冲宽度";
    list.iSubItem = 4;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)4,(WPARAM)&list);

	list.cx = 150;
    list.pszText   = "合闸脉冲宽度";
    list.iSubItem = 5;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)5,(WPARAM)&list);

	for(i=0;i<m_SboNum;i++)
		for(j=0;j<6;j++)
			switch(j)
			{
			case 0:
				SetCell(hWnd,Str(i),i,j);
				break;
			case 1:
				SetCell(hWnd,mPzkIni.mSboBuf.pSbo[i].name ,i,j);
				break;
			case 2:
				SetCell(hWnd,Str(mPzkIni.mSboBuf.pSbo[i].SboId),i,j);
				break;
			case 3:
				if(mPzkIni.mSboBuf.pSbo[i].valid)
					SetCell(hWnd,"yes",i,j);
				else
					SetCell(hWnd,"no",i,j);
				break;
			case 4:
				SetCell(hWnd,Str(mPzkIni.mSboBuf.pSbo[i].TripPulseWidth ),i,j);
				break;
			case 5:
				SetCell(hWnd,Str(mPzkIni.mSboBuf.pSbo[i].ClosePulseWidth ),i,j);
				break;
			}

////////////////////insert Do List
    hWnd = ::GetDlgItem(m_hWnd, IDC_LIST2);

    // Set the LVCOLUMN structure with the required
    // column information
    list.mask =  LVCF_TEXT |LVCF_WIDTH|
        LVCF_FMT |LVCF_SUBITEM;
    list.fmt = LVCFMT_LEFT;

    list.cx = 100;
    list.pszText   = "No.";
    list.iSubItem = 0;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)0,(WPARAM)&list);

    list.cx = 100;
    list.pszText   = "名称";
    list.iSubItem = 1;
    //Inserts the column
    ::SendMessage(hWnd,LVM_INSERTCOLUMN,
        (WPARAM)1,(WPARAM)&list);

    list.cx = 100;
    list.pszText   = "DO序号";
    list.iSubItem = 2;
    ::SendMessage(hWnd  ,LVM_INSERTCOLUMN,
        (WPARAM)2,(WPARAM)&list);

	for(i=0;i<m_DoNum;i++)
		for(j=0;j<3;j++)
			switch(j)
			{
			case 0:
				SetCell(hWnd,Str(i),i,j);
				break;
			case 1:
				SetCell(hWnd,mPzkIni.mDoBuf.pDo[i].name ,i,j);
				break;
			case 2:
				SetCell(hWnd,Str(mPzkIni.mDoBuf.pDo[i].DOAddr ),i,j);
				break;
			}
}

void CDoSboDlg::SetCell(HWND hWnd1,
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

CString CDoSboDlg::GetItemText(
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

/////////////////////////////////////////////////////////////////////////////
// CDoSboDlg message handlers

void CDoSboDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	mMenu.LoadMenu(IDR_ITEM_MENU);

	m_SboWaitTime = mPzkIni.mIopCfg.SBOTimeOut;
	m_SboNum = mPzkIni.mSboBuf.SboNum;
	m_DoNum = mPzkIni.mDoBuf.DoNum;

	UpdateData(FALSE);

	m_SboList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_DoList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	InsertItems();
	bEverEdited = false;
	mSelControl = SEL_NONE;
}

void CDoSboDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	int ItemNo;
	CListCtrl *pList = (CListCtrl *)GetDlgItem(IDC_LIST1);

	ItemNo = pList->GetSelectionMark();

	if(ItemNo < 0)
		return;

	mSboItem.name = pList->GetItemText(ItemNo,1);
	mSboItem.SboId = atoi(pList->GetItemText(ItemNo,2));
	if(pList->GetItemText(ItemNo,3) == "yes")
		mSboItem.valid = true;
	else
		mSboItem.valid = false;
	mSboItem.TripPulseWidth = atoi(pList->GetItemText(ItemNo,4));
	mSboItem.ClosePulseWidth = atoi(pList->GetItemText(ItemNo,5));

	CSboItemDlg tempdlg;
	if(tempdlg.DoModal() != TRUE)
		return;

	pList->SetItemText(ItemNo,1,mSboItem.name);
	pList->SetItemText(ItemNo,2,Str(mSboItem.SboId));
	if(mSboItem.valid)
		pList->SetItemText(ItemNo,3,"yes");
	else
		pList->SetItemText(ItemNo,3,"no");
	pList->SetItemText(ItemNo,4,Str(mSboItem.TripPulseWidth));
	pList->SetItemText(ItemNo,5,Str(mSboItem.ClosePulseWidth));

	bEverEdited = true;

	*pResult = 0;
}

void CDoSboDlg::OnOK()
{
	// TODO: Add your control notification handler code here

}

void CDoSboDlg::OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	int ItemNo;
	CListCtrl *pList = (CListCtrl *)GetDlgItem(IDC_LIST2);

	ItemNo = pList->GetSelectionMark();

	if(ItemNo < 0)
		return;

	mDoItem.name = pList->GetItemText(ItemNo,1);
	mDoItem.DOAddr = atoi(pList->GetItemText(ItemNo,2));

	CDoItemDlg tempdlg;
	if(tempdlg.DoModal() != TRUE)
		return;

	pList->SetItemText(ItemNo,1,mDoItem.name);
	pList->SetItemText(ItemNo,2,Str(mDoItem.DOAddr));

	bEverEdited = true;

	*pResult = 0;
}

void CDoSboDlg::OnSetfocusList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	mSelControl = SEL_SBO;
	*pResult = 0;
}

void CDoSboDlg::OnSetfocusList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	mSelControl = SEL_DO;
	*pResult = 0;
}

void CDoSboDlg::OnAdditem()
{
	// TODO: Add your control notification handler code here
	int mNum;
	CListCtrl *pList;

	if(mSelControl == SEL_SBO)
	{
		pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
		mNum = pList->GetItemCount();
		if (mNum >= mPzkIni.mSboBuf.SboMax)
		{
			msgbox("已经达到SBO最大个数，不能继续添加!");
			return;
		}
		mSboItem.name = "";
		mSboItem.SboId = 0;
		mSboItem.valid = true;
		mSboItem.TripPulseWidth = 0;
		mSboItem.ClosePulseWidth = 0;

		CSboItemDlg tempdlg;
		if(tempdlg.DoModal() != TRUE)
			return;

		pList->InsertItem(mNum,Str(mNum),NULL);
		pList->SetItemText(mNum,1,mSboItem.name);
		pList->SetItemText(mNum,2,Str(mSboItem.SboId));
		if(mSboItem.valid)
			pList->SetItemText(mNum,3,"yes");
		else
			pList->SetItemText(mNum,3,"no");
		pList->SetItemText(mNum,4,Str(mSboItem.TripPulseWidth));
		pList->SetItemText(mNum,5,Str(mSboItem.ClosePulseWidth));

		m_SboNum += 1;
		UpdateData(FALSE);
		bEverEdited = true;
	}
	else if(mSelControl = SEL_DO)
	{
		pList = (CListCtrl *)GetDlgItem(IDC_LIST2);
		mNum = pList->GetItemCount();

		if(mNum >= mPzkIni.mDoBuf.DoMax)
		{
			msgbox("已经达到DO最大个数，不能继续添加!");
			return;
		}

		mDoItem.name = "";
		mDoItem.DOAddr = 0;

		CDoItemDlg tempdlg1;
		if(tempdlg1.DoModal() != TRUE)
			return;

		pList->InsertItem(mNum,Str(mNum),NULL);
		pList->SetItemText(mNum,1,mDoItem.name);
		pList->SetItemText(mNum,2,Str(mDoItem.DOAddr));

		m_DoNum += 1;
		UpdateData(FALSE);
		bEverEdited = true;
	}
	else
		msgbox("请先选择对象！");
}

void CDoSboDlg::OnRemoveitem()
{
	// TODO: Add your control notification handler code here
	int ItemNo;
	CListCtrl *pList;
	CString ShowStr;
	POSITION pos;
	CString str,str1;

	if(mSelControl == SEL_SBO)
	{
		pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
/*		mNo = pList->GetSelectionMark();
		if(mNo == -1)
		{
			msgbox("请先选择你要删除的项!");
			return;
		}
		ShowStr.Format("你确定要删除SBO第%d项吗？",mNo);
		i = AfxMessageBox(ShowStr,MB_YESNO);
		if( i != IDYES)
			return;
		pList->DeleteItem(mNo);
*/
		pos = pList->GetFirstSelectedItemPosition();
		if(!pos)
			return;

		str="你确定要删除SBO第";
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

		m_SboNum = pList->GetItemCount();
		for(int i=0;i<m_SboNum;i++)
			pList->SetItemText(i,0,Str(i));

		UpdateData(FALSE);
		bEverEdited = true;
	}
	else if(mSelControl == SEL_DO)
	{
		pList = (CListCtrl *)GetDlgItem(IDC_LIST2);
/*		mNo = pList->GetSelectionMark();
		if(mNo == -1)
		{
			msgbox("请先选择你要删除的项!");
			return;
		}
		ShowStr.Format("你确定要删除DO第%d项吗？",mNo);
		i = AfxMessageBox(ShowStr,MB_YESNO);
		if( i != IDYES)
			return;
		pList->DeleteItem(mNo);
*/
		pos = pList->GetFirstSelectedItemPosition();
		if(!pos)
			return;

		str="你确定要删除DO第";
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

		m_DoNum = pList->GetItemCount();
		for(int i=0;i<m_DoNum;i++)
			pList->SetItemText(i,0,Str(i));

		UpdateData(FALSE);
		bEverEdited = true;
	}
	else
		msgbox("请先选择对象！");
}

void CDoSboDlg::OnEdititem()
{
	// TODO: Add your control notification handler code here
	int mNo;
	CListCtrl *pList;
	POSITION pos;

	if(mSelControl == SEL_SBO)
	{
		pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
		pos = pList->GetFirstSelectedItemPosition();
		if(!pos)
			return;

		mNo = pList->GetSelectionMark();

		if(mNo < 0)
			return;

		mSboItem.name = pList->GetItemText(mNo,1);
		mSboItem.SboId = atoi(pList->GetItemText(mNo,2));
		if(pList->GetItemText(mNo,3) == "yes")
			mSboItem.valid = true;
		else
			mSboItem.valid = false;
		mSboItem.TripPulseWidth = atoi(pList->GetItemText(mNo,4));
		mSboItem.ClosePulseWidth = atoi(pList->GetItemText(mNo,5));

		CSboItemDlg tempdlg;
		if(tempdlg.DoModal() != TRUE)
			return;

		pList->SetItemText(mNo,1,mSboItem.name);
		pList->SetItemText(mNo,2,Str(mSboItem.SboId));
		if(mSboItem.valid)
			pList->SetItemText(mNo,3,"yes");
		else
			pList->SetItemText(mNo,3,"no");
		pList->SetItemText(mNo,4,Str(mSboItem.TripPulseWidth));
		pList->SetItemText(mNo,5,Str(mSboItem.ClosePulseWidth));
		bEverEdited = true;
	}
	else if(mSelControl = SEL_DO)
	{
		pList = (CListCtrl *)GetDlgItem(IDC_LIST2);
		pos = pList->GetFirstSelectedItemPosition();
		if(!pos)
			return;

		mNo = pList->GetSelectionMark();

		if(mNo < 0)
			return;

		mDoItem.name = pList->GetItemText(mNo,1);
		mDoItem.DOAddr = atoi(pList->GetItemText(mNo,2));

		CDoItemDlg tempdlg1;
		if(tempdlg1.DoModal() != TRUE)
			return;

		pList->SetItemText(mNo,1,mDoItem.name);
		pList->SetItemText(mNo,2,Str(mDoItem.DOAddr));
		bEverEdited = true;
	}
	else
		msgbox("请先选择对象！");
}

void CDoSboDlg::OnSave()
{
	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;
	int i;
	CListCtrl *pList;
	UpdateData(TRUE);

	mPzkIni.mIopCfg.SBOTimeOut = m_SboWaitTime;
	mPzkIni.mSboBuf.SboNum = m_SboNum;
	mPzkIni.mIopCfg.SBONumber = m_SboNum;
	pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
	for(i=0;i<mPzkIni.mSboBuf.SboMax;i++)
		mPzkIni.mSboBuf.pValid[i] = false;

	for(i=0 ;i<m_SboNum ;i++)
	{
		mPzkIni.mSboBuf.pValid[i] = true;
		mPzkIni.mSboBuf.pSbo[i].name = pList->GetItemText(i,1);
		mPzkIni.mSboBuf.pSbo[i].SboId = atoi(pList->GetItemText(i,2));
		if(pList->GetItemText(i,3) == "yes")
			mPzkIni.mSboBuf.pSbo[i].valid = true;
		else
			mPzkIni.mSboBuf.pSbo[i].valid = false;
		mPzkIni.mSboBuf.pSbo[i].TripPulseWidth = atoi(pList->GetItemText(i,4));
		mPzkIni.mSboBuf.pSbo[i].ClosePulseWidth = atoi(pList->GetItemText(i,5));
	}

	mPzkIni.mDoBuf.DoNum = m_DoNum;
	mPzkIni.mIopCfg.DONumber = m_DoNum;
	pList = (CListCtrl *)GetDlgItem(IDC_LIST2);
	for(i=0;i<mPzkIni.mDoBuf.DoMax;i++)
		mPzkIni.mDoBuf.pValid[i] = false;

	for(i=0; i<m_DoNum; i++)
	{
		mPzkIni.mDoBuf.pValid[i] = true;
		mPzkIni.mDoBuf.pDo[i].name = pList->GetItemText(i,1);
		mPzkIni.mDoBuf.pDo[i].DOAddr = atoi(pList->GetItemText(i,2));
	}
	bEverEdited = false;
	mPzkIni.EverModified = true;
}

void CDoSboDlg::OnItemAdd()
{
	// TODO: Add your command handler code here
	OnAdditem();
}

void CDoSboDlg::OnItemEdit()
{
	// TODO: Add your command handler code here
	OnEdititem();
}

void CDoSboDlg::OnItemSave()
{
	// TODO: Add your command handler code here
	OnSave();
}

void CDoSboDlg::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CPoint oPoint;//定义一个用于确定光标位置的位置
    GetCursorPos( &oPoint);//
	CMenu *hMenu;
	hMenu = mMenu.GetSubMenu(0);
	hMenu->TrackPopupMenu(TPM_LEFTALIGN,oPoint.x,oPoint.y,this,0);
	*pResult = 0;
}

void CDoSboDlg::OnRclickList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CPoint oPoint;//定义一个用于确定光标位置的位置
    GetCursorPos( &oPoint);//
	CMenu *hMenu;
	hMenu = mMenu.GetSubMenu(0);
	hMenu->TrackPopupMenu(TPM_LEFTALIGN,oPoint.x,oPoint.y,this,0);
	*pResult = 0;
}

void CDoSboDlg::OnItemRemove()
{
	// TODO: Add your command handler code here
	OnRemoveitem();
}

BOOL CDoSboDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	int i;
	try
	{
		if(bEverEdited)
		{
			i = AfxMessageBox("您已经修改了遥控配置，在退出该配置前确定要保存吗？",MB_YESNOCANCEL);
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

LRESULT CDoSboDlg::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)
{
	if(bEverEdited)
	{
		int i = AfxMessageBox("保存当前对遥控配置所做的更改吗？",MB_YESNOCANCEL);
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

void CDoSboDlg::OnRevert()
{
	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;

	int i,j;
	CString str;
    HWND hWnd = ::GetDlgItem(m_hWnd, IDC_LIST1);
	CListCtrl *pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
	m_SboWaitTime = mPzkIni.mIopCfg.SBOTimeOut;
	m_SboNum = mPzkIni.mSboBuf.SboNum;
	m_DoNum = mPzkIni.mDoBuf.DoNum;

	UpdateData(FALSE);

	pList->DeleteAllItems();
	for(i=0;i<m_SboNum;i++)
		for(j=0;j<6;j++)
			switch(j)
			{
			case 0:
				SetCell(hWnd,Str(i),i,j);
				break;
			case 1:
				SetCell(hWnd,mPzkIni.mSboBuf.pSbo[i].name ,i,j);
				break;
			case 2:
				SetCell(hWnd,Str(mPzkIni.mSboBuf.pSbo[i].SboId),i,j);
				break;
			case 3:
				if(mPzkIni.mSboBuf.pSbo[i].valid)
					SetCell(hWnd,"yes",i,j);
				else
					SetCell(hWnd,"no",i,j);
				break;
			case 4:
				SetCell(hWnd,Str(mPzkIni.mSboBuf.pSbo[i].TripPulseWidth ),i,j);
				break;
			case 5:
				SetCell(hWnd,Str(mPzkIni.mSboBuf.pSbo[i].ClosePulseWidth ),i,j);
				break;
			}

	pList = (CListCtrl *)GetDlgItem(IDC_LIST2);
    hWnd = ::GetDlgItem(m_hWnd, IDC_LIST2);
	pList->DeleteAllItems();
	for(i=0;i<m_DoNum;i++)
		for(j=0;j<3;j++)
			switch(j)
			{
			case 0:
				SetCell(hWnd,Str(i),i,j);
				break;
			case 1:
				SetCell(hWnd,mPzkIni.mDoBuf.pDo[i].name ,i,j);
				break;
			case 2:
				SetCell(hWnd,Str(mPzkIni.mDoBuf.pDo[i].DOAddr ),i,j);
				break;
			}

	bEverEdited = false;
}

LRESULT CDoSboDlg::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)
{
	OnRevert();
	return TRUE;
}

void CDoSboDlg::OnChangeEdit1()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDoSboDlg::OnItemCancel()
{
	// TODO: Add your command handler code here
	OnRevert();
}
