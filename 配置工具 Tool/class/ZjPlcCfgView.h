#if !defined(AFX_ZJPLCCFGVIEW_H__69FC757B_DD8D_485F_951C_7540C630FF82__INCLUDED_)
#define AFX_ZJPLCCFGVIEW_H__69FC757B_DD8D_485F_951C_7540C630FF82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZjPlcCfgView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZjPlcCfgView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CZjPlcCfgView : public CFormView
{
protected:
	CZjPlcCfgView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CZjPlcCfgView)

// Form Data
public:
	//{{AFX_DATA(CZjPlcCfgView)
	enum { IDD = IDD_ZJPLC_VIEW };
	CEdit	m_Editbox;
	CComboBox	m_ComBo1;
	CListCtrl	m_List;
	int		m_Total;
	int		m_RelcoseTime;
	int		m_PlcTime;
	BOOL	m_PlcEnable;
	BOOL	m_BztEnable1;
	BOOL	m_BztEnable2;
	int		m_LogicVol;
	//}}AFX_DATA

// Attributes
public:

protected:
	bool bEverEdited;
	int nItem, nSubItem;

// Operations
public:

protected:
	void UpdateList(bool[]);
	void LoadData();
	void ResetRelcose();
	bool GetRecloseEnable(CString sEnable);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZjPlcCfgView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CZjPlcCfgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CZjPlcCfgView)
	afx_msg void OnSave();
	afx_msg void OnCANCEl();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusCombo1();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnKillfocusEdit2();
	afx_msg void OnKillfocusEdit3();
	afx_msg void OnCheck4();
	afx_msg void OnChangeNormalvol();
	afx_msg void OnBztenable1();
	afx_msg void OnBztenable2();
	//}}AFX_MSG
	afx_msg LRESULT OnMsgSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZJPLCCFGVIEW_H__69FC757B_DD8D_485F_951C_7540C630FF82__INCLUDED_)
