#if !defined(AFX_MYTREECTRL_H__B8275A9F_0E5C_4D0D_8666_2F7D57338D99__INCLUDED_)
#define AFX_MYTREECTRL_H__B8275A9F_0E5C_4D0D_8666_2F7D57338D99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl window
class CMyTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CMyTreeCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyTreeCtrl();

	CSplitterWnd *m_wndSplitter;
	// Generated message map functions
protected:
	CMenu mMenu;
	HTREEITEM hPreItem,hCurItem;
	bool bChangeBecauseOtherUnsave;
	bool bSBChange;   //用来判断是否是这个sb树自己从无选择自动选择的0号节点
public:
	int TreeClass;

protected:
	//{{AFX_MSG(CMyTreeCtrl)
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuAdditem();
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuRemoveitem();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg LRESULT OnReturnPreItem(bool bSameTree, bool bOtherTree);
	afx_msg LRESULT OnDeleteNewNote(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTREECTRL_H__B8275A9F_0E5C_4D0D_8666_2F7D57338D99__INCLUDED_)
