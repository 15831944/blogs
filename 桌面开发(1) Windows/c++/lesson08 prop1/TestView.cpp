
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
#include "PropSheet.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	ON_COMMAND(ID_PROPERTYSHEET, &CTestView::OnPropertysheet)
END_MESSAGE_MAP()

// CTestView ����/����

CTestView::CTestView()
{
	// TODO: �ڴ˴���ӹ������
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
	CFont font;
	font.CreatePointFont(300, "�����п�");
	CFont *pOldFont;
	pOldFont = pDC->SelectObject(&font);
	CString strTemp;
	strTemp = "���ְҵ: ";
	switch (m_iOccupation)
	{
	case 0:
		strTemp += "����Ա";
		break;
	case 1:
		strTemp += "ϵͳ����ʦ";
		break;
	case 2:
		strTemp += "��Ŀ����";
		break;
	default:
		break;
	}
	pDC->TextOutA(0, 0, strTemp);

	strTemp = "��Ĺ����ص�: " + m_strWorkAddr;
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	pDC->TextOutA(0, tm.tmHeight, strTemp);

	strTemp = "�����Ȥ����: ";
	CString like[4] = {"���� ", "���� ", "���� ", "��Ӿ "};
	for (int i = 0; i < 4; i++)
	{
		if (m_bLike[i])
			strTemp += like[i];
	}
	pDC->TextOutA(0, tm.tmHeight * 2, strTemp);

	strTemp = "���н��ˮƽ: " + m_strSalary;
	pDC->TextOutA(0, tm.tmHeight * 3, strTemp);

	pDC->SelectObject(pOldFont);
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

// ������˵��ϵİ�ťʱ���¼��������, ���Խ����κ�һ���������Ϣӳ��
void CTestView::OnPropertysheet()
{
	// TODO: �ڴ���������������
	CPropSheet propSheet("���Ա�����");
	propSheet.SetWizardMode();		// �����Ա������ģʽ
	INT_PTR result = propSheet.DoModal();		// ���Ա����ڱ�����, �����Ա�������
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
