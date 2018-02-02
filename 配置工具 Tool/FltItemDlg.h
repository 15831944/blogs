#if !defined(AFX_FLTITEMDLG_H__DCB103FE_4993_4D32_BAAF_599BD5F88C15__INCLUDED_)
#define AFX_FLTITEMDLG_H__DCB103FE_4993_4D32_BAAF_599BD5F88C15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FltItemDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFltItemDlg dialog

class CFltItemDlg : public CDialog
{
// Construction
public:
	CFltItemDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFltItemDlg)
	enum { IDD = IDD_FLTITEMDLG };
	CComboBox	m_3I0FaultEnable;
	CComboBox	m_IpFaultEnable;
	CString	m_name;
	int		m_FaultId;
	int		m_IpValue;
	int		m_3I0Value;
	int		m_PositiveResistance;
	int		m_PositiveReactance;
	int		m_ZeroResistance;
	int		m_ZeroReactance;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFltItemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFltItemDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
	afx_msg void OnChangeEdit4();
	afx_msg void OnChangeEdit5();
	afx_msg void OnChangeEdit6();
	afx_msg void OnChangeEdit7();
	afx_msg void OnChangeEdit8();
	afx_msg void OnKillfocusEdit2();
	afx_msg void OnKillfocusEdit3();
	afx_msg void OnKillfocusEdit4();
	afx_msg void OnKillfocusEdit5();
	afx_msg void OnKillfocusEdit6();
	afx_msg void OnKillfocusEdit7();
	afx_msg void OnKillfocusEdit8();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLTITEMDLG_H__DCB103FE_4993_4D32_BAAF_599BD5F88C15__INCLUDED_)
