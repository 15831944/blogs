
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
#include "Graph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	ON_COMMAND(IDM_FILE_WIRTE, &CTestView::OnFileWirte)
	ON_COMMAND(IDM_FILE_READ, &CTestView::OnFileRead)
	ON_COMMAND(IDM_DOT, &CTestView::OnDot)
	ON_COMMAND(IDM_LINE, &CTestView::OnLine)
	ON_COMMAND(IDM_RECT, &CTestView::OnRect)
	ON_COMMAND(IDM_ELLIPSE, &CTestView::OnEllipse)
//	ON_WM_MBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CTestView ����/����

CTestView::CTestView()
	: m_nDrawType(0)
	, m_ptOrigin(0)
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

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	int nCount = m_obArray.GetSize();
	for (int i = 0; i < nCount; i++)
	{
		CGraph *pGraph = (CGraph *)m_obArray.GetAt(i);
		pGraph->Draw(pDC);
	}
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
	CFile file("Test.txt", CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);	// �鵵�������ļ�
	int		i = 4;
	char	c = 'a';
	float	f = 1.3;				// ������������
	CString	str("wanghuiyong");		// ������������
	ar << i << c << f << str;		// �洢����(���ز��������), ���д�벻��׷��
}


void CTestView::OnFileRead()
{
	// TODO: �ڴ���������������
	CFile file("Test.txt", CFile::modeRead);
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


void CTestView::OnDot()
{
	// TODO: �ڴ���������������
	m_nDrawType = 1;
}


void CTestView::OnLine()
{
	// TODO: �ڴ���������������
	m_nDrawType = 2;
}


void CTestView::OnRect()
{
	// TODO: �ڴ���������������
	m_nDrawType = 3;
}


void CTestView::OnEllipse()
{
	// TODO: �ڴ���������������
	m_nDrawType = 4;
}


void CTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_ptOrigin = point;
	CView::OnLButtonDown(nFlags, point);
}


void CTestView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// ͼ�εı���
	CGraph *pGraph =new CGraph(m_nDrawType, m_ptOrigin, point);
	m_obArray.Add(pGraph);
	CView::OnLButtonUp(nFlags, point);
}
