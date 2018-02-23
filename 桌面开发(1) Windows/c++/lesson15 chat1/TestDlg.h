
// TestDlg.h : 头文件
//

#pragma once


// CTestDlg 对话框
class CTestDlg : public CDialogEx
{
// 构造
public:
	CTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnRecvData(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	BOOL InitSocket(void);
private:
	SOCKET m_socket;	// 自身的IP地址, 服务器或客户端
public:
	static DWORD WINAPI RecvProc(LPVOID lpParameter);
	afx_msg void OnBnClickedBtnSend();
};

struct RECVPARAM
{
	SOCKET	sock;
	HWND	hwnd;
};