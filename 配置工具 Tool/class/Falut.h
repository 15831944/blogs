#if !defined(AFX_FALUT_H__E8BA3A89_2413_4CA5_93F6_EBBE0FA2E7C8__INCLUDED_)
#define AFX_FALUT_H__E8BA3A89_2413_4CA5_93F6_EBBE0FA2E7C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Falut.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFalut dialog

class CFalut : public CDialog
{
// Construction
public:
	CFalut(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFalut)
	enum { IDD = IDD_FAULT_MAIN };
    CTabCtrl m_tab;
//	CPage1   m_page1;
//	CPage2   m_page2;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFalut)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFalut)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickList5(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FALUT_H__E8BA3A89_2413_4CA5_93F6_EBBE0FA2E7C8__INCLUDED_)
