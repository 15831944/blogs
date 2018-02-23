
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
	ON_COMMAND(IDM_FILE_WIRTE, &CTestView::OnFileWirte)
	ON_COMMAND(IDM_FILE_READ, &CTestView::OnFileRead)
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


void CTestView::OnFileWirte()
{
	// TODO: 在此添加命令处理程序代码
	CFile file("1.txt", CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);
	int		i = 4;
	char	c = 'a';
	float	f = 1.3;
	CString	str("wanghuiyong");
	ar << i << c << f << str;		// 存储数据(重载插入运算符)
}


void CTestView::OnFileRead()
{
	// TODO: 在此添加命令处理程序代码
	CFile file("1.txt", CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	int		i;
	char	c;
	float	f;
	CString	str;
	ar >> i >> c >> f >> str;		// 需按照相同的顺序提取
	
	CString strResult;
	strResult.Format("%d, %c, %f, %s", i, c, f, str);
	MessageBox(strResult);
}
