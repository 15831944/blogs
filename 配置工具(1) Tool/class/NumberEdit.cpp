// NumberEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "NumberEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNumberEdit

CNumberEdit::CNumberEdit()
{
}

CNumberEdit::~CNumberEdit()
{
}


BEGIN_MESSAGE_MAP(CNumberEdit, CEdit)
	//{{AFX_MSG_MAP(CNumberEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNumberEdit message handlers

void CNumberEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CString str;
	int start,end;
	if((nChar<0x20) || ((nChar>='0') && (nChar<='9')))
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else if(nChar == '-')
	{
		CEdit::GetWindowText(str);
		if(str.Find('-') < 0)
		{
			CEdit::GetSel(start, end);
			if(start == 0)
				CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
		else
		{
			CEdit::GetSel(start, end);
			str == str.Mid(start, end - start);
			if( (start == 0) && (str.Find('-') >= 0) )
				CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
	}
	else
		::MessageBeep(0xffffffff);
}
