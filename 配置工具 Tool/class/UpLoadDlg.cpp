// UpLoadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "UpLoadDlg.h"
#include "MainFrm.h"
#include "ReadPzkIni.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern bool bAlowUpLoad;
/////////////////////////////////////////////////////////////////////////////
// CUpLoadDlg dialog
extern bool flt_3I0;
extern bool flt1_Current;
extern bool flt2_Current;
extern bool byd_ZeroU;
extern bool byd_ZeroI;
extern bool byd_Voltage;
extern bool byd_Current;

CUpLoadDlg::CUpLoadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUpLoadDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUpLoadDlg)
	m_ShowMsg = _T("");
	//}}AFX_DATA_INIT
	bDlgRuning = false;
}


void CUpLoadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpLoadDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_ShowMsg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUpLoadDlg, CDialog)
	//{{AFX_MSG_MAP(CUpLoadDlg)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UPLOAD_PROGRESS, OnUploadProgress)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpLoadDlg message handlers

void CUpLoadDlg::OnEdit()
{
	// TODO: Add your control notification handler code here

	flt_3I0 = false;
	flt1_Current = false;
	flt2_Current = false;
	byd_ZeroU = false;
	byd_ZeroI = false;
	byd_Voltage = false;
	byd_Current = false;
	CDialog::OnCancel();
	pFrame->OpenUploadFile(fileType);
}

void CUpLoadDlg::OnExit()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CUpLoadDlg::OnSave()
{
	// TODO: Add your control notification handler code here
	CString filter;
	filter = "All Supported Files(*.ini)|*.ini|";
	filter+= "All Files(*.*)|*.*||";
	CFileDialog dlg(FALSE,NULL,"",OFN_HIDEREADONLY,(LPCSTR)filter);
	if (dlg.DoModal() != IDOK)
		return;
	CString lpszPathName = dlg.GetPathName();
	CString expName = lpszPathName.Right(3);
	expName.MakeLower();

	if(expName != "ini")
		lpszPathName += ".ini";

	CFileFind find;int i;
	if(find.FindFile(lpszPathName))
	{
		i = AfxMessageBox("此文件已经存在,确认要覆盖它吗?",MB_YESNO);
		if (i == IDNO)
			return;
	}

	char tempPath[256];
	CString ExistFileName;
	GetTempPath(256, tempPath);
	if(fileType == PROTECT_FILE)
		ExistFileName = tempPath + ProtFileName;
	else if(fileType == FAULT_FILE)
		ExistFileName = tempPath + FaultFileName;
	else if(fileType == SXPLC_FILE)
		ExistFileName = tempPath + PlcFileName;
	else if(fileType == ZJPLC_FILE)
		ExistFileName = tempPath + ZjPlcFileName;
	else if(fileType == JZSLG_FILE)
		ExistFileName = tempPath + JZSPlcFileName;
	else if(fileType == MLPLC_FILE)
		ExistFileName = tempPath + mlPlcFileName;
	else if(fileType == MLPLC_FILE)
		ExistFileName = tempPath + FaultFileName;
	else
	{
		CDialog::OnCancel();
		return;
	}
	CopyFile(ExistFileName, lpszPathName, FALSE);
	CDialog::OnCancel();
}

void CUpLoadDlg::OnCancel()
{
	// TODO: Add extra cleanup here
	bAlowUpLoad = false;
	CDialog::OnCancel();
}

LRESULT CUpLoadDlg::OnUploadProgress(WPARAM wParam, LPARAM lParam)
{
	CButton *bn;
	if(!bDlgRuning)
		return TRUE;

	short mPercent = (short)wParam;
	char *pszMsg = (char*)lParam;

	m_ProgCtrl.SetPos(mPercent);
	if(mPercent >= 100)
	{
		m_ShowMsg = "上载成功!";
		bn = (CButton *)GetDlgItem(IDCANCEL);
		bn->ShowWindow(FALSE);
		CRect rc;
		GetWindowRect(&rc);
		rc.bottom += 60;
		SetWindowPos(this, rc.left, rc.right, rc.Width(), rc.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}
	else
		m_ShowMsg = "正在上载，请等待... ...";
	UpdateData(UPDATE_WRITE);

	return TRUE;
}

BOOL CUpLoadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_UPLOAD);
	this->SetIcon(hIcon,FALSE);
	CRect rc;
	GetWindowRect(&rc);
	rc.bottom -= 60;
	SetWindowPos(this, rc.left, rc.right, rc.Width(), rc.Height(), SWP_NOMOVE | SWP_NOZORDER);
	m_ProgCtrl.SetRange(0, 100);
	bDlgRuning = true;
	m_ShowMsg = "正在上载，请等待... ...";
	UpdateData(UPDATE_WRITE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUpLoadDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	bDlgRuning = false;
}

int CUpLoadDlg::DoModal(int FileType)
{
	fileType = FileType;
	return CDialog::DoModal();
}
