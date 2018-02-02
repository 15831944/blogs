#if !defined(AFX_SXYJ_H__BEDA4000_96C9_4C19_B005_EE3754854A76__INCLUDED_)
#define AFX_SXYJ_H__BEDA4000_96C9_4C19_B005_EE3754854A76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Sxyj.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSxyj form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CSxyj : public CFormView
{
protected:
	CSxyj();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSxyj)

// Form Data
public:
	//{{AFX_DATA(CSxyj)
	enum { IDD = IDD_SXYJ_VIEW };
	CEdit	m_Input1;
	CListCtrl	m_List2;
	CComboBox	m_LineNo;
	CEdit	m_Input;
	CListCtrl	m_List1;
	int		m_MainWindowNum;
	int		m_YxNum;
	int		m_ProtLineNum;
	CString	m_LineName;
	int		m_YcNum;
	int		m_WindowNum0;
	int		m_WindowNum1;
	CString	m_DeviceName;
	//}}AFX_DATA

// Attributes
public:
	int nItem, nSubItem;
	CListCtrl* listArray[2];
	bool bEverEdited;

// Operations
public:
	void InitListCtrl();
	void LoadSxyjConfig(int);
	void yulan();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSxyj)
	public:
		virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSxyj();
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSxyj)
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEdit4();
	afx_msg void OnChangeEdit4();
	afx_msg void OnChangeEdit6();
	afx_msg void OnKillfocusEdit6();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnKillfocusEdit2();
	afx_msg void OnClickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEdit8();
	afx_msg void OnChangeEdit5();
	afx_msg void OnKillfocusEdit5();
	afx_msg void OnChangeEdit3();
	afx_msg void OnKillfocusEdit3();
	afx_msg void OnSave();
	afx_msg void OnChangeEdit1();
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnCancel();
	//}}AFX_MSG
	afx_msg LRESULT OnMsgSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SXYJ_H__BEDA4000_96C9_4C19_B005_EE3754854A76__INCLUDED_)
