// ObjDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "ObjDlg.h"
#include "ReadPzkIni.h"
#include "MyFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int mObjNum;
//extern ObjStru_ ObjItem;
/////////////////////////////////////////////////////////////////////////////
// CObjDlg

IMPLEMENT_DYNCREATE(CObjDlg, CFormView)

CObjDlg::CObjDlg()
	: CFormView(CObjDlg::IDD)
{
	//{{AFX_DATA_INIT(CObjDlg)
	m_name = _T("");
	m_Index = 0;
	m_RTUid = 0;
	m_ObjType = 0;
	m_ObjSize = 0;
	m_Sequence = 0;
	m_Source = 0;
	m_RelateProc = 0;
	m_Scale = 0;
	//}}AFX_DATA_INIT
}

CObjDlg::~CObjDlg()
{
}

void CObjDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjDlg)
	DDX_Control(pDX, IDC_COMBO2, m_atCurrentPort);
	DDX_Control(pDX, IDC_COMBO1, m_valid);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_Index);
	DDX_Text(pDX, IDC_EDIT3, m_RTUid);
	DDX_Text(pDX, IDC_EDIT4, m_ObjType);
	DDX_Text(pDX, IDC_EDIT5, m_ObjSize);
	DDX_Text(pDX, IDC_EDIT6, m_Sequence);
	DDX_Text(pDX, IDC_EDIT7, m_Source);
	DDX_Text(pDX, IDC_EDIT8, m_RelateProc);
	DDX_Text(pDX, IDC_EDIT9, m_Scale);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CObjDlg, CFormView)
	//{{AFX_MSG_MAP(CObjDlg)
	ON_BN_CLICKED(IDSAVE, OnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjDlg diagnostics

#ifdef _DEBUG
void CObjDlg::AssertValid() const
{
	CFormView::AssertValid();
}

void CObjDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CObjDlg message handlers

void CObjDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	m_name = mPzkIni.mObjBuf.pObj[mObjNum].name;
	m_Index = mPzkIni.mObjBuf.pObj[mObjNum].Index;
	if(mPzkIni.mObjBuf.pObj[mObjNum].valid)
		m_valid.SetCurSel(0);
	else
		m_valid.SetCurSel(1);
	m_RTUid = mPzkIni.mObjBuf.pObj[mObjNum].RTUid;
	m_ObjType = mPzkIni.mObjBuf.pObj[mObjNum].ObjType;
	m_ObjSize = mPzkIni.mObjBuf.pObj[mObjNum].ObjSize;
	m_Sequence = mPzkIni.mObjBuf.pObj[mObjNum].Sequence;
	if(mPzkIni.mObjBuf.pObj[mObjNum].atCurrentPort)
		m_atCurrentPort.SetCurSel(0);
	else
		m_atCurrentPort.SetCurSel(1);
	m_Source = mPzkIni.mObjBuf.pObj[mObjNum].Source;
	m_RelateProc = mPzkIni.mObjBuf.pObj[mObjNum].RelateProc;
	m_Scale = mPzkIni.mObjBuf.pObj[mObjNum].Scale;

	UpdateData(FALSE);
}

void CObjDlg::OnSave()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	mPzkIni.mObjBuf.pObj[mObjNum].name = m_name;
	mPzkIni.mObjBuf.pObj[mObjNum].Index = m_Index;
	if(m_valid.GetCurSel() == 0)
		mPzkIni.mObjBuf.pObj[mObjNum].valid = true;
	else
		mPzkIni.mObjBuf.pObj[mObjNum].valid = false;
	mPzkIni.mObjBuf.pObj[mObjNum].RTUid = m_RTUid;
	mPzkIni.mObjBuf.pObj[mObjNum].ObjType = m_ObjType;
	mPzkIni.mObjBuf.pObj[mObjNum].ObjSize = m_ObjSize;
	mPzkIni.mObjBuf.pObj[mObjNum].Sequence = m_Sequence;
	if (m_atCurrentPort.GetCurSel() == 0)
		mPzkIni.mObjBuf.pObj[mObjNum].atCurrentPort = true;
	else
		mPzkIni.mObjBuf.pObj[mObjNum].atCurrentPort = false;
	mPzkIni.mObjBuf.pObj[mObjNum].Source = m_Source;
	mPzkIni.mObjBuf.pObj[mObjNum].RelateProc = m_RelateProc;
	mPzkIni.mObjBuf.pObj[mObjNum].Scale = m_Scale;

}
