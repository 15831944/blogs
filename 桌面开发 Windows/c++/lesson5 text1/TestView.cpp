
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
	ON_WM_CREATE()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CTestView ����/����

CTestView::CTestView()
	: m_strLine(_T(""))
	, m_ptOrigin(0)
	, m_nWidth(0)
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

// �����ػ�ʱ����(�����CDC���ĸ�?)
void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���(������ӵĴ��붼�ǻ���pDC��)
	
	CString str("ţ������������������");
	pDC->TextOut(100, 50, str);
	// ��ȡ�ַ����ڴ�������ʾʱ�Ŀ�Ⱥ͸߶�
	CSize sz = pDC->GetTextExtent(str);

	// װ��һ����ID��ʶ���ַ�����Դ���ִ���ַ���������, �õ�ʱ����м���, ����Ҫÿ�ζ����³�ʼ��
	str.LoadString(IDS_STRING130);	// �˺��� Resource.h �����ɶ���
	pDC->TextOutA(0, 150, str);

	// path bracket ·����
	pDC->BeginPath();
	pDC->Rectangle(100, 50, 100 + sz.cx, 50 + sz.cy);
	pDC->EndPath();
	pDC->SelectClipPath(RGN_DIFF);		// ·������Ϊ��������(ͬһ��DC, �ͻ�������)

	for (int i = 0; i <= 300; i += 10)
	{
		// ����
		pDC->MoveTo(0, i);
		pDC->LineTo(300, i);
		// ����
		pDC->MoveTo(i, 0);
		pDC->LineTo(i, 300);
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


// CTestView ��Ϣ�������(��ӱ���ĳ�Ա����)

// ���ڴ���֮��(�˺���ִֻ��һ��)
int CTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	
	CClientDC dc(this);		// �� OnDraw �е� DC ��ͬһ��???
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);	// ��ȡ��ǰ�豸���������ı��������Ϣ, ϵͳ����ߴ���ṹ��
	// GetSystemMetrics
	bitmap.LoadBitmapA("newBitMap.bmp");
	// �ڴ��ڴ���֮��, ���������, Ĭ��Ϊ����, û�г�Ա���ʲ�����, ������������Ǳ����(�̳��� CWnd)��Ա����
	CreateSolidCaret(tm.tmAveCharWidth / 8, tm.tmHeight);
	// CreateCaret(&bitmap);			// ����ͼ�β����
	ShowCaret();					// ��ʾ�����(û�е��� SetCaretPos ������Ĭ����(0, 0)λ��)

	SetTimer(1, 100, nullptr);		// 100 ms
	return 0;
}


void CTestView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this);	// ����ͬһ�� DC ???
	CFont font;
	font.CreatePointFont(300, "�����п�", nullptr);
	CFont *pOldFont = dc.SelectObject(&font);
	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);
	if (0x0d == nChar)	// �����ַ�Ϊ�س�CR
	{
		m_strLine.Empty();	// ������һ�е��ַ����ᱻ�ػ�
		m_ptOrigin.y += tm.tmHeight;
	}
	else if (0x08 == nChar) // �˸�BS
	{
		COLORREF clr = dc.SetTextColor(dc.GetBkColor());
		dc.TextOutA(m_ptOrigin.x, m_ptOrigin.y, m_strLine);		// ���ַ�������Ϊ����ɫ����ɾ����Ч��, ��������ַ��������ػ���鷳
		m_strLine = m_strLine.Left(m_strLine.GetLength() - 1);	// ����ַ�����Ϊ��, �������������˸�, Ҳ�������?
		dc.SetTextColor(clr);	// �ָ�����ɫ
	}
	else
	{
		m_strLine += (char)nChar;
	}
	// �Ӳ������λ�ý������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	SetCaretPos(point);				// �������λ�����
	m_strLine.Empty();				// ����ַ���
	m_ptOrigin = point;				// �����������ֵ
	CView::OnLButtonDown(nFlags, point);
}


void CTestView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (1 == nIDEvent)
	{
		m_nWidth += 5;

		CClientDC dc(this);
		TEXTMETRIC tm;
		dc.GetTextMetrics(&tm);
		// ��������
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
