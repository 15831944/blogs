
// TestView.cpp : CTestView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Test.h"
#endif

#include "TestDoc.h"
#include "TestView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CTestView ����/����

CTestView::CTestView()
{
	// TODO: �ڴ˴���ӹ������

}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	extern LPCSTR clsname;
	cs.lpszClass = clsname;		// ��ͼ�ڿ��֮��, �Դ��ڱ����͹����޸�����ͼ�ϲŻ����ֳ���
	// �޸���ͼ��Ĺ��ͱ��������������������������
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, \
		LoadCursor(nullptr, IDC_CROSS), (HBRUSH)GetStockObject(BLACK_BRUSH), 0);
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW);	// ʹ��ȱʡֵ
	return CView::PreCreateWindow(cs);
}

// CTestView ����

void CTestView::OnDraw(CDC* /*pDC*/)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CTestView ���

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestView ��Ϣ�������


int CTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	SetClassLong(m_hWnd, GCL_HBRBACKGROUND, (LONG)GetStockObject(BLACK_BRUSH));	// �޸ı���
	SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)LoadCursor(nullptr, IDC_HELP));		// �޸Ĺ��
	return 0;
}


void CTestView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString str;
	str.Format("x = %d, y = %d", point.x, point.y);
	CMainFrame *frame = (CMainFrame *)GetParent();
	// frame->m_wndStatusBar.SetWindowText(str);
	// fframe->SetMessageText(str);
	// (frame->GetMessageBar())->SetWindowText(str);
	frame->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowText(str);

	CView::OnMouseMove(nFlags, point);
}
