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

	
	SOCKET		sockClient = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN	addrServer;

	addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(6000);

	sendto(sockClient, "Helo", strlen("Hello") + 1, 0, (SOCKADDR *)&addrServer, sizeof(SOCKADDR));
	closesocket(sockClient);
	WSACleanup();
	system("pause");
}