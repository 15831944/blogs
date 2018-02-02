
// TestView.cpp : CTestView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CTestView 构造/析构

CTestView::CTestView()
{
	// TODO: 在此处添加构造代码

}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	extern LPCSTR clsname;
	cs.lpszClass = clsname;		// 视图在框架之上, 对窗口背景和光标的修改在视图上才会体现出来
	// 修改视图类的光标和背景而不用重新设计整个窗口类
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, \
		LoadCursor(nullptr, IDC_CROSS), (HBRUSH)GetStockObject(BLACK_BRUSH), 0);
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW);	// 使用缺省值
	return CView::PreCreateWindow(cs);
}

// CTestView 绘制

void CTestView::OnDraw(CDC* /*pDC*/)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CTestView 诊断

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestView 消息处理程序


int CTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetClassLong(m_hWnd, GCL_HBRBACKGROUND, (LONG)GetStockObject(BLACK_BRUSH));	// 修改背景
	SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)LoadCursor(nullptr, IDC_HELP));		// 修改光标
	return 0;
}


void CTestView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString str;
	str.Format("x = %d, y = %d", point.x, point.y);
	CMainFrame *frame = (CMainFrame *)GetParent();
	// frame->m_wndStatusBar.SetWindowText(str);
	// fframe->SetMessageText(str);
	// (frame->GetMessageBar())->SetWindowText(str);
	frame->GetDescendantWindow(AFX_IDW_STATUS_BAR)->SetWindowText(str);

	CView::OnMouseMove(nFlags, point);
}
