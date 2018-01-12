#include <stdio.h>

#define _VVV int a; int b; char c

int main()
{
	_VVV;
	
	a = 1;
	b = 2;
	c = 3;
	printf("a = %d, b = %d, c = %d\n", a, b, c);
}
