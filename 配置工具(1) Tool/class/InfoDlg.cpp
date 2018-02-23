// InfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "InfoDlg.h"
#include "MyFun.h"
#include "ReadPzkIni.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg

IMPLEMENT_DYNCREATE(CInfoDlg, CFormView)

CInfoDlg::CInfoDlg()
	: CFormView(CInfoDlg::IDD)
{
	//{{AFX_DATA_INIT(CInfoDlg)
	m_Version = _T("");
	m_Date = _T("");
	m_ProcessMax = 0;
	m_NetMax = 0;
	m_RTUMax = 0;
	m_ObjectMax = 0;
	m_FileMax = 0;
	m_IopAiMax = 0;
	m_IopDiMax = 0;
	m_IopSboMax = 0;
	m_IopDoMax = 0;
	m_FaultMax = 0;
	m_ScaleMax = 0;
	m_ObjectTotal = 0;
	m_ProtectMax = 0;
	//}}AFX_DATA_INIT
}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoDlg)
	DDX_Text(pDX, IDC_EDIT1, m_Version);
	DDX_Text(pDX, IDC_EDIT2, m_Date);
	DDX_Text(pDX, IDC_EDIT3, m_ProcessMax);
	DDX_Text(pDX, IDC_EDIT4, m_NetMax);
	DDX_Text(pDX, IDC_EDIT5, m_RTUMax);
	DDX_Text(pDX, IDC_EDIT6, m_ObjectMax);
	DDX_Text(pDX, IDC_EDIT7, m_FileMax);
	DDX_Text(pDX, IDC_EDIT8, m_IopAiMax);
	DDX_Text(pDX, IDC_EDIT9, m_IopDiMax);
	DDX_Text(pDX, IDC_EDIT10, m_IopSboMax);
	DDX_Text(pDX, IDC_EDIT11, m_IopDoMax);
	DDX_Text(pDX, IDC_EDIT13, m_FaultMax);
	DDX_Text(pDX, IDC_EDIT14, m_ScaleMax);
	DDX_Text(pDX, IDC_EDIT15, m_ObjectTotal);
	DDX_Text(pDX, IDC_EDIT12, m_ProtectMax);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfoDlg, CFormView)
	//{{AFX_MSG_MAP(CInfoDlg)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg diagnostics

#ifdef _DEBUG
void CInfoDlg::AssertValid() const
{
	CFormView::AssertValid();
}

void CInfoDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg message handlers

void CInfoDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	m_Version = mPzkIni.mInfo.Version;
	m_Date = mPzkIni.mInfo.Date;
	m_ProcessMax = mPzkIni.mInfo.ProcessMax;
	m_NetMax = mPzkIni.mInfo.NetMax;
	m_RTUMax = mPzkIni.mInfo.RTUMax;
	m_ObjectMax = mPzkIni.mInfo.ObjectMax;
	m_FileMax = mPzkIni.mInfo.FileMax;
	m_IopAiMax = mPzkIni.mInfo.IopAiMax;
	m_IopDiMax = mPzkIni.mInfo.IopDiMax;
	m_IopSboMax = mPzkIni.mInfo.IopSboMax;
	m_IopDoMax = mPzkIni.mInfo.IopDoMax;
	m_ProtectMax = mPzkIni.mInfo.ProtectMax;
	m_FaultMax = mPzkIni.mInfo.FaultMax;
	m_ScaleMax = mPzkIni.mInfo.ScaleMax;
	m_ObjectTotal = mPzkIni.mInfo.ObjectMax;

	UpdateData(FALSE);
}
