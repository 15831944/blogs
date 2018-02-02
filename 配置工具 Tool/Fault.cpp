// Fault.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "Fault.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFault dialog


CFault::CFault(CWnd* pParent /*=NULL*/)
	: CDialog(CFault::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFault)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFault::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFault)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFault, CDialog)
	//{{AFX_MSG_MAP(CFault)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFault message handlers

void CFault::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	/*
	CString str;
	CComboBox *pCombo;
	HWND pWnd;
	Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST1);
    LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
    RECT rect;
    //get the row number
    nItem = temp->iItem;
    //get the column number
    nSubItem = temp->iSubItem;
	if(nSubItem == 0)
		return;

	if(nSubItem == 1)
	{
		return;
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO4);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO1);
		pCombo->SetCurSel(m_List1.GetItemData(nItem));
	}
	else if(nSubItem == 2)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_COMBO3);
		pCombo = (CComboBox *)GetDlgItem(IDC_COMBO3);
		str = m_List1.GetItemText(nItem, nSubItem);
		if(str.Compare("Í¶Èë") == 0)
			pCombo->SetCurSel(0);
		else
			pCombo->SetCurSel(1);
	}
	else if(nSubItem != 5)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT9);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT9);
		m_Input.SetWindowText(m_List1.GetItemText(nItem, nSubItem));
	}
	else
		return;

	pCombo->SetItemHeight(-1,12);

    //Retrieve the text of the selected subItem 
    //from the list

    RECT rect1,rect2;
    // this macro is used to retrieve the Rectanle 
    // of the selected SubItem
    ListView_GetSubItemRect(hWnd1,temp->iItem,
        temp->iSubItem,LVIR_BOUNDS,&rect);
    //Get the Rectange of the listControl
    ::GetWindowRect(temp->hdr.hwndFrom,&rect1);
    //Get the Rectange of the Dialog
    ::GetWindowRect(m_hWnd,&rect2);

    int x=rect1.left-rect2.left;
    int y=rect1.top-rect2.top;

	::SetWindowPos(pWnd,
		HWND_TOP,rect.left+x+1,rect.top+y, 
		rect.right-rect.left+4,
		rect.bottom-rect.top+3,NULL);
	::ShowWindow(pWnd,SW_SHOW);
	::SetFocus(pWnd);
	*/
	*pResult = 0;
}

void CFault::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
