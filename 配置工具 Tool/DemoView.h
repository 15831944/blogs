// DemoView.h : interface of the CDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEMOVIEW_H__250FB43A_FCEB_49F3_AF3E_B7C61B37BFB0__INCLUDED_)
#define AFX_DEMOVIEW_H__250FB43A_FCEB_49F3_AF3E_B7C61B37BFB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DemoDoc.h"

class CDemoView : public CView
{
protected: // create from serialization only
	DECLARE_DYNCREATE(CDemoView)
public:
	CDemoView();

// Attributes
public:
	CDemoDoc* GetDocument();
protected:
	bool runing;
	RECT rect;
	CDC  *pViewDc;
	int  cx,cy;
	CString str;
// Operations
public:

protected:
	static UINT CDemoView::RunStr(LPVOID para);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDemoView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DemoView.cpp
inline CDemoDoc* CDemoView::GetDocument()
   { return (CDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOVIEW_H__250FB43A_FCEB_49F3_AF3E_B7C61B37BFB0__INCLUDED_)
