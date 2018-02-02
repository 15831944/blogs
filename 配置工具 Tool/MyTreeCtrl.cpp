// MyTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "MyTreeCtrl.h"
#include "MyFun.h"
#include "TempClass.h"
#include "ReadPzkIni.h"
#include "XTOutBarCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct Sel_Tree
{
	CMyTreeCtrl *hPreSelTree;
	CMyTreeCtrl *hCurSelTree;
}SelTreeStru;

extern SelTreeStru mSelTree;
/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl
CMyTreeCtrl::CMyTreeCtrl()
{
	mMenu.LoadMenu(IDR_MENU1);
	TreeClass = NONE_TREE;
	hPreItem = hCurItem =NULL;
	bChangeBecauseOtherUnsave = false;
	bSBChange = false;
}

CMyTreeCtrl::~CMyTreeCtrl()
{
	int i = this->GetCount();
	TRACE(Str(TreeClass));
}


BEGIN_MESSAGE_MAP(CMyTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CMyTreeCtrl)
	ON_WM_MENUSELECT()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_COMMAND(IDC_MENU_ADDITEM, OnMenuAdditem)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	ON_COMMAND(IDC_MENU_REMOVEITEM, OnMenuRemoveitem)
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(TVN_SELCHANGING, OnSelchanging)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	//}}AFX_MSG_MAP
	ON_MESSAGE(RETURN_PRESEL_ITEM,OnReturnPreItem)
	ON_MESSAGE(DELETE_NEW_NODE,OnDeleteNewNote)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl message handlers


void CMyTreeCtrl::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu)
{
	CTreeCtrl::OnMenuSelect(nItemID, nFlags, hSysMenu);
	// TODO: Add your message handler code here

}

void CMyTreeCtrl::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	HTREEITEM mTreeItem,mParentItem;
	int mItemData;

	mTreeItem = GetSelectedItem();
	mParentItem = GetRootItem();
	mItemData = GetItemData(mTreeItem);

//	m_wndSplitter->CreateView(0,1,RUNTIME_CLASS(CTempClass),CSize(100,100),NULL);
//	m_wndSplitter->RecalcLayout();

	XT_OUTBAR_INFO obi;
	obi.nFolder   = TreeClass;
	obi.nIndex    = mItemData;
	obi.nDragFrom = -1;
	obi.nDragTo   = -1;
//	obi.lpszText  = GetItemText(iIndex);
	obi.bFolder   = false;

	CWnd* pOwner = AfxGetMainWnd();
	ASSERT_VALID(pOwner);

	pOwner->SendMessage(XTWM_OUTBAR_NOTIFY,	OBN_XT_ITEMCLICK, (LPARAM)&obi);
	*pResult = 0;
}

void CMyTreeCtrl::OnRclick(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	bSBChange = true;
	CMenu *pMenu;
	pMenu = mMenu.GetSubMenu(0);

	CPoint oPoint;
	GetCursorPos(&oPoint);

	//pMenu->TrackPopupMenu(TPM_LEFTALIGN,oPoint.x,oPoint.y,0);
	pMenu->TrackPopupMenu(TPM_LEFTALIGN,oPoint.x,oPoint.y,this,0);
	*pResult = 0;
}

void CMyTreeCtrl::OnMenuAdditem()
{
	// TODO: Add your command handler code here
	HTREEITEM mSelItem,mParentItem,mItem;
	mSelItem = GetSelectedItem();
	mParentItem = GetParentItem(mSelItem);
	int i;
	CString tempstr;

/*	XT_OUTBAR_INFO obi;
	obi.nFolder   = TreeClass;
	obi.nDragFrom = -1;
	obi.nDragTo   = -1;
//	obi.lpszText  = GetItemText(iIndex);
	obi.bFolder   = false;
*/
	switch(TreeClass)
	{
	case RTU_TREE:
		i=0;
		while(i<mPzkIni.mRtuBuf.RtuMax)
		{
			if (!mPzkIni.mRtuBuf.pValid[i] && !mPzkIni.mRtuBuf.ptempValid[i])
				break;
			i++;
		}
		mPzkIni.mRtuBuf.ptempValid[i] = true;
		tempstr.Format("RTU_%d",i);
		mItem = InsertItem(tempstr,0,1,mParentItem,TVI_LAST);
		mPzkIni.mRtuBuf.pRtu[i].name = tempstr;
		mPzkIni.mRtuBuf.pRtu[i].valid = false;
		mPzkIni.mRtuBuf.pRtu[i].devid = 0;
		mPzkIni.mRtuBuf.pRtu[i].Address = 0;
		mPzkIni.mRtuBuf.pRtu[i].ProcessId = 0;
		mPzkIni.mRtuBuf.pRtu[i].RTUid = i;
		mPzkIni.mRtuBuf.pRtu[i].AiNum = 0;
		mPzkIni.mRtuBuf.pRtu[i].BiNum = 0;
		mPzkIni.mRtuBuf.pRtu[i].CiNum = 0;
		mPzkIni.mRtuBuf.pRtu[i].SboNum = 0;
		mPzkIni.mRtuBuf.pRtu[i].DoNum = 0;
		SetItemData(mItem,i);
//		obi.nIndex    = i;
		break;
	case PROC_TREE:

		i=0;
		while(i<mPzkIni.mProcBuf.ProcMax)
		{
			if (!mPzkIni.mProcBuf.pValid[i] && !mPzkIni.mProcBuf.ptempValid[i])
				break;
			i++;
		}
		mPzkIni.mProcBuf.ptempValid[i] = true;
		tempstr.Format("PROCESS_%d",i);
		mItem=InsertItem(tempstr,0,1,mParentItem,TVI_LAST);
		mPzkIni.mProcBuf.pProc[i].name = tempstr;
		mPzkIni.mProcBuf.pProc[i].valid = true;
		mPzkIni.mProcBuf.pProc[i].MiscParamNum = 0;
		int count;
		for(count=0;count<mPzkIni.mRtuBuf.RtuMax;count++)
			mPzkIni.mProcBuf.pProc[i].RTUNum[count] = false;
		for(count =0;count<mPzkIni.mProcBuf.ProcMax;count++)
			mPzkIni.mProcBuf.pProc[i].RelateProc[count] = false;
		SetItemData(mItem,i);
//		obi.nIndex    = i;
		break;
	case OBJ_TREE:
		InsertItem("OBJ新建项",mParentItem,TVI_LAST);
		break;
	}
	SortChildren(mParentItem);
	Select(mItem,TVGN_CARET);
//	Select(mItem,TVGN_DROPHILITE);
//	SelectDropTarget(mItem);
//	CWnd* pOwner = AfxGetMainWnd();
//	pOwner->SendMessage(XTWM_OUTBAR_NOTIFY,	OBN_XT_ITEMCLICK, (LPARAM)&obi);
}

void CMyTreeCtrl::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult)
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM mItem;
	mItem = GetSelectedItem();
	CString str;
	(GetEditControl())->GetWindowText(str);
	SetItemText(mItem,str);
	int data = GetItemData(mItem);
	switch(TreeClass)
	{
	case RTU_TREE:
		mPzkIni.mRtuBuf.pRtu[data].name = str;
		break;
	case PROC_TREE:
		mPzkIni.mProcBuf.pProc[data].name = str;
		break;
	case OBJ_TREE:
		mPzkIni.mObjBuf.pObj[data].name = str;
		break;
	}
	*pResult = 0;
}

void CMyTreeCtrl::OnMenuRemoveitem()
{
	// TODO: Add your command handler code here
	HTREEITEM mItem,mParentItem;
	mItem = GetSelectedItem();
//	mParentItem = GetParentItem(mItem);

	if(mItem == NULL)
		return;
	int data = GetItemData(mItem);
	int i,okcancel;
	if(TreeClass == RTU_TREE)
	{
		for(i=0;i<mPzkIni.mProcBuf.ProcMax;i++)
		{
			if(mPzkIni.mProcBuf.pValid[i] && mPzkIni.mProcBuf.pProc[i].RTUNum[data])
				break;
		}
		if(i < mPzkIni.mProcBuf.ProcMax)
		{
			okcancel = AfxMessageBox("此RTU已被某进程所关联,请先取消它与所有进程的关联!");//在删除它之前请先删除某进程与它的关联!");
			return;
		}
	}

	if(TreeClass == PROC_TREE)
	{
		for(i=0;i<mPzkIni.mProcBuf.ProcMax;i++)
		{
			if(mPzkIni.mProcBuf.pValid[i] && mPzkIni.mProcBuf.pProc[i].RelateProc[data])
				break;
		}
		if(i<mPzkIni.mProcBuf.ProcMax)
		{
			okcancel = AfxMessageBox("此进程已被其他某进程所关联,请先取消其它进程与它的关联!");//在删除它之前请先删除某进程与它的关联!");
			return;
		}
	}

	okcancel = AfxMessageBox("您确定要删除此项吗?",MB_YESNO);
	if(okcancel != IDYES)
		return;

	bForDel = true;
	switch(TreeClass)
	{
	case RTU_TREE:
		mPzkIni.mRtuBuf.pValid[data] = false;
		mPzkIni.mRtuBuf.ptempValid[data] = false;
		mPzkIni.mProcBuf.pProc[mPzkIni.mRtuBuf.pRtu[data].ProcessId].RTUNum[data]=false;
		break;
	case PROC_TREE:
		mPzkIni.mProcBuf.pValid[data] = false;
		mPzkIni.mProcBuf.ptempValid[data] = false;
		for(i=0;i<mPzkIni.mRtuBuf.RtuMax;i++)
			if(mPzkIni.mProcBuf.pProc[data].RTUNum[i])
				mPzkIni.mRtuBuf.pRtu[i].valid = false;
		break;
	case OBJ_TREE:
		mPzkIni.mObjBuf.pValid[data] = false;
		break;
	}
	DeleteItem(mItem);
	if(GetCount() <= 0)
	{
		XT_OUTBAR_INFO obi;
		obi.nFolder   = -1;
		obi.nIndex    = 0;
		obi.nDragFrom = -1;
		obi.nDragTo   = -1;
		obi.lpszText  = "";
		obi.bFolder   = false;
		hCurItem = hPreItem = NULL;
		CWnd* pOwner = AfxGetMainWnd();
		pOwner->SendMessage(XTWM_OUTBAR_NOTIFY,	OBN_XT_ITEMCLICK, (LPARAM)&obi);
	}
/*
	XT_OUTBAR_INFO obi;
	obi.nFolder   = TreeClass;
	obi.nIndex    = 0;
	obi.nDragFrom = -1;
	obi.nDragTo   = -1;
//	obi.lpszText  = GetItemText(iIndex);
	obi.bFolder   = false;
	if(!ItemHasChildren(mParentItem))
		return;
	mItem = GetChildItem(mParentItem);

	data = GetItemData(mItem);
	Select(mItem,TVGN_CARET);
	CWnd* pOwner = AfxGetMainWnd();
	pOwner->SendMessage(XTWM_OUTBAR_NOTIFY,	OBN_XT_ITEMCLICK, (LPARAM)&obi);
*/
}

void CMyTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	UINT uFlags;
	HTREEITEM oldSelectItem = GetSelectedItem();
	HTREEITEM hItem = HitTest(point, &uFlags);

	if(hItem != NULL && oldSelectItem != hItem)//如果原来选中的节点和右键击中的节点不同，则选中当前节点；
		SelectItem(hItem);

	CTreeCtrl::OnRButtonDown(nFlags, point);
}

void CMyTreeCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if(nChar ==13)
	{
		bSBChange = true;
		HTREEITEM mTreeItem,mParentItem;
		int mItemData;

		mTreeItem = GetSelectedItem();
		mParentItem = GetRootItem();
		mItemData = GetItemData(mTreeItem);

		XT_OUTBAR_INFO obi;
		obi.nFolder   = TreeClass;
		obi.nIndex    = mItemData;
		obi.nDragFrom = -1;
		obi.nDragTo   = -1;
	//	obi.lpszText  = GetItemText(iIndex);
		obi.bFolder   = false;

		CWnd* pOwner = AfxGetMainWnd();
		ASSERT_VALID(pOwner);

		pOwner->SendMessage(XTWM_OUTBAR_NOTIFY,	OBN_XT_ITEMCLICK, (LPARAM)&obi);
	}
	CTreeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMyTreeCtrl::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	*pResult = 0;

	if(!bSBChange && (hPreItem == NULL))
	{
		SelectItem(NULL);
		return;
	}

	bSBChange = false;

	if(bChangeBecauseOtherUnsave)
	{
		bChangeBecauseOtherUnsave = false;
		return;
	}

	HTREEITEM mTreeItem,mParentItem;
	int mItemData;

	mTreeItem = GetSelectedItem();

	if(mTreeItem == NULL)
		return;

	hCurItem = mTreeItem;

	mParentItem = GetRootItem();
	//	msgbox("reach here3");
	mItemData = GetItemData(mTreeItem);

//	m_wndSplitter->CreateView(0,1,RUNTIME_CLASS(CTempClass),CSize(100,100),NULL);
//	m_wndSplitter->RecalcLayout();

	XT_OUTBAR_INFO obi;
	obi.nFolder   = TreeClass;
	obi.nIndex    = mItemData;
	obi.nDragFrom = -1;
	obi.nDragTo   = -1;
//	obi.lpszText  = GetItemText(iIndex);
	obi.bFolder   = false;

	CWnd* pOwner = AfxGetMainWnd();
	ASSERT_VALID(pOwner);

	mSelTree.hCurSelTree = this;
	pOwner->SendMessage(XTWM_OUTBAR_NOTIFY,	OBN_XT_ITEMCLICK, (LPARAM)&obi);
	*pResult = 0;
}

//当第二个参数为true是，此函数仅用来设置被选的项的图表为未选择的图标
LRESULT CMyTreeCtrl::OnReturnPreItem(bool bSameTree, bool bSetUnselIcon)
{
	HTREEITEM hParentItem;
	HTREEITEM hDelItem;

	if(bSetUnselIcon)
	{
		SetItemImage(hCurItem,0,1);
		hParentItem = GetParentItem(hCurItem);
		SelectItem(NULL);
//		return TRUE;
	}

	if(bSameTree)
	{
		if(hPreItem == NULL)
			return FALSE;
		Select(hPreItem,TVGN_CARET);
		hDelItem = hPreItem;
	}
	else
	{
		if(hCurItem == NULL)
			return FALSE;
//		Select(hCurItem,TVGN_CARET);
		hDelItem = hCurItem;
		bChangeBecauseOtherUnsave = true;
	}


	int mDel = GetItemData(hDelItem);

	switch(TreeClass)
	{
	case RTU_TREE:
		if(mPzkIni.mRtuBuf.pValid[mDel])
			break;
		mPzkIni.mRtuBuf.ptempValid[mDel] = false;
		DeleteItem(hDelItem);
		hCurItem = NULL;
		break;
	case PROC_TREE:
		if(mPzkIni.mProcBuf.pValid[mDel])
			break;
		mPzkIni.mProcBuf.ptempValid[mDel] = false;
		DeleteItem(hDelItem);
		hCurItem = NULL;
		break;
	case OBJ_TREE:
		break;
	default:
		break;
	}
	return TRUE;

}


void CMyTreeCtrl::OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	hPreItem = GetSelectedItem();

	*pResult = 0;
}

LRESULT CMyTreeCtrl::OnDeleteNewNote(WPARAM wParam, LPARAM lParam)
{
	BOOL isSameTree = (BOOL)wParam;
	if(GetCount() <= 0)
		return TRUE;
	switch(TreeClass)
	{
	case RTU_TREE:
		if(isSameTree == TRUE)
		{
			if(hPreItem == NULL)
				return FALSE;
			if(mPzkIni.mRtuBuf.ptempValid[GetItemData(hPreItem)])
			{
				mPzkIni.mRtuBuf.ptempValid[GetItemData(hPreItem)] = false;
				DeleteItem(hPreItem);
			}
		}
		else
		{
			if(hCurItem == NULL)
				return FALSE;
			if(mPzkIni.mRtuBuf.ptempValid[GetItemData(hCurItem)])
			{
				mPzkIni.mRtuBuf.ptempValid[GetItemData(hCurItem)] = false;
				DeleteItem(hCurItem);
			}
		}
		break;
	case PROC_TREE:
		if(isSameTree == TRUE)
		{
			if(hPreItem == NULL)
				return FALSE;
			if(mPzkIni.mProcBuf.ptempValid[GetItemData(hPreItem)])
			{
				mPzkIni.mProcBuf.ptempValid[GetItemData(hPreItem)] = false;
				DeleteItem(hPreItem);
			}
		}
		else
		{
			if(hCurItem == NULL)
				return FALSE;
			if(mPzkIni.mProcBuf.ptempValid[GetItemData(hCurItem)])
			{
				mPzkIni.mProcBuf.ptempValid[GetItemData(hCurItem)] = false;
				DeleteItem(hCurItem);
			}
		}
		break;
	}
	/*
	BOOL isCurTree,isSameTree;
	isCurTree = (BOOL)wParam;
	isSameTree = (BOOL)lParam;

	HTREEITEM hRootItem,hTreeItem;
	hRootItem = GetRootItem();

	int count,i,data;
	count = GetCount();

	switch(TreeClass)
	{
	case RTU_TREE:
		for(i=0;i<count;i++)
		{
			if(i==0)
				hTreeItem = GetChildItem(hRootItem);
			else
				hTreeItem = GetNextSiblingItem(hTreeItem);
			data = GetItemData(hTreeItem);
			if(!mPzkIni.mRtuBuf.pValid[data] && mPzkIni.mRtuBuf.ptempValid[data])
			{
				DeleteItem(hTreeItem);
				mPzkIni.mRtuBuf.ptempValid[data] = false;
			}
		}
		break;
	case PROC_TREE:
		for(i=0;i<count;i++)
		{
			if(i==0)
				hTreeItem = GetChildItem(hRootItem);
			else
				hTreeItem = GetNextSiblingItem(hTreeItem);
			data = GetItemData(hTreeItem);
			if(!mPzkIni.mProcBuf.pValid[data] && mPzkIni.mProcBuf.ptempValid[data])
			{
				DeleteItem(hTreeItem);
				mPzkIni.mProcBuf.ptempValid[data] = false;
			}
		}
		break;
	}
	*/
	return TRUE;
}

void CMyTreeCtrl::OnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = GetSelectedItem();

	bSBChange = true;

	*pResult = 0;
}
