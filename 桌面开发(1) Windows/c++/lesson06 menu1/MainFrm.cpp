
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
	ON_COMMAND(ID_TEST, &CMainFrame::OnTest)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, &CMainFrame::OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, &CMainFrame::OnUpdateFileNew)
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
	// m_bAutoMenuEnable = false;	// �������ݲ˵�������������Ӧ�����Զ������������, ���ɳ���Ա���
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

	// �Բ˵�����б��(�Թ�)
	GetMenu()->GetSubMenu(0)->CheckMenuItem(1, MF_BYPOSITION | MF_CHECKED);				// ͨ���������ʲ˵���
	GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_FILE_NEW, MF_BYCOMMAND | MF_CHECKED);	// ͨ�� ID �ŷ���

	// ����ȱʡ�˵���(�Դ�����ʾ, һ���Ӳ˵�ֻ����һ��ȱʡ�˵���)
	GetMenu()->GetSubMenu(0)->SetDefaultItem(2, true);
	GetMenu()->GetSubMenu(0)->SetDefaultItem(ID_FILE_SAVE_AS, false);

	// ������λͼ��ǵĲ˵���
	CString str;
	str.Format("x = %d, y = %d", GetSystemMetrics(SM_CXMENUCHECK), GetSystemMetrics(SM_CYMENUCHECK));
	MessageBox(str);
	m_bitmap.LoadBitmapA("newBitmap");
	GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(0, MF_BYPOSITION, &m_bitmap, &m_bitmap);

	// �˵����ʹ��(����)
	GetMenu()->GetSubMenu(0)->EnableMenuItem(1, MF_BYPOSITION | MF_DISABLED);

	// ���������˵�
	SetMenu(nullptr);

	// ���ز˵�
	CMenu menu;		// �ֲ�����
	menu.LoadMenuA(IDR_MAINFRAME);
	SetMenu(&menu);
	menu.Detach();	// ���˵�����Ͷ���Ͽ�, ��ֲ���������ʱ���������������, ʹ�˵���Ȼ��Ч
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

// �����¼�����������Ϣ����Ϊ COMMAND

// �½����Ӳ˵���ť
void CMainFrame::OnTest()
{
	// TODO: �ڴ���������������
	MessageBox("MainFrame Clicked!");
}

// �����¼����������Ϣ����Ϊ UPDATE_COMMAND_UI

void CMainFrame::OnUpdateEditCut(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������

	if (ID_EDIT_CUT == pCmdUI->m_nID)
		pCmdUI->Enable();	// ��"�༭->����"�˵�������Ϊʹ��, �˵����͹������ж��ı�, ��Ϊ�õ���ͬһ��ID��, ���������ܲ�ͬ
}

void CMainFrame::OnUpdateFileNew(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������

	if (ID_FILE_NEW == pCmdUI->m_nID 
		|| 0 == pCmdUI->m_nIndex)
		pCmdUI->Enable(false);	// ��"�ļ�->�½�"�˵�������Ϊ��ʹ��
}
