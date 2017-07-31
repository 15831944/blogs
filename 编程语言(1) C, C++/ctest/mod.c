#include <stdio.h>


/*******************************************************************************
	利用无符号数的溢出进行队列的遍历, 参考录波程序取上一个周波点的位置的时候
	current		0		1		28		100		127		128		228		255
	last		128		129		156		228		255		0		100		127
*******************************************************************************/

unsigned short lastCyc(unsigned short current);

int main()
{
	unsigned short current;

	printf("%d\n", lastCyc(0));
	printf("%d\n", lastCyc(1));		// 结果为负, 溢出
	printf("%d\n", lastCyc(100));
	printf("%d\n", lastCyc(127));
	printf("%d\n", lastCyc(128));
	printf("%d\n", lastCyc(228));
	printf("%d\n", lastCyc(255));
}

unsigned short lastCyc(unsigned short current)
{
	unsigned short last;

	last = (unsigned short)(current - 128) % 256;

	return last;
}
