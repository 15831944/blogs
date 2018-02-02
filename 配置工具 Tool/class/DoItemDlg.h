#if !defined(AFX_DOITEMDLG_H__6D84A033_2DD4_4C4C_9471_50413617654E__INCLUDED_)
#define AFX_DOITEMDLG_H__6D84A033_2DD4_4C4C_9471_50413617654E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DoItemDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDoItemDlg dialog

class CDoItemDlg : public CDialog
{
// Construction
public:
	CDoItemDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDoItemDlg)
	enum { IDD = IDD_DOITEMDLG };
	CString	m_name;
	int		m_DOAddr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoItemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDoItemDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOITEMDLG_H__6D84A033_2DD4_4C4C_9471_50413617654E__INCLUDED_)
