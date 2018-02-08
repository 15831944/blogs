#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int hungry();
int eat_humberger();

int main ()
{
	do{
		eat_humberger();
	}while (hungry());
}

int hungry()
{
	int h;

	scanf("%d", &h);
	if (h != 0)
		return TRUE;
	else
		return FALSE;
}

int eat_humberger()
{	
	static int num = 0;
	printf("ate %d\t", ++num);
	return 0;
}
