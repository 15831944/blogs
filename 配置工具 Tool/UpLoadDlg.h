#if !defined(AFX_UPLOADDLG_H__A131F53E_BE79_4555_AC93_91721A84592B__INCLUDED_)
#define AFX_UPLOADDLG_H__A131F53E_BE79_4555_AC93_91721A84592B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpLoadDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUpLoadDlg dialog

class CUpLoadDlg : public CDialog
{
// Construction
public:
	CUpLoadDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUpLoadDlg)
	enum { IDD = IDD_UPLOAD };
	CProgressCtrl	m_ProgCtrl;
	CString	m_ShowMsg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpLoadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int fileType;

public:
	int DoModal(int FileType);

protected:
	bool bDlgRuning;
	// Generated message map functions
	//{{AFX_MSG(CUpLoadDlg)
	afx_msg void OnEdit();
	afx_msg void OnExit();
	afx_msg void OnSave();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg LRESULT OnUploadProgress(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPLOADDLG_H__A131F53E_BE79_4555_AC93_91721A84592B__INCLUDED_)
