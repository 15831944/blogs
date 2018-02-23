
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "Test.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ȫ�ֱ���
LPCSTR clsname = "wanghuiyong";


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(IDM_TEST, &CMainFrame::OnTest)
	ON_COMMAND(IDM_VIEW_NEWTOOL, &CMainFrame::OnViewNewtool)
	ON_UPDATE_COMMAND_UI(IDM_VIEW_NEWTOOL, &CMainFrame::OnUpdateViewNewtool)
	ON_MESSAGE(UM_PROGRESS, OnProgress)	// �ֶ������Ϣӳ��
	ON_WM_PAINT()
END_MESSAGE_MAP()

// ״̬���Ķ���
static UINT indicators[] =
{
	// ����ʱ�ַ�����ԴID
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	// �� String Table �ж����µ��ַ�����Դ
	IDS_TIMER,
	IDS_PROGRESS,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

// Ҳ�����ڴ��ڴ���֮��ı䴰�ڵ����
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// ���ü��ع�������Դ�ķ�ʽ
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);		// ����������ͣ��������λ��
	EnableDocking(CBRS_ALIGN_ANY);					// ��ܴ��ڿ��Ա�ͣ��������λ��
	DockControlBar(&m_wndToolBar);					// ������ͣ��������ܴ���(����ͣ���Ĺ���)

	// �ڴ��ڴ���֮������޸Ĵ��ڵ����
	LONG currentStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	SetWindowLong(m_hWnd, GWL_STYLE, currentStyle & ~WS_MAXIMIZEBOX);		// ȥ����󻯿�
	SetClassLong(m_hWnd, GCL_HICON, (LONG)LoadIcon(nullptr, IDI_ERROR));	// �޸�ͼ��

	// ����ͼ��
	m_hIcon[0] = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	m_hIcon[1] = LoadIcon(theApp.m_hInstance, MAKEINTRESOURCE(IDI_ICON2));
	m_hIcon[2] = LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON3));
	SetClassLong(m_hWnd, GCL_HICON, (LONG)m_hIcon[0]);
	SetTimer(1, 1000, nullptr);

	// �����Լ��Ĺ�����
	if (!m_newToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_newToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("δ�ܴ����¹�����\n");
		return -1;      // δ�ܴ���
	}
	m_newToolBar.EnableDocking(CBRS_ALIGN_ANY);		
	// EnableDocking(CBRS_ALIGN_ANY);				// �����ظ�����
	DockControlBar(&m_newToolBar);
	
	// �Զ���״̬��
	CTime t = CTime::GetCurrentTime();
	CString str = t.Format("%H:%M:%S");
	CClientDC dc(this);
	CSize sz = dc.GetTextExtent(str);
	int index = 0;
	index = m_wndStatusBar.CommandToIndex(IDS_TIMER);
	m_wndStatusBar.SetPaneText(index, str, true);
	m_wndStatusBar.SetPaneInfo(index, IDS_TIMER, SBPS_NORMAL, sz.cx);

	// ����������
	/*
	CRect rect;
	index = m_wndStatusBar.CommandToIndex(IDS_PROGRESS);
	m_wndStatusBar.GetItemRect(index, &rect);			// �޷���ȡ��ȷ�Ľ������ߴ�
	// m_progress.Create(WS_CHILD | WS_VISIBLE, CRect(100, 200, 400, 220), this, 123);
	// m_progress.Create(WS_CHILD | WS_VISIBLE | PBS_VERTICAL, CRect(100, 50, 120, 350), this, 123);	// ��ֱ
	m_progress.Create(WS_CHILD | WS_VISIBLE, rect, &m_wndStatusBar, 123);
	m_progress.SetPos(50);
	*/
	
	// SendMessage(UM_PROGRESS);
	// PostMessage(UM_PROGRESS);

	return 0;
}

// �麯��, �ڴ��ڴ���֮ǰ�ı䴰�ڵ���ۺʹ�С
// CREATESTRUCT �ṹ��� CreateWindowEx �����Ĳ�����ȫһ��, ֻ����˳���෴
// cs ����������, ������е��޸Ļᷴӳ�� MFC �ĵײ������, Ȼ��ײ������� CreateWindowEx ��������
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  �޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.cx = 800;					// ���ڿ��
	cs.cy = 600;					// ���ڸ߶�
	cs.lpszName = "�����µĴ��ڱ���";	// ���ڱ���
	cs.style &= ~FWS_ADDTOTITLE;	// ������ʽ, Ĭ����ʾ�����ĵ��ı���

	// ���������ƺ�ע������ MFC �ײ�ʵ�ֵ�, ���򲻿���ȥ�޸�����ʽ, ����������Լ��Ĵ����ಢע��, ���޸���ʽ
	// ע��ͼ�����ڿ����, �����, ���ڱ���������ͼ��
	WNDCLASS wndcls;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndcls.hCursor = LoadCursor(nullptr, IDC_HELP);
	wndcls.hIcon = LoadIcon(nullptr, IDI_ERROR);
	wndcls.hInstance = AfxGetInstanceHandle();	// ��ǰʵ��
	wndcls.lpfnWndProc = ::DefWindowProc;
	wndcls.lpszClassName = clsname;
	wndcls.lpszMenuName = nullptr;	// �˵��� CTestApp::InitInstance() �м���
	wndcls.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndcls);

	cs.lpszClass = clsname;
	// �޸Ŀ�����ͼ������������������������
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, 0, 0, LoadIcon(nullptr, IDI_WARNING));
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW);
	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

// ���۴Ӳ˵����ǹ����������������Ӧ
void CMainFrame::OnTest()
{
	// TODO: �ڴ���������������
	MessageBox("test");
}


void CMainFrame::OnViewNewtool()
{
	// TODO: �ڴ���������������
	/*
	if (m_newToolBar.IsWindowVisible())
	{
		m_newToolBar.ShowWindow(SW_HIDE);
	}
	else
	{
		m_newToolBar.ShowWindow(SW_SHOW);
	}
	RecalcLayout();					// ������������غ����������
	DockControlBar(&m_newToolBar);	// ����״̬ʱҲ����������
	// �������ʾʱ���ϴ���ʧ��λ�ó���, ������Ĭ�ϵĶ���
	;
	*/

	BOOL visible = m_newToolBar.IsWindowVisible();
	ShowControlBar(&m_newToolBar, !visible, false);
}


void CMainFrame::OnUpdateViewNewtool(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_newToolBar.IsWindowVisible());
}

LRESULT CMainFrame::OnProgress(WPARAM wParam, LPARAM lParam)
{
	// ����������, �����Ǹ����ڽ�������������״̬�����Ǹ�λ��֮��
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
	// TODO: �ڴ˴������Ϣ����������
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
	m_progress.SetPos(50);	// ����50%
	// ��Ϊ��ͼ��Ϣ���� CFrameWnd::OnPaint()
}
