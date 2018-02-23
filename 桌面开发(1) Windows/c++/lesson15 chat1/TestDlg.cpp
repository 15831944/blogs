
// TestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_RECVDATA WM_USER + 1

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestDlg �Ի���




CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_RECVDATA, OnRecvData)
	ON_BN_CLICKED(IDC_BTN_SEND, &CTestDlg::OnBnClickedBtnSend)
END_MESSAGE_MAP()


// CTestDlg ��Ϣ�������

BOOL CTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitSocket();
	RECVPARAM *pRecvParam = new RECVPARAM;
	pRecvParam->sock = m_socket;
	pRecvParam->hwnd = m_hWnd;
	HANDLE hThread = CreateThread(nullptr, 0, RecvProc, (LPVOID)pRecvParam, 0, nullptr);
	CloseHandle(hThread);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CTestDlg::InitSocket(void)
{
	// ��������ͻ����׽��ֳ�ʼ��
	m_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (INVALID_SOCKET == m_socket)
	{
		MessageBox("�׽��ִ���ʧ��!");
		return FALSE;
	}
	// ��������ַ��
	SOCKADDR_IN		addrSock;
	addrSock.sin_family = AF_INET;
	addrSock.sin_port = htons(6000);
	addrSock.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	int rtnval;
	rtnval = bind(m_socket, (SOCKADDR *)&addrSock, sizeof(SOCKADDR));
	if (SOCKET_ERROR == rtnval)
	{
		closesocket(m_socket);
		MessageBox("��ʧ��");
		return FALSE;
	}
	return TRUE;
}

// ����������(���ձ����̺��������̷��͵�����)
DWORD WINAPI CTestDlg::RecvProc(LPVOID lpParameter)
{
	SOCKET		sock = ((RECVPARAM *)lpParameter)->sock;	// ��ʱ������Ϊ�������׽���
	HWND		hwnd = ((RECVPARAM *)lpParameter)->hwnd;
	SOCKADDR_IN	addrFrom;				// �������ӵ������̵Ŀͻ��˵�ַ
	int			len = sizeof(SOCKADDR);
	char		recvBuf[200];
	char		tempBuf[300];
	int			rtnval;

	while (TRUE)
	{
		rtnval = recvfrom(sock, recvBuf, 200, 0, (SOCKADDR *)&addrFrom, &len);
		if (SOCKET_ERROR == rtnval)
		{
			break;
		}
		sprintf(tempBuf, "%s˵: %s", inet_ntoa(addrFrom.sin_addr), recvBuf);
		::PostMessage(hwnd, WM_RECVDATA, 0, (LPARAM)tempBuf);	// ͨ���ڶ�������������������
	}
	return 0;
}

// �������ݴ���
LRESULT CTestDlg::OnRecvData(WPARAM wParam, LPARAM lParam)
{
	CString str = (char *)lParam;
	CString strTemp;
	GetDlgItemText(IDC_EDIT_RECEIVE, strTemp);
	str += "\r\n";
	str += strTemp;
	SetDlgItemText(IDC_EDIT_RECEIVE, str);
	return 0;
}

// �ͻ��˺���
void CTestDlg::OnBnClickedBtnSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// ��ȡIP��ַ�ؼ��е�����
	DWORD dwIP;
	CIPAddressCtrl *pIPAddr = (CIPAddressCtrl *)GetDlgItem(IDC_IPADDRESS1);
	pIPAddr->GetAddress(dwIP);

	// ���͵�Ŀ�������IP��ַ
	SOCKADDR_IN	addrTo;
	addrTo.sin_family = AF_INET;
	addrTo.sin_port = htons(6000);
	addrTo.sin_addr.S_un.S_addr = htonl(dwIP);

	// ��ȡ���ͱ༭����Ҫ���͵���������
	CString strSend;
	GetDlgItemText(IDC_EDIT_SEND, strSend);

	// ����(��ʱ������Ϊ�ͻ����׽���)
	sendto(m_socket, strSend, strSend.GetLength() + 1, 0, (SOCKADDR *)&addrTo, sizeof(SOCKADDR));

	// ��շ��ͱ༭��
	SetDlgItemText(IDC_EDIT_SEND, "");
}
