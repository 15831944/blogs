// FaultCfgView.h: interface for the FaultCfgView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FAULTCFGVIEW_H__03D00795_6EE6_4B1A_AB5E_E43EE55EEE3F__INCLUDED_)
#define AFX_FAULTCFGVIEW_H__03D00795_6EE6_4B1A_AB5E_E43EE55EEE3F__INCLUDED_
        
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "resource.h"
class CFaultCfgView  : public CFormView
{
protected:

	DECLARE_DYNCREATE(CFaultCfgView)
public:
	enum { IDD = IDD_FAULT_VIEW };
	CListCtrl	m_List9;
	CListCtrl	m_List32;
	CListCtrl	m_List31;
	CListCtrl	m_List30;
	CListCtrl	m_List29;
	CListCtrl	m_List28;
	CListCtrl	m_List27;
	CListCtrl	m_List26;
	CListCtrl	m_List25;
	CListCtrl	m_List24;
	CListCtrl	m_List23;
	CListCtrl	m_List22;
	CListCtrl	m_List21;
	CListCtrl	m_List20;
	CListCtrl	m_List19;
	CListCtrl	m_List18;
	CListCtrl	m_List17;
	CListCtrl	m_List16;
	CListCtrl	m_List15;
	CListCtrl	m_List14;
	CListCtrl	m_List13;
	CListCtrl	m_List12;
	CListCtrl	m_List11;
	CListCtrl	m_List10;
	CListCtrl	m_List8;
	CListCtrl	m_List7;
	CListCtrl	m_List6;
	BOOL	m_Check1;
	BOOL	m_Check2;
	BOOL	m_Check3;
	CEdit	m_Input;
	CComboBox	m_Enable;
	CComboBox	m_ProtType;
	CListCtrl	m_List5;
	CListCtrl	m_List4;
	CListCtrl	m_List3;
	CListCtrl	m_List2;
	CComboBox	m_ConnectMode;
	CComboBox	m_LineNo;
	CListCtrl	m_List1;
	CString	m_Version;
	CString	m_CreateTime;
	int		m_LineNum;
	int		m_PNumPerLine;
	int		m_SboNo;
	int		m_SwitchNo;
	int     m_FixActTime;
	int		m_Remote;
	int		m_Local;
	//}}AFX_DATA

// Attributes
public:

protected:
	int nItem, nSubItem;
	bool bEverEdited;

	CListCtrl* listArray[_Max_Prot_Line];

	int mSbo[_Max_Prot_Line];
	int mSwitch[_Max_Prot_Line];
	int mRemote[_Max_Prot_Line];
	int mLocal[_Max_Prot_Line];
	int mMode[_Max_Prot_Line];
	int CMode;   //接线方式（CONNECTMODE）

// Operations
public:


protected:
	void InitListCtrl();
	void SetListFocus(int no);
public:
	void LoadFaultConfig();
	CFaultCfgView();
	void yulan();
	virtual ~CFaultCfgView();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProtCfgView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CProtCfgView)
	
	afx_msg void OnInsertfront();
	afx_msg void OnKillfocusEdit3();	
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickList4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickList5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSave();
	afx_msg void OnCancel();
	afx_msg void OnKillfocusEdit4();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
	afx_msg void OnChangeEdit4();
	afx_msg void OnChangeEdit5();
	afx_msg void OnChangeEdit6();
	afx_msg void OnChangeEdit7();
	afx_msg void OnChangeEdit8();
	afx_msg void OnKillfocusCombo3();
	afx_msg void OnKillfocusCombo4();
	afx_msg void OnKillfocusEdit9();
	afx_msg void OnKillfocusEdit5();
	afx_msg void OnKillfocusEdit6();
	afx_msg void OnKillfocusEdit7();
	afx_msg void OnKillfocusEdit8();
	afx_msg void OnKillfocusCombo2();
	afx_msg void OnSelchangeCombo2();
	afx_msg void OnClickList6(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickList7(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickList8(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuitem32801();
	afx_msg void OnRemovertu();
	int CheckNum(CString str);
	//}}AFX_MSG
	afx_msg LRESULT OnMsgSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_FAULTCFGVIEW_H__03D00795_6EE6_4B1A_AB5E_E43EE55EEE3F__INCLUDED_)
