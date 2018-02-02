// DemoDoc.cpp : implementation of the CDemoDoc class
//

#include "stdafx.h"
#include "Demo.h"
#include "ReadPzkIni.h"
#include "MyFun.h"
#include "DemoDoc.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoDoc

IMPLEMENT_DYNCREATE(CDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CDemoDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDoc construction/destruction

CDemoDoc::CDemoDoc()
{
	// TODO: add one-time construction code here

}

CDemoDoc::~CDemoDoc()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDemoDoc serialization

void CDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDemoDoc diagnostics

#ifdef _DEBUG
void CDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoDoc commands

BOOL CDemoDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	// if (!CDocument::OnOpenDocument(lpszPathName))
	// 	return FALSE;

	// TODO: Add your specialized creation code here
	if(lpszPathName != mPzkIni.GetFileName())
	{
		if (pFrame->CurActiveView != 0)
		{
			CView *pView = (CView*)pFrame->m_wndSplitter->GetPane(0,1);
			BOOL bclose;
			bclose = pFrame->SendSaveMsg(pView,pFrame->CurActiveView);
			if( bclose != TRUE)
				return FALSE;
		}
		if(!mPzkIni.CloseFile())
		{
			return FALSE;
		}

	}
    if(!mPzkIni.OpenFile(lpszPathName))
		return FALSE;

	if (!pFrame->ShowOutLookBar())
		msgbox("œ‘ æOutLookBar ß∞‹!");

	AfxGetMainWnd()->SetWindowText(TitleName+lpszPathName);
	return TRUE;
}
/*
void CDemoDoc::OnFileOpen()
{
	// TODO: Add your command handler code here

	CString filter;
	filter = "All Supported Files(*.ini)|*.ini|";
	filter+= "All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL,0,(LPCSTR)filter);
	if (dlg.DoModal() != IDOK)
		return;
	CString lpszPathName = dlg.GetPathName();
	SetPathName(lpszPathName,TRUE);
	OnOpenDocument((LPCTSTR)lpszPathName);
}
*/
/*
void CDemoDoc::OnFileClose1()
{
	// TODO: Add your command handler code here
	if (!SaveModified())
		return;
	UpdateAllViews(NULL);
}

void CDemoDoc::OnFileNew()
{
	// TODO: Add your command handler code here
	msgbox("reach here");
	if(!mPzkIni.CloseFile())
		return;
	mPzkIni.NewFile();

	OnNewDocument();

	if (!pFrame->ShowOutLookBar())
		msgbox("œ‘ æOutLookBar ß∞‹!");
}
*/
