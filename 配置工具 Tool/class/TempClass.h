#if !defined(AFX_TEMPCLASS_H__5CD639DE_F464_4F06_BCBB_FDD9C3138ED3__INCLUDED_)
#define AFX_TEMPCLASS_H__5CD639DE_F464_4F06_BCBB_FDD9C3138ED3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TempClass.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTempClass form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CTempClass : public CFormView
{
protected:
	CTempClass();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTempClass)

// Form Data
public:
	//{{AFX_DATA(CTempClass)
	enum { IDD = IDD_Dlg };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTempClass)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTempClass();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CTempClass)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEMPCLASS_H__5CD639DE_F464_4F06_BCBB_FDD9C3138ED3__INCLUDED_)
