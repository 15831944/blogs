
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
	ON_COMMAND(IDM_DOT, &CTestView::OnDot)
	ON_COMMAND(IDM_LINE, &CTestView::OnLine)
	ON_COMMAND(IDM_RECT, &CTestView::OnRect)
	ON_COMMAND(IDM_ELLIPSE, &CTestView::OnEllipse)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
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
// �麯��, �� OnPaint �����б�����, ��Ӧ WM_PAINT ��Ϣ
void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

	// �������ͼ�ζ�������ػ�
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
	/* ͼ�εı��� */
	// CGraph graph(m_nDrawType, m_ptOrigin, point);
	// m_ptrArray.Add(&graph);
	CGraph *pGraph = new CGraph(m_nDrawType, m_ptOrigin, point);	// û������
	m_ptrArray.Add(pGraph);

	CView::OnLButtonUp(nFlags, point);
}


void CTestView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CView::OnPaint()
}
