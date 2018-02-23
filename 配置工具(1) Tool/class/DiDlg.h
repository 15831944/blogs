#if !defined(AFX_DIDLG_H__D3379371_2779_43C4_A4D7_116BAD987F11__INCLUDED_)
#define AFX_DIDLG_H__D3379371_2779_43C4_A4D7_116BAD987F11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DiDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDiDlg form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDiDlg : public CFormView
{
protected:
	CDiDlg();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDiDlg)

// Form Data
public:
	//{{AFX_DATA(CDiDlg)
	enum { IDD = IDD_DIDLG };
	CComboBox	m_Combo1;
	BOOL	m_Check1;
	BOOL	m_Check10;
	BOOL	m_Check11;
	BOOL	m_Check12;
	BOOL	m_Check13;
	BOOL	m_Check14;
	BOOL	m_Check15;
	BOOL	m_Check16;
	BOOL	m_Check17;
	BOOL	m_Check18;
	BOOL	m_Check9;
	BOOL	m_Check8;
	BOOL	m_Check7;
	BOOL	m_Check6;
	BOOL	m_Check5;
	BOOL	m_Check4;
	BOOL	m_Check32;
	BOOL	m_Check31;
	BOOL	m_Check30;
	BOOL	m_Check3;
	BOOL	m_Check29;
	BOOL	m_Check28;
	BOOL	m_Check27;
	BOOL	m_Check26;
	BOOL	m_Check25;
	BOOL	m_Check24;
	BOOL	m_Check23;
	BOOL	m_Check22;
	BOOL	m_Check21;
	BOOL	m_Check20;
	BOOL	m_Check2;
	BOOL	m_Check19;
	int		m_Edit1;
	int		m_Edit2;
	//}}AFX_DATA

// Attributes
public:

protected:
	bool bEverEdited;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiDlg)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDiDlg();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDiDlg)
	afx_msg void OnSave();
	afx_msg void OnCheck1();
	afx_msg void OnChangeEdit1();
	afx_msg void OnCheck10();
	afx_msg void OnCheck11();
	afx_msg void OnCheck12();
	afx_msg void OnCheck13();
	afx_msg void OnCheck14();
	afx_msg void OnCheck15();
	afx_msg void OnCheck16();
	afx_msg void OnCheck17();
	afx_msg void OnCheck18();
	afx_msg void OnCheck19();
	afx_msg void OnCheck2();
	afx_msg void OnCheck20();
	afx_msg void OnCheck21();
	afx_msg void OnCheck22();
	afx_msg void OnCheck23();
	afx_msg void OnCheck24();
	afx_msg void OnCheck25();
	afx_msg void OnCheck26();
	afx_msg void OnCheck27();
	afx_msg void OnCheck28();
	afx_msg void OnCheck29();
	afx_msg void OnCheck3();
	afx_msg void OnCheck30();
	afx_msg void OnCheck31();
	afx_msg void OnCheck32();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnCheck7();
	afx_msg void OnCheck8();
	afx_msg void OnCheck9();
	afx_msg void OnRevert();
	afx_msg void OnChangeEdit2();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnKillfocusEdit2();
	//}}AFX_MSG
	afx_msg LRESULT OnMsgSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIDLG_H__D3379371_2779_43C4_A4D7_116BAD987F11__INCLUDED_)
