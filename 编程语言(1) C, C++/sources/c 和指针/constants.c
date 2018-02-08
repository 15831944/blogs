#include <stdio.h>
#include <stdlib.h>



int main ()
{
	printf("EOF = %x %d\n", EOF, EOF);
	printf("NULL = %p\n", NULL);
	printf("NUL = '%c' %d\n", NUL, NUL);
	printf("/377 = %c  %x %d\n", '\377', '\377', '\377');
}
