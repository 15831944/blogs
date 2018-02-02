// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Demo.h"
#include "ReadPzkIni.h"
#include "MyFun.h"

#include "MainFrm.h"
#include "TempClass.h"
#include "DemoView.h"
#include "Pzk300NormalCfgView.h"
#include "Pzk300ProCfgView.h"
#include "UpLoadDlg.h"
#include "DownloadDlg.h"
#include "ProtCfgView.h"
#include "Fault.h"
#include "TestView.h"
#include "PlcCfgView.h"
#include "ZjPlcCfgView.h"
#include "ChooseFileDlg.h"
#include "36BCANSHU.h"
#include "FaultCfgView.h"
#include "resource.h"
#include "netlink.h"
#include "SxJzsCfgView.h"
#include "KMGCfgView.h"
#include "Sxyj.h"

#include "NetPort.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern bool flt_3I0;
extern bool flt1_Current;
extern bool flt2_Current;
extern bool byd_ZeroU;
extern bool byd_ZeroI;
extern bool byd_Voltage;
extern bool byd_Current;

const unsigned short INFO_DLG  = 10001;
const unsigned short AI_DLG    = 10002;
const unsigned short DI_DLG    = 10003;
const unsigned short SBO_DLG   = 10004;
const unsigned short PRO_DLG   = 10005;
const unsigned short FLT_DLG   = 10006;
const unsigned short SCALE_DLG = 10007;
const unsigned short RTU_DLG   = 10008;
const unsigned short PROC_DLG  = 10009;
const unsigned short PULSE_DLG = 10010;
const unsigned short PZK300_CFG_DLG = 10011;
const unsigned short PZK300_U_DLG	= 10012;

const unsigned short PZK300_NORMAL_CFG_DLG	= 10013;
const unsigned short PZK300_PRO_CFG_DLG		= 10014;

const unsigned short PROTECT_DLG = 10020;
const unsigned short SXPLC_DLG	 = 10021;
const unsigned short ZJPLC_DLG	 = 10022;
const unsigned short JZSPLC_DLG	 = 10023;
const unsigned short FAULT_DLG	 = 10024;
const unsigned short SXJZS_DLG	 = 10025;
const unsigned short KMG_DLG	 = 10026;
const unsigned short SXYJ_DLG    = 10027;

CReadPzkIni mPzkIni;
extern int CurProcNum;
extern int mObjNum;
extern int RtuNo;
CView *pOldView = NULL;
bool bCloseWindow = true;
extern CDemoApp theApp;
CUpLoadDlg UpLoadDlg;
CDownLoadDlg DownLoadDlg;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame
int isisis;

extern bool LoginIn;
extern SocketInterfStru SocketInterf;
extern bool CallReset();


IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_FILE_CLOSE1, OnFileClose1)
	ON_COMMAND(ID_FILE_MYSAVE, OnFileMysave)
	ON_COMMAND(ID_FILE_MYSAVE_AS, OnFileMysaveAs)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_WM_CLOSE()
	ON_COMMAND(ID_UPLOAD, OnUplaod)
	ON_COMMAND(ID_DOWNLAOD, OnDownlaod)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_COMMAND(ID_DOWNFILE, OnDownfile)
	ON_COMMAND(ID_CONNECT,OnConnect)
	ON_COMMAND(ID_SHUTDOWN, OnShutdown)
	ON_COMMAND(ID_RESET_MK, OnResetMk)
	//}}AFX_MSG_MAP
	ON_MESSAGE(XTWM_OUTBAR_NOTIFY, OnOutbarNotify)
	ON_MESSAGE(SET_FRAME_WINTEXT, OnSetWinText)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_CurActiveView = 0;
	m_bCreateSplitter = false;
	m_PreSelFolder=-1;
	m_PreSelItem=-1;
}

CMainFrame::~CMainFrame()
{
	if(m_bCreateSplitter)
	{
		// delete m_pImageList;
		delete m_wndSplitter;
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_bAutoMenuEnable=FALSE;
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

#ifndef __SUPERMODE
	CMenu *pMenu = GetMenu();
	ASSERT_VALID (pMenu);
	pMenu->EnableMenuItem(ID_FILE_NEW, MF_GRAYED);
	this->UpdateWindow();
#endif
	return 0;
}

LRESULT CMainFrame::OnOutbarNotify(WPARAM wParam, LPARAM lParam)
{
	int nBarAction = (int)wParam;
	// Cast the lParam to a XT_OUTBAR_INFO* struct pointer.
	XT_OUTBAR_INFO* pOBInfo = (XT_OUTBAR_INFO*)lParam;
	ASSERT(pOBInfo);
	int mSelFolder,mSelItem;

//	CString str;
	switch (nBarAction)
	{
	case OBN_XT_ITEMCLICK:
		mSelFolder = pOBInfo->nFolder;
		mSelItem   = pOBInfo->nIndex;
		if ((mSelFolder == m_PreSelFolder) && (mSelItem == m_PreSelItem))
		{
			return TRUE;
		}
		m_wndSplitter->DeleteView(0,1);
		if(!bCloseWindow)
		{
			bCloseWindow = true;
			break;
		}
		m_PreSelFolder = mSelFolder;
		m_PreSelItem = mSelItem;

		switch(mSelFolder)
		{
		case 0:
			switch(mSelItem)
			{
			case 0:
				m_wndSplitter->CreateView(0,1,RUNTIME_CLASS(CPlcCfgView),CSize(100,100),NULL);
				m_CurActiveView = SXPLC_DLG;//PZK300_CFG_DLG;
				break;
			case 1:
				m_wndSplitter->CreateView(0,1,RUNTIME_CLASS(CProtCfgView),CSize(900,900),NULL);
				m_CurActiveView = PROTECT_DLG;
				break;
			case 2:
				m_wndSplitter->CreateView(0,1,RUNTIME_CLASS(CZjPlcCfgView),CSize(900,900),NULL);
				m_CurActiveView = ZJPLC_DLG;
				break;
			case 3:
				m_wndSplitter->CreateView(0,1,RUNTIME_CLASS(C36BCANSHU),CSize(900,900),NULL);
				m_CurActiveView = JZSPLC_DLG;
				break;
			case 4:
			//	AfxMessageBox("FFFFF");
				m_wndSplitter->CreateView(0,1,RUNTIME_CLASS(CFaultCfgView),CSize(900,900),NULL);
				m_CurActiveView = FAULT_DLG;
				break;
			case 5:
			//	AfxMessageBox("00000000");
				m_wndSplitter->CreateView(0,1,RUNTIME_CLASS(CSxJzsCfgView),CSize(900,900),NULL);
				m_CurActiveView = SXJZS_DLG;
				break;
			case 6:
				//fxMessageBox("00000000");
				m_wndSplitter->CreateView(0,1,RUNTIME_CLASS(CKMGCfgView),CSize(900,900),NULL);
				m_CurActiveView = KMG_DLG;
				break;
			case 7:
				m_wndSplitter->CreateView(0,1,RUNTIME_CLASS(CSxyj),CSize(900,900),NULL);
				m_CurActiveView = SXYJ_DLG;
			default:
				break;
			}
			break;
		default:
			m_wndSplitter->CreateView(0,1,RUNTIME_CLASS(CDemoView),CSize(100,100),NULL);
			m_CurActiveView = 0;
			break;
		}
//		m_wndSplitter->CreateView(0,1,RUNTIME_CLASS(CTempClass),CSize(100,100),NULL);
		m_wndSplitter->RecalcLayout();
		break;

	case OBN_XT_FOLDERCHANGE:
		TRACE2( "Folder selected: %d, Name: %s.\n", pOBInfo->nIndex, pOBInfo->lpszText);
		break;

	case OBN_XT_ONLABELENDEDIT:
		TRACE2( "Item edited: %d, New name: %s.\n", pOBInfo->nIndex, pOBInfo->lpszText);
		break;

	case OBN_XT_ONGROUPENDEDIT:
		TRACE2( "Folder edited: %d, New name: %s.\n", pOBInfo->nIndex, pOBInfo->lpszText);
		break;

	case OBN_XT_DRAGITEM:
		TRACE3( "Dragging From: %d, To: %d, Name: %s.\n", pOBInfo->nDragFrom, pOBInfo->nDragTo, pOBInfo->lpszText);
		break;

	case OBN_XT_ITEMHOVER:
		TRACE2( "Hovering Item: %d, Name: %s.\n", pOBInfo->nIndex, pOBInfo->lpszText);
		break;

	case OBN_XT_DELETEITEM:

/*		if (!m_bDestroy && AfxMessageBox(_T("Are you sure you want to remove this folder shortcut?"),
			MB_ICONWARNING|MB_YESNO) == IDNO)
		{
			// The user selected No, return FALSE to abort the action.
			return FALSE;
		}
		TRACE2( "Item deleted: %d, Name: %s.\n", pOBInfo->nIndex, pOBInfo->lpszText);
*/		break;

	case OBN_XT_DELETEFOLDER:
/*		if (!m_bDestroy && AfxMessageBox(_T("Are you sure you want to remove the specified folder?"),
			MB_ICONWARNING|MB_YESNO) == IDNO)
		{
			// The user selected No, return FALSE to abort the action.
			return FALSE;
		}
		TRACE2( "Folder deleted: %d, Name: %s.\n", pOBInfo->nIndex, pOBInfo->lpszText);
*/		break;
	}

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &= ~FWS_ADDTOTITLE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
BOOL CMainFrame::ShowOutLookBar()
{
	CCreateContext pContext;
	pContext.m_pCurrentDoc = GetActiveDocument();
	pContext.m_pNewViewClass = RUNTIME_CLASS(CDemoView);
	m_CurActiveView = 0;
	if (!m_bCreateSplitter)
	{
		if(pOldView == NULL)
		{
			pOldView = GetActiveView();
			pOldView->SetDlgCtrlID(0);
		}
		m_wndSplitter = new CSplitterWnd[1];
		if (!m_wndSplitter->CreateStatic(this, 1, 2))
			return FALSE;
		// Here we create the outbar control using the splitter as its parent
		// and setting its id to the first pane.
//		UINT wndid = m_wndSplitter->IdFromRowCol(0, 0);
		if (!m_wndOutlookBar.Create(WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN, CRect(0,0,0,0),
			m_wndSplitter, m_wndSplitter->IdFromRowCol(0, 0), OBS_XT_DEFAULT))
		{
			TRACE0("Failed to create outlook bar.");
			return FALSE;
		}

		if (!m_wndSplitter->CreateView(0, 1, pContext.m_pNewViewClass,
			CSize(100, 100), &pContext))
		{
			m_wndSplitter->DestroyWindow();
			return FALSE;
		}

		// Set the background and text color of the outlook bar.
		//m_wndOutlookBar.SetBackColor(RGB(0x3a,0x6e,0xa5));
		m_wndOutlookBar.SetBackColor(RGB(0x3a,0x95,0x55));
		m_wndOutlookBar.SetTextColor(RGB(0xff,0xff,0x00));

		// Set the default sizes for the splitter panes.
		CRect r;
		GetClientRect(&r);

	//	m_wndSplitter->SetColumnInfo( 0, r.Width()/8, 0 );
		m_wndSplitter->SetColumnInfo( 0, 90, 0 );
	//	m_wndSplitter->ShowWindow(SW_SHOW);

	}

	try{
		m_wndSplitter->DeleteView(0,1);}
	catch(CException e)
	{
		throw;
	}

	m_wndSplitter->CreateView(0, 1, pContext.m_pNewViewClass,CSize(100, 100), &pContext);
	this->SetActiveView(pOldView);
	m_wndSplitter->RecalcLayout();
	RecalcLayout();
	pOldView->ShowWindow(SW_HIDE);
	if(m_bCreateNewView)
	{
		delete m_pNewActiveView;
		m_bCreateNewView = false;
	}
//	pOldView->SetDlgCtrlID(0);
	m_wndSplitter->RecalcLayout();
	RecalcLayout();
	m_wndSplitter->ShowWindow(SW_SHOW);
	// Add items to the outlook bar.
	m_PreSelFolder=-1;m_PreSelItem=-1;
	InitializeOutlookBar();

	return TRUE;
}

static UINT nIcons[] =
{
    IDI_ICON1, IDI_ICON3,  IDI_ICON4,  IDI_ICON7,
    IDI_ICON8, IDI_ICON2,  IDI_ICON11, IDI_ICON6,
    IDI_ICON9, IDI_ICON10, IDI_ICON5
};

void CMainFrame::InitializeOutlookBar()
{
	// Create the image lists used by the outlook bar.
	int i;
//	HTREEITEM hTreeItem;
	CString tempStr;
	int iFolder; // index of the added folder

	if(!m_bCreateSplitter)
	{
		m_ImageSmall.Create (16, 16, ILC_COLOR16|ILC_MASK, 2, 1);
		m_ImageLarge.Create (32, 32, ILC_COLOR16|ILC_MASK, 2, 1);

		// initiailize the image lists.
		for (i = 0; i < 11; ++i)
		{
			HICON hIcon = AfxGetApp()->LoadIcon(nIcons[i]);
			ASSERT(hIcon);

			m_ImageSmall.Add(hIcon);
			m_ImageLarge.Add(hIcon);
		}

		// set the image lists for the outlook bar.
		m_wndOutlookBar.SetImageList(&m_ImageLarge, OBS_XT_LARGEICON);
		m_wndOutlookBar.SetImageList(&m_ImageSmall, OBS_XT_SMALLICON);

		// Add the first folder to the outlook bar.
		iFolder = m_wndOutlookBar.AddFolder(_T("配置项目"), 0);
		// Add items to the folder, syntax is folder, index, text, image, and item data.

		//m_wndOutlookBar.InsertItem(iFolder, 1, _T("PLC逻辑配置项"), 9, 0);
		//m_wndOutlookBar.InsertItem(iFolder, 2, _T("保护项配置"), 1, 1);
	}
	else
		m_wndOutlookBar.RemoveItem(0);

//	CString cs;
//	cs.Format("%d",mPzkIni.FileType);
//  AfxMessageBox(cs);
	switch(mPzkIni.FileType)
	{
	case PROTECT_FILE:
		i = m_wndOutlookBar.InsertItem(0, 2, _T("保护配置项"), 1, 1);//1
	//	AfxMessageBox("PROTECT_FILE");
		break;
	case SXPLC_FILE:
		m_wndOutlookBar.InsertItem(0, 1, _T("绍兴PLC逻辑配置项"), 9, 0);
		break;
	case ZJPLC_FILE:
		m_wndOutlookBar.InsertItem(0, 3, _T("诸暨PLC逻辑配置项"), 2, 2);
		break;
	case JZSLG_FILE:
		m_wndOutlookBar.InsertItem(0, 3, _T("集中式PZK-36B逻辑关系"), 2, 3);
		break;
    case MLPLC_FILE:
		m_wndOutlookBar.InsertItem(0, 3, _T("母联式PZK-36B逻辑关系"), 2, 3);
		break;
	case FAULT_FILE:
		m_wndOutlookBar.InsertItem(0, 3, _T("故障配置项"), 2, 4);//4
	//	AfxMessageBox("FAULT_FILE");
		break;
	case SXJZS_FILE:
		m_wndOutlookBar.InsertItem(0, 3, _T("绍兴集中式"), 2, 5);//5
		break;
	case KMG_FILE:
		m_wndOutlookBar.InsertItem(0, 2, _T("PZK560F/L分界狗配置项"), 1, 6);//6
		break;
	case SXYJ_FILE:
		m_wndOutlookBar.InsertItem(0, 1, _T("液晶显示配置项"), 2, 7);//6
		break;
	}
	// We want to receive notification messages.
	m_wndOutlookBar.SetOwner(this);

	// Select the first folder in the bar.
	m_wndOutlookBar.SetSelFolder(0);

	// Sizing for splitter
	CRect r;
	GetClientRect(&r);
	m_wndSplitter->SetColumnInfo( 0, r.Width()/7, 0 );
	m_wndSplitter->SetColumnInfo( 1, r.Width()/5, 0 );
//	m_wndSplitter1.SetSplitterStyle(XT_SPLIT_NOFULLDRAG);
	m_wndSplitter->RecalcLayout();
	m_bCreateSplitter = true;
}

void CMainFrame::OnDestroy()
{
	m_bDestroy = true;
	CFrameWnd::OnDestroy();
}

void CMainFrame::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

void CMainFrame::OnFileClose1()
{
	// TODO: Add your command handler code here
	CCreateContext context;
//	pOldView = (CView *)GetDlgItem(0);
	//ASSERT( pOldView );
	if(!pOldView)
		return;

//	if(m_CurActiveView == 0)
//		return;
	if(!mPzkIni.IniFileOpened)
		return;

	if (m_CurActiveView != 0)
	{
		CView *pView = (CView*)m_wndSplitter->GetPane(0,1);
		BOOL bclose;
		bclose = SendSaveMsg(pView,m_CurActiveView);
		if( bclose != TRUE)
			return;
	}
	if(!mPzkIni.CloseFile())
		return;

	m_CurActiveView = 0;
//	pOldView->ShowWindow(SW_SHOW);
	m_wndSplitter->ShowWindow(SW_HIDE);

	CDocument *pDc = pOldView->GetDocument();
	pDc->OnNewDocument();
	AfxGetMainWnd()->SetWindowText(TitleName);
	RecalcLayout();

//	if(m_bCreateNewView)
//		m_pNewActiveView->DestroyWindow();
	m_pNewActiveView = (CView*)new CDemoView;
	CRect rect;
//	rect = CFrameWnd::rectDefault;
	context.m_pCurrentDoc = this->GetActiveDocument();//pOldView->GetDocument();//new CDocument[1];
	m_pNewActiveView->Create(NULL, NULL, 0L, rect, // and the frame
		this, 0, &context);
	m_pNewActiveView->OnInitialUpdate();
	m_bCreateNewView = true;

	SetActiveView(m_pNewActiveView);
	m_pNewActiveView->ShowWindow(SW_SHOW);
	SetWindowLong(m_pNewActiveView->m_hWnd, GWL_ID, AFX_IDW_PANE_FIRST);  // gotta have it
	RecalcLayout();
//	pDc->SetPathName("",TRUE);

//	m_wndOutlookBar.DestroyWindow();
//	m_wndSplitter->DestroyWindow();
//	delete m_wndSplitter;
	return;
}

void CMainFrame::OnFileMysave()
{
	// TODO: Add your command handler code here

	if(!mPzkIni.IniFileOpened)
	{
		AfxMessageBox("在保存文件前请先打开文件!");
		return;
	}

	if (m_CurActiveView != 0)
	{
		CView *pView = (CView*)m_wndSplitter->GetPane(0,1);
		BOOL bclose;
		bclose = SendSaveMsg(pView,m_CurActiveView);
		if( bclose != TRUE)
		{
			SendUnSaveMsg(pView,m_CurActiveView);
			return;
		}

	}

	CDocument *pDc = pOldView->GetDocument();
	CString CurPathName = pDc->GetPathName();
	if(mPzkIni.GetFileName() == "")
		pDc->DeleteContents();

	if(!mPzkIni.SaveToIni())
		return;
	if(pOldView != NULL)
	{
		CString file_path;
		pDc->OnNewDocument();
		pDc->SetPathName(mPzkIni.GetFileName(),TRUE);
		AfxGetMainWnd()->SetWindowText(TitleName + mPzkIni.GetFileName());
	}
//	m_wndSplitter->DeleteView(0,1);
//	m_wndSplitter->CreateView(0,1,RUNTIME_CLASS(CDemoView),CSize(100,100),NULL);
//	m_wndSplitter->RecalcLayout();
}

void CMainFrame::OnFileMysaveAs()
{

	// TODO: Add your command handler code here
	if(!mPzkIni.IniFileOpened)
	{
		AfxMessageBox("在保存文件前请先打开文件!");
		return;
	}
	CString filter;
	filter = "All Supported Files(*.ini)|*.ini|";
	filter+= "All Files(*.*)|*.*||";
	CFileDialog dlg(FALSE,NULL,mPzkIni.GetFileName(),OFN_HIDEREADONLY,(LPCSTR)filter);
	if (dlg.DoModal() != IDOK)
		return;
	CString lpszPathName = dlg.GetPathName();
	CFileFind find;int i;
	if(find.FindFile(lpszPathName))
	{
		i = AfxMessageBox("此文件已经存在,确认要覆盖它吗?",MB_YESNO);
		if (i == IDNO)
			return;
	}

	if(pOldView != NULL)
	{
		CDocument *pDc = pOldView->GetDocument();
		pDc->OnNewDocument();
		pDc->SetPathName(lpszPathName,TRUE);
		SetWindowText(TitleName + lpszPathName);
	}
	mPzkIni.SaveToIni(lpszPathName);
}

void CMainFrame::OnFileNew()
{
	// TODO: Add your command handler code here
#ifndef __SUPERMODE
	return;
#endif

	if (m_CurActiveView != 0)
	{
		CView *pView = (CView*)m_wndSplitter->GetPane(0,1);
		BOOL bclose;
		bclose = SendSaveMsg(pView,m_CurActiveView);
		if( bclose != TRUE)
			return;

		if(!mPzkIni.CloseFile())
			return;
	}
	mPzkIni.NewFile();
	if(pOldView == NULL)
	{
		pOldView = GetActiveView();
		pOldView->SetDlgCtrlID(0);
	}
	if(pOldView != NULL)
	{
		CDocument *pDc = pOldView->GetDocument();
		pDc->OnNewDocument();
		pDc->SetPathName("新建配置文件",TRUE);
		SetWindowText(TitleName + "新建配置文件");
	}
	if (!ShowOutLookBar())
		msgbox("显示OutLookBar失败!");
}

void CMainFrame::OnFileOpen()
{

	// TODO: Add your command handler code here
	CString filter;

	filter = "All Supported Files(*.ini)|*.ini|";
	filter+= "All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL,0,(LPCSTR)filter);
	if (dlg.DoModal() != IDOK)
		return;

	flt_3I0 = false;
	flt1_Current = false;
	flt2_Current = false;
	byd_ZeroU = false;
	byd_ZeroI = false;
	byd_Voltage = false;
	byd_Current = false;

	CString lpszPathName = dlg.GetPathName();
	CFileFind findfile;
	if(!findfile.FindFile(lpszPathName))
		return;
	if(pOldView == NULL)
	{
		pOldView = GetActiveView();
		pOldView->SetDlgCtrlID(0);
	}
	if(pOldView != NULL)
	{
		CDocument *pDc = pOldView->GetDocument();
		pDc->OnNewDocument();
		pDc->SetPathName(lpszPathName,TRUE);
	}
//	OnOpenDocument((LPCTSTR)lpszPathName);
	//CView *pView = GetActiveView();
	if (m_CurActiveView != 0)
	{
		CView *pView = (CView*)m_wndSplitter->GetPane(0,1);
		BOOL bclose;
		bclose = SendSaveMsg(pView,m_CurActiveView);
		if( bclose != TRUE)
			return;
	}

	if(lpszPathName != mPzkIni.GetFileName())
		if(!mPzkIni.CloseFile())
		{
			AfxMessageBox("关闭文件失败");
			return;
		}

    if(!mPzkIni.OpenFile(lpszPathName))
	{
		AfxMessageBox("打开文件失败");
		return;
	}
//	AfxMessageBox(lpszPathName);
	SetWindowText(TitleName + lpszPathName);

//	PostMessage(SET_FRAME_WINTEXT,0,&lpszPathName);
	if (!ShowOutLookBar())
		;//AfxMessageBox("无效文件!");
}

void CMainFrame::OpenUploadFile(int FileType)
{
	char tempPath[256];
	CString lpszPathName;
	CFileFind findfile;

	GetTempPath(256, tempPath);
	if(FileType == PROTECT_FILE)
		lpszPathName = tempPath + ProtFileName;
	else if(FileType == SXPLC_FILE)
		lpszPathName = tempPath + PlcFileName;
	else if(FileType == ZJPLC_FILE)
		lpszPathName = tempPath + ZjPlcFileName;
	else if(FileType == JZSLG_FILE)
		lpszPathName = tempPath + JZSPlcFileName;
	else if(FileType == MLPLC_FILE)
		lpszPathName = tempPath + mlPlcFileName;
	else if(FileType == FAULT_FILE)
		lpszPathName = tempPath + FaultFileName;
	else if(FileType == SXJZS_FILE)
		lpszPathName = tempPath + SxjzsFileName;
	else if(FileType == KMG_FILE)
		lpszPathName = tempPath + KMGFileName;
	else if(FileType == SXYJ_FILE)
		lpszPathName = tempPath + SXYJFileName;
	else
	{
		AfxMessageBox("此工具不支持此文件格式!");
		return;
	}
	if(!findfile.FindFile(lpszPathName))
		return;
	if (m_CurActiveView != 0)
	{
		CView *pView = (CView*)m_wndSplitter->GetPane(0,1);
		BOOL bclose;
		bclose = SendSaveMsg(pView,m_CurActiveView);
		if( bclose != TRUE)
			return;

		if(!mPzkIni.CloseFile())
			return;
	}
	mPzkIni.OpenTempFile(lpszPathName);
	if(pOldView == NULL)
	{
		pOldView = GetActiveView();
		pOldView->SetDlgCtrlID(0);
	}
	if(pOldView != NULL)
	{
		CDocument *pDc = pOldView->GetDocument();
		pDc->OnNewDocument();
		pDc->SetPathName("新建配置文件",TRUE);
		SetWindowText(TitleName + "新建配置文件");
	}
	if (!ShowOutLookBar())
		msgbox("显示OutLookBar失败!");
}

BOOL  CMainFrame::SendSaveMsg(CView *pView,int mDlgCtrlId)
{
	BOOL bclose;
	switch(mDlgCtrlId)
	{
	case PZK300_NORMAL_CFG_DLG:
		bclose = ((CPzk300NormalCfgView *)pView)->SendMessage(SAVE_FILE,0,0);
		break;
	case PZK300_PRO_CFG_DLG:
		bclose = ((CPzk300ProCfgView *)pView)->SendMessage(SAVE_FILE,0,0);
		break;
	case PROTECT_DLG:
		bclose = ((CProtCfgView *)pView)->SendMessage(SAVE_FILE, 0, 0);
		break;
	case SXPLC_DLG:
		bclose = ((CPlcCfgView *)pView)->SendMessage(SAVE_FILE, 0, 0);
		break;
	case ZJPLC_DLG:
		bclose = ((CZjPlcCfgView *)pView)->SendMessage(SAVE_FILE, 0, 0);
		break;
	case JZSPLC_DLG:
		bclose = ((C36BCANSHU *)pView)->SendMessage(SAVE_FILE, 0, 0);
		break;
	case FAULT_DLG:
		bclose = ((CFault *)pView)->SendMessage(SAVE_FILE, 0, 0);
		break;
	case SXJZS_DLG:
		bclose = ((CSxJzsCfgView *)pView)->SendMessage(SAVE_FILE, 0, 0);
		break;
	case KMG_DLG:
		bclose = ((CKMGCfgView *)pView)->SendMessage(SAVE_FILE, 0, 0);
		break;
	case SXYJ_DLG:
		bclose = ((CSxyj *)pView)->SendMessage(SAVE_FILE, 0, 0);
		break;
	default:
		return TRUE;
	}

	return bclose;
}

BOOL CMainFrame::SendUnSaveMsg(CView *pView,int mDlgCtrlId)
{
	BOOL bclose; //这里的返回没什么用
	switch(mDlgCtrlId)
	{
	case PZK300_NORMAL_CFG_DLG:
		bclose = ((CPzk300NormalCfgView *)pView)->SendMessage(UNSAVE_FILE,0,0);
		break;
	case PZK300_PRO_CFG_DLG:
		bclose = ((CPzk300ProCfgView *)pView)->SendMessage(UNSAVE_FILE,0,0);
		break;
	case PROTECT_DLG:
		bclose = ((CProtCfgView *)pView)->SendMessage(UNSAVE_FILE, 0, 0);
		break;
	case SXPLC_DLG:
		bclose = ((CPlcCfgView *)pView)->SendMessage(UNSAVE_FILE, 0, 0);
		break;
	case ZJPLC_DLG:
		bclose = ((CZjPlcCfgView *)pView)->SendMessage(UNSAVE_FILE, 0, 0);
		break;
	case JZSPLC_DLG:
		bclose = ((C36BCANSHU *)pView)->SendMessage(UNSAVE_FILE, 0, 0);
		break;
	case FAULT_DLG:
		bclose = ((CFault *)pView)->SendMessage(UNSAVE_FILE, 0, 0);
		break;
	case SXJZS_DLG:
		bclose = ((CSxJzsCfgView *)pView)->SendMessage(UNSAVE_FILE, 0, 0);
		break;
	case SXYJ_DLG:
		bclose = ((CSxyj *)pView)->SendMessage(UNSAVE_FILE, 0, 0);
		break;
	default:
		return TRUE;
	}

	return TRUE;
}

BOOL CMainFrame::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	return CFrameWnd::DestroyWindow();
}

void CMainFrame::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	if (m_CurActiveView != 0)
	{
		CView *pView = (CView*)m_wndSplitter->GetPane(0,1);
		BOOL bclose;
		bclose = SendSaveMsg(pView,m_CurActiveView);
		if( bclose != TRUE)
		return;
	}

		if(!mPzkIni.CloseFile())
		{
			AfxMessageBox("文件未关闭");
			return;
		}
	CFrameWnd::OnClose();
}

LRESULT CMainFrame::OnSetWinText(WPARAM wParam, LPARAM lParam)
{
//	LPVOID p = (LPVOID)wParam;
	CString *strr = (CString *)lParam;
	Sleep(50);
	SetWindowText(strr->GetBuffer(strr->GetLength()));
	return TRUE;
}

extern UINT UploadFile(LPVOID para);

void CMainFrame::OnUplaod()
{
	// TODO: Add your command handler code here
	CString dstFileName;
/*	if(!theApp.m_uFtp)
	{
		theApp.OpenUsb();
		if(!theApp.m_uFtp)
			AfxMessageBox("请先正确连接USB设备!");
		return;
	}
*/
	if(!LoginIn)
	{
		AfxMessageBox("请先建立网络连接!");
			return;
	}

	CString tempFileName;
	char tempPath[256];
	int FileType;

	CChooseFileDlg dlg;
	dlg.DoModal(&FileType);
	GetTempPath(256, tempPath);
	tempFileName.Format("%s",tempPath);
	if(tempFileName.GetAt(tempFileName.GetLength() - 1) != '\\')
		tempFileName += "\\";
	if(FileType == PROTECT_FILE)
		dstFileName = ProtFileName;
	else if(FileType == SXPLC_FILE)
		dstFileName = PlcFileName;
	else if(FileType == ZJPLC_FILE)
		dstFileName =ZjPlcFileName;
	else if(FileType == JZSLG_FILE)
		dstFileName =JZSPlcFileName;
	else if(FileType == MLPLC_FILE)
		dstFileName =mlPlcFileName;
	else if(FileType == FAULT_FILE)
		dstFileName =FaultFileName;
	else if(FileType == SXJZS_FILE)
		dstFileName =SxjzsFileName;
	else if(FileType == KMG_FILE)
		dstFileName =KMGFileName;
	else if(FileType == SXYJ_FILE)
		dstFileName = SXYJFileName;
	else
	{
	//	AfxMessageBox("此工具不支持此文件格式!");
		return;
	}
//	AfxMessageBox(dstFileName);
	tempFileName += dstFileName;
	CStringArray arrStr;
	arrStr.RemoveAll();
	arrStr.Add(tempPath);
	arrStr.Add(dstFileName);
	if(FileType == SXYJ_FILE)
	{
		arrStr.Add("/opt/");
	}
	else
	{
		arrStr.Add("/mnt/");
	}
	AfxBeginThread(UploadFile, &arrStr);

	UpLoadDlg.DoModal(FileType);
}

extern UINT DownloadFile(LPVOID para);

void CMainFrame::OnDownlaod()
{
	// TODO: Add your command handler code here
	CString filter;
	filter = "All Supported Files(*.ini)|*.ini|";
	filter+= "All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL,0,(LPCSTR)filter);
	CString lpszPathName;

	CString tempFileName;
	char tempPath[256];

	/*
	if(!theApp.m_uFtp)
	{
		theApp.OpenUsb();
		if(!theApp.m_uFtp)
			AfxMessageBox("请先正确连接USB设备!");
		return;
	}
	*/

	if(!LoginIn)
	{
		AfxMessageBox("请先建立网络连接!");
			return;
	}
	if(!mPzkIni.IniFileOpened)
	{

		if (dlg.DoModal() != IDOK)
			return;
		lpszPathName = dlg.GetPathName();
//		if(GetFloderPath(lpszPathName, &lpszFolderName) != TRUE)
		//	return;
		//lpszFileName = dlg.GetFileName();

		/*if((lpszPathName.Compare(tempFileName) != 0) &&
			!CopyFile(lpszPathName, tempFileName, FALSE))	//FALSE means:if newfile exist, overwrite it
		{
			//;
			AfxMessageBox("保存为临时文件时出错，请重新下载");
			return;
		}
		*/
	}
	else
	{
		if(AfxMessageBox("要下载方式字吗？",MB_YESNO) == IDNO)
			return;
		GetTempPath(256, tempPath);
		tempFileName.Format("%s",tempPath);
		if(tempFileName.GetAt(tempFileName.GetLength() - 1) != '\\')
			tempFileName += "\\";
		if(mPzkIni.FileType == PROTECT_FILE)
			tempFileName += ProtFileName;
		else if(mPzkIni.FileType == SXPLC_FILE)
			tempFileName += PlcFileName;
		else if(mPzkIni.FileType == ZJPLC_FILE)
			tempFileName += ZjPlcFileName;
		else if(mPzkIni.FileType == JZSLG_FILE)
			tempFileName += JZSPlcFileName;
		else if(mPzkIni.FileType == MLPLC_FILE)
			tempFileName += mlPlcFileName;
		else if(mPzkIni.FileType == FAULT_FILE)
			tempFileName += FaultFileName;
		else if(mPzkIni.FileType == SXJZS_FILE)
			tempFileName += SxjzsFileName;
		else if(mPzkIni.FileType == KMG_FILE)
			tempFileName += KMGFileName;
		else if(mPzkIni.FileType == SXYJ_FILE)
			tempFileName += SXYJFileName;
		else
		{
			//AfxMessageBox("此工具不支持此文件格式!");
			return;
		}
		//	AfxMessageBox(tempFileName);
		//CString ss;
		if (m_CurActiveView != 0)
		{
			CView *pView = (CView*)m_wndSplitter->GetPane(0,1);
			BOOL bclose;
			//ss.Format("%d",m_CurActiveView);
			//AfxMessageBox(ss);
			bclose = SendSaveMsg(pView,m_CurActiveView);

			if(!bclose)
				return;
		}

		if(!mPzkIni.SaveToTempIni(tempFileName))
		{
			AfxMessageBox("保存为临时文件时出错，请重新下载!");
			return;
		}
	}
	CStringArray arrStr;
	arrStr.RemoveAll();
	if(mPzkIni.FileType == SXYJ_FILE)
	{
		arrStr.Add("/opt/");
	}
	else
	{
		arrStr.Add("/mnt/");
	}
	if(mPzkIni.FileType == PROTECT_FILE)
		arrStr.Add(ProtFileName);
	else if(mPzkIni.FileType == SXPLC_FILE)
		arrStr.Add(PlcFileName);
	else if(mPzkIni.FileType == ZJPLC_FILE)
		arrStr.Add(ZjPlcFileName);
	else if(mPzkIni.FileType == JZSLG_FILE)
		arrStr.Add(JZSPlcFileName);
	else if(mPzkIni.FileType == MLPLC_FILE)
		arrStr.Add(mlPlcFileName);
	else if(mPzkIni.FileType == FAULT_FILE)
		arrStr.Add(FaultFileName);
	else if(mPzkIni.FileType == SXJZS_FILE)
		arrStr.Add(SxjzsFileName);
	else if(mPzkIni.FileType == KMG_FILE)
		arrStr.Add(KMGFileName);
	else if(mPzkIni.FileType == SXYJ_FILE)
		arrStr.Add(SXYJFileName);
	arrStr.Add(tempPath);
	AfxBeginThread(DownloadFile, &arrStr);
	DownLoadDlg.DoModal();
}

void CMainFrame::OnUpdateFileNew(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
#ifndef __SUPERMODE
	pCmdUI->Enable(FALSE);
#else
	pCmdUI->Enable(TRUE);
#endif
}

void CMainFrame::CreateNewView()
{
//	m_pNewActiveView = (CView*)new CDemoView;
	m_bCreateNewView = false;
	return;
	RECT rect;
	rect.left = 0;
	rect.top =  0;

	CCreateContext context;
	context.m_pCurrentDoc = this->GetActiveDocument();//pOldView->GetDocument();//new CDocument[1];
	m_pNewActiveView->Create(NULL, NULL, 0L, rect, // and the frame
		this, 0, &context);
}

void CMainFrame::OnDownfile()
{
	// TODO: Add your command handler code here
	CString filter;
	filter = "All Supported Files(*.ini)|*.ini|";
	filter+= "All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,(LPCSTR)filter);
	if (dlg.DoModal() != IDOK)
		return;

	CString fileName = dlg.GetFileName();
	CString filePath = dlg.GetPathName();
	int i = filePath.Find(fileName);
	filePath = filePath.Mid(0, i);

	//AfxMessageBox(filePath);

	CStringArray arrStr;
	arrStr.RemoveAll();
	arrStr.Add("/mnt/");
	arrStr.Add(fileName);
	arrStr.Add(filePath);

	AfxBeginThread(DownloadFile, &arrStr);
	DownLoadDlg.DoModal();
}


void CMainFrame::OnConnect()
{
	Cnetlink tempDlg;
	OnShutdown();
	tempDlg.DoModal();
}

void CMainFrame::OnShutdown()
{

	if(SocketInterf.Socket[0])
	{
		_close(SocketInterf.Socket[0]);
		SocketInterf.Socket[0] = 0;
	}

	if(SocketInterf.Socket[1])
	{
		_close(SocketInterf.Socket[1]);
		SocketInterf.Socket[1] = 0;
	}

	LoginIn = false;
}

void CMainFrame::OnResetMk()
{
	// TODO: Add your command handler code here
	CallReset();
}
