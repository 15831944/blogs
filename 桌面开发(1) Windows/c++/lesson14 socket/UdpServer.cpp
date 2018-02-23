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

	SOCKET		sockServer = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN	addrServer;
	SOCKADDR_IN	addrClient;
	int			len = sizeof(SOCKADDR);
	char		recvBuf[100];

	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(6000);

	// 只需要绑定, 不需要监听或接受连接
	bind(sockServer, (SOCKADDR *)&addrServer, sizeof(SOCKADDR));
	recvfrom(sockServer, recvBuf, 100, 0, (SOCKADDR *)&addrClient, &len);
	printf("%s\n", recvBuf);
	closesocket(sockServer);
	WSACleanup();
	system("pause");
}