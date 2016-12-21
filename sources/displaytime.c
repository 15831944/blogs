#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void displayCurrentTime(const char *string);

/**********************************
	http://www.groad.net/bbs/thread-1064-1-1.html
**********************************/
int main()
{
	fd_set			readfds;
	struct timeval	timeout;
	int				ret;

	FD_ZERO(&readfds);
	FD_SET(0, &readfds);

	timeout.tv_sec = 10;	// 即使在while循环前, timeout 也会随时间流逝而被修改, 不论循环几次, 整个程序最多维持10s
	timeout.tv_usec = 0;

	while (1)
	{
		displayCurrentTime("before select");
		ret = select(1, &readfds, NULL, NULL, &timeout);
		displayCurrentTime("after select");

		switch (ret)
		{
		case 0:
			printf("No data in ten seconds.\n");
			exit(0);
		case -1:
			perror("select error");
			exit(1);
		default:
			getchar();
			printf("Data is availabel now.\n");
		}
	}
	return (0);
}

void displayCurrentTime(const char *string)
{
	int		seconds;

	seconds = time((time_t *)NULL);
	printf("%ds: %s\n", seconds, string);
}
