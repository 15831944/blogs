#if !defined(AFX_PROCDLG_H__A452D90B_C43B_4416_8547_74D19AE748FC__INCLUDED_)
#define AFX_PROCDLG_H__A452D90B_C43B_4416_8547_74D19AE748FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProcDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProcDlg form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CProcDlg : public CFormView
{
protected:
	CProcDlg();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CProcDlg)

// Form Data
public:
	//{{AFX_DATA(CProcDlg)
	enum { IDD = IDD_PROCDLG };
	CListBox	m_List5;
	CListBox	m_List4;
	CComboBox	m_valid;
	CListCtrl	m_List3;
	CListBox	m_List2;
	CListBox	m_List1;
	CString	m_Version;
	CString	m_Date;
	CString	m_author;
	CString	m_Program;
	int		m_MiscParamNum;
	CString	m_Input;
	CString	m_Input1;
	//}}AFX_DATA

// Attributes
public:

protected:
	CString GetItemText(HWND hWnd, int nItem, int nSubItem) const;
// Operations
protected:
	int nItem, nSubItem;
	bool bEverEdited;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProcDlg)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProcDlg();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CProcDlg)
	afx_msg void OnAddall();
	afx_msg void OnAddone();
	afx_msg void OnRemoveone();
	afx_msg void OnRemoveall();
	afx_msg void OnDblclkList1();
	afx_msg void OnDblclkList2();
	afx_msg void OnClickList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEdit8();
	afx_msg void OnSave();
	afx_msg void OnAdditem();
	afx_msg void OnRemoveitem();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
	afx_msg void OnChangeEdit4();
	afx_msg void OnChangeEdit5();
	afx_msg void OnChangeEdit6();
	afx_msg void OnChangeEdit7();
	afx_msg void OnAddrtuall();
	afx_msg void OnAddrtuone();
	afx_msg void OnRemovertuone();
	afx_msg void OnRemovertuall();
	afx_msg void OnDblclkList4();
	afx_msg void OnDblclkList5();
	afx_msg void OnRevert();
	afx_msg void OnChangeEdit8();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnChangeEdit1();
	//}}AFX_MSG
	afx_msg LRESULT OnMsgSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCDLG_H__A452D90B_C43B_4416_8547_74D19AE748FC__INCLUDED_)
