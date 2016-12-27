/********************************************************************
	功能: 文件描述符集操作
	来源: http://www.groad.net/bbs/thread-1064-1-1.html
*********************************************************************/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int main(void)
{
	fd_set		read_set;
	fd_set		write_set;
	int			i, n = 8;

	FD_ZERO(&read_set);
	FD_SET(0, &read_set);
	FD_SET(2, &read_set);
	FD_SET(4, &read_set);
	FD_SET(6, &read_set);
	FD_SET(8, &read_set);

	FD_ZERO(&write_set);
	FD_SET(1, &write_set);
	FD_SET(3, &write_set);

	printf ("read set: \n");
	for (i = 0; i < n; i++)
	{
		printf ("bit %d is %d\n", i, (FD_ISSET(i, &read_set) ? 1/*"set"*/ : 0/*"clear"*/));
	}
	printf ("write set: \n");
	for (i = 0; i < n; i++)
	{
		printf ("bit %d is %d\n", i, (FD_ISSET(i, &write_set) ? 1/*"set"*/ : 0/*"clear"*/));
	}
	printf("%d %d\n", sizeof(int), sizeof(fd_set));

	memcpy(&i, &read_set, sizeof(int));		// 截取文件描述符中的低16位, 注意是低16位
	printf("i = %xH\n", i);

	printf("s = %p\n", &read_set);

	int *p = (int *)&read_set;
	printf("p = %p %xH\n", p, *p);

	char *q = (char *)&read_set + 1;
	printf("q = %p %xH\n", q, *q);
	return (0);
}
