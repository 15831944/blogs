// Pzk300Cfg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "Pzk300Cfg.h"
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
// CPzk300Cfg

IMPLEMENT_DYNCREATE(CPzk300Cfg, CFormView)

CPzk300Cfg::CPzk300Cfg()
	: CFormView(CPzk300Cfg::IDD)
{
	//{{AFX_DATA_INIT(CPzk300Cfg)
	m_pw = _T("");
	m_addr = _T("");
	m_ct1 = 0;
	m_wp = 0.0f;
	m_wq = 0.0f;
	m_u3 = 0;
	m_u4 = 0;
	m_i0 = 0;
	m_thdu = 0;
	m_cos = 0.0f;
	m_k = 0.0f;
	m_td = 0;
	m_powercut = 0;
	m_ct2 = 0;
	//}}AFX_DATA_INIT
	bEverEdited = false;
}

CPzk300Cfg::~CPzk300Cfg()
{
}

void CPzk300Cfg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPzk300Cfg)
	DDX_Control(pDX, IDC_COMBO1, m_hormanic);
	DDX_Text(pDX, IDC_EDIT1, m_pw);
	DDV_MaxChars(pDX, m_pw, 3);
	DDX_Text(pDX, IDC_EDIT2, m_addr);
	DDV_MaxChars(pDX, m_addr, 4);
	DDX_Text(pDX, IDC_EDIT3, m_ct1);
	DDX_Text(pDX, IDC_EDIT5, m_wp);
	DDX_Text(pDX, IDC_EDIT6, m_wq);
	DDX_Text(pDX, IDC_EDIT7, m_u3);
	DDX_Text(pDX, IDC_EDIT8, m_u4);
	DDX_Text(pDX, IDC_EDIT9, m_i0);
	DDX_Text(pDX, IDC_EDIT10, m_thdu);
	DDX_Text(pDX, IDC_EDIT11, m_cos);
	DDX_Text(pDX, IDC_EDIT12, m_k);
	DDX_Text(pDX, IDC_EDIT13, m_td);
	DDX_Text(pDX, IDC_EDIT14, m_powercut);
	DDX_Text(pDX, IDC_EDIT4, m_ct2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPzk300Cfg, CFormView)
	//{{AFX_MSG_MAP(CPzk300Cfg)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, OnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, OnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT9, OnChangeEdit9)
	ON_EN_CHANGE(IDC_EDIT10, OnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT11, OnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT12, OnChangeEdit12)
	ON_EN_CHANGE(IDC_EDIT13, OnChangeEdit13)
	ON_EN_CHANGE(IDC_EDIT14, OnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT16, OnChangeEdit16)
	ON_EN_KILLFOCUS(IDC_EDIT7, OnKillfocusEdit7)
	ON_EN_KILLFOCUS(IDC_EDIT8, OnKillfocusEdit8)
	ON_EN_KILLFOCUS(IDC_EDIT9, OnKillfocusEdit9)
	ON_EN_KILLFOCUS(IDC_EDIT10, OnKillfocusEdit10)
	ON_EN_KILLFOCUS(IDC_EDIT11, OnKillfocusEdit11)
	ON_EN_KILLFOCUS(IDC_EDIT12, OnKillfocusEdit12)
	ON_BN_CLICKED(IDC_CANCEl, OnCancel)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT13, OnKillfocusEdit13)
	//}}AFX_MSG_MAP
	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPzk300Cfg diagnostics

#ifdef _DEBUG
void CPzk300Cfg::AssertValid() const
{
	CFormView::AssertValid();
}

void CPzk300Cfg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPzk300Cfg message handlers

void CPzk300Cfg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	mNumberEdit.SubclassDlgItem(IDC_EDIT5,this);
	mNumberEdit1.SubclassDlgItem(IDC_EDIT6,this);
	mNumberEdit2.SubclassDlgItem(IDC_EDIT11,this);
	mNumberEdit3.SubclassDlgItem(IDC_EDIT12,this);

	m_pw = mPzkIni.mPzk300CfgBuf.Pw;
	m_addr = mPzkIni.mPzk300CfgBuf.Addr;
	m_ct1 = mPzkIni.mPzk300CfgBuf.Ct.Ct1;
	m_ct2 = mPzkIni.mPzk300CfgBuf.Ct.Ct2;
	m_wp = mPzkIni.mPzk300CfgBuf.Wp;
	m_wq = mPzkIni.mPzk300CfgBuf.Wq;
	m_u3 = mPzkIni.mPzk300CfgBuf.U3;
	m_u4 = mPzkIni.mPzk300CfgBuf.U4;
	m_i0 = mPzkIni.mPzk300CfgBuf.I0;
	m_thdu = mPzkIni.mPzk300CfgBuf.THDu;
	m_cos = mPzkIni.mPzk300CfgBuf.Cos;
	m_k = mPzkIni.mPzk300CfgBuf.K;
	m_td = mPzkIni.mPzk300CfgBuf.Td;
	m_powercut = mPzkIni.mPzk300CfgBuf.PowerCut;
	if(mPzkIni.mPzk300CfgBuf.Hormanic == 32)
		m_hormanic.SetCurSel(0);
	else
		m_hormanic.SetCurSel(1);
	UpdateData(FALSE);
}

LRESULT CPzk300Cfg::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)
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

LRESULT CPzk300Cfg::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)
{
	OnCancel();
	return TRUE;
}

BOOL CPzk300Cfg::DestroyWindow()
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

void CPzk300Cfg::OnSave()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	mPzkIni.mPzk300CfgBuf.Pw = m_pw;
	mPzkIni.mPzk300CfgBuf.Addr = m_addr;
	mPzkIni.mPzk300CfgBuf.Ct.Ct1 = m_ct1;
	mPzkIni.mPzk300CfgBuf.Ct.Ct2 = m_ct2;
	mPzkIni.mPzk300CfgBuf.Wp = m_wp;
	mPzkIni.mPzk300CfgBuf.Wq = m_wq;
	mPzkIni.mPzk300CfgBuf.U3 = m_u3;
	mPzkIni.mPzk300CfgBuf.U4 = m_u4;
	mPzkIni.mPzk300CfgBuf.I0 = m_i0;
	mPzkIni.mPzk300CfgBuf.THDu = m_thdu;
	mPzkIni.mPzk300CfgBuf.Cos = m_cos;
	mPzkIni.mPzk300CfgBuf.K = m_k;
	mPzkIni.mPzk300CfgBuf.Td = m_td;
	if(m_hormanic.GetCurSel() == 0)
		mPzkIni.mPzk300CfgBuf.PowerCut = 32;
	else
		mPzkIni.mPzk300CfgBuf.PowerCut = 64;

	bEverEdited = false;
	mPzkIni.EverModified = true;
}

void CPzk300Cfg::OnCancel()
{
	// TODO: Add your control notification handler code here
	m_pw = mPzkIni.mPzk300CfgBuf.Pw;
	m_addr = mPzkIni.mPzk300CfgBuf.Addr;
	m_ct1 = mPzkIni.mPzk300CfgBuf.Ct.Ct1;
	m_ct2 = mPzkIni.mPzk300CfgBuf.Ct.Ct2;
	m_wp = mPzkIni.mPzk300CfgBuf.Wp;
	m_wq = mPzkIni.mPzk300CfgBuf.Wq;
	m_u3 = mPzkIni.mPzk300CfgBuf.U3;
	m_u4 = mPzkIni.mPzk300CfgBuf.U4;
	m_i0 = mPzkIni.mPzk300CfgBuf.I0;
	m_thdu = mPzkIni.mPzk300CfgBuf.THDu;
	m_cos = mPzkIni.mPzk300CfgBuf.Cos;
	m_k = mPzkIni.mPzk300CfgBuf.K;
	m_td = mPzkIni.mPzk300CfgBuf.Td;
	m_powercut = mPzkIni.mPzk300CfgBuf.PowerCut;
	if(mPzkIni.mPzk300CfgBuf.Hormanic == 32)
		m_hormanic.SetCurSel(0);
	else
		m_hormanic.SetCurSel(1);
	UpdateData(FALSE);
	bEverEdited = false;
}

void CPzk300Cfg::OnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300Cfg::OnChangeEdit1()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300Cfg::OnChangeEdit2()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300Cfg::OnChangeEdit3()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300Cfg::OnChangeEdit4()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300Cfg::OnChangeEdit5()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300Cfg::OnChangeEdit6()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300Cfg::OnChangeEdit7()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300Cfg::OnChangeEdit8()
{
	// TODO: Add your control notification handler code here

	bEverEdited = true;
}

void CPzk300Cfg::OnChangeEdit9()
{
	// TODO: Add your control notification handler code here

	bEverEdited = true;
}

void CPzk300Cfg::OnChangeEdit10()
{
	// TODO: Add your control notification handler code here

	bEverEdited = true;
}

void CPzk300Cfg::OnChangeEdit11()
{
	// TODO: Add your control notification handler code here
	//0.85 ~ 1.00

	bEverEdited = true;
}

void CPzk300Cfg::OnChangeEdit12()
{
	// TODO: Add your control notification handler code here

}

void CPzk300Cfg::OnChangeEdit13()
{
	// TODO: Add your control notification handler code here

	bEverEdited = true;
}

void CPzk300Cfg::OnChangeEdit14()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300Cfg::OnChangeEdit16()
{
	// TODO: Add your control notification handler code here
	bEverEdited = true;
}

void CPzk300Cfg::OnKillfocusEdit7()
{
	// TODO: Add your control notification handler code here
	//235 ~ 253
	UpdateData(UPDATE_READ);
	if(m_u3 > 253)
	{
		AfxMessageBox("最大值不能超过"+Str(253));
		m_u3 = 253;
	}
	else if(m_u3 < 235)
	{
		AfxMessageBox("最小值不能少于"+Str(235));
		m_u3 = 235;
	}
	UpdateData(UPDATE_WRITE);
}

void CPzk300Cfg::OnKillfocusEdit8()
{
	// TODO: Add your control notification handler code here
	//187 ~ 204
	UpdateData(UPDATE_READ);
	if(m_u4 > 204)
	{
		AfxMessageBox("最大值不能超过"+Str(204));
		m_u4 = 204;
	}
	else if(m_u4 < 187)
	{
		AfxMessageBox("最小值不能少于"+Str(187));
		m_u4 = 187;
	}
	UpdateData(UPDATE_WRITE);
}

void CPzk300Cfg::OnKillfocusEdit9()
{
	// TODO: Add your control notification handler code here
	//5 ~ 60
	UpdateData(UPDATE_READ);
	if(m_i0 > 60)
	{
		AfxMessageBox("最大值不能超过"+Str(60));
		m_i0 = 60;
	}
	else if(m_i0 < 5)
	{
		AfxMessageBox("最小值不能少于"+Str(5));
		m_i0 = 5;
	}
	UpdateData(UPDATE_WRITE);
}

void CPzk300Cfg::OnKillfocusEdit10()
{
	// TODO: Add your control notification handler code here
	//5 ~ 20
	UpdateData(UPDATE_READ);
	if(m_thdu > 20)
	{
		AfxMessageBox("最大值不能超过"+Str(20));
		m_thdu = 20;
	}
	else if(m_thdu < 5)
	{
		AfxMessageBox("最小值不能少于"+Str(5));
		m_thdu = 5;
	}
	UpdateData(UPDATE_WRITE);
}

void CPzk300Cfg::OnKillfocusEdit11()
{
	// TODO: Add your control notification handler code here
	//0.85 ~ 1.00
	UpdateData(UPDATE_READ);
	if(m_cos > 1.00)
	{
		AfxMessageBox("最大值不能超过"+Str(1.00));
		m_cos = 1.00;
	}
	else if(m_cos < 0.85)
	{
		AfxMessageBox("最小值不能少于"+Str(0.85));
		m_cos = 0.85;
	}
	UpdateData(UPDATE_WRITE);
}

void CPzk300Cfg::OnKillfocusEdit12()
{
	// TODO: Add your control notification handler code here
	//0.6 ~ 1.6
	UpdateData(UPDATE_READ);
	if(m_k > 1.6)
	{
		AfxMessageBox("最大值不能超过"+Str(1.6));
		m_k = 1.6;
	}
	else if(m_k < 0.6)
	{
		AfxMessageBox("最小值不能少于"+Str(0.6));
		m_k = 0.6;
	}
	UpdateData(UPDATE_WRITE);

	bEverEdited = true;
}

void CPzk300Cfg::OnKillfocusEdit13()
{
	// TODO: Add your control notification handler code here
	//1 ~ 100
	UpdateData(UPDATE_READ);
	if(m_td > 100)
	{
		AfxMessageBox("最大值不能超过"+Str(100));
		m_td = 100;
	}
	else if(m_td < 1)
	{
		AfxMessageBox("最小值不能少于"+Str(1));
		m_td = 1;
	}
	UpdateData(UPDATE_WRITE);

}
