
// TestDoc.cpp : CTestDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Test.h"
#endif

#include "TestDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTestDoc

IMPLEMENT_DYNCREATE(CTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestDoc, CDocument)
END_MESSAGE_MAP()


// CTestDoc ����/����

CTestDoc::CTestDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CTestDoc::~CTestDoc()
{
}

// �麯��
// ��������ʱ����ô˺���, Ĭ���½�һ��"�ޱ���"�ĵ�, ͨ�����ĵ�ģ�����
// ����ļ��½�ʱҲ����ô˺���, ͨ�� ID_FILE_NEW ������Ϣ��Ӧ���� CWinApp::OnFileNew
BOOL CTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	SetTitle("�ҵ��ĵ�����");
	return TRUE;
}




// CTestDoc ���л�
// �ļ��˵�, �򿪺ͱ�����������˺���
// ����ȱ���, �ٴ���ͬ���ļ�, �����ĵ������Ѿ����˹���, �Ͳ����ٽ���˺�����
// ���ĵ�Ӧ�ó���, ÿһʱ��ֻ����ʾһ���ĵ�, ����õ���ͬһ���ĵ�����ȥ������ͬ���ļ�
void CTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
		int		i = 4;
		char	c = 'a';
		float	f = 1.3;
		CString	str("wanghuiyong");
		ar << i << c << f << str;	// ͨ�� ar �������ݱ��浽�ļ���
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
		int		i;
		char	c;
		float	f;
		CString	str;
		ar >> i >> c >> f >> str;
	
		CString strResult;
		strResult.Format("%d, %c, %f, %s", i, c, f, str);
		AfxMessageBox(strResult);
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CTestDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CTestDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CTestDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CTestDoc ���

#ifdef _DEBUG
void CTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTestDoc ����
