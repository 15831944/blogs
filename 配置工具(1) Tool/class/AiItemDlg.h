#if !defined(AFX_AIITEMDLG_H__644065C2_58FD_45C5_AA8C_2BED387D7BFD__INCLUDED_)
#define AFX_AIITEMDLG_H__644065C2_58FD_45C5_AA8C_2BED387D7BFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AiItemDlg.h : header file
//

#include "NumberEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CAiItemDlg dialog

class CAiItemDlg : public CDialog
{
// Construction
public:
	CAiItemDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAiItemDlg)
	enum { IDD = IDD_AIITEMDLG };
	CComboBox	m_type;
	CComboBox	m_valid;
	CString	m_name;
	int		m_LineNum;
	int		m_MaxValue;
	int		m_MinValue;
	float	m_rating;
	int		m_RelateLine;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAiItemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CNumberEdit mNumberEdit;
	// Generated message map functions
	//{{AFX_MSG(CAiItemDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit4();
	afx_msg void OnChangeEdit5();
	afx_msg void OnChangeEdit6();
	afx_msg void OnChangeEdit7();
	afx_msg void OnKillfocusEdit2();
	afx_msg void OnKillfocusEdit5();
	afx_msg void OnKillfocusEdit6();
	afx_msg void OnKillfocusEdit4();
	afx_msg void OnKillfocusEdit7();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AIITEMDLG_H__644065C2_58FD_45C5_AA8C_2BED387D7BFD__INCLUDED_)
