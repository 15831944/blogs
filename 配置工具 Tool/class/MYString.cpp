// MYString.cpp: implementation of the CMYString class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Demo.h"
#include "MYString.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyString::CMyString()
{

}

CMyString::~CMyString()
{

}

void CMyString::TrimSpace()
{
	TrimLeft(" ");
	TrimRight(" ");

	return;
}