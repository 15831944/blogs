
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
	ON_COMMAND(IDM_DOT, &CTestView::OnDot)
	ON_COMMAND(IDM_LINE, &CTestView::OnLine)
	ON_COMMAND(IDM_RECTANGLE, &CTestView::OnRectangle)
	ON_COMMAND(IDM_ELLIPSE, &CTestView::OnEllipse)
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


void CTestView::OnRectangle()
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
	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
	dc.SelectObject(&pen);
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	CBrush *pBrush = CBrush::FromHandle(hBrush);
	dc.SelectObject(pBrush);
	switch(m_nDrawType)
	{
	case 1:
		dc.SetPixel(point, RGB(255, 0, 0));
		break;
	case 2:
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		break;
	case 3:
		dc.Rectangle(CRect(m_ptOrigin, point));	// ������ LPCRECT ������, ��˲��ü�ȡ��ַ��
		break;
	case 4:
		dc.Ellipse(CRect(m_ptOrigin, point));
		break;
	default:
		break;
	}
	CView::OnLButtonUp(nFlags, point);
}
