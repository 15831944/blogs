#if !defined(AFX_PRODLG_H__5E4461DF_66C0_4FA5_99F9_FD1D76AA586C__INCLUDED_)
#define AFX_PRODLG_H__5E4461DF_66C0_4FA5_99F9_FD1D76AA586C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProDlg form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CProDlg : public CFormView
{
protected:
	CProDlg();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CProDlg)

// Form Data
public:
	//{{AFX_DATA(CProDlg)
	enum { IDD = IDD_PRODLG };
	CListCtrl	m_ProList;
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
	//{{AFX_VIRTUAL(CProDlg)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProDlg();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CProDlg)
	afx_msg void OnItemAdd();
	afx_msg void OnItemRemove();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemEdit();
	afx_msg void OnOK();
	afx_msg void OnSave();
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
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

#endif // !defined(AFX_PRODLG_H__5E4461DF_66C0_4FA5_99F9_FD1D76AA586C__INCLUDED_)
