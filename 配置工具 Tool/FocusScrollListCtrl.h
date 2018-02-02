#if !defined(AFX_FOCUSSCROLLLISTCTRL_H__757FE6BF_8FB4_46C5_807E_DC637C882147__INCLUDED_)
#define AFX_FOCUSSCROLLLISTCTRL_H__757FE6BF_8FB4_46C5_807E_DC637C882147__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FocusScrollListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFocusScrollListCtrl window

class CFocusScrollListCtrl : public CListCtrl
{
// Construction
public:
	CFocusScrollListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFocusScrollListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFocusScrollListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFocusScrollListCtrl)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOCUSSCROLLLISTCTRL_H__757FE6BF_8FB4_46C5_807E_DC637C882147__INCLUDED_)
