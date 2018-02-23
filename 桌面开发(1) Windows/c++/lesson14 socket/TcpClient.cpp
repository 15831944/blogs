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

	SOCKET	sockClient = socket(AF_INET, SOCK_STREAM, 0);

	// 手动指定服务器地址
	SOCKADDR_IN		addrServer;
	addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(6000);

	connect(sockClient, (SOCKADDR *)&addrServer, sizeof(SOCKADDR));

	char recvBuf[100];
	recv(sockClient, recvBuf, 100, 0);
	printf("%s\n", recvBuf);

	const char *c = "This is wanghuiyong";
	send(sockClient, c, strlen(c) + 1, 0);

	closesocket(sockClient);
	WSACleanup();
	system("pause");

}