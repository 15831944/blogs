// TestBtn.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test.h"
#include "TestBtn.h"


// CTestBtn

IMPLEMENT_DYNAMIC(CTestBtn, CButton)

CTestBtn::CTestBtn()
{
	m_pBtn = nullptr;
}

CTestBtn::~CTestBtn()
{
}


BEGIN_MESSAGE_MAP(CTestBtn, CButton)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CTestBtn ��Ϣ�������




void CTestBtn::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ShowWindow(SW_HIDE);
	m_pBtn->ShowWindow(SW_SHOW);
	
	CButton::OnMouseMove(nFlags, point);
}
