#include <stdio.h>

int main()
{
	int i, j = 0;
	int lines;
	scanf("%d", &lines);
	for (i=lines; i>0; i--)
	{
		printf("%d\n", ++j);
	}
}
