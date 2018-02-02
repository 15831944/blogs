#include<winsock2.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>


#define PORT 8887
#define SOCKET_RCV_BUFLEN 10242//4100//4097

#define PORT1 8889

#define MAX_SOCKET_NUM 2	//实现应用需要连接的socket总数
typedef struct {
	int Socket[MAX_SOCKET_NUM];
	int Port[MAX_SOCKET_NUM];
	char *NetRcvBuf[MAX_SOCKET_NUM];
	int RcvGet[MAX_SOCKET_NUM];
	int RcvPut[MAX_SOCKET_NUM];
} SocketInterfStru;

UINT NetRcv(LPVOID para);
UINT NetRcv1(LPVOID para);
