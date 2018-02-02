#if !defined(AFX_DOWNLOADDLG_H__51EFAF34_EEF3_4AF7_BFA0_3851F9E87E6D__INCLUDED_)
#define AFX_DOWNLOADDLG_H__51EFAF34_EEF3_4AF7_BFA0_3851F9E87E6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DownLoadDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDownLoadDlg dialog

class CDownLoadDlg : public CDialog
{
// Construction
public:
	CDownLoadDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDownLoadDlg)
	enum { IDD = IDD_DOWNLOAD };
	CProgressCtrl	m_ProgCtrl;
	CString	m_ShowMsg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDownLoadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

protected:
	bool bDlgRuning;
	// Generated message map functions
	//{{AFX_MSG(CDownLoadDlg)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg LRESULT OnDownloadProgress(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOWNLOADDLG_H__51EFAF34_EEF3_4AF7_BFA0_3851F9E87E6D__INCLUDED_)
