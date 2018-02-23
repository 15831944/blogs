#if !defined(AFX_SXJZSCFGVIEW_H__D5CC2716_51C7_4C82_BE68_51FEF8589626__INCLUDED_)
#define AFX_SXJZSCFGVIEW_H__D5CC2716_51C7_4C82_BE68_51FEF8589626__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SxJzsCfgView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSxJzsCfgView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CSxJzsCfgView : public CFormView
{
protected:
	CSxJzsCfgView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSxJzsCfgView)

// Form Data
public:
	//{{AFX_DATA(CSxJzsCfgView)
	enum { IDD = IDD_SXJZS_VIEW };
	CComboBox	m_LineType;
	CComboBox	m_LineNo;
	CComboBox	m_Enable;
	CEdit	m_Input;
	CListCtrl	m_List1;
	int		m_SboNum;
	CString	m_Version;
	int		m_LineNum;
	int		m_PNumPerLine;
	BOOL	m_Check5;
	BOOL	m_Check6;
	int		m_SwitchNum;
	BOOL	m_Check1;
	BOOL	m_Check2;
	BOOL	m_Check3;
	BOOL	m_Check4;
	BOOL	m_Check7;
	int		m_FixActTime;
	int		m_ZXCHZTime;
	int		m_FZXCHZTime;
	CString	m_strEdit;
	int		m_LeftDTUNum;
	//}}AFX_DATA

// Attributes
public:
	protected:
	int nItem, nSubItem;
	CListCtrl* listArray[1];
	bool bEverEdited;
	int LineType;//线路类型:0-主线;1-分支线
	int SwitchType;//开关类型(0-断路器, 1-负荷开关)

// Operations
public:
protected:
	void InitListCtrl();
	void LoadSxjzsConfig(int);
	void yulan();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSxJzsCfgView)
public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	virtual ~CSxJzsCfgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSxJzsCfgView)
	afx_msg void OnSave();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEdit1();
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnSelchangeCombo3();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnKillfocusEdit2();
	afx_msg void OnChangeEdit5();
	afx_msg void OnKillfocusEdit5();
	afx_msg void OnKillfocusCombo5();
	afx_msg void OnSelchangeCombo2();
	afx_msg void OnKillfocusCombo2();
	afx_msg void OnSelchangeCombo4();
	afx_msg void OnKillfocusEdit3();
	afx_msg void OnCANCEl();
	afx_msg void OnCheck7();
	afx_msg void OnChangeEdit6();
	afx_msg void OnKillfocusEdit6();
	afx_msg void OnKillfocusList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEdit8();
	afx_msg void OnChangeEdit9();
	afx_msg void OnKillfocusEdit8();
	afx_msg void OnKillfocusEdit9();
	afx_msg void OnSelchangeCombo5();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnChangeEdit11();
	afx_msg void OnKillfocusCombo3();
	afx_msg void OnSetfocusCombo3();
	afx_msg void OnCANCElAgo(int);
	afx_msg void OnSaveAgo(int);
	afx_msg void OnChangeEdit13();
	afx_msg void OnKillfocusEdit13();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	afx_msg void OnKillfocusEdit11();
	//}}AFX_MSG
	afx_msg LRESULT OnMsgSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SXJZSCFGVIEW_H__D5CC2716_51C7_4C82_BE68_51FEF8589626__INCLUDED_)
