#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

/********************************************************************************************************
	监测从键盘输入的可读事件
		若不进行任何输入, 无可读事件, 超时返回
		若仅输入字母, 由于数据并未被送往终端, 超时返回
		若输入字母加回车, 则发生可读事件, 回车本身也算做输入字符
		若输入ctrl-d, 则文件结束符也认为是输入事件, 只不过读取的数据长度为0, 此时若不调用 exit(), 程序会进入死循环
		若输入字母加ctrl-d, 则读取到的数据长度为输入字母数
********************************************************************************************************/
int main()
{
	char			buffer[128];
	int				result, len;
	fd_set			inputs, testinputs;
	struct timeval	timeout;

	FD_ZERO(&inputs);
	FD_SET(0, &inputs);					// 测试标准输入

	while (1)
	{
		testinputs = inputs;			// 每次循环重新初始化文件描述符集
		timeout.tv_sec = 2;
		timeout.tv_usec = 500000;       // 超时等待2.5秒

		result = select(FD_SETSIZE, &testinputs, (fd_set *)NULL, (fd_set *)NULL, &timeout);

		switch(result)
		{
		case 0:
			printf("select timeout\n");
			break;
		case -1:
			perror("select error");
			exit(1);
		default:
			if (FD_ISSET(0, &testinputs))		// 测试描述符是否就绪(标准输入是否有输入并可读)
			{
				ioctl(0, FIONREAD, &len);		// 缓冲区中需要读取的字节数
				if (len == 0)
				{
					printf("eof, read keyboard done\n");	// 标准输入无数据(按下 ctrl + d 组合键), 文件末尾依然认为是可读的
					exit(0);
					// break;
				}
				len = read(0, buffer, len);		// 处理读取内容
				buffer[len] = 0;
				printf("\nread %d chars from keyboard: %s\n", len, buffer);
			}
			break;
		}
	}
}
