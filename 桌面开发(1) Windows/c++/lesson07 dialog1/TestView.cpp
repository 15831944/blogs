
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
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	ON_COMMAND(IDM_DIALOG, &CTestView::OnDialog)
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

// �����˵�"�Ի���"����Ӧ����
void CTestView::OnDialog()
{
	// TODO: �ڴ���������������

	CTestDlg dlg;	// �ѹ�����ָ��ID�ŵĶԻ���
	dlg.DoModal();	// ��������ʾģ̬�Ի���, ����Ҫ����ID��, ������ʾ������(����������)���ᱻ����, ��� dlg �����Ǿֲ�����, ����OK��Ի���ᱻ����
	
	/*
	CTestDlg *pDlg = new CTestDlg();	// ��ģ̬�Ի������Ǿֲ�����, ������ָ���ֻ�����ڴ�й©, Ӧʹ�����ݳ�Ա
	pDlg->Create(IDD_DIALOG1, this);	// ������ģ̬�Ի���, ����Ϊ�Ի����ID�ź͸�����ָ��
	pDlg->ShowWindow(SW_SHOW);			// ��ʾ��ģ̬�Ի���, ����OK�󲻻ᱻ����, Ĭ���ɻ����CDialog::OnOk������Ӧ, ���� CDialog::EndDialog ������������, ������������ʵ�� OnOk ������������
	*/
}
