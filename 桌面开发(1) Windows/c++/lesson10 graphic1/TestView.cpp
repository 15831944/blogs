
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
#include "SettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	ON_COMMAND(IDM_DOT, &CTestView::OnDot)
	ON_COMMAND(IDM_LINE, &CTestView::OnLine)
	ON_COMMAND(IDM_RECTANGLE, &CTestView::OnRectangle)
	ON_COMMAND(IDM_ELLIPSE, &CTestView::OnEllipse)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(IDM_SETTING, &CTestView::OnSetting)
	ON_COMMAND(IDM_COLOR, &CTestView::OnColor)
	ON_COMMAND(IDM_FONT, &CTestView::OnFont)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CTestView 构造/析构

CTestView::CTestView()
	: m_nDrawType(0)
	, m_ptOrigin(0)
	, m_nLineWidth(0)
	, m_nLineStyle(0)
	, m_strFontName(_T(""))
{
	// TODO: 在此处添加构造代码
	m_clr = RGB(255, 0, 0);

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

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CFont *pOldFont = pDC->SelectObject(&m_font);
	pDC->TextOutA(0, 0, m_strFontName);
	pDC->SelectObject(pOldFont);
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


void CTestView::OnRectangle()
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
	CView::OnLButtonDown(nFlags, point);
}


void CTestView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	CPen pen(/*PS_SOLID  */(int)m_nLineStyle, m_nLineWidth, m_clr);
	dc.SelectObject(&pen);
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	CBrush *pBrush = CBrush::FromHandle(hBrush);
	dc.SelectObject(pBrush);
	switch(m_nDrawType)
	{
	case 1:
		dc.SetPixel(point, m_clr);
		break;
	case 2:
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		break;
	case 3:
		dc.Rectangle(CRect(m_ptOrigin, point));	// 重载了 LPCRECT 操作符, 因此不用加取地址符
		break;
	case 4:
		dc.Ellipse(CRect(m_ptOrigin, point));
		break;
	default:
		break;
	}
	CView::OnLButtonUp(nFlags, point);
}

// 主菜单按钮命令响应
void CTestView::OnSetting()
{
	// TODO: 在此添加命令处理程序代码
	CSettingDlg dlg;	// 每次点击菜单按钮都重新生成对话框对象
	// 初始化为上次的值
	dlg.m_nLineWidth = m_nLineWidth;
	dlg.m_nLineStyle = m_nLineStyle;
	dlg.m_clr = m_clr;
	// 确认修改
	if (IDOK == dlg.DoModal())
	{
		m_nLineWidth = dlg.m_nLineWidth;
		m_nLineStyle = dlg.m_nLineStyle;
	}
}


void CTestView::OnColor()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog dlg;
	dlg.m_cc.Flags |= CC_RGBINIT;
	dlg.m_cc.rgbResult = m_clr;
	if (IDOK == dlg.DoModal())
	{
		m_clr = dlg.m_cc.rgbResult;
	}
}


void CTestView::OnFont()
{
	// TODO: 在此添加命令处理程序代码
	CFontDialog dlg;
	if (IDOK == dlg.DoModal())
	{
		if (m_font.m_hObject)
			m_font.DeleteObject();
		m_font.CreateFontIndirectA(dlg.m_cf.lpLogFont);
		m_strFontName = dlg.m_cf.lpLogFont->lfFaceName;
		Invalidate();	// 使窗口进行重绘
	}
}


BOOL CTestView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_NEW_BITMAP);
	BITMAP bmp;
	bitmap.GetBitmap(&bmp);
	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);
	dcCompatible.SelectObject(&bitmap);
	CRect rect;
	GetClientRect(&rect);
	// pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcCompatible, 0, 0, SRCCOPY);	// 按照原始尺寸拷贝
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dcCompatible, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
	return true;
	// return CView::OnEraseBkgnd(pDC);
}
