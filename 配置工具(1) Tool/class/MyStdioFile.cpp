// MyStdioFile.cpp: implementation of the CMyStdioFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Demo.h"
#include "MyStdioFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyStdioFile::CMyStdioFile()
{

}

CMyStdioFile::~CMyStdioFile()
{

}

bool CMyStdioFile::ReadLineWithout2SideSpace(CString *LineString)
{
	bool EndOfFile;

	if(FALSE == ReadString(*LineString))
	    EndOfFile = false;
	else
		EndOfFile = true;

	LineString->TrimLeft(" ");
	LineString->TrimRight(" ");

	return EndOfFile;
}
