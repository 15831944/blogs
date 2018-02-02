// Pzk300U.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "Pzk300U.h"
#include "MyFun.h"
#include "ReadPzkIni.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern bool bCloseWindow;

#define UPDATE_WRITE FALSE
#define UPDATE_READ	 TRUE
/////////////////////////////////////////////////////////////////////////////
// CPzk300U

IMPLEMENT_DYNCREATE(CPzk300U, CFormView)

CPzk300U::CPzk300U()
	: CFormView(CPzk300U::IDD)
{
	//{{AFX_DATA_INIT(CPzk300U)
	m_OverA = FALSE;
	m_OverB = FALSE;
	m_OverC = FALSE;
	m_LoseA = FALSE;
	m_LoseB = FALSE;
	m_LoseC = FALSE;
	m_OverVA = 0;
	m_OverVB = 0;
	m_OverVC = 0;
	m_LoseVA = 0;
	m_LoseVB = 0;
	m_LoseVC = 0;
	//}}AFX_DATA_INIT
	bEverEdited = false;
}

CPzk300U::~CPzk300U()
{
}

void CPzk300U::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPzk300U)
	DDX_Check(pDX, IDC_CHECK1, m_OverA);
	DDX_Check(pDX, IDC_CHECK2, m_OverB);
	DDX_Check(pDX, IDC_CHECK3, m_OverC);
	DDX_Check(pDX, IDC_CHECK4, m_LoseA);
	DDX_Check(pDX, IDC_CHECK5, m_LoseB);
	DDX_Check(pDX, IDC_CHECK6, m_LoseC);
	DDX_Text(pDX, IDC_EDIT1, m_OverVA);
	DDX_Text(pDX, IDC_EDIT2, m_OverVB);
	DDX_Text(pDX, IDC_EDIT3, m_OverVC);
	DDX_Text(pDX, IDC_EDIT4, m_LoseVA);
	DDX_Text(pDX, IDC_EDIT5, m_LoseVB);
	DDX_Text(pDX, IDC_EDIT6, m_LoseVC);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPzk300U, CFormView)
	//{{AFX_MSG_MAP(CPzk300U)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_CANCEl, OnCancel)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnKillfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT3, OnKillfocusEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT4, OnKillfocusEdit4)
	ON_EN_KILLFOCUS(IDC_EDIT5, OnKillfocusEdit5)
	ON_EN_KILLFOCUS(IDC_EDIT6, OnKillfocusEdit6)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPzk300U diagnostics

#ifdef _DEBUG
void CPzk300U::AssertValid() const
{
	CFormView::AssertValid();
}

void CPzk300U::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPzk300U message handlers

void CPzk300U::OnSave()
{
	// TODO: Add your control notification handler code here
	UpdateData(UPDATE_READ);
	mPzkIni.mPzk300CfgBuf.U1.Valid = mPzkIni.mPzk300CfgBuf.U2.Valid = 0;
	if(m_OverA)
		mPzkIni.mPzk300CfgBuf.U1.Valid |= BitMask[0];
	if(m_OverB)
		mPzkIni.mPzk300CfgBuf.U1.Valid |= BitMask[1];
	if(m_OverC)
		mPzkIni.mPzk300CfgBuf.U1.Valid |= BitMask[2];

	if(m_LoseA)
		mPzkIni.mPzk300CfgBuf.U2.Valid |= BitMask[0];
	if(m_LoseB)
		mPzkIni.mPzk300CfgBuf.U2.Valid |= BitMask[1];
	if(m_LoseC)
		mPzkIni.mPzk300CfgBuf.U2.Valid |= BitMask[2];

	mPzkIni.mPzk300CfgBuf.U1.Val[0] = m_OverVA;
	mPzkIni.mPzk300CfgBuf.U1.Val[1] = m_OverVB;
	mPzkIni.mPzk300CfgBuf.U1.Val[2] = m_OverVC;
	mPzkIni.mPzk300CfgBuf.U2.Val[0] = m_LoseVA;
	mPzkIni.mPzk300CfgBuf.U2.Val[1] = m_LoseVB;
	mPzkIni.mPzk300CfgBuf.U2.Val[2] = m_LoseVC;

	bEverEdited = false;
	mPzkIni.EverModified = true;
}

void CPzk300U::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	if(mPzkIni.mPzk300CfgBuf.U1.Valid & BitMask[0])
		m_OverA = TRUE;
	else
		m_OverA	= FALSE;

	if(mPzkIni.mPzk300CfgBuf.U1.Valid & BitMask[1])
		m_OverB = TRUE;
	else
		m_OverB	= FALSE;

	if(mPzkIni.mPzk300CfgBuf.U1.Valid & BitMask[2])
		m_OverC = TRUE;
	else
		m_OverC	= FALSE;

	if(mPzkIni.mPzk300CfgBuf.U2.Valid & BitMask[0])
		m_LoseA = TRUE;
	else
		m_LoseA = FALSE;

	if(mPzkIni.mPzk300CfgBuf.U2.Valid & BitMask[1])
		m_LoseB = TRUE;
	else
		m_LoseB = FALSE;

	if(mPzkIni.mPzk300CfgBuf.U2.Valid & BitMask[2])
		m_LoseC = TRUE;
	else
		m_LoseC = FALSE;

	m_OverVA = mPzkIni.mPzk300CfgBuf.U1.Val[0];
	m_OverVB = mPzkIni.mPzk300CfgBuf.U1.Val[1];
	m_OverVC = mPzkIni.mPzk300CfgBuf.U1.Val[2];
	m_LoseVA = mPzkIni.mPzk300CfgBuf.U2.Val[0];
	m_LoseVB = mPzkIni.mPzk300CfgBuf.U2.Val[1];
	m_LoseVC = mPzkIni.mPzk300CfgBuf.U2.Val[2];

	UpdateData(UPDATE_WRITE);
}

void CPzk300U::OnCancel()
{
	// TODO: Add your control notification handler code here
	if(mPzkIni.mPzk300CfgBuf.U1.Valid & BitMask[0])
		m_OverA = TRUE;
	else
		m_OverA	= FALSE;

	if(mPzkIni.mPzk300CfgBuf.U1.Valid & BitMask[1])
		m_OverB = TRUE;
	else
		m_OverB	= FALSE;

	if(mPzkIni.mPzk300CfgBuf.U1.Valid & BitMask[2])
		m_OverC = TRUE;
	else
		m_OverC	= FALSE;

	if(mPzkIni.mPzk300CfgBuf.U2.Valid & BitMask[0])
		m_LoseA = TRUE;
	else
		m_LoseA = FALSE;

	if(mPzkIni.mPzk300CfgBuf.U2.Valid & BitMask[1])
		m_LoseB = TRUE;
	else
		m_LoseB = FALSE;

	if(mPzkIni.mPzk300CfgBuf.U2.Valid & BitMask[2])
		m_LoseC = TRUE;
	else
		m_LoseC = FALSE;

	m_OverVA = mPzkIni.mPzk300CfgBuf.U1.Val[0];
	m_OverVB = mPzkIni.mPzk300CfgBuf.U1.Val[1];
	m_OverVC = mPzkIni.mPzk300CfgBuf.U1.Val[2];
	m_LoseVA = mPzkIni.mPzk300CfgBuf.U2.Val[0];
	m_LoseVB = mPzkIni.mPzk300CfgBuf.U2.Val[1];
	m_LoseVC = mPzkIni.mPzk300CfgBuf.U2.Val[2];

	UpdateData(UPDATE_WRITE);
	bEverEdited = false;
}

LRESULT CPzk300U::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)
{
	if(bEverEdited)
	{
		int i = AfxMessageBox("您已经修改了交流输入量配置，在退出该配置前确定要保存吗？",MB_YESNOCANCEL);
		if(i == IDYES)
			OnSave();
		else if(i == IDCANCEL)
		{
//			bCloseWindow = false;
			return FALSE;
		}
		else
			OnCancel();
	}
	bEverEdited = false;
	return TRUE;
}

LRESULT CPzk300U::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)
{
	OnCancel();
	return TRUE;
}

BOOL CPzk300U::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	int i;
	try
	{
		if(bEverEdited)
		{
			i = AfxMessageBox("您已经修改了交流输入量配置，在退出该配置前确定要保存吗？",MB_YESNOCANCEL);
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
	return CFormView::DestroyWindow();
}

void CPzk300U::OnCheck1()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300U::OnCheck2()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300U::OnCheck3()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300U::OnCheck4()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300U::OnCheck5()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300U::OnCheck6()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300U::OnKillfocusEdit1()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300U::OnKillfocusEdit2()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300U::OnKillfocusEdit3()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300U::OnKillfocusEdit4()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300U::OnKillfocusEdit5()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300U::OnKillfocusEdit6()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}
