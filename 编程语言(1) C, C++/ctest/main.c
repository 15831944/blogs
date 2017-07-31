#include <stdio.h>

#define xxxx int yyyy; int zzz; char ccc

int main()
{
	int a = -32767;
	int b = -32768;
	printf("%d\n", sizeof(a));
	printf("a = %d %x\n", a, a);
	printf("b = %d %x\n", b, b);
	
	int c = !(a > b);
	printf("c = %d\n", c);
	
	if (-1)
		printf("a\n");	
	
	printf("%d\n", !-1);
	return 0;
}

