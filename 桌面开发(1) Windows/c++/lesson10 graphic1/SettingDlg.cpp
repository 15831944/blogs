// SettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "SettingDlg.h"
#include "afxdialogex.h"


// CSettingDlg 对话框

IMPLEMENT_DYNAMIC(CSettingDlg, CDialog)

CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg::IDD, pParent)
	, m_nLineWidth(0)
	, m_nLineStyle(0)
{
	m_clr = RGB(255, 0, 0);
	m_brush.CreateSolidBrush(RGB(0, 0, 255));
	m_font.CreatePointFont(200, "华文行楷");
}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LINE_WIDTH, m_nLineWidth);
	DDX_Radio(pDX, IDC_RADIO1, m_nLineStyle);
	DDX_Control(pDX, IDOK, m_btnTest);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	ON_EN_CHANGE(IDC_LINE_WIDTH, &CSettingDlg::OnChangeLineWidth)
	ON_BN_CLICKED(IDC_RADIO1, &CSettingDlg::OnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CSettingDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CSettingDlg::OnBnClickedRadio3)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSettingDlg 消息处理程序


void CSettingDlg::OnChangeLineWidth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	Invalidate();
}


void CSettingDlg::OnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();
}


void CSettingDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();
}


void CSettingDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();
}


void CSettingDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	UpdateData();	// 获取控件的值
	CPen pen(m_nLineStyle, m_nLineWidth, m_clr);
	dc.SelectObject(&pen);
	CRect rect;
	GetDlgItem(IDC_SAMPLE)->GetWindowRect(&rect);	// 屏幕坐标
	ScreenToClient(rect);
	dc.MoveTo(rect.left + 20, rect.top + rect.Height() / 2);
	dc.LineTo(rect.right - 20, rect.top + rect.Height() / 2);
	// 不为绘图消息调用 CDialog::OnPaint()
}

// 绘制对话框外观
// 对话框所有的子窗口都会分别调用这个函数, 传入各自的 DC
HBRUSH CSettingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (IDC_LINE_STYLE == pWnd->GetDlgCtrlID())	// 获取子窗口控件
	{
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		return m_brush;
	}
	if (IDC_LINE_WIDTH == pWnd->GetDlgCtrlID())
	{
		pDC->SetTextColor(RGB(255, 0, 0));
		// pDC->SetBkMode(TRANSPARENT);
		pDC->SetBkColor(RGB(0, 255, 0));
		return m_brush;
	}
	if (IDC_TEXT == pWnd->GetDlgCtrlID())
	{
		pDC->SelectObject(&m_font);
	}
	if (IDOK == pWnd->GetDlgCtrlID())
	{
		return m_brush;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
