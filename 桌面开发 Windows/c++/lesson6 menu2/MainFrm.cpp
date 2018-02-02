
// MainFrm.cpp : CMainFrame ���ʵ��
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
	ON_COMMAND(IDM_HELLO, OnHello)	// �ֶ������Ϣӳ��
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
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
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// ����Ӳ˵�
	CMenu menu;
	menu.CreatePopupMenu();
	GetMenu()->AppendMenuA(MF_POPUP, (UINT)menu.m_hMenu, "׷���Ӳ˵�");
	GetMenu()->InsertMenuA(2, MF_BYPOSITION | MF_POPUP, (UINT)menu.m_hMenu, "�����Ӳ˵�");
	
	// ��Ӳ˵���
	menu.AppendMenuA(MF_STRING, 111, "Hello1");
	menu.AppendMenuA(MF_STRING, 112, "Hello2");
	menu.AppendMenuA(MF_STRING, 113, "Hello3");
	menu.AppendMenuA(MF_STRING, IDM_HELLO, "Hello4");
	menu.Detach();

	GetMenu()->GetSubMenu(0)->AppendMenuA(MF_STRING, 114, "Welcome");
	GetMenu()->GetSubMenu(0)->InsertMenuA(ID_FILE_OPEN, MF_BYCOMMAND | MF_STRING, 115, "HEHE");

	// ɾ���Ӳ˵�
	GetMenu()->DeleteMenu(1, MF_BYPOSITION);

	// ɾ���˵���
	GetMenu()->GetSubMenu(0)->DeleteMenu(2, MF_BYPOSITION);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

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

void CMainFrame::OnHello()
{
	MessageBox("Hello");
}