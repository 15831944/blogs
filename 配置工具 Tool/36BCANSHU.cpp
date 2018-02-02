// 36BCANSHU.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "ReadPzkIni.h"
#include "MyFun.h"
#include "36BCANSHU.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C36BCANSHU
IMPLEMENT_DYNCREATE(C36BCANSHU, CFormView)

C36BCANSHU::C36BCANSHU()
	: CFormView(C36BCANSHU::IDD)
{
	//{{AFX_DATA_INIT(C36BCANSHU)
	m_version = _T("");
	m_createtime = _T("");
	m_flow = 0;
	m_voltage = 0;
	m_cxtime = 0;
	m_PlcEnable = FALSE;
	m_OutNum1 = 0;
	m_OutNum2 = 0;
	m_OOEnable = FALSE;
	m_OTEnable = FALSE;
	m_TOEnable = FALSE;
	m_TTEnable = FALSE;
	m_OneTime = 0;
	m_TwoTime = 0;
	m_mltime1 = 0;
	//}}AFX_DATA_INIT
}

C36BCANSHU::~C36BCANSHU()
{
}

void C36BCANSHU::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C36BCANSHU)
	DDX_Control(pDX, IDC_COMBO1, m_modetype);
	DDX_Control(pDX, IDC_COMBO4, m_Enable);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_EDIT11, m_MLTime);
	DDX_Text(pDX, IDC_EDIT1, m_version);
	DDX_Text(pDX, IDC_EDIT2, m_createtime);
	DDX_Text(pDX, IDC_EDIT5, m_flow);
	DDX_Text(pDX, IDC_EDIT6, m_voltage);
	DDX_Text(pDX, IDC_EDIT10, m_cxtime);
	DDX_Text(pDX, IDC_EDIT11, m_mltime1);
	DDX_Check(pDX, IDC_CHECK1, m_PlcEnable);
	DDX_Text(pDX, IDC_EDIT3, m_OutNum1);
	DDX_Text(pDX, IDC_EDIT4, m_OutNum2);
	DDX_Check(pDX, IDC_CHECK2, m_OOEnable);
	DDX_Check(pDX, IDC_CHECK3, m_OTEnable);
	DDX_Check(pDX, IDC_CHECK4, m_TOEnable);
	DDX_Check(pDX, IDC_CHECK5, m_TTEnable);
	DDX_Check(pDX, IDC_CHECK6, m_MLEnable);
	DDX_Control(pDX, IDC_CHECK6, m_ML);
	DDX_Text(pDX, IDC_EDIT7, m_OneTime);
	DDX_Text(pDX, IDC_EDIT8, m_TwoTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C36BCANSHU, CFormView)
	//{{AFX_MSG_MAP(C36BCANSHU)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_CBN_EDITCHANGE(IDC_COMBO4, OnKillfocusCombo3)
	ON_CBN_KILLFOCUS(IDC_COMBO4, OnKillfocusCombo4)
	ON_EN_KILLFOCUS(IDC_EDIT9, OnKillfocusEdit9)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_CANCEl, OnCANCEl)
	ON_EN_KILLFOCUS(IDC_EDIT3, OnKillfocusEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT4, OnKillfocusEdit4)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT8, OnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT10, OnChangeEdit10)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_CBN_EDITCHANGE(IDC_COMBO1, OnEditchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_EN_CHANGE(IDC_EDIT11, OnChangeEdit11)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C36BCANSHU diagnostics

#ifdef _DEBUG
void C36BCANSHU::AssertValid() const
{
	CFormView::AssertValid();
}

void C36BCANSHU::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C36BCANSHU message handlers

void C36BCANSHU::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	m_version = mPzkIni.ProtFile.Cfg.Version;
	m_createtime = mPzkIni.ProtFile.Cfg.CreateTime;
	m_voltage = mPzkIni.ProtFile.Cfg.VOGE;
	m_flow = mPzkIni.ProtFile.Cfg.CURRENT;
	m_PlcEnable = mPzkIni.ProtFile.Cfg.isuseful;
	m_cxtime = mPzkIni.ProtFile.Cfg.atme.outtime;
	Save_Out1=m_OutNum1 = mPzkIni.ProtFile.Cfg.OutNum1;
	Save_Out2=m_OutNum2 = mPzkIni.ProtFile.Cfg.OutNum2;
	m_OOEnable = mPzkIni.pzkjx[1][1].yesorno;
	m_OTEnable = mPzkIni.pzkjx[1][2].yesorno;
	m_TOEnable = mPzkIni.pzkjx[2][1].yesorno;
	m_TTEnable = mPzkIni.pzkjx[2][2].yesorno;
	m_OneTime = mPzkIni.ProtFile.Cfg.atme.onetime;
	m_TwoTime = mPzkIni.ProtFile.Cfg.atme.twotime;
	m_modetype.AddString("0-进线是断路器，出线是负荷开关");
	m_modetype.AddString("1-进线是负荷开关，出线是断路器");
	m_modetype.AddString("2-进线，出线均是断路器");
	m_modetype.SetCurSel(mPzkIni.ProtFile.Cfg.modetype);

	bEverEdited = false;
	InitListCtrl();
//	m_mltime1 = 0;
	if(mPzkIni.MLValid == 1)
	{
		m_ML.EnableWindow(true);
		m_MLTime.EnableWindow(true);
		m_MLEnable = mPzkIni.pzkml.yesorno;
		m_mltime1 = mPzkIni.pzkml.time;
	}
	UpdateData(UPDATE_WRITE);
}
void C36BCANSHU::InitListCtrl()
{
	int i = 0;
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(i++, "序号", LVCFMT_LEFT, 70, -1);
	m_list.InsertColumn(i++, "名称", LVCFMT_LEFT, 150, -1);
	m_list.InsertColumn(i++, "重合闸使能", LVCFMT_LEFT, 180, -1);
	UpdateData(UPDATE_WRITE);
	LoadProtectConfig();
}
void C36BCANSHU::LoadProtectConfig()
{
	int addItem,i,j;
	int line;
	CString str1;
	m_list.DeleteAllItems();
	line=1;
	jxnum=0;
	for(i=1; i<4; i++)
	{
		for(j=1;j<11;j++)
		{
			if(mPzkIni.pzkcx[i][j].istrue==1)
			{
				addItem = m_list.InsertItem(line, Str(line), 0);
				m_list.SetItemText(addItem, 1, mPzkIni.pzkcx[i][j].name);
				if(1==mPzkIni.pzkcx[i][j].yesorno)
					m_list.SetItemText(addItem, 2, "投入");
				else
					m_list.SetItemText(addItem, 2, "退出");
				line++;
			}
		}
	}
}

void C36BCANSHU::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult)
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
	if(nSubItem == 0)
		return;

	if(nSubItem == 1)
	{
		return;
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO4);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO4);
		pCombo->SetCurSel(m_list.GetItemData(nItem));
	}
	else if(nSubItem == 2)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO4);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO4);
		str = m_list.GetItemText(nItem, nSubItem);
		if(str.Compare("投入") == 0)
			pCombo->SetCurSel(0);
		else
			pCombo->SetCurSel(1);
	}
	else
		return;
	pCombo->SetItemHeight(-1,12);
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

void C36BCANSHU::OnKillfocusCombo3()
{
	// TODO: Add your control notification handler code here
	//这里是多余的
}

void C36BCANSHU::OnKillfocusCombo4()
{
	// TODO: Add your control notification handler code here
	if(m_Enable.GetCurSel() == 0)
	{
		m_list.SetItemText(nItem, 2, "投入");
	}
	else
	{
		m_list.SetItemText(nItem, 2, "退出");
	}
	bEverEdited = true;
	m_Enable.ShowWindow(SW_HIDE);
}

void C36BCANSHU::OnKillfocusEdit9()
{
	// TODO: Add your control notification handler code here
}
LRESULT C36BCANSHU::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)
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
LRESULT C36BCANSHU::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}
void C36BCANSHU::OnSave()
{

	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;
	UpdateData(TRUE);
	int i,j,k=0;
	CString str1,str2;
	CString tr,tc;
	int puanduan[40],pdnum=1,inm;
	UpdateData(UPDATE_READ);
	while(m_list.GetItemText(k,1)!="")
	{
		for (i=0;i<4;i++)
		{
			for (j=0;j<11;j++)
			{
				str1.Format("%d段进线%d", i,j);
				if (str1==m_list.GetItemText(k,1))
				{
					puanduan[pdnum]=myatoi(m_list.GetItemText(k,2));
					pdnum++;
				}
			}
		}
		k++;
	}
	if (pdnum>2)
		for (inm=1;inm<pdnum-1;inm++)
		{
			if(puanduan[inm]<=0 || puanduan[inm]>=puanduan[inm+1])
			{
				AfxMessageBox("重合闸时间应当越来越大！！！");
				OnCANCEl();
				return;
			}
		}

	if (m_voltage<0 || m_flow<0)
	{
		AfxMessageBox("无流无压门槛必须都大于零！！！");
		OnCANCEl();
		return;
	}
	mPzkIni.ProtFile.Cfg.Version = m_version;
	mPzkIni.ProtFile.Cfg.CreateTime = m_createtime;
	mPzkIni.ProtFile.Cfg.VOGE = m_voltage;
	mPzkIni.ProtFile.Cfg.CURRENT = m_flow;
	mPzkIni.ProtFile.Cfg.modetype = m_modetype.GetCurSel();
	mPzkIni.ProtFile.Cfg.atme.outtime = m_cxtime;
	mPzkIni.ProtFile.Cfg.atme.onetime = m_OneTime;
	mPzkIni.ProtFile.Cfg.atme.twotime = m_TwoTime;
	mPzkIni.pzkml.time = m_mltime1;
	mPzkIni.ProtFile.Cfg.OutNum1 = m_OutNum1;
	mPzkIni.ProtFile.Cfg.OutNum2 = m_OutNum2;
    mPzkIni.pzkml.yesorno = m_MLEnable;
	mPzkIni.ProtFile.Cfg.isuseful = (m_PlcEnable)? true : false;
	mPzkIni.pzkjx[1][1].yesorno = (m_OOEnable)? true : false;
	mPzkIni.pzkjx[1][2].yesorno = (m_OTEnable)? true : false;
	mPzkIni.pzkjx[2][1].yesorno = (m_TOEnable)? true : false;
	mPzkIni.pzkjx[2][2].yesorno = (m_TTEnable)? true : false;
	tr="投入";
	tc="退出";
	for (i=1;i<4;i++)
	{
		for (j=1;j<11;j++)
			mPzkIni.pzkcx[i][j].istrue=0;
	}
	k=0;
	while(m_list.GetItemText(k,1)!="")
	{
		for (i=1;i<4;i++)
		{
			for (j=1;j<11;j++)
			{
				str2.Format("%d段出线%d", i,j);
				if (str2==m_list.GetItemText(k,1))
				{
					if (tr==m_list.GetItemText(k,2))
					{
						mPzkIni.pzkcx[i][j].name = str2;
						mPzkIni.pzkcx[i][j].yesorno=1;
						mPzkIni.pzkcx[i][j].istrue = 1;
					}else if (tc==m_list.GetItemText(k,2))
					{
						mPzkIni.pzkcx[i][j].yesorno=0;
						mPzkIni.pzkcx[i][j].istrue = 1;
						mPzkIni.pzkcx[i][j].name = str2;
					}
				}
			}
		}
		k++;
	}
	mPzkIni.SaveToIni();

	bEverEdited = false;
}

void C36BCANSHU::OnCANCEl()
{
	// TODO: Add your control notification handler code here
	m_version = mPzkIni.ProtFile.Cfg.Version;
	m_createtime = mPzkIni.ProtFile.Cfg.CreateTime;
	m_voltage = mPzkIni.ProtFile.Cfg.VOGE;
	m_flow = mPzkIni.ProtFile.Cfg.CURRENT;
	m_modetype.SetCurSel(mPzkIni.ProtFile.Cfg.modetype);
	m_cxtime = mPzkIni.ProtFile.Cfg.atme.outtime;
	UpdateData(UPDATE_WRITE);
	LoadProtectConfig();
}

void C36BCANSHU::OnKillfocusEdit3()
{
	// TODO: Add your control notification handler code here
	UpdateData(UPDATE_READ);
	m_Total = 1 + m_OutNum1 + m_OutNum2;
	if(m_Total > 30)
	{
		m_Total = 30;
		m_OutNum1 = m_Total - 1 - m_OutNum2;
	}
	UpdateData(UPDATE_WRITE);
	if(Save_Out1 != m_OutNum1)
	{
		ResetRelcose(Save_Out1, Save_Out2,m_OutNum1, Save_Out2);
	}
	Save_Out1 = m_OutNum1;
}

void C36BCANSHU::OnKillfocusEdit4()
{
	// TODO: Add your control notification handler code here
	UpdateData(UPDATE_READ);
	m_Total = 1 + m_OutNum1 + m_OutNum2;
	if(m_Total > 22)
	{
		m_Total = 22;
		m_OutNum2 = m_Total - 1 - m_OutNum1;
	}
	UpdateData(UPDATE_WRITE);
	if(Save_Out2 != m_OutNum2)
		ResetRelcose(Save_Out1, Save_Out2, Save_Out1, m_OutNum2);
	Save_Out2 = m_OutNum2;
}
void C36BCANSHU::ResetRelcose(int pOut1, int pOut2,int Out1,  int Out2)
{
	CString name1,str1,str2;
	CString tr="投入";
	CString tc="退出";
	int i,j;
	for (j=0;j<pOut1;j++)
	{
			str1 = m_list.GetItemText(j, 1);
			if (tr==m_list.GetItemText(j,2))
				mPzkIni.pzkcxls[1][j+1].yesorno=1;
			else if (tc==m_list.GetItemText(j,2))
				mPzkIni.pzkcxls[1][j+1].yesorno=0;
			mPzkIni.pzkcxls[1][j+1].name = str1;
			mPzkIni.pzkcxls[1][j+1].istrue = 0;
	}
	for (j=pOut1;j<pOut1+pOut2;j++)
	{
			str1 = m_list.GetItemText(j, 1);
			if (tr==m_list.GetItemText(j,2))
				mPzkIni.pzkcxls[2][j-pOut1+1].yesorno=1;
			else if (tc==m_list.GetItemText(j,2))
				mPzkIni.pzkcxls[2][j-pOut1+1].yesorno=0;
			mPzkIni.pzkcxls[2][j-pOut1+1].name = str1;
			mPzkIni.pzkcxls[2][j-pOut1+1].istrue = 0;
	}
	for (i=1;i<=Out1;i++)
	{
		if(mPzkIni.pzkcxls[1][i].istrue != 1)
		{

		mPzkIni.pzkcxls[1][i].istrue = 1;
//		if (i > pOut1)
//		{
			str1.Format("1段出线%d",i);
			mPzkIni.pzkcxls[1][i].yesorno = 0;
			mPzkIni.pzkcxls[1][i].name = str1;
			mPzkIni.pzkcxls[1][i].istrue = 1;
		}
	}
	for (i=1;i<=Out2;i++)
	{
		if(mPzkIni.pzkcxls[2][i].istrue != 1)
		{
		mPzkIni.pzkcxls[2][i].istrue = 1;
//		if (i > pOut2)
//		{
			str1.Format("2段出线%d",i);
			mPzkIni.pzkcxls[2][i].yesorno = 0;
			mPzkIni.pzkcxls[2][i].name = str1;
			mPzkIni.pzkcxls[2][i].istrue = 1;
//		}
		}
	}

	int addItem;
	int line;
	m_list.DeleteAllItems();
	line=1;
	jxnum=0;
	for(i=1; i<4; i++)
	{
		for(j=1;j<11;j++)
		{
			if(mPzkIni.pzkcxls[i][j].istrue==1)
			{
				addItem = m_list.InsertItem(line, Str(line), 0);
				m_list.SetItemText(addItem, 1, mPzkIni.pzkcxls[i][j].name);
				if(1==mPzkIni.pzkcxls[i][j].yesorno)
					m_list.SetItemText(addItem, 2, "投入");
				else
					m_list.SetItemText(addItem, 2, "退出");
				line++;
			}
		}
	}
	for(i=1; i<4; i++)
	{
		for(j=1;j<11;j++)
		{
			mPzkIni.pzkcxls[i][j].istrue=0;
		}
	}
	//UpdateList(nRec);*/
}

void C36BCANSHU::OnChangeEdit1()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;

}

void C36BCANSHU::OnChangeEdit2()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;

}

void C36BCANSHU::OnChangeEdit8()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;

}

void C36BCANSHU::OnChangeEdit3()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void C36BCANSHU::OnChangeEdit4()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void C36BCANSHU::OnChangeEdit5()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void C36BCANSHU::OnChangeEdit6()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void C36BCANSHU::OnChangeEdit7()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void C36BCANSHU::OnChangeEdit10()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void C36BCANSHU::OnCheck2()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void C36BCANSHU::OnCheck3()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void C36BCANSHU::OnCheck4()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void C36BCANSHU::OnCheck5()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void C36BCANSHU::OnCheck1()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void C36BCANSHU::OnEditchangeCombo1()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void C36BCANSHU::OnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void C36BCANSHU::OnCheck6()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void C36BCANSHU::OnChangeEdit11()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	bEverEdited = true;
}
