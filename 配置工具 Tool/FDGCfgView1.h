#if !defined(AFX_FDGCFGVIEW1_H__A1370089_9AE1_4261_AF41_3ECC125E95CE__INCLUDED_)
#define AFX_FDGCFGVIEW1_H__A1370089_9AE1_4261_AF41_3ECC125E95CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FDGCfgView1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFDGCfgView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CFDGCfgView : public CFormView
{
protected:
	CFDGCfgView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFDGCfgView)

// Form Data
public:
	//{{AFX_DATA(CFDGCfgView)
	enum { IDD = IDD_FDG_VIEW };
	CEdit	m_Input;
	CComboBox	m_Enable;
	CComboBox	m_FDGType;
	CListCtrl	m_List1;
	BOOL	m_Check1;
	BOOL	m_Check2;
	BOOL	m_Check3;
	BOOL	m_Check4;
	BOOL	m_Check5;
	BOOL	m_Check6;
	int		m_FixActTime;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	void InitListCtrl();//2017-4-26
	void LoadFDGConfig();//2017-4-26

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFDGCfgView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate();
	
	//}}AFX_VIRTUAL

// Implementation
protected:
	int CMode;//FTU接线方式
	int DMode;//控制器模式
	int SType;//分段模式规格
	int AType;//自适应模式
	int SwType, nItem, nSubItem;
	CListCtrl* listArray[1];
	bool bEverEdited;

	virtual ~CFDGCfgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFDGCfgView)
	afx_msg LRESULT OnMsgSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	afx_msg void OnRadio8();
	afx_msg void OnRadio9();
	afx_msg void OnRadio10();
	afx_msg void OnRadio11();
	afx_msg void OnRadio12();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnRadio13();
	afx_msg void OnRadio14();
	afx_msg void OnRadio15();
	afx_msg void OnEditchangeCombo1();
	afx_msg void OnChangeEdit1();
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnKillfocusCombo2();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEdit2();
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FDGCFGVIEW1_H__A1370089_9AE1_4261_AF41_3ECC125E95CE__INCLUDED_)
