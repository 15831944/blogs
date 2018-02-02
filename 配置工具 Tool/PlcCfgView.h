#if !defined(AFX_PLCCFGVIEW_H__E0CAF16C_8B13_4D35_AEA1_E7033C5F375D__INCLUDED_)
#define AFX_PLCCFGVIEW_H__E0CAF16C_8B13_4D35_AEA1_E7033C5F375D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlcCfgView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlcCfgView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CPlcCfgView : public CFormView
{
protected:
	CPlcCfgView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPlcCfgView)

// Form Data
public:
	//{{AFX_DATA(CPlcCfgView)
	enum { IDD = IDD_PLCCFG_VIEW };
	CEdit	m_Editbox;
	CComboBox	m_ComBo1;
	CListCtrl	m_List;
	int		m_Total;
	int		m_InNum;
	int		m_Out1;
	int		m_Out2;
	int		m_T1;
	int		m_T2;
	int		m_T3;
	int		m_T4;
	int		m_T5;
	int		m_T6;
	int		m_Value1;
	int		m_Time1;
	int		m_Value2;
	int		m_Time2;
	BOOL	m_Check1;
	BOOL	m_Check2;
	BOOL	m_Check3;
	BOOL	m_PlcEnable;
	int		m_AutoBztValue;
	int		m_AutoBztTime;
	BOOL	m_AutoBztEnable;
	int		m_TripTime;
	int		m_CloseTime;
	BOOL	m_CheckVol;
	BOOL	m_BztCheckVol;
	int		m_RecloseDelay;
	int		m_LogicVol;
	//}}AFX_DATA

// Attributes
public:

protected:
	bool bEverEdited;
	int nItem, nSubItem;

// Operations
public:

protected:
	int	Save_InNum, Save_Out1, Save_Out2;

protected:
	void UpdateList(PlcRecStru);
	void LoadData();
	void ResetRelcose(int pIn, int pOut1, int pOut2, int In,  int Out1,  int Out2);
	bool GetRecloseEnable(CString sEnable);
	bool GetCheckVoltage(CString sEnable);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlcCfgView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPlcCfgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CPlcCfgView)
	afx_msg void OnKillfocusEdit12();
	afx_msg void OnKillfocusEdit13();
	afx_msg void OnKillfocusEdit2();
	afx_msg void OnKillfocusEdit3();
	afx_msg void OnKillfocusEdit4();
	afx_msg void OnSave();
	afx_msg void OnCANCEl();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusCombo1();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
	afx_msg void OnChangeEdit4();
	afx_msg void OnChangeEdit5();
	afx_msg void OnChangeEdit6();
	afx_msg void OnChangeEdit7();
	afx_msg void OnChangeEdit8();
	afx_msg void OnChangeEdit9();
	afx_msg void OnChangeEdit10();
	afx_msg void OnChangeEdit11();
	afx_msg void OnChangeEdit12();
	afx_msg void OnChangeEdit13();
	afx_msg void OnChangeEdit14();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnChangeEdit15();
	afx_msg void OnChangeEdit16();
	afx_msg void OnChangeEdit17();
	afx_msg void OnChangeEdit18();
	afx_msg void OnCheck6();
	afx_msg void OnCheck7();
	afx_msg void OnKillfocusEditbox();
	//}}AFX_MSG
	afx_msg LRESULT OnMsgSaveFile(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLCCFGVIEW_H__E0CAF16C_8B13_4D35_AEA1_E7033C5F375D__INCLUDED_)
