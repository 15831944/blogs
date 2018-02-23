#if !defined(AFX_DOSBODLG_H__2D1EB18C_D388_4A35_96FF_E9850701EB33__INCLUDED_)
#define AFX_DOSBODLG_H__2D1EB18C_D388_4A35_96FF_E9850701EB33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DoSboDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDoSboDlg form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDoSboDlg : public CFormView
{
protected:
	CDoSboDlg();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CDoSboDlg)

// Form Data
public:
	//{{AFX_DATA(CDoSboDlg)
	enum { IDD = IDD_SBO_DO_DLG };
	CListCtrl	m_DoList;
	CListCtrl	m_SboList;
	int		m_SboWaitTime;
	int		m_SboNum;
	int		m_DoNum;
	//}}AFX_DATA
protected:
	void InsertItems();
	void SetCell(HWND hWnd1, CString value, int nRow, int nCol);
	CString GetItemText(HWND hWnd, int nItem, int nSubItem) const;
	int nItem, nSubItem;

	int mSelControl;
	CMenu mMenu;
	bool bEverEdited;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoSboDlg)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDoSboDlg();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDoSboDlg)
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOK();
	afx_msg void OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAdditem();
	afx_msg void OnRemoveitem();
	afx_msg void OnEdititem();
	afx_msg void OnSave();
	afx_msg void OnItemAdd();
	afx_msg void OnItemEdit();
	afx_msg void OnItemSave();
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemRemove();
	afx_msg void OnRevert();
	afx_msg void OnChangeEdit1();
	afx_msg void OnItemCancel();
	//}}AFX_MSG
	afx_msg LRESULT OnMsgSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOSBODLG_H__2D1EB18C_D388_4A35_96FF_E9850701EB33__INCLUDED_)
