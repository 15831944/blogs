#if !defined(AFX_TESTVIEW_H__CC104FC8_C371_4258_B135_5D7A0A107310__INCLUDED_)
#define AFX_TESTVIEW_H__CC104FC8_C371_4258_B135_5D7A0A107310__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CTestView : public CFormView
{
protected:
	CTestView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTestView)

// Form Data
public:
	//{{AFX_DATA(CTestView)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CTestView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTVIEW_H__CC104FC8_C371_4258_B135_5D7A0A107310__INCLUDED_)
