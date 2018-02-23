#if !defined(AFX_INFODLG_H__6269F23A_0975_4B42_B7D7_46656FB30195__INCLUDED_)
#define AFX_INFODLG_H__6269F23A_0975_4B42_B7D7_46656FB30195__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CInfoDlg : public CFormView
{
protected:
	CInfoDlg();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CInfoDlg)

// Form Data
public:
	//{{AFX_DATA(CInfoDlg)
	enum { IDD = IDD_INFODLG };
	CString	m_Version;
	CString	m_Date;
	int		m_ProcessMax;
	int		m_NetMax;
	int		m_RTUMax;
	int		m_ObjectMax;
	int		m_FileMax;
	int		m_IopAiMax;
	int		m_IopDiMax;
	int		m_IopSboMax;
	int		m_IopDoMax;
	int		m_FaultMax;
	int		m_ScaleMax;
	int		m_ObjectTotal;
	int		m_ProtectMax;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoDlg)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CInfoDlg();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CInfoDlg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFODLG_H__6269F23A_0975_4B42_B7D7_46656FB30195__INCLUDED_)
