#include <stdio.h>
#include <string.h>
int main()
{
	struct id{
		int number;
		char name [16];
	}a, b;

	a.number = 1;
	strcpy(a.name,"wanghuiyong");
	b = a;
	printf("%d\n", b.number);
	printf("%s\n", b.name);
}
