
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
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CTestView ����/����

CTestView::CTestView()
	: m_ptOrigin(0)
	, m_bDraw(false)
	, m_ptOld(0)
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

// ����������
void CTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// MessageBox("������ʹ��������������ͼ");
	m_ptOrigin = m_ptOld = point;
	m_bDraw = true;
	CView::OnLButtonDown(nFlags, point);
}

// ����������
void CTestView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bDraw = false;

	// ʹ�� HDC ���
	HDC hdc;
	hdc = ::GetDC(m_hWnd);								// ��ȡDC, ����ȫ�ֺ���, �����Ǳ����ھ��
	MoveToEx(hdc, m_ptOrigin.x, m_ptOrigin.y, NULL);	// ����ԭ��
	LineTo(hdc, point.x, point.y);						// �����յ�
	::ReleaseDC(m_hWnd, hdc);							// �ͷ� DC


	// ʹ�� CDC, CClientDC, CWindowDC ��
	CDC *pDC = GetDC();						// ���� CWnd ��Ա����
	pDC->MoveTo(m_ptOrigin);
	pDC->LineTo(point);
	ReleaseDC(pDC);							// �ͷ� DC


	CClientDC dc(this);						// CClientDC �����ڹ��캯���л�ȡ DC, �������������ͷ� DC ���, ���캯�����뱾����
	CClientDC dc(GetParent());				// ���븸����(��ܴ���)ָ��
	dc.MoveTo(m_ptOrigin);
	dc.LineTo(point);


	CWindowDC dc(this);
	CWindowDC dc(GetParent());				// ���Է��ʷǿͻ�����(����������)
	CWindowDC dc(GetDesktopWindow());		// ��ȡ�ĸ����ھͿ��������ﻭ, ����Ҳ��һ������
	dc.MoveTo(m_ptOrigin);
	dc.LineTo(point);


	// ʹ�� CPen, CBrush ��
	CClientDC dc(this);
	CPen pen(PS_SOLID, 5, RGB(255, 0, 0));
	CPen *pOldPen = dc.SelectObject(&pen);	// ������ѡ���豸��������, ���ؾɵĻ���
	dc.MoveTo(m_ptOrigin);
	dc.LineTo(point);
	dc.SelectObject(pOldPen);				// �ָ�Ϊ��ǰ�Ļ���


	CBitmap bitmap;
	bitmap.LoadBitmapA("D:\newBitmap.bmp");
	CBrush brush(&bitmap);
	CBrush brush(RGB(255, 0, 0));
	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));	// �����ת��Ϊ��������, FromHandle �Ǿ�̬��Ա����, ����ʹ��������ʵ������
	CClientDC dc(this);
	dc.FillRect(CRect(m_ptOrigin, point), &brush);		// ����Ҫ����ˢѡ���豸��������, ��Ϊ�����Ѿ�����
	CBrush *pOldBrush = dc.SelectObject(pBrush);		// ����ˢѡ���豸������, �滻ȱʡ�Ļ�ˢ
	dc.Rectangle(CRect(m_ptOrigin, point));				// ���ƾ���, ��Ҫ�Ƚ���ˢѡ���豸������
	dc.SelectObject(pOldBrush);


	CView::OnLButtonUp(nFlags, point);
}

// �������ƶ�
void CTestView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this);
	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen *pOldPen = dc.SelectObject(&pen);
	if (m_bDraw == true)
	{
		dc.SetROP2(R2_BLACK);	// ��ͼģʽ

		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		dc.LineTo(m_ptOld);

		dc.MoveTo(m_ptOrigin);
		dc.MoveTo(m_ptOld);
		dc.LineTo(point);

		m_ptOrigin = point;
		m_ptOld = point;
	}
	dc.SelectObject(pOldPen);
	CView::OnMouseMove(nFlags, point);
}
