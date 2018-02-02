// ProcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "ProcDlg.h"
#include "MyFun.h"
#include "ReadPzkIni.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int CurProcNum;
extern bool bCloseWindow;
/////////////////////////////////////////////////////////////////////////////
// CProcDlg

IMPLEMENT_DYNCREATE(CProcDlg, CFormView)

CProcDlg::CProcDlg()
	: CFormView(CProcDlg::IDD)
{
	//{{AFX_DATA_INIT(CProcDlg)
	m_Version = _T("");
	m_Date = _T("");
	m_author = _T("");
	m_Program = _T("");
	m_MiscParamNum = 0;
	m_Input = _T("");
	m_Input1 = _T("");
	//}}AFX_DATA_INIT
}

CProcDlg::~CProcDlg()
{
}

void CProcDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProcDlg)
	DDX_Control(pDX, IDC_LIST5, m_List5);
	DDX_Control(pDX, IDC_LIST4, m_List4);
	DDX_Control(pDX, IDC_COMBO1, m_valid);
	DDX_Control(pDX, IDC_LIST3, m_List3);
	DDX_Control(pDX, IDC_LIST2, m_List2);
	DDX_Control(pDX, IDC_LIST1, m_List1);
	DDX_Text(pDX, IDC_EDIT2, m_Version);
	DDX_Text(pDX, IDC_EDIT3, m_Date);
	DDX_Text(pDX, IDC_EDIT4, m_author);
	DDX_Text(pDX, IDC_EDIT5, m_Program);
	DDX_Text(pDX, IDC_EDIT7, m_MiscParamNum);
	DDX_Text(pDX, IDC_EDIT8, m_Input);
	DDX_Text(pDX, IDC_EDIT1, m_Input1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProcDlg, CFormView)
	//{{AFX_MSG_MAP(CProcDlg)
	ON_BN_CLICKED(IDC_ADDALL, OnAddall)
	ON_BN_CLICKED(IDC_ADDONE, OnAddone)
	ON_BN_CLICKED(IDC_REMOVEONE, OnRemoveone)
	ON_BN_CLICKED(IDC_REMOVEALL, OnRemoveall)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	ON_LBN_DBLCLK(IDC_LIST2, OnDblclkList2)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, OnClickList3)
	ON_EN_KILLFOCUS(IDC_EDIT8, OnKillfocusEdit8)
	ON_BN_CLICKED(IDSAVE, OnSave)
	ON_BN_CLICKED(IDC_ADDITEM, OnAdditem)
	ON_BN_CLICKED(IDC_REMOVEITEM, OnRemoveitem)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeEdit7)
	ON_BN_CLICKED(IDC_ADDRTUALL, OnAddrtuall)
	ON_BN_CLICKED(IDC_ADDRTUONE, OnAddrtuone)
	ON_BN_CLICKED(IDC_REMOVERTUONE, OnRemovertuone)
	ON_BN_CLICKED(IDC_REMOVERTUALL, OnRemovertuall)
	ON_LBN_DBLCLK(IDC_LIST4, OnDblclkList4)
	ON_LBN_DBLCLK(IDC_LIST5, OnDblclkList5)
	ON_BN_CLICKED(IDREVERT, OnRevert)
	ON_EN_CHANGE(IDC_EDIT8, OnChangeEdit8)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcDlg diagnostics

#ifdef _DEBUG
void CProcDlg::AssertValid() const
{
	CFormView::AssertValid();
}

void CProcDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProcDlg message handlers
CString CProcDlg::GetItemText(
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

void CProcDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	int ItemIndex;
	int i,nIndex,nIndex1;
	m_List3.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List3.InsertColumn(0,"序号",LVCFMT_LEFT,50,-1);
	m_List3.InsertColumn(1,"杂项说明",LVCFMT_LEFT,100,-1);
	m_List3.InsertColumn(2,"杂项",LVCFMT_LEFT,100,-1);

	if(CurProcNum > mPzkIni.mProBuf.ProMax)
	{
		msgbox("error:the process num is large than process maxisize number!");
		return;
	}

	if(mPzkIni.mProcBuf.pProc[CurProcNum].valid)
		m_valid.SetCurSel(0);
	else
		m_valid.SetCurSel(1);
	m_Version  = mPzkIni.mProcBuf.pProc[CurProcNum].Version;
	m_Date = mPzkIni.mProcBuf.pProc[CurProcNum].Date;
	m_author = mPzkIni.mProcBuf.pProc[CurProcNum].author;
	m_Program = mPzkIni.mProcBuf.pProc[CurProcNum].Program;

	for(i=0,nIndex=0,nIndex1=0;i<mPzkIni.mProcBuf.ProcMax;i++)
	{
		if(mPzkIni.mProcBuf.pProc[CurProcNum].RelateProc[i])
		{
			//m_List1.InsertString(nIndex++,Str(i));
			ItemIndex = m_List1.AddString(mPzkIni.mProcBuf.pProc[i].name);
			m_List1.SetItemData(ItemIndex,i);
		}
		else
			if(mPzkIni.mProcBuf.pValid[i] && i!=CurProcNum)
			{
				//m_List2.InsertString(nIndex1++,Str(i));
				ItemIndex = m_List2.AddString(mPzkIni.mProcBuf.pProc[i].name);
				m_List2.SetItemData(ItemIndex,i);
			}
	}

	for(i=0,nIndex=0,nIndex1=0;i<mPzkIni.mRtuBuf.RtuMax;i++)
	{
		if(mPzkIni.mProcBuf.pProc[CurProcNum].RTUNum[i])
		{
			ItemIndex = m_List4.AddString(mPzkIni.mRtuBuf.pRtu[i].name);
			m_List4.SetItemData(ItemIndex,i);
		}
		else
			if(mPzkIni.mRtuBuf.pValid[i] && !mPzkIni.mRtuBuf.pRtu[i].valid)
			{
				ItemIndex = m_List5.AddString(mPzkIni.mRtuBuf.pRtu[i].name);
				m_List5.SetItemData(ItemIndex,i);
			}
	}

//	m_RTUNum = mPzkIni.mProcBuf.pProc[CurProcNum].RTUNum;
	m_MiscParamNum = mPzkIni.mProcBuf.pProc[CurProcNum].MiscParamNum;

	CString tempstr;

	for(i=0;i<m_MiscParamNum;i++)
	{
		m_List3.InsertItem(i,Str(i),NULL);
		m_List3.SetItemText(i,1,mPzkIni.mProcBuf.pProc[CurProcNum].pMiscNote[i]);
		m_List3.SetItemText(i,2,Str(mPzkIni.mProcBuf.pProc[CurProcNum].pMiscVal[i]));
	}

	UpdateData(FALSE);
	bEverEdited = false;

}

void CProcDlg::OnAddall()
{
	// TODO: Add your control notification handler code here
	int i,CurPosi;
	UINT ItemData;
	int AddCounter = m_List2.GetCount();
	for(i=0;i<AddCounter;i++)
	{
		ItemData = m_List2.GetItemData(0);
		CurPosi = m_List1.AddString(mPzkIni.mProcBuf.pProc[ItemData].name);
		m_List1.SetItemData(CurPosi,(DWORD)ItemData);
		m_List2.DeleteString(0);
	}
	bEverEdited = true;
}

void CProcDlg::OnAddone()
{
	// TODO: Add your control notification handler code here
	int CurSel = m_List2.GetCurSel();
	if (CurSel == LB_ERR )
		return;
	int ItemData,CurPosi;
	ItemData = m_List2.GetItemData(CurSel);
	CurPosi = m_List1.AddString(mPzkIni.mProcBuf.pProc[ItemData].name);
	m_List1.SetItemData(CurPosi,ItemData);
	m_List2.DeleteString(CurSel);
	bEverEdited = true;
}

void CProcDlg::OnRemoveone()
{
	// TODO: Add your control notification handler code here
	int CurSel = m_List1.GetCurSel();
	if (CurSel == LB_ERR )
		return;
	int ItemData,CurPosi;
	ItemData = m_List1.GetItemData(CurSel);
	CurPosi = m_List2.AddString(mPzkIni.mProcBuf.pProc[ItemData].name);
	m_List2.SetItemData(CurPosi,ItemData);
	m_List1.DeleteString(CurSel);
	bEverEdited = true;
}


void CProcDlg::OnRemoveall()
{
	// TODO: Add your control notification handler code here
	int i,CurPosi;
	UINT ItemData;
	int AddCounter = m_List1.GetCount();
	for(i=0;i<AddCounter;i++)
	{
		ItemData = m_List1.GetItemData(0);
		CurPosi = m_List2.AddString(mPzkIni.mProcBuf.pProc[ItemData].name);
		m_List2.SetItemData(CurPosi,ItemData);
		m_List1.DeleteString(0);
	}
	bEverEdited = true;
}

void CProcDlg::OnDblclkList1()
{
	// TODO: Add your control notification handler code here
	OnRemoveone();
}

void CProcDlg::OnDblclkList2()
{
	// TODO: Add your control notification handler code here
	OnAddone();
}

void CProcDlg::OnClickList3(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	int mEdit;
	Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST3);
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
	if(nSubItem == 1)
		mEdit = IDC_EDIT8;
	else if(nSubItem == 2)
		mEdit = IDC_EDIT1;
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

	::SetWindowPos(::GetDlgItem(m_hWnd,mEdit),
		HWND_TOP,rect.left+x+4,rect.top+y+3,
		rect.right-rect.left - 3,
		rect.bottom-rect.top - 3,NULL);
	::ShowWindow(::GetDlgItem(m_hWnd,mEdit),SW_SHOW);
	::SetFocus(::GetDlgItem(m_hWnd,mEdit));
	//Draw a Rectangle around the SubItem
	::Rectangle(::GetDC(temp->hdr.hwndFrom),
		rect.left,rect.top-1,rect.right,rect.bottom);
	//Set the listItem text in the EditBox
	::SetWindowText(::GetDlgItem(m_hWnd,mEdit),str);

	*pResult = 0;
}

void CProcDlg::OnKillfocusEdit8()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString str1 = m_Input;
	CListCtrl *pList = (CListCtrl *)GetDlgItem(IDC_LIST3);
	pList->SetItemText(nItem,nSubItem,str1);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT8),SW_HIDE);
//	bEverEdited = true;
}

void CProcDlg::OnSave()
{
	// TODO: Add your control notification handler code here
	if(!(bEverEdited || mPzkIni.mProcBuf.ptempValid[CurProcNum]))
		return;
	int i;
	UpdateData(TRUE);
//	mPzkIni.mProcBuf.pProc[CurProcNum].name = m_name;
	if(m_valid.GetCurSel() == 0)
		mPzkIni.mProcBuf.pProc[CurProcNum].valid = true;
	else
		mPzkIni.mProcBuf.pProc[CurProcNum].valid = false;
	mPzkIni.mProcBuf.pProc[CurProcNum].Version = m_Version;
	mPzkIni.mProcBuf.pProc[CurProcNum].Date = m_Date;
	mPzkIni.mProcBuf.pProc[CurProcNum].author = m_author;
	mPzkIni.mProcBuf.pProc[CurProcNum].Program = m_Program;

	UINT ItemData;
	int AddCounter = m_List1.GetCount();
	for(i =0;i<mPzkIni.mProcBuf.ProcMax;i++)
		mPzkIni.mProcBuf.pProc[CurProcNum].RelateProc[i] = false;
	for(i=0;i<AddCounter;i++)
	{
		ItemData = m_List1.GetItemData(i);
		mPzkIni.mProcBuf.pProc[CurProcNum].RelateProc[ItemData] = true;
	}

	AddCounter = m_List4.GetCount();
	for(i =0;i<mPzkIni.mRtuBuf.RtuMax;i++)
	{
		mPzkIni.mProcBuf.pProc[CurProcNum].RTUNum[i] = false;
		if(mPzkIni.mRtuBuf.pRtu[i].ProcessId == CurProcNum)
			mPzkIni.mRtuBuf.pRtu[i].valid = false;
	}
	for(i=0;i<AddCounter;i++)
	{
		ItemData = m_List4.GetItemData(i);
		mPzkIni.mProcBuf.pProc[CurProcNum].RTUNum[ItemData] = true;
		mPzkIni.mRtuBuf.pRtu[ItemData].ProcessId = CurProcNum;
		mPzkIni.mRtuBuf.pRtu[ItemData].valid = true;
	}
	//mPzkIni.mProcBuf.pProc[CurProcNum].RTUNum = m_RTUNum;

	if(mPzkIni.mProcBuf.pProc[CurProcNum].MiscParamNum > 0)
	{
		delete[] mPzkIni.mProcBuf.pProc[CurProcNum].pMiscNote;
		delete[] mPzkIni.mProcBuf.pProc[CurProcNum].pMiscVal;
	}
	mPzkIni.mProcBuf.pProc[CurProcNum].MiscParamNum = m_MiscParamNum;
	mPzkIni.mProcBuf.pProc[CurProcNum].pMiscNote = new CString[m_MiscParamNum];
	mPzkIni.mProcBuf.pProc[CurProcNum].pMiscVal = new unsigned char[m_MiscParamNum];
	for(i=0;i<m_MiscParamNum;i++)
	{
		mPzkIni.mProcBuf.pProc[CurProcNum].pMiscNote[i] = m_List3.GetItemText(i,1);
		mPzkIni.mProcBuf.pProc[CurProcNum].pMiscVal[i] = (unsigned char)myatoi(m_List3.GetItemText(i,2));
	}
	mPzkIni.mProcBuf.pValid[CurProcNum] = true;
	mPzkIni.mProcBuf.ptempValid[CurProcNum] = false;
	bEverEdited = false;
	mPzkIni.EverModified = true;
	return;
}

void CProcDlg::OnAdditem()
{
	// TODO: Add your control notification handler code here
	int ItemCount = m_List3.GetItemCount();

	if(ItemCount >= mPzkIni.mProcBuf.ProcMax)
	{
		AfxMessageBox("已经达到进程最大个数，不能继续添加!");
		return;
	}
	m_List3.InsertItem(ItemCount,Str(ItemCount));
	m_List3.SetItemText(ItemCount,1,"");
	m_List3.SetItemText(ItemCount,2,"0");

	m_MiscParamNum += 1;

	UpdateData(FALSE);
	bEverEdited = true;
}

void CProcDlg::OnRemoveitem()
{
	// TODO: Add your control notification handler code here
	int ItemNo;
	int ItemNum;
	CListCtrl *pList;
	POSITION pos;
	pList = (CListCtrl *)GetDlgItem(IDC_LIST3);
	pos = pList->GetFirstSelectedItemPosition();
	if(!pos)
		return;
	ItemNo = pList->GetSelectionMark();

	if(ItemNo < 0)
		return;

	int OkNo = AfxMessageBox("你确定要删除吗?",MB_YESNO);
	if(OkNo != IDYES)
		return;

	pList->DeleteItem(ItemNo);
	ItemNum = pList->GetItemCount();
	for(int i=0;i<ItemNum;i++)
		pList->SetItemText(i,0,Str(i));

	m_MiscParamNum = ItemNum;
	UpdateData(FALSE);
	bEverEdited = true;

}

void CProcDlg::OnChangeEdit2()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CProcDlg::OnChangeEdit3()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CProcDlg::OnChangeEdit4()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CProcDlg::OnChangeEdit5()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CProcDlg::OnChangeEdit6()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CProcDlg::OnChangeEdit7()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CProcDlg::OnChangeEdit1()
{
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT1);
	char str[32];
	pEdit->GetWindowText(str,32);
	int i = atoi(str);//.GetBuffer(str.GetLength()));
	if( i > 255)
	{
		i = 255;
		AfxMessageBox("不允许输入大于255的值!");
		pEdit->SetWindowText(Str(i));
	}
}

BOOL CProcDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	int i;

	if(bForDel)
	{
		bForDel = false;
		return CFormView::DestroyWindow();
	}
	try
	{
		if(bEverEdited || mPzkIni.mProcBuf.ptempValid[CurProcNum])
		{
			i = AfxMessageBox("您已经修改了第"+Str(CurProcNum)+"个进程的配置，在退出该配置前确定要保存吗？",MB_YESNOCANCEL);
			if(i == IDYES)
				OnSave();
			else if(i == IDCANCEL)
			{
				bCloseWindow = false;
				return FALSE;
			}
		}
		bEverEdited = true;
		return CFormView::DestroyWindow();
	}

	catch(CException* e)
	{
		throw;
	}

}

void CProcDlg::OnAddrtuall()
{
	// TODO: Add your control notification handler code here
	int i,CurPosi;
	UINT ItemData;
	int AddCounter = m_List5.GetCount();
	for(i=0;i<AddCounter;i++)
	{
		ItemData = m_List5.GetItemData(0);
		CurPosi = m_List4.AddString(mPzkIni.mRtuBuf.pRtu[ItemData].name);
		m_List4.SetItemData(CurPosi,(DWORD)ItemData);
		m_List5.DeleteString(0);
	}
	bEverEdited = true;
}

void CProcDlg::OnAddrtuone()
{
	// TODO: Add your control notification handler code here
	int CurSel = m_List5.GetCurSel();
	if (CurSel == LB_ERR )
		return;
	int ItemData,CurPosi;
	ItemData = m_List5.GetItemData(CurSel);
	CurPosi = m_List4.AddString(mPzkIni.mRtuBuf.pRtu[ItemData].name);
	m_List4.SetItemData(CurPosi,ItemData);
	m_List5.DeleteString(CurSel);
	bEverEdited = true;
}

void CProcDlg::OnRemovertuone()
{
	// TODO: Add your control notification handler code here
	int CurSel = m_List4.GetCurSel();
	if (CurSel == LB_ERR )
		return;
	int ItemData,CurPosi;
	ItemData = m_List4.GetItemData(CurSel);
	CurPosi = m_List5.AddString(mPzkIni.mRtuBuf.pRtu[ItemData].name);
	m_List5.SetItemData(CurPosi,ItemData);
	m_List4.DeleteString(CurSel);
	bEverEdited = true;
}

void CProcDlg::OnRemovertuall()
{
	// TODO: Add your control notification handler code here
	int i,CurPosi;
	UINT ItemData;
	int AddCounter = m_List4.GetCount();
	for(i=0;i<AddCounter;i++)
	{
		ItemData = m_List4.GetItemData(0);
		CurPosi = m_List5.AddString(mPzkIni.mRtuBuf.pRtu[ItemData].name);
		m_List5.SetItemData(CurPosi,ItemData);
		m_List4.DeleteString(0);
	}
	bEverEdited = true;
}

void CProcDlg::OnDblclkList4()
{
	// TODO: Add your control notification handler code here
	OnRemovertuone();
}

void CProcDlg::OnDblclkList5()
{
	// TODO: Add your control notification handler code here
	OnAddrtuone();
}

LRESULT CProcDlg::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)
{
	if(bEverEdited || mPzkIni.mProcBuf.ptempValid[CurProcNum])
	{
		int i = AfxMessageBox("保存对第"+Str(CurProcNum)+"个进程的配置所做的修改吗？",MB_YESNOCANCEL);
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

void CProcDlg::OnRevert()
{
	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;

	int ItemIndex;
	int i,nIndex,nIndex1;

	if(mPzkIni.mProcBuf.pProc[CurProcNum].valid)
		m_valid.SetCurSel(0);
	else
		m_valid.SetCurSel(1);
	m_Version  = mPzkIni.mProcBuf.pProc[CurProcNum].Version;
	m_Date = mPzkIni.mProcBuf.pProc[CurProcNum].Date;
	m_author = mPzkIni.mProcBuf.pProc[CurProcNum].author;
	m_Program = mPzkIni.mProcBuf.pProc[CurProcNum].Program;
//	UpdateData(FALSE);

	int AddCounter = m_List1.GetCount();
	for(i=0;i<AddCounter;i++)
		m_List1.DeleteString(0);
	AddCounter = m_List2.GetCount();
	for(i=0;i<AddCounter;i++)
		m_List2.DeleteString(0);
	AddCounter = m_List4.GetCount();
	for(i=0;i<AddCounter;i++)
		m_List4.DeleteString(0);
	AddCounter = m_List5.GetCount();
	for(i=0;i<AddCounter;i++)
		m_List5.DeleteString(0);
	m_List3.DeleteAllItems();
	for(i=0,nIndex=0,nIndex1=0;i<mPzkIni.mProcBuf.ProcMax;i++)
	{
		if(mPzkIni.mProcBuf.pProc[CurProcNum].RelateProc[i])
		{
			//m_List1.InsertString(nIndex++,Str(i));
			ItemIndex = m_List1.AddString(mPzkIni.mProcBuf.pProc[i].name);
			m_List1.SetItemData(ItemIndex,i);
		}
		else
			if(mPzkIni.mProcBuf.pValid[i] && i!=CurProcNum)
			{
				//m_List2.InsertString(nIndex1++,Str(i));
				ItemIndex = m_List2.AddString(mPzkIni.mProcBuf.pProc[i].name);
				m_List2.SetItemData(ItemIndex,i);
			}
	}

	for(i=0,nIndex=0,nIndex1=0;i<mPzkIni.mRtuBuf.RtuMax;i++)
	{
		if(mPzkIni.mProcBuf.pProc[CurProcNum].RTUNum[i])
		{
			ItemIndex = m_List4.AddString(mPzkIni.mRtuBuf.pRtu[i].name);
			m_List4.SetItemData(ItemIndex,i);
		}
		else
			if(mPzkIni.mRtuBuf.pValid[i] && !mPzkIni.mRtuBuf.pRtu[i].valid)
			{
				ItemIndex = m_List5.AddString(mPzkIni.mRtuBuf.pRtu[i].name);
				m_List5.SetItemData(ItemIndex,i);
			}
	}

//	m_RTUNum = mPzkIni.mProcBuf.pProc[CurProcNum].RTUNum;
	m_MiscParamNum = mPzkIni.mProcBuf.pProc[CurProcNum].MiscParamNum;
	UpdateData(FALSE);
	CString tempstr;
	for(i=0;i<m_MiscParamNum;i++)
	{
		m_List3.InsertItem(i,Str(i),NULL);
		m_List3.SetItemText(i,1,mPzkIni.mProcBuf.pProc[CurProcNum].pMiscNote[i]);
		m_List3.SetItemText(i,2,Str(mPzkIni.mProcBuf.pProc[CurProcNum].pMiscVal[i]));
	}

	bEverEdited = false;
}

LRESULT CProcDlg::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)
{
	OnRevert();
	return TRUE;
}

void CProcDlg::OnChangeEdit8()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CProcDlg::OnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CProcDlg::OnKillfocusEdit1()
{
	// TODO: Add your control notification handler code here
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT1);
	char str[32];
	pEdit->GetWindowText(str,32);
	if(strlen(str) == 0)
		pEdit->SetWindowText("0");

	int i = atoi(str);//.GetBuffer(str.GetLength()));
	if( i > 255)
	{
		i = 255;
		pEdit->SetWindowText(Str(i));
	}

	UpdateData(TRUE);

	CString str1 = m_Input1;
	CListCtrl *pList = (CListCtrl *)GetDlgItem(IDC_LIST3);
	pList->SetItemText(nItem,nSubItem,str1);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT1),SW_HIDE);
}
