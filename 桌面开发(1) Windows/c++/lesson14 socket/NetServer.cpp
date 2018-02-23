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
	char		sendBuf[100];
	char		tempBuf[200];

	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(6000);

	bind(sockServer, (SOCKADDR *)&addrServer, sizeof(SOCKADDR));

	while (1)
	{
		// 接收来自客户端的数据
		recvfrom(sockServer, recvBuf, 100, 0, (SOCKADDR *)&addrClient, &len);
		if ('q' == recvBuf[0])
		{
			sendto(sockServer, "q", strlen("q") + 1, 0, (SOCKADDR *)&addrClient, len);
			printf("Chat Ended!\n");
			break;
		}
		sprintf(tempBuf, "%s says: %s", inet_ntoa(addrClient.sin_addr), recvBuf);
		printf("%s\n", tempBuf);

		// 向客户端发送数据
		printf("I say: ");
		gets(sendBuf);	// 从输入流接收一行数据
		sendto(sockServer, sendBuf, strlen(sendBuf) + 1, 0, (SOCKADDR *)&addrClient, len);
	}

	closesocket(sockServer);
	WSACleanup();
}
