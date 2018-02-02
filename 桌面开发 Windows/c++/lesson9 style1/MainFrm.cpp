
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "Test.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 全局变量
LPCSTR clsname = "wanghuiyong";


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(IDM_TEST, &CMainFrame::OnTest)
	ON_COMMAND(IDM_VIEW_NEWTOOL, &CMainFrame::OnViewNewtool)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_NEWTOOL, &CMainFrame::OnUpdateViewNewtool)
	ON_MESSAGE(UM_PROGRESS, OnProgress)	// 手动添加消息映射
	ON_WM_PAINT()
END_MESSAGE_MAP()

// 状态栏的定义
static UINT indicators[] =
{
	// 以下时字符串资源ID
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	// 在 String Table 中定义新的字符串资源
	IDS_TIMER,
	IDS_PROGRESS,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

// 也可以在窗口创建之后改变窗口的外观
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// 采用加载工具栏资源的方式
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);		// 工具栏可以停靠在任意位置
	EnableDocking(CBRS_ALIGN_ANY);					// 框架窗口可以被停靠在任意位置
	DockControlBar(&m_wndToolBar);					// 工具栏停靠在主框架窗口(建立停靠的关联)

	// 在窗口创建之后继续修改窗口的外观
	LONG currentStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	SetWindowLong(m_hWnd, GWL_STYLE, currentStyle & ~WS_MAXIMIZEBOX);		// 去掉最大化框
	SetClassLong(m_hWnd, GCL_HICON, (LONG)LoadIcon(nullptr, IDI_ERROR));	// 修改图标

	// 加载图标
	m_hIcon[0] = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	m_hIcon[1] = LoadIcon(theApp.m_hInstance, MAKEINTRESOURCE(IDI_ICON2));
	m_hIcon[2] = LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON3));
	SetClassLong(m_hWnd, GCL_HICON, (LONG)m_hIcon[0]);
	SetTimer(1, 1000, nullptr);

	// 创建自己的工具栏
	if (!m_newToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_newToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("未能创建新工具栏\n");
		return -1;      // 未能创建
	}
	m_newToolBar.EnableDocking(CBRS_ALIGN_ANY);		
	// EnableDocking(CBRS_ALIGN_ANY);				// 无须重复调用
	DockControlBar(&m_newToolBar);
	
	// 自定义状态栏
	CTime t = CTime::GetCurrentTime();
	CString str = t.Format("%H:%M:%S");
	CClientDC dc(this);
	CSize sz = dc.GetTextExtent(str);
	int index = 0;
	index = m_wndStatusBar.CommandToIndex(IDS_TIMER);
	m_wndStatusBar.SetPaneText(index, str, true);
	m_wndStatusBar.SetPaneInfo(index, IDS_TIMER, SBPS_NORMAL, sz.cx);

	// 创建进度栏
	/*
	CRect rect;
	index = m_wndStatusBar.CommandToIndex(IDS_PROGRESS);
	m_wndStatusBar.GetItemRect(index, &rect);			// 无法获取正确的进度栏尺寸
	// m_progress.Create(WS_CHILD | WS_VISIBLE, CRect(100, 200, 400, 220), this, 123);
	// m_progress.Create(WS_CHILD | WS_VISIBLE | PBS_VERTICAL, CRect(100, 50, 120, 350), this, 123);	// 垂直
	m_progress.Create(WS_CHILD | WS_VISIBLE, rect, &m_wndStatusBar, 123);
	m_progress.SetPos(50);
	*/
	
	// SendMessage(UM_PROGRESS);
	// PostMessage(UM_PROGRESS);

	return 0;
}

// 虚函数, 在窗口创建之前改变窗口的外观和大小
// CREATESTRUCT 结构体和 CreateWindowEx 函数的参数完全一致, 只不过顺序相反
// cs 是引用类型, 对其进行的修改会反映到 MFC 的底层代码中, 然后底层代码调用 CreateWindowEx 创建窗口
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  修改 CREATESTRUCT cs 来修改窗口类或样式
	cs.cx = 800;					// 窗口宽度
	cs.cy = 600;					// 窗口高度
	cs.lpszName = "王慧勇的窗口标题";	// 窗口标题
	cs.style &= ~FWS_ADDTOTITLE;	// 窗口样式, 默认显示的是文档的标题

	// 窗口类的设计和注册是由 MFC 底层实现的, 程序不可以去修改其样式, 但可以设计自己的窗口类并注册, 来修改样式
	// 注意图标属于框架类, 而光标, 窗口背景属于视图类
	WNDCLASS wndcls;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndcls.hCursor = LoadCursor(nullptr, IDC_HELP);
	wndcls.hIcon = LoadIcon(nullptr, IDI_ERROR);
	wndcls.hInstance = AfxGetInstanceHandle();	// 当前实例
	wndcls.lpfnWndProc = ::DefWindowProc;
	wndcls.lpszClassName = clsname;
	wndcls.lpszMenuName = nullptr;	// 菜单在 CTestApp::InitInstance() 中加载
	wndcls.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndcls);

	cs.lpszClass = clsname;
	// 修改框架类的图标而不用重新设计整个窗口类
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, 0, 0, LoadIcon(nullptr, IDI_WARNING));
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW);
	return TRUE;
}

// CMainFrame 诊断

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


// CMainFrame 消息处理程序


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	static int index = 1;
	SetClassLong(m_hWnd, GCL_HICON, (LONG)m_hIcon[index]);
	index = ++index % 3;

	CTime t = CTime::GetCurrentTime();
	CString str = t.Format("%H:%M:%S");
	CClientDC dc(this);
	CSize sz = dc.GetTextExtent(str);
	int i = m_wndStatusBar.CommandToIndex(IDS_TIMER);
	m_wndStatusBar.SetPaneText(i, str, true);
	m_wndStatusBar.SetPaneInfo(i, IDS_TIMER, SBPS_NORMAL, sz.cx);

	m_progress.StepIt();

	CFrameWnd::OnTimer(nIDEvent);
}

// 不论从菜单还是工具栏，点击都会响应
void CMainFrame::OnTest()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("test");
}


void CMainFrame::OnViewNewtool()
{
	// TODO: 在此添加命令处理程序代码
	/*
	if (m_newToolBar.IsWindowVisible())
	{
		m_newToolBar.ShowWindow(SW_HIDE);
	}
	else
	{
		m_newToolBar.ShowWindow(SW_SHOW);
	}
	RecalcLayout();					// 避免控制栏隐藏后控制条还在
	DockControlBar(&m_newToolBar);	// 悬浮状态时也能正常隐藏
	// 如何在显示时从上次消失的位置出现, 而不是默认的顶部
	;
	*/

	BOOL visible = m_newToolBar.IsWindowVisible();
	ShowControlBar(&m_newToolBar, !visible, false);
}


void CMainFrame::OnUpdateViewNewtool(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_newToolBar.IsWindowVisible());
}

LRESULT CMainFrame::OnProgress(WPARAM wParam, LPARAM lParam)
{
	// 创建进度栏, 本质是覆盖在将进度栏覆盖在状态栏的那个位置之上
	CRect rect;
	int index = m_wndStatusBar.CommandToIndex(IDS_PROGRESS);
	m_wndStatusBar.GetItemRect(index, &rect);
	m_progress.Create(WS_CHILD | WS_VISIBLE | PBS_SMOOTH, rect, &m_wndStatusBar, 123);
	m_progress.SetPos(50);
	return true;
}

void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	int index = m_wndStatusBar.CommandToIndex(IDS_PROGRESS);
	m_wndStatusBar.GetItemRect(index, &rect);
	if (!m_progress.m_hWnd)
	{
		m_progress.Create(WS_CHILD | WS_VISIBLE | PBS_SMOOTH, rect, &m_wndStatusBar, 123);
	}
	else
	{
		m_progress.MoveWindow(rect);
	}
	m_progress.SetPos(50);	// 进度50%
	// 不为绘图消息调用 CFrameWnd::OnPaint()
}
