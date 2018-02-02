// FloatEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "FloatEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFloatEdit

CFloatEdit::CFloatEdit()
{
}

CFloatEdit::~CFloatEdit()
{
}


BEGIN_MESSAGE_MAP(CFloatEdit, CEdit)
	//{{AFX_MSG_MAP(CFloatEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFloatEdit message handlers

void CFloatEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CString str;
	int start,end;
	int pointstart = 0;
	if(nChar < 0x20)
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		return;
	}

	if((nChar>='0') && (nChar<='9'))
	{
		CEdit::GetWindowText(str);
		CEdit::GetSel(start, end);
		pointstart = str.Find('.');
		if(pointstart >= start)
		{
			CEdit::OnChar(nChar, nRepCnt, nFlags);
			return;
		}
		str = str.Left(start) + str.Right(str.GetLength() - end);
		start = str.Find('.');
		if((start >= 0) && (str.GetLength() - start) > 2)
			return;
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else if(nChar=='.')
	{
		CEdit::GetWindowText(str);
		if(str.Find('.') < 0)
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		else
		{
			CEdit::GetSel(start,end);
			str = str.Mid(start,end-start);
			if(str.Find('.') >= 0)
				CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
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
