#if !defined(AFX_FLTDLG_H__C49C7FF1_3463_465A_A38B_0F9DF0BA497B__INCLUDED_)
#define AFX_FLTDLG_H__C49C7FF1_3463_465A_A38B_0F9DF0BA497B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FltDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFltDlg form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CFltDlg : public CFormView
{
protected:
	CFltDlg();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFltDlg)

// Form Data
public:
	//{{AFX_DATA(CFltDlg)
	enum { IDD = IDD_FLTDLG };
	CListCtrl	m_FltList;
	int		m_Edit1;
	//}}AFX_DATA
protected:
	void InsertItems();
	void SetCell(HWND hWnd1, CString value, int nRow, int nCol);
	CString GetItemText(HWND hWnd, int nItem, int nSubItem) const;
	int nItem, nSubItem;
	CMenu mMenu;
	bool bEverEdited;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFltDlg)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFltDlg();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFltDlg)
	afx_msg void OnAdditem();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRemoveitem();
	afx_msg void OnEdit();
	afx_msg void OnOK();
	afx_msg void OnSave();
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemAdd();
	afx_msg void OnItemEdit();
	afx_msg void OnItemRemove();
	afx_msg void OnItemSave();
	afx_msg void OnRevert();
	afx_msg void OnItemCancel();
	//}}AFX_MSG
	afx_msg LRESULT OnMsgSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLTDLG_H__C49C7FF1_3463_465A_A38B_0F9DF0BA497B__INCLUDED_)
