#if !defined(AFX_SCALEITEMDLG_H__3BDD6712_797E_4819_8581_BA75164F2043__INCLUDED_)
#define AFX_SCALEITEMDLG_H__3BDD6712_797E_4819_8581_BA75164F2043__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScaleItemDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScaleItemDlg dialog

class CScaleItemDlg : public CDialog
{
// Construction
public:
	CScaleItemDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScaleItemDlg)
	enum { IDD = IDD_SCALEITEMDLG };
	CString	m_name;
	int		m_HWMaxVal;
	int		m_HWMinVal;
	int		m_UserMaxVal;
	int		m_UserMinVal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScaleItemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScaleItemDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnKillfocusEdit2();
	afx_msg void OnKillfocusEdit3();
	afx_msg void OnKillfocusEdit4();
	afx_msg void OnKillfocusEdit5();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
	afx_msg void OnChangeEdit4();
	afx_msg void OnChangeEdit5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCALEITEMDLG_H__3BDD6712_797E_4819_8581_BA75164F2043__INCLUDED_)
