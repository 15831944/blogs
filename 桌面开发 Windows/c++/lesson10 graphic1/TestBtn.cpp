// TestBtn.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "TestBtn.h"


// CTestBtn

IMPLEMENT_DYNAMIC(CTestBtn, CButton)

CTestBtn::CTestBtn()
{

}

CTestBtn::~CTestBtn()
{
}


BEGIN_MESSAGE_MAP(CTestBtn, CButton)
END_MESSAGE_MAP()



// CTestBtn 消息处理程序




void CTestBtn::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项
	UINT uStyle = DFCS_BUTTONPUSH;
	ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);	// 只对按钮有效
	// 按钮风格
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		uStyle |= DFCS_PUSHED;
	}
	// 绘制按钮框
	::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, DFC_BUTTON, uStyle);
	// 获取按钮文本
	CString strText;
	GetWindowText(strText);
	// 绘制按钮文本
	COLORREF crOldColor = ::SetTextColor(lpDrawItemStruct->hDC, RGB(255, 0, 0));
	::DrawText(lpDrawItemStruct->hDC, strText,strText.GetLength(),
	          &lpDrawItemStruct->rcItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	::SetTextColor(lpDrawItemStruct->hDC, crOldColor);
}
