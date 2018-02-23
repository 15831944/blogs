#if !defined(AFX_PZK300NORMALCFGVIEW_H__895C02D0_0689_48B1_9238_BBD1FC2DDC2A__INCLUDED_)
#define AFX_PZK300NORMALCFGVIEW_H__895C02D0_0689_48B1_9238_BBD1FC2DDC2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pzk300NormalCfgView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPzk300NormalCfgView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "FloatEdit.h"
#include "NumberEdit.h"

class CPzk300NormalCfgView : public CFormView
{
protected:
	CPzk300NormalCfgView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPzk300NormalCfgView)

// Form Data
public:
	//{{AFX_DATA(CPzk300NormalCfgView)
	enum { IDD = IDD_PZK300_NORMAL_CFG };
	CButton	m_BN2;
	CButton	m_BN1;
	CComboBox	m_Combo1;
	CNumberEdit	m_Edit2;
	CEdit	m_Edit1;
	CFocusScrollListCtrl	m_List;
	//}}AFX_DATA

// Attributes
public:
protected:
	bool bCurViewIsActive;
	CFloatEdit mFloatEdit;
	CNumberEdit mNumberEdit;
	int nItem, nSubItem;
	CMenu mMenu;
	bool bEverEdited;
// Operations
public:

protected:
	CString GetUnionValue(Pzk300UnionStru val, int datatype);
	void LoadData();
	int GetDataTypeFromText(CString str);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPzk300NormalCfgView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPzk300NormalCfgView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CPzk300NormalCfgView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnKillfocusEdit2();
	afx_msg void OnKillfocusEdit3();
	afx_msg void OnKillfocusCombo1();
	afx_msg void OnSave();
	afx_msg void OnCANCEl();
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void On300Add();
	afx_msg void On300Remove();
	afx_msg void On300Insert();
	//}}AFX_MSG
	afx_msg LRESULT OnMsgSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PZK300NORMALCFGVIEW_H__895C02D0_0689_48B1_9238_BBD1FC2DDC2A__INCLUDED_)
