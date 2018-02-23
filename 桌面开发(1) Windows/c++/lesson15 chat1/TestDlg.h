
// TestDlg.h : ͷ�ļ�
//

#pragma once


// CTestDlg �Ի���
class CTestDlg : public CDialogEx
{
// ����
public:
	CTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnRecvData(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	BOOL InitSocket(void);
private:
	SOCKET m_socket;	// �����IP��ַ, ��������ͻ���
public:
	static DWORD WINAPI RecvProc(LPVOID lpParameter);
	afx_msg void OnBnClickedBtnSend();
};

struct RECVPARAM
{
	SOCKET	sock;
	HWND	hwnd;
};