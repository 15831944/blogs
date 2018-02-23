
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
	ON_WM_CREATE()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CTestView 构造/析构

CTestView::CTestView()
	: m_strLine(_T(""))
	, m_ptOrigin(0)
	, m_nWidth(0)
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

// 窗口重绘时调用(传入的CDC是哪个?)
void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码(以下添加的代码都是基于pDC的)
	
	CString str("牛逼闪闪的王慧勇先生");
	pDC->TextOut(100, 50, str);
	// 获取字符串在窗口上显示时的宽度和高度
	CSize sz = pDC->GetTextExtent(str);

	// 装载一个以ID标识的字符串资源到现存的字符串对象中, 用的时候进行加载, 不需要每次都重新初始化
	str.LoadString(IDS_STRING130);	// 此宏在 Resource.h 中生成定义
	pDC->TextOutA(0, 150, str);

	// path bracket 路径层
	pDC->BeginPath();
	pDC->Rectangle(100, 50, 100 + sz.cx, 50 + sz.cy);
	pDC->EndPath();
	pDC->SelectClipPath(RGN_DIFF);		// 路径层作为剪切区域(同一个DC, 客户区域内)

	for (int i = 0; i <= 300; i += 10)
	{
		// 横线
		pDC->MoveTo(0, i);
		pDC->LineTo(300, i);
		// 竖线
		pDC->MoveTo(i, 0);
		pDC->LineTo(i, 300);
	}
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


// CTestView 消息处理程序(添加本类的成员函数)

// 窗口创建之后(此函数只执行一次)
int CTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	
	CClientDC dc(this);		// 跟 OnDraw 中的 DC 是同一个???
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);	// 获取当前设备描述表中文本字体的信息, 系统字体尺寸给结构体
	// GetSystemMetrics
	bitmap.LoadBitmapA("newBitMap.bmp");
	// 在窗口创建之后, 创建插入符, 默认为隐藏, 没有成员访问操作符, 表明这个函数是本类的(继承自 CWnd)成员函数
	CreateSolidCaret(tm.tmAveCharWidth / 8, tm.tmHeight);
	// CreateCaret(&bitmap);			// 创建图形插入符
	ShowCaret();					// 显示插入符(没有调用 SetCaretPos 函数，默认在(0, 0)位置)

	SetTimer(1, 100, nullptr);		// 100 ms
	return 0;
}


void CTestView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);	// 都是同一个 DC ???
	CFont font;
	font.CreatePointFont(300, "华文行楷", nullptr);
	CFont *pOldFont = dc.SelectObject(&font);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	if (0x0d == nChar)	// 输入字符为回车CR
	{
		m_strLine.Empty();	// 但是上一行的字符不会被重绘
		m_ptOrigin.y += tm.tmHeight;
	}
	else if (0x08 == nChar) // 退格BS
	{
		COLORREF clr = dc.SetTextColor(dc.GetBkColor());
		dc.TextOutA(m_ptOrigin.x, m_ptOrigin.y, m_strLine);		// 将字符串设置为背景色当作删除的效果, 否则计算字符长度来重绘很麻烦
		m_strLine = m_strLine.Left(m_strLine.GetLength() - 1);	// 如果字符本身为空, 即在新行输入退格, 也不会出错?
		dc.SetTextColor(clr);	// 恢复旧颜色
	}
	else
	{
		m_strLine += (char)nChar;
	}
	// 从插入符的位置进行输出
	CSize sz = dc.GetTextExtent(m_strLine);
	CPoint pt;
	pt.x = m_ptOrigin.x + sz.cx;
	pt.y = m_ptOrigin.y;
	SetCaretPos(pt);
	dc.TextOutA(m_ptOrigin.x, m_ptOrigin.y, m_strLine);
	dc.SelectObject(pOldFont);
	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	SetCaretPos(point);				// 鼠标点击定位插入符
	m_strLine.Empty();				// 清空字符串
	m_ptOrigin = point;				// 保存鼠标坐标值
	CView::OnLButtonDown(nFlags, point);
}


void CTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (1 == nIDEvent)
	{
		m_nWidth += 5;

		CClientDC dc(this);
		TEXTMETRIC tm;
		dc.GetTextMetrics(&tm);
		// 矩形区域
		CRect rect;
		rect.left = 0;
		rect.top = 150;
		rect.right = m_nWidth;
		rect.bottom = rect.top + tm.tmHeight;

		dc.SetTextColor(RGB(255, 0, 0));
		CString str;
		str.LoadStringA(IDS_STRING130);
		dc.DrawText(str, rect, DT_LEFT);

		rect.top = 100;
		rect.bottom = rect.top + tm.tmHeight;
		dc.DrawText(str, rect, DT_RIGHT);

		CSize sz = dc.GetTextExtent(str);
		if (m_nWidth > sz.cx)
		{
			m_nWidth = 0;
			dc.SetTextColor(RGB(0, 255, 0));
			dc.TextOutA(0, 150, str);
		}
	}
	CView::OnTimer(nIDEvent);
}
