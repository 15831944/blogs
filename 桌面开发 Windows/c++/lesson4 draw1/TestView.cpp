
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CTestView 构造/析构

CTestView::CTestView()
	: m_ptOrigin(0)
	, m_bDraw(false)
	, m_ptOld(0)
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

// 鼠标左键按下
void CTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// MessageBox("王慧勇使用鼠标左键单击视图");
	m_ptOrigin = m_ptOld = point;
	m_bDraw = true;
	CView::OnLButtonDown(nFlags, point);
}

// 鼠标左键弹起
void CTestView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bDraw = false;

	// 使用 HDC 句柄
	HDC hdc;
	hdc = ::GetDC(m_hWnd);								// 获取DC, 调用全局函数, 参数是本窗口句柄
	MoveToEx(hdc, m_ptOrigin.x, m_ptOrigin.y, NULL);	// 设置原点
	LineTo(hdc, point.x, point.y);						// 设置终点
	::ReleaseDC(m_hWnd, hdc);							// 释放 DC


	// 使用 CDC, CClientDC, CWindowDC 类
	CDC *pDC = GetDC();						// 调用 CWnd 成员函数
	pDC->MoveTo(m_ptOrigin);
	pDC->LineTo(point);
	ReleaseDC(pDC);							// 释放 DC


	CClientDC dc(this);						// CClientDC 对象在构造函数中获取 DC, 在析构函数中释放 DC 句柄, 构造函数传入本窗口
	CClientDC dc(GetParent());				// 传入父窗口(框架窗口)指针
	dc.MoveTo(m_ptOrigin);
	dc.LineTo(point);


	CWindowDC dc(this);
	CWindowDC dc(GetParent());				// 可以访问非客户区域(包括标题栏)
	CWindowDC dc(GetDesktopWindow());		// 获取哪个窗口就可以在哪里画, 桌面也是一个窗口
	dc.MoveTo(m_ptOrigin);
	dc.LineTo(point);


	// 使用 CPen, CBrush 类
	CClientDC dc(this);
	CPen pen(PS_SOLID, 5, RGB(255, 0, 0));
	CPen *pOldPen = dc.SelectObject(&pen);	// 将画笔选入设备描述表中, 返回旧的画笔
	dc.MoveTo(m_ptOrigin);
	dc.LineTo(point);
	dc.SelectObject(pOldPen);				// 恢复为先前的画笔


	CBitmap bitmap;
	bitmap.LoadBitmapA("D:\newBitmap.bmp");
	CBrush brush(&bitmap);
	CBrush brush(RGB(255, 0, 0));
	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));	// 将句柄转换为对象类型, FromHandle 是静态成员函数, 可以使用类名或实例调用
	CClientDC dc(this);
	dc.FillRect(CRect(m_ptOrigin, point), &brush);		// 不需要将画刷选入设备描述表中, 因为参数已经带了
	CBrush *pOldBrush = dc.SelectObject(pBrush);		// 将画刷选入设备描述表, 替换缺省的画刷
	dc.Rectangle(CRect(m_ptOrigin, point));				// 绘制矩形, 需要先将画刷选入设备描述表
	dc.SelectObject(pOldBrush);


	CView::OnLButtonUp(nFlags, point);
}

// 鼠标滚轮移动
void CTestView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen *pOldPen = dc.SelectObject(&pen);
	if (m_bDraw == true)
	{
		dc.SetROP2(R2_BLACK);	// 绘图模式

		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		dc.LineTo(m_ptOld);

		dc.MoveTo(m_ptOrigin);
		dc.MoveTo(m_ptOld);
		dc.LineTo(point);

		m_ptOrigin = point;
		m_ptOld = point;
	}
	dc.SelectObject(pOldPen);
	CView::OnMouseMove(nFlags, point);
}
