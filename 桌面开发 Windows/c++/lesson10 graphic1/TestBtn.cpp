// TestBtn.cpp : ʵ���ļ�
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



// CTestBtn ��Ϣ�������




void CTestBtn::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  ������Ĵ����Ի���ָ����
	UINT uStyle = DFCS_BUTTONPUSH;
	ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);	// ֻ�԰�ť��Ч
	// ��ť���
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		uStyle |= DFCS_PUSHED;
	}
	// ���ư�ť��
	::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, DFC_BUTTON, uStyle);
	// ��ȡ��ť�ı�
	CString strText;
	GetWindowText(strText);
	// ���ư�ť�ı�
	COLORREF crOldColor = ::SetTextColor(lpDrawItemStruct->hDC, RGB(255, 0, 0));
	::DrawText(lpDrawItemStruct->hDC, strText,strText.GetLength(),
	          &lpDrawItemStruct->rcItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	::SetTextColor(lpDrawItemStruct->hDC, crOldColor);
}
