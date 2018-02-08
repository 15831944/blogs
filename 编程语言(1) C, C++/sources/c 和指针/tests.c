#include <stdio.h>
#include <string.h>
int main()
{
	char message[] = "Original_message";
//	char (*p)[64];
	char *p;
	p = strcpy(message, "abcd");
	strcat(p, "haha");
	printf("%s\n", message);
}
