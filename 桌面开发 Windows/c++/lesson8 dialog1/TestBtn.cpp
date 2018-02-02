// TestBtn.cpp : 实现文件
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



// CTestBtn 消息处理程序




void CTestBtn::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ShowWindow(SW_HIDE);
	m_pBtn->ShowWindow(SW_SHOW);
	
	CButton::OnMouseMove(nFlags, point);
}
