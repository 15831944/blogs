// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__2486F51E_8985_401E_AB91_D618397AED05__INCLUDED_)
#define AFX_MAINFRM_H__2486F51E_8985_401E_AB91_D618397AED05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyTreeCtrl.h"
#include "XTOutBarCtrl.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void Serialize(CArchive& ar);
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void InitializeOutlookBar();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CXTOutBarCtrl  m_wndOutlookBar;

	CImageList	   m_ImageLarge;
	CImageList	   m_ImageSmall;
	bool             m_bDestroy;
//	CMyTreeCtrl m_wndTreeCtrl,m_wndTreeCtrl1;
//	CMyTreeCtrl m_wndTreeCtrl2,m_wndTreeCtrl3;
	CImageList *m_pImageList;
	bool bCreateNewView;

	bool bCreateSplitter;
	int  mPreSelFolder,mPreSelItem;
	bool BeginCreateOutlookBar;
	CView* pNewActiveView;
public:
	int CurActiveView;
	CSplitterWnd *m_wndSplitter;
public:
	BOOL  ShowOutLookBar();
	BOOL  SendSaveMsg(CView *pView,int mDlgCtrlId);
	BOOL  SendUnSaveMsg(CView *pView,int mDlgCtrlId);
	void  OpenUploadFile(int);
	void  CreateNewView();
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnFileClose1();
	afx_msg void OnFileMysave();
	afx_msg void OnFileMysaveAs();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnClose();
	afx_msg void OnUplaod();
	afx_msg void OnDownlaod();
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnDownfile();
	afx_msg void OnConnect();
	afx_msg void OnShutdown();
	afx_msg void OnResetMk();
	//}}AFX_MSG
	afx_msg LRESULT OnOutbarNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetWinText(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__2486F51E_8985_401E_AB91_D618397AED05__INCLUDED_)
