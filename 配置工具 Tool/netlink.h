#if !defined(AFX_NETLINK_H__857663A2_0EE4_41D1_A61A_DE977CA155BC__INCLUDED_)
#define AFX_NETLINK_H__857663A2_0EE4_41D1_A61A_DE977CA155BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// netlink.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cnetlink dialog

class Cnetlink : public CDialog
{
// Construction
public:
	Cnetlink(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cnetlink)
	enum { IDD = IDD_CREATE_NET_LINK };
	CComboBox	m_Combo;
	CListBox	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cnetlink)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cnetlink)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButton1();
	afx_msg void OnDblclkList1();
	virtual BOOL OnInitDialog();
	void FindNeighBor(void);
	afx_msg void OnResetMk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETLINK_H__857663A2_0EE4_41D1_A61A_DE977CA155BC__INCLUDED_)
