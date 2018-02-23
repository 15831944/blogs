#if !defined(AFX_CHOOSEFILEDLG_H__A2EA4B37_41EA_4FCD_A9B1_DEC025D4B328__INCLUDED_)
#define AFX_CHOOSEFILEDLG_H__A2EA4B37_41EA_4FCD_A9B1_DEC025D4B328__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChooseFileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseFileDlg dialog

class CChooseFileDlg : public CDialog
{
// Construction
public:
	CChooseFileDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChooseFileDlg)
	enum { IDD = IDD_CHOOSEFILE };
	CComboBox	m_GongCheng;
	CComboBox	m_FileType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseFileDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int *fileType;
	int CMode;

public:
	int DoModal(int *FileType);

	// Generated message map functions
	//{{AFX_MSG(CChooseFileDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnSelchangeCombo2();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEFILEDLG_H__A2EA4B37_41EA_4FCD_A9B1_DEC025D4B328__INCLUDED_)
