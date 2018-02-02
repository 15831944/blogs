#if !defined(AFX_PZK300PROCFGVIEW_H__D8F9F3BE_21FE_4944_B06F_081F18589FC1__INCLUDED_)
#define AFX_PZK300PROCFGVIEW_H__D8F9F3BE_21FE_4944_B06F_081F18589FC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pzk300ProCfgView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPzk300ProCfgView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "NumberEdit.h"

class CPzk300ProCfgView : public CFormView
{
protected:
	CPzk300ProCfgView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPzk300ProCfgView)

// Form Data
public:
	//{{AFX_DATA(CPzk300ProCfgView)
	enum { IDD = IDD_PZK300_PROTECT_CFG };
	CButton	m_BN2;
	CNumberEdit	m_Edit2;
	CComboBox	m_Combo1;
	CButton	m_BN1;
	CEdit	m_Edit1;
	CFocusScrollListCtrl	m_List;
	//}}AFX_DATA

// Attributes
public:
protected:
	bool bCurViewIsActive;
	int nItem, nSubItem;
	CMenu mMenu;
	bool bEverEdited;
// Operations
public:

protected:
	void LoadData();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPzk300ProCfgView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPzk300ProCfgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CPzk300ProCfgView)
	afx_msg void On300Add();
	afx_msg void On300Insert();
	afx_msg void On300Remove();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnKillfocusEdit2();
	afx_msg void OnKillfocusCombo1();
	afx_msg void OnSave();
	afx_msg void OnCANCEl();
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScrollList1(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScrollList1(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	afx_msg LRESULT OnMsgSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PZK300PROCFGVIEW_H__D8F9F3BE_21FE_4944_B06F_081F18589FC1__INCLUDED_)
