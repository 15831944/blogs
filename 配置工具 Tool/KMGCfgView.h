#if !defined(AFX_KMGCFGVIEW_H__23FE6375_555B_4247_B4D6_2C33F2135669__INCLUDED_)
#define AFX_KMGCFGVIEW_H__23FE6375_555B_4247_B4D6_2C33F2135669__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KMGCfgView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKMGCfgView dialog

class CKMGCfgView : public CFormView
{
// Construction
public:
	CKMGCfgView();
	DECLARE_DYNCREATE(CKMGCfgView)
	//{{AFX_DATA(CKMGCfgView)
	enum { IDD = IDD_KMG_VIEW };
	CComboBox	m_Enable;
	CEdit	m_Input;
	CListCtrl	m_List1;
	CComboBox	m_KMGType;
	CString	m_Version;
	BOOL	m_Check1;
	BOOL	m_Check2;
	BOOL	m_Check3;
	BOOL	m_Check4;
	BOOL	m_Check5;
	int		m_SboNum;
	int		m_SwitchNum;
	BOOL	m_Check6;
	int		m_FixActTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKMGCfgView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	int nItem, nSubItem;
	CListCtrl* listArray[1];
	bool bEverEdited;
	int SwitchType;//开关类型(0-断路器, 1-负荷开关)
	int CMode;//接线方式

	#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
public:
	void InitListCtrl();
	void LoadKMGConfig();

	// Generated message map functions
	//{{AFX_MSG(CKMGCfgView)
	afx_msg LRESULT OnMsgSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnChangeEdit4();
	afx_msg void OnKillfocusEdit4();
	afx_msg void OnChangeEdit5();
	afx_msg void OnKillfocusEdit5();
	afx_msg void OnSave();
	afx_msg void OnKillfocusEdit3();
	afx_msg void OnKillfocusCombo2();
	afx_msg void OnButton2();
	afx_msg void OnRadio3();
	afx_msg void OnCheck6();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnKillfocusEdit6();
	afx_msg void OnChangeEdit6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KMGCFGVIEW_H__23FE6375_555B_4247_B4D6_2C33F2135669__INCLUDED_)
