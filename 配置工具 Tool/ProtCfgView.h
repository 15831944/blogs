#if !defined(AFX_PROTCFGVIEW_H__1334DEA8_F1E1_4FEC_93FE_FF1D87676FF2__INCLUDED_)
#define AFX_PROTCFGVIEW_H__1334DEA8_F1E1_4FEC_93FE_FF1D87676FF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProtCfgView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProtCfgView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CProtCfgView : public CFormView
{
protected:
	CProtCfgView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CProtCfgView)

// Form Data
public:
	//{{AFX_DATA(CProtCfgView)
	enum { IDD = IDD_PROTECT_VIEW };
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
	CEdit	m_Input;
	CComboBox	m_Enable;
	CComboBox	m_ProtType;
	CListCtrl	m_List5;
	CListCtrl	m_List4;
	CListCtrl	m_List3;
	CListCtrl	m_List2;
	BOOL	m_Check1;
	BOOL	m_Check2;
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
	void LoadProtectConfig();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProtCfgView)
	public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CProtCfgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CProtCfgView)
	afx_msg int CheckNum(CString str);//by lz
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
	afx_msg void OnCheck2();
	afx_msg void OnCheck1();
	afx_msg void OnKillfocusEdit21();
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEdit21();
	afx_msg void OnRadio4();
	afx_msg void OnRadio3();
	afx_msg void OnRadio2();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnMsgSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROTCFGVIEW_H__1334DEA8_F1E1_4FEC_93FE_FF1D87676FF2__INCLUDED_)
