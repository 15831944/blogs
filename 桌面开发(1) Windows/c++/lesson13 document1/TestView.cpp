
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

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	ON_COMMAND(IDM_FILE_WIRTE, &CTestView::OnFileWirte)
	ON_COMMAND(IDM_FILE_READ, &CTestView::OnFileRead)
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


void CTestView::OnFileWirte()
{
	// TODO: �ڴ���������������
	CFile file("1.txt", CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);
	int		i = 4;
	char	c = 'a';
	float	f = 1.3;
	CString	str("wanghuiyong");
	ar << i << c << f << str;		// �洢����(���ز��������)
}


void CTestView::OnFileRead()
{
	// TODO: �ڴ���������������
	CFile file("1.txt", CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	int		i;
	char	c;
	float	f;
	CString	str;
	ar >> i >> c >> f >> str;		// �谴����ͬ��˳����ȡ
	
	CString strResult;
	strResult.Format("%d, %c, %f, %s", i, c, f, str);
	MessageBox(strResult);
}
