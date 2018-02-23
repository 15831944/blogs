// Sxyj.cpp : implementation file
//

#include "stdafx.h"
#include "demo.h"
#include "Sxyj.h"
#include "ReadPzkIni.h"
#include "MyFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSxyj

CFont font2;

IMPLEMENT_DYNCREATE(CSxyj, CFormView)

CSxyj::CSxyj()
	: CFormView(CSxyj::IDD)
{
	//{{AFX_DATA_INIT(CSxyj)
	m_YxNum = 0;
	m_ProtLineNum = 0;
	m_LineName = _T("");
	m_YcNum = 0;
	m_DeviceName = _T("");
	//}}AFX_DATA_INIT
	bEverEdited = false;
}

CSxyj::~CSxyj()
{
}

void CSxyj::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSxyj)
	DDX_Control(pDX, IDC_EDIT8, m_Input1);
	DDX_Control(pDX, IDC_LIST2, m_List2);
	DDX_Control(pDX, IDC_COMBO1, m_LineNo);
	DDX_Control(pDX, IDC_EDIT2, m_Input);
	DDX_Control(pDX, IDC_LIST1, m_List1);
	DDX_Text(pDX, IDC_EDIT4, m_YxNum);
	DDX_Text(pDX, IDC_EDIT6, m_ProtLineNum);
	DDX_Text(pDX, IDC_EDIT3, m_LineName);
	DDX_Text(pDX, IDC_EDIT5, m_YcNum);
	DDX_Text(pDX, IDC_EDIT1, m_DeviceName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSxyj, CFormView)
	//{{AFX_MSG_MAP(CSxyj)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_EN_KILLFOCUS(IDC_EDIT4, OnKillfocusEdit4)
	ON_EN_CHANGE(IDC_EDIT4, OnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit6)
	ON_EN_KILLFOCUS(IDC_EDIT6, OnKillfocusEdit6)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_EN_KILLFOCUS(IDC_EDIT2, OnKillfocusEdit2)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, OnClickList2)
	ON_EN_KILLFOCUS(IDC_EDIT8, OnKillfocusEdit8)
	ON_EN_CHANGE(IDC_EDIT5, OnChangeEdit5)
	ON_EN_KILLFOCUS(IDC_EDIT5, OnKillfocusEdit5)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_EN_KILLFOCUS(IDC_EDIT3, OnKillfocusEdit3)
	ON_BN_CLICKED(IDC_BUTTON1, OnSave)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, OnCancel)
	//}}AFX_MSG_MAP

	ON_MESSAGE(SAVE_FILE,OnMsgSaveFile)
	ON_MESSAGE(UNSAVE_FILE,OnMsgUnSaveFile)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSxyj diagnostics

#ifdef _DEBUG
void CSxyj::AssertValid() const
{
	CFormView::AssertValid();
}

void CSxyj::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSxyj message handlers

void CSxyj::OnInitialUpdate()
{

	CFormView::OnInitialUpdate();

	//memcpy(&(mPzkIni.SXYJFileTemp),&(mPzkIni.SXYJFile),sizeof(SXYJCfgStru));
	m_ProtLineNum = mPzkIni.SXYJFileTemp.Cfg.ProtLineNum;
	m_DeviceName = mPzkIni.SXYJFileTemp.Cfg.DeviceName;
	UpdateData(UPDATE_WRITE);
	InitListCtrl();
	listArray[0]->ShowWindow(SW_SHOW);
	listArray[1]->ShowWindow(SW_SHOW);

	int i;
	//�����·�������б�
	if(m_ProtLineNum > 0)
	{
		CString formatStr;
		m_LineNo.ResetContent();
		for(i=1; i<=m_ProtLineNum; i++)
		{
			formatStr.Format("��·%d", i);
			m_LineNo.AddString(formatStr);
		}
		m_LineNo.SetCurSel(0);
	}

}

void CSxyj::InitListCtrl()
{

	int i=0;
	int j=0;
	CSize sz;
	sz.cx = sz.cy = 30;
	listArray[0] = &m_List1;
	listArray[1] = &m_List2;
	for(j=0; j<=0; j++)
	{
		listArray[j]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		listArray[j]->ApproximateViewRect(sz,1);
		listArray[j]->InsertColumn(i++, "���", LVCFMT_CENTER, 80, -1);
		listArray[j]->InsertColumn(i++, "����", LVCFMT_CENTER, 200, -1);
		listArray[j]->InsertColumn(i++, "���", LVCFMT_CENTER, 147, -1);

	}


	i=0;
	for(j=1; j<=1; j++)
	{
		listArray[j]->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		listArray[j]->ApproximateViewRect(sz,1);
		listArray[j]->InsertColumn(i++, "���", LVCFMT_LEFT, 50, -1);
		listArray[j]->InsertColumn(i++, "����", LVCFMT_CENTER, 95, -1);
		listArray[j]->InsertColumn(i++, "Scaleϵ��", LVCFMT_CENTER, 70, -1);
		listArray[j]->InsertColumn(i++, "���", LVCFMT_CENTER, 70, -1);
		listArray[j]->InsertColumn(i++, "��λ", LVCFMT_CENTER, 70, -1);
		listArray[j]->InsertColumn(i++, "���", LVCFMT_CENTER, 73, -1);

	}

	CRect rect;
	listArray[0]->GetWindowRect(&rect);
	listArray[1]->GetWindowRect(&rect);

	rect.top -= 80;
	rect.bottom -= 80;

	LoadSxyjConfig(0);

}
void CSxyj::LoadSxyjConfig(int LineNo)
{
	int i;
	int addItem;
	listArray[0]->DeleteAllItems();
	for(i=0; i<mPzkIni.SXYJFileTemp.Line[LineNo].LineCfg.YxNum; i++)
	{
		addItem = listArray[0]->InsertItem(i, Str(i), 0);
		listArray[0]->SetItemData(addItem, i);
		listArray[0]->SetItemText(addItem, 1, mPzkIni.SXYJFileTemp.Line[LineNo].SXYJYXItem[i].Name);
		listArray[0]->SetItemText(addItem,2, mPzkIni.SXYJFileTemp.Line[LineNo].SXYJYXItem[i].dot);
	}

	listArray[1]->DeleteAllItems();
	for(i=0; i<mPzkIni.SXYJFileTemp.Line[LineNo].LineCfg.YcNum; i++)
	{
		addItem = listArray[1]->InsertItem(i, Str(i), 0);
		listArray[1]->SetItemData(addItem, i);
		listArray[1]->SetItemText(addItem, 1, mPzkIni.SXYJFileTemp.Line[LineNo].SXYJYCItem[i].Name);
		listArray[1]->SetItemText(addItem, 2, mPzkIni.SXYJFileTemp.Line[LineNo].SXYJYCItem[i].Divied);
		listArray[1]->SetItemText(addItem, 3, mPzkIni.SXYJFileTemp.Line[LineNo].SXYJYCItem[i].Scale);
		listArray[1]->SetItemText(addItem, 4, mPzkIni.SXYJFileTemp.Line[LineNo].SXYJYCItem[i].Unit);
		listArray[1]->SetItemText(addItem,5, mPzkIni.SXYJFileTemp.Line[LineNo].SXYJYCItem[i].dot);
	}

	m_LineName = mPzkIni.SXYJFileTemp.Line[LineNo].LineCfg.LineName;
	m_YxNum = mPzkIni.SXYJFileTemp.Line[LineNo].LineCfg.YxNum ;
	m_YcNum = mPzkIni.SXYJFileTemp.Line[LineNo].LineCfg.YcNum ;

	m_ProtLineNum = mPzkIni.SXYJFileTemp.Cfg.ProtLineNum;
	m_DeviceName = mPzkIni.SXYJFileTemp.Cfg.DeviceName;

	UpdateData(UPDATE_WRITE);
	yulan();
}

void CSxyj::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

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
	if(nItem < 0)
		return;
	if(nSubItem == 0)
		return;
	else if(nSubItem != 3)
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT2);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT2);
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
	*pResult = 0;

}

void CSxyj::OnKillfocusEdit4() //ң�Ÿ���ʧȥ����
{
	// TODO: Add your control notification handler code here
	int i;
	UpdateData(true);
	i = m_LineNo.GetCurSel();//�ڼ�����·


	if(m_YxNum > 12)
	{
		AfxMessageBox("���ң�Ÿ������ܳ���"+Str(12)+"��!");
		m_YxNum = 12 ;
		UpdateData(UPDATE_WRITE);
	}

	if(m_YxNum < 0)
	{
		AfxMessageBox("��Сң�Ÿ�������С��"+Str(0)+"��!");
		m_YxNum = 1;
		UpdateData(UPDATE_WRITE);//�ؼ���ʾ
	}

	mPzkIni.SXYJFileTemp.Line[i].LineCfg.YxNum	= m_YxNum;
	LoadSxyjConfig(i);
}

void CSxyj::OnChangeEdit4() // ң�Ÿ��������仯
{
	bEverEdited = true;
	UpdateData(true);//���浽����

}

void CSxyj::OnChangeEdit6() //��·���ı�
{
	bEverEdited = true;
	UpdateData(true);//���浽����
}

void CSxyj::OnKillfocusEdit6() //��·��ʧȥ����
{
	UpdateData(UPDATE_READ);
	if(m_ProtLineNum > 24)//��Ŵ�0 ��ʼ��ԭ��
	{
		AfxMessageBox("�����·�����ܳ���"+Str("24��!"));
		m_ProtLineNum = 24;
		UpdateData(UPDATE_WRITE);
	}

	if(m_ProtLineNum <= 0)
	{
		AfxMessageBox("��С��·������С��"+Str(1)+Str("��!"));
		m_ProtLineNum = 1;
		UpdateData(UPDATE_WRITE);
	}
	mPzkIni.SXYJFileTemp.Cfg.ProtLineNum = m_ProtLineNum;//��·��
	m_LineNo.ResetContent();
	if(m_ProtLineNum > 0)
	{
		CString formatStr;
		for(int i=1; i<=m_ProtLineNum; i++)
		{
			formatStr.Format("��·%d", i);
			m_LineNo.AddString(formatStr);
		}
	}
	m_LineNo.SetCurSel(0);
	LoadSxyjConfig(0);
}

void CSxyj::OnSelchangeCombo1() //�л���·��
{
	// TODO: Add your control notification handler code here

	UpdateData(true);//�ӽ��浽����
	int i;
	i = m_LineNo.GetCurSel();//�õ���ǰ��·��
	LoadSxyjConfig(i);
}

void CSxyj::OnKillfocusEdit2() //���ֱ༭ʧȥ����
{
	// TODO: Add your control notification handler code here

	CString str;
	m_Input.GetWindowText(str);
	listArray[0]->SetItemText(nItem, nSubItem, str);

	UpdateData(TRUE);
	int i = m_LineNo.GetCurSel();//�õ���·��
	CString str1;
	str1=str;

	if(nSubItem == 1)//��
	{
		//ע�������ôŪ����ͬ
		 mPzkIni.SXYJFileTemp.Line[i].SXYJYXItem[nItem].Name.Format("%s",str);
	}
	else if(nSubItem == 2)
	{
	//	mPzkIni.SXYJFileTemp.Line[i].SXYJYXItem[nItem].dot = str1;
		mPzkIni.SXYJFileTemp.Line[i].SXYJYXItem[nItem].dot.Format("%s",str);
	}
//	str.Format("%s",mPzkIni.SXYJFileTemp.Line[0].SXYJYXItem[0].Name);
//	AfxMessageBox(str);

	m_Input.ShowWindow(SW_HIDE);
	bEverEdited = true;

}

void CSxyj::OnClickList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	CString str;
	CComboBox *pCombo;
	HWND pWnd;
	Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST2);
    LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
    RECT rect;
    //get the row number
    nItem = temp->iItem;
    //get the column number
    nSubItem = temp->iSubItem;
	if(nItem < 0)
		return;
	if(nSubItem == 0)
		return;
	else if(nSubItem == 1 || nSubItem == 2 || nSubItem == 3 || nSubItem == 4  || nSubItem == 5 )
	{
		pWnd = ::GetDlgItem(m_hWnd,IDC_EDIT8);
		pCombo = (CComboBox *)GetDlgItem(IDC_EDIT8);
		m_Input1.SetWindowText(m_List2.GetItemText(nItem, nSubItem));
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
	*pResult = 0;
}

void CSxyj::OnKillfocusEdit8()
{
	// TODO: Add your control notification handler code here

	CString str;
	m_Input1.GetWindowText(str);

	listArray[1]->SetItemText(nItem, nSubItem, str);


	int i = m_LineNo.GetCurSel();//�õ���·��
	if(nSubItem == 1)
	{
		//ע��
		mPzkIni.SXYJFileTemp.Line[i].SXYJYCItem[nItem].Name.Format("%s",str);
	}
	else if(nSubItem == 2)
	{
		mPzkIni.SXYJFileTemp.Line[i].SXYJYCItem[nItem].Divied.Format("%s",str);
	}
	else if(nSubItem == 3)
	{
		mPzkIni.SXYJFileTemp.Line[i].SXYJYCItem[nItem].Scale.Format("%s",str);
	}
	else if(nSubItem == 4)
	{
		mPzkIni.SXYJFileTemp.Line[i].SXYJYCItem[nItem].Unit.Format("%s",str);
	}
	else if(nSubItem == 5)
	{
		mPzkIni.SXYJFileTemp.Line[i].SXYJYCItem[nItem].dot.Format("%s",str);
	}

	m_Input1.ShowWindow(SW_HIDE);
	bEverEdited = true;
}

void CSxyj::OnChangeEdit5() //ң������仯
{
	bEverEdited = true;
	UpdateData(true);//���浽����
}

void CSxyj::OnKillfocusEdit5()//ң�����ʧȥ����
{
	int i;
	UpdateData(true);
	i = m_LineNo.GetCurSel();//�ڼ�����·

	if(m_YcNum > 12)
	{
		AfxMessageBox("���ң��������ܳ���"+Str(12)+"��!");
		m_YcNum = 12 ;
		UpdateData(UPDATE_WRITE);
	}

	if(m_YcNum < 0)
	{
		AfxMessageBox("��Сң���������С��"+Str(0)+"��!");
		m_YcNum = 1;
		UpdateData(UPDATE_WRITE);//�ؼ���ʾ
	}

	mPzkIni.SXYJFileTemp.Line[i].LineCfg.YcNum	= m_YcNum;
	LoadSxyjConfig(i);
}

void CSxyj::OnChangeEdit3()//��·���仯
{

	int i = m_LineNo.GetCurSel();//�õ���ǰ��·��
	bEverEdited = true;
	UpdateData(TRUE);
	int nLen = strlen(m_LineName);
	if(nLen>20)//20���ַ���10������
	{
		MessageBox("��·���������!","��������",MB_OK);
		m_LineName=m_LineName.Left(20);//��ȡ20���ַ�
		UpdateData(FALSE);
	}
	else
	{
		mPzkIni.SXYJFileTemp.Line[i].LineCfg.LineName=m_LineName;
	}
}

void CSxyj::OnKillfocusEdit3() //��·��ʧȥ����
{
	int i = m_LineNo.GetCurSel();//�õ���ǰ��·��
	UpdateData(TRUE);
	int nLen = strlen(m_LineName);

	if(nLen == 0 )//==0
	{
		AfxMessageBox("��·������Ϊ��!");
	}
	else
	{
		mPzkIni.SXYJFileTemp.Line[i].LineCfg.LineName=m_LineName;
	}
}

void CSxyj::OnSave()//����
{
	mPzkIni.SXYJFile.Cfg.ProtLineNum = mPzkIni.SXYJFileTemp.Cfg.ProtLineNum;
	mPzkIni.SXYJFile.Cfg.DeviceName = mPzkIni.SXYJFileTemp.Cfg.DeviceName;

	int i = m_LineNo.GetCurSel();
	mPzkIni.SXYJFile.Line[i].LineCfg.LineName=mPzkIni.SXYJFileTemp.Line[i].LineCfg.LineName;
	mPzkIni.SXYJFile.Line[i].LineCfg.YxNum=mPzkIni.SXYJFileTemp.Line[i].LineCfg.YxNum;
	mPzkIni.SXYJFile.Line[i].LineCfg.YcNum=mPzkIni.SXYJFileTemp.Line[i].LineCfg.YcNum;


	int j = 0;

	for(j=0; j<mPzkIni.SXYJFileTemp.Line[i].LineCfg.YxNum; j++)
	{
		mPzkIni.SXYJFile.Line[i].SXYJYXItem[j].Name = mPzkIni.SXYJFileTemp.Line[i].SXYJYXItem[j].Name;
		mPzkIni.SXYJFile.Line[i].SXYJYXItem[j].dot = mPzkIni.SXYJFileTemp.Line[i].SXYJYXItem[j].dot;

	}

	for(j=0; j<mPzkIni.SXYJFileTemp.Line[i].LineCfg.YcNum; j++)
	{
		mPzkIni.SXYJFile.Line[i].SXYJYCItem[j].Name = mPzkIni.SXYJFileTemp.Line[i].SXYJYCItem[j].Name;
		mPzkIni.SXYJFile.Line[i].SXYJYCItem[j].Divied = mPzkIni.SXYJFileTemp.Line[i].SXYJYCItem[j].Divied;
		mPzkIni.SXYJFile.Line[i].SXYJYCItem[j].Scale = mPzkIni.SXYJFileTemp.Line[i].SXYJYCItem[j].Scale;
		mPzkIni.SXYJFile.Line[i].SXYJYCItem[j].Unit = mPzkIni.SXYJFileTemp.Line[i].SXYJYCItem[j].Unit;
		mPzkIni.SXYJFile.Line[i].SXYJYCItem[j].dot = mPzkIni.SXYJFileTemp.Line[i].SXYJYCItem[j].dot;
	}

	bEverEdited = false;
	mPzkIni.EverModified = true;
	yulan();
//	15532965286
}


LRESULT CSxyj::OnMsgUnSaveFile(WPARAM wParam, LPARAM lParam)
{
//	OnCANCEl();
	return TRUE;
}

LRESULT CSxyj::OnMsgSaveFile(WPARAM wParam, LPARAM lParam)
{
	if(bEverEdited)
	{
		int i = AfxMessageBox("���浱ǰ�Ա����������������޸���",MB_YESNOCANCEL);
		if(i == IDYES)
			OnSave();
		else if(i == IDCANCEL)
		{
//			bCloseWindow = false;
			return FALSE;
		}
		else
		;//	OnCANCEl();
	}
	return TRUE;
}

void CSxyj::OnChangeEdit1() //�ն����仯
{
	bEverEdited = true;
	UpdateData(TRUE);
	int nLen = strlen(m_DeviceName);
	if(nLen>20)//20���ַ���10������
	{
		MessageBox("�ն����������!","��������",MB_OK);
		m_DeviceName=m_DeviceName.Left(20);//��ȡ20���ַ�
		UpdateData(FALSE);
	}
	else
	{
		mPzkIni.SXYJFileTemp.Cfg.DeviceName=m_DeviceName;
	}
}

void CSxyj::OnKillfocusEdit1() //�ն���ʧȥ����
{
	UpdateData(TRUE);
	int nLen = strlen(m_DeviceName);

	if(nLen == 0 )//==0
	{
		AfxMessageBox("�ն�������Ϊ��!");
	}
	else
	{
		mPzkIni.SXYJFileTemp.Cfg.DeviceName=m_DeviceName;
	}
}

void CSxyj::OnCancel()
{
	mPzkIni.SXYJFileTemp.Cfg.ProtLineNum = mPzkIni.SXYJFile.Cfg.ProtLineNum;
	mPzkIni.SXYJFileTemp.Cfg.DeviceName = mPzkIni.SXYJFile.Cfg.DeviceName;


	int i = m_LineNo.GetCurSel();
	mPzkIni.SXYJFileTemp.Line[i].LineCfg.LineName=mPzkIni.SXYJFile.Line[i].LineCfg.LineName;
	mPzkIni.SXYJFileTemp.Line[i].LineCfg.YxNum=mPzkIni.SXYJFile.Line[i].LineCfg.YxNum;
	mPzkIni.SXYJFileTemp.Line[i].LineCfg.YcNum=mPzkIni.SXYJFile.Line[i].LineCfg.YcNum;


	int j = 0;

	for(j=0; j<mPzkIni.SXYJFileTemp.Line[i].LineCfg.YxNum; j++)
	{
		mPzkIni.SXYJFileTemp.Line[i].SXYJYXItem[j].Name = mPzkIni.SXYJFile.Line[i].SXYJYXItem[j].Name;
		mPzkIni.SXYJFileTemp.Line[i].SXYJYXItem[j].dot = mPzkIni.SXYJFile.Line[i].SXYJYXItem[j].dot;

	}

	for(j=0; j<mPzkIni.SXYJFileTemp.Line[i].LineCfg.YcNum; j++)
	{
		mPzkIni.SXYJFileTemp.Line[i].SXYJYCItem[j].Name = mPzkIni.SXYJFile.Line[i].SXYJYCItem[j].Name;
		mPzkIni.SXYJFileTemp.Line[i].SXYJYCItem[j].Divied = mPzkIni.SXYJFile.Line[i].SXYJYCItem[j].Divied;
		mPzkIni.SXYJFileTemp.Line[i].SXYJYCItem[j].Scale = mPzkIni.SXYJFile.Line[i].SXYJYCItem[j].Scale;
		mPzkIni.SXYJFileTemp.Line[i].SXYJYCItem[j].Unit = mPzkIni.SXYJFile.Line[i].SXYJYCItem[j].Unit;
		mPzkIni.SXYJFileTemp.Line[i].SXYJYCItem[j].dot = mPzkIni.SXYJFile.Line[i].SXYJYCItem[j].dot;
	}
	LoadSxyjConfig(i);
	bEverEdited = false;

}


void CSxyj::yulan()
{

	int i;//��·���
	int j;
	CString str;
	CString str1;
	CString str2;

	for(i=0;i<mPzkIni.SXYJFile.Cfg.ProtLineNum;i++)//N����·
	{
		str+="��·";
		str+=Str(i+1);
		str+=" (";
		str+=mPzkIni.SXYJFile.Line[i].LineCfg.LineName;
		str+=" )";
		str+="    ";
		str+="\r\n";
		str+="ң�Ÿ���:";
		str+=Str(mPzkIni.SXYJFile.Line[i].LineCfg.YxNum);
		str+="\r\n";
		str+="����";
		str+="\t\t";
		str+="���";
		str+="\t";
		str+="\r\n";
		for(j=0;j<mPzkIni.SXYJFile.Line[i].LineCfg.YxNum;j++)
		{
			str+=mPzkIni.SXYJFile.Line[i].SXYJYXItem[j].Name;
			str+="                 ";
			str+=mPzkIni.SXYJFile.Line[i].SXYJYXItem[j].dot;
			str+="\r\n";
		}
		str+="\r\n";
		str+="ң�����:";
		str+=Str(mPzkIni.SXYJFile.Line[i].LineCfg.YcNum);
		str+="\r\n";
		str+="����";
		str+="        ";
		str+="Scaleϵ��";
		str+="      ";
		str+="���";
		str+="      ";
		str+="��λ";
		str+="      ";
		str+="���";
		str+="\r\n";
	//	str+="\r\n";
		for(j=0;j<mPzkIni.SXYJFile.Line[i].LineCfg.YcNum;j++)
		{
			str+=mPzkIni.SXYJFile.Line[i].SXYJYCItem[j].Name;
			str+="             ";
			str+=mPzkIni.SXYJFile.Line[i].SXYJYCItem[j].Divied;
			str+="     ";
			str+=mPzkIni.SXYJFile.Line[i].SXYJYCItem[j].Scale;
			str+="              ";
			str+=mPzkIni.SXYJFile.Line[i].SXYJYCItem[j].Unit;
			str+="     ";
			str+=mPzkIni.SXYJFile.Line[i].SXYJYCItem[j].dot;
			str+="\r\n";
		}


		str+="\r\n";
	}

		CEdit *pEdt=(CEdit*)GetDlgItem(IDC_EDIT7);
		font2.CreatePointFont(100,"Arial");
		pEdt->SetFont(&font2);


	SetDlgItemText(IDC_EDIT7,str);















}
