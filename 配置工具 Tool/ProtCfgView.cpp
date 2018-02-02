// ProtCfgView.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "ReadPzkIni.h"
#include "MyFun.h"
#include "ProtCfgView.h"
#include "ProItemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CToolTipCtrl m_ToolTipCtrl1;
//CToolTipCtrl m_ToolTipCtrl2;
//CToolTipCtrl m_ToolTipCtrl3;
CString ProtectName[] = {	"��������",
							"ʧѹ����",
							"���籸Ͷ",
							"ProtectType3",
							"ZeroCurrent",

							"SmallI_3U0",
							"_SmallI_3I0",
							"�غ�բ",
							"������ʧѹ",
							"�����",

							"Enable_PLC",
							"Zʱ�ޱ���",
							"ProtectType12",
							"ProtectType13",
							"ProtectType14",
							"ProtectType15",

							"ProtectType16",
							"ProtectType17",
							"ProtectType18",
							"ProtectType19",
							"ProtectType20"

							"ProtectType21",
							"ProtectType22",
							"ProtectType23",
							"ProtectType24",
							"ProtectType25"

							"ProtectType26",
							"ProtectType27",
							"ProtectType28",
							"ProtectType29",
							"ProtectType30"

							"ProtectType31",
							"ProtectType32"
};

/////////////////////////////////////////////////////////////////////////////
// CProtCfgView

IMPLEMENT_DYNCREATE(CProtCfgView, CFormView)

CProtCfgView::CProtCfgView()
	: CFormView(CProtCfgView::IDD)
{
	//{{AFX_DATA_INIT(CProtCfgView)
	m_Version = _T("");
	m_CreateTime = _T("");
	m_LineNum = 0;
	m_PNumPerLine = 0;
	m_SboNo = 0;
	m_SwitchNo = 0;
	m_FixActTime = mPzkIni.ProtFile.Cfg.FixActTime;
	m_Remote = 0;
	m_SboNo = mPzkIni.ProtFile.Cfg.Switch_Remote;
	m_SwitchNo = mPzkIni.ProtFile.Cfg.Switch_Local;
	CMode = mPzkIni.ProtFile.Cfg.V_ConnectMode;
	//}}AFX_DATA_INIT
	bEverEdited = false;
	/*
	for(int i=0; i<_Max_Prot_Line; i++)
	{
	//	mSbo[i] = mPzkIni.ProtFile.Line[i].LineCfg.Line_Sbo;
		m_SboNo[i] = mPzkIni.ProtFile.Cfg.FixActTime;
	//	m_SboNo[i] = mPzkIni.ProtFile.Cfg.Switch_Remote;
		m_SwitchNo[i] = mPzkIni.ProtFile.Cfg.Switch_Local;
		mMode[i] = mPzkIni.ProtFile.Cfg.V_ConnectMode;
	}
	*/
}

CProtCfgView::~CProtCfgView()
{
}

void CProtCfgView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProtCfgView)
	DDX_Control(pDX, IDC_LIST9, m_List9);
	DDX_Control(pDX, IDC_LIST32, m_List32);
	DDX_Control(pDX, IDC_LIST31, m_List31);
	DDX_Control(pDX, IDC_LIST30, m_List30);
	DDX_Control(pDX, IDC_LIST29, m_List29);
	DDX_Control(pDX, IDC_LIST28, m_List28);
	DDX_Control(pDX, IDC_LIST27, m_List27);
	DDX_Control(pDX, IDC_LIST26, m_List26);
	DDX_Control(pDX, IDC_LIST25, m_List25);
	DDX_Control(pDX, IDC_LIST24, m_List24);
	DDX_Control(pDX, IDC_LIST23, m_List23);
	DDX_Control(pDX, IDC_LIST22, m_List22);
	DDX_Control(pDX, IDC_LIST21, m_List21);
	DDX_Control(pDX, IDC_LIST20, m_List20);
	DDX_Control(pDX, IDC_LIST19, m_List19);
	DDX_Control(pDX, IDC_LIST18, m_List18);
	DDX_Control(pDX, IDC_LIST17, m_List17);
	DDX_Control(pDX, IDC_LIST16, m_List16);
	DDX_Control(pDX, IDC_LIST15, m_List15);
	DDX_Control(pDX, IDC_LIST14, m_List14);
	DDX_Control(pDX, IDC_LIST13, m_List13);
	DDX_Control(pDX, IDC_LIST12, m_List12);
	DDX_Control(pDX, IDC_LIST11, m_List11);
	DDX_Control(pDX, IDC_LIST10, m_List10);
	DDX_Control(pDX, IDC_LIST8, m_List8);
	DDX_Control(pDX, IDC_LIST7, m_List7);
	DDX_Control(pDX, IDC_LIST6, m_List6);
	DDX_Control(pDX, IDC_EDIT9, m_Input);
	DDX_Control(pDX, IDC_COMBO3, m_Enable);
	DDX_Control(pDX, IDC_COMBO4, m_ProtType);
	DDX_Control(pDX, IDC_LIST5, m_List5);
	DDX_Control(pDX, IDC_LIST4, m_List4);
	DDX_Control(pDX, IDC_LIST3, m_List3);
	DDX_Control(pDX, IDC_LIST2, m_List2);
	DDX_Check(pDX, IDC_CHECK1, m_Check1);
	DDX_Check(pDX, IDC_CHECK2, m_Check2);
	DDX_Control(pDX, IDC_COMBO2, m_ConnectMode);
	DDX_Control(pDX, IDC_COMBO1, m_LineNo);
	DDX_Control(pDX, IDC_LIST1, m_List1);
	DDX_Text(pDX, IDC_EDIT1, m_Version);
	DDX_Text(pDX, IDC_EDIT2, m_CreateTime);
	DDX_Text(pDX, IDC_EDIT3, m_LineNum);
	DDX_Text(pDX, IDC_EDIT4, m_PNumPerLine);
	DDX_Text(pDX, IDC_EDIT5, m_SboNo);
	DDX_Text(pDX, IDC_EDIT6, m_SwitchNo);
	DDX_Text(pDX, IDC_EDIT21, m_FixActTime);
	DDX_Text(pDX, IDC_EDIT7, m_Remote);
	DDX_Text(pDX, IDC_EDIT8, m_Local);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProtCfgView, CFormView)
	//{{AFX_MSG_MAP(CProtCfgView)
	ON_EN_KILLFOCUS(IDC_EDIT3, OnKillfocusEdit3)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, OnClickList2)
	ON_NOTIFY(NM_CLICK, IDC_LIST3, OnClickList3)
	ON_NOTIFY(NM_CLICK, IDC_LIST4, OnClickList4)
	ON_NOTIFY(NM_CLICK, IDC_LIST5, OnClickList5)
	ON_BN_CLICKED(IDSAVE, OnSave)
	ON_EN_KILLFOCUS(IDC_EDIT4, OnKillfocusEdit4)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, OnChangeEdit8)
	ON_CBN_KILLFOCUS(IDC_COMBO3, OnKillfocusCombo3)
	ON_CBN_KILLFOCUS(IDC_COMBO4, OnKillfocusCombo4)
	ON_EN_KILLFOCUS(IDC_EDIT9, OnKillfocusEdit9)
	ON_EN_KILLFOCUS(IDC_EDIT5, OnKillfocusEdit5)
	ON_EN_KILLFOCUS(IDC_EDIT6, OnKillfocusEdit6)
	ON_EN_KILLFOCUS(IDC_EDIT7, OnKillfocusEdit7)
	ON_EN_KILLFOCUS(IDC_EDIT8, OnKillfocusEdit8)
	ON_CBN_KILLFOCUS(IDC_COMBO2, OnKillfocusCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_NOTIFY(NM_CLICK, IDC_LIST6, OnClickList6)
	ON_NOTIFY(NM_CLICK, IDC_LIST7, OnClickList7)
	ON_NOTIFY(NM_CLICK, IDC_LIST8, OnClickList8)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_EN_KILLFOCUS(IDC_EDIT21, OnKillfocusEdit21)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_EN_CHANGE(IDC_EDIT21, OnChangeEdit21)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_CANCEl, OnCancel)
	ON_NOTIFY(NM_CLICK, IDC_LIST9, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST10, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST11, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST12, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST13, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST14, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST15, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST16, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST17, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST18, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST19, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST20, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST21, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST22, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST23, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST24, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST25, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST26, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST27, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST28, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST29, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST30, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST31, OnClickList8)
	ON_NOTIFY(NM_CLICK, IDC_LIST32, OnClickList8)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProtCfgView diagnostics

#ifdef _DEBUG
void CProtCfgView::AssertValid() const
{
	CFormView::AssertValid();
}

void CProtCfgView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProtCfgView message handlers
void CProtCfgView::SetListFocus(int no)
{
	for(int i=0; i<_Max_Prot_Line; i++)
	{
		if(i == no)
			listArray[i]->ShowWindow(SW_SHOW);
		else
			listArray[i]->ShowWindow(SW_HIDE);
	}
}


/*void CProtCfgView::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	CMenu menu,*pSubMenu;//��������Ҫ�õ���cmenu����
    menu.LoadMenu(IDR_RTU_MENU);//װ���Զ�����Ҽ��˵�
    pSubMenu=menu.GetSubMenu(0);//��ȡ��һ�������˵������Ե�һ���˵��������Ӳ˵�
    CPoint oPoint;//����һ������ȷ�����λ�õ�λ��
    GetCursorPos(&oPoint);//��ȡ��ǰ����λ�ã��Ա�ʹ�ò˵����Ը�����
    pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,oPoint.x,oPoint.y,this);   //��ָ��λ����ʾ�����˵�
	*pResult = 0;
}
*/

/*
void CProtCfgView::OnMenuitem32801()//���һ����Ϣִ�к���
{

	CProItemDlg tempdlg;
	//LineNo = m_LineNo.GetCurSel();

	if(tempdlg.DoModal()==IDOK)
	{
	//	mPzkIni.ProtFile.Line[LineNo].LineCfg.LineNum++;//����·����1 //���ָ�ֵ
	//	m_LineNum=mPzkIni.ProtFile.Line[LineNo].LineCfg.LineNum;//��������
	//	UpdateData(FALSE);//������������
	//	LoadFaultConfig();//����load
	}
}
*/

void CProtCfgView::LoadProtectConfig()
{
	int i;
	int addItem;
	for(int LineNo=0; LineNo<_Max_Prot_Line; LineNo++)
	{
		listArray[LineNo]->DeleteAllItems();
		for(i=0; i<m_PNumPerLine; i++)
		{
			addItem = listArray[LineNo]->InsertItem(i, Str(i), 0);
			listArray[LineNo]->SetItemData(addItem, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type);
			listArray[LineNo]->SetItemText(addItem, 1, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Name);//ProtectName[mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type]);
			if(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Enable == 255)
				listArray[LineNo]->SetItemText(addItem, 2, "Ͷ��");
			else if(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Enable == 1)
				listArray[LineNo]->SetItemText(addItem, 2, "�澯");
			else if(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Enable == 0)
				listArray[LineNo]->SetItemText(addItem, 2, "�˳�");
			listArray[LineNo]->SetItemText(addItem, 3, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value));
			listArray[LineNo]->SetItemText(addItem, 4, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Time));
			listArray[LineNo]->SetItemText(addItem, 5, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Unit);
		}
	}
}

void CProtCfgView::InitListCtrl()
{
	int i=0;
	CSize sz;

	sz.cx = sz.cy = 30;
/*	m_List1.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List1.ApproximateViewRect(sz,1);
	m_List1.InsertColumn(i++, "���", LVCFMT_LEFT, 50, -1);
	m_List1.InsertColumn(i++, "����", LVCFMT_LEFT, 120, -1);
	m_List1.InsertColumn(i++, "Ͷ/��", LVCFMT_CENTER, 80, -1);
	m_List1.InsertColumn(i++, "��ֵ", LVCFMT_RIGHT, 100, -1);
	m_List1.InsertColumn(i++, "ʱ��(ms)", LVCFMT_RIGHT, 100, -1);
	m_List1.InsertColumn(i++, "��ֵ��λ/��ע", LVCFMT_RIGHT, 100, -1);

	i = 0;
	m_List2.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List2.ApproximateViewRect(sz,1);
	m_List2.InsertColumn(i++, "���", LVCFMT_LEFT, 50, -1);
	m_List2.InsertColumn(i++, "����", LVCFMT_LEFT, 120, -1);
	m_List2.InsertColumn(i++, "Ͷ/��", LVCFMT_CENTER, 80, -1);
	m_List2.InsertColumn(i++, "��ֵ", LVCFMT_RIGHT, 100, -1);
	m_List2.InsertColumn(i++, "ʱ��(ms)", LVCFMT_RIGHT, 100, -1);
	m_List2.InsertColumn(i++, "��ֵ��λ/��ע", LVCFMT_RIGHT, 100, -1);

	i = 0;
	m_List3.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List3.ApproximateViewRect(sz,1);
	m_List3.InsertColumn(i++, "���", LVCFMT_LEFT, 50, -1);
	m_List3.InsertColumn(i++, "����", LVCFMT_LEFT, 120, -1);
	m_List3.InsertColumn(i++, "Ͷ/��", LVCFMT_CENTER, 80, -1);
	m_List3.InsertColumn(i++, "��ֵ", LVCFMT_RIGHT, 100, -1);
	m_List3.InsertColumn(i++, "ʱ��(ms)", LVCFMT_RIGHT, 100, -1);
	m_List3.InsertColumn(i++, "��ֵ��λ/��ע", LVCFMT_RIGHT, 100, -1);

	i = 0;
	m_List4.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List4.ApproximateViewRect(sz,1);
	m_List4.InsertColumn(i++, "���", LVCFMT_LEFT, 50, -1);
	m_List4.InsertColumn(i++, "����", LVCFMT_LEFT, 120, -1);
	m_List4.InsertColumn(i++, "Ͷ/��", LVCFMT_CENTER, 80, -1);
	m_List4.InsertColumn(i++, "��ֵ", LVCFMT_RIGHT, 100, -1);
	m_List4.InsertColumn(i++, "ʱ��(ms)", LVCFMT_RIGHT, 100, -1);
	m_List4.InsertColumn(i++, "��ֵ��λ/��ע", LVCFMT_RIGHT, 100, -1);

	i = 0;
	m_List5.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List5.ApproximateViewRect(sz,1);
	m_List5.InsertColumn(i++, "���", LVCFMT_LEFT, 50, -1);
	m_List5.InsertColumn(i++, "����", LVCFMT_LEFT, 120, -1);
	m_List5.InsertColumn(i++, "Ͷ/��", LVCFMT_CENTER, 80, -1);
	m_List5.InsertColumn(i++, "��ֵ", LVCFMT_RIGHT, 100, -1);
	m_List5.InsertColumn(i++, "ʱ��(ms)", LVCFMT_RIGHT, 100, -1);
	m_List5.InsertColumn(i++, "��ֵ��λ/��ע", LVCFMT_RIGHT, 100, -1);

	i = 0;
	m_List5.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List5.ApproximateViewRect(sz,1);
	m_List5.InsertColumn(i++, "���", LVCFMT_LEFT, 50, -1);
	m_List5.InsertColumn(i++, "����", LVCFMT_LEFT, 120, -1);
	m_List5.InsertColumn(i++, "Ͷ/��", LVCFMT_CENTER, 80, -1);
	m_List5.InsertColumn(i++, "��ֵ", LVCFMT_RIGHT, 100, -1);
	m_List5.InsertColumn(i++, "ʱ��(ms)", LVCFMT_RIGHT, 100, -1);
	m_List5.InsertColumn(i++, "��ֵ��λ/��ע", LVCFMT_RIGHT, 100, -1);

	i = 0;
	m_List5.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List5.ApproximateViewRect(sz,1);
	m_List5.InsertColumn(i++, "���", LVCFMT_LEFT, 50, -1);
	m_List5.InsertColumn(i++, "����", LVCFMT_LEFT, 120, -1);
	m_List5.InsertColumn(i++, "Ͷ/��", LVCFMT_CENTER, 80, -1);
	m_List5.InsertColumn(i++, "��ֵ", LVCFMT_RIGHT, 100, -1);
	m_List5.InsertColumn(i++, "ʱ��(ms)", LVCFMT_RIGHT, 100, -1);
	m_List5.InsertColumn(i++, "��ֵ��λ/��ע", LVCFMT_RIGHT, 100, -1);

	i = 0;
	m_List5.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_List5.ApproximateViewRect(sz,1);
	m_List5.InsertColumn(i++, "���", LVCFMT_LEFT, 50, -1);
	m_List5.InsertColumn(i++, "����", LVCFMT_LEFT, 120, -1);
	m_List5.InsertColumn(i++, "Ͷ/��", LVCFMT_CENTER, 80, -1);
	m_List5.InsertColumn(i++, "��ֵ", LVCFMT_RIGHT, 100, -1);
	m_List5.InsertColumn(i++, "ʱ��(ms)", LVCFMT_RIGHT, 100, -1);
	m_List5.InsertColumn(i++, "��ֵ��λ/��ע", LVCFMT_RIGHT, 100, -1);
*/
	listArray[0] = &m_List1;
	listArray[1] = &m_List2;
	listArray[2] = &m_List3;
	listArray[3] = &m_List4;
	listArray[4] = &m_List5;
	listArray[5] = &m_List6;
	listArray[6] = &m_List7;
	listArray[7] = &m_List8;
	listArray[8] = &m_List9;
	listArray[9] = &m_List10;
	listArray[10] = &m_List11;
	listArray[11] = &m_List12;
	listArray[12] = &m_List13;
	listArray[13] = &m_List14;
	listArray[14] = &m_List15;
	listArray[15] = &m_List16;
	listArray[16] = &m_List17;
	listArray[17] = &m_List18;
	listArray[18] = &m_List19;
	listArray[19] = &m_List20;
	listArray[20] = &m_List21;
	listArray[21] = &m_List22;
	listArray[22] = &m_List23;
	listArray[23] = &m_List24;
	listArray[24] = &m_List25;
	listArray[25] = &m_List26;
	listArray[26] = &m_List27;
	listArray[27] = &m_List28;
	listArray[28] = &m_List29;
	listArray[29] = &m_List30;
	listArray[30] = &m_List31;
	listArray[31] = &m_List32;


	for(int j=0; j<_Max_Prot_Line; j++)
	{
		listArray[j]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		listArray[j]->ApproximateViewRect(sz,1);
		listArray[j]->InsertColumn(i++, "���", LVCFMT_LEFT, 40, -1);
		listArray[j]->InsertColumn(i++, "����", LVCFMT_LEFT, 130, -1);
		listArray[j]->InsertColumn(i++, "Ͷ/��", LVCFMT_CENTER, 80, -1);
		listArray[j]->InsertColumn(i++, "��ֵ", LVCFMT_RIGHT, 80, -1);
		listArray[j]->InsertColumn(i++, "ʱ��(s)", LVCFMT_RIGHT, 90, -1);
		listArray[j]->InsertColumn(i++, "��ֵ��λ/��ע", LVCFMT_RIGHT, 151, -1);
	}

	CRect rect;
	listArray[0]->GetWindowRect(&rect);
//	listArray[0]->GetWindowRgn
//	rect.top -= 71;
//	rect.bottom -= 71;
	rect.top -= 80;
	rect.bottom -= 80;
	for(i=0; i<_Max_Prot_Line; i++)
		listArray[i]->MoveWindow(rect, TRUE);
	LoadProtectConfig();
}

void CProtCfgView::OnInitialUpdate()
{

	EnableToolTips(TRUE);


	// m_StaticText1.Create(_T("����򻯽���"), WS_CHILD|SS_NOTIFY|WS_VISIBLE, //CRect(665,165,760,180),this);
		// CRect(190,165,260,180),this);


	// m_StaticText2.Create(_T("				"), WS_CHILD|SS_NOTIFY|WS_VISIBLE, //CRect(665,165,745,180),this);
    //    CRect(305,165,385,180),this);
	// m_StaticText3.Create(_T("				"), WS_CHILD|SS_NOTIFY|WS_VISIBLE,// CRect(665,165,725,180),this);

    //   CRect(435,165,495,180),this);


	CFormView::OnInitialUpdate();
	int i = 0;

	// TODO: Add your specialized code here and/or call the base class

	//m_ConnectMode.AddString("����򻯽���ģʽ(��UabΪһ���ѹ��UcbΪ��һ���ѹ)");
	//m_ConnectMode.AddString("������ȫ����ģʽ(��2J12Ϊһ���ѹ��2J13Ϊ��һ���ѹ)");
//	m_ConnectMode.AddString("���ͽ���ģʽ(��2J12Ϊһ���ѹ)");

	//m_ConnectMode.SetCurSel(CMode);

	//���õڼ�����ѡ��ѡ��
	if(CMode==0)
		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(1);
	else if(CMode ==1)
		((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(1);
	else if(CMode ==2)
		((CButton *)GetDlgItem(IDC_RADIO4))->SetCheck(1);
	else
		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(1);


	m_ToolTipCtrl1.Create(this);
	m_ToolTipCtrl1.AddTool(GetDlgItem(IDC_RADIO2),_T("һ���ߵ�ѹUab���ն˵�U1a����,��һ���ߵ�ѹUcb���ն˵�U1c����"));//���
	m_ToolTipCtrl1.AddTool(GetDlgItem(IDC_RADIO3),_T("һ�������ѹ���ն˵�U1a/U1b/U1c,��һ�������ѹ���ն˵�U2a/U2b/U2c"));//���
	m_ToolTipCtrl1.AddTool(GetDlgItem(IDC_RADIO4),_T("�����ѹ���ն˵�U1a/U1b/U1c"));//���
	m_ToolTipCtrl1.SetMaxTipWidth(300);
	m_ToolTipCtrl1.Activate(TRUE);
	m_ToolTipCtrl1.SetDelayTime(TTDT_INITIAL, 0);
	m_ToolTipCtrl1.SetDelayTime(TTDT_AUTOPOP, 90000);
	//m_ToolTipCtrl1.SetDelayTime(500); //���õ�����ʾ��Ϣ����þ���ʧ

	//ToolTip ����ؼ�����Ҫ�ж�����λ�ã��Լ�����ʱ��⣬һ����������ؼ�����ͻ���ʾ�����ȥ����
	 //onmousemove����
	//for(i=0; i<32; i++)
	//	m_ProtType.AddString(ProtectName[i]);


	m_Version = mPzkIni.ProtFile.Cfg.Version;
	m_CreateTime = mPzkIni.ProtFile.Cfg.CreateTime;
	m_LineNum = mPzkIni.ProtFile.Cfg.LineNum;
	m_PNumPerLine = mPzkIni.ProtFile.Cfg.PNPL;

	/*
	if(mPzkIni.ProtFile.Cfg.ControlWByte[0] == 1)
	{
		m_Check2 = true;
	}
	else
	{
		m_Check2 = false;
	}
	if(mPzkIni.ProtFile.Cfg.ControlWByte[1] == 1)
	{
		m_Check1 = true;
	}
	else
	{
		m_Check1 = false;
	}
	*/

	if(mPzkIni.ProtFile.Cfg.Prot_YXEnable == 255)
	{
		m_Check2 = true;
	}
	else
	{
		m_Check2 = false;
	}
	if(mPzkIni.ProtFile.Cfg.Prot_MsgEnable == 255)
	{
		m_Check1 = true;
	}
	else
	{
		m_Check1 = false;
	}

	m_Local = mPzkIni.ProtFile.Line[0].LineCfg.Line_Switch;


	UpdateData(UPDATE_WRITE);
	InitListCtrl();

	if(m_LineNum > 0)
	{
		CString formatStr;
		for(i=1; i<=m_LineNum; i++)
		{
			formatStr.Format("��·%d", i);
			m_LineNo.AddString(formatStr);
		}
		SetListFocus(0);
		m_LineNo.SetCurSel(0);
	}
	//OnSelchangeCombo1();
}

void CProtCfgView::OnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	int LineNo;
//	int i;

//	int addItem;

	LineNo = m_LineNo.GetCurSel();
	/*
	m_SboNo = mSbo[LineNo];//mPzkIni.ProtFile.Line[LineNo].LineCfg.Line_Sbo;
	m_SwitchNo = mSwitch[LineNo];//mPzkIni.ProtFile.Line[LineNo].LineCfg.Line_Switch;
	m_Remote = mRemote[LineNo];//mPzkIni.ProtFile.Line[LineNo].LineCfg.Line_Switch_Remote;
	m_Local = mLocal[LineNo];//mPzkIni.ProtFile.Line[LineNo].LineCfg.Line_Switch_Local;
//	m_ConnectMode.SetCurSel(CMode);//mPzkIni.ProtFile.Line[LineNo].LineCfg.V_ConnectMode);
*/
	m_Local = mPzkIni.ProtFile.Line[LineNo].LineCfg.Line_Switch;

	UpdateData(UPDATE_WRITE);


	SetListFocus(LineNo);
}

void CProtCfgView::OnKillfocusEdit3()
{
	// TODO: Add your control notification handler code here
	int CurLine = m_LineNo.GetCurSel();

	UpdateData(UPDATE_READ);
/*	if(m_LineNum > _Max_Prot_Line)
	{
		AfxMessageBox("�����·�����ܳ���"+Str(_Max_Prot_Line)+"!");
		m_LineNum = _Max_Prot_Line;
		UpdateData(UPDATE_WRITE);
	}
*/
	if(m_LineNum > _Max_Prot_Line)
	{
		AfxMessageBox("�����·�����ܳ���"+Str(_Max_Prot_Line)+Str("��!"));
		m_LineNum = _Max_Prot_Line;
		UpdateData(UPDATE_WRITE);
	}

	if(m_LineNum <= 0)
	{
		AfxMessageBox("��С��·������С��"+Str(1)+Str("��!"));
		m_LineNum = 1;
		UpdateData(UPDATE_WRITE);
	}

	m_LineNo.ResetContent();
	if(m_LineNum > 0)
	{
		CString formatStr;
		for(int i=1; i<=m_LineNum; i++)
		{
			formatStr.Format("��·%d", i);
			m_LineNo.AddString(formatStr);
		}
		if( (m_LineNo.GetCount() > CurLine) && (CurLine > 0) )
			m_LineNo.SetCurSel(CurLine);
		else
		{
			m_LineNo.SetCurSel(0);
			OnSelchangeCombo1();
		}
	}
	else
	{
		if(CurLine >= 0)
			listArray[CurLine]->ShowWindow(SW_HIDE);
	}
}

int CProtCfgView::CheckNum(CString str)
{
	int NumFlag=0;//0 is ok
	bool FloatFlag=false;
	for(int i=0;i<str.GetLength();i++)
	{
		if((int)(str.GetAt(i))>=48 && (int)(str.GetAt(i))<=57)
			continue;
		else if(str.GetAt(i)=='.')
		{
			if(FloatFlag == false)
			{
				FloatFlag = true;
				continue;
			}
			else
			{
				NumFlag = 1;//����1��С����
				break;
			}
		}
		else
		{
			NumFlag = 2;//��������
			break;
		}
	}

	return NumFlag;
}


void CProtCfgView::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	CString srr;
	CString CheckStr;
	bool Check;
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

	if(nSubItem == 0)
		return;

	if(nSubItem == 1)
	{
		return;
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO4);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO4);
		pCombo->SetCurSel(m_List1.GetItemData(nItem));
	}
	else if(nSubItem == 2)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO3);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO3);
		str = m_List1.GetItemText(nItem, nSubItem);
		if(str.Compare("Ͷ��") == 0)
			pCombo->SetCurSel(0);
		else if(str.Compare("�澯") == 0)
			pCombo->SetCurSel(1);
		else if(str.Compare("�˳�") == 0)
			pCombo->SetCurSel(2);
	}
	else if(nSubItem != 5 )
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT9);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT9);
		m_Input.SetWindowText(m_List1.GetItemText(nItem, nSubItem));
	}
	else
		return;

//	if(nItem ==0)
	//	return;

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

void CProtCfgView::OnClickList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CString str;
	CComboBox *pCombo;
	HWND pWnd;
	Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST2);
    LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
    RECT rect;
    //get the row number
    nItem = temp->iItem;
    //get the column number
    nSubItem = temp->iSubItem;
	if(nItem < 0)
		return;
	if(nSubItem == 0)
		return;

	if(nSubItem == 1)
	{
		return;
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO4);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO4);
		pCombo->SetCurSel(m_List2.GetItemData(nItem));
	}
	else if(nSubItem == 2)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO3);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO3);
		str = m_List2.GetItemText(nItem, nSubItem);
		if(str.Compare("Ͷ��") == 0)
			pCombo->SetCurSel(0);
		else if(str.Compare("�澯") == 0)
			pCombo->SetCurSel(1);
		else if(str.Compare("�˳�") == 0)
			pCombo->SetCurSel(2);
	}
	else if(nSubItem != 5)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT9);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT9);
		m_Input.SetWindowText(m_List2.GetItemText(nItem, nSubItem));
	}
	else
		return;

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

void CProtCfgView::OnClickList3(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CString str;
	CComboBox *pCombo;
	HWND pWnd;
	Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST3);
    LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
    RECT rect;
    //get the row number
    nItem = temp->iItem;
    //get the column number
    nSubItem = temp->iSubItem;
	if(nItem < 0)
		return;
	if(nSubItem == 0)
		return;

	if(nSubItem == 1)
	{
		return;
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO4);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO4);
		pCombo->SetCurSel(m_List3.GetItemData(nItem));
	}
	else if(nSubItem == 2)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO3);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO3);
		str = m_List3.GetItemText(nItem, nSubItem);
		if(str.Compare("Ͷ��") == 0)
			pCombo->SetCurSel(0);
		else if(str.Compare("�澯") == 0)
			pCombo->SetCurSel(1);
		else if(str.Compare("�˳�") == 0)
			pCombo->SetCurSel(2);
	}
	else if(nSubItem != 5)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT9);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT9);
		m_Input.SetWindowText(m_List3.GetItemText(nItem, nSubItem));
	}
	else
		return;

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

void CProtCfgView::OnClickList4(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CString str;
	CComboBox *pCombo;
	HWND pWnd;
	Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST4);
    LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
    RECT rect;
    //get the row number
    nItem = temp->iItem;
    //get the column number
    nSubItem = temp->iSubItem;
	if(nItem < 0)
		return;
	if(nSubItem == 0)
		return;

	if(nSubItem == 1)
	{
		return;
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO4);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO4);
		pCombo->SetCurSel(m_List4.GetItemData(nItem));
	}
	else if(nSubItem == 2)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO3);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO3);
		str = m_List4.GetItemText(nItem, nSubItem);
		if(str.Compare("Ͷ��") == 0)
			pCombo->SetCurSel(0);
		else if(str.Compare("�澯") == 0)
			pCombo->SetCurSel(1);
		else if(str.Compare("�˳�") == 0)
			pCombo->SetCurSel(2);
	}
	else if(nSubItem != 5)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT9);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT9);
		m_Input.SetWindowText(m_List4.GetItemText(nItem, nSubItem));
	}
	else
		return;


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

void CProtCfgView::OnClickList5(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CString str;
	CComboBox *pCombo;
	HWND pWnd;
	Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST5);
    LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
    RECT rect;
    //get the row number
    nItem = temp->iItem;
    //get the column number
    nSubItem = temp->iSubItem;
	if(nItem < 0)
		return;
	if(nSubItem == 0)
		return;

	if(nSubItem == 1)
	{
		return;
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO4);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO4);
		pCombo->SetCurSel(m_List5.GetItemData(nItem));
	}
	else if(nSubItem == 2)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO3);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO3);
		str = m_List5.GetItemText(nItem, nSubItem);
		if(str.Compare("Ͷ��") == 0)
			pCombo->SetCurSel(0);
		else if(str.Compare("�澯") == 0)
			pCombo->SetCurSel(1);
		else if(str.Compare("�˳�") == 0)
			pCombo->SetCurSel(2);
	}
	else if(nSubItem != 5)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT9);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT9);
		m_Input.SetWindowText(m_List5.GetItemText(nItem, nSubItem));
	}
	else
		return;

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

LRESULT CProtCfgView::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)
{
//	OnCANCEl();
	return TRUE;
}

LRESULT CProtCfgView::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)
{
	if(bEverEdited)
	{
		int i = AfxMessageBox("���浱ǰ�Ա����������������޸���",MB_YESNOCANCEL);
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

void CProtCfgView::OnSave()
{
	// TODO: Add your control notification handler code here
	int i,j;

	UpdateData(UPDATE_READ);
	mPzkIni.ProtFile.Cfg.Version = m_Version;
	mPzkIni.ProtFile.Cfg.CreateTime = m_CreateTime;
	mPzkIni.ProtFile.Cfg.LineNum = m_LineNum;
	mPzkIni.ProtFile.Cfg.FixActTime = m_FixActTime;
	mPzkIni.ProtFile.Cfg.Switch_Local = m_SwitchNo;
	mPzkIni.ProtFile.Cfg.Switch_Remote = m_SboNo;
	mPzkIni.ProtFile.Cfg.PNPL = m_PNumPerLine;
	mPzkIni.ProtFile.Cfg.V_ConnectMode=CMode;

	/*
	if(m_Check1 == true)
	    mPzkIni.ProtFile.Cfg.ControlWByte[1] = 1;
	else
        mPzkIni.ProtFile.Cfg.ControlWByte[1] = 0;
	if(m_Check2 == true)
	    mPzkIni.ProtFile.Cfg.ControlWByte[0] = 1;
	else
        mPzkIni.ProtFile.Cfg.ControlWByte[0] = 0;
	*/

	if(m_Check1 == true)
	    mPzkIni.ProtFile.Cfg.Prot_MsgEnable = 255;
	else
        mPzkIni.ProtFile.Cfg.Prot_MsgEnable = 0;

	if(m_Check2 == true)
	    mPzkIni.ProtFile.Cfg.Prot_YXEnable = 255;
	else
        mPzkIni.ProtFile.Cfg.Prot_YXEnable = 0;

	for(i=0; i<mPzkIni.ProtFile.Cfg.LineNum; i++)
	{
		/*     ���б�����ʽ�ֵ����ã���ÿһ����·��������Զ���͵ء����߷�ʽ������
		mPzkIni.ProtFile.Line[i].LineCfg.Line_Sbo = mSbo[i];
		mPzkIni.ProtFile.Line[i].LineCfg.Line_Switch = mSwitch[i];
		mPzkIni.ProtFile.Line[i].LineCfg.Line_Switch_Remote = mRemote[i];
		mPzkIni.ProtFile.Line[i].LineCfg.Line_Switch_Local = mLocal[i];
		mPzkIni.ProtFile.Line[i].LineCfg.V_ConnectMode = mMode[i];
		*/

		for(j=0; j<m_PNumPerLine; j++)
		{
			mPzkIni.ProtFile.Line[i].ProtItem[j].Type = listArray[i]->GetItemData(j);
			if(listArray[i]->GetItemText(j,2) == "Ͷ��")
				mPzkIni.ProtFile.Line[i].ProtItem[j].Enable = 255;
			else if(listArray[i]->GetItemText(j,2) == "�澯")
				mPzkIni.ProtFile.Line[i].ProtItem[j].Enable = 1;
			else if(listArray[i]->GetItemText(j,2) == "�˳�")
				mPzkIni.ProtFile.Line[i].ProtItem[j].Enable = 0;
			mPzkIni.ProtFile.Line[i].ProtItem[j].Value = myatof(listArray[i]->GetItemText(j,3));
			mPzkIni.ProtFile.Line[i].ProtItem[j].Time = myatof(listArray[i]->GetItemText(j,4));

		//	mPzkIni.ProtFile.Line[i].ProtItem[j].Name =listArray[i]->GetItemText(j,1);//add by lz
		//	mPzkIni.ProtFile.Line[i].ProtItem[j].Unit =listArray[i]->GetItemText(j,5);//add by lz

		}
	}
	bEverEdited = false;
	mPzkIni.EverModified = true;
}

void CProtCfgView::OnCancel()
{
	// TODO: Add your control notification handler code here
	int i;

	m_Version = mPzkIni.ProtFile.Cfg.Version;
	m_CreateTime = mPzkIni.ProtFile.Cfg.CreateTime;
	m_LineNum = mPzkIni.ProtFile.Cfg.LineNum;
	m_PNumPerLine = mPzkIni.ProtFile.Cfg.PNPL;

	for(i=0; i<5; i++)
	{
		mSbo[i] = mPzkIni.ProtFile.Line[i].LineCfg.Line_Sbo;
		mSwitch[i] = mPzkIni.ProtFile.Line[i].LineCfg.Line_Switch;
		mRemote[i] = mPzkIni.ProtFile.Line[i].LineCfg.Line_Switch_Remote;
		mLocal[i] = mPzkIni.ProtFile.Line[i].LineCfg.Line_Switch_Local;
		mMode[i] = mPzkIni.ProtFile.Line[i].LineCfg.V_ConnectMode;

	}

	UpdateData(UPDATE_WRITE);

	if(m_LineNum > 0)
	{
		CString formatStr;
		m_LineNo.ResetContent();
		for(i=1; i<=m_LineNum; i++)
		{
			formatStr.Format("��·%d", i);
			m_LineNo.AddString(formatStr);
		}
		SetListFocus(0);
		m_LineNo.SetCurSel(0);
	}
	else
		SetListFocus(-1);
	LoadProtectConfig();
	OnSelchangeCombo1();
	bEverEdited = false;
}

void CProtCfgView::OnKillfocusEdit4()
{
	// TODO: Add your control notification handler code here
	UpdateData(UPDATE_READ);
	if(m_PNumPerLine > 32)
	{
		AfxMessageBox("ÿ����·����󱣻������ܳ���32��!");
		m_PNumPerLine = 32;
		UpdateData(UPDATE_WRITE);
	}
	int LineNo;
	int addItem;
	for(LineNo=0; LineNo<5; LineNo++)
	{
		listArray[LineNo]->DeleteAllItems();
		for(int i=0; i<m_PNumPerLine; i++)
		{
			addItem = listArray[LineNo]->InsertItem(i, Str(i), 0);
			listArray[LineNo]->SetItemData(addItem, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type);
			listArray[LineNo]->SetItemText(addItem, 1, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Name);//ProtectName[mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Type]);
			if(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Enable == 255)
				listArray[LineNo]->SetItemText(addItem, 2, "Ͷ��");
			else if(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Enable == 1)
				listArray[LineNo]->SetItemText(addItem, 2, "�˳�");
			else if(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Enable == 0)
				listArray[LineNo]->SetItemText(addItem, 2, "�˳�");
			listArray[LineNo]->SetItemText(addItem, 3, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Value));
			listArray[LineNo]->SetItemText(addItem, 4, Str(mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Time));
			listArray[LineNo]->SetItemText(addItem, 5, mPzkIni.ProtFile.Line[LineNo].ProtItem[i].Unit);
		}
	}
	bEverEdited = false;
}

void CProtCfgView::OnChangeEdit1()
{
	bEverEdited = true;
}

void CProtCfgView::OnChangeEdit2()
{
	bEverEdited = true;
}

void CProtCfgView::OnChangeEdit3()
{
	bEverEdited = true;
}

void CProtCfgView::OnChangeEdit4()
{
	bEverEdited = true;
}

void CProtCfgView::OnChangeEdit5()
{
	bEverEdited = true;
}
void CProtCfgView::OnChangeEdit6()
{
	bEverEdited = true;
}

void CProtCfgView::OnChangeEdit7()
{
	bEverEdited = true;
}

void CProtCfgView::OnChangeEdit8()
{
	bEverEdited = true;
}

void CProtCfgView::OnKillfocusCombo3()
{
	// TODO: Add your control notification handler code here
	if(m_Enable.GetCurSel() == 0)
		listArray[m_LineNo.GetCurSel()]->SetItemText(nItem, nSubItem, "Ͷ��");
	else if(m_Enable.GetCurSel() == 1)
		listArray[m_LineNo.GetCurSel()]->SetItemText(nItem, nSubItem, "�澯");
	else if(m_Enable.GetCurSel() == 2)
		listArray[m_LineNo.GetCurSel()]->SetItemText(nItem, nSubItem, "�˳�");
	m_Enable.ShowWindow(SW_HIDE);
	bEverEdited = true;
}

void CProtCfgView::OnKillfocusCombo4()
{
	// TODO: Add your control notification handler code here
	int LineNo = m_LineNo.GetCurSel();
	listArray[m_LineNo.GetCurSel()]->SetItemText(nItem, nSubItem, ProtectName[m_ProtType.GetCurSel()]);
	listArray[m_LineNo.GetCurSel()]->SetItemData(nItem, m_ProtType.GetCurSel());
	listArray[m_LineNo.GetCurSel()]->SetItemText(nItem, 5, mPzkIni.ProtFile.Line[LineNo].ProtItem[m_ProtType.GetCurSel()].Unit);
	m_ProtType.ShowWindow(SW_HIDE);
	bEverEdited = true;
}

void CProtCfgView::OnKillfocusEdit9()
{
	// TODO: Add your control notification handler code here
	CString str;
	m_Input.GetWindowText(str);
	int flag = CheckNum(str);
	if(flag == 1)//����1��С����
	{
		AfxMessageBox("��������ȷ�����ݸ�ʽ!");
	}
	else if(flag == 2)//��������
	{
		AfxMessageBox("��������ȷ������!");
	}
	else //0 is OK
	{
		listArray[m_LineNo.GetCurSel()]->SetItemText(nItem, nSubItem, str);
		m_Input.ShowWindow(SW_HIDE);
		bEverEdited = true;
	}
}

void CProtCfgView::OnKillfocusEdit5()
{
	// TODO: Add your control notification handler code here
	UpdateData(UPDATE_READ);
	if(m_SboNo > 63)
	{
		AfxMessageBox("���Զ������ң�źŲ��ܳ���"+Str(63));
		m_SboNo = 63;
		UpdateData(UPDATE_WRITE);
	}
	if(m_SboNo < 0)
	{
		AfxMessageBox("��СԶ������ң�źŲ���С��"+Str(0));
		m_SboNo = 0;
		UpdateData(UPDATE_WRITE);
	}


	int LineNo = m_LineNo.GetCurSel();
	if(LineNo < 0)
		return;
	UpdateData(UPDATE_READ);
	mSbo[LineNo] = m_SboNo;
}

void CProtCfgView::OnKillfocusEdit6()
{
	// TODO: Add your control notification handler code here
	UpdateData(UPDATE_READ);
	if(m_SwitchNo > 63)
	{
		AfxMessageBox("���͵ز���ң�źŲ��ܳ���"+Str(63));
		m_SwitchNo = 63;
		UpdateData(UPDATE_WRITE);
	}
	if(m_SwitchNo < 0)
	{
		AfxMessageBox("��С�͵ز���ң�źŲ���С��"+Str(0));
		m_SwitchNo = 0;
		UpdateData(UPDATE_WRITE);
	}

	int LineNo = m_LineNo.GetCurSel();
	if(LineNo < 0)
		return;
	UpdateData(UPDATE_READ);
	mSwitch[LineNo] = m_SwitchNo;
}

void CProtCfgView::OnKillfocusEdit7()
{
	// TODO: Add your control notification handler code here
	int LineNo = m_LineNo.GetCurSel();
	if(LineNo < 0)
		return;
	UpdateData(UPDATE_READ);
	mRemote[LineNo] = m_Remote;
}

void CProtCfgView::OnKillfocusEdit8()
{
	UpdateData(UPDATE_READ);
	if(m_Local > 63)
	{
		AfxMessageBox("��󿪹�״̬�����ܳ���"+Str(63));
		m_Local = 63;
		UpdateData(UPDATE_WRITE);
	}
	if(m_Local < 0)
	{
		AfxMessageBox("��С����״̬������С��"+Str(0));
		m_Local = 0;
		UpdateData(UPDATE_WRITE);
	}

	// TODO: Add your control notification handler code here
	int LineNo;
	CString str;
	UpdateData(UPDATE_READ);
	LineNo = m_LineNo.GetCurSel();
    mPzkIni.ProtFile.Line[LineNo].LineCfg.Line_Switch = m_Local;
}

void CProtCfgView::OnKillfocusCombo2()
{
	// TODO: Add your control notification handler code here
	int LineNo = m_LineNo.GetCurSel();
	if(LineNo < 0)
		return;
	//mMode[LineNo] = m_ConnectMode.GetCurSel();
	CMode = m_ConnectMode.GetCurSel();
	//CString str;
	//str.Format("%d",CMode);
//	AfxMessageBox(str);
}

void CProtCfgView::OnSelchangeCombo2()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CProtCfgView::OnClickList6(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CString str;
	CComboBox *pCombo;
	HWND pWnd;
	Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST6);
    LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
    RECT rect;
    //get the row number
    nItem = temp->iItem;
    //get the column number
    nSubItem = temp->iSubItem;
	if(nItem < 0)
		return;
	if(nSubItem == 0)
		return;

	if(nSubItem == 1)
	{
		return;
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO4);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO4);
		pCombo->SetCurSel(m_List6.GetItemData(nItem));
	}
	else if(nSubItem == 2)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO3);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO3);
		str = m_List6.GetItemText(nItem, nSubItem);
		if(str.Compare("Ͷ��") == 0)
			pCombo->SetCurSel(0);
		else if(str.Compare("�澯") == 0)
			pCombo->SetCurSel(1);
		else if(str.Compare("�˳�") == 0)
			pCombo->SetCurSel(2);
	}
	else if(nSubItem != 5)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT9);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT9);
		m_Input.SetWindowText(m_List6.GetItemText(nItem, nSubItem));
	}
	else
		return;

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

void CProtCfgView::OnClickList7(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CString str;
	CComboBox *pCombo;
	HWND pWnd;
	Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST7);
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
		pCombo->SetCurSel(m_List7.GetItemData(nItem));
	}
	else if(nSubItem == 2)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO3);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO3);
		str = m_List7.GetItemText(nItem, nSubItem);
		if(str.Compare("Ͷ��") == 0)
			pCombo->SetCurSel(0);
		else if(str.Compare("�澯") == 0)
			pCombo->SetCurSel(1);
		else if(str.Compare("�˳�") == 0)
			pCombo->SetCurSel(2);
	}
	else if(nSubItem != 5)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT9);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT9);
		m_Input.SetWindowText(m_List7.GetItemText(nItem, nSubItem));
	}
	else
		return;

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

void CProtCfgView::OnClickList8(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CString str;
	CComboBox *pCombo;
	HWND pWnd;
	Invalidate();
	//HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST8);
	int LineNo = m_LineNo.GetCurSel();
	if( (LineNo < 0) || (LineNo >= _Max_Prot_Line) )
		return;
	HWND hWnd1 = listArray[LineNo]->m_hWnd;
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
		pCombo->SetCurSel(listArray[LineNo]->GetItemData(nItem));
	}
	else if(nSubItem == 2)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO3);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO3);
		str = listArray[LineNo]->GetItemText(nItem, nSubItem);
		if(str.Compare("Ͷ��") == 0)
			pCombo->SetCurSel(0);
		else if(str.Compare("�澯") == 0)
			pCombo->SetCurSel(1);
		else if(str.Compare("�˳�") == 0)
			pCombo->SetCurSel(2);
	}
	else if(nSubItem != 5)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT9);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT9);
		m_Input.SetWindowText(listArray[LineNo]->GetItemText(nItem, nSubItem));
	}
	else
		return;

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

void CProtCfgView::OnCheck2()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CProtCfgView::OnCheck1()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

/*void CProtCfgView::OnRButtonDown(UINT nFlags, CPoint point)
{

	// TODO: Add your message handler code here and/or call default

	CMenu menu,*pSubMenu;//��������Ҫ�õ���cmenu����
    menu.LoadMenu(IDR_RTU_MENU);//װ���Զ�����Ҽ��˵�
	 CPoint oPoint;//����һ������ȷ�����λ�õ�λ��
    GetCursorPos(&oPoint);//��ȡ��ǰ����λ�ã��Ա�ʹ�ò˵����Ը�����
    pSubMenu=menu.GetSubMenu(0);//��ȡ��һ�������˵������Ե�һ���˵��������Ӳ˵�
    //	pSubMenu->EnableMenuItem(IDR_OBJPASTE, MF_ENABLED);
    pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,oPoint.x,oPoint.y,this,0);   //��ָ��λ
	//CFormView::OnRButtonDown(nFlags, point);
}
*/

void CProtCfgView::OnKillfocusEdit21()
{
	// TODO: Add your control notification handler code here
	UpdateData(UPDATE_READ);
	if(m_FixActTime > 45)
	{
		AfxMessageBox("������ʱ�䲻�ܳ���"+Str(45)+Str("ms"));
		m_FixActTime = 45;
		UpdateData(UPDATE_WRITE);
	}
	if(m_FixActTime < 30)
	{
		AfxMessageBox("��С����ʱ�䲻��С��"+Str(30)+Str("ms"));
		m_FixActTime = 30;
		UpdateData(UPDATE_WRITE);
	}

}

void CProtCfgView::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult)
{
/*	//NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	CString srr;
	CString CheckStr;
	bool Check;
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
	if(nSubItem == 3 || nSubItem == 4)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT9);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT9);
		//m_Input.SetWindowText(m_List1.GetItemText(nItem, nSubItem));
		CheckStr=m_List1.GetItemText(nItem, nSubItem);
		AfxMessageBox(CheckStr);
		Check=CheckNum(CheckStr);
		if(Check == false)
		{
			AfxMessageBox("��������");
		}
		else
			m_Input.SetWindowText(CheckStr);

	}
	else
		return ;

	*pResult = 0;*/
}

void CProtCfgView::OnChangeEdit21()
{
	bEverEdited = true;
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here

}

void CProtCfgView::OnRadio4()
{
	// TODO: Add your control notification handler code here
	((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(0);//
	((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(0);//
	((CButton *)GetDlgItem(IDC_RADIO4))->SetCheck(1);//
	CMode=2;
	bEverEdited = true;
//	EnableToolTips(TRUE);
//	m_ToolTipCtrl.Create(this);
//	CWnd* pW=GetDlgItem(IDC_RADIO4);//�õ�����ָ��
//	m_ToolTipCtrl.AddTool(pW,"�����ѹ���ն˵�U1a/U1b/U1c");//���
//	m_ToolTipCtrl.SetMaxTipWidth(300);
//	m_ToolTipCtrl.Activate(TRUE);
//	m_ToolTipCtrl.SetDelayTime(500); //���õ�����ʾ��Ϣ����þ���ʧ
}

void CProtCfgView::OnRadio3()
{
	// TODO: Add your control notification handler code here
	((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(0);//
	((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(1);//
	((CButton *)GetDlgItem(IDC_RADIO4))->SetCheck(0);//
	CMode=1;
	bEverEdited = true;
//	EnableToolTips(TRUE);
//	m_ToolTipCtrl.Create(this);
///	CWnd* pW=GetDlgItem(IDC_RADIO3);//�õ�����ָ��
//	m_ToolTipCtrl.AddTool(pW,"һ�������ѹ���ն˵�U1a/U1b/U1c����һ�������ѹ���ն˵�U2a/U2b/U2c");//���
//	m_ToolTipCtrl.SetMaxTipWidth(300);
//	m_ToolTipCtrl.Activate(TRUE);
//	m_ToolTipCtrl.SetDelayTime(500); //���õ�����ʾ��Ϣ����þ���ʧ
}

void CProtCfgView::OnRadio2()
{
	// TODO: Add your control notification handler code here
	((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(1);//
	((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(0);//
	((CButton *)GetDlgItem(IDC_RADIO4))->SetCheck(0);//
	CMode=0;
	bEverEdited = true;
//	EnableToolTips(TRUE);
//	m_ToolTipCtrl.Create(this);
//	CWnd* pW=GetDlgItem(IDC_RADIO2);//�õ�����ָ��
//	m_ToolTipCtrl.AddTool(pW,"һ���ߵ�ѹUab���ն˵�U1a���ӣ���һ���ߵ�ѹUcb���ն˵�U1c����");//���
//	m_ToolTipCtrl.SetMaxTipWidth(300);
//	m_ToolTipCtrl.Activate(TRUE);
//	m_ToolTipCtrl.SetDelayTime(500); //���õ�����ʾ��Ϣ����þ���ʧ




}
BOOL CProtCfgView::PreTranslateMessage(MSG* pMsg)
{
//	AfxMessageBox("000");
//	ASSERT(pMsg != NULL);
//if (pMsg->message == WM_MOUSEMOVE )//|| pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_LBUTTONUP)
//	if (pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_LBUTTONUP)

	//AfxMessageBox("000");
//	if(pMsg->message == WM_MOUSEMOVE)

	//m_ToolTipCtrl2.RelayEvent(pMsg);
	//m_ToolTipCtrl3.RelayEvent(pMsg);

	if(IsWindow(m_ToolTipCtrl1.m_hWnd))
	{
		m_ToolTipCtrl1.RelayEvent(pMsg);
	}
	 //	m_ToolTipCtrl1.RelayEvent(pMsg);
	return CFormView::PreTranslateMessage(pMsg);

//CFormView
}


void CProtCfgView::OnMouseMove(UINT nFlags, CPoint point) //��ȡ���λ�� //����ʹ��
{
/*	// TODO: Add your message handler code here and/or call default
//	AfxMessageBox("111");


//	CRect rect_Cemian1;
//	CRect rect_Cemian2;
//	CRect rect_Cemian3;
//	GetDlgItem(IDC_STATIC99)->GetWindowRect(rect_Cemian1);
//	GetDlgItem(IDC_STATIC100)->GetWindowRect(rect_Cemian2);
//	GetDlgItem(IDC_STATIC101)->GetWindowRect(rect_Cemian3);

//	ScreenToClient(rect_Cemian1);
//	ScreenToClient(rect_Cemian2);
//	ScreenToClient(rect_Cemian3);



//	if (PtInRect(&rect_Cemian1,point))
//	{
//	AfxMessageBox("1");

//		m_ToolTipCtrl1.Create(this);
		m_ToolTipCtrl1.AddTool(&m_StaticText1,_T("һ���ߵ�ѹUab���ն˵�U1a����,��һ���ߵ�ѹUcb���ն˵�U1c����"));//���
		m_ToolTipCtrl1.SetMaxTipWidth(300);
		m_ToolTipCtrl1.Activate(TRUE);

		m_ToolTipCtrl1.SetDelayTime(TTDT_INITIAL, 0);
		//m_ToolTipCtrl1.SetDelayTime(TTDT_AUTOPOP, 300);

		m_ToolTipCtrl1.SetDelayTime(300); //���õ�����ʾ��Ϣ����þ���ʧ
	}
	else if(PtInRect(&rect_Cemian2,point))
	{
	//		AfxMessageBox("2");
		m_ToolTipCtrl1.Create(this);
		m_ToolTipCtrl1.AddTool(&m_StaticText2,_T("һ�������ѹ���ն˵�U1a/U1b/U1c,��һ�������ѹ���ն˵�U2a/U2b/U2c"));//���
		m_ToolTipCtrl1.SetMaxTipWidth(300);
		m_ToolTipCtrl1.Activate(TRUE);


		m_ToolTipCtrl1.SetDelayTime(TTDT_INITIAL, 0);
	//	m_ToolTipCtrl1.SetDelayTime(TTDT_AUTOPOP, 300);
		m_ToolTipCtrl1.SetDelayTime(300); //���õ�����ʾ��Ϣ����þ���ʧ
	//EnableToolTips(FALSE);
	}
	else if(PtInRect(&rect_Cemian3,point))
	{
	//	AfxMessageBox("3");
		m_ToolTipCtrl1.Create(this);
		m_ToolTipCtrl1.AddTool(&m_StaticText3,_T("�����ѹ���ն˵�U1a/U1b/U1c"));//���
		m_ToolTipCtrl1.SetMaxTipWidth(300);
		m_ToolTipCtrl1.Activate(TRUE);


		m_ToolTipCtrl1.SetDelayTime(TTDT_INITIAL, 0);
	//	m_ToolTipCtrl1.SetDelayTime(TTDT_AUTOPOP, 300);
		m_ToolTipCtrl1.SetDelayTime(300); //���õ�����ʾ��Ϣ����þ���ʧ


	}
*/
	CFormView::OnMouseMove(nFlags, point);
}
