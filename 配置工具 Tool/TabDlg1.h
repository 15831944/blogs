#if !defined(AFX_TABDLG1_H__3CBC66D3_FB92_478B_A799_4E16E6795F38__INCLUDED_)
#define AFX_TABDLG1_H__3CBC66D3_FB92_478B_A799_4E16E6795F38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabDlg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabDlg1 dialog

class CTabDlg1 : public CpropertyPage
{
// Construction
public:
	CTabDlg1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTabDlg1)
	enum { IDD = IDD_TABDLG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabDlg1)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTabDlg1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABDLG1_H__3CBC66D3_FB92_478B_A799_4E16E6795F38__INCLUDED_)
