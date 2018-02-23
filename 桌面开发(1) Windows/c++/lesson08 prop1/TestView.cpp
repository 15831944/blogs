
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
#include "PropSheet.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	ON_COMMAND(ID_PROPERTYSHEET, &CTestView::OnPropertysheet)
END_MESSAGE_MAP()

// CTestView 构造/析构

CTestView::CTestView()
{
	// TODO: 在此处添加构造代码
	m_iOccupation = -1;
	m_strWorkAddr = "";
	memset(m_bLike, 0, sizeof(m_bLike));
	m_strSalary = "";
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
	CFont font;
	font.CreatePointFont(300, "华文行楷");
	CFont *pOldFont;
	pOldFont = pDC->SelectObject(&font);
	CString strTemp;
	strTemp = "你的职业: ";
	switch (m_iOccupation)
	{
	case 0:
		strTemp += "程序员";
		break;
	case 1:
		strTemp += "系统工程师";
		break;
	case 2:
		strTemp += "项目经理";
		break;
	default:
		break;
	}
	pDC->TextOutA(0, 0, strTemp);

	strTemp = "你的工作地点: " + m_strWorkAddr;
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	pDC->TextOutA(0, tm.tmHeight, strTemp);

	strTemp = "你的兴趣爱好: ";
	CString like[4] = {"足球 ", "篮球 ", "排球 ", "游泳 "};
	for (int i = 0; i < 4; i++)
	{
		if (m_bLike[i])
			strTemp += like[i];
	}
	pDC->TextOutA(0, tm.tmHeight * 2, strTemp);

	strTemp = "你的薪资水平: " + m_strSalary;
	pDC->TextOutA(0, tm.tmHeight * 3, strTemp);

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

// 点击主菜单上的按钮时的事件处理程序, 可以交给任何一个类进行消息映射
void CTestView::OnPropertysheet()
{
	// TODO: 在此添加命令处理程序代码
	CPropSheet propSheet("属性表单程序");
	propSheet.SetWizardMode();		// 将属性表单变成向导模式
	INT_PTR result = propSheet.DoModal();		// 属性表单窗口被销毁, 但属性表单对象还在
	if (ID_WIZFINISH == result)
	{
		m_iOccupation = propSheet.m_prop1.m_occupation;
		m_strWorkAddr = propSheet.m_prop1.m_workAddr;
		m_bLike[0] = propSheet.m_prop2.m_football;
		m_bLike[1] = propSheet.m_prop2.m_basketball;
		m_bLike[2] = propSheet.m_prop2.m_volleyball;
		m_bLike[3] = propSheet.m_prop2.m_swim;
		m_strSalary = propSheet.m_prop3.m_srtSalary;

		Invalidate();
	}

}
