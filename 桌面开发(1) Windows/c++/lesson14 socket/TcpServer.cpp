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
		// ������������, ��ȡ�ͻ��˵ĵ�ַ, ��ַ���Ⱥ��׽���
		sockClient = accept(sockServer, (SOCKADDR *)&addrClient, &len);
		// ����
		sprintf(sendBuf, "Welcome %s to http://www.sunxin.org", inet_ntoa(addrClient.sin_addr));
		send(sockClient, sendBuf, strlen(sendBuf) + 1, 0);
		// ����
		recv(sockClient, recvBuf, 100, 0);
		printf("%s\n", recvBuf);
		// �ر�����
		closesocket(sockClient);
	}
}