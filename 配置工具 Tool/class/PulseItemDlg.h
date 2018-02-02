#if !defined(AFX_PULSEITEMDLG_H__9A319BDD_44F3_449B_BE4E_7A46C1E86208__INCLUDED_)
#define AFX_PULSEITEMDLG_H__9A319BDD_44F3_449B_BE4E_7A46C1E86208__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PulseItemDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPulseItemDlg dialog

class CPulseItemDlg : public CDialog
{
// Construction
public:
	CPulseItemDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPulseItemDlg)
	enum { IDD = IDD_PULSEITEMDLG };
	CComboBox	m_AccMode;
	CString	m_name;
	int		m_InputAddr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPulseItemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPulseItemDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnChangeEdit2();
	afx_msg void OnKillfocusEdit2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PULSEITEMDLG_H__9A319BDD_44F3_449B_BE4E_7A46C1E86208__INCLUDED_)
