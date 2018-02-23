
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
#include "Graph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CScrollView)

BEGIN_MESSAGE_MAP(CTestView, CScrollView)
	ON_COMMAND(IDM_DOT, &CTestView::OnDot)
	ON_COMMAND(IDM_LINE, &CTestView::OnLine)
	ON_COMMAND(IDM_RECT, &CTestView::OnRect)
	ON_COMMAND(IDM_ELLIPSE, &CTestView::OnEllipse)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CTestView 构造/析构

CTestView::CTestView()
	: m_nDrawType(0)
	, m_ptOrigin(0)
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

	return CScrollView::PreCreateWindow(cs);
}

// CTestView 绘制
// 虚函数, 在 OnPaint 函数中被调用, 响应 WM_PAINT 消息
void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	// 将保存的图形对象进行重绘, 使用逻辑坐标
	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	pDC->SelectObject(pBrush);
	for (int i = 0; i < m_ptrArray.GetSize(); i++)
	{
		switch (((CGraph *)m_ptrArray.GetAt(i))->m_nDrawType)
		{
		case 1:
			pDC->SetPixel(((CGraph *)m_ptrArray.GetAt(i))->m_ptEnd, RGB(0, 0, 0));
			break;
		case 2:
			pDC->MoveTo(((CGraph *)m_ptrArray.GetAt(i))->m_ptOrigin);
			pDC->LineTo(((CGraph *)m_ptrArray.GetAt(i))->m_ptEnd);
			break;
		case 3:
			pDC->Rectangle(CRect(((CGraph *)m_ptrArray.GetAt(i))->m_ptOrigin, ((CGraph *)m_ptrArray.GetAt(i))->m_ptEnd));
			break;
		case 4:
			pDC->Ellipse(CRect(((CGraph *)m_ptrArray.GetAt(i))->m_ptOrigin, ((CGraph *)m_ptrArray.GetAt(i))->m_ptEnd));
			break;
		default:
			break;
		}
	}
}


// CTestView 诊断

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestView 消息处理程序


void CTestView::OnDot()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 1;
}


void CTestView::OnLine()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 2;
}


void CTestView::OnRect()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 3;
}


void CTestView::OnEllipse()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 4;
}


void CTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_ptOrigin = point;
	CScrollView::OnLButtonDown(nFlags, point);
}


void CTestView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	dc.SelectObject(pBrush);
	switch (m_nDrawType)
	{
	case 1:
		dc.SetPixel(point, RGB(0, 0, 0));
		break;
	case 2:
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		break;
	case 3:
		dc.Rectangle(CRect(m_ptOrigin, point));
		break;
	case 4:
		dc.Ellipse(CRect(m_ptOrigin, point));
		break;
	default:
		break;
	}
	// 保存时, 设备点转换为逻辑点(后面OnDraw绘制时, 逻辑点再转换为设备点)
	OnPrepareDC(&dc);			// 设备原点从(0, 0)变为(0, -100)
	dc.DPtoLP(&m_ptOrigin);		// 逻辑点Y坐标在这里要加100, 绘制时逻辑点转换为设备点再减100
	dc.DPtoLP(&point);

	/* 图形的保存 */
	// CGraph graph(m_nDrawType, m_ptOrigin, point);
	// m_ptrArray.Add(&graph);
	CGraph *pGraph = new CGraph(m_nDrawType, m_ptOrigin, point);	// 没有销毁
	m_ptrArray.Add(pGraph);

	CScrollView::OnLButtonUp(nFlags, point);
}


void CTestView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	OnPrepareDC(&dc);	// 调整显示上下文属性, 设置视口原点
	OnDraw(&dc);
	// 不为绘图消息调用 CScrollView::OnPaint()
}

// 在创建之后, OnDraw 绘制之前调用
void CTestView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	SetScrollSizes(MM_TEXT, CSize(800, 600));
}
