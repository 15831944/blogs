#if !defined(AFX_FAULT_H__9204D923_9688_4E5C_8398_5F02B0BCE4E3__INCLUDED_)
#define AFX_FAULT_H__9204D923_9688_4E5C_8398_5F02B0BCE4E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Fault.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFault dialog

class CFault : public CDialog
{
// Construction
public:
	CFault(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFault)

		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFault)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFault)
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FAULT_H__9204D923_9688_4E5C_8398_5F02B0BCE4E3__INCLUDED_)
