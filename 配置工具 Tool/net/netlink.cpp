// netlink.cpp : implementation file
//


#include "stdafx.h"
#include "demo.h"
#include "netlink.h"
#include<winsock2.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>
#include "NetPort.h"

#pragma comment(lib,"ws2_32.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cnetlink dialog
void InitSocket();
bool LoginIn;
extern CStringArray IpArr;
extern bool CreateALink(int sockno, CString ip);

Cnetlink::Cnetlink(CWnd* pParent /*=NULL*/)
	: CDialog(Cnetlink::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cnetlink)
	//}}AFX_DATA_INIT
}


void Cnetlink::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cnetlink)
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cnetlink, CDialog)
	//{{AFX_MSG_MAP(Cnetlink)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	ON_COMMAND(ID_RESET_MK, OnResetMk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cnetlink message handlers

void Cnetlink::OnOK() 
{
	// TODO: Add extra validation here
	
	CString dstIp;
	int i;
	LoginIn = false;
	InitSocket();
	m_Combo.GetWindowText(dstIp);
	if(dstIp.IsEmpty())
	{
		AfxMessageBox("请选择或输入您要连接的服务器地址");
		return ;
	}
	i = 0;
	while(i < IpArr.GetSize())
	{
		if( IpArr.GetAt(i).Compare(dstIp) == 0)
			break;
		i++;
	}

	if(i >= IpArr.GetSize())
	{
		IpArr.Add(dstIp);
		m_Combo.AddString(dstIp);
	}

	//AfxMessageBox(dstIp);
	if(!CreateALink(0, dstIp))
		return;

	LoginIn = true;

	CreateALink(1, dstIp);

	
	
	CDialog::OnOK();
}

void Cnetlink::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void Cnetlink::FindNeighBor()
{
	SOCKET s;
	sockaddr_in addrto;
	WSADATA wsdata;
	BOOL bsocket;
	char *smsg = "where are you?";
	char buffer[256];
	int n;
	m_List.ResetContent();
	WSAStartup(0x0202,&wsdata);
	s=WSASocket(AF_INET,SOCK_DGRAM,0,NULL,0,WSA_FLAG_OVERLAPPED);
	bsocket = TRUE;
	addrto.sin_family= AF_INET;
	addrto.sin_addr.s_addr=INADDR_BROADCAST;
	addrto.sin_port=htons(8001);
	bool opt = true;
	//设置为广播类型
	setsockopt(s,SOL_SOCKET,SO_BROADCAST,(char FAR*)&opt,sizeof(opt));
	
	int iMode=1;//0阻塞
	ioctlsocket(s,FIONBIO,(u_long FAR*)&iMode);

	int nlen = sizeof(addrto);
	int ret=sendto(s,smsg,strlen(smsg)+1,0,(sockaddr *)&addrto,nlen);
	if(ret == SOCKET_ERROR)
	{	
		AfxMessageBox(WSAGetLastError());
		AfxMessageBox("bad");
	}
	else
	{
		Sleep(2000);
		n = 0;
		while(n>=0)
		{
			if((n=recvfrom(s,buffer,256,0,NULL,NULL))>0)
				m_List.AddString(buffer);
		}
	}
	closesocket(s);
	WSACleanup();
}


void Cnetlink::OnButton1() 
{
	// TODO: Add your control notification handler code here
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	FindNeighBor();
	SetCursor(LoadCursor(NULL, IDC_ARROW));	
	
}

void Cnetlink::OnDblclkList1() 
{
	// TODO: Add your control notification handler code here
	int sel = m_List.GetCurSel();
	if(sel < 0)
		return;

	CString ip;
	m_List.GetText(sel, ip);

	int FindComboItem = m_Combo.FindString(0, ip);
	if(FindComboItem >= 0)
		m_Combo.SetCurSel(FindComboItem);
	else
	{ 
		int SelComboItem = m_Combo.AddString(ip);
//		IpArr.Add(ip);
		m_Combo.SetCurSel(SelComboItem);
	}
}

BOOL Cnetlink::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	AfxMessageBox("netlink");
	// TODO: Add extra initialization here
	SetCursor(LoadCursor(NULL, IDC_WAIT));
//	FindNeighBor();
	// TODO: Add extra initialization here
	int i = 0;
	//CString len;
	//len.Format("%d",IpArr.GetSize());
	//AfxMessageBox(len);
	while(i < IpArr.GetSize())
		m_Combo.AddString(IpArr.GetAt(i++));
	m_Combo.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Cnetlink::OnResetMk() 
{
	// TODO: Add your command handler code here
}
