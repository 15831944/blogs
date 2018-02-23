
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "Test.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_TEST, &CMainFrame::OnTest)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, &CMainFrame::OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, &CMainFrame::OnUpdateFileNew)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	// m_bAutoMenuEnable = false;	// 不再依据菜单项有无命令相应函数自动进行命令更新, 改由程序员完成
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

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
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// 对菜单项进行标记(对勾)
	GetMenu()->GetSubMenu(0)->CheckMenuItem(1, MF_BYPOSITION | MF_CHECKED);				// 通过索引访问菜单项
	GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_FILE_NEW, MF_BYCOMMAND | MF_CHECKED);	// 通过 ID 号访问

	// 设置缺省菜单项(以粗体显示, 一个子菜单只能有一个缺省菜单项)
	GetMenu()->GetSubMenu(0)->SetDefaultItem(2, true);
	GetMenu()->GetSubMenu(0)->SetDefaultItem(ID_FILE_SAVE_AS, false);

	// 设置用位图标记的菜单项
	CString str;
	str.Format("x = %d, y = %d", GetSystemMetrics(SM_CXMENUCHECK), GetSystemMetrics(SM_CYMENUCHECK));
	MessageBox(str);
	m_bitmap.LoadBitmapA("newBitmap");
	GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(0, MF_BYPOSITION, &m_bitmap, &m_bitmap);

	// 菜单项的使能(灰显)
	GetMenu()->GetSubMenu(0)->EnableMenuItem(1, MF_BYPOSITION | MF_DISABLED);

	// 移走整个菜单
	SetMenu(nullptr);

	// 加载菜单
	CMenu menu;		// 局部变量
	menu.LoadMenuA(IDR_MAINFRAME);
	SetMenu(&menu);
	menu.Detach();	// 将菜单句柄和对象断开, 则局部变量销毁时不会调用析构函数, 使菜单仍然有效
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

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

// 以下事件处理程序的消息类型为 COMMAND

// 新建的子菜单按钮
void CMainFrame::OnTest()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox("MainFrame Clicked!");
}

// 以下事件处理程序消息类型为 UPDATE_COMMAND_UI

void CMainFrame::OnUpdateEditCut(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码

	if (ID_EDIT_CUT == pCmdUI->m_nID)
		pCmdUI->Enable();	// 将"编辑->剪切"菜单项设置为使能, 菜单栏和工具栏中都改变, 因为用的是同一个ID号, 但索引可能不同
}

void CMainFrame::OnUpdateFileNew(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码

	if (ID_FILE_NEW == pCmdUI->m_nID 
		|| 0 == pCmdUI->m_nIndex)
		pCmdUI->Enable(false);	// 将"文件->新建"菜单项设置为不使能
}
