// PulseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "PulseDlg.h"
#include "ReadPzkIni.h"
#include "MyFun.h"
#include "PulseItemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern PulseStru_ mPulseItem;
extern bool bCloseWindow;
/////////////////////////////////////////////////////////////////////////////
// CPulseDlg

IMPLEMENT_DYNCREATE(CPulseDlg, CFormView)

CPulseDlg::CPulseDlg()
	: CFormView(CPulseDlg::IDD)
{
	//{{AFX_DATA_INIT(CPulseDlg)
	m_PulseNum = 0;
	//}}AFX_DATA_INIT
}

CPulseDlg::~CPulseDlg()
{
}

void CPulseDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPulseDlg)
	DDX_Control(pDX, IDC_LIST1, m_List1);
	DDX_Text(pDX, IDC_EDIT1, m_PulseNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPulseDlg, CFormView)
	//{{AFX_MSG_MAP(CPulseDlg)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
	ON_COMMAND(ID_ITEM_ADD, OnItemAdd)
	ON_COMMAND(ID_ITEM_REMOVE, OnItemRemove)
	ON_COMMAND(ID_ITEM_EDIT, OnItemEdit)
	ON_BN_CLICKED(IDSAVE, OnSave)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDREVERT, OnRevert)
	ON_COMMAND(ID_ITEM_CANCEL, OnItemCancel)
	ON_COMMAND(ID_ITEM_SAVE, OnItemSave)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPulseDlg diagnostics

#ifdef _DEBUG
void CPulseDlg::AssertValid() const
{
	CFormView::AssertValid();
}

void CPulseDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPulseDlg message handlers

void CPulseDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	m_PulseNum = mPzkIni.mPulseBuf.PulseNum;
	UpdateData(FALSE);
	m_List1.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List1.InsertColumn(0,"NO.",LVCFMT_CENTER,50,-1);
	m_List1.InsertColumn(1,"脉冲名称",LVCFMT_CENTER,100,-1);
	m_List1.InsertColumn(2,"输入地址",LVCFMT_CENTER,80,-1);
	m_List1.InsertColumn(3,"脉冲类型",LVCFMT_CENTER,80,-1);
//	msgbox(Str(mPzkIni.mPulseBuf.PulseMax));
	for(int i=0;i<mPzkIni.mPulseBuf.PulseNum;i++)
	{
		m_List1.InsertItem(i,Str(i));
		m_List1.SetItemText(i,1,mPzkIni.mPulseBuf.pPulse[i].name);
		m_List1.SetItemText(i,2,Str(mPzkIni.mPulseBuf.pPulse[i].InputAddr));
		m_List1.SetItemText(i,3,Str(mPzkIni.mPulseBuf.pPulse[i].AccMode));
	}
	mMenu.LoadMenu(IDR_ITEM_MENU);
	bEverEdited = false;
}

void CPulseDlg::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CPoint oPoint;//定义一个用于确定光标位置的位置
    GetCursorPos( &oPoint);//
	CMenu *hMenu;
	hMenu = mMenu.GetSubMenu(0);
	hMenu->TrackPopupMenu(TPM_LEFTALIGN,oPoint.x,oPoint.y,this,0);
	*pResult = 0;
}

void CPulseDlg::OnItemAdd()
{
	// TODO: Add your command handler code here
	mPulseItem.name = "";
	mPulseItem.InputAddr = 0;
	mPulseItem.AccMode = 0;

	CPulseItemDlg tempdlg;
	if(tempdlg.DoModal() != TRUE)
		return;
	m_List1.InsertItem(m_PulseNum,Str(m_PulseNum));
	m_List1.SetItemText(m_PulseNum,1,mPulseItem.name);
	m_List1.SetItemText(m_PulseNum,2,Str(mPulseItem.InputAddr));
	m_List1.SetItemText(m_PulseNum,3,Str(mPulseItem.AccMode));
	m_PulseNum++;
	UpdateData(FALSE);
	bEverEdited = true;
}

void CPulseDlg::OnItemRemove()
{
	// TODO: Add your command handler code here
	int ItemNo;
	CListCtrl *pList;
	pList = (CListCtrl *)GetDlgItem(IDC_LIST1);
	POSITION pos;
/*	int SelItem = m_List1.GetSelectionMark();
	if(SelItem < 0)
		return;
	CString tempstr;
	tempstr.Format("你确定要删除Pulse第%d项吗?",SelItem);
	int i = AfxMessageBox(tempstr,MB_YESNO);
	if(i == IDNO)
		return;
	m_List1.DeleteItem(SelItem);
*/
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

	m_PulseNum = m_List1.GetItemCount();
	for(int i=0;i<m_PulseNum;i++)
	{
		m_List1.SetItemText(i,0,Str(i));
	}
	UpdateData(FALSE);
	bEverEdited = true;
}

void CPulseDlg::OnItemEdit()
{
	// TODO: Add your command handler code here
	POSITION pos;
	pos = m_List1.GetFirstSelectedItemPosition();
	if(!pos)
		return;

	int SelItem = m_List1.GetSelectionMark();
	mPulseItem.name = m_List1.GetItemText(SelItem,1);
	mPulseItem.InputAddr = atoi(m_List1.GetItemText(SelItem,2));
	mPulseItem.AccMode = atoi(m_List1.GetItemText(SelItem,3));

	CPulseItemDlg tempdlg;
	if(tempdlg.DoModal() == FALSE)
		return;

	m_List1.SetItemText(SelItem,1,mPulseItem.name);
	m_List1.SetItemText(SelItem,2,Str(mPulseItem.InputAddr));
	m_List1.SetItemText(SelItem,3,Str(mPulseItem.AccMode));

	bEverEdited = true;
}

void CPulseDlg::OnSave()
{
	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;
	int i;
	for(i=0;i<mPzkIni.mPulseBuf.PulseMax;i++)
		mPzkIni.mPulseBuf.pValid[i] = false;

	for(i=0;i<m_PulseNum;i++)
	{
		mPzkIni.mPulseBuf.pValid[i] = true;
		mPzkIni.mPulseBuf.pPulse[i].name = m_List1.GetItemText(i,1);
		mPzkIni.mPulseBuf.pPulse[i].InputAddr = myatoi(m_List1.GetItemText(i,2));
		mPzkIni.mPulseBuf.pPulse[i].AccMode = myatoi(m_List1.GetItemText(i,3));
	}
	mPzkIni.mPulseBuf.PulseNum = m_PulseNum;

	bEverEdited = false;
	mPzkIni.EverModified = true;
}

void CPulseDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	OnItemEdit();
	*pResult = 0;
}

BOOL CPulseDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	int i;
	try
	{
		if(bEverEdited)
		{
			i = AfxMessageBox("您已经修改了脉冲量配置，在退出该配置前确定要保存吗？",MB_YESNOCANCEL);
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

LRESULT CPulseDlg::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)
{
	if(bEverEdited)
	{
		int i = AfxMessageBox("保存当前对脉冲量配置所做的更改吗？",MB_YESNOCANCEL);
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

void CPulseDlg::OnRevert()
{
	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;

	m_PulseNum = mPzkIni.mPulseBuf.PulseNum;
	UpdateData(FALSE);

	m_List1.DeleteAllItems();
	for(int i=0;i<mPzkIni.mPulseBuf.PulseNum;i++)
	{
		m_List1.InsertItem(i,Str(i));
		m_List1.SetItemText(i,1,mPzkIni.mPulseBuf.pPulse[i].name);
		m_List1.SetItemText(i,2,Str(mPzkIni.mPulseBuf.pPulse[i].InputAddr));
		m_List1.SetItemText(i,3,Str(mPzkIni.mPulseBuf.pPulse[i].AccMode));
	}

	bEverEdited = false;
}

LRESULT CPulseDlg::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)
{
	OnRevert();
	return TRUE;
}

void CPulseDlg::OnItemCancel()
{
	// TODO: Add your command handler code here
	OnRevert();
}

void CPulseDlg::OnItemSave()
{
	// TODO: Add your command handler code here
	OnSave();
}
