// TestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include "afxdialogex.h"


// CTestDlg �Ի���

IMPLEMENT_DYNAMIC(CTestDlg, CDialog)

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
	, m_blsCreate(false)
{

	num1 = 0;
	m_num1 = 0;
	m_num2 = 0;
	m_num3 = 0;
}

CTestDlg::~CTestDlg()
{
}

// �ɿ�ܵ���, ��Ҫ���� UpdateData ����
void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	// ����Ա�����Ϳؼ����ݽ��й���(�Զ�����)
	DDX_Text(pDX, IDC_EDIT1, m_num1);
	DDX_Text(pDX, IDC_EDIT2, m_num2);
	DDX_Text(pDX, IDC_EDIT3, m_num3);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_EDIT3, m_Edit3);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_ADD, &CTestDlg::OnBnClickedBtnAdd)
	ON_STN_CLICKED(IDC_NUMBER1, &CTestDlg::OnClickedNumber1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CTestDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CTestDlg ��Ϣ�������

// �����̬��ťʱ����Ӧ����(ͨ����Ϣ)
void CTestDlg::OnBnClickedBtnAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// ������̬��ť
	/*if (m_blsCreate == false)
	{
		m_blsCreate = true;
		m_btn.Create("��ť", BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD, CRect(0, 0, 100, 50), this, 123);
	}
	else
	{
		m_blsCreate = false;
		m_btn.DestroyWindow();	// ��ťҲ�Ǵ���
	}*/

	if (!m_btn.m_hWnd)
	{
		m_btn.Create("��ť", BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD, CRect(0, 0, 100, 50), this, 123);
	}
	else
	{
		m_btn.DestroyWindow();
	}

	/* �����ò�ͬ�ķ�ʽ���ʿؼ� */
	int num1 = 0, num2 = 0, num3 = 0;
	char ch1[10], ch2[10], ch3[10];
	/*
	// ��1�ַ�ʽ: �Ȼ�ȡ�༭��ؼ�����, �ٻ�ȡ�����ı�
	// GetDlgItem(IDC_EDIT1)->GetWindowTextA(ch1, 10);
	// GetDlgItem(IDC_EDIT2)->GetWindowTextA(ch2, 10);
	// ��2�ַ�ʽ: ֱ�ӻ�ȡ�ؼ�������ı�, �൱����һ�ֵ����
	GetDlgItemText(IDC_EDIT1, ch1, 10);
	GetDlgItemText(IDC_EDIT2, ch2, 10);

	num1 = atoi(ch1);
	num2 = atoi(ch2);
	num3 = num1 + num2;
	itoa(num3, ch3, 10);

	// GetDlgItem(IDC_EDIT3)->SetWindowTextA(ch3);
	SetDlgItemText(IDC_EDIT3, ch3);
	*/
	/*
	// ��3�ַ�ʽ: ֱ�ӻ�ȡ�ؼ��������ֵ
	num1 = GetDlgItemInt(IDC_EDIT1);
	num2 = GetDlgItemInt(IDC_EDIT2);
	num3 = num1 + num2;
	SetDlgItemInt(IDC_EDIT3, num3);
	*/

	// ��4�ַ�ʽ: ʹ��ֵ����(����(attach)�ؼ�����)
	/*UpdateData();		// ��ȡ����
	m_num3 = m_num1 + m_num2;
	UpdateData(false);*/

	// ��5�ַ�ʽ: ʹ�ÿؼ�����(����(attach)�ؼ�����)
	/*m_Edit1.GetWindowTextA(ch1, 10);
	m_Edit2.GetWindowTextA(ch2, 10);
	num1 = atoi(ch1);
	num2 = atoi(ch2);
	num3 = num1 + num2;
	itoa(num3, ch3, 10);
	m_Edit3.SetWindowTextA(ch3);*/

	// ��6�ַ�ʽ: ������Ϣ���Ի�������ȡ�ı�
	// ::SendMessageA(GetDlgItem(IDC_EDIT1)->m_hWnd, WM_GETTEXT, 10, (LPARAM)ch1);
	// ::SendMessageA(m_Edit1.m_hWnd, WM_GETTEXT, 10, (LPARAM)ch1);
	// GetDlgItem(IDC_EDIT1)->SendMessage(WM_GETTEXT, 10, (LPARAM)ch1);
	//m_Edit1.SendMessage(WM_GETTEXT, 10, (LPARAM)ch1);
	// m_Edit2.SendMessage(WM_GETTEXT, 10, (LPARAM)ch2);
	// ��7�ַ�ʽ: ֱ�Ӹ��Ի�������ϵ��ӿؼ�������Ϣ
	SendDlgItemMessage(IDC_EDIT1, WM_GETTEXT, 10, (LPARAM)ch1);
	SendDlgItemMessage(IDC_EDIT2, WM_GETTEXT, 10, (LPARAM)ch2);
	num1 = atoi(ch1);
	num2 = atoi(ch2);
	num3 = num1 + num2;
	itoa(num3, ch3, 10);
	// m_Edit3.SendMessage(WM_SETTEXT, 0, (LPARAM)ch3);
	SendDlgItemMessage(IDC_EDIT3, WM_SETTEXT, 0, (LPARAM)ch3);
	// SendDlgItemMessage(IDC_EDIT3, EM_SETSEL, 1, 3);
	SendDlgItemMessage(IDC_EDIT3, EM_SETSEL, 0, -1);	// ���ؼ���������ѡ��
	m_Edit3.SetFocus();									// ���ؼ���Ϊ����
}


void CTestDlg::OnClickedNumber1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItem(IDC_NUMBER1)->GetWindowTextA(str);
	if (str == "Number1")
	{
		GetDlgItem(IDC_NUMBER1)->SetWindowText("��ֵ1");
	}
	else
	{
		GetDlgItem(IDC_NUMBER1)->SetWindowText("Number1");
	}
}


void CTestDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItemText(IDC_BUTTON2, str);
	if (str == "����<<")
	{
		SetDlgItemText(IDC_BUTTON2, "��չ>>");
	}
	else
	{
		SetDlgItemText(IDC_BUTTON2, "����<<");
	}

	static CRect rectLarge;
	static CRect rectSmall;

	if (rectLarge.IsRectNull())	// ���� IsRectEmpty
	{
		CRect rectSeparator;
		GetWindowRect(&rectLarge);	// ��ȡԭʼ�Ի����С
		GetDlgItem(IDC_SEPARATOR)->GetWindowRect(&rectSeparator);

		rectSmall.left =rectLarge.left;
		rectSmall.right = rectLarge.right;
		rectSmall.top = rectLarge.top;
		rectSmall.bottom = rectSeparator.bottom;
	}
	if (str == "����<<")
	{
		SetWindowPos(nullptr, 0, 0, rectSmall.Width(), rectSmall.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
		SetWindowPos(nullptr, 0, 0, rectLarge.Width(), rectLarge.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}
}

// �����Ǹ����OnOK����
void CTestDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// GetDlgItem(IDC_EDIT1)->GetNextWindow()->SetFocus();
	// GetFocus()->GetNextWindow()->SetFocus();
	// GetFocus()->GetWindow(GW_HWNDNEXT)->SetFocus();
	GetNextDlgTabItem(GetFocus())->SetFocus();

	// CDialog::OnOK();	// ����ȷ����ť���»س���������Ĭ�ϰ�ť, ���رնԻ���
}

WNDPROC prevProc;

// �Զ���༭��Ĵ��ڹ��̺���, ע��ԭ�Ͳ��ܱ�
// ����� hwnd ������Ӧ�Ǳ༭��1�ľ��
LRESULT CALLBACK WinSunProc(
	HWND	hwnd,
	UINT	uMsg,
	WPARAM	wParam,
	LPARAM	lParam
	)
{
	// ע�ⴰ�ڹ��̺�����ȫ�ֺ���, ֻ�ܵ���SDK����, ���ܵ��öԻ���ĳ�Ա����
	if (uMsg == WM_CHAR && wParam == 0x0d)	// �յ�����س���Ϣ
	{
		// ::SetFocus(::GetNextWindow(hwnd, GW_HWNDNEXT));	// �����������һ���༭��(���鷢�ֲ���, Ҫ���� tab order ֪��˭����һ��)
		//::SetFocus(::GetWindow(hwnd, GW_HWNDNEXT));
		::SetFocus(::GetNextDlgTabItem(::GetParent(hwnd), hwnd, false));	// �����ڼ��Ի���, ����ʹ
		return 1;
	}
	else
	{
		return prevProc(hwnd, uMsg, wParam, lParam);	// ����ԭʼ�Ĵ��ڹ��̺���
	}
}

// �������麯������, ��������Ϣ
BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	// ����ָ���༭��Ĵ��ڹ��̺���
	prevProc = (WNDPROC)SetWindowLong(GetDlgItem(IDC_EDIT1)->m_hWnd, GWL_WNDPROC, (LONG)WinSunProc);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
