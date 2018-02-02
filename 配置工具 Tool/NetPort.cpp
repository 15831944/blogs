#include "stdafx.h"
#include "NetPort.h"
#include "MainFrm.h"
#include "usb.h"

#include "xml.h"
#include<winsock2.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>

#pragma comment(lib,"ws2_32.lib")

extern CMainFrame *pFame;
extern TimeOutStru mWaitTimeOut;
extern bool DisPoseXmlStr(struct xmlpgeStru *ppackage);
extern void RelNode(struct nodeStru **pnode);

SocketInterfStru  SocketInterf;

CString ServerIp = "";

char NetRcvBuf[SOCKET_RCV_BUFLEN];	//跟网络应用程序接口
char NetRcvBuf1[SOCKET_RCV_BUFLEN];	//跟维护子进程接口

void InitSocket()
{
	SocketInterf.Socket[0] = SocketInterf.Socket[1] = 0;
	SocketInterf.Port[0] = PORT;
	SocketInterf.Port[1] = PORT1;
	SocketInterf.NetRcvBuf[0] = NetRcvBuf;
	SocketInterf.NetRcvBuf[1] = NetRcvBuf1;
	SocketInterf.RcvGet[0] = SocketInterf.RcvGet[1] = 0;
	SocketInterf.RcvPut[0] = SocketInterf.RcvPut[1] = 0;
}

bool InitNetSocket(int no, CString dstIp)
{
	
	struct sockaddr_in ServerAddr;
	WSADATA WSAData;

	if( WSAStartup( MAKEWORD( 2, 2 ), &WSAData ) )//初始化
	{
		//TRACE( "initializationing error!\n" );
		AfxMessageBox("初始化错误");
		WSACleanup( );
		return false;
	}

	if( ( SocketInterf.Socket[no] = socket( AF_INET, SOCK_STREAM, 0 ) ) == INVALID_SOCKET )
	{
	//	printf( "创建套接字失败!\n" );
		AfxMessageBox("创建套接字失败");
		WSACleanup( );
		exit( 0 );
	}

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(SocketInterf.Port[no]);
	ServerAddr.sin_addr.s_addr = inet_addr(dstIp);
	memset(&(ServerAddr.sin_zero), 0, sizeof(ServerAddr.sin_zero));
	
	int iMode = 1;//1; //0：阻塞
	ioctlsocket(SocketInterf.Socket[no], FIONBIO, (u_long FAR*) &iMode);

	int error=-1, len;
	len = sizeof(int);
	timeval tm;
	fd_set set;
	bool ret = false;
	if( connect(SocketInterf.Socket[no], (struct sockaddr *)&ServerAddr, sizeof(struct sockaddr)) == -1)
	{
		tm.tv_sec = 1;
		tm.tv_usec = 0;
		FD_ZERO(&set);
		FD_SET(SocketInterf.Socket[no], &set);
		if( select(SocketInterf.Socket[no]+1, NULL, &set, NULL, &tm) > 0)
		{
			getsockopt(SocketInterf.Socket[no], SOL_SOCKET, SO_ERROR, (char*)&error, &len);
			if(error == 0) 
				ret = true;
			else 
				ret = false;
		}
		else
			ret = false;
	}
	else
		ret = true;

	if(!ret)
	{
		AfxMessageBox( "连接失败,请确认本机或目标机是否网络正常" );
		WSACleanup( );
		return false;
	}

	iMode = 0;//1; //0：阻塞
	ioctlsocket(SocketInterf.Socket[no], FIONBIO, (u_long FAR*) &iMode);
	int nNetTimeout = 30000;//1秒  
    setsockopt(SocketInterf.Socket[no], SOL_SOCKET, SO_RCVTIMEO, (char*)&nNetTimeout, sizeof(int));          
    SocketInterf.RcvGet[no] = SocketInterf.RcvPut[no] = 0;


	return true;

}

bool CreateALink(int sockno, CString ip)
{
	if(SocketInterf.Socket[sockno] > 0)
	{
		closesocket( SocketInterf.Socket[sockno] );
		WSACleanup( );
	}

	if(!InitNetSocket(sockno, ip))
		return false;

	return true;
}

bool CopyStrToBuf(char *SrcBuf,int SrcLen)
{
	int remainlen;
	int i;

	if(SocketInterf.RcvPut[0] >= SocketInterf.RcvGet[0])
		remainlen = SOCKET_RCV_BUFLEN - (SocketInterf.RcvPut[0] - SocketInterf.RcvGet[0]);
	else
		remainlen = SocketInterf.RcvGet[0] - SocketInterf.RcvPut[0] - 1;

	for(i=0; i<SrcLen; i++)
	{
		SocketInterf.NetRcvBuf[0][SocketInterf.RcvPut[0]++] = SrcBuf[i];
		if (SocketInterf.RcvPut[0] >= SOCKET_RCV_BUFLEN)
			SocketInterf.RcvPut[0] = 0;
		if(SocketInterf.RcvPut[0] == SocketInterf.RcvGet[0])
		{
			SocketInterf.RcvGet[0]++;
			if (SocketInterf.RcvGet[0] >= SOCKET_RCV_BUFLEN)
				SocketInterf.RcvGet[0] = 0;
		}
	}

	if(SrcLen > remainlen)
		return false;

	return true;
}

bool GetAProtlStr(char *srcbuf, int *srcget, int *srcput, char **objbuf, int *objlen)
{
#define FIND_HEAD 0
#define FIND_BODY 1

	int find_state = FIND_HEAD;
	int findhead = 0;
	int findend = 0;
	bool bFindFinish = false;
	int j = 0;
	int findget = *srcget;

	if(mWaitTimeOut.wait_flag == RSP_WAIT_FILE_DATA)
	{
		findhead = *srcget;
		findget = *srcput;
		findend = *srcput;
		bFindFinish = true;
	}
	else
	{
		while((findget != *srcput) && !bFindFinish)
		{
			switch(find_state)
			{
			case FIND_HEAD:
				if(srcbuf[findget] == '$')
				{
					find_state = FIND_BODY;
					findhead = findget;
				}
				break;
			case FIND_BODY:
				if(srcbuf[findget] == '\n')
				{
					bFindFinish = true;
					findend = findget;
				}
				break;
			default:
				break;
			}//end switch
			findget = (findget + 1) % SOCKET_RCV_BUFLEN;
		} //end while
	}
	if(!bFindFinish)
		return false;

	*srcget = findget;	//为什么不=findend，因为找到'\n'后，get要继续向后走一个
	*objlen = findend - findhead;
	if (*objlen < 0)
		*objlen += SOCKET_RCV_BUFLEN;
	*objbuf = (char *)malloc(*objlen+1);

	if(findend >= findhead)
		memcpy(*objbuf, srcbuf+findhead, *objlen);
	else
	{
		j = SOCKET_RCV_BUFLEN - findhead;
		memcpy(*objbuf, &srcbuf[findhead], j);
		memcpy(*objbuf + j, srcbuf, *objlen - j);
	}
	return true;
}


//
//把一个字符缓冲区拷贝给NetRcvBuf，如果溢出则返回false，否则返回true
//这个函数给客户端端用
//
bool CopyStrToBuf1(char *SrcBuf,int SrcLen)
{
	int remainlen;
	int i;

	if(SocketInterf.RcvPut[1] >= SocketInterf.RcvGet[1])
		remainlen = SOCKET_RCV_BUFLEN - (SocketInterf.RcvPut[1] - SocketInterf.RcvGet[1]);
	else
		remainlen = SocketInterf.RcvGet[1] - SocketInterf.RcvPut[1] - 1;

	for(i=0; i<SrcLen; i++)
	{
		SocketInterf.NetRcvBuf[1][SocketInterf.RcvPut[1]++] = SrcBuf[i];
		if (SocketInterf.RcvPut[1] >= SOCKET_RCV_BUFLEN)
			SocketInterf.RcvPut[1] = 0;
		if(SocketInterf.RcvPut[1] == SocketInterf.RcvGet[1])
		{
			SocketInterf.RcvGet[1] += 1;
			if (SocketInterf.RcvGet[1] >= SOCKET_RCV_BUFLEN)
				SocketInterf.RcvGet[1] = 0;
		}
	}

	if(SrcLen > remainlen)
		return false;

	return true;
}

UINT NetRcv(LPVOID para)
{
	char buf[SOCKET_RCV_BUFLEN];
	int numbytes;
	char *protl_str;
	int protl_len;
	CString DebugStr;

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();

	if(SocketInterf.Socket[0])
	{
		numbytes = recv( SocketInterf.Socket[0], buf, SOCKET_RCV_BUFLEN, 0 );
		if(numbytes < 0)
		{
			AfxMessageBox("网络连接中断，请重新连接");
			closesocket( SocketInterf.Socket[0] );
			WSACleanup( );
			SocketInterf.Socket[0] = 0;
//			CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->GetMainWnd();
//			CRightListView *pRView = (CRightListView *)pFrame->GetRightPane();
//			pRView->EnableWindow(FALSE);
			return TRUE;
		}
		CopyStrToBuf(buf, numbytes);
//			DebugStr.Format("%s", buf);
//			pFrame->SendMessage(SHOW_DEBUG_MSG, (WPARAM)&DebugStr);
		if(GetAProtlStr(SocketInterf.NetRcvBuf[0], 
						&(SocketInterf.RcvGet[0]),
						&(SocketInterf.RcvPut[0]),
						&protl_str,
						&protl_len))
		{
//			DebugStr.Format("GetAProtlStr : %s", protl_str);
//			pFrame->SendMessage(SHOW_DEBUG_MSG, (WPARAM)&DebugStr);
//			SetDebugHistory(protl_str, protl_len, true);
			if(!Dispose((unsigned char*)protl_str, protl_len))
				;//RcvGet = RcvPut = 0;
		}
		else
			return FALSE;
//		memset(buf, 0, MAXDATASIZE);
	}

	return TRUE;
}

//
//接收来自维护子进程的数据
//
UINT NetRcv1(LPVOID para)
{
	char buf[SOCKET_RCV_BUFLEN];
	int numbytes;
	CString DebugStr;
	char *xmlstr;
	int xmllen;
	struct xmlpgeStru xmlpge;

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();

	if(SocketInterf.Socket[1])
	{
//		Sleep(1000);
		numbytes = recv( SocketInterf.Socket[1], buf, SOCKET_RCV_BUFLEN, 0 );
		if(numbytes < 0)
		{
			AfxMessageBox("网络连接中断，请重新连接");
			closesocket( SocketInterf.Socket[1] );
			WSACleanup( );
			SocketInterf.Socket[1] = 0;
			return TRUE;
		}

		xmlpge.node = NULL;

		CopyStrToBuf1(buf, numbytes);
/*
		if(bwait_bytes)
		{
			if(GetBytes())
				return FALSE;
		}
		else */if(GetAXmlStr(SocketInterf.NetRcvBuf[1],
							&(SocketInterf.RcvGet[1]),
							&(SocketInterf.RcvPut[1]),
							&xmlstr, &xmllen))
		{
//			SetDebugHistory(xmlstr, xmllen, true);
			if(!ParseXmlStr(xmlstr,xmllen,&xmlpge))
			{
				free(xmlstr);
				return FALSE;
			}
			free(xmlstr);
			if(!DisPoseXmlStr(&xmlpge))
				return FALSE;
			RelNode(&(xmlpge.node));
		}
		else
			return FALSE;
	}

	return TRUE;
}
