// DownLoadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "DownLoadDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern bool bAlowDownLoad;
extern TimeOutStru mWaitTimeOut;
extern CDemoApp theApp;
extern bool CallReset();
extern BOOL PcUsbComm(HUFTP hUFTP, TCHAR *msg, DWORD len,bool bNeedRequest);
/////////////////////////////////////////////////////////////////////////////
// CDownLoadDlg dialog


CDownLoadDlg::CDownLoadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDownLoadDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDownLoadDlg)
	m_ShowMsg = _T("");
	//}}AFX_DATA_INIT
	bDlgRuning = false;
}


void CDownLoadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDownLoadDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_ShowMsg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDownLoadDlg, CDialog)
	//{{AFX_MSG_MAP(CDownLoadDlg)
	//}}AFX_MSG_MAP
	ON_MESSAGE(DOWNLOAD_PROGRESS, OnDownloadProgress)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDownLoadDlg message handlers

void CDownLoadDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	bAlowDownLoad = false;
	CDialog::OnCancel();
}

LRESULT CDownLoadDlg::OnDownloadProgress(WPARAM wParam, LPARAM lParam)
{
	CButton *bn = (CButton*)GetDlgItem(IDCANCEL);
	if(!bDlgRuning)
		return TRUE;

	short mPercent = (short)wParam;
//	char *pszMsg = (char*)lParam;

	m_ProgCtrl.SetPos(mPercent);
	if(mPercent >= 100)
	{
		bn->SetWindowText("确定");
		m_ShowMsg = "下载成功!";
//		Sleep(1000);
//		CDialog::OnCancel();
	}
	else
		m_ShowMsg = "正在下载，请等待... ...";
	UpdateData(UPDATE_WRITE);

	return TRUE;
}

BOOL CDownLoadDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_DOWNLOAD);
	this->SetIcon(hIcon,FALSE);
	m_ProgCtrl.SetRange(0, 100);
	m_ShowMsg = "正在下载，请等待... ...";
	UpdateData(UPDATE_WRITE);
	bDlgRuning = true;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDownLoadDlg::OnOK() 
{
	// TODO: Add extra validation here
	/*
	char msg[300];// = "$ls /\n";

	CButton *bn = (CButton*)GetDlgItem(IDOK);
	bn->EnableWindow(FALSE);

	strcpy(msg, "$reset\n");
	mWaitTimeOut.wait_flag = RSP_RESET;
	if(!PcUsbComm(theApp.m_uFtp, msg, strlen(msg), true))
	{
		AfxMessageBox("发送复位命令失败!");
	}
	*/

	CallReset();
	CDialog::OnCancel();
}
