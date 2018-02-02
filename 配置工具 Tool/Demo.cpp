// Demo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Demo.h"

#include "MainFrm.h"
#include "DemoDoc.h"
#include "DemoView.h"
#include "ReadPzkIni.h"
#include "MyFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CMainFrame		*pFrame;
CString			TitleName = "MK保护故障逻辑编辑工具 1.0  ";
CStringArray	IpArr;

/////////////////////////////////////////////////////////////////////////////
// CDemoApp
static void LoadIpHistory();
static void SaveIpHistory();

BEGIN_MESSAGE_MAP(CDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CDemoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoApp construction

CDemoApp::CDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_uFtp = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDemoApp object

CDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDemoApp initialization

BOOL CDemoApp::InitInstance()
{
	AfxEnableControlContainer();
	OpenUsb();						// 连接USB设备
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();	// Load standard INI file options (including MRU)
	LoadIpHistory();			// 读取 IpHistroy.ini 配置文件

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	// 单文档模板
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDemoDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CDemoView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	pFrame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_KEHUI_ICON);
	AfxGetMainWnd()->SetIcon(hIcon,FALSE);
	AfxGetMainWnd()->SetWindowText(TitleName);
	((CMainFrame *)AfxGetMainWnd())->CreateNewView();
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CDemoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDemoApp message handlers

int CDemoApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	SaveIpHistory();
	return CWinApp::ExitInstance();
}

// 连接USB设备
BOOL CDemoApp::OpenUsb()
{
	HDEVINFO  DeviceList = USBGetDeviceList( );
    int       devID      = 0;

    // Detect whether any MOTUSB device is attached to the system
    DWORD status = USBOpenDevice( DeviceList, 0, &m_USBDevice );
    if ( status != USB_STATUS_OK )
    {
        // The device should be connected. If it's not so show error
        USBReleaseDeviceList( DeviceList );
//        AfxMessageBox("Device doesn't connected to the system\n"
//                      "Please connect the device and run application again", MB_OK | MB_ICONSTOP);
        return FALSE;
    }

    USBCloseDevice(&m_USBDevice);

    // Lookup for the 1st device with VID = 0xABCD and PID = 0x1235
    for ( devID=0; devID<255; devID++)
    {
        DWORD status = USBOpenDevice( DeviceList, 0, &m_USBDevice );
        if ( status != USB_STATUS_OK )
            break;

        USB_DEVICE_DESCRIPTOR desc;
        USBGetDeviceDesc(m_USBDevice, &desc, 0);
        if (desc.idVendor == 0xABCD && desc.idProduct == 0x1235) {
            break;
        }
        USBCloseDevice( &m_USBDevice );
    }

    if ( !m_USBDevice ) {
//        AfxMessageBox("USB Device with VendorID = 0xABCD and ProductID = 0x1235 doesn't found\n"
//                      "Please connect the device and run program again", MB_OK | MB_ICONSTOP);
        return FALSE;
    }

    USBReleaseDeviceList( DeviceList );

    m_uFtp = Uftp_Connect(m_USBDevice);
    if ( !m_uFtp ) {
        CString msg;
        LPCTSTR szErrText = USBGetErrorText(GetLastError());
//        msg.Format("Can't connect to device interface: %s", szErrText);
        LocalFree( (void*) szErrText );
        AfxMessageBox( msg );
        return FALSE;
    }

	char SayHello[] = "$helo\n";
	SendToUsb(SayHello, strlen(SayHello), RSP_HELO, false);
	return TRUE;
}

// 程序启动时, 读取 IpHistroy.ini 配置文件
staitc void LoadIpHistory()
{
	CStdioFile	file;
	char		file_path[256];

	/* 获取文件路径并打开文件 */
	if(GetCurrentDirectory(256, file_path) <= 0)
		return;
	strcat(file_path,"\\IpHistroy.ini");
	if(file.Open(file_path, CFile::modeRead, NULL) == NULL)
		return;

	/* 读取IP地址存入字符串数组 */
	IpArr.RemoveAll();
	CString ip;
	while(file.ReadString(ip) > 0)
		IpArr.Add(ip);

	/* 读取完毕关闭文件 */
	file.Close();
	return;
}

// 程序退出时, 保存 IpHistroy.ini 配置文件
static void SaveIpHistory()
{
	CStdioFile	file;
	char		file_path[256];

	/* 获取文件路径并打开文件 */
	if(GetCurrentDirectory(256, file_path) <= 0)
		return;
	strcat(file_path, "\\IpHistroy.ini");
	file.Open(file_path, CFile::modeWrite | CFile::modeCreate, NULL);

	/* 将字符串数组中存在的IP地址保存到文件中 */
	int IpNum = IpArr.GetSize();
	int i = 0;
	while(i < IpNum)
	{
		file.WriteString(IpArr.GetAt(i)+"\n");
		i++;
	}

	/* 写入完成关闭文件 */
	file.Close();
	return;
}
