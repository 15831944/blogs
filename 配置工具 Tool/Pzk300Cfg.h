#if !defined(AFX_PZK300CFG_H__D3371945_F838_40F9_A7A3_2DACD4971D16__INCLUDED_)
#define AFX_PZK300CFG_H__D3371945_F838_40F9_A7A3_2DACD4971D16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pzk300Cfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPzk300Cfg form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "NumberEdit.h"

class CPzk300Cfg : public CFormView
{
protected:
	CPzk300Cfg();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPzk300Cfg)

// Form Data
public:
	//{{AFX_DATA(CPzk300Cfg)
	enum { IDD = IDD_PZK300CFG };
	CComboBox	m_hormanic;
	CString	m_pw;
	CString	m_addr;
	int		m_ct1;
	float	m_wp;
	float	m_wq;
	int		m_u3;
	int		m_u4;
	int		m_i0;
	int		m_thdu;
	float	m_cos;
	float	m_k;
	int		m_td;
	int		m_powercut;
	int		m_ct2;
	//}}AFX_DATA

// Attributes
public:

private:
	CNumberEdit mNumberEdit,mNumberEdit1,mNumberEdit2,mNumberEdit3;

protected:
	bool bEverEdited;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPzk300Cfg)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPzk300Cfg();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CPzk300Cfg)
	afx_msg void OnSave();
	afx_msg void OnCancel();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
	afx_msg void OnChangeEdit4();
	afx_msg void OnChangeEdit5();
	afx_msg void OnChangeEdit6();
	afx_msg void OnChangeEdit7();
	afx_msg void OnChangeEdit8();
	afx_msg void OnChangeEdit9();
	afx_msg void OnChangeEdit10();
	afx_msg void OnChangeEdit11();
	afx_msg void OnChangeEdit12();
	afx_msg void OnChangeEdit13();
	afx_msg void OnChangeEdit14();
	afx_msg void OnChangeEdit16();
	afx_msg void OnKillfocusEdit7();
	afx_msg void OnKillfocusEdit8();
	afx_msg void OnKillfocusEdit9();
	afx_msg void OnKillfocusEdit10();
	afx_msg void OnKillfocusEdit11();
	afx_msg void OnKillfocusEdit12();
	afx_msg void OnKillfocusEdit13();
	//}}AFX_MSG
	afx_msg LRESULT OnMsgSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PZK300CFG_H__D3371945_F838_40F9_A7A3_2DACD4971D16__INCLUDED_)
