
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
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	ON_COMMAND(IDM_DIALOG, &CTestView::OnDialog)
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

// 单击菜单"对话框"的响应函数
void CTestView::OnDialog()
{
	// TODO: 在此添加命令处理程序代码

	CTestDlg dlg;	// 已关联到指定ID号的对话框
	dlg.DoModal();	// 创建并显示模态对话框, 不需要传入ID号, 且在显示过程中(阻塞在这里)不会被销毁, 因此 dlg 可以是局部变量, 单击OK后对话框会被销毁
	
	/*
	CTestDlg *pDlg = new CTestDlg();	// 非模态对话框不能是局部变量, 但是用指针又会造成内存泄漏, 应使用数据成员
	pDlg->Create(IDD_DIALOG1, this);	// 创建非模态对话框, 参数为对话框的ID号和父窗口指针
	pDlg->ShowWindow(SW_SHOW);			// 显示非模态对话框, 单击OK后不会被销毁, 默认由基类的CDialog::OnOk函数响应, 调用 CDialog::EndDialog 函数将其隐藏, 可在派生类中实现 OnOk 函数进行销毁
	*/
}
