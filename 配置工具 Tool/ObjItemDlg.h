#if !defined(AFX_OBJITEMDLG_H__57A36E9B_59E2_4562_8751_F99990CAD5E6__INCLUDED_)
#define AFX_OBJITEMDLG_H__57A36E9B_59E2_4562_8751_F99990CAD5E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ObjItemDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CObjItemDlg dialog

class CObjItemDlg : public CDialog
{
// Construction
public:
	CObjItemDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CObjItemDlg)
	enum { IDD = IDD_OBJITEMDLG };
	CComboBox	m_combo;
	int		m_xianluhao;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CObjItemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CObjItemDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	int CheckNum(CString str);
	bool Check(CString str);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJITEMDLG_H__57A36E9B_59E2_4562_8751_F99990CAD5E6__INCLUDED_)
