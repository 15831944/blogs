#if !defined(AFX_PULSEDLG_H__0E9C5C71_B341_41BB_B2AF_00D863D773FA__INCLUDED_)
#define AFX_PULSEDLG_H__0E9C5C71_B341_41BB_B2AF_00D863D773FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PulseDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPulseDlg form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CPulseDlg : public CFormView
{
protected:
	CPulseDlg();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPulseDlg)

// Form Data
public:
	//{{AFX_DATA(CPulseDlg)
	enum { IDD = IDD_PULSEDLG };
	CListCtrl	m_List1;
	int		m_PulseNum;
	//}}AFX_DATA
protected:
	bool bEverEdited;
	CMenu mMenu;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPulseDlg)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPulseDlg();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CPulseDlg)
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemAdd();
	afx_msg void OnItemRemove();
	afx_msg void OnItemEdit();
	afx_msg void OnOK();
	afx_msg void OnSave();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRevert();
	afx_msg void OnItemCancel();
	afx_msg void OnItemSave();
	//}}AFX_MSG
	afx_msg LRESULT OnMsgSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PULSEDLG_H__0E9C5C71_B341_41BB_B2AF_00D863D773FA__INCLUDED_)
