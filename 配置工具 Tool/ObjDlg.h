#if !defined(AFX_OBJDLG_H__2DAB2094_559F_4BBA_8AF8_6647D7B3D8C9__INCLUDED_)
#define AFX_OBJDLG_H__2DAB2094_559F_4BBA_8AF8_6647D7B3D8C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ObjDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CObjDlg form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CObjDlg : public CFormView
{
protected:
	CObjDlg();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CObjDlg)

// Form Data
public:
	//{{AFX_DATA(CObjDlg)
	enum { IDD = IDD_OBJDLG };
	CComboBox	m_atCurrentPort;
	CComboBox	m_valid;
	CString	m_name;
	int		m_Index;
	int		m_RTUid;
	int		m_ObjType;
	int		m_ObjSize;
	int		m_Sequence;
	int		m_Source;
	int		m_RelateProc;
	int		m_Scale;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjDlg)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CObjDlg();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CObjDlg)
	afx_msg void OnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJDLG_H__2DAB2094_559F_4BBA_8AF8_6647D7B3D8C9__INCLUDED_)
