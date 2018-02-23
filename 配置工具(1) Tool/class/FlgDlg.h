#if !defined(AFX_FLGDLG_H__92AA21AA_1EB8_464C_8929_27704F4EEEB7__INCLUDED_)
#define AFX_FLGDLG_H__92AA21AA_1EB8_464C_8929_27704F4EEEB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FlgDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFlgDlg form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CFlgDlg : public CFormView
{
protected:
	CFlgDlg();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFlgDlg)

// Form Data
public:
	//{{AFX_DATA(CFlgDlg)
	enum { IDD = IDD_FLTDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFlgDlg();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFlgDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLGDLG_H__92AA21AA_1EB8_464C_8929_27704F4EEEB7__INCLUDED_)
