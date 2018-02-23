
// TestDoc.cpp : CTestDoc 类的实现
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

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTestDoc

IMPLEMENT_DYNCREATE(CTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestDoc, CDocument)
END_MESSAGE_MAP()


// CTestDoc 构造/析构

CTestDoc::CTestDoc()
{
	// TODO: 在此添加一次性构造代码

}

CTestDoc::~CTestDoc()
{
}

// 虚函数
// 程序启动时会调用此函数, 默认新建一个"无标题"文档, 通过但文档模板调用
// 点击文件新建时也会调用此函数, 通过 ID_FILE_NEW 命令消息相应函数 CWinApp::OnFileNew
BOOL CTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	SetTitle("我的文档标题");
	return TRUE;
}




// CTestDoc 序列化
// 文件菜单, 打开和保存命令都会进入此函数
// 如果先保存, 再打开相同的文件, 由于文档对象已经有了关联, 就不会再进入此函数了
// 单文档应用程序, 每一时刻只能显示一个文档, 因此用的是同一个文档对象去关联不同的文件
void CTestDoc::Serialize(CArchive& ar)
{
	POSITION pos = GetFirstViewPosition();
	CTestView *pView = (CTestView *)GetNextView(pos);
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		/*
		int		i = 5;
		char	c = 'b';
		float	f = 1.4;
		CString	str("wanghuiyong");
		ar << i << c << f << str;	// 通过 ar 对象将数据保存到文件中
		*/
		int nCount = pView->m_obArray.GetSize();	// 视图类有多少个 CGraph 对象
		ar << nCount;
		for (int i = 0; i < nCount; i++)
		{
			ar << pView->m_obArray.GetAt(i);	// 这里框架会调用 CGraph::Serialize 函数
		}
	}
	else
	{
		// TODO: 在此添加加载代码
		/*
		int		i;
		char	c;
		float	f;
		CString	str;
		ar >> i >> c >> f >> str;
	
		CString strResult;
		strResult.Format("%d, %c, %f, %s", i, c, f, str);
		AfxMessageBox(strResult);
		*/
		int nCount;
		ar >> nCount;
		CGraph *pGraph;		// 会调用那个不带参数的构造函数
		for (int i = 0; i < nCount; i++)
		{
			ar >> pGraph;
			pView->m_obArray.Add(pGraph);
		}
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CTestDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CTestDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CTestDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CTestDoc 诊断

#ifdef _DEBUG
void CTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTestDoc 命令
