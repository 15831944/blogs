// Windows Socket Application
#include <stdio.h>
#include <Winsock2.h>	// ��Ŀ��Ҫ���� ws2_32.lib ��

void main()
{
	WORD	wVersionRequested;
	WSADATA	wsaData;
	int		err;

	// ���� WinSock.dll �׽��ֿ�, �����׽��ֿ�İ汾Э��
	// ����: �汾��, WSADATA �ṹ��ָ��
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

	// ֻ��Ҫ��, ����Ҫ�������������
	bind(sockServer, (SOCKADDR *)&addrServer, sizeof(SOCKADDR));
	recvfrom(sockServer, recvBuf, 100, 0, (SOCKADDR *)&addrClient, &len);
	printf("%s\n", recvBuf);
	closesocket(sockServer);
	WSACleanup();
	system("pause");
}