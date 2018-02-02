// ZjPlcCfgView.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "ReadPzkIni.h"
#include "ZjPlcCfgView.h"
#include "MyFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZjPlcCfgView

IMPLEMENT_DYNCREATE(CZjPlcCfgView, CFormView)

CZjPlcCfgView::CZjPlcCfgView()
	: CFormView(CZjPlcCfgView::IDD)
{
	//{{AFX_DATA_INIT(CZjPlcCfgView)
	m_Total = 0;
	m_RelcoseTime = 0;
	m_PlcTime = 0;
	m_PlcEnable = FALSE;
	m_BztEnable1 = FALSE;
	m_BztEnable2 = FALSE;
	m_LogicVol = 0;
	//}}AFX_DATA_INIT
	bEverEdited = false;
}

CZjPlcCfgView::~CZjPlcCfgView()
{
}

void CZjPlcCfgView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZjPlcCfgView)
	DDX_Control(pDX, IDC_EDITBOX, m_Editbox);
	DDX_Control(pDX, IDC_COMBO1, m_ComBo1);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Text(pDX, IDC_EDIT1, m_Total);
	DDX_Text(pDX, IDC_EDIT2, m_RelcoseTime);
	DDX_Text(pDX, IDC_EDIT3, m_PlcTime);
	DDX_Check(pDX, IDC_CHECK4, m_PlcEnable);
	DDX_Check(pDX, IDC_BZTENABLE1, m_BztEnable1);
	DDX_Check(pDX, IDC_BZTENABLE2, m_BztEnable2);
	DDX_Text(pDX, IDC_NORMALVOL, m_LogicVol);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZjPlcCfgView, CFormView)
	//{{AFX_MSG_MAP(CZjPlcCfgView)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_CANCEl, OnCANCEl)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_CBN_KILLFOCUS(IDC_COMBO1, OnKillfocusCombo1)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT3, OnKillfocusEdit3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_EN_CHANGE(IDC_NORMALVOL, OnChangeNormalvol)
	ON_BN_CLICKED(IDC_BZTENABLE1, OnBztenable1)
	ON_BN_CLICKED(IDC_BZTENABLE2, OnBztenable2)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZjPlcCfgView diagnostics

#ifdef _DEBUG
void CZjPlcCfgView::AssertValid() const
{
	CFormView::AssertValid();
}

void CZjPlcCfgView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

bool CZjPlcCfgView::GetRecloseEnable(CString sEnable)
{
	if(sEnable.Compare("投入") == 0)
		return true;
	else
		return false;
}

void CZjPlcCfgView::ResetRelcose()
{
	bool NRecloseEnable[32];
	int i = 0;	//从进线开始

	memset(NRecloseEnable, false, 32);
	while(i < m_List.GetItemCount())
	{
		NRecloseEnable[i] = GetRecloseEnable(m_List.GetItemText(i, 2));
		i++;
	}

	UpdateList(NRecloseEnable);
}
/////////////////////////////////////////////////////////////////////////////
// CZjPlcCfgView message handlers
void CZjPlcCfgView::UpdateList(bool ReCloseEnable[])
{
	CString formatStr;
	int addItem;
	m_List.DeleteAllItems();
	for(int i=0; i<m_Total; i++)
	{
		if(i == 0)
			formatStr = "主单元重合闸投/退";
		else
			formatStr.Format("单元%d重合闸投/退", i);

		addItem = m_List.InsertItem(i, Str(i), 0);
		m_List.SetItemText(addItem, 1, formatStr);
//投/退
		if(ReCloseEnable[i])
			m_List.SetItemText(addItem, 2, "投入");
		else
			m_List.SetItemText(addItem, 2, "退出");
	}
}

void CZjPlcCfgView::LoadData()
{
	m_PlcEnable = mPzkIni.ZjPlcFile.Cfg.PlcEnable;
	m_Total = mPzkIni.ZjPlcFile.Cfg.UnitTotal;

	m_RelcoseTime = mPzkIni.ZjPlcFile.Delay.InRecloseTime;
	m_PlcTime = mPzkIni.ZjPlcFile.Delay.PlcTime;

	m_BztEnable1 = (mPzkIni.ZjPlcFile.Bzt[0].Enable)? TRUE : FALSE;
	m_BztEnable2 = (mPzkIni.ZjPlcFile.Bzt[1].Enable)? TRUE : FALSE;

	m_LogicVol = mPzkIni.ZjPlcFile.Cfg.LogicVol;

	UpdateData(UPDATE_WRITE);
	UpdateList(mPzkIni.ZjPlcFile.Reclose.ReClose);
}

void CZjPlcCfgView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	int i = 0;
	m_List.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List.InsertColumn(i++, "序号", LVCFMT_LEFT, 45, -1);
	m_List.InsertColumn(i++, "名称", LVCFMT_LEFT, 145, -1);
	m_List.InsertColumn(i++, "投/退", LVCFMT_CENTER, 80, -1);

	LoadData();
}

void CZjPlcCfgView::OnSave()
{
	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;

	UpdateData(UPDATE_READ);

	mPzkIni.ZjPlcFile.Cfg.PlcEnable = (m_PlcEnable)? true : false;
	mPzkIni.ZjPlcFile.Cfg.UnitTotal = m_Total;

	mPzkIni.ZjPlcFile.Delay.InRecloseTime = m_RelcoseTime;
	mPzkIni.ZjPlcFile.Delay.PlcTime = m_PlcTime;

	mPzkIni.ZjPlcFile.Bzt[0].Enable = (m_BztEnable1)? true : false;
	mPzkIni.ZjPlcFile.Bzt[1].Enable = (m_BztEnable2)? true : false;

	mPzkIni.ZjPlcFile.Cfg.LogicVol = m_LogicVol;

	int num = m_List.GetItemCount();
	for(int i=0; i<num; i++)
	{
		if(m_List.GetItemText(i, 2) == "投入")
			mPzkIni.ZjPlcFile.Reclose.ReClose[i] = true;
		else
			mPzkIni.ZjPlcFile.Reclose.ReClose[i] = false;
	}

	bEverEdited = false;
	mPzkIni.EverModified = true;
}

void CZjPlcCfgView::OnCANCEl()
{
	// TODO: Add your control notification handler code here
	LoadData();
	bEverEdited = false;
}

void CZjPlcCfgView::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult)
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
	if(nSubItem != 2)
		return;

	pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO1);
	pCombo = (CComboBox *)GetDlgItem(IDC_COMBO1);
	if(m_List.GetItemText(nItem, nSubItem) == "投入")
		pCombo->SetCurSel(0);
	else
		pCombo->SetCurSel(1);

	pCombo->SetItemHeight(-1,12);

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

void CZjPlcCfgView::OnKillfocusCombo1()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
	AfxMessageBox("4444444");
	int i = m_ComBo1.GetCurSel();
	if(i == 0)
		m_List.SetItemText(nItem, nSubItem, "投入");
	else
		m_List.SetItemText(nItem, nSubItem, "退出");
	m_ComBo1.ShowWindow(SW_HIDE);
}

LRESULT CZjPlcCfgView::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)
{
//	OnCANCEl();
	return TRUE;
}

LRESULT CZjPlcCfgView::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)
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


void CZjPlcCfgView::OnKillfocusEdit1()
{
	// TODO: Add your control notification handler code here
	UpdateData(UPDATE_READ);
	bEverEdited = true;
	//下面这行明天改过来
	ResetRelcose();
}

void CZjPlcCfgView::OnKillfocusEdit2()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CZjPlcCfgView::OnKillfocusEdit3()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CZjPlcCfgView::OnCheck4()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CZjPlcCfgView::OnChangeNormalvol()
{
	bEverEdited = true;
}

void CZjPlcCfgView::OnBztenable1()
{
	// TODO: Add your control notification handler code here

}

void CZjPlcCfgView::OnBztenable2()
{
	// TODO: Add your control notification handler code here

}
