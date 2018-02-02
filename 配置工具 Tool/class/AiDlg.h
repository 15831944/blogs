#if !defined(AFX_AIDLG_H__1D6C5B64_DF4E_43A0_87FE_6A4A663085DA__INCLUDED_)
#define AFX_AIDLG_H__1D6C5B64_DF4E_43A0_87FE_6A4A663085DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AiDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAiDlg form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CAiDlg : public CFormView	
{
protected:
	CAiDlg();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAiDlg)

// Form Data
public:
	//{{AFX_DATA(CAiDlg)
	enum { IDD = IDD_AIDLG };
	CComboBox	m_Combo3;
	CComboBox	m_Combo2;
	CComboBox	m_Combo1;
	int		m_AiNum;
	//}}AFX_DATA
protected:
	void InsertItems();
	void SetCell(HWND hWnd1, CString value, int nRow, int nCol);
	CString GetItemText(HWND hWnd, int nItem, int nSubItem) const;
	int nItem, nSubItem;
	CListCtrl *pAiList;// = (CListCtrl *)GetDlgItem(this,IDC_LIST1);
	CEdit *pInEdit;
	CComboBox *pInCombo;
	CMenu mMenu;
	bool bEverEdited;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAiDlg)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAiDlg();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CAiDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAdditem();
	afx_msg void OnRemoveitem();
	afx_msg void OnEdititem();
	afx_msg void OnOK();
	afx_msg void OnSave();
	afx_msg void OnItemAdd();
	afx_msg void OnItemEdit();
	afx_msg void OnItemRemove();
	afx_msg void OnItemSave();
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnSelchangeCombo2();
	afx_msg void OnSelchangeCombo3();
	afx_msg void OnFileSave();
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

#endif // !defined(AFX_AIDLG_H__1D6C5B64_DF4E_43A0_87FE_6A4A663085DA__INCLUDED_)
