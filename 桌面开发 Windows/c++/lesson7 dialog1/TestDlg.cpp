// TestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include "afxdialogex.h"


// CTestDlg 对话框

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

// 由框架调用, 需要调用 UpdateData 函数
void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	// 将成员变量和控件内容进行关联(自动生成)
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


// CTestDlg 消息处理程序

// 点击静态按钮时的响应函数(通告消息)
void CTestDlg::OnBnClickedBtnAdd()
{
	// TODO: 在此添加控件通知处理程序代码

	// 创建动态按钮
	/*if (m_blsCreate == false)
	{
		m_blsCreate = true;
		m_btn.Create("按钮", BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD, CRect(0, 0, 100, 50), this, 123);
	}
	else
	{
		m_blsCreate = false;
		m_btn.DestroyWindow();	// 按钮也是窗口
	}*/

	if (!m_btn.m_hWnd)
	{
		m_btn.Create("按钮", BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD, CRect(0, 0, 100, 50), this, 123);
	}
	else
	{
		m_btn.DestroyWindow();
	}

	/* 下面用不同的方式访问控件 */
	int num1 = 0, num2 = 0, num3 = 0;
	char ch1[10], ch2[10], ch3[10];
	/*
	// 第1种方式: 先获取编辑框控件对象, 再获取窗口文本
	// GetDlgItem(IDC_EDIT1)->GetWindowTextA(ch1, 10);
	// GetDlgItem(IDC_EDIT2)->GetWindowTextA(ch2, 10);
	// 第2种方式: 直接获取控件对象的文本, 相当于上一种的组合
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
	// 第3种方式: 直接获取控件对象的数值
	num1 = GetDlgItemInt(IDC_EDIT1);
	num2 = GetDlgItemInt(IDC_EDIT2);
	num3 = num1 + num2;
	SetDlgItemInt(IDC_EDIT3, num3);
	*/

	// 第4种方式: 使用值变量(关联(attach)控件内容)
	/*UpdateData();		// 获取数据
	m_num3 = m_num1 + m_num2;
	UpdateData(false);*/

	// 第5种方式: 使用控件变量(关联(attach)控件本身)
	/*m_Edit1.GetWindowTextA(ch1, 10);
	m_Edit2.GetWindowTextA(ch2, 10);
	num1 = atoi(ch1);
	num2 = atoi(ch2);
	num3 = num1 + num2;
	itoa(num3, ch3, 10);
	m_Edit3.SetWindowTextA(ch3);*/

	// 第6种方式: 发送消息给对话框对象获取文本
	// ::SendMessageA(GetDlgItem(IDC_EDIT1)->m_hWnd, WM_GETTEXT, 10, (LPARAM)ch1);
	// ::SendMessageA(m_Edit1.m_hWnd, WM_GETTEXT, 10, (LPARAM)ch1);
	// GetDlgItem(IDC_EDIT1)->SendMessage(WM_GETTEXT, 10, (LPARAM)ch1);
	//m_Edit1.SendMessage(WM_GETTEXT, 10, (LPARAM)ch1);
	// m_Edit2.SendMessage(WM_GETTEXT, 10, (LPARAM)ch2);
	// 第7种方式: 直接给对话框对象上的子控件发送消息
	SendDlgItemMessage(IDC_EDIT1, WM_GETTEXT, 10, (LPARAM)ch1);
	SendDlgItemMessage(IDC_EDIT2, WM_GETTEXT, 10, (LPARAM)ch2);
	num1 = atoi(ch1);
	num2 = atoi(ch2);
	num3 = num1 + num2;
	itoa(num3, ch3, 10);
	// m_Edit3.SendMessage(WM_SETTEXT, 0, (LPARAM)ch3);
	SendDlgItemMessage(IDC_EDIT3, WM_SETTEXT, 0, (LPARAM)ch3);
	// SendDlgItemMessage(IDC_EDIT3, EM_SETSEL, 1, 3);
	SendDlgItemMessage(IDC_EDIT3, EM_SETSEL, 0, -1);	// 将控件内容设置选中
	m_Edit3.SetFocus();									// 将控件设为焦点
}


void CTestDlg::OnClickedNumber1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_NUMBER1)->GetWindowTextA(str);
	if (str == "Number1")
	{
		GetDlgItem(IDC_NUMBER1)->SetWindowText("数值1");
	}
	else
	{
		GetDlgItem(IDC_NUMBER1)->SetWindowText("Number1");
	}
}


void CTestDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItemText(IDC_BUTTON2, str);
	if (str == "收缩<<")
	{
		SetDlgItemText(IDC_BUTTON2, "扩展>>");
	}
	else
	{
		SetDlgItemText(IDC_BUTTON2, "收缩<<");
	}

	static CRect rectLarge;
	static CRect rectSmall;

	if (rectLarge.IsRectNull())	// 区分 IsRectEmpty
	{
		CRect rectSeparator;
		GetWindowRect(&rectLarge);	// 获取原始对话框大小
		GetDlgItem(IDC_SEPARATOR)->GetWindowRect(&rectSeparator);

		rectSmall.left =rectLarge.left;
		rectSmall.right = rectLarge.right;
		rectSmall.top = rectLarge.top;
		rectSmall.bottom = rectSeparator.bottom;
	}
	if (str == "收缩<<")
	{
		SetWindowPos(nullptr, 0, 0, rectSmall.Width(), rectSmall.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
		SetWindowPos(nullptr, 0, 0, rectLarge.Width(), rectLarge.Height(), SWP_NOMOVE | SWP_NOZORDER);
	}
}

// 将覆盖父类的OnOK函数
void CTestDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	// GetDlgItem(IDC_EDIT1)->GetNextWindow()->SetFocus();
	// GetFocus()->GetNextWindow()->SetFocus();
	// GetFocus()->GetWindow(GW_HWNDNEXT)->SetFocus();
	GetNextDlgTabItem(GetFocus())->SetFocus();

	// CDialog::OnOK();	// 单击确定按钮或按下回车键作用于默认按钮, 则会关闭对话框
}

WNDPROC prevProc;

// 自定义编辑框的窗口过程函数, 注意原型不能变
// 传入的 hwnd 参数即应是编辑框1的句柄
LRESULT CALLBACK WinSunProc(
	HWND	hwnd,
	UINT	uMsg,
	WPARAM	wParam,
	LPARAM	lParam
	)
{
	// 注意窗口过程函数是全局函数, 只能调用SDK函数, 不能调用对话框的成员函数
	if (uMsg == WM_CHAR && wParam == 0x0d)	// 收到输入回车消息
	{
		// ::SetFocus(::GetNextWindow(hwnd, GW_HWNDNEXT));	// 将焦点放在下一个编辑框(试验发现不行, 要依据 tab order 知道谁是下一个)
		//::SetFocus(::GetWindow(hwnd, GW_HWNDNEXT));
		::SetFocus(::GetNextDlgTabItem(::GetParent(hwnd), hwnd, false));	// 父窗口即对话框, 这句好使
		return 1;
	}
	else
	{
		return prevProc(hwnd, uMsg, wParam, lParam);	// 调用原始的窗口过程函数
	}
}

// 类向导在虚函数里找, 而不是消息
BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 重新指定编辑框的窗口过程函数
	prevProc = (WNDPROC)SetWindowLong(GetDlgItem(IDC_EDIT1)->m_hWnd, GWL_WNDPROC, (LONG)WinSunProc);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
