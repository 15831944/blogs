#if !defined(AFX_SCALEDLG1_H__09A9B44B_5F5B_4FF5_957F_AE74FECF1E13__INCLUDED_)
#define AFX_SCALEDLG1_H__09A9B44B_5F5B_4FF5_957F_AE74FECF1E13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScaleDlg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScaleDlg1 form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CScaleDlg1 : public CFormView
{
protected:
	CScaleDlg1();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CScaleDlg1)

// Form Data
public:
	//{{AFX_DATA(CScaleDlg1)
	enum { IDD = IDD_SCALEDLG };
	CListCtrl	m_List1;
	int		m_ScaleNum;
	CString	m_Input;
	//}}AFX_DATA

// Attributes
public:

protected:
	int nItem, nSubItem;
	bool bEverEdited;
	CMenu mMenu,*mSubMenu;
	CString GetItemText(HWND hWnd, int nItem, int nSubItem) const;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScaleDlg1)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CScaleDlg1();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CScaleDlg1)
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEdit2();
	afx_msg void OnSave();
	afx_msg void OnAdditem();
	afx_msg void OnRemoveitem();
	afx_msg void OnChangeEdit2();
	afx_msg void OnRevert();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEdititem();
	afx_msg void OnItemAdd();
	afx_msg void OnItemEdit();
	afx_msg void OnItemRemove();
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

#endif // !defined(AFX_SCALEDLG1_H__09A9B44B_5F5B_4FF5_957F_AE74FECF1E13__INCLUDED_)
