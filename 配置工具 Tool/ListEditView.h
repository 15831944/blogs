#if !defined(AFX_LISTEDITVIEW_H__D1DE0D3D_ECE1_4980_8384_E9DA3E782001__INCLUDED_)
#define AFX_LISTEDITVIEW_H__D1DE0D3D_ECE1_4980_8384_E9DA3E782001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListEditView.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CLVEdit 

class CLVEdit : public CEdit
{
// Construction
public:
    CLVEdit() :m_x(0),m_y(0) {}

// Attributes
public:
    int m_x;
    int m_y;

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CLVEdit)
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CLVEdit() {};

    // Generated message map functions
protected:
    //{{AFX_MSG(CLVEdit)
    afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CListEditView view

class CListEditView : public CListView
{
protected:
	CListEditView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CListEditView)

// Attributes
protected:
    int        m_cx;
    BOOL        m_nEdit;
    CLVEdit    m_LVEdit;

// Operations
protected:
    virtual void RepaintSelectedItems();
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
    virtual LPCTSTR MakeShortString(CDC* pDC,LPCTSTR lpszLong,int nColumnLen);

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListEditView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CListEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CListEditView)
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEndLabelEdit(NMHDR* pNMHDR,LRESULT* pResult);
    afx_msg void OnBeginLabelEdit(NMHDR* pNMHDR,LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTEDITVIEW_H__D1DE0D3D_ECE1_4980_8384_E9DA3E782001__INCLUDED_)
