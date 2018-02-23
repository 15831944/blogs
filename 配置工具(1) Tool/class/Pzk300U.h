#if !defined(AFX_PZK300U_H__9A6AC532_F092_4A5F_AF90_356B0912DCA0__INCLUDED_)
#define AFX_PZK300U_H__9A6AC532_F092_4A5F_AF90_356B0912DCA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Pzk300U.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPzk300U form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CPzk300U : public CFormView
{
protected:
	CPzk300U();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPzk300U)

// Form Data
public:
	//{{AFX_DATA(CPzk300U)
	enum { IDD = IDD_PZK300U };
	BOOL	m_OverA;
	BOOL	m_OverB;
	BOOL	m_OverC;
	BOOL	m_LoseA;
	BOOL	m_LoseB;
	BOOL	m_LoseC;
	int		m_OverVA;
	int		m_OverVB;
	int		m_OverVC;
	int		m_LoseVA;
	int		m_LoseVB;
	int		m_LoseVC;
	//}}AFX_DATA

// Attributes
public:

private:

protected:
	bool bEverEdited;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPzk300U)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPzk300U();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CPzk300U)
	afx_msg void OnSave();
	afx_msg void OnCancel();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnKillfocusEdit1();
	afx_msg void OnKillfocusEdit2();
	afx_msg void OnKillfocusEdit3();
	afx_msg void OnKillfocusEdit4();
	afx_msg void OnKillfocusEdit5();
	afx_msg void OnKillfocusEdit6();
	//}}AFX_MSG
	afx_msg LRESULT OnMsgSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PZK300U_H__9A6AC532_F092_4A5F_AF90_356B0912DCA0__INCLUDED_)
