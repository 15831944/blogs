#include <stdio.h>
#include <sys/select.h>

int main()
{
	int a;
	fd_set set;
	printf("%d %d\n", sizeof(a), sizeof(set));
}
