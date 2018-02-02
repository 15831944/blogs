#if !defined(AFX_36BCANSHU_H__E4875DD0_0FBB_457B_9432_F5DCF207507F__INCLUDED_)
#define AFX_36BCANSHU_H__E4875DD0_0FBB_457B_9432_F5DCF207507F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 36BCANSHU.h : header file
//
extern int isisis;
/////////////////////////////////////////////////////////////////////////////
// C36BCANSHU form view
#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
class C36BCANSHU : public CFormView
{
protected:
	C36BCANSHU();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(C36BCANSHU)

// Form Data
public:
	//{{AFX_DATA(C36BCANSHU)
	enum { IDD = IDD_36BCANSHU_VIEW };
	CComboBox	m_modetype;
	CComboBox	m_Enable;
	CEdit    m_MLTime;
	CListCtrl	m_list;
	CButton   m_ML;
	CString	m_version;
	CString	m_createtime;
	int		m_flow;
	int		m_voltage;
	int		m_cxtime;
	int     m_mltime1;
	BOOL	m_PlcEnable;
	int		m_OutNum1;
	int		m_OutNum2;
	BOOL	m_OOEnable;
	BOOL	m_OTEnable;
	BOOL	m_TOEnable;
	BOOL	m_TTEnable;
	BOOL    m_MLEnable;
	int		m_OneTime;
	int		m_TwoTime;
	//}}AFX_DATA
	int     m_Total;
// Attributes
public:
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C36BCANSHU)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	int nItem, nSubItem;
	bool bEverEdited;
	int jxnum;
	int	Save_InNum, Save_Out1, Save_Out2;
	CListCtrl* listArray[_Max_Prot_Line];
	void InitListCtrl();
	void LoadProtectConfig();
	void UpdateList(bool[]);
	void ResetRelcose(int pOut1, int pOut2,int Out1,  int Out2);
	virtual ~C36BCANSHU();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(C36BCANSHU)
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusCombo3();
	afx_msg void OnKillfocusCombo4();
	afx_msg void OnKillfocusEdit9();
	afx_msg void OnSave();
	afx_msg void OnCANCEl();
	afx_msg void OnKillfocusEdit3();
	afx_msg void OnKillfocusEdit4();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit8();
	afx_msg void OnChangeEdit3();
	afx_msg void OnChangeEdit4();
	afx_msg void OnChangeEdit5();
	afx_msg void OnChangeEdit6();
	afx_msg void OnChangeEdit7();
	afx_msg void OnChangeEdit10();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnCheck1();
	afx_msg void OnEditchangeCombo1();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnCheck6();
	afx_msg void OnChangeEdit11();
	//}}AFX_MSG
	afx_msg LRESULT OnMsgSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_36BCANSHU_H__E4875DD0_0FBB_457B_9432_F5DCF207507F__INCLUDED_)
