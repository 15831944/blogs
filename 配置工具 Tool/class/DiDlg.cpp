// DiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "DiDlg.h"
#include "ReadPzkIni.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern bool bCloseWindow;
/////////////////////////////////////////////////////////////////////////////
// CDiDlg

IMPLEMENT_DYNCREATE(CDiDlg, CFormView)

CDiDlg::CDiDlg()
	: CFormView(CDiDlg::IDD)
{
	//{{AFX_DATA_INIT(CDiDlg)
	m_Check1 = FALSE;
	m_Check10 = FALSE;
	m_Check11 = FALSE;
	m_Check12 = FALSE;
	m_Check13 = FALSE;
	m_Check14 = FALSE;
	m_Check15 = FALSE;
	m_Check16 = FALSE;
	m_Check17 = FALSE;
	m_Check18 = FALSE;
	m_Check9 = FALSE;
	m_Check8 = FALSE;
	m_Check7 = FALSE;
	m_Check6 = FALSE;
	m_Check5 = FALSE;
	m_Check4 = FALSE;
	m_Check32 = FALSE;
	m_Check31 = FALSE;
	m_Check30 = FALSE;
	m_Check3 = FALSE;
	m_Check29 = FALSE;
	m_Check28 = FALSE;
	m_Check27 = FALSE;
	m_Check26 = FALSE;
	m_Check25 = FALSE;
	m_Check24 = FALSE;
	m_Check23 = FALSE;
	m_Check22 = FALSE;
	m_Check21 = FALSE;
	m_Check20 = FALSE;
	m_Check2 = FALSE;
	m_Check19 = FALSE;
	m_Edit1 = 0;
	m_Edit2 = 0;
	//}}AFX_DATA_INIT
}

CDiDlg::~CDiDlg()
{
}

void CDiDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiDlg)
	DDX_Control(pDX, IDC_COMBO1, m_Combo1);
	DDX_Check(pDX, IDC_CHECK1, m_Check1);
	DDX_Check(pDX, IDC_CHECK10, m_Check10);
	DDX_Check(pDX, IDC_CHECK11, m_Check11);
	DDX_Check(pDX, IDC_CHECK12, m_Check12);
	DDX_Check(pDX, IDC_CHECK13, m_Check13);
	DDX_Check(pDX, IDC_CHECK14, m_Check14);
	DDX_Check(pDX, IDC_CHECK15, m_Check15);
	DDX_Check(pDX, IDC_CHECK16, m_Check16);
	DDX_Check(pDX, IDC_CHECK17, m_Check17);
	DDX_Check(pDX, IDC_CHECK18, m_Check18);
	DDX_Check(pDX, IDC_CHECK9, m_Check9);
	DDX_Check(pDX, IDC_CHECK8, m_Check8);
	DDX_Check(pDX, IDC_CHECK7, m_Check7);
	DDX_Check(pDX, IDC_CHECK6, m_Check6);
	DDX_Check(pDX, IDC_CHECK5, m_Check5);
	DDX_Check(pDX, IDC_CHECK4, m_Check4);
	DDX_Check(pDX, IDC_CHECK32, m_Check32);
	DDX_Check(pDX, IDC_CHECK31, m_Check31);
	DDX_Check(pDX, IDC_CHECK30, m_Check30);
	DDX_Check(pDX, IDC_CHECK3, m_Check3);
	DDX_Check(pDX, IDC_CHECK29, m_Check29);
	DDX_Check(pDX, IDC_CHECK28, m_Check28);
	DDX_Check(pDX, IDC_CHECK27, m_Check27);
	DDX_Check(pDX, IDC_CHECK26, m_Check26);
	DDX_Check(pDX, IDC_CHECK25, m_Check25);
	DDX_Check(pDX, IDC_CHECK24, m_Check24);
	DDX_Check(pDX, IDC_CHECK23, m_Check23);
	DDX_Check(pDX, IDC_CHECK22, m_Check22);
	DDX_Check(pDX, IDC_CHECK21, m_Check21);
	DDX_Check(pDX, IDC_CHECK20, m_Check20);
	DDX_Check(pDX, IDC_CHECK2, m_Check2);
	DDX_Check(pDX, IDC_CHECK19, m_Check19);
	DDX_Text(pDX, IDC_EDIT1, m_Edit1);
	DDX_Text(pDX, IDC_EDIT2, m_Edit2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDiDlg, CFormView)
	//{{AFX_MSG_MAP(CDiDlg)
	ON_BN_CLICKED(IDSAVE, OnSave)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_BN_CLICKED(IDC_CHECK10, OnCheck10)
	ON_BN_CLICKED(IDC_CHECK11, OnCheck11)
	ON_BN_CLICKED(IDC_CHECK12, OnCheck12)
	ON_BN_CLICKED(IDC_CHECK13, OnCheck13)
	ON_BN_CLICKED(IDC_CHECK14, OnCheck14)
	ON_BN_CLICKED(IDC_CHECK15, OnCheck15)
	ON_BN_CLICKED(IDC_CHECK16, OnCheck16)
	ON_BN_CLICKED(IDC_CHECK17, OnCheck17)
	ON_BN_CLICKED(IDC_CHECK18, OnCheck18)
	ON_BN_CLICKED(IDC_CHECK19, OnCheck19)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK20, OnCheck20)
	ON_BN_CLICKED(IDC_CHECK21, OnCheck21)
	ON_BN_CLICKED(IDC_CHECK22, OnCheck22)
	ON_BN_CLICKED(IDC_CHECK23, OnCheck23)
	ON_BN_CLICKED(IDC_CHECK24, OnCheck24)
	ON_BN_CLICKED(IDC_CHECK25, OnCheck25)
	ON_BN_CLICKED(IDC_CHECK26, OnCheck26)
	ON_BN_CLICKED(IDC_CHECK27, OnCheck27)
	ON_BN_CLICKED(IDC_CHECK28, OnCheck28)
	ON_BN_CLICKED(IDC_CHECK29, OnCheck29)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK30, OnCheck30)
	ON_BN_CLICKED(IDC_CHECK31, OnCheck31)
	ON_BN_CLICKED(IDC_CHECK32, OnCheck32)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck8)
	ON_BN_CLICKED(IDC_CHECK9, OnCheck9)
	ON_BN_CLICKED(IDREVERT, OnRevert)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnKillfocusEdit2)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiDlg diagnostics

#ifdef _DEBUG
void CDiDlg::AssertValid() const
{
	CFormView::AssertValid();
}

void CDiDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDiDlg message handlers

void CDiDlg::OnInitialUpdate()
{
	int i;
	BOOL mBool;
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	m_Edit1=mPzkIni.mIopCfg.IntRate;
	m_Edit2=mPzkIni.mIopCfg.SoeResolution;

	m_Combo1.SetCurSel(mPzkIni.mIopCfg.StatusWetOption);

	for(i=1;i<17;i++)
	{
		if(mPzkIni.mIopCfg.InputSoeCheck & BitMask[i-1])
			mBool = TRUE;
		else
			mBool = FALSE;

		if(i==16)
			m_Check16 = mBool;
		else if(i==1)
			m_Check1 = mBool;
		else if(i==2)
			m_Check2 = mBool;
		else if(i==3)
			m_Check3 = mBool;
		else if(i==4)
			m_Check4 = mBool;
		else if(i==5)
			m_Check5 = mBool;
		else if(i==6)
			m_Check6 = mBool;
		else if(i==7)
			m_Check7 = mBool;
		else if(i==8)
			m_Check8 = mBool;
		else if(i==9)
			m_Check9 = mBool;
		else if(i==10)
			m_Check10 = mBool;
		else if(i==11)
			m_Check11 = mBool;
		else if(i==12)
			m_Check12 = mBool;
		else if(i==13)
			m_Check13 = mBool;
		else if(i==14)
			m_Check14 = mBool;
		else
			m_Check15 = mBool;
	}

	for(i=1;i<17;i++)
	{
		if(mPzkIni.mIopCfg.SbxSoeCheck & BitMask[i-1])
			mBool = TRUE;
		else
			mBool = FALSE;

		if(i==16)
			m_Check32 = mBool;
		else if(i==1)
			m_Check17 = mBool;
		else if(i==2)
			m_Check18 = mBool;
		else if(i==3)
			m_Check19 = mBool;
		else if(i==4)
			m_Check20 = mBool;
		else if(i==5)
			m_Check21 = mBool;
		else if(i==6)
			m_Check22 = mBool;
		else if(i==7)
			m_Check23 = mBool;
		else if(i==8)
			m_Check24 = mBool;
		else if(i==9)
			m_Check25 = mBool;
		else if(i==10)
			m_Check26 = mBool;
		else if(i==11)
			m_Check27 = mBool;
		else if(i==12)
			m_Check28 = mBool;
		else if(i==13)
			m_Check29 = mBool;
		else if(i==14)
			m_Check30 = mBool;
		else
			m_Check31 = mBool;
	}
	UpdateData(FALSE);
	bEverEdited = false;
}

void CDiDlg::OnSave()
{
	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;
	UpdateData(TRUE);

	mPzkIni.mIopCfg.IntRate = m_Edit1;
	mPzkIni.mIopCfg.SoeResolution = m_Edit2;
	mPzkIni.mIopCfg.StatusWetOption = m_Combo1.GetCurSel();

	mPzkIni.mIopCfg.InputSoeCheck = 0;
	mPzkIni.mIopCfg.SbxSoeCheck = 0;

	if(m_Check1)
		mPzkIni.mIopCfg.InputSoeCheck |= BitMask[0];
	if(m_Check2)
		mPzkIni.mIopCfg.InputSoeCheck |= BitMask[1];
	if(m_Check3)
		mPzkIni.mIopCfg.InputSoeCheck |= BitMask[2];
	if(m_Check4)
		mPzkIni.mIopCfg.InputSoeCheck |= BitMask[3];
	if(m_Check5)
		mPzkIni.mIopCfg.InputSoeCheck |= BitMask[4];
	if(m_Check6)
		mPzkIni.mIopCfg.InputSoeCheck |= BitMask[5];
	if(m_Check7)
		mPzkIni.mIopCfg.InputSoeCheck |= BitMask[6];
	if(m_Check8)
		mPzkIni.mIopCfg.InputSoeCheck |= BitMask[7];
	if(m_Check9)
		mPzkIni.mIopCfg.InputSoeCheck |= BitMask[8];
	if(m_Check10)
		mPzkIni.mIopCfg.InputSoeCheck |= BitMask[9];
	if(m_Check11)
		mPzkIni.mIopCfg.InputSoeCheck |= BitMask[10];
	if(m_Check12)
		mPzkIni.mIopCfg.InputSoeCheck |= BitMask[11];
	if(m_Check13)
		mPzkIni.mIopCfg.InputSoeCheck |= BitMask[12];
	if(m_Check14)
		mPzkIni.mIopCfg.InputSoeCheck |= BitMask[13];
	if(m_Check15)
		mPzkIni.mIopCfg.InputSoeCheck |= BitMask[14];
	if(m_Check16)
		mPzkIni.mIopCfg.InputSoeCheck |= BitMask[15];

	if(m_Check17)
		mPzkIni.mIopCfg.SbxSoeCheck |= BitMask[0];
	if(m_Check18)
		mPzkIni.mIopCfg.SbxSoeCheck |= BitMask[1];
	if(m_Check19)
		mPzkIni.mIopCfg.SbxSoeCheck |= BitMask[2];
	if(m_Check20)
		mPzkIni.mIopCfg.SbxSoeCheck |= BitMask[3];
	if(m_Check21)
		mPzkIni.mIopCfg.SbxSoeCheck |= BitMask[4];
	if(m_Check22)
		mPzkIni.mIopCfg.SbxSoeCheck |= BitMask[5];
	if(m_Check23)
		mPzkIni.mIopCfg.SbxSoeCheck |= BitMask[6];
	if(m_Check24)
		mPzkIni.mIopCfg.SbxSoeCheck |= BitMask[7];
	if(m_Check25)
		mPzkIni.mIopCfg.SbxSoeCheck |= BitMask[8];
	if(m_Check26)
		mPzkIni.mIopCfg.SbxSoeCheck |= BitMask[9];
	if(m_Check27)
		mPzkIni.mIopCfg.SbxSoeCheck |= BitMask[10];
	if(m_Check28)
		mPzkIni.mIopCfg.SbxSoeCheck |= BitMask[11];
	if(m_Check29)
		mPzkIni.mIopCfg.SbxSoeCheck |= BitMask[12];
	if(m_Check30)
		mPzkIni.mIopCfg.SbxSoeCheck |= BitMask[13];
	if(m_Check31)
		mPzkIni.mIopCfg.SbxSoeCheck |= BitMask[14];
	if(m_Check32)
		mPzkIni.mIopCfg.SbxSoeCheck |= BitMask[15];

	bEverEdited = false;
	mPzkIni.EverModified = true;
	return;
}

void CDiDlg::OnCheck1()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnChangeEdit1()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT1);
	char str[32];
	pEdit->GetWindowText(str,32);
	int i = atoi(str);//.GetBuffer(str.GetLength()));
	if( i > 255)
	{
		AfxMessageBox("不允许输入大于255的值!");
		pEdit->SetWindowText("255");
	}
	bEverEdited = true;
}

void CDiDlg::OnCheck10()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck11()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck12()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck13()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck14()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck15()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck16()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck17()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck18()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck19()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck2()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck20()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck21()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck22()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck23()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck24()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck25()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck26()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck27()
{
	bEverEdited = true;
}

void CDiDlg::OnCheck28()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck29()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck3()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck30()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck31()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck32()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck4()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck5()
{
	bEverEdited = true;
}

void CDiDlg::OnCheck6()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck7()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck8()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnCheck9()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

BOOL CDiDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	int i;
	try
	{
		if(bEverEdited)
		{
			i = AfxMessageBox("您已经修改了遥信量配置，在退出该配置前确定要保存吗？",MB_YESNOCANCEL);
			if(i == IDYES)
				OnSave();
			else if(i == IDCANCEL)
			{
				bCloseWindow = false;
				return TRUE;
			}
		}
		return CFormView::DestroyWindow();
	}

	catch(CException e)
	{
		throw;
	}

}

LRESULT CDiDlg::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)
{
	if(bEverEdited)
	{
		int i = AfxMessageBox("保存当前对遥信量配置所做的更改吗？",MB_YESNOCANCEL);
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

void CDiDlg::OnRevert()
{
	// TODO: Add your control notification handler code here
	if(!bEverEdited)
		return;

	UpdateData(FALSE);
	bEverEdited = false;
}

LRESULT CDiDlg::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)
{
	OnRevert();
	return TRUE;
}

void CDiDlg::OnChangeEdit2()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT2);
	char str[32];
	pEdit->GetWindowText(str,32);
	int i = atoi(str);//.GetBuffer(str.GetLength()));
	if( i > 255)
	{
		AfxMessageBox("不允许输入大于255的值!");
		pEdit->SetWindowText("255");
	}
	bEverEdited = true;
}

void CDiDlg::OnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CDiDlg::OnKillfocusEdit1()
{
	// TODO: Add your control notification handler code here
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT1);
	char str[32];
	pEdit->GetWindowText(str,32);
	if(strlen(str) == 0)
	{
		pEdit->SetWindowText("0");
		return;
	}
}

void CDiDlg::OnKillfocusEdit2()
{
	// TODO: Add your control notification handler code here
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT2);
	char str[32];
	pEdit->GetWindowText(str,32);
	if(strlen(str) == 0)
	{
		pEdit->SetWindowText("0");
		return;
	}
}
