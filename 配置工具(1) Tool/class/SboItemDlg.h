#if !defined(AFX_SBOITEMDLG_H__E8827FF8_9FEB_4D66_BAAF_36526A39AAD2__INCLUDED_)
#define AFX_SBOITEMDLG_H__E8827FF8_9FEB_4D66_BAAF_36526A39AAD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SboItemDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSboItemDlg dialog

class CSboItemDlg : public CDialog
{
// Construction
public:
	CSboItemDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSboItemDlg)
	enum { IDD = IDD_SboItemDlg };
	CComboBox	m_valid;
	CString	m_name;
	int		m_SboId;
	int		m_tpw;
	int		m_cpw;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSboItemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSboItemDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
	afx_msg void OnChangeEdit4();
	afx_msg void OnKillfocusEdit2();
	afx_msg void OnKillfocusEdit3();
	afx_msg void OnKillfocusEdit4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SBOITEMDLG_H__E8827FF8_9FEB_4D66_BAAF_36526A39AAD2__INCLUDED_)
