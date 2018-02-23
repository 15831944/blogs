// Windows Socket Application
#include <stdio.h>
#include <Winsock2.h>	// 项目需要链接 ws2_32.lib 库

void main()
{
	WORD	wVersionRequested;
	WSADATA	wsaData;
	int		err;

	// 加载 WinSock.dll 套接字库, 进行套接字库的版本协商
	// 参数: 版本号, WSADATA 结构体指针
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return;
	}
	if (   LOBYTE(wsaData.wVersion) != 1
		|| HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return;
	}


	SOCKET		sockServer = socket(AF_INET, SOCK_STREAM, 0);
	SOCKET		sockClient;
	SOCKADDR_IN	addrServer;
	SOCKADDR_IN	addrClient;
	int			len = sizeof(SOCKADDR);
	char		sendBuf[100];
	char		recvBuf[100];

	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(6000);	// > 1024

	bind(sockServer, (SOCKADDR *)&addrServer, len);
	listen(sockServer, 5);

	while (1)
	{
		// 接受连接请求, 获取客户端的地址, 地址长度和套接字
		sockClient = accept(sockServer, (SOCKADDR *)&addrClient, &len);
		// 发送
		sprintf(sendBuf, "Welcome %s to http://www.sunxin.org", inet_ntoa(addrClient.sin_addr));
		send(sockClient, sendBuf, strlen(sendBuf) + 1, 0);
		// 接收
		recv(sockClient, recvBuf, 100, 0);
		printf("%s\n", recvBuf);
		// 关闭连接
		closesocket(sockClient);
	}
}